#pragma once

#include "quickfix/Application.h"
#include "MessageCrackerImpl.h"

class ApplicationImpl : public FIX::Application
{
public:
	ApplicationImpl(FIX::MessageCracker* messageCracker);

	virtual void onCreate(const FIX::SessionID&) override;

	virtual void onLogon(const FIX::SessionID&) override;
	
	virtual void onLogout(const FIX::SessionID&) override;
	
	virtual void toAdmin(FIX::Message&, const FIX::SessionID&) override;
	
	virtual void toApp(FIX::Message&, const FIX::SessionID&) throw(FIX::DoNotSend)override;
	
	virtual void fromAdmin(const FIX::Message&, const FIX::SessionID&) throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon) override;
	
	virtual void fromApp(const FIX::Message&, const FIX::SessionID&) throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType) override;

private:
	FIX::MessageCracker* m_MessageCracker;

	int m_SenderSeqNum;
};
