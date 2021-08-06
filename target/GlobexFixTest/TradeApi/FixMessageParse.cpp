#include "FixMessageParse.h"
#include "TradeApiCommon.h"
#include "Logger.h"
#include "GlobalParam.h"
#include "WorkThread.h"
#include "MemCacheTemplateSingleton.h"

FixMessageParse::FixMessageParse(TradeSpi* tradeSpi)
	:m_TradeSpi(tradeSpi), m_ParseBuffDataLen(0)
{
	m_CacheList = new CacheList();
	m_FixMessage = new FixMessage();
	m_LogBuff = new char[BUFF_SIZE];
	m_ParseBuff = new char[BUFF_SIZE];
}
FixMessageParse::~FixMessageParse()
{
	delete m_CacheList;
	m_CacheList = nullptr;
	delete m_FixMessage;
	m_FixMessage = nullptr;
	delete [] m_LogBuff;
	m_LogBuff = nullptr;
	delete [] m_ParseBuff;
	m_ParseBuff = nullptr;
}

void FixMessageParse::OnSessionDisConnected()
{
	
}

void FixMessageParse::OnRecv(char* buff, int len)
{
	m_CacheList->PushBack(buff, len);
}

void FixMessageParse::Parse()
{
	while (!m_CacheList->IsEmpty())
	{
		int len = 0;
		int popLen = 0;
		char* data = (char*)m_CacheList->GetData(len);

		int itemLen = 0;
		while (GetItemEnd((char*)data, len - popLen, itemLen))
		{
			int tag = -1;
			string value;
			if (m_ParseBuffDataLen > 0)
			{
				memcpy(m_ParseBuff + m_ParseBuffDataLen, data, itemLen);
				m_ParseBuffDataLen += itemLen;
				if (ParseOneItem(m_ParseBuff, m_ParseBuffDataLen, tag, value))
				{
					m_FixMessage->SetItem(tag, value);
				}
				else
				{
					_ASSERT(false);
				}
				m_ParseBuffDataLen = 0;
			}
			else
			{
				if (ParseOneItem(data, itemLen, tag, value))
				{
					m_FixMessage->SetItem(tag, value);
				}
				else
				{
					_ASSERT(false);
				}
			}
			popLen += itemLen;
			data += itemLen;


			if (tag == 10)
			{
				m_TradeSpi->OnFixMessage(m_FixMessage);
				m_FixMessage = FixMessage::Allocate();
			}
		}
		if (len - popLen > 0)
		{
			memcpy(m_ParseBuff + m_ParseBuffDataLen, data, len - popLen);
			m_ParseBuffDataLen += len - popLen;
		}
		m_CacheList->PopFront(nullptr, len);
	}
	while (WorkThread::GetInstance().NextQueue());
}
