#include "ItsEngine.h"
#include "Logger.h"
#include "ItsUtility.h"
#include "ItsFields.h"
#include "command_id.h"
#include "TimeUtility.h"
#include "Udp.h"
#include "Event.h"


ItsEngine::ItsEngine()
	:m_ItsSubscriber(nullptr), m_Mdb(nullptr)
{
}
ItsEngine::~ItsEngine()
{
	sqlite3_close(m_Mdb);
}
void ItsEngine::RegisterSubscriber(ItsSubscriber* itsSubscriber)
{
	m_ItsSubscriber = itsSubscriber;
	TcpSelectBase::Subscriber(this);
}
bool ItsEngine::Init(const char* dbName)
{
	sqlite3_open(dbName, &m_Mdb);
	ItsMdb::GetInstance().SetDB(m_Mdb);
	ItsMdb::GetInstance().SetCallback(this);
	ItsMdb::GetInstance().CreateAllTables();
	//ItsMdb::GetInstance().SelectAllTables();

	return TcpSelectServer::Init();
}


void ItsEngine::OnRtnOrder(ItsOrder* field)
{
	SendUdp(field);
}
void ItsEngine::OnRtnTrade(ItsTrade* field)
{
	SendUdp(field);
}
void ItsEngine::OnErrRtnOrderCancel(ItsErrRtnOrderCancel* field)
{
	SendUdp(field);
}
void ItsEngine::OnRspOrder(int sessionID, ItsRspOrder* field)
{
	ItsMdb::GetInstance().InsertRecord(field);
	TcpEvent* tcpEvent = TcpEvent::Allocate();
	tcpEvent->EventID = EventSend;
	tcpEvent->SessionID = sessionID;
	auto len = (unsigned short)field->ToStream(tcpEvent->Buff + sizeof(unsigned short), BuffSize - sizeof(unsigned short));
	*(unsigned short*)tcpEvent->Buff = len;
	tcpEvent->Length = len + sizeof(unsigned short);
	OnEvent(tcpEvent);
}

void ItsEngine::OnConnect(int sessionID, const char* ip, int port)
{
	m_SessionIDs.insert(sessionID);
}
void ItsEngine::OnDisConnect(int sessionID, const char* ip, int port)
{
	m_SessionIDs.erase(sessionID);
}
void ItsEngine::OnRecv(TcpEvent* tcpEvent)
{
	m_RecvDatas.push_back(tcpEvent);
}
void ItsEngine::HandleOtherTask()
{
	HandleRecvData();
}

void ItsEngine::HandleRecvData()
{
	while (!m_RecvDatas.empty())
	{
		auto tcpEvent = m_RecvDatas.front();
		m_RecvDatas.pop_front();
		while (tcpEvent->Length > 0)
		{
			int len = *(unsigned short*)(tcpEvent->ReadPos);
			_ASSERT(len + sizeof(unsigned short) == tcpEvent->Length);
			if (tcpEvent->Length < len + sizeof(unsigned short))
			{
				WRITE_LOG(LogLevel::Error, "Invalid Message:[%s] Message len:[%d], recv Length:[%d]", tcpEvent->ReadPos, len + sizeof(unsigned short), tcpEvent->Length);
				return;
			}
			tcpEvent->Shift(sizeof(unsigned short));
			WRITE_LOG(LogLevel::Info, "ItsMsg Len:[%d], Recv:[%s]", len, tcpEvent->ReadPos);

			const char* end = tcpEvent->ReadPos + len;
			m_ItsItems.clear();
			GetItsItems(tcpEvent->ReadPos, end, m_ItsItems);
			tcpEvent->Shift(len);
			if (!CheckItsMessage(m_ItsItems))
			{
				WRITE_LOG(LogLevel::Error, "Invalid Message:[%s], len:[%d]", tcpEvent->ReadPos, len);
				break;;
			}
			auto cmd = atoi(m_ItsItems[1].c_str());
			switch (cmd)
			{
			case CMS_CID_INSERT_ORDER:
			{
				HandleInsertOrder(tcpEvent->SessionID, new ItsInsertOrder(m_ItsItems));
				break;
			}
			case CMS_CID_CANCEL_ORDER:
			{
				HandleCancelOrder(tcpEvent->SessionID, new ItsInsertOrderCancel(m_ItsItems));
				break;
			}
			default:
				break;
			}
		}
		tcpEvent->Free();
	}
}
void ItsEngine::HandleInsertOrder(int sessionID, ItsInsertOrder* itsInsertOrder)
{
	auto it = find_if(m_InsertOrderKeys.begin(), m_InsertOrderKeys.end(), [&](ItsInsertOrderKey* key) {
		return key->TradingDay == itsInsertOrder->TradingDay && key->RequestID == itsInsertOrder->RequestID;
		});
	if (it != m_InsertOrderKeys.end())
	{
		ItsRspOrder itsRspOrder;
		itsRspOrder.ProtocolType = "A";
		itsRspOrder.SequenceNo = itsInsertOrder->SequenceNo;
		itsRspOrder.Reserve1 = "1";
		itsRspOrder.Reserve2 = "0";
		itsRspOrder.ErrorID = "0";
		itsRspOrder.ErrorMsg = "ÖØ¸´±¨µ¥";
		OnRspOrder(sessionID, &itsRspOrder);
		return;
	}
	m_InsertOrderKeys.insert(new ItsInsertOrderKey({ itsInsertOrder->TradingDay, itsInsertOrder->RequestID }));
	ItsMdb::GetInstance().InsertRecord(itsInsertOrder);
	m_ItsSubscriber->ReqInsertOrder(sessionID, itsInsertOrder);
}
void ItsEngine::HandleCancelOrder(int sessionID, ItsInsertOrderCancel* itsInsertOrderCancel)
{
	ItsMdb::GetInstance().InsertRecord(itsInsertOrderCancel);
	m_ItsSubscriber->ReqInsertOrderCancel(sessionID, itsInsertOrderCancel);
}

