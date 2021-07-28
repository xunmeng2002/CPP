#include "ApplicationImpl.h"
#include "Logger.h"
#include "CryptoppEncode.h"
#include "GlobalParam.h"

using namespace std;

ApplicationImpl::ApplicationImpl(FIX::MessageCracker* messageCracker)
	:m_MessageCracker(messageCracker), m_SenderSeqNum(1)
{

}

void ApplicationImpl::onCreate(const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onCreate: SessionID[%s]", sessionID.toString().c_str());
}

void ApplicationImpl::onLogon(const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onLogon: SessionID[%s]", sessionID.toString().c_str());
}

void ApplicationImpl::onLogout(const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onLogout: SessionID[%s]", sessionID.toString().c_str());
}

void ApplicationImpl::toAdmin(FIX::Message& message, const FIX::SessionID& sessionID)
{
	FIX::Header& msgHeader = message.getHeader();
	if (!msgHeader.isSetField(FIX::FIELD::SenderSubID))
	{
		msgHeader.setField(FIX::SenderSubID(sessionID.getSenderCompID().getValue().substr(3).c_str()));
	}
	msgHeader.setField(FIX::TargetSubID("G"));
	msgHeader.setField(FIX::SenderLocationID("CN"));
	

	FIX::MsgType msgType;
	msgHeader.getField(msgType);
	const std::string& strmsgType = msgType.getValue();
	
	FIX::IntField seqNum(34, GlobalParam::GetInstance().GetNextExpectedMsgSeqNum());
	msgHeader.setField(seqNum);
	if (strmsgType == FIX::MsgType_Logon)
	{
		const std::string strRealSenderID = msgHeader.getField(FIX::FIELD::SenderCompID);
		auto strv = strRealSenderID + "U";
		msgHeader.setField(FIX::SenderCompID(strv));

		message.setField(1603, "TEST_BYIFTS");
		message.setField(1604, "1.0");
		message.setField(1605, "Boyee");
		message.setField(1400, "CME-1-SHA-256");

		string accessID = "yViqIrml6RgUhh8xiaMZ";
		string secretKey = "JgVEhx2av_-J_IeUv3JevOH3tiP_voNs9f0CVAISUZc";
		std::string canonicalRequest = GetCanonicalReq(message);
		std::string encodedHmac = calculateHMAC(secretKey, canonicalRequest);

		FIX::IntField encodeLen(354, accessID.length());
		message.setField(encodeLen);
		message.setField(355, accessID);
		message.setField(1400, "CME-1-SHA-256");
		FIX::IntField encodedHmacLen(1401, encodedHmac.length());
		message.setField(encodedHmacLen);
		message.setField(1402, encodedHmac);
	}
	else
	{
		msgHeader.setField(FIX::SenderCompID(GlobalParam::GetInstance().GetSenderCompID()));
	}

	WRITE_LOG(LogLevel::Info, "toAdmin: SessionID[%s], Message: [%s]", sessionID.toString().c_str(), message.toString().c_str());
}

void ApplicationImpl::toApp(FIX::Message& message, const FIX::SessionID& sessionID) throw(FIX::DoNotSend)
{
	WRITE_LOG(LogLevel::Info, "toApp: SessionID[%s], Message: [%s]", sessionID.toString().c_str(), message.toString().c_str());
}

void ApplicationImpl::fromAdmin(const FIX::Message& message, const FIX::SessionID& sessionID) throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon)
{
	WRITE_LOG(LogLevel::Info, "fromAdmin: SessionID[%s], Message: [%s]", sessionID.toString().c_str(), message.toString().c_str());
	
	if (m_MessageCracker != nullptr)
	{
		m_MessageCracker->crack(message, sessionID);
	}
}

void ApplicationImpl::fromApp(const FIX::Message& message, const FIX::SessionID& sessionID) throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType)
{
	WRITE_LOG(LogLevel::Info, "fromApp: SessionID[%s], Message: [%s]", sessionID.toString().c_str(), message.toString().c_str());
	
	if (m_MessageCracker != nullptr)
	{
		m_MessageCracker->crack(message, sessionID);
	}
}
