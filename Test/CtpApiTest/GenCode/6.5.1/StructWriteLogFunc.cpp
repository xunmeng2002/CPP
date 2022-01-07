#include "StructWriteLogFunc.h"
#include "Logger.h"



void WriteDissemination(CThostFtdcDisseminationField* Dissemination)
{
	if(Dissemination)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcDisseminationField: , SequenceSeries[%d]SequenceNo[%d]",
			, Dissemination->SequenceSeriesDissemination->SequenceNo);
	}
}

void WriteReqUserLogin(CThostFtdcReqUserLoginField* ReqUserLogin)
{
	if(ReqUserLogin)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqUserLoginField: , TradingDay[%s]BrokerID[%s], UserID[%s], Password[%s], UserProductInfo[%s], InterfaceProductInfo[%s], ProtocolInfo[%s], MacAddress[%s], OneTimePassword[%s], reserve1[%s], LoginRemark[%s], ClientIPPort[%d], ClientIPAddress[%s]",
			, ReqUserLogin->TradingDayReqUserLogin->BrokerID, ReqUserLogin->UserID, ReqUserLogin->Password, ReqUserLogin->UserProductInfo, ReqUserLogin->InterfaceProductInfo, ReqUserLogin->ProtocolInfo, ReqUserLogin->MacAddress, ReqUserLogin->OneTimePassword, ReqUserLogin->reserve1, ReqUserLogin->LoginRemark, ReqUserLogin->ClientIPPort, ReqUserLogin->ClientIPAddress);
	}
}

void WriteRspUserLogin(CThostFtdcRspUserLoginField* RspUserLogin)
{
	if(RspUserLogin)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRspUserLoginField: , TradingDay[%s]LoginTime[%s], BrokerID[%s], UserID[%s], SystemName[%s], FrontID[%d], SessionID[%d], MaxOrderRef[%s], SHFETime[%s], DCETime[%s], CZCETime[%s], FFEXTime[%s], INETime[%s]",
			, RspUserLogin->TradingDayRspUserLogin->LoginTime, RspUserLogin->BrokerID, RspUserLogin->UserID, RspUserLogin->SystemName, RspUserLogin->FrontID, RspUserLogin->SessionID, RspUserLogin->MaxOrderRef, RspUserLogin->SHFETime, RspUserLogin->DCETime, RspUserLogin->CZCETime, RspUserLogin->FFEXTime, RspUserLogin->INETime);
	}
}

void WriteUserLogout(CThostFtdcUserLogoutField* UserLogout)
{
	if(UserLogout)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcUserLogoutField: , BrokerID[%s]UserID[%s]",
			, UserLogout->BrokerIDUserLogout->UserID);
	}
}

void WriteForceUserLogout(CThostFtdcForceUserLogoutField* ForceUserLogout)
{
	if(ForceUserLogout)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcForceUserLogoutField: , BrokerID[%s]UserID[%s]",
			, ForceUserLogout->BrokerIDForceUserLogout->UserID);
	}
}

void WriteReqAuthenticate(CThostFtdcReqAuthenticateField* ReqAuthenticate)
{
	if(ReqAuthenticate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqAuthenticateField: , BrokerID[%s]UserID[%s], UserProductInfo[%s], AuthCode[%s], AppID[%s]",
			, ReqAuthenticate->BrokerIDReqAuthenticate->UserID, ReqAuthenticate->UserProductInfo, ReqAuthenticate->AuthCode, ReqAuthenticate->AppID);
	}
}

void WriteRspAuthenticate(CThostFtdcRspAuthenticateField* RspAuthenticate)
{
	if(RspAuthenticate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRspAuthenticateField: , BrokerID[%s]UserID[%s], UserProductInfo[%s], AppID[%s], AppType[%c]",
			, RspAuthenticate->BrokerIDRspAuthenticate->UserID, RspAuthenticate->UserProductInfo, RspAuthenticate->AppID, RspAuthenticate->AppType);
	}
}

void WriteAuthenticationInfo(CThostFtdcAuthenticationInfoField* AuthenticationInfo)
{
	if(AuthenticationInfo)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcAuthenticationInfoField: , BrokerID[%s]UserID[%s], UserProductInfo[%s], AuthInfo[%s], IsResult[%d], AppID[%s], AppType[%c], reserve1[%s], ClientIPAddress[%s]",
			, AuthenticationInfo->BrokerIDAuthenticationInfo->UserID, AuthenticationInfo->UserProductInfo, AuthenticationInfo->AuthInfo, AuthenticationInfo->IsResult, AuthenticationInfo->AppID, AuthenticationInfo->AppType, AuthenticationInfo->reserve1, AuthenticationInfo->ClientIPAddress);
	}
}

void WriteRspUserLogin2(CThostFtdcRspUserLogin2Field* RspUserLogin2)
{
	if(RspUserLogin2)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRspUserLogin2Field: , TradingDay[%s]LoginTime[%s], BrokerID[%s], UserID[%s], SystemName[%s], FrontID[%d], SessionID[%d], MaxOrderRef[%s], SHFETime[%s], DCETime[%s], CZCETime[%s], FFEXTime[%s], INETime[%s], RandomString[%s]",
			, RspUserLogin2->TradingDayRspUserLogin2->LoginTime, RspUserLogin2->BrokerID, RspUserLogin2->UserID, RspUserLogin2->SystemName, RspUserLogin2->FrontID, RspUserLogin2->SessionID, RspUserLogin2->MaxOrderRef, RspUserLogin2->SHFETime, RspUserLogin2->DCETime, RspUserLogin2->CZCETime, RspUserLogin2->FFEXTime, RspUserLogin2->INETime, RspUserLogin2->RandomString);
	}
}

void WriteTransferHeader(CThostFtdcTransferHeaderField* TransferHeader)
{
	if(TransferHeader)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTransferHeaderField: , Version[%s]TradeCode[%s], TradeDate[%s], TradeTime[%s], TradeSerial[%s], FutureID[%s], BankID[%s], BankBrchID[%s], OperNo[%s], DeviceID[%s], RecordNum[%s], SessionID[%d], RequestID[%d]",
			, TransferHeader->VersionTransferHeader->TradeCode, TransferHeader->TradeDate, TransferHeader->TradeTime, TransferHeader->TradeSerial, TransferHeader->FutureID, TransferHeader->BankID, TransferHeader->BankBrchID, TransferHeader->OperNo, TransferHeader->DeviceID, TransferHeader->RecordNum, TransferHeader->SessionID, TransferHeader->RequestID);
	}
}

void WriteTransferBankToFutureReq(CThostFtdcTransferBankToFutureReqField* TransferBankToFutureReq)
{
	if(TransferBankToFutureReq)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTransferBankToFutureReqField: , FutureAccount[%s]FuturePwdFlag[%c], FutureAccPwd[%s], TradeAmt[%f], CustFee[%f], CurrencyCode[%s]",
			, TransferBankToFutureReq->FutureAccountTransferBankToFutureReq->FuturePwdFlag, TransferBankToFutureReq->FutureAccPwd, TransferBankToFutureReq->TradeAmt, TransferBankToFutureReq->CustFee, TransferBankToFutureReq->CurrencyCode);
	}
}

void WriteTransferBankToFutureRsp(CThostFtdcTransferBankToFutureRspField* TransferBankToFutureRsp)
{
	if(TransferBankToFutureRsp)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTransferBankToFutureRspField: , RetCode[%s]RetInfo[%s], FutureAccount[%s], TradeAmt[%f], CustFee[%f], CurrencyCode[%s]",
			, TransferBankToFutureRsp->RetCodeTransferBankToFutureRsp->RetInfo, TransferBankToFutureRsp->FutureAccount, TransferBankToFutureRsp->TradeAmt, TransferBankToFutureRsp->CustFee, TransferBankToFutureRsp->CurrencyCode);
	}
}

void WriteTransferFutureToBankReq(CThostFtdcTransferFutureToBankReqField* TransferFutureToBankReq)
{
	if(TransferFutureToBankReq)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTransferFutureToBankReqField: , FutureAccount[%s]FuturePwdFlag[%c], FutureAccPwd[%s], TradeAmt[%f], CustFee[%f], CurrencyCode[%s]",
			, TransferFutureToBankReq->FutureAccountTransferFutureToBankReq->FuturePwdFlag, TransferFutureToBankReq->FutureAccPwd, TransferFutureToBankReq->TradeAmt, TransferFutureToBankReq->CustFee, TransferFutureToBankReq->CurrencyCode);
	}
}

void WriteTransferFutureToBankRsp(CThostFtdcTransferFutureToBankRspField* TransferFutureToBankRsp)
{
	if(TransferFutureToBankRsp)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTransferFutureToBankRspField: , RetCode[%s]RetInfo[%s], FutureAccount[%s], TradeAmt[%f], CustFee[%f], CurrencyCode[%s]",
			, TransferFutureToBankRsp->RetCodeTransferFutureToBankRsp->RetInfo, TransferFutureToBankRsp->FutureAccount, TransferFutureToBankRsp->TradeAmt, TransferFutureToBankRsp->CustFee, TransferFutureToBankRsp->CurrencyCode);
	}
}

void WriteTransferQryBankReq(CThostFtdcTransferQryBankReqField* TransferQryBankReq)
{
	if(TransferQryBankReq)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTransferQryBankReqField: , FutureAccount[%s]FuturePwdFlag[%c], FutureAccPwd[%s], CurrencyCode[%s]",
			, TransferQryBankReq->FutureAccountTransferQryBankReq->FuturePwdFlag, TransferQryBankReq->FutureAccPwd, TransferQryBankReq->CurrencyCode);
	}
}

void WriteTransferQryBankRsp(CThostFtdcTransferQryBankRspField* TransferQryBankRsp)
{
	if(TransferQryBankRsp)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTransferQryBankRspField: , RetCode[%s]RetInfo[%s], FutureAccount[%s], TradeAmt[%f], UseAmt[%f], FetchAmt[%f], CurrencyCode[%s]",
			, TransferQryBankRsp->RetCodeTransferQryBankRsp->RetInfo, TransferQryBankRsp->FutureAccount, TransferQryBankRsp->TradeAmt, TransferQryBankRsp->UseAmt, TransferQryBankRsp->FetchAmt, TransferQryBankRsp->CurrencyCode);
	}
}

void WriteTransferQryDetailReq(CThostFtdcTransferQryDetailReqField* TransferQryDetailReq)
{
	if(TransferQryDetailReq)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTransferQryDetailReqField: , FutureAccount[%s]",
			, TransferQryDetailReq->FutureAccount);
	}
}

void WriteTransferQryDetailRsp(CThostFtdcTransferQryDetailRspField* TransferQryDetailRsp)
{
	if(TransferQryDetailRsp)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTransferQryDetailRspField: , TradeDate[%s]TradeTime[%s], TradeCode[%s], FutureSerial[%d], FutureID[%s], FutureAccount[%s], BankSerial[%d], BankID[%s], BankBrchID[%s], BankAccount[%s], CertCode[%s], CurrencyCode[%s], TxAmount[%f], Flag[%c]",
			, TransferQryDetailRsp->TradeDateTransferQryDetailRsp->TradeTime, TransferQryDetailRsp->TradeCode, TransferQryDetailRsp->FutureSerial, TransferQryDetailRsp->FutureID, TransferQryDetailRsp->FutureAccount, TransferQryDetailRsp->BankSerial, TransferQryDetailRsp->BankID, TransferQryDetailRsp->BankBrchID, TransferQryDetailRsp->BankAccount, TransferQryDetailRsp->CertCode, TransferQryDetailRsp->CurrencyCode, TransferQryDetailRsp->TxAmount, TransferQryDetailRsp->Flag);
	}
}

void WriteRspInfo(CThostFtdcRspInfoField* RspInfo)
{
	if(RspInfo)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRspInfoField: , ErrorID[%d]ErrorMsg[%s]",
			, RspInfo->ErrorIDRspInfo->ErrorMsg);
	}
}

void WriteExchange(CThostFtdcExchangeField* Exchange)
{
	if(Exchange)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExchangeField: , ExchangeID[%s]ExchangeName[%s], ExchangeProperty[%c]",
			, Exchange->ExchangeIDExchange->ExchangeName, Exchange->ExchangeProperty);
	}
}

void WriteProduct(CThostFtdcProductField* Product)
{
	if(Product)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcProductField: , reserve1[%s]ProductName[%s], ExchangeID[%s], ProductClass[%c], VolumeMultiple[%d], PriceTick[%f], MaxMarketOrderVolume[%d], MinMarketOrderVolume[%d], MaxLimitOrderVolume[%d], MinLimitOrderVolume[%d], PositionType[%c], PositionDateType[%c], CloseDealType[%c], TradeCurrencyID[%s], MortgageFundUseRange[%c], reserve2[%s], UnderlyingMultiple[%f], ProductID[%s], ExchangeProductID[%s]",
			, Product->reserve1Product->ProductName, Product->ExchangeID, Product->ProductClass, Product->VolumeMultiple, Product->PriceTick, Product->MaxMarketOrderVolume, Product->MinMarketOrderVolume, Product->MaxLimitOrderVolume, Product->MinLimitOrderVolume, Product->PositionType, Product->PositionDateType, Product->CloseDealType, Product->TradeCurrencyID, Product->MortgageFundUseRange, Product->reserve2, Product->UnderlyingMultiple, Product->ProductID, Product->ExchangeProductID);
	}
}

void WriteInstrument(CThostFtdcInstrumentField* Instrument)
{
	if(Instrument)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInstrumentField: , reserve1[%s]ExchangeID[%s], InstrumentName[%s], reserve2[%s], reserve3[%s], ProductClass[%c], DeliveryYear[%d], DeliveryMonth[%d], MaxMarketOrderVolume[%d], MinMarketOrderVolume[%d], MaxLimitOrderVolume[%d], MinLimitOrderVolume[%d], VolumeMultiple[%d], PriceTick[%f], CreateDate[%s], OpenDate[%s], ExpireDate[%s], StartDelivDate[%s], EndDelivDate[%s], InstLifePhase[%c], IsTrading[%d], PositionType[%c], PositionDateType[%c], LongMarginRatio[%f], ShortMarginRatio[%f], MaxMarginSideAlgorithm[%c], reserve4[%s], StrikePrice[%f], OptionsType[%c], UnderlyingMultiple[%f], CombinationType[%c], InstrumentID[%s], ExchangeInstID[%s], ProductID[%s], UnderlyingInstrID[%s]",
			, Instrument->reserve1Instrument->ExchangeID, Instrument->InstrumentName, Instrument->reserve2, Instrument->reserve3, Instrument->ProductClass, Instrument->DeliveryYear, Instrument->DeliveryMonth, Instrument->MaxMarketOrderVolume, Instrument->MinMarketOrderVolume, Instrument->MaxLimitOrderVolume, Instrument->MinLimitOrderVolume, Instrument->VolumeMultiple, Instrument->PriceTick, Instrument->CreateDate, Instrument->OpenDate, Instrument->ExpireDate, Instrument->StartDelivDate, Instrument->EndDelivDate, Instrument->InstLifePhase, Instrument->IsTrading, Instrument->PositionType, Instrument->PositionDateType, Instrument->LongMarginRatio, Instrument->ShortMarginRatio, Instrument->MaxMarginSideAlgorithm, Instrument->reserve4, Instrument->StrikePrice, Instrument->OptionsType, Instrument->UnderlyingMultiple, Instrument->CombinationType, Instrument->InstrumentID, Instrument->ExchangeInstID, Instrument->ProductID, Instrument->UnderlyingInstrID);
	}
}

void WriteBroker(CThostFtdcBrokerField* Broker)
{
	if(Broker)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcBrokerField: , BrokerID[%s]BrokerAbbr[%s], BrokerName[%s], IsActive[%d]",
			, Broker->BrokerIDBroker->BrokerAbbr, Broker->BrokerName, Broker->IsActive);
	}
}

void WriteTrader(CThostFtdcTraderField* Trader)
{
	if(Trader)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTraderField: , ExchangeID[%s]TraderID[%s], ParticipantID[%s], Password[%s], InstallCount[%d], BrokerID[%s]",
			, Trader->ExchangeIDTrader->TraderID, Trader->ParticipantID, Trader->Password, Trader->InstallCount, Trader->BrokerID);
	}
}

void WriteInvestor(CThostFtdcInvestorField* Investor)
{
	if(Investor)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInvestorField: , InvestorID[%s]BrokerID[%s], InvestorGroupID[%s], InvestorName[%s], IdentifiedCardType[%c], IdentifiedCardNo[%s], IsActive[%d], Telephone[%s], Address[%s], OpenDate[%s], Mobile[%s], CommModelID[%s], MarginModelID[%s]",
			, Investor->InvestorIDInvestor->BrokerID, Investor->InvestorGroupID, Investor->InvestorName, Investor->IdentifiedCardType, Investor->IdentifiedCardNo, Investor->IsActive, Investor->Telephone, Investor->Address, Investor->OpenDate, Investor->Mobile, Investor->CommModelID, Investor->MarginModelID);
	}
}

void WriteTradingCode(CThostFtdcTradingCodeField* TradingCode)
{
	if(TradingCode)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTradingCodeField: , InvestorID[%s]BrokerID[%s], ExchangeID[%s], ClientID[%s], IsActive[%d], ClientIDType[%c], BranchID[%s], BizType[%c], InvestUnitID[%s]",
			, TradingCode->InvestorIDTradingCode->BrokerID, TradingCode->ExchangeID, TradingCode->ClientID, TradingCode->IsActive, TradingCode->ClientIDType, TradingCode->BranchID, TradingCode->BizType, TradingCode->InvestUnitID);
	}
}

void WritePartBroker(CThostFtdcPartBrokerField* PartBroker)
{
	if(PartBroker)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcPartBrokerField: , BrokerID[%s]ExchangeID[%s], ParticipantID[%s], IsActive[%d]",
			, PartBroker->BrokerIDPartBroker->ExchangeID, PartBroker->ParticipantID, PartBroker->IsActive);
	}
}

void WriteSuperUser(CThostFtdcSuperUserField* SuperUser)
{
	if(SuperUser)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSuperUserField: , UserID[%s]UserName[%s], Password[%s], IsActive[%d]",
			, SuperUser->UserIDSuperUser->UserName, SuperUser->Password, SuperUser->IsActive);
	}
}

void WriteSuperUserFunction(CThostFtdcSuperUserFunctionField* SuperUserFunction)
{
	if(SuperUserFunction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSuperUserFunctionField: , UserID[%s]FunctionCode[%c]",
			, SuperUserFunction->UserIDSuperUserFunction->FunctionCode);
	}
}

void WriteInvestorGroup(CThostFtdcInvestorGroupField* InvestorGroup)
{
	if(InvestorGroup)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInvestorGroupField: , BrokerID[%s]InvestorGroupID[%s], InvestorGroupName[%s]",
			, InvestorGroup->BrokerIDInvestorGroup->InvestorGroupID, InvestorGroup->InvestorGroupName);
	}
}

void WriteTradingAccount(CThostFtdcTradingAccountField* TradingAccount)
{
	if(TradingAccount)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTradingAccountField: , BrokerID[%s]AccountID[%s], PreMortgage[%f], PreCredit[%f], PreDeposit[%f], PreBalance[%f], PreMargin[%f], InterestBase[%f], Interest[%f], Deposit[%f], Withdraw[%f], FrozenMargin[%f], FrozenCash[%f], FrozenCommission[%f], CurrMargin[%f], CashIn[%f], Commission[%f], CloseProfit[%f], PositionProfit[%f], Balance[%f], Available[%f], WithdrawQuota[%f], Reserve[%f], TradingDay[%s], SettlementID[%d], Credit[%f], Mortgage[%f], ExchangeMargin[%f], DeliveryMargin[%f], ExchangeDeliveryMargin[%f], ReserveBalance[%f], CurrencyID[%s], PreFundMortgageIn[%f], PreFundMortgageOut[%f], FundMortgageIn[%f], FundMortgageOut[%f], FundMortgageAvailable[%f], MortgageableFund[%f], SpecProductMargin[%f], SpecProductFrozenMargin[%f], SpecProductCommission[%f], SpecProductFrozenCommission[%f], SpecProductPositionProfit[%f], SpecProductCloseProfit[%f], SpecProductPositionProfitByAlg[%f], SpecProductExchangeMargin[%f], BizType[%c], FrozenSwap[%f], RemainSwap[%f]",
			, TradingAccount->BrokerIDTradingAccount->AccountID, TradingAccount->PreMortgage, TradingAccount->PreCredit, TradingAccount->PreDeposit, TradingAccount->PreBalance, TradingAccount->PreMargin, TradingAccount->InterestBase, TradingAccount->Interest, TradingAccount->Deposit, TradingAccount->Withdraw, TradingAccount->FrozenMargin, TradingAccount->FrozenCash, TradingAccount->FrozenCommission, TradingAccount->CurrMargin, TradingAccount->CashIn, TradingAccount->Commission, TradingAccount->CloseProfit, TradingAccount->PositionProfit, TradingAccount->Balance, TradingAccount->Available, TradingAccount->WithdrawQuota, TradingAccount->Reserve, TradingAccount->TradingDay, TradingAccount->SettlementID, TradingAccount->Credit, TradingAccount->Mortgage, TradingAccount->ExchangeMargin, TradingAccount->DeliveryMargin, TradingAccount->ExchangeDeliveryMargin, TradingAccount->ReserveBalance, TradingAccount->CurrencyID, TradingAccount->PreFundMortgageIn, TradingAccount->PreFundMortgageOut, TradingAccount->FundMortgageIn, TradingAccount->FundMortgageOut, TradingAccount->FundMortgageAvailable, TradingAccount->MortgageableFund, TradingAccount->SpecProductMargin, TradingAccount->SpecProductFrozenMargin, TradingAccount->SpecProductCommission, TradingAccount->SpecProductFrozenCommission, TradingAccount->SpecProductPositionProfit, TradingAccount->SpecProductCloseProfit, TradingAccount->SpecProductPositionProfitByAlg, TradingAccount->SpecProductExchangeMargin, TradingAccount->BizType, TradingAccount->FrozenSwap, TradingAccount->RemainSwap);
	}
}

void WriteInvestorPosition(CThostFtdcInvestorPositionField* InvestorPosition)
{
	if(InvestorPosition)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInvestorPositionField: , reserve1[%s]BrokerID[%s], InvestorID[%s], PosiDirection[%c], HedgeFlag[%c], PositionDate[%c], YdPosition[%d], Position[%d], LongFrozen[%d], ShortFrozen[%d], LongFrozenAmount[%f], ShortFrozenAmount[%f], OpenVolume[%d], CloseVolume[%d], OpenAmount[%f], CloseAmount[%f], PositionCost[%f], PreMargin[%f], UseMargin[%f], FrozenMargin[%f], FrozenCash[%f], FrozenCommission[%f], CashIn[%f], Commission[%f], CloseProfit[%f], PositionProfit[%f], PreSettlementPrice[%f], SettlementPrice[%f], TradingDay[%s], SettlementID[%d], OpenCost[%f], ExchangeMargin[%f], CombPosition[%d], CombLongFrozen[%d], CombShortFrozen[%d], CloseProfitByDate[%f], CloseProfitByTrade[%f], TodayPosition[%d], MarginRateByMoney[%f], MarginRateByVolume[%f], StrikeFrozen[%d], StrikeFrozenAmount[%f], AbandonFrozen[%d], ExchangeID[%s], YdStrikeFrozen[%d], InvestUnitID[%s], PositionCostOffset[%f], TasPosition[%d], TasPositionCost[%f], InstrumentID[%s]",
			, InvestorPosition->reserve1InvestorPosition->BrokerID, InvestorPosition->InvestorID, InvestorPosition->PosiDirection, InvestorPosition->HedgeFlag, InvestorPosition->PositionDate, InvestorPosition->YdPosition, InvestorPosition->Position, InvestorPosition->LongFrozen, InvestorPosition->ShortFrozen, InvestorPosition->LongFrozenAmount, InvestorPosition->ShortFrozenAmount, InvestorPosition->OpenVolume, InvestorPosition->CloseVolume, InvestorPosition->OpenAmount, InvestorPosition->CloseAmount, InvestorPosition->PositionCost, InvestorPosition->PreMargin, InvestorPosition->UseMargin, InvestorPosition->FrozenMargin, InvestorPosition->FrozenCash, InvestorPosition->FrozenCommission, InvestorPosition->CashIn, InvestorPosition->Commission, InvestorPosition->CloseProfit, InvestorPosition->PositionProfit, InvestorPosition->PreSettlementPrice, InvestorPosition->SettlementPrice, InvestorPosition->TradingDay, InvestorPosition->SettlementID, InvestorPosition->OpenCost, InvestorPosition->ExchangeMargin, InvestorPosition->CombPosition, InvestorPosition->CombLongFrozen, InvestorPosition->CombShortFrozen, InvestorPosition->CloseProfitByDate, InvestorPosition->CloseProfitByTrade, InvestorPosition->TodayPosition, InvestorPosition->MarginRateByMoney, InvestorPosition->MarginRateByVolume, InvestorPosition->StrikeFrozen, InvestorPosition->StrikeFrozenAmount, InvestorPosition->AbandonFrozen, InvestorPosition->ExchangeID, InvestorPosition->YdStrikeFrozen, InvestorPosition->InvestUnitID, InvestorPosition->PositionCostOffset, InvestorPosition->TasPosition, InvestorPosition->TasPositionCost, InvestorPosition->InstrumentID);
	}
}

void WriteInstrumentMarginRate(CThostFtdcInstrumentMarginRateField* InstrumentMarginRate)
{
	if(InstrumentMarginRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInstrumentMarginRateField: , reserve1[%s]InvestorRange[%c], BrokerID[%s], InvestorID[%s], HedgeFlag[%c], LongMarginRatioByMoney[%f], LongMarginRatioByVolume[%f], ShortMarginRatioByMoney[%f], ShortMarginRatioByVolume[%f], IsRelative[%d], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			, InstrumentMarginRate->reserve1InstrumentMarginRate->InvestorRange, InstrumentMarginRate->BrokerID, InstrumentMarginRate->InvestorID, InstrumentMarginRate->HedgeFlag, InstrumentMarginRate->LongMarginRatioByMoney, InstrumentMarginRate->LongMarginRatioByVolume, InstrumentMarginRate->ShortMarginRatioByMoney, InstrumentMarginRate->ShortMarginRatioByVolume, InstrumentMarginRate->IsRelative, InstrumentMarginRate->ExchangeID, InstrumentMarginRate->InvestUnitID, InstrumentMarginRate->InstrumentID);
	}
}

void WriteInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField* InstrumentCommissionRate)
{
	if(InstrumentCommissionRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInstrumentCommissionRateField: , reserve1[%s]InvestorRange[%c], BrokerID[%s], InvestorID[%s], OpenRatioByMoney[%f], OpenRatioByVolume[%f], CloseRatioByMoney[%f], CloseRatioByVolume[%f], CloseTodayRatioByMoney[%f], CloseTodayRatioByVolume[%f], ExchangeID[%s], BizType[%c], InvestUnitID[%s], InstrumentID[%s]",
			, InstrumentCommissionRate->reserve1InstrumentCommissionRate->InvestorRange, InstrumentCommissionRate->BrokerID, InstrumentCommissionRate->InvestorID, InstrumentCommissionRate->OpenRatioByMoney, InstrumentCommissionRate->OpenRatioByVolume, InstrumentCommissionRate->CloseRatioByMoney, InstrumentCommissionRate->CloseRatioByVolume, InstrumentCommissionRate->CloseTodayRatioByMoney, InstrumentCommissionRate->CloseTodayRatioByVolume, InstrumentCommissionRate->ExchangeID, InstrumentCommissionRate->BizType, InstrumentCommissionRate->InvestUnitID, InstrumentCommissionRate->InstrumentID);
	}
}

void WriteDepthMarketData(CThostFtdcDepthMarketDataField* DepthMarketData)
{
	if(DepthMarketData)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcDepthMarketDataField: , TradingDay[%s]reserve1[%s], ExchangeID[%s], reserve2[%s], LastPrice[%f], PreSettlementPrice[%f], PreClosePrice[%f], PreOpenInterest[%f], OpenPrice[%f], HighestPrice[%f], LowestPrice[%f], Volume[%d], Turnover[%f], OpenInterest[%f], ClosePrice[%f], SettlementPrice[%f], UpperLimitPrice[%f], LowerLimitPrice[%f], PreDelta[%f], CurrDelta[%f], UpdateTime[%s], UpdateMillisec[%d], BidPrice1[%f], BidVolume1[%d], AskPrice1[%f], AskVolume1[%d], BidPrice2[%f], BidVolume2[%d], AskPrice2[%f], AskVolume2[%d], BidPrice3[%f], BidVolume3[%d], AskPrice3[%f], AskVolume3[%d], BidPrice4[%f], BidVolume4[%d], AskPrice4[%f], AskVolume4[%d], BidPrice5[%f], BidVolume5[%d], AskPrice5[%f], AskVolume5[%d], AveragePrice[%f], ActionDay[%s], InstrumentID[%s], ExchangeInstID[%s]",
			, DepthMarketData->TradingDayDepthMarketData->reserve1, DepthMarketData->ExchangeID, DepthMarketData->reserve2, DepthMarketData->LastPrice, DepthMarketData->PreSettlementPrice, DepthMarketData->PreClosePrice, DepthMarketData->PreOpenInterest, DepthMarketData->OpenPrice, DepthMarketData->HighestPrice, DepthMarketData->LowestPrice, DepthMarketData->Volume, DepthMarketData->Turnover, DepthMarketData->OpenInterest, DepthMarketData->ClosePrice, DepthMarketData->SettlementPrice, DepthMarketData->UpperLimitPrice, DepthMarketData->LowerLimitPrice, DepthMarketData->PreDelta, DepthMarketData->CurrDelta, DepthMarketData->UpdateTime, DepthMarketData->UpdateMillisec, DepthMarketData->BidPrice1, DepthMarketData->BidVolume1, DepthMarketData->AskPrice1, DepthMarketData->AskVolume1, DepthMarketData->BidPrice2, DepthMarketData->BidVolume2, DepthMarketData->AskPrice2, DepthMarketData->AskVolume2, DepthMarketData->BidPrice3, DepthMarketData->BidVolume3, DepthMarketData->AskPrice3, DepthMarketData->AskVolume3, DepthMarketData->BidPrice4, DepthMarketData->BidVolume4, DepthMarketData->AskPrice4, DepthMarketData->AskVolume4, DepthMarketData->BidPrice5, DepthMarketData->BidVolume5, DepthMarketData->AskPrice5, DepthMarketData->AskVolume5, DepthMarketData->AveragePrice, DepthMarketData->ActionDay, DepthMarketData->InstrumentID, DepthMarketData->ExchangeInstID);
	}
}

void WriteInstrumentTradingRight(CThostFtdcInstrumentTradingRightField* InstrumentTradingRight)
{
	if(InstrumentTradingRight)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInstrumentTradingRightField: , reserve1[%s]InvestorRange[%c], BrokerID[%s], InvestorID[%s], TradingRight[%c], InstrumentID[%s]",
			, InstrumentTradingRight->reserve1InstrumentTradingRight->InvestorRange, InstrumentTradingRight->BrokerID, InstrumentTradingRight->InvestorID, InstrumentTradingRight->TradingRight, InstrumentTradingRight->InstrumentID);
	}
}

void WriteBrokerUser(CThostFtdcBrokerUserField* BrokerUser)
{
	if(BrokerUser)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcBrokerUserField: , BrokerID[%s]UserID[%s], UserName[%s], UserType[%c], IsActive[%d], IsUsingOTP[%d], IsAuthForce[%d]",
			, BrokerUser->BrokerIDBrokerUser->UserID, BrokerUser->UserName, BrokerUser->UserType, BrokerUser->IsActive, BrokerUser->IsUsingOTP, BrokerUser->IsAuthForce);
	}
}

void WriteBrokerUserPassword(CThostFtdcBrokerUserPasswordField* BrokerUserPassword)
{
	if(BrokerUserPassword)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcBrokerUserPasswordField: , BrokerID[%s]UserID[%s], Password[%s], LastUpdateTime[%s], LastLoginTime[%s], ExpireDate[%s], WeakExpireDate[%s]",
			, BrokerUserPassword->BrokerIDBrokerUserPassword->UserID, BrokerUserPassword->Password, BrokerUserPassword->LastUpdateTime, BrokerUserPassword->LastLoginTime, BrokerUserPassword->ExpireDate, BrokerUserPassword->WeakExpireDate);
	}
}

void WriteBrokerUserFunction(CThostFtdcBrokerUserFunctionField* BrokerUserFunction)
{
	if(BrokerUserFunction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcBrokerUserFunctionField: , BrokerID[%s]UserID[%s], BrokerFunctionCode[%c]",
			, BrokerUserFunction->BrokerIDBrokerUserFunction->UserID, BrokerUserFunction->BrokerFunctionCode);
	}
}

void WriteTraderOffer(CThostFtdcTraderOfferField* TraderOffer)
{
	if(TraderOffer)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTraderOfferField: , ExchangeID[%s]TraderID[%s], ParticipantID[%s], Password[%s], InstallID[%d], OrderLocalID[%s], TraderConnectStatus[%c], ConnectRequestDate[%s], ConnectRequestTime[%s], LastReportDate[%s], LastReportTime[%s], ConnectDate[%s], ConnectTime[%s], StartDate[%s], StartTime[%s], TradingDay[%s], BrokerID[%s], MaxTradeID[%s], MaxOrderMessageReference[%s]",
			, TraderOffer->ExchangeIDTraderOffer->TraderID, TraderOffer->ParticipantID, TraderOffer->Password, TraderOffer->InstallID, TraderOffer->OrderLocalID, TraderOffer->TraderConnectStatus, TraderOffer->ConnectRequestDate, TraderOffer->ConnectRequestTime, TraderOffer->LastReportDate, TraderOffer->LastReportTime, TraderOffer->ConnectDate, TraderOffer->ConnectTime, TraderOffer->StartDate, TraderOffer->StartTime, TraderOffer->TradingDay, TraderOffer->BrokerID, TraderOffer->MaxTradeID, TraderOffer->MaxOrderMessageReference);
	}
}

void WriteSettlementInfo(CThostFtdcSettlementInfoField* SettlementInfo)
{
	if(SettlementInfo)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSettlementInfoField: , TradingDay[%s]SettlementID[%d], BrokerID[%s], InvestorID[%s], SequenceNo[%d], Content[%s], AccountID[%s], CurrencyID[%s]",
			, SettlementInfo->TradingDaySettlementInfo->SettlementID, SettlementInfo->BrokerID, SettlementInfo->InvestorID, SettlementInfo->SequenceNo, SettlementInfo->Content, SettlementInfo->AccountID, SettlementInfo->CurrencyID);
	}
}

void WriteInstrumentMarginRateAdjust(CThostFtdcInstrumentMarginRateAdjustField* InstrumentMarginRateAdjust)
{
	if(InstrumentMarginRateAdjust)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInstrumentMarginRateAdjustField: , reserve1[%s]InvestorRange[%c], BrokerID[%s], InvestorID[%s], HedgeFlag[%c], LongMarginRatioByMoney[%f], LongMarginRatioByVolume[%f], ShortMarginRatioByMoney[%f], ShortMarginRatioByVolume[%f], IsRelative[%d], InstrumentID[%s]",
			, InstrumentMarginRateAdjust->reserve1InstrumentMarginRateAdjust->InvestorRange, InstrumentMarginRateAdjust->BrokerID, InstrumentMarginRateAdjust->InvestorID, InstrumentMarginRateAdjust->HedgeFlag, InstrumentMarginRateAdjust->LongMarginRatioByMoney, InstrumentMarginRateAdjust->LongMarginRatioByVolume, InstrumentMarginRateAdjust->ShortMarginRatioByMoney, InstrumentMarginRateAdjust->ShortMarginRatioByVolume, InstrumentMarginRateAdjust->IsRelative, InstrumentMarginRateAdjust->InstrumentID);
	}
}

void WriteExchangeMarginRate(CThostFtdcExchangeMarginRateField* ExchangeMarginRate)
{
	if(ExchangeMarginRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExchangeMarginRateField: , BrokerID[%s]reserve1[%s], HedgeFlag[%c], LongMarginRatioByMoney[%f], LongMarginRatioByVolume[%f], ShortMarginRatioByMoney[%f], ShortMarginRatioByVolume[%f], ExchangeID[%s], InstrumentID[%s]",
			, ExchangeMarginRate->BrokerIDExchangeMarginRate->reserve1, ExchangeMarginRate->HedgeFlag, ExchangeMarginRate->LongMarginRatioByMoney, ExchangeMarginRate->LongMarginRatioByVolume, ExchangeMarginRate->ShortMarginRatioByMoney, ExchangeMarginRate->ShortMarginRatioByVolume, ExchangeMarginRate->ExchangeID, ExchangeMarginRate->InstrumentID);
	}
}

void WriteExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField* ExchangeMarginRateAdjust)
{
	if(ExchangeMarginRateAdjust)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExchangeMarginRateAdjustField: , BrokerID[%s]reserve1[%s], HedgeFlag[%c], LongMarginRatioByMoney[%f], LongMarginRatioByVolume[%f], ShortMarginRatioByMoney[%f], ShortMarginRatioByVolume[%f], ExchLongMarginRatioByMoney[%f], ExchLongMarginRatioByVolume[%f], ExchShortMarginRatioByMoney[%f], ExchShortMarginRatioByVolume[%f], NoLongMarginRatioByMoney[%f], NoLongMarginRatioByVolume[%f], NoShortMarginRatioByMoney[%f], NoShortMarginRatioByVolume[%f], InstrumentID[%s]",
			, ExchangeMarginRateAdjust->BrokerIDExchangeMarginRateAdjust->reserve1, ExchangeMarginRateAdjust->HedgeFlag, ExchangeMarginRateAdjust->LongMarginRatioByMoney, ExchangeMarginRateAdjust->LongMarginRatioByVolume, ExchangeMarginRateAdjust->ShortMarginRatioByMoney, ExchangeMarginRateAdjust->ShortMarginRatioByVolume, ExchangeMarginRateAdjust->ExchLongMarginRatioByMoney, ExchangeMarginRateAdjust->ExchLongMarginRatioByVolume, ExchangeMarginRateAdjust->ExchShortMarginRatioByMoney, ExchangeMarginRateAdjust->ExchShortMarginRatioByVolume, ExchangeMarginRateAdjust->NoLongMarginRatioByMoney, ExchangeMarginRateAdjust->NoLongMarginRatioByVolume, ExchangeMarginRateAdjust->NoShortMarginRatioByMoney, ExchangeMarginRateAdjust->NoShortMarginRatioByVolume, ExchangeMarginRateAdjust->InstrumentID);
	}
}

void WriteExchangeRate(CThostFtdcExchangeRateField* ExchangeRate)
{
	if(ExchangeRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExchangeRateField: , BrokerID[%s]FromCurrencyID[%s], FromCurrencyUnit[%f], ToCurrencyID[%s], ExchangeRate[%f]",
			, ExchangeRate->BrokerIDExchangeRate->FromCurrencyID, ExchangeRate->FromCurrencyUnit, ExchangeRate->ToCurrencyID, ExchangeRate->ExchangeRate);
	}
}

void WriteSettlementRef(CThostFtdcSettlementRefField* SettlementRef)
{
	if(SettlementRef)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSettlementRefField: , TradingDay[%s]SettlementID[%d]",
			, SettlementRef->TradingDaySettlementRef->SettlementID);
	}
}

void WriteCurrentTime(CThostFtdcCurrentTimeField* CurrentTime)
{
	if(CurrentTime)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcCurrentTimeField: , CurrDate[%s]CurrTime[%s], CurrMillisec[%d], ActionDay[%s]",
			, CurrentTime->CurrDateCurrentTime->CurrTime, CurrentTime->CurrMillisec, CurrentTime->ActionDay);
	}
}

void WriteCommPhase(CThostFtdcCommPhaseField* CommPhase)
{
	if(CommPhase)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcCommPhaseField: , TradingDay[%s]CommPhaseNo[%d], SystemID[%s]",
			, CommPhase->TradingDayCommPhase->CommPhaseNo, CommPhase->SystemID);
	}
}

void WriteLoginInfo(CThostFtdcLoginInfoField* LoginInfo)
{
	if(LoginInfo)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcLoginInfoField: , FrontID[%d]SessionID[%d], BrokerID[%s], UserID[%s], LoginDate[%s], LoginTime[%s], reserve1[%s], UserProductInfo[%s], InterfaceProductInfo[%s], ProtocolInfo[%s], SystemName[%s], PasswordDeprecated[%s], MaxOrderRef[%s], SHFETime[%s], DCETime[%s], CZCETime[%s], FFEXTime[%s], MacAddress[%s], OneTimePassword[%s], INETime[%s], IsQryControl[%d], LoginRemark[%s], Password[%s], IPAddress[%s]",
			, LoginInfo->FrontIDLoginInfo->SessionID, LoginInfo->BrokerID, LoginInfo->UserID, LoginInfo->LoginDate, LoginInfo->LoginTime, LoginInfo->reserve1, LoginInfo->UserProductInfo, LoginInfo->InterfaceProductInfo, LoginInfo->ProtocolInfo, LoginInfo->SystemName, LoginInfo->PasswordDeprecated, LoginInfo->MaxOrderRef, LoginInfo->SHFETime, LoginInfo->DCETime, LoginInfo->CZCETime, LoginInfo->FFEXTime, LoginInfo->MacAddress, LoginInfo->OneTimePassword, LoginInfo->INETime, LoginInfo->IsQryControl, LoginInfo->LoginRemark, LoginInfo->Password, LoginInfo->IPAddress);
	}
}

void WriteLogoutAll(CThostFtdcLogoutAllField* LogoutAll)
{
	if(LogoutAll)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcLogoutAllField: , FrontID[%d]SessionID[%d], SystemName[%s]",
			, LogoutAll->FrontIDLogoutAll->SessionID, LogoutAll->SystemName);
	}
}

void WriteFrontStatus(CThostFtdcFrontStatusField* FrontStatus)
{
	if(FrontStatus)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcFrontStatusField: , FrontID[%d]LastReportDate[%s], LastReportTime[%s], IsActive[%d]",
			, FrontStatus->FrontIDFrontStatus->LastReportDate, FrontStatus->LastReportTime, FrontStatus->IsActive);
	}
}

void WriteUserPasswordUpdate(CThostFtdcUserPasswordUpdateField* UserPasswordUpdate)
{
	if(UserPasswordUpdate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcUserPasswordUpdateField: , BrokerID[%s]UserID[%s], OldPassword[%s], NewPassword[%s]",
			, UserPasswordUpdate->BrokerIDUserPasswordUpdate->UserID, UserPasswordUpdate->OldPassword, UserPasswordUpdate->NewPassword);
	}
}

void WriteInputOrder(CThostFtdcInputOrderField* InputOrder)
{
	if(InputOrder)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInputOrderField: , BrokerID[%s]InvestorID[%s], reserve1[%s], OrderRef[%s], UserID[%s], OrderPriceType[%c], Direction[%c], CombOffsetFlag[%s], CombHedgeFlag[%s], LimitPrice[%f], VolumeTotalOriginal[%d], TimeCondition[%c], GTDDate[%s], VolumeCondition[%c], MinVolume[%d], ContingentCondition[%c], StopPrice[%f], ForceCloseReason[%c], IsAutoSuspend[%d], BusinessUnit[%s], RequestID[%d], UserForceClose[%d], IsSwapOrder[%d], ExchangeID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], ClientID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			, InputOrder->BrokerIDInputOrder->InvestorID, InputOrder->reserve1, InputOrder->OrderRef, InputOrder->UserID, InputOrder->OrderPriceType, InputOrder->Direction, InputOrder->CombOffsetFlag, InputOrder->CombHedgeFlag, InputOrder->LimitPrice, InputOrder->VolumeTotalOriginal, InputOrder->TimeCondition, InputOrder->GTDDate, InputOrder->VolumeCondition, InputOrder->MinVolume, InputOrder->ContingentCondition, InputOrder->StopPrice, InputOrder->ForceCloseReason, InputOrder->IsAutoSuspend, InputOrder->BusinessUnit, InputOrder->RequestID, InputOrder->UserForceClose, InputOrder->IsSwapOrder, InputOrder->ExchangeID, InputOrder->InvestUnitID, InputOrder->AccountID, InputOrder->CurrencyID, InputOrder->ClientID, InputOrder->reserve2, InputOrder->MacAddress, InputOrder->InstrumentID, InputOrder->IPAddress);
	}
}

void WriteOrder(CThostFtdcOrderField* Order)
{
	if(Order)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcOrderField: , BrokerID[%s]InvestorID[%s], reserve1[%s], OrderRef[%s], UserID[%s], OrderPriceType[%c], Direction[%c], CombOffsetFlag[%s], CombHedgeFlag[%s], LimitPrice[%f], VolumeTotalOriginal[%d], TimeCondition[%c], GTDDate[%s], VolumeCondition[%c], MinVolume[%d], ContingentCondition[%c], StopPrice[%f], ForceCloseReason[%c], IsAutoSuspend[%d], BusinessUnit[%s], RequestID[%d], OrderLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve2[%s], TraderID[%s], InstallID[%d], OrderSubmitStatus[%c], NotifySequence[%d], TradingDay[%s], SettlementID[%d], OrderSysID[%s], OrderSource[%c], OrderStatus[%c], OrderType[%c], VolumeTraded[%d], VolumeTotal[%d], InsertDate[%s], InsertTime[%s], ActiveTime[%s], SuspendTime[%s], UpdateTime[%s], CancelTime[%s], ActiveTraderID[%s], ClearingPartID[%s], SequenceNo[%d], FrontID[%d], SessionID[%d], UserProductInfo[%s], StatusMsg[%s], UserForceClose[%d], ActiveUserID[%s], BrokerOrderSeq[%d], RelativeOrderSysID[%s], ZCETotalTradedVolume[%d], IsSwapOrder[%d], BranchID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], reserve3[%s], MacAddress[%s], InstrumentID[%s], ExchangeInstID[%s], IPAddress[%s]",
			, Order->BrokerIDOrder->InvestorID, Order->reserve1, Order->OrderRef, Order->UserID, Order->OrderPriceType, Order->Direction, Order->CombOffsetFlag, Order->CombHedgeFlag, Order->LimitPrice, Order->VolumeTotalOriginal, Order->TimeCondition, Order->GTDDate, Order->VolumeCondition, Order->MinVolume, Order->ContingentCondition, Order->StopPrice, Order->ForceCloseReason, Order->IsAutoSuspend, Order->BusinessUnit, Order->RequestID, Order->OrderLocalID, Order->ExchangeID, Order->ParticipantID, Order->ClientID, Order->reserve2, Order->TraderID, Order->InstallID, Order->OrderSubmitStatus, Order->NotifySequence, Order->TradingDay, Order->SettlementID, Order->OrderSysID, Order->OrderSource, Order->OrderStatus, Order->OrderType, Order->VolumeTraded, Order->VolumeTotal, Order->InsertDate, Order->InsertTime, Order->ActiveTime, Order->SuspendTime, Order->UpdateTime, Order->CancelTime, Order->ActiveTraderID, Order->ClearingPartID, Order->SequenceNo, Order->FrontID, Order->SessionID, Order->UserProductInfo, Order->StatusMsg, Order->UserForceClose, Order->ActiveUserID, Order->BrokerOrderSeq, Order->RelativeOrderSysID, Order->ZCETotalTradedVolume, Order->IsSwapOrder, Order->BranchID, Order->InvestUnitID, Order->AccountID, Order->CurrencyID, Order->reserve3, Order->MacAddress, Order->InstrumentID, Order->ExchangeInstID, Order->IPAddress);
	}
}

void WriteExchangeOrder(CThostFtdcExchangeOrderField* ExchangeOrder)
{
	if(ExchangeOrder)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExchangeOrderField: , OrderPriceType[%c]Direction[%c], CombOffsetFlag[%s], CombHedgeFlag[%s], LimitPrice[%f], VolumeTotalOriginal[%d], TimeCondition[%c], GTDDate[%s], VolumeCondition[%c], MinVolume[%d], ContingentCondition[%c], StopPrice[%f], ForceCloseReason[%c], IsAutoSuspend[%d], BusinessUnit[%s], RequestID[%d], OrderLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve1[%s], TraderID[%s], InstallID[%d], OrderSubmitStatus[%c], NotifySequence[%d], TradingDay[%s], SettlementID[%d], OrderSysID[%s], OrderSource[%c], OrderStatus[%c], OrderType[%c], VolumeTraded[%d], VolumeTotal[%d], InsertDate[%s], InsertTime[%s], ActiveTime[%s], SuspendTime[%s], UpdateTime[%s], CancelTime[%s], ActiveTraderID[%s], ClearingPartID[%s], SequenceNo[%d], BranchID[%s], reserve2[%s], MacAddress[%s], ExchangeInstID[%s], IPAddress[%s]",
			, ExchangeOrder->OrderPriceTypeExchangeOrder->Direction, ExchangeOrder->CombOffsetFlag, ExchangeOrder->CombHedgeFlag, ExchangeOrder->LimitPrice, ExchangeOrder->VolumeTotalOriginal, ExchangeOrder->TimeCondition, ExchangeOrder->GTDDate, ExchangeOrder->VolumeCondition, ExchangeOrder->MinVolume, ExchangeOrder->ContingentCondition, ExchangeOrder->StopPrice, ExchangeOrder->ForceCloseReason, ExchangeOrder->IsAutoSuspend, ExchangeOrder->BusinessUnit, ExchangeOrder->RequestID, ExchangeOrder->OrderLocalID, ExchangeOrder->ExchangeID, ExchangeOrder->ParticipantID, ExchangeOrder->ClientID, ExchangeOrder->reserve1, ExchangeOrder->TraderID, ExchangeOrder->InstallID, ExchangeOrder->OrderSubmitStatus, ExchangeOrder->NotifySequence, ExchangeOrder->TradingDay, ExchangeOrder->SettlementID, ExchangeOrder->OrderSysID, ExchangeOrder->OrderSource, ExchangeOrder->OrderStatus, ExchangeOrder->OrderType, ExchangeOrder->VolumeTraded, ExchangeOrder->VolumeTotal, ExchangeOrder->InsertDate, ExchangeOrder->InsertTime, ExchangeOrder->ActiveTime, ExchangeOrder->SuspendTime, ExchangeOrder->UpdateTime, ExchangeOrder->CancelTime, ExchangeOrder->ActiveTraderID, ExchangeOrder->ClearingPartID, ExchangeOrder->SequenceNo, ExchangeOrder->BranchID, ExchangeOrder->reserve2, ExchangeOrder->MacAddress, ExchangeOrder->ExchangeInstID, ExchangeOrder->IPAddress);
	}
}

void WriteExchangeOrderInsertError(CThostFtdcExchangeOrderInsertErrorField* ExchangeOrderInsertError)
{
	if(ExchangeOrderInsertError)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExchangeOrderInsertErrorField: , ExchangeID[%s]ParticipantID[%s], TraderID[%s], InstallID[%d], OrderLocalID[%s], ErrorID[%d], ErrorMsg[%s]",
			, ExchangeOrderInsertError->ExchangeIDExchangeOrderInsertError->ParticipantID, ExchangeOrderInsertError->TraderID, ExchangeOrderInsertError->InstallID, ExchangeOrderInsertError->OrderLocalID, ExchangeOrderInsertError->ErrorID, ExchangeOrderInsertError->ErrorMsg);
	}
}

void WriteInputOrderAction(CThostFtdcInputOrderActionField* InputOrderAction)
{
	if(InputOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInputOrderActionField: , BrokerID[%s]InvestorID[%s], OrderActionRef[%d], OrderRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], OrderSysID[%s], ActionFlag[%c], LimitPrice[%f], VolumeChange[%d], UserID[%s], reserve1[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			, InputOrderAction->BrokerIDInputOrderAction->InvestorID, InputOrderAction->OrderActionRef, InputOrderAction->OrderRef, InputOrderAction->RequestID, InputOrderAction->FrontID, InputOrderAction->SessionID, InputOrderAction->ExchangeID, InputOrderAction->OrderSysID, InputOrderAction->ActionFlag, InputOrderAction->LimitPrice, InputOrderAction->VolumeChange, InputOrderAction->UserID, InputOrderAction->reserve1, InputOrderAction->InvestUnitID, InputOrderAction->reserve2, InputOrderAction->MacAddress, InputOrderAction->InstrumentID, InputOrderAction->IPAddress);
	}
}

void WriteOrderAction(CThostFtdcOrderActionField* OrderAction)
{
	if(OrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcOrderActionField: , BrokerID[%s]InvestorID[%s], OrderActionRef[%d], OrderRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], OrderSysID[%s], ActionFlag[%c], LimitPrice[%f], VolumeChange[%d], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], OrderLocalID[%s], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], StatusMsg[%s], reserve1[%s], BranchID[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			, OrderAction->BrokerIDOrderAction->InvestorID, OrderAction->OrderActionRef, OrderAction->OrderRef, OrderAction->RequestID, OrderAction->FrontID, OrderAction->SessionID, OrderAction->ExchangeID, OrderAction->OrderSysID, OrderAction->ActionFlag, OrderAction->LimitPrice, OrderAction->VolumeChange, OrderAction->ActionDate, OrderAction->ActionTime, OrderAction->TraderID, OrderAction->InstallID, OrderAction->OrderLocalID, OrderAction->ActionLocalID, OrderAction->ParticipantID, OrderAction->ClientID, OrderAction->BusinessUnit, OrderAction->OrderActionStatus, OrderAction->UserID, OrderAction->StatusMsg, OrderAction->reserve1, OrderAction->BranchID, OrderAction->InvestUnitID, OrderAction->reserve2, OrderAction->MacAddress, OrderAction->InstrumentID, OrderAction->IPAddress);
	}
}

void WriteExchangeOrderAction(CThostFtdcExchangeOrderActionField* ExchangeOrderAction)
{
	if(ExchangeOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExchangeOrderActionField: , ExchangeID[%s]OrderSysID[%s], ActionFlag[%c], LimitPrice[%f], VolumeChange[%d], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], OrderLocalID[%s], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], BranchID[%s], reserve1[%s], MacAddress[%s], IPAddress[%s]",
			, ExchangeOrderAction->ExchangeIDExchangeOrderAction->OrderSysID, ExchangeOrderAction->ActionFlag, ExchangeOrderAction->LimitPrice, ExchangeOrderAction->VolumeChange, ExchangeOrderAction->ActionDate, ExchangeOrderAction->ActionTime, ExchangeOrderAction->TraderID, ExchangeOrderAction->InstallID, ExchangeOrderAction->OrderLocalID, ExchangeOrderAction->ActionLocalID, ExchangeOrderAction->ParticipantID, ExchangeOrderAction->ClientID, ExchangeOrderAction->BusinessUnit, ExchangeOrderAction->OrderActionStatus, ExchangeOrderAction->UserID, ExchangeOrderAction->BranchID, ExchangeOrderAction->reserve1, ExchangeOrderAction->MacAddress, ExchangeOrderAction->IPAddress);
	}
}

void WriteExchangeOrderActionError(CThostFtdcExchangeOrderActionErrorField* ExchangeOrderActionError)
{
	if(ExchangeOrderActionError)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExchangeOrderActionErrorField: , ExchangeID[%s]OrderSysID[%s], TraderID[%s], InstallID[%d], OrderLocalID[%s], ActionLocalID[%s], ErrorID[%d], ErrorMsg[%s]",
			, ExchangeOrderActionError->ExchangeIDExchangeOrderActionError->OrderSysID, ExchangeOrderActionError->TraderID, ExchangeOrderActionError->InstallID, ExchangeOrderActionError->OrderLocalID, ExchangeOrderActionError->ActionLocalID, ExchangeOrderActionError->ErrorID, ExchangeOrderActionError->ErrorMsg);
	}
}

void WriteExchangeTrade(CThostFtdcExchangeTradeField* ExchangeTrade)
{
	if(ExchangeTrade)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExchangeTradeField: , ExchangeID[%s]TradeID[%s], Direction[%c], OrderSysID[%s], ParticipantID[%s], ClientID[%s], TradingRole[%c], reserve1[%s], OffsetFlag[%c], HedgeFlag[%c], Price[%f], Volume[%d], TradeDate[%s], TradeTime[%s], TradeType[%c], PriceSource[%c], TraderID[%s], OrderLocalID[%s], ClearingPartID[%s], BusinessUnit[%s], SequenceNo[%d], TradeSource[%c], ExchangeInstID[%s]",
			, ExchangeTrade->ExchangeIDExchangeTrade->TradeID, ExchangeTrade->Direction, ExchangeTrade->OrderSysID, ExchangeTrade->ParticipantID, ExchangeTrade->ClientID, ExchangeTrade->TradingRole, ExchangeTrade->reserve1, ExchangeTrade->OffsetFlag, ExchangeTrade->HedgeFlag, ExchangeTrade->Price, ExchangeTrade->Volume, ExchangeTrade->TradeDate, ExchangeTrade->TradeTime, ExchangeTrade->TradeType, ExchangeTrade->PriceSource, ExchangeTrade->TraderID, ExchangeTrade->OrderLocalID, ExchangeTrade->ClearingPartID, ExchangeTrade->BusinessUnit, ExchangeTrade->SequenceNo, ExchangeTrade->TradeSource, ExchangeTrade->ExchangeInstID);
	}
}

void WriteTrade(CThostFtdcTradeField* Trade)
{
	if(Trade)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTradeField: , BrokerID[%s]InvestorID[%s], reserve1[%s], OrderRef[%s], UserID[%s], ExchangeID[%s], TradeID[%s], Direction[%c], OrderSysID[%s], ParticipantID[%s], ClientID[%s], TradingRole[%c], reserve2[%s], OffsetFlag[%c], HedgeFlag[%c], Price[%f], Volume[%d], TradeDate[%s], TradeTime[%s], TradeType[%c], PriceSource[%c], TraderID[%s], OrderLocalID[%s], ClearingPartID[%s], BusinessUnit[%s], SequenceNo[%d], TradingDay[%s], SettlementID[%d], BrokerOrderSeq[%d], TradeSource[%c], InvestUnitID[%s], InstrumentID[%s], ExchangeInstID[%s]",
			, Trade->BrokerIDTrade->InvestorID, Trade->reserve1, Trade->OrderRef, Trade->UserID, Trade->ExchangeID, Trade->TradeID, Trade->Direction, Trade->OrderSysID, Trade->ParticipantID, Trade->ClientID, Trade->TradingRole, Trade->reserve2, Trade->OffsetFlag, Trade->HedgeFlag, Trade->Price, Trade->Volume, Trade->TradeDate, Trade->TradeTime, Trade->TradeType, Trade->PriceSource, Trade->TraderID, Trade->OrderLocalID, Trade->ClearingPartID, Trade->BusinessUnit, Trade->SequenceNo, Trade->TradingDay, Trade->SettlementID, Trade->BrokerOrderSeq, Trade->TradeSource, Trade->InvestUnitID, Trade->InstrumentID, Trade->ExchangeInstID);
	}
}

void WriteUserSession(CThostFtdcUserSessionField* UserSession)
{
	if(UserSession)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcUserSessionField: , FrontID[%d]SessionID[%d], BrokerID[%s], UserID[%s], LoginDate[%s], LoginTime[%s], reserve1[%s], UserProductInfo[%s], InterfaceProductInfo[%s], ProtocolInfo[%s], MacAddress[%s], LoginRemark[%s], IPAddress[%s]",
			, UserSession->FrontIDUserSession->SessionID, UserSession->BrokerID, UserSession->UserID, UserSession->LoginDate, UserSession->LoginTime, UserSession->reserve1, UserSession->UserProductInfo, UserSession->InterfaceProductInfo, UserSession->ProtocolInfo, UserSession->MacAddress, UserSession->LoginRemark, UserSession->IPAddress);
	}
}

void WriteQryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField* QryMaxOrderVolume)
{
	if(QryMaxOrderVolume)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryMaxOrderVolumeField: , BrokerID[%s]InvestorID[%s], reserve1[%s], Direction[%c], OffsetFlag[%c], HedgeFlag[%c], MaxVolume[%d], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			, QryMaxOrderVolume->BrokerIDQryMaxOrderVolume->InvestorID, QryMaxOrderVolume->reserve1, QryMaxOrderVolume->Direction, QryMaxOrderVolume->OffsetFlag, QryMaxOrderVolume->HedgeFlag, QryMaxOrderVolume->MaxVolume, QryMaxOrderVolume->ExchangeID, QryMaxOrderVolume->InvestUnitID, QryMaxOrderVolume->InstrumentID);
	}
}

void WriteSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField* SettlementInfoConfirm)
{
	if(SettlementInfoConfirm)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSettlementInfoConfirmField: , BrokerID[%s]InvestorID[%s], ConfirmDate[%s], ConfirmTime[%s], SettlementID[%d], AccountID[%s], CurrencyID[%s]",
			, SettlementInfoConfirm->BrokerIDSettlementInfoConfirm->InvestorID, SettlementInfoConfirm->ConfirmDate, SettlementInfoConfirm->ConfirmTime, SettlementInfoConfirm->SettlementID, SettlementInfoConfirm->AccountID, SettlementInfoConfirm->CurrencyID);
	}
}

void WriteSyncDeposit(CThostFtdcSyncDepositField* SyncDeposit)
{
	if(SyncDeposit)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSyncDepositField: , DepositSeqNo[%s]BrokerID[%s], InvestorID[%s], Deposit[%f], IsForce[%d], CurrencyID[%s]",
			, SyncDeposit->DepositSeqNoSyncDeposit->BrokerID, SyncDeposit->InvestorID, SyncDeposit->Deposit, SyncDeposit->IsForce, SyncDeposit->CurrencyID);
	}
}

void WriteSyncFundMortgage(CThostFtdcSyncFundMortgageField* SyncFundMortgage)
{
	if(SyncFundMortgage)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSyncFundMortgageField: , MortgageSeqNo[%s]BrokerID[%s], InvestorID[%s], FromCurrencyID[%s], MortgageAmount[%f], ToCurrencyID[%s]",
			, SyncFundMortgage->MortgageSeqNoSyncFundMortgage->BrokerID, SyncFundMortgage->InvestorID, SyncFundMortgage->FromCurrencyID, SyncFundMortgage->MortgageAmount, SyncFundMortgage->ToCurrencyID);
	}
}

void WriteBrokerSync(CThostFtdcBrokerSyncField* BrokerSync)
{
	if(BrokerSync)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcBrokerSyncField: , BrokerID[%s]",
			, BrokerSync->BrokerID);
	}
}

void WriteSyncingInvestor(CThostFtdcSyncingInvestorField* SyncingInvestor)
{
	if(SyncingInvestor)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSyncingInvestorField: , InvestorID[%s]BrokerID[%s], InvestorGroupID[%s], InvestorName[%s], IdentifiedCardType[%c], IdentifiedCardNo[%s], IsActive[%d], Telephone[%s], Address[%s], OpenDate[%s], Mobile[%s], CommModelID[%s], MarginModelID[%s]",
			, SyncingInvestor->InvestorIDSyncingInvestor->BrokerID, SyncingInvestor->InvestorGroupID, SyncingInvestor->InvestorName, SyncingInvestor->IdentifiedCardType, SyncingInvestor->IdentifiedCardNo, SyncingInvestor->IsActive, SyncingInvestor->Telephone, SyncingInvestor->Address, SyncingInvestor->OpenDate, SyncingInvestor->Mobile, SyncingInvestor->CommModelID, SyncingInvestor->MarginModelID);
	}
}

void WriteSyncingTradingCode(CThostFtdcSyncingTradingCodeField* SyncingTradingCode)
{
	if(SyncingTradingCode)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSyncingTradingCodeField: , InvestorID[%s]BrokerID[%s], ExchangeID[%s], ClientID[%s], IsActive[%d], ClientIDType[%c]",
			, SyncingTradingCode->InvestorIDSyncingTradingCode->BrokerID, SyncingTradingCode->ExchangeID, SyncingTradingCode->ClientID, SyncingTradingCode->IsActive, SyncingTradingCode->ClientIDType);
	}
}

void WriteSyncingInvestorGroup(CThostFtdcSyncingInvestorGroupField* SyncingInvestorGroup)
{
	if(SyncingInvestorGroup)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSyncingInvestorGroupField: , BrokerID[%s]InvestorGroupID[%s], InvestorGroupName[%s]",
			, SyncingInvestorGroup->BrokerIDSyncingInvestorGroup->InvestorGroupID, SyncingInvestorGroup->InvestorGroupName);
	}
}

void WriteSyncingTradingAccount(CThostFtdcSyncingTradingAccountField* SyncingTradingAccount)
{
	if(SyncingTradingAccount)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSyncingTradingAccountField: , BrokerID[%s]AccountID[%s], PreMortgage[%f], PreCredit[%f], PreDeposit[%f], PreBalance[%f], PreMargin[%f], InterestBase[%f], Interest[%f], Deposit[%f], Withdraw[%f], FrozenMargin[%f], FrozenCash[%f], FrozenCommission[%f], CurrMargin[%f], CashIn[%f], Commission[%f], CloseProfit[%f], PositionProfit[%f], Balance[%f], Available[%f], WithdrawQuota[%f], Reserve[%f], TradingDay[%s], SettlementID[%d], Credit[%f], Mortgage[%f], ExchangeMargin[%f], DeliveryMargin[%f], ExchangeDeliveryMargin[%f], ReserveBalance[%f], CurrencyID[%s], PreFundMortgageIn[%f], PreFundMortgageOut[%f], FundMortgageIn[%f], FundMortgageOut[%f], FundMortgageAvailable[%f], MortgageableFund[%f], SpecProductMargin[%f], SpecProductFrozenMargin[%f], SpecProductCommission[%f], SpecProductFrozenCommission[%f], SpecProductPositionProfit[%f], SpecProductCloseProfit[%f], SpecProductPositionProfitByAlg[%f], SpecProductExchangeMargin[%f], FrozenSwap[%f], RemainSwap[%f]",
			, SyncingTradingAccount->BrokerIDSyncingTradingAccount->AccountID, SyncingTradingAccount->PreMortgage, SyncingTradingAccount->PreCredit, SyncingTradingAccount->PreDeposit, SyncingTradingAccount->PreBalance, SyncingTradingAccount->PreMargin, SyncingTradingAccount->InterestBase, SyncingTradingAccount->Interest, SyncingTradingAccount->Deposit, SyncingTradingAccount->Withdraw, SyncingTradingAccount->FrozenMargin, SyncingTradingAccount->FrozenCash, SyncingTradingAccount->FrozenCommission, SyncingTradingAccount->CurrMargin, SyncingTradingAccount->CashIn, SyncingTradingAccount->Commission, SyncingTradingAccount->CloseProfit, SyncingTradingAccount->PositionProfit, SyncingTradingAccount->Balance, SyncingTradingAccount->Available, SyncingTradingAccount->WithdrawQuota, SyncingTradingAccount->Reserve, SyncingTradingAccount->TradingDay, SyncingTradingAccount->SettlementID, SyncingTradingAccount->Credit, SyncingTradingAccount->Mortgage, SyncingTradingAccount->ExchangeMargin, SyncingTradingAccount->DeliveryMargin, SyncingTradingAccount->ExchangeDeliveryMargin, SyncingTradingAccount->ReserveBalance, SyncingTradingAccount->CurrencyID, SyncingTradingAccount->PreFundMortgageIn, SyncingTradingAccount->PreFundMortgageOut, SyncingTradingAccount->FundMortgageIn, SyncingTradingAccount->FundMortgageOut, SyncingTradingAccount->FundMortgageAvailable, SyncingTradingAccount->MortgageableFund, SyncingTradingAccount->SpecProductMargin, SyncingTradingAccount->SpecProductFrozenMargin, SyncingTradingAccount->SpecProductCommission, SyncingTradingAccount->SpecProductFrozenCommission, SyncingTradingAccount->SpecProductPositionProfit, SyncingTradingAccount->SpecProductCloseProfit, SyncingTradingAccount->SpecProductPositionProfitByAlg, SyncingTradingAccount->SpecProductExchangeMargin, SyncingTradingAccount->FrozenSwap, SyncingTradingAccount->RemainSwap);
	}
}

void WriteSyncingInvestorPosition(CThostFtdcSyncingInvestorPositionField* SyncingInvestorPosition)
{
	if(SyncingInvestorPosition)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSyncingInvestorPositionField: , reserve1[%s]BrokerID[%s], InvestorID[%s], PosiDirection[%c], HedgeFlag[%c], PositionDate[%c], YdPosition[%d], Position[%d], LongFrozen[%d], ShortFrozen[%d], LongFrozenAmount[%f], ShortFrozenAmount[%f], OpenVolume[%d], CloseVolume[%d], OpenAmount[%f], CloseAmount[%f], PositionCost[%f], PreMargin[%f], UseMargin[%f], FrozenMargin[%f], FrozenCash[%f], FrozenCommission[%f], CashIn[%f], Commission[%f], CloseProfit[%f], PositionProfit[%f], PreSettlementPrice[%f], SettlementPrice[%f], TradingDay[%s], SettlementID[%d], OpenCost[%f], ExchangeMargin[%f], CombPosition[%d], CombLongFrozen[%d], CombShortFrozen[%d], CloseProfitByDate[%f], CloseProfitByTrade[%f], TodayPosition[%d], MarginRateByMoney[%f], MarginRateByVolume[%f], StrikeFrozen[%d], StrikeFrozenAmount[%f], AbandonFrozen[%d], ExchangeID[%s], YdStrikeFrozen[%d], InvestUnitID[%s], PositionCostOffset[%f], TasPosition[%d], TasPositionCost[%f], InstrumentID[%s]",
			, SyncingInvestorPosition->reserve1SyncingInvestorPosition->BrokerID, SyncingInvestorPosition->InvestorID, SyncingInvestorPosition->PosiDirection, SyncingInvestorPosition->HedgeFlag, SyncingInvestorPosition->PositionDate, SyncingInvestorPosition->YdPosition, SyncingInvestorPosition->Position, SyncingInvestorPosition->LongFrozen, SyncingInvestorPosition->ShortFrozen, SyncingInvestorPosition->LongFrozenAmount, SyncingInvestorPosition->ShortFrozenAmount, SyncingInvestorPosition->OpenVolume, SyncingInvestorPosition->CloseVolume, SyncingInvestorPosition->OpenAmount, SyncingInvestorPosition->CloseAmount, SyncingInvestorPosition->PositionCost, SyncingInvestorPosition->PreMargin, SyncingInvestorPosition->UseMargin, SyncingInvestorPosition->FrozenMargin, SyncingInvestorPosition->FrozenCash, SyncingInvestorPosition->FrozenCommission, SyncingInvestorPosition->CashIn, SyncingInvestorPosition->Commission, SyncingInvestorPosition->CloseProfit, SyncingInvestorPosition->PositionProfit, SyncingInvestorPosition->PreSettlementPrice, SyncingInvestorPosition->SettlementPrice, SyncingInvestorPosition->TradingDay, SyncingInvestorPosition->SettlementID, SyncingInvestorPosition->OpenCost, SyncingInvestorPosition->ExchangeMargin, SyncingInvestorPosition->CombPosition, SyncingInvestorPosition->CombLongFrozen, SyncingInvestorPosition->CombShortFrozen, SyncingInvestorPosition->CloseProfitByDate, SyncingInvestorPosition->CloseProfitByTrade, SyncingInvestorPosition->TodayPosition, SyncingInvestorPosition->MarginRateByMoney, SyncingInvestorPosition->MarginRateByVolume, SyncingInvestorPosition->StrikeFrozen, SyncingInvestorPosition->StrikeFrozenAmount, SyncingInvestorPosition->AbandonFrozen, SyncingInvestorPosition->ExchangeID, SyncingInvestorPosition->YdStrikeFrozen, SyncingInvestorPosition->InvestUnitID, SyncingInvestorPosition->PositionCostOffset, SyncingInvestorPosition->TasPosition, SyncingInvestorPosition->TasPositionCost, SyncingInvestorPosition->InstrumentID);
	}
}

void WriteSyncingInstrumentMarginRate(CThostFtdcSyncingInstrumentMarginRateField* SyncingInstrumentMarginRate)
{
	if(SyncingInstrumentMarginRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSyncingInstrumentMarginRateField: , reserve1[%s]InvestorRange[%c], BrokerID[%s], InvestorID[%s], HedgeFlag[%c], LongMarginRatioByMoney[%f], LongMarginRatioByVolume[%f], ShortMarginRatioByMoney[%f], ShortMarginRatioByVolume[%f], IsRelative[%d], InstrumentID[%s]",
			, SyncingInstrumentMarginRate->reserve1SyncingInstrumentMarginRate->InvestorRange, SyncingInstrumentMarginRate->BrokerID, SyncingInstrumentMarginRate->InvestorID, SyncingInstrumentMarginRate->HedgeFlag, SyncingInstrumentMarginRate->LongMarginRatioByMoney, SyncingInstrumentMarginRate->LongMarginRatioByVolume, SyncingInstrumentMarginRate->ShortMarginRatioByMoney, SyncingInstrumentMarginRate->ShortMarginRatioByVolume, SyncingInstrumentMarginRate->IsRelative, SyncingInstrumentMarginRate->InstrumentID);
	}
}

void WriteSyncingInstrumentCommissionRate(CThostFtdcSyncingInstrumentCommissionRateField* SyncingInstrumentCommissionRate)
{
	if(SyncingInstrumentCommissionRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSyncingInstrumentCommissionRateField: , reserve1[%s]InvestorRange[%c], BrokerID[%s], InvestorID[%s], OpenRatioByMoney[%f], OpenRatioByVolume[%f], CloseRatioByMoney[%f], CloseRatioByVolume[%f], CloseTodayRatioByMoney[%f], CloseTodayRatioByVolume[%f], InstrumentID[%s]",
			, SyncingInstrumentCommissionRate->reserve1SyncingInstrumentCommissionRate->InvestorRange, SyncingInstrumentCommissionRate->BrokerID, SyncingInstrumentCommissionRate->InvestorID, SyncingInstrumentCommissionRate->OpenRatioByMoney, SyncingInstrumentCommissionRate->OpenRatioByVolume, SyncingInstrumentCommissionRate->CloseRatioByMoney, SyncingInstrumentCommissionRate->CloseRatioByVolume, SyncingInstrumentCommissionRate->CloseTodayRatioByMoney, SyncingInstrumentCommissionRate->CloseTodayRatioByVolume, SyncingInstrumentCommissionRate->InstrumentID);
	}
}

void WriteSyncingInstrumentTradingRight(CThostFtdcSyncingInstrumentTradingRightField* SyncingInstrumentTradingRight)
{
	if(SyncingInstrumentTradingRight)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSyncingInstrumentTradingRightField: , reserve1[%s]InvestorRange[%c], BrokerID[%s], InvestorID[%s], TradingRight[%c], InstrumentID[%s]",
			, SyncingInstrumentTradingRight->reserve1SyncingInstrumentTradingRight->InvestorRange, SyncingInstrumentTradingRight->BrokerID, SyncingInstrumentTradingRight->InvestorID, SyncingInstrumentTradingRight->TradingRight, SyncingInstrumentTradingRight->InstrumentID);
	}
}

void WriteQryOrder(CThostFtdcQryOrderField* QryOrder)
{
	if(QryOrder)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryOrderField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ExchangeID[%s], OrderSysID[%s], InsertTimeStart[%s], InsertTimeEnd[%s], InvestUnitID[%s], InstrumentID[%s]",
			, QryOrder->BrokerIDQryOrder->InvestorID, QryOrder->reserve1, QryOrder->ExchangeID, QryOrder->OrderSysID, QryOrder->InsertTimeStart, QryOrder->InsertTimeEnd, QryOrder->InvestUnitID, QryOrder->InstrumentID);
	}
}

void WriteQryTrade(CThostFtdcQryTradeField* QryTrade)
{
	if(QryTrade)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryTradeField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ExchangeID[%s], TradeID[%s], TradeTimeStart[%s], TradeTimeEnd[%s], InvestUnitID[%s], InstrumentID[%s]",
			, QryTrade->BrokerIDQryTrade->InvestorID, QryTrade->reserve1, QryTrade->ExchangeID, QryTrade->TradeID, QryTrade->TradeTimeStart, QryTrade->TradeTimeEnd, QryTrade->InvestUnitID, QryTrade->InstrumentID);
	}
}

void WriteQryInvestorPosition(CThostFtdcQryInvestorPositionField* QryInvestorPosition)
{
	if(QryInvestorPosition)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryInvestorPositionField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			, QryInvestorPosition->BrokerIDQryInvestorPosition->InvestorID, QryInvestorPosition->reserve1, QryInvestorPosition->ExchangeID, QryInvestorPosition->InvestUnitID, QryInvestorPosition->InstrumentID);
	}
}

void WriteQryTradingAccount(CThostFtdcQryTradingAccountField* QryTradingAccount)
{
	if(QryTradingAccount)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryTradingAccountField: , BrokerID[%s]InvestorID[%s], CurrencyID[%s], BizType[%c], AccountID[%s]",
			, QryTradingAccount->BrokerIDQryTradingAccount->InvestorID, QryTradingAccount->CurrencyID, QryTradingAccount->BizType, QryTradingAccount->AccountID);
	}
}

void WriteQryInvestor(CThostFtdcQryInvestorField* QryInvestor)
{
	if(QryInvestor)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryInvestorField: , BrokerID[%s]InvestorID[%s]",
			, QryInvestor->BrokerIDQryInvestor->InvestorID);
	}
}

void WriteQryTradingCode(CThostFtdcQryTradingCodeField* QryTradingCode)
{
	if(QryTradingCode)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryTradingCodeField: , BrokerID[%s]InvestorID[%s], ExchangeID[%s], ClientID[%s], ClientIDType[%c], InvestUnitID[%s]",
			, QryTradingCode->BrokerIDQryTradingCode->InvestorID, QryTradingCode->ExchangeID, QryTradingCode->ClientID, QryTradingCode->ClientIDType, QryTradingCode->InvestUnitID);
	}
}

void WriteQryInvestorGroup(CThostFtdcQryInvestorGroupField* QryInvestorGroup)
{
	if(QryInvestorGroup)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryInvestorGroupField: , BrokerID[%s]",
			, QryInvestorGroup->BrokerID);
	}
}

void WriteQryInstrumentMarginRate(CThostFtdcQryInstrumentMarginRateField* QryInstrumentMarginRate)
{
	if(QryInstrumentMarginRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryInstrumentMarginRateField: , BrokerID[%s]InvestorID[%s], reserve1[%s], HedgeFlag[%c], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			, QryInstrumentMarginRate->BrokerIDQryInstrumentMarginRate->InvestorID, QryInstrumentMarginRate->reserve1, QryInstrumentMarginRate->HedgeFlag, QryInstrumentMarginRate->ExchangeID, QryInstrumentMarginRate->InvestUnitID, QryInstrumentMarginRate->InstrumentID);
	}
}

void WriteQryInstrumentCommissionRate(CThostFtdcQryInstrumentCommissionRateField* QryInstrumentCommissionRate)
{
	if(QryInstrumentCommissionRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryInstrumentCommissionRateField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			, QryInstrumentCommissionRate->BrokerIDQryInstrumentCommissionRate->InvestorID, QryInstrumentCommissionRate->reserve1, QryInstrumentCommissionRate->ExchangeID, QryInstrumentCommissionRate->InvestUnitID, QryInstrumentCommissionRate->InstrumentID);
	}
}

void WriteQryInstrumentTradingRight(CThostFtdcQryInstrumentTradingRightField* QryInstrumentTradingRight)
{
	if(QryInstrumentTradingRight)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryInstrumentTradingRightField: , BrokerID[%s]InvestorID[%s], reserve1[%s], InstrumentID[%s]",
			, QryInstrumentTradingRight->BrokerIDQryInstrumentTradingRight->InvestorID, QryInstrumentTradingRight->reserve1, QryInstrumentTradingRight->InstrumentID);
	}
}

void WriteQryBroker(CThostFtdcQryBrokerField* QryBroker)
{
	if(QryBroker)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryBrokerField: , BrokerID[%s]",
			, QryBroker->BrokerID);
	}
}

void WriteQryTrader(CThostFtdcQryTraderField* QryTrader)
{
	if(QryTrader)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryTraderField: , ExchangeID[%s]ParticipantID[%s], TraderID[%s]",
			, QryTrader->ExchangeIDQryTrader->ParticipantID, QryTrader->TraderID);
	}
}

void WriteQrySuperUserFunction(CThostFtdcQrySuperUserFunctionField* QrySuperUserFunction)
{
	if(QrySuperUserFunction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQrySuperUserFunctionField: , UserID[%s]",
			, QrySuperUserFunction->UserID);
	}
}

void WriteQryUserSession(CThostFtdcQryUserSessionField* QryUserSession)
{
	if(QryUserSession)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryUserSessionField: , FrontID[%d]SessionID[%d], BrokerID[%s], UserID[%s]",
			, QryUserSession->FrontIDQryUserSession->SessionID, QryUserSession->BrokerID, QryUserSession->UserID);
	}
}

void WriteQryPartBroker(CThostFtdcQryPartBrokerField* QryPartBroker)
{
	if(QryPartBroker)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryPartBrokerField: , ExchangeID[%s]BrokerID[%s], ParticipantID[%s]",
			, QryPartBroker->ExchangeIDQryPartBroker->BrokerID, QryPartBroker->ParticipantID);
	}
}

void WriteQryFrontStatus(CThostFtdcQryFrontStatusField* QryFrontStatus)
{
	if(QryFrontStatus)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryFrontStatusField: , FrontID[%d]",
			, QryFrontStatus->FrontID);
	}
}

void WriteQryExchangeOrder(CThostFtdcQryExchangeOrderField* QryExchangeOrder)
{
	if(QryExchangeOrder)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryExchangeOrderField: , ParticipantID[%s]ClientID[%s], reserve1[%s], ExchangeID[%s], TraderID[%s], ExchangeInstID[%s]",
			, QryExchangeOrder->ParticipantIDQryExchangeOrder->ClientID, QryExchangeOrder->reserve1, QryExchangeOrder->ExchangeID, QryExchangeOrder->TraderID, QryExchangeOrder->ExchangeInstID);
	}
}

void WriteQryOrderAction(CThostFtdcQryOrderActionField* QryOrderAction)
{
	if(QryOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryOrderActionField: , BrokerID[%s]InvestorID[%s], ExchangeID[%s]",
			, QryOrderAction->BrokerIDQryOrderAction->InvestorID, QryOrderAction->ExchangeID);
	}
}

void WriteQryExchangeOrderAction(CThostFtdcQryExchangeOrderActionField* QryExchangeOrderAction)
{
	if(QryExchangeOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryExchangeOrderActionField: , ParticipantID[%s]ClientID[%s], ExchangeID[%s], TraderID[%s]",
			, QryExchangeOrderAction->ParticipantIDQryExchangeOrderAction->ClientID, QryExchangeOrderAction->ExchangeID, QryExchangeOrderAction->TraderID);
	}
}

void WriteQrySuperUser(CThostFtdcQrySuperUserField* QrySuperUser)
{
	if(QrySuperUser)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQrySuperUserField: , UserID[%s]",
			, QrySuperUser->UserID);
	}
}

void WriteQryExchange(CThostFtdcQryExchangeField* QryExchange)
{
	if(QryExchange)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryExchangeField: , ExchangeID[%s]",
			, QryExchange->ExchangeID);
	}
}

void WriteQryProduct(CThostFtdcQryProductField* QryProduct)
{
	if(QryProduct)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryProductField: , reserve1[%s]ProductClass[%c], ExchangeID[%s], ProductID[%s]",
			, QryProduct->reserve1QryProduct->ProductClass, QryProduct->ExchangeID, QryProduct->ProductID);
	}
}

void WriteQryInstrument(CThostFtdcQryInstrumentField* QryInstrument)
{
	if(QryInstrument)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryInstrumentField: , reserve1[%s]ExchangeID[%s], reserve2[%s], reserve3[%s], InstrumentID[%s], ExchangeInstID[%s], ProductID[%s]",
			, QryInstrument->reserve1QryInstrument->ExchangeID, QryInstrument->reserve2, QryInstrument->reserve3, QryInstrument->InstrumentID, QryInstrument->ExchangeInstID, QryInstrument->ProductID);
	}
}

void WriteQryDepthMarketData(CThostFtdcQryDepthMarketDataField* QryDepthMarketData)
{
	if(QryDepthMarketData)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryDepthMarketDataField: , reserve1[%s]ExchangeID[%s], InstrumentID[%s]",
			, QryDepthMarketData->reserve1QryDepthMarketData->ExchangeID, QryDepthMarketData->InstrumentID);
	}
}

void WriteQryBrokerUser(CThostFtdcQryBrokerUserField* QryBrokerUser)
{
	if(QryBrokerUser)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryBrokerUserField: , BrokerID[%s]UserID[%s]",
			, QryBrokerUser->BrokerIDQryBrokerUser->UserID);
	}
}

void WriteQryBrokerUserFunction(CThostFtdcQryBrokerUserFunctionField* QryBrokerUserFunction)
{
	if(QryBrokerUserFunction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryBrokerUserFunctionField: , BrokerID[%s]UserID[%s]",
			, QryBrokerUserFunction->BrokerIDQryBrokerUserFunction->UserID);
	}
}

void WriteQryTraderOffer(CThostFtdcQryTraderOfferField* QryTraderOffer)
{
	if(QryTraderOffer)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryTraderOfferField: , ExchangeID[%s]ParticipantID[%s], TraderID[%s]",
			, QryTraderOffer->ExchangeIDQryTraderOffer->ParticipantID, QryTraderOffer->TraderID);
	}
}

void WriteQrySyncDeposit(CThostFtdcQrySyncDepositField* QrySyncDeposit)
{
	if(QrySyncDeposit)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQrySyncDepositField: , BrokerID[%s]DepositSeqNo[%s]",
			, QrySyncDeposit->BrokerIDQrySyncDeposit->DepositSeqNo);
	}
}

void WriteQrySettlementInfo(CThostFtdcQrySettlementInfoField* QrySettlementInfo)
{
	if(QrySettlementInfo)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQrySettlementInfoField: , BrokerID[%s]InvestorID[%s], TradingDay[%s], AccountID[%s], CurrencyID[%s]",
			, QrySettlementInfo->BrokerIDQrySettlementInfo->InvestorID, QrySettlementInfo->TradingDay, QrySettlementInfo->AccountID, QrySettlementInfo->CurrencyID);
	}
}

void WriteQryExchangeMarginRate(CThostFtdcQryExchangeMarginRateField* QryExchangeMarginRate)
{
	if(QryExchangeMarginRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryExchangeMarginRateField: , BrokerID[%s]reserve1[%s], HedgeFlag[%c], ExchangeID[%s], InstrumentID[%s]",
			, QryExchangeMarginRate->BrokerIDQryExchangeMarginRate->reserve1, QryExchangeMarginRate->HedgeFlag, QryExchangeMarginRate->ExchangeID, QryExchangeMarginRate->InstrumentID);
	}
}

void WriteQryExchangeMarginRateAdjust(CThostFtdcQryExchangeMarginRateAdjustField* QryExchangeMarginRateAdjust)
{
	if(QryExchangeMarginRateAdjust)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryExchangeMarginRateAdjustField: , BrokerID[%s]reserve1[%s], HedgeFlag[%c], InstrumentID[%s]",
			, QryExchangeMarginRateAdjust->BrokerIDQryExchangeMarginRateAdjust->reserve1, QryExchangeMarginRateAdjust->HedgeFlag, QryExchangeMarginRateAdjust->InstrumentID);
	}
}

void WriteQryExchangeRate(CThostFtdcQryExchangeRateField* QryExchangeRate)
{
	if(QryExchangeRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryExchangeRateField: , BrokerID[%s]FromCurrencyID[%s], ToCurrencyID[%s]",
			, QryExchangeRate->BrokerIDQryExchangeRate->FromCurrencyID, QryExchangeRate->ToCurrencyID);
	}
}

void WriteQrySyncFundMortgage(CThostFtdcQrySyncFundMortgageField* QrySyncFundMortgage)
{
	if(QrySyncFundMortgage)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQrySyncFundMortgageField: , BrokerID[%s]MortgageSeqNo[%s]",
			, QrySyncFundMortgage->BrokerIDQrySyncFundMortgage->MortgageSeqNo);
	}
}

void WriteQryHisOrder(CThostFtdcQryHisOrderField* QryHisOrder)
{
	if(QryHisOrder)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryHisOrderField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ExchangeID[%s], OrderSysID[%s], InsertTimeStart[%s], InsertTimeEnd[%s], TradingDay[%s], SettlementID[%d], InstrumentID[%s]",
			, QryHisOrder->BrokerIDQryHisOrder->InvestorID, QryHisOrder->reserve1, QryHisOrder->ExchangeID, QryHisOrder->OrderSysID, QryHisOrder->InsertTimeStart, QryHisOrder->InsertTimeEnd, QryHisOrder->TradingDay, QryHisOrder->SettlementID, QryHisOrder->InstrumentID);
	}
}

void WriteOptionInstrMiniMargin(CThostFtdcOptionInstrMiniMarginField* OptionInstrMiniMargin)
{
	if(OptionInstrMiniMargin)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcOptionInstrMiniMarginField: , reserve1[%s]InvestorRange[%c], BrokerID[%s], InvestorID[%s], MinMargin[%f], ValueMethod[%c], IsRelative[%d], InstrumentID[%s]",
			, OptionInstrMiniMargin->reserve1OptionInstrMiniMargin->InvestorRange, OptionInstrMiniMargin->BrokerID, OptionInstrMiniMargin->InvestorID, OptionInstrMiniMargin->MinMargin, OptionInstrMiniMargin->ValueMethod, OptionInstrMiniMargin->IsRelative, OptionInstrMiniMargin->InstrumentID);
	}
}

void WriteOptionInstrMarginAdjust(CThostFtdcOptionInstrMarginAdjustField* OptionInstrMarginAdjust)
{
	if(OptionInstrMarginAdjust)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcOptionInstrMarginAdjustField: , reserve1[%s]InvestorRange[%c], BrokerID[%s], InvestorID[%s], SShortMarginRatioByMoney[%f], SShortMarginRatioByVolume[%f], HShortMarginRatioByMoney[%f], HShortMarginRatioByVolume[%f], AShortMarginRatioByMoney[%f], AShortMarginRatioByVolume[%f], IsRelative[%d], MShortMarginRatioByMoney[%f], MShortMarginRatioByVolume[%f], InstrumentID[%s]",
			, OptionInstrMarginAdjust->reserve1OptionInstrMarginAdjust->InvestorRange, OptionInstrMarginAdjust->BrokerID, OptionInstrMarginAdjust->InvestorID, OptionInstrMarginAdjust->SShortMarginRatioByMoney, OptionInstrMarginAdjust->SShortMarginRatioByVolume, OptionInstrMarginAdjust->HShortMarginRatioByMoney, OptionInstrMarginAdjust->HShortMarginRatioByVolume, OptionInstrMarginAdjust->AShortMarginRatioByMoney, OptionInstrMarginAdjust->AShortMarginRatioByVolume, OptionInstrMarginAdjust->IsRelative, OptionInstrMarginAdjust->MShortMarginRatioByMoney, OptionInstrMarginAdjust->MShortMarginRatioByVolume, OptionInstrMarginAdjust->InstrumentID);
	}
}

void WriteOptionInstrCommRate(CThostFtdcOptionInstrCommRateField* OptionInstrCommRate)
{
	if(OptionInstrCommRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcOptionInstrCommRateField: , reserve1[%s]InvestorRange[%c], BrokerID[%s], InvestorID[%s], OpenRatioByMoney[%f], OpenRatioByVolume[%f], CloseRatioByMoney[%f], CloseRatioByVolume[%f], CloseTodayRatioByMoney[%f], CloseTodayRatioByVolume[%f], StrikeRatioByMoney[%f], StrikeRatioByVolume[%f], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			, OptionInstrCommRate->reserve1OptionInstrCommRate->InvestorRange, OptionInstrCommRate->BrokerID, OptionInstrCommRate->InvestorID, OptionInstrCommRate->OpenRatioByMoney, OptionInstrCommRate->OpenRatioByVolume, OptionInstrCommRate->CloseRatioByMoney, OptionInstrCommRate->CloseRatioByVolume, OptionInstrCommRate->CloseTodayRatioByMoney, OptionInstrCommRate->CloseTodayRatioByVolume, OptionInstrCommRate->StrikeRatioByMoney, OptionInstrCommRate->StrikeRatioByVolume, OptionInstrCommRate->ExchangeID, OptionInstrCommRate->InvestUnitID, OptionInstrCommRate->InstrumentID);
	}
}

void WriteOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField* OptionInstrTradeCost)
{
	if(OptionInstrTradeCost)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcOptionInstrTradeCostField: , BrokerID[%s]InvestorID[%s], reserve1[%s], HedgeFlag[%c], FixedMargin[%f], MiniMargin[%f], Royalty[%f], ExchFixedMargin[%f], ExchMiniMargin[%f], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			, OptionInstrTradeCost->BrokerIDOptionInstrTradeCost->InvestorID, OptionInstrTradeCost->reserve1, OptionInstrTradeCost->HedgeFlag, OptionInstrTradeCost->FixedMargin, OptionInstrTradeCost->MiniMargin, OptionInstrTradeCost->Royalty, OptionInstrTradeCost->ExchFixedMargin, OptionInstrTradeCost->ExchMiniMargin, OptionInstrTradeCost->ExchangeID, OptionInstrTradeCost->InvestUnitID, OptionInstrTradeCost->InstrumentID);
	}
}

void WriteQryOptionInstrTradeCost(CThostFtdcQryOptionInstrTradeCostField* QryOptionInstrTradeCost)
{
	if(QryOptionInstrTradeCost)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryOptionInstrTradeCostField: , BrokerID[%s]InvestorID[%s], reserve1[%s], HedgeFlag[%c], InputPrice[%f], UnderlyingPrice[%f], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			, QryOptionInstrTradeCost->BrokerIDQryOptionInstrTradeCost->InvestorID, QryOptionInstrTradeCost->reserve1, QryOptionInstrTradeCost->HedgeFlag, QryOptionInstrTradeCost->InputPrice, QryOptionInstrTradeCost->UnderlyingPrice, QryOptionInstrTradeCost->ExchangeID, QryOptionInstrTradeCost->InvestUnitID, QryOptionInstrTradeCost->InstrumentID);
	}
}

void WriteQryOptionInstrCommRate(CThostFtdcQryOptionInstrCommRateField* QryOptionInstrCommRate)
{
	if(QryOptionInstrCommRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryOptionInstrCommRateField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			, QryOptionInstrCommRate->BrokerIDQryOptionInstrCommRate->InvestorID, QryOptionInstrCommRate->reserve1, QryOptionInstrCommRate->ExchangeID, QryOptionInstrCommRate->InvestUnitID, QryOptionInstrCommRate->InstrumentID);
	}
}

void WriteIndexPrice(CThostFtdcIndexPriceField* IndexPrice)
{
	if(IndexPrice)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcIndexPriceField: , BrokerID[%s]reserve1[%s], ClosePrice[%f], InstrumentID[%s]",
			, IndexPrice->BrokerIDIndexPrice->reserve1, IndexPrice->ClosePrice, IndexPrice->InstrumentID);
	}
}

void WriteInputExecOrder(CThostFtdcInputExecOrderField* InputExecOrder)
{
	if(InputExecOrder)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInputExecOrderField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ExecOrderRef[%s], UserID[%s], Volume[%d], RequestID[%d], BusinessUnit[%s], OffsetFlag[%c], HedgeFlag[%c], ActionType[%c], PosiDirection[%c], ReservePositionFlag[%c], CloseFlag[%c], ExchangeID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], ClientID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			, InputExecOrder->BrokerIDInputExecOrder->InvestorID, InputExecOrder->reserve1, InputExecOrder->ExecOrderRef, InputExecOrder->UserID, InputExecOrder->Volume, InputExecOrder->RequestID, InputExecOrder->BusinessUnit, InputExecOrder->OffsetFlag, InputExecOrder->HedgeFlag, InputExecOrder->ActionType, InputExecOrder->PosiDirection, InputExecOrder->ReservePositionFlag, InputExecOrder->CloseFlag, InputExecOrder->ExchangeID, InputExecOrder->InvestUnitID, InputExecOrder->AccountID, InputExecOrder->CurrencyID, InputExecOrder->ClientID, InputExecOrder->reserve2, InputExecOrder->MacAddress, InputExecOrder->InstrumentID, InputExecOrder->IPAddress);
	}
}

void WriteInputExecOrderAction(CThostFtdcInputExecOrderActionField* InputExecOrderAction)
{
	if(InputExecOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInputExecOrderActionField: , BrokerID[%s]InvestorID[%s], ExecOrderActionRef[%d], ExecOrderRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], ExecOrderSysID[%s], ActionFlag[%c], UserID[%s], reserve1[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			, InputExecOrderAction->BrokerIDInputExecOrderAction->InvestorID, InputExecOrderAction->ExecOrderActionRef, InputExecOrderAction->ExecOrderRef, InputExecOrderAction->RequestID, InputExecOrderAction->FrontID, InputExecOrderAction->SessionID, InputExecOrderAction->ExchangeID, InputExecOrderAction->ExecOrderSysID, InputExecOrderAction->ActionFlag, InputExecOrderAction->UserID, InputExecOrderAction->reserve1, InputExecOrderAction->InvestUnitID, InputExecOrderAction->reserve2, InputExecOrderAction->MacAddress, InputExecOrderAction->InstrumentID, InputExecOrderAction->IPAddress);
	}
}

void WriteExecOrder(CThostFtdcExecOrderField* ExecOrder)
{
	if(ExecOrder)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExecOrderField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ExecOrderRef[%s], UserID[%s], Volume[%d], RequestID[%d], BusinessUnit[%s], OffsetFlag[%c], HedgeFlag[%c], ActionType[%c], PosiDirection[%c], ReservePositionFlag[%c], CloseFlag[%c], ExecOrderLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve2[%s], TraderID[%s], InstallID[%d], OrderSubmitStatus[%c], NotifySequence[%d], TradingDay[%s], SettlementID[%d], ExecOrderSysID[%s], InsertDate[%s], InsertTime[%s], CancelTime[%s], ExecResult[%c], ClearingPartID[%s], SequenceNo[%d], FrontID[%d], SessionID[%d], UserProductInfo[%s], StatusMsg[%s], ActiveUserID[%s], BrokerExecOrderSeq[%d], BranchID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], reserve3[%s], MacAddress[%s], InstrumentID[%s], ExchangeInstID[%s], IPAddress[%s]",
			, ExecOrder->BrokerIDExecOrder->InvestorID, ExecOrder->reserve1, ExecOrder->ExecOrderRef, ExecOrder->UserID, ExecOrder->Volume, ExecOrder->RequestID, ExecOrder->BusinessUnit, ExecOrder->OffsetFlag, ExecOrder->HedgeFlag, ExecOrder->ActionType, ExecOrder->PosiDirection, ExecOrder->ReservePositionFlag, ExecOrder->CloseFlag, ExecOrder->ExecOrderLocalID, ExecOrder->ExchangeID, ExecOrder->ParticipantID, ExecOrder->ClientID, ExecOrder->reserve2, ExecOrder->TraderID, ExecOrder->InstallID, ExecOrder->OrderSubmitStatus, ExecOrder->NotifySequence, ExecOrder->TradingDay, ExecOrder->SettlementID, ExecOrder->ExecOrderSysID, ExecOrder->InsertDate, ExecOrder->InsertTime, ExecOrder->CancelTime, ExecOrder->ExecResult, ExecOrder->ClearingPartID, ExecOrder->SequenceNo, ExecOrder->FrontID, ExecOrder->SessionID, ExecOrder->UserProductInfo, ExecOrder->StatusMsg, ExecOrder->ActiveUserID, ExecOrder->BrokerExecOrderSeq, ExecOrder->BranchID, ExecOrder->InvestUnitID, ExecOrder->AccountID, ExecOrder->CurrencyID, ExecOrder->reserve3, ExecOrder->MacAddress, ExecOrder->InstrumentID, ExecOrder->ExchangeInstID, ExecOrder->IPAddress);
	}
}

void WriteExecOrderAction(CThostFtdcExecOrderActionField* ExecOrderAction)
{
	if(ExecOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExecOrderActionField: , BrokerID[%s]InvestorID[%s], ExecOrderActionRef[%d], ExecOrderRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], ExecOrderSysID[%s], ActionFlag[%c], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], ExecOrderLocalID[%s], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], ActionType[%c], StatusMsg[%s], reserve1[%s], BranchID[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			, ExecOrderAction->BrokerIDExecOrderAction->InvestorID, ExecOrderAction->ExecOrderActionRef, ExecOrderAction->ExecOrderRef, ExecOrderAction->RequestID, ExecOrderAction->FrontID, ExecOrderAction->SessionID, ExecOrderAction->ExchangeID, ExecOrderAction->ExecOrderSysID, ExecOrderAction->ActionFlag, ExecOrderAction->ActionDate, ExecOrderAction->ActionTime, ExecOrderAction->TraderID, ExecOrderAction->InstallID, ExecOrderAction->ExecOrderLocalID, ExecOrderAction->ActionLocalID, ExecOrderAction->ParticipantID, ExecOrderAction->ClientID, ExecOrderAction->BusinessUnit, ExecOrderAction->OrderActionStatus, ExecOrderAction->UserID, ExecOrderAction->ActionType, ExecOrderAction->StatusMsg, ExecOrderAction->reserve1, ExecOrderAction->BranchID, ExecOrderAction->InvestUnitID, ExecOrderAction->reserve2, ExecOrderAction->MacAddress, ExecOrderAction->InstrumentID, ExecOrderAction->IPAddress);
	}
}

void WriteQryExecOrder(CThostFtdcQryExecOrderField* QryExecOrder)
{
	if(QryExecOrder)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryExecOrderField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ExchangeID[%s], ExecOrderSysID[%s], InsertTimeStart[%s], InsertTimeEnd[%s], InstrumentID[%s]",
			, QryExecOrder->BrokerIDQryExecOrder->InvestorID, QryExecOrder->reserve1, QryExecOrder->ExchangeID, QryExecOrder->ExecOrderSysID, QryExecOrder->InsertTimeStart, QryExecOrder->InsertTimeEnd, QryExecOrder->InstrumentID);
	}
}

void WriteExchangeExecOrder(CThostFtdcExchangeExecOrderField* ExchangeExecOrder)
{
	if(ExchangeExecOrder)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExchangeExecOrderField: , Volume[%d]RequestID[%d], BusinessUnit[%s], OffsetFlag[%c], HedgeFlag[%c], ActionType[%c], PosiDirection[%c], ReservePositionFlag[%c], CloseFlag[%c], ExecOrderLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve1[%s], TraderID[%s], InstallID[%d], OrderSubmitStatus[%c], NotifySequence[%d], TradingDay[%s], SettlementID[%d], ExecOrderSysID[%s], InsertDate[%s], InsertTime[%s], CancelTime[%s], ExecResult[%c], ClearingPartID[%s], SequenceNo[%d], BranchID[%s], reserve2[%s], MacAddress[%s], ExchangeInstID[%s], IPAddress[%s]",
			, ExchangeExecOrder->VolumeExchangeExecOrder->RequestID, ExchangeExecOrder->BusinessUnit, ExchangeExecOrder->OffsetFlag, ExchangeExecOrder->HedgeFlag, ExchangeExecOrder->ActionType, ExchangeExecOrder->PosiDirection, ExchangeExecOrder->ReservePositionFlag, ExchangeExecOrder->CloseFlag, ExchangeExecOrder->ExecOrderLocalID, ExchangeExecOrder->ExchangeID, ExchangeExecOrder->ParticipantID, ExchangeExecOrder->ClientID, ExchangeExecOrder->reserve1, ExchangeExecOrder->TraderID, ExchangeExecOrder->InstallID, ExchangeExecOrder->OrderSubmitStatus, ExchangeExecOrder->NotifySequence, ExchangeExecOrder->TradingDay, ExchangeExecOrder->SettlementID, ExchangeExecOrder->ExecOrderSysID, ExchangeExecOrder->InsertDate, ExchangeExecOrder->InsertTime, ExchangeExecOrder->CancelTime, ExchangeExecOrder->ExecResult, ExchangeExecOrder->ClearingPartID, ExchangeExecOrder->SequenceNo, ExchangeExecOrder->BranchID, ExchangeExecOrder->reserve2, ExchangeExecOrder->MacAddress, ExchangeExecOrder->ExchangeInstID, ExchangeExecOrder->IPAddress);
	}
}

void WriteQryExchangeExecOrder(CThostFtdcQryExchangeExecOrderField* QryExchangeExecOrder)
{
	if(QryExchangeExecOrder)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryExchangeExecOrderField: , ParticipantID[%s]ClientID[%s], reserve1[%s], ExchangeID[%s], TraderID[%s], ExchangeInstID[%s]",
			, QryExchangeExecOrder->ParticipantIDQryExchangeExecOrder->ClientID, QryExchangeExecOrder->reserve1, QryExchangeExecOrder->ExchangeID, QryExchangeExecOrder->TraderID, QryExchangeExecOrder->ExchangeInstID);
	}
}

void WriteQryExecOrderAction(CThostFtdcQryExecOrderActionField* QryExecOrderAction)
{
	if(QryExecOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryExecOrderActionField: , BrokerID[%s]InvestorID[%s], ExchangeID[%s]",
			, QryExecOrderAction->BrokerIDQryExecOrderAction->InvestorID, QryExecOrderAction->ExchangeID);
	}
}

void WriteExchangeExecOrderAction(CThostFtdcExchangeExecOrderActionField* ExchangeExecOrderAction)
{
	if(ExchangeExecOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExchangeExecOrderActionField: , ExchangeID[%s]ExecOrderSysID[%s], ActionFlag[%c], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], ExecOrderLocalID[%s], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], ActionType[%c], BranchID[%s], reserve1[%s], MacAddress[%s], reserve2[%s], Volume[%d], IPAddress[%s], ExchangeInstID[%s]",
			, ExchangeExecOrderAction->ExchangeIDExchangeExecOrderAction->ExecOrderSysID, ExchangeExecOrderAction->ActionFlag, ExchangeExecOrderAction->ActionDate, ExchangeExecOrderAction->ActionTime, ExchangeExecOrderAction->TraderID, ExchangeExecOrderAction->InstallID, ExchangeExecOrderAction->ExecOrderLocalID, ExchangeExecOrderAction->ActionLocalID, ExchangeExecOrderAction->ParticipantID, ExchangeExecOrderAction->ClientID, ExchangeExecOrderAction->BusinessUnit, ExchangeExecOrderAction->OrderActionStatus, ExchangeExecOrderAction->UserID, ExchangeExecOrderAction->ActionType, ExchangeExecOrderAction->BranchID, ExchangeExecOrderAction->reserve1, ExchangeExecOrderAction->MacAddress, ExchangeExecOrderAction->reserve2, ExchangeExecOrderAction->Volume, ExchangeExecOrderAction->IPAddress, ExchangeExecOrderAction->ExchangeInstID);
	}
}

void WriteQryExchangeExecOrderAction(CThostFtdcQryExchangeExecOrderActionField* QryExchangeExecOrderAction)
{
	if(QryExchangeExecOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryExchangeExecOrderActionField: , ParticipantID[%s]ClientID[%s], ExchangeID[%s], TraderID[%s]",
			, QryExchangeExecOrderAction->ParticipantIDQryExchangeExecOrderAction->ClientID, QryExchangeExecOrderAction->ExchangeID, QryExchangeExecOrderAction->TraderID);
	}
}

void WriteErrExecOrder(CThostFtdcErrExecOrderField* ErrExecOrder)
{
	if(ErrExecOrder)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcErrExecOrderField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ExecOrderRef[%s], UserID[%s], Volume[%d], RequestID[%d], BusinessUnit[%s], OffsetFlag[%c], HedgeFlag[%c], ActionType[%c], PosiDirection[%c], ReservePositionFlag[%c], CloseFlag[%c], ExchangeID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], ClientID[%s], reserve2[%s], MacAddress[%s], ErrorID[%d], ErrorMsg[%s], InstrumentID[%s], IPAddress[%s]",
			, ErrExecOrder->BrokerIDErrExecOrder->InvestorID, ErrExecOrder->reserve1, ErrExecOrder->ExecOrderRef, ErrExecOrder->UserID, ErrExecOrder->Volume, ErrExecOrder->RequestID, ErrExecOrder->BusinessUnit, ErrExecOrder->OffsetFlag, ErrExecOrder->HedgeFlag, ErrExecOrder->ActionType, ErrExecOrder->PosiDirection, ErrExecOrder->ReservePositionFlag, ErrExecOrder->CloseFlag, ErrExecOrder->ExchangeID, ErrExecOrder->InvestUnitID, ErrExecOrder->AccountID, ErrExecOrder->CurrencyID, ErrExecOrder->ClientID, ErrExecOrder->reserve2, ErrExecOrder->MacAddress, ErrExecOrder->ErrorID, ErrExecOrder->ErrorMsg, ErrExecOrder->InstrumentID, ErrExecOrder->IPAddress);
	}
}

void WriteQryErrExecOrder(CThostFtdcQryErrExecOrderField* QryErrExecOrder)
{
	if(QryErrExecOrder)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryErrExecOrderField: , BrokerID[%s]InvestorID[%s]",
			, QryErrExecOrder->BrokerIDQryErrExecOrder->InvestorID);
	}
}

void WriteErrExecOrderAction(CThostFtdcErrExecOrderActionField* ErrExecOrderAction)
{
	if(ErrExecOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcErrExecOrderActionField: , BrokerID[%s]InvestorID[%s], ExecOrderActionRef[%d], ExecOrderRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], ExecOrderSysID[%s], ActionFlag[%c], UserID[%s], reserve1[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], ErrorID[%d], ErrorMsg[%s], InstrumentID[%s], IPAddress[%s]",
			, ErrExecOrderAction->BrokerIDErrExecOrderAction->InvestorID, ErrExecOrderAction->ExecOrderActionRef, ErrExecOrderAction->ExecOrderRef, ErrExecOrderAction->RequestID, ErrExecOrderAction->FrontID, ErrExecOrderAction->SessionID, ErrExecOrderAction->ExchangeID, ErrExecOrderAction->ExecOrderSysID, ErrExecOrderAction->ActionFlag, ErrExecOrderAction->UserID, ErrExecOrderAction->reserve1, ErrExecOrderAction->InvestUnitID, ErrExecOrderAction->reserve2, ErrExecOrderAction->MacAddress, ErrExecOrderAction->ErrorID, ErrExecOrderAction->ErrorMsg, ErrExecOrderAction->InstrumentID, ErrExecOrderAction->IPAddress);
	}
}

void WriteQryErrExecOrderAction(CThostFtdcQryErrExecOrderActionField* QryErrExecOrderAction)
{
	if(QryErrExecOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryErrExecOrderActionField: , BrokerID[%s]InvestorID[%s]",
			, QryErrExecOrderAction->BrokerIDQryErrExecOrderAction->InvestorID);
	}
}

void WriteOptionInstrTradingRight(CThostFtdcOptionInstrTradingRightField* OptionInstrTradingRight)
{
	if(OptionInstrTradingRight)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcOptionInstrTradingRightField: , reserve1[%s]InvestorRange[%c], BrokerID[%s], InvestorID[%s], Direction[%c], TradingRight[%c], InstrumentID[%s]",
			, OptionInstrTradingRight->reserve1OptionInstrTradingRight->InvestorRange, OptionInstrTradingRight->BrokerID, OptionInstrTradingRight->InvestorID, OptionInstrTradingRight->Direction, OptionInstrTradingRight->TradingRight, OptionInstrTradingRight->InstrumentID);
	}
}

void WriteQryOptionInstrTradingRight(CThostFtdcQryOptionInstrTradingRightField* QryOptionInstrTradingRight)
{
	if(QryOptionInstrTradingRight)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryOptionInstrTradingRightField: , BrokerID[%s]InvestorID[%s], reserve1[%s], Direction[%c], InstrumentID[%s]",
			, QryOptionInstrTradingRight->BrokerIDQryOptionInstrTradingRight->InvestorID, QryOptionInstrTradingRight->reserve1, QryOptionInstrTradingRight->Direction, QryOptionInstrTradingRight->InstrumentID);
	}
}

void WriteInputForQuote(CThostFtdcInputForQuoteField* InputForQuote)
{
	if(InputForQuote)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInputForQuoteField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ForQuoteRef[%s], UserID[%s], ExchangeID[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			, InputForQuote->BrokerIDInputForQuote->InvestorID, InputForQuote->reserve1, InputForQuote->ForQuoteRef, InputForQuote->UserID, InputForQuote->ExchangeID, InputForQuote->InvestUnitID, InputForQuote->reserve2, InputForQuote->MacAddress, InputForQuote->InstrumentID, InputForQuote->IPAddress);
	}
}

void WriteForQuote(CThostFtdcForQuoteField* ForQuote)
{
	if(ForQuote)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcForQuoteField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ForQuoteRef[%s], UserID[%s], ForQuoteLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve2[%s], TraderID[%s], InstallID[%d], InsertDate[%s], InsertTime[%s], ForQuoteStatus[%c], FrontID[%d], SessionID[%d], StatusMsg[%s], ActiveUserID[%s], BrokerForQutoSeq[%d], InvestUnitID[%s], reserve3[%s], MacAddress[%s], InstrumentID[%s], ExchangeInstID[%s], IPAddress[%s]",
			, ForQuote->BrokerIDForQuote->InvestorID, ForQuote->reserve1, ForQuote->ForQuoteRef, ForQuote->UserID, ForQuote->ForQuoteLocalID, ForQuote->ExchangeID, ForQuote->ParticipantID, ForQuote->ClientID, ForQuote->reserve2, ForQuote->TraderID, ForQuote->InstallID, ForQuote->InsertDate, ForQuote->InsertTime, ForQuote->ForQuoteStatus, ForQuote->FrontID, ForQuote->SessionID, ForQuote->StatusMsg, ForQuote->ActiveUserID, ForQuote->BrokerForQutoSeq, ForQuote->InvestUnitID, ForQuote->reserve3, ForQuote->MacAddress, ForQuote->InstrumentID, ForQuote->ExchangeInstID, ForQuote->IPAddress);
	}
}

void WriteQryForQuote(CThostFtdcQryForQuoteField* QryForQuote)
{
	if(QryForQuote)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryForQuoteField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ExchangeID[%s], InsertTimeStart[%s], InsertTimeEnd[%s], InvestUnitID[%s], InstrumentID[%s]",
			, QryForQuote->BrokerIDQryForQuote->InvestorID, QryForQuote->reserve1, QryForQuote->ExchangeID, QryForQuote->InsertTimeStart, QryForQuote->InsertTimeEnd, QryForQuote->InvestUnitID, QryForQuote->InstrumentID);
	}
}

void WriteExchangeForQuote(CThostFtdcExchangeForQuoteField* ExchangeForQuote)
{
	if(ExchangeForQuote)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExchangeForQuoteField: , ForQuoteLocalID[%s]ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve1[%s], TraderID[%s], InstallID[%d], InsertDate[%s], InsertTime[%s], ForQuoteStatus[%c], reserve2[%s], MacAddress[%s], ExchangeInstID[%s], IPAddress[%s]",
			, ExchangeForQuote->ForQuoteLocalIDExchangeForQuote->ExchangeID, ExchangeForQuote->ParticipantID, ExchangeForQuote->ClientID, ExchangeForQuote->reserve1, ExchangeForQuote->TraderID, ExchangeForQuote->InstallID, ExchangeForQuote->InsertDate, ExchangeForQuote->InsertTime, ExchangeForQuote->ForQuoteStatus, ExchangeForQuote->reserve2, ExchangeForQuote->MacAddress, ExchangeForQuote->ExchangeInstID, ExchangeForQuote->IPAddress);
	}
}

void WriteQryExchangeForQuote(CThostFtdcQryExchangeForQuoteField* QryExchangeForQuote)
{
	if(QryExchangeForQuote)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryExchangeForQuoteField: , ParticipantID[%s]ClientID[%s], reserve1[%s], ExchangeID[%s], TraderID[%s], ExchangeInstID[%s]",
			, QryExchangeForQuote->ParticipantIDQryExchangeForQuote->ClientID, QryExchangeForQuote->reserve1, QryExchangeForQuote->ExchangeID, QryExchangeForQuote->TraderID, QryExchangeForQuote->ExchangeInstID);
	}
}

void WriteInputQuote(CThostFtdcInputQuoteField* InputQuote)
{
	if(InputQuote)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInputQuoteField: , BrokerID[%s]InvestorID[%s], reserve1[%s], QuoteRef[%s], UserID[%s], AskPrice[%f], BidPrice[%f], AskVolume[%d], BidVolume[%d], RequestID[%d], BusinessUnit[%s], AskOffsetFlag[%c], BidOffsetFlag[%c], AskHedgeFlag[%c], BidHedgeFlag[%c], AskOrderRef[%s], BidOrderRef[%s], ForQuoteSysID[%s], ExchangeID[%s], InvestUnitID[%s], ClientID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			, InputQuote->BrokerIDInputQuote->InvestorID, InputQuote->reserve1, InputQuote->QuoteRef, InputQuote->UserID, InputQuote->AskPrice, InputQuote->BidPrice, InputQuote->AskVolume, InputQuote->BidVolume, InputQuote->RequestID, InputQuote->BusinessUnit, InputQuote->AskOffsetFlag, InputQuote->BidOffsetFlag, InputQuote->AskHedgeFlag, InputQuote->BidHedgeFlag, InputQuote->AskOrderRef, InputQuote->BidOrderRef, InputQuote->ForQuoteSysID, InputQuote->ExchangeID, InputQuote->InvestUnitID, InputQuote->ClientID, InputQuote->reserve2, InputQuote->MacAddress, InputQuote->InstrumentID, InputQuote->IPAddress);
	}
}

void WriteInputQuoteAction(CThostFtdcInputQuoteActionField* InputQuoteAction)
{
	if(InputQuoteAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInputQuoteActionField: , BrokerID[%s]InvestorID[%s], QuoteActionRef[%d], QuoteRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], QuoteSysID[%s], ActionFlag[%c], UserID[%s], reserve1[%s], InvestUnitID[%s], ClientID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			, InputQuoteAction->BrokerIDInputQuoteAction->InvestorID, InputQuoteAction->QuoteActionRef, InputQuoteAction->QuoteRef, InputQuoteAction->RequestID, InputQuoteAction->FrontID, InputQuoteAction->SessionID, InputQuoteAction->ExchangeID, InputQuoteAction->QuoteSysID, InputQuoteAction->ActionFlag, InputQuoteAction->UserID, InputQuoteAction->reserve1, InputQuoteAction->InvestUnitID, InputQuoteAction->ClientID, InputQuoteAction->reserve2, InputQuoteAction->MacAddress, InputQuoteAction->InstrumentID, InputQuoteAction->IPAddress);
	}
}

void WriteQuote(CThostFtdcQuoteField* Quote)
{
	if(Quote)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQuoteField: , BrokerID[%s]InvestorID[%s], reserve1[%s], QuoteRef[%s], UserID[%s], AskPrice[%f], BidPrice[%f], AskVolume[%d], BidVolume[%d], RequestID[%d], BusinessUnit[%s], AskOffsetFlag[%c], BidOffsetFlag[%c], AskHedgeFlag[%c], BidHedgeFlag[%c], QuoteLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve2[%s], TraderID[%s], InstallID[%d], NotifySequence[%d], OrderSubmitStatus[%c], TradingDay[%s], SettlementID[%d], QuoteSysID[%s], InsertDate[%s], InsertTime[%s], CancelTime[%s], QuoteStatus[%c], ClearingPartID[%s], SequenceNo[%d], AskOrderSysID[%s], BidOrderSysID[%s], FrontID[%d], SessionID[%d], UserProductInfo[%s], StatusMsg[%s], ActiveUserID[%s], BrokerQuoteSeq[%d], AskOrderRef[%s], BidOrderRef[%s], ForQuoteSysID[%s], BranchID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], reserve3[%s], MacAddress[%s], InstrumentID[%s], ExchangeInstID[%s], IPAddress[%s]",
			, Quote->BrokerIDQuote->InvestorID, Quote->reserve1, Quote->QuoteRef, Quote->UserID, Quote->AskPrice, Quote->BidPrice, Quote->AskVolume, Quote->BidVolume, Quote->RequestID, Quote->BusinessUnit, Quote->AskOffsetFlag, Quote->BidOffsetFlag, Quote->AskHedgeFlag, Quote->BidHedgeFlag, Quote->QuoteLocalID, Quote->ExchangeID, Quote->ParticipantID, Quote->ClientID, Quote->reserve2, Quote->TraderID, Quote->InstallID, Quote->NotifySequence, Quote->OrderSubmitStatus, Quote->TradingDay, Quote->SettlementID, Quote->QuoteSysID, Quote->InsertDate, Quote->InsertTime, Quote->CancelTime, Quote->QuoteStatus, Quote->ClearingPartID, Quote->SequenceNo, Quote->AskOrderSysID, Quote->BidOrderSysID, Quote->FrontID, Quote->SessionID, Quote->UserProductInfo, Quote->StatusMsg, Quote->ActiveUserID, Quote->BrokerQuoteSeq, Quote->AskOrderRef, Quote->BidOrderRef, Quote->ForQuoteSysID, Quote->BranchID, Quote->InvestUnitID, Quote->AccountID, Quote->CurrencyID, Quote->reserve3, Quote->MacAddress, Quote->InstrumentID, Quote->ExchangeInstID, Quote->IPAddress);
	}
}

void WriteQuoteAction(CThostFtdcQuoteActionField* QuoteAction)
{
	if(QuoteAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQuoteActionField: , BrokerID[%s]InvestorID[%s], QuoteActionRef[%d], QuoteRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], QuoteSysID[%s], ActionFlag[%c], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], QuoteLocalID[%s], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], StatusMsg[%s], reserve1[%s], BranchID[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			, QuoteAction->BrokerIDQuoteAction->InvestorID, QuoteAction->QuoteActionRef, QuoteAction->QuoteRef, QuoteAction->RequestID, QuoteAction->FrontID, QuoteAction->SessionID, QuoteAction->ExchangeID, QuoteAction->QuoteSysID, QuoteAction->ActionFlag, QuoteAction->ActionDate, QuoteAction->ActionTime, QuoteAction->TraderID, QuoteAction->InstallID, QuoteAction->QuoteLocalID, QuoteAction->ActionLocalID, QuoteAction->ParticipantID, QuoteAction->ClientID, QuoteAction->BusinessUnit, QuoteAction->OrderActionStatus, QuoteAction->UserID, QuoteAction->StatusMsg, QuoteAction->reserve1, QuoteAction->BranchID, QuoteAction->InvestUnitID, QuoteAction->reserve2, QuoteAction->MacAddress, QuoteAction->InstrumentID, QuoteAction->IPAddress);
	}
}

void WriteQryQuote(CThostFtdcQryQuoteField* QryQuote)
{
	if(QryQuote)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryQuoteField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ExchangeID[%s], QuoteSysID[%s], InsertTimeStart[%s], InsertTimeEnd[%s], InvestUnitID[%s], InstrumentID[%s]",
			, QryQuote->BrokerIDQryQuote->InvestorID, QryQuote->reserve1, QryQuote->ExchangeID, QryQuote->QuoteSysID, QryQuote->InsertTimeStart, QryQuote->InsertTimeEnd, QryQuote->InvestUnitID, QryQuote->InstrumentID);
	}
}

void WriteExchangeQuote(CThostFtdcExchangeQuoteField* ExchangeQuote)
{
	if(ExchangeQuote)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExchangeQuoteField: , AskPrice[%f]BidPrice[%f], AskVolume[%d], BidVolume[%d], RequestID[%d], BusinessUnit[%s], AskOffsetFlag[%c], BidOffsetFlag[%c], AskHedgeFlag[%c], BidHedgeFlag[%c], QuoteLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve1[%s], TraderID[%s], InstallID[%d], NotifySequence[%d], OrderSubmitStatus[%c], TradingDay[%s], SettlementID[%d], QuoteSysID[%s], InsertDate[%s], InsertTime[%s], CancelTime[%s], QuoteStatus[%c], ClearingPartID[%s], SequenceNo[%d], AskOrderSysID[%s], BidOrderSysID[%s], ForQuoteSysID[%s], BranchID[%s], reserve2[%s], MacAddress[%s], ExchangeInstID[%s], IPAddress[%s]",
			, ExchangeQuote->AskPriceExchangeQuote->BidPrice, ExchangeQuote->AskVolume, ExchangeQuote->BidVolume, ExchangeQuote->RequestID, ExchangeQuote->BusinessUnit, ExchangeQuote->AskOffsetFlag, ExchangeQuote->BidOffsetFlag, ExchangeQuote->AskHedgeFlag, ExchangeQuote->BidHedgeFlag, ExchangeQuote->QuoteLocalID, ExchangeQuote->ExchangeID, ExchangeQuote->ParticipantID, ExchangeQuote->ClientID, ExchangeQuote->reserve1, ExchangeQuote->TraderID, ExchangeQuote->InstallID, ExchangeQuote->NotifySequence, ExchangeQuote->OrderSubmitStatus, ExchangeQuote->TradingDay, ExchangeQuote->SettlementID, ExchangeQuote->QuoteSysID, ExchangeQuote->InsertDate, ExchangeQuote->InsertTime, ExchangeQuote->CancelTime, ExchangeQuote->QuoteStatus, ExchangeQuote->ClearingPartID, ExchangeQuote->SequenceNo, ExchangeQuote->AskOrderSysID, ExchangeQuote->BidOrderSysID, ExchangeQuote->ForQuoteSysID, ExchangeQuote->BranchID, ExchangeQuote->reserve2, ExchangeQuote->MacAddress, ExchangeQuote->ExchangeInstID, ExchangeQuote->IPAddress);
	}
}

void WriteQryExchangeQuote(CThostFtdcQryExchangeQuoteField* QryExchangeQuote)
{
	if(QryExchangeQuote)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryExchangeQuoteField: , ParticipantID[%s]ClientID[%s], reserve1[%s], ExchangeID[%s], TraderID[%s], ExchangeInstID[%s]",
			, QryExchangeQuote->ParticipantIDQryExchangeQuote->ClientID, QryExchangeQuote->reserve1, QryExchangeQuote->ExchangeID, QryExchangeQuote->TraderID, QryExchangeQuote->ExchangeInstID);
	}
}

void WriteQryQuoteAction(CThostFtdcQryQuoteActionField* QryQuoteAction)
{
	if(QryQuoteAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryQuoteActionField: , BrokerID[%s]InvestorID[%s], ExchangeID[%s]",
			, QryQuoteAction->BrokerIDQryQuoteAction->InvestorID, QryQuoteAction->ExchangeID);
	}
}

void WriteExchangeQuoteAction(CThostFtdcExchangeQuoteActionField* ExchangeQuoteAction)
{
	if(ExchangeQuoteAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExchangeQuoteActionField: , ExchangeID[%s]QuoteSysID[%s], ActionFlag[%c], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], QuoteLocalID[%s], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], reserve1[%s], MacAddress[%s], IPAddress[%s]",
			, ExchangeQuoteAction->ExchangeIDExchangeQuoteAction->QuoteSysID, ExchangeQuoteAction->ActionFlag, ExchangeQuoteAction->ActionDate, ExchangeQuoteAction->ActionTime, ExchangeQuoteAction->TraderID, ExchangeQuoteAction->InstallID, ExchangeQuoteAction->QuoteLocalID, ExchangeQuoteAction->ActionLocalID, ExchangeQuoteAction->ParticipantID, ExchangeQuoteAction->ClientID, ExchangeQuoteAction->BusinessUnit, ExchangeQuoteAction->OrderActionStatus, ExchangeQuoteAction->UserID, ExchangeQuoteAction->reserve1, ExchangeQuoteAction->MacAddress, ExchangeQuoteAction->IPAddress);
	}
}

void WriteQryExchangeQuoteAction(CThostFtdcQryExchangeQuoteActionField* QryExchangeQuoteAction)
{
	if(QryExchangeQuoteAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryExchangeQuoteActionField: , ParticipantID[%s]ClientID[%s], ExchangeID[%s], TraderID[%s]",
			, QryExchangeQuoteAction->ParticipantIDQryExchangeQuoteAction->ClientID, QryExchangeQuoteAction->ExchangeID, QryExchangeQuoteAction->TraderID);
	}
}

void WriteOptionInstrDelta(CThostFtdcOptionInstrDeltaField* OptionInstrDelta)
{
	if(OptionInstrDelta)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcOptionInstrDeltaField: , reserve1[%s]InvestorRange[%c], BrokerID[%s], InvestorID[%s], Delta[%f], InstrumentID[%s]",
			, OptionInstrDelta->reserve1OptionInstrDelta->InvestorRange, OptionInstrDelta->BrokerID, OptionInstrDelta->InvestorID, OptionInstrDelta->Delta, OptionInstrDelta->InstrumentID);
	}
}

void WriteForQuoteRsp(CThostFtdcForQuoteRspField* ForQuoteRsp)
{
	if(ForQuoteRsp)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcForQuoteRspField: , TradingDay[%s]reserve1[%s], ForQuoteSysID[%s], ForQuoteTime[%s], ActionDay[%s], ExchangeID[%s], InstrumentID[%s]",
			, ForQuoteRsp->TradingDayForQuoteRsp->reserve1, ForQuoteRsp->ForQuoteSysID, ForQuoteRsp->ForQuoteTime, ForQuoteRsp->ActionDay, ForQuoteRsp->ExchangeID, ForQuoteRsp->InstrumentID);
	}
}

void WriteStrikeOffset(CThostFtdcStrikeOffsetField* StrikeOffset)
{
	if(StrikeOffset)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcStrikeOffsetField: , reserve1[%s]InvestorRange[%c], BrokerID[%s], InvestorID[%s], Offset[%f], OffsetType[%c], InstrumentID[%s]",
			, StrikeOffset->reserve1StrikeOffset->InvestorRange, StrikeOffset->BrokerID, StrikeOffset->InvestorID, StrikeOffset->Offset, StrikeOffset->OffsetType, StrikeOffset->InstrumentID);
	}
}

void WriteQryStrikeOffset(CThostFtdcQryStrikeOffsetField* QryStrikeOffset)
{
	if(QryStrikeOffset)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryStrikeOffsetField: , BrokerID[%s]InvestorID[%s], reserve1[%s], InstrumentID[%s]",
			, QryStrikeOffset->BrokerIDQryStrikeOffset->InvestorID, QryStrikeOffset->reserve1, QryStrikeOffset->InstrumentID);
	}
}

void WriteInputBatchOrderAction(CThostFtdcInputBatchOrderActionField* InputBatchOrderAction)
{
	if(InputBatchOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInputBatchOrderActionField: , BrokerID[%s]InvestorID[%s], OrderActionRef[%d], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], UserID[%s], InvestUnitID[%s], reserve1[%s], MacAddress[%s], IPAddress[%s]",
			, InputBatchOrderAction->BrokerIDInputBatchOrderAction->InvestorID, InputBatchOrderAction->OrderActionRef, InputBatchOrderAction->RequestID, InputBatchOrderAction->FrontID, InputBatchOrderAction->SessionID, InputBatchOrderAction->ExchangeID, InputBatchOrderAction->UserID, InputBatchOrderAction->InvestUnitID, InputBatchOrderAction->reserve1, InputBatchOrderAction->MacAddress, InputBatchOrderAction->IPAddress);
	}
}

void WriteBatchOrderAction(CThostFtdcBatchOrderActionField* BatchOrderAction)
{
	if(BatchOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcBatchOrderActionField: , BrokerID[%s]InvestorID[%s], OrderActionRef[%d], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], StatusMsg[%s], InvestUnitID[%s], reserve1[%s], MacAddress[%s], IPAddress[%s]",
			, BatchOrderAction->BrokerIDBatchOrderAction->InvestorID, BatchOrderAction->OrderActionRef, BatchOrderAction->RequestID, BatchOrderAction->FrontID, BatchOrderAction->SessionID, BatchOrderAction->ExchangeID, BatchOrderAction->ActionDate, BatchOrderAction->ActionTime, BatchOrderAction->TraderID, BatchOrderAction->InstallID, BatchOrderAction->ActionLocalID, BatchOrderAction->ParticipantID, BatchOrderAction->ClientID, BatchOrderAction->BusinessUnit, BatchOrderAction->OrderActionStatus, BatchOrderAction->UserID, BatchOrderAction->StatusMsg, BatchOrderAction->InvestUnitID, BatchOrderAction->reserve1, BatchOrderAction->MacAddress, BatchOrderAction->IPAddress);
	}
}

void WriteExchangeBatchOrderAction(CThostFtdcExchangeBatchOrderActionField* ExchangeBatchOrderAction)
{
	if(ExchangeBatchOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExchangeBatchOrderActionField: , ExchangeID[%s]ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], reserve1[%s], MacAddress[%s], IPAddress[%s]",
			, ExchangeBatchOrderAction->ExchangeIDExchangeBatchOrderAction->ActionDate, ExchangeBatchOrderAction->ActionTime, ExchangeBatchOrderAction->TraderID, ExchangeBatchOrderAction->InstallID, ExchangeBatchOrderAction->ActionLocalID, ExchangeBatchOrderAction->ParticipantID, ExchangeBatchOrderAction->ClientID, ExchangeBatchOrderAction->BusinessUnit, ExchangeBatchOrderAction->OrderActionStatus, ExchangeBatchOrderAction->UserID, ExchangeBatchOrderAction->reserve1, ExchangeBatchOrderAction->MacAddress, ExchangeBatchOrderAction->IPAddress);
	}
}

void WriteQryBatchOrderAction(CThostFtdcQryBatchOrderActionField* QryBatchOrderAction)
{
	if(QryBatchOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryBatchOrderActionField: , BrokerID[%s]InvestorID[%s], ExchangeID[%s]",
			, QryBatchOrderAction->BrokerIDQryBatchOrderAction->InvestorID, QryBatchOrderAction->ExchangeID);
	}
}

void WriteCombInstrumentGuard(CThostFtdcCombInstrumentGuardField* CombInstrumentGuard)
{
	if(CombInstrumentGuard)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcCombInstrumentGuardField: , BrokerID[%s]reserve1[%s], GuarantRatio[%f], ExchangeID[%s], InstrumentID[%s]",
			, CombInstrumentGuard->BrokerIDCombInstrumentGuard->reserve1, CombInstrumentGuard->GuarantRatio, CombInstrumentGuard->ExchangeID, CombInstrumentGuard->InstrumentID);
	}
}

void WriteQryCombInstrumentGuard(CThostFtdcQryCombInstrumentGuardField* QryCombInstrumentGuard)
{
	if(QryCombInstrumentGuard)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryCombInstrumentGuardField: , BrokerID[%s]reserve1[%s], ExchangeID[%s], InstrumentID[%s]",
			, QryCombInstrumentGuard->BrokerIDQryCombInstrumentGuard->reserve1, QryCombInstrumentGuard->ExchangeID, QryCombInstrumentGuard->InstrumentID);
	}
}

void WriteInputCombAction(CThostFtdcInputCombActionField* InputCombAction)
{
	if(InputCombAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInputCombActionField: , BrokerID[%s]InvestorID[%s], reserve1[%s], CombActionRef[%s], UserID[%s], Direction[%c], Volume[%d], CombDirection[%c], HedgeFlag[%c], ExchangeID[%s], reserve2[%s], MacAddress[%s], InvestUnitID[%s], FrontID[%d], SessionID[%d], InstrumentID[%s], IPAddress[%s]",
			, InputCombAction->BrokerIDInputCombAction->InvestorID, InputCombAction->reserve1, InputCombAction->CombActionRef, InputCombAction->UserID, InputCombAction->Direction, InputCombAction->Volume, InputCombAction->CombDirection, InputCombAction->HedgeFlag, InputCombAction->ExchangeID, InputCombAction->reserve2, InputCombAction->MacAddress, InputCombAction->InvestUnitID, InputCombAction->FrontID, InputCombAction->SessionID, InputCombAction->InstrumentID, InputCombAction->IPAddress);
	}
}

void WriteCombAction(CThostFtdcCombActionField* CombAction)
{
	if(CombAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcCombActionField: , BrokerID[%s]InvestorID[%s], reserve1[%s], CombActionRef[%s], UserID[%s], Direction[%c], Volume[%d], CombDirection[%c], HedgeFlag[%c], ActionLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve2[%s], TraderID[%s], InstallID[%d], ActionStatus[%c], NotifySequence[%d], TradingDay[%s], SettlementID[%d], SequenceNo[%d], FrontID[%d], SessionID[%d], UserProductInfo[%s], StatusMsg[%s], reserve3[%s], MacAddress[%s], ComTradeID[%s], BranchID[%s], InvestUnitID[%s], InstrumentID[%s], ExchangeInstID[%s], IPAddress[%s]",
			, CombAction->BrokerIDCombAction->InvestorID, CombAction->reserve1, CombAction->CombActionRef, CombAction->UserID, CombAction->Direction, CombAction->Volume, CombAction->CombDirection, CombAction->HedgeFlag, CombAction->ActionLocalID, CombAction->ExchangeID, CombAction->ParticipantID, CombAction->ClientID, CombAction->reserve2, CombAction->TraderID, CombAction->InstallID, CombAction->ActionStatus, CombAction->NotifySequence, CombAction->TradingDay, CombAction->SettlementID, CombAction->SequenceNo, CombAction->FrontID, CombAction->SessionID, CombAction->UserProductInfo, CombAction->StatusMsg, CombAction->reserve3, CombAction->MacAddress, CombAction->ComTradeID, CombAction->BranchID, CombAction->InvestUnitID, CombAction->InstrumentID, CombAction->ExchangeInstID, CombAction->IPAddress);
	}
}

void WriteQryCombAction(CThostFtdcQryCombActionField* QryCombAction)
{
	if(QryCombAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryCombActionField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			, QryCombAction->BrokerIDQryCombAction->InvestorID, QryCombAction->reserve1, QryCombAction->ExchangeID, QryCombAction->InvestUnitID, QryCombAction->InstrumentID);
	}
}

void WriteExchangeCombAction(CThostFtdcExchangeCombActionField* ExchangeCombAction)
{
	if(ExchangeCombAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExchangeCombActionField: , Direction[%c]Volume[%d], CombDirection[%c], HedgeFlag[%c], ActionLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve1[%s], TraderID[%s], InstallID[%d], ActionStatus[%c], NotifySequence[%d], TradingDay[%s], SettlementID[%d], SequenceNo[%d], reserve2[%s], MacAddress[%s], ComTradeID[%s], BranchID[%s], ExchangeInstID[%s], IPAddress[%s]",
			, ExchangeCombAction->DirectionExchangeCombAction->Volume, ExchangeCombAction->CombDirection, ExchangeCombAction->HedgeFlag, ExchangeCombAction->ActionLocalID, ExchangeCombAction->ExchangeID, ExchangeCombAction->ParticipantID, ExchangeCombAction->ClientID, ExchangeCombAction->reserve1, ExchangeCombAction->TraderID, ExchangeCombAction->InstallID, ExchangeCombAction->ActionStatus, ExchangeCombAction->NotifySequence, ExchangeCombAction->TradingDay, ExchangeCombAction->SettlementID, ExchangeCombAction->SequenceNo, ExchangeCombAction->reserve2, ExchangeCombAction->MacAddress, ExchangeCombAction->ComTradeID, ExchangeCombAction->BranchID, ExchangeCombAction->ExchangeInstID, ExchangeCombAction->IPAddress);
	}
}

void WriteQryExchangeCombAction(CThostFtdcQryExchangeCombActionField* QryExchangeCombAction)
{
	if(QryExchangeCombAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryExchangeCombActionField: , ParticipantID[%s]ClientID[%s], reserve1[%s], ExchangeID[%s], TraderID[%s], ExchangeInstID[%s]",
			, QryExchangeCombAction->ParticipantIDQryExchangeCombAction->ClientID, QryExchangeCombAction->reserve1, QryExchangeCombAction->ExchangeID, QryExchangeCombAction->TraderID, QryExchangeCombAction->ExchangeInstID);
	}
}

void WriteProductExchRate(CThostFtdcProductExchRateField* ProductExchRate)
{
	if(ProductExchRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcProductExchRateField: , reserve1[%s]QuoteCurrencyID[%s], ExchangeRate[%f], ExchangeID[%s], ProductID[%s]",
			, ProductExchRate->reserve1ProductExchRate->QuoteCurrencyID, ProductExchRate->ExchangeRate, ProductExchRate->ExchangeID, ProductExchRate->ProductID);
	}
}

void WriteQryProductExchRate(CThostFtdcQryProductExchRateField* QryProductExchRate)
{
	if(QryProductExchRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryProductExchRateField: , reserve1[%s]ExchangeID[%s], ProductID[%s]",
			, QryProductExchRate->reserve1QryProductExchRate->ExchangeID, QryProductExchRate->ProductID);
	}
}

void WriteQryForQuoteParam(CThostFtdcQryForQuoteParamField* QryForQuoteParam)
{
	if(QryForQuoteParam)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryForQuoteParamField: , BrokerID[%s]reserve1[%s], ExchangeID[%s], InstrumentID[%s]",
			, QryForQuoteParam->BrokerIDQryForQuoteParam->reserve1, QryForQuoteParam->ExchangeID, QryForQuoteParam->InstrumentID);
	}
}

void WriteForQuoteParam(CThostFtdcForQuoteParamField* ForQuoteParam)
{
	if(ForQuoteParam)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcForQuoteParamField: , BrokerID[%s]reserve1[%s], ExchangeID[%s], LastPrice[%f], PriceInterval[%f], InstrumentID[%s]",
			, ForQuoteParam->BrokerIDForQuoteParam->reserve1, ForQuoteParam->ExchangeID, ForQuoteParam->LastPrice, ForQuoteParam->PriceInterval, ForQuoteParam->InstrumentID);
	}
}

void WriteMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField* MMOptionInstrCommRate)
{
	if(MMOptionInstrCommRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcMMOptionInstrCommRateField: , reserve1[%s]InvestorRange[%c], BrokerID[%s], InvestorID[%s], OpenRatioByMoney[%f], OpenRatioByVolume[%f], CloseRatioByMoney[%f], CloseRatioByVolume[%f], CloseTodayRatioByMoney[%f], CloseTodayRatioByVolume[%f], StrikeRatioByMoney[%f], StrikeRatioByVolume[%f], InstrumentID[%s]",
			, MMOptionInstrCommRate->reserve1MMOptionInstrCommRate->InvestorRange, MMOptionInstrCommRate->BrokerID, MMOptionInstrCommRate->InvestorID, MMOptionInstrCommRate->OpenRatioByMoney, MMOptionInstrCommRate->OpenRatioByVolume, MMOptionInstrCommRate->CloseRatioByMoney, MMOptionInstrCommRate->CloseRatioByVolume, MMOptionInstrCommRate->CloseTodayRatioByMoney, MMOptionInstrCommRate->CloseTodayRatioByVolume, MMOptionInstrCommRate->StrikeRatioByMoney, MMOptionInstrCommRate->StrikeRatioByVolume, MMOptionInstrCommRate->InstrumentID);
	}
}

void WriteQryMMOptionInstrCommRate(CThostFtdcQryMMOptionInstrCommRateField* QryMMOptionInstrCommRate)
{
	if(QryMMOptionInstrCommRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryMMOptionInstrCommRateField: , BrokerID[%s]InvestorID[%s], reserve1[%s], InstrumentID[%s]",
			, QryMMOptionInstrCommRate->BrokerIDQryMMOptionInstrCommRate->InvestorID, QryMMOptionInstrCommRate->reserve1, QryMMOptionInstrCommRate->InstrumentID);
	}
}

void WriteMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField* MMInstrumentCommissionRate)
{
	if(MMInstrumentCommissionRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcMMInstrumentCommissionRateField: , reserve1[%s]InvestorRange[%c], BrokerID[%s], InvestorID[%s], OpenRatioByMoney[%f], OpenRatioByVolume[%f], CloseRatioByMoney[%f], CloseRatioByVolume[%f], CloseTodayRatioByMoney[%f], CloseTodayRatioByVolume[%f], InstrumentID[%s]",
			, MMInstrumentCommissionRate->reserve1MMInstrumentCommissionRate->InvestorRange, MMInstrumentCommissionRate->BrokerID, MMInstrumentCommissionRate->InvestorID, MMInstrumentCommissionRate->OpenRatioByMoney, MMInstrumentCommissionRate->OpenRatioByVolume, MMInstrumentCommissionRate->CloseRatioByMoney, MMInstrumentCommissionRate->CloseRatioByVolume, MMInstrumentCommissionRate->CloseTodayRatioByMoney, MMInstrumentCommissionRate->CloseTodayRatioByVolume, MMInstrumentCommissionRate->InstrumentID);
	}
}

void WriteQryMMInstrumentCommissionRate(CThostFtdcQryMMInstrumentCommissionRateField* QryMMInstrumentCommissionRate)
{
	if(QryMMInstrumentCommissionRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryMMInstrumentCommissionRateField: , BrokerID[%s]InvestorID[%s], reserve1[%s], InstrumentID[%s]",
			, QryMMInstrumentCommissionRate->BrokerIDQryMMInstrumentCommissionRate->InvestorID, QryMMInstrumentCommissionRate->reserve1, QryMMInstrumentCommissionRate->InstrumentID);
	}
}

void WriteInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField* InstrumentOrderCommRate)
{
	if(InstrumentOrderCommRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInstrumentOrderCommRateField: , reserve1[%s]InvestorRange[%c], BrokerID[%s], InvestorID[%s], HedgeFlag[%c], OrderCommByVolume[%f], OrderActionCommByVolume[%f], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			, InstrumentOrderCommRate->reserve1InstrumentOrderCommRate->InvestorRange, InstrumentOrderCommRate->BrokerID, InstrumentOrderCommRate->InvestorID, InstrumentOrderCommRate->HedgeFlag, InstrumentOrderCommRate->OrderCommByVolume, InstrumentOrderCommRate->OrderActionCommByVolume, InstrumentOrderCommRate->ExchangeID, InstrumentOrderCommRate->InvestUnitID, InstrumentOrderCommRate->InstrumentID);
	}
}

void WriteQryInstrumentOrderCommRate(CThostFtdcQryInstrumentOrderCommRateField* QryInstrumentOrderCommRate)
{
	if(QryInstrumentOrderCommRate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryInstrumentOrderCommRateField: , BrokerID[%s]InvestorID[%s], reserve1[%s], InstrumentID[%s]",
			, QryInstrumentOrderCommRate->BrokerIDQryInstrumentOrderCommRate->InvestorID, QryInstrumentOrderCommRate->reserve1, QryInstrumentOrderCommRate->InstrumentID);
	}
}

void WriteTradeParam(CThostFtdcTradeParamField* TradeParam)
{
	if(TradeParam)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTradeParamField: , BrokerID[%s]TradeParamID[%c], TradeParamValue[%s], Memo[%s]",
			, TradeParam->BrokerIDTradeParam->TradeParamID, TradeParam->TradeParamValue, TradeParam->Memo);
	}
}

void WriteInstrumentMarginRateUL(CThostFtdcInstrumentMarginRateULField* InstrumentMarginRateUL)
{
	if(InstrumentMarginRateUL)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInstrumentMarginRateULField: , reserve1[%s]InvestorRange[%c], BrokerID[%s], InvestorID[%s], HedgeFlag[%c], LongMarginRatioByMoney[%f], LongMarginRatioByVolume[%f], ShortMarginRatioByMoney[%f], ShortMarginRatioByVolume[%f], InstrumentID[%s]",
			, InstrumentMarginRateUL->reserve1InstrumentMarginRateUL->InvestorRange, InstrumentMarginRateUL->BrokerID, InstrumentMarginRateUL->InvestorID, InstrumentMarginRateUL->HedgeFlag, InstrumentMarginRateUL->LongMarginRatioByMoney, InstrumentMarginRateUL->LongMarginRatioByVolume, InstrumentMarginRateUL->ShortMarginRatioByMoney, InstrumentMarginRateUL->ShortMarginRatioByVolume, InstrumentMarginRateUL->InstrumentID);
	}
}

void WriteFutureLimitPosiParam(CThostFtdcFutureLimitPosiParamField* FutureLimitPosiParam)
{
	if(FutureLimitPosiParam)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcFutureLimitPosiParamField: , InvestorRange[%c]BrokerID[%s], InvestorID[%s], reserve1[%s], SpecOpenVolume[%d], ArbiOpenVolume[%d], OpenVolume[%d], ProductID[%s]",
			, FutureLimitPosiParam->InvestorRangeFutureLimitPosiParam->BrokerID, FutureLimitPosiParam->InvestorID, FutureLimitPosiParam->reserve1, FutureLimitPosiParam->SpecOpenVolume, FutureLimitPosiParam->ArbiOpenVolume, FutureLimitPosiParam->OpenVolume, FutureLimitPosiParam->ProductID);
	}
}

void WriteLoginForbiddenIP(CThostFtdcLoginForbiddenIPField* LoginForbiddenIP)
{
	if(LoginForbiddenIP)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcLoginForbiddenIPField: , reserve1[%s]IPAddress[%s]",
			, LoginForbiddenIP->reserve1LoginForbiddenIP->IPAddress);
	}
}

void WriteIPList(CThostFtdcIPListField* IPList)
{
	if(IPList)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcIPListField: , reserve1[%s]IsWhite[%d], IPAddress[%s]",
			, IPList->reserve1IPList->IsWhite, IPList->IPAddress);
	}
}

void WriteInputOptionSelfClose(CThostFtdcInputOptionSelfCloseField* InputOptionSelfClose)
{
	if(InputOptionSelfClose)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInputOptionSelfCloseField: , BrokerID[%s]InvestorID[%s], reserve1[%s], OptionSelfCloseRef[%s], UserID[%s], Volume[%d], RequestID[%d], BusinessUnit[%s], HedgeFlag[%c], OptSelfCloseFlag[%c], ExchangeID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], ClientID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			, InputOptionSelfClose->BrokerIDInputOptionSelfClose->InvestorID, InputOptionSelfClose->reserve1, InputOptionSelfClose->OptionSelfCloseRef, InputOptionSelfClose->UserID, InputOptionSelfClose->Volume, InputOptionSelfClose->RequestID, InputOptionSelfClose->BusinessUnit, InputOptionSelfClose->HedgeFlag, InputOptionSelfClose->OptSelfCloseFlag, InputOptionSelfClose->ExchangeID, InputOptionSelfClose->InvestUnitID, InputOptionSelfClose->AccountID, InputOptionSelfClose->CurrencyID, InputOptionSelfClose->ClientID, InputOptionSelfClose->reserve2, InputOptionSelfClose->MacAddress, InputOptionSelfClose->InstrumentID, InputOptionSelfClose->IPAddress);
	}
}

void WriteInputOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField* InputOptionSelfCloseAction)
{
	if(InputOptionSelfCloseAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInputOptionSelfCloseActionField: , BrokerID[%s]InvestorID[%s], OptionSelfCloseActionRef[%d], OptionSelfCloseRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], OptionSelfCloseSysID[%s], ActionFlag[%c], UserID[%s], reserve1[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			, InputOptionSelfCloseAction->BrokerIDInputOptionSelfCloseAction->InvestorID, InputOptionSelfCloseAction->OptionSelfCloseActionRef, InputOptionSelfCloseAction->OptionSelfCloseRef, InputOptionSelfCloseAction->RequestID, InputOptionSelfCloseAction->FrontID, InputOptionSelfCloseAction->SessionID, InputOptionSelfCloseAction->ExchangeID, InputOptionSelfCloseAction->OptionSelfCloseSysID, InputOptionSelfCloseAction->ActionFlag, InputOptionSelfCloseAction->UserID, InputOptionSelfCloseAction->reserve1, InputOptionSelfCloseAction->InvestUnitID, InputOptionSelfCloseAction->reserve2, InputOptionSelfCloseAction->MacAddress, InputOptionSelfCloseAction->InstrumentID, InputOptionSelfCloseAction->IPAddress);
	}
}

void WriteOptionSelfClose(CThostFtdcOptionSelfCloseField* OptionSelfClose)
{
	if(OptionSelfClose)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcOptionSelfCloseField: , BrokerID[%s]InvestorID[%s], reserve1[%s], OptionSelfCloseRef[%s], UserID[%s], Volume[%d], RequestID[%d], BusinessUnit[%s], HedgeFlag[%c], OptSelfCloseFlag[%c], OptionSelfCloseLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve2[%s], TraderID[%s], InstallID[%d], OrderSubmitStatus[%c], NotifySequence[%d], TradingDay[%s], SettlementID[%d], OptionSelfCloseSysID[%s], InsertDate[%s], InsertTime[%s], CancelTime[%s], ExecResult[%c], ClearingPartID[%s], SequenceNo[%d], FrontID[%d], SessionID[%d], UserProductInfo[%s], StatusMsg[%s], ActiveUserID[%s], BrokerOptionSelfCloseSeq[%d], BranchID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], reserve3[%s], MacAddress[%s], InstrumentID[%s], ExchangeInstID[%s], IPAddress[%s]",
			, OptionSelfClose->BrokerIDOptionSelfClose->InvestorID, OptionSelfClose->reserve1, OptionSelfClose->OptionSelfCloseRef, OptionSelfClose->UserID, OptionSelfClose->Volume, OptionSelfClose->RequestID, OptionSelfClose->BusinessUnit, OptionSelfClose->HedgeFlag, OptionSelfClose->OptSelfCloseFlag, OptionSelfClose->OptionSelfCloseLocalID, OptionSelfClose->ExchangeID, OptionSelfClose->ParticipantID, OptionSelfClose->ClientID, OptionSelfClose->reserve2, OptionSelfClose->TraderID, OptionSelfClose->InstallID, OptionSelfClose->OrderSubmitStatus, OptionSelfClose->NotifySequence, OptionSelfClose->TradingDay, OptionSelfClose->SettlementID, OptionSelfClose->OptionSelfCloseSysID, OptionSelfClose->InsertDate, OptionSelfClose->InsertTime, OptionSelfClose->CancelTime, OptionSelfClose->ExecResult, OptionSelfClose->ClearingPartID, OptionSelfClose->SequenceNo, OptionSelfClose->FrontID, OptionSelfClose->SessionID, OptionSelfClose->UserProductInfo, OptionSelfClose->StatusMsg, OptionSelfClose->ActiveUserID, OptionSelfClose->BrokerOptionSelfCloseSeq, OptionSelfClose->BranchID, OptionSelfClose->InvestUnitID, OptionSelfClose->AccountID, OptionSelfClose->CurrencyID, OptionSelfClose->reserve3, OptionSelfClose->MacAddress, OptionSelfClose->InstrumentID, OptionSelfClose->ExchangeInstID, OptionSelfClose->IPAddress);
	}
}

void WriteOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField* OptionSelfCloseAction)
{
	if(OptionSelfCloseAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcOptionSelfCloseActionField: , BrokerID[%s]InvestorID[%s], OptionSelfCloseActionRef[%d], OptionSelfCloseRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], OptionSelfCloseSysID[%s], ActionFlag[%c], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], OptionSelfCloseLocalID[%s], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], StatusMsg[%s], reserve1[%s], BranchID[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			, OptionSelfCloseAction->BrokerIDOptionSelfCloseAction->InvestorID, OptionSelfCloseAction->OptionSelfCloseActionRef, OptionSelfCloseAction->OptionSelfCloseRef, OptionSelfCloseAction->RequestID, OptionSelfCloseAction->FrontID, OptionSelfCloseAction->SessionID, OptionSelfCloseAction->ExchangeID, OptionSelfCloseAction->OptionSelfCloseSysID, OptionSelfCloseAction->ActionFlag, OptionSelfCloseAction->ActionDate, OptionSelfCloseAction->ActionTime, OptionSelfCloseAction->TraderID, OptionSelfCloseAction->InstallID, OptionSelfCloseAction->OptionSelfCloseLocalID, OptionSelfCloseAction->ActionLocalID, OptionSelfCloseAction->ParticipantID, OptionSelfCloseAction->ClientID, OptionSelfCloseAction->BusinessUnit, OptionSelfCloseAction->OrderActionStatus, OptionSelfCloseAction->UserID, OptionSelfCloseAction->StatusMsg, OptionSelfCloseAction->reserve1, OptionSelfCloseAction->BranchID, OptionSelfCloseAction->InvestUnitID, OptionSelfCloseAction->reserve2, OptionSelfCloseAction->MacAddress, OptionSelfCloseAction->InstrumentID, OptionSelfCloseAction->IPAddress);
	}
}

void WriteQryOptionSelfClose(CThostFtdcQryOptionSelfCloseField* QryOptionSelfClose)
{
	if(QryOptionSelfClose)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryOptionSelfCloseField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ExchangeID[%s], OptionSelfCloseSysID[%s], InsertTimeStart[%s], InsertTimeEnd[%s], InstrumentID[%s]",
			, QryOptionSelfClose->BrokerIDQryOptionSelfClose->InvestorID, QryOptionSelfClose->reserve1, QryOptionSelfClose->ExchangeID, QryOptionSelfClose->OptionSelfCloseSysID, QryOptionSelfClose->InsertTimeStart, QryOptionSelfClose->InsertTimeEnd, QryOptionSelfClose->InstrumentID);
	}
}

void WriteExchangeOptionSelfClose(CThostFtdcExchangeOptionSelfCloseField* ExchangeOptionSelfClose)
{
	if(ExchangeOptionSelfClose)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExchangeOptionSelfCloseField: , Volume[%d]RequestID[%d], BusinessUnit[%s], HedgeFlag[%c], OptSelfCloseFlag[%c], OptionSelfCloseLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve1[%s], TraderID[%s], InstallID[%d], OrderSubmitStatus[%c], NotifySequence[%d], TradingDay[%s], SettlementID[%d], OptionSelfCloseSysID[%s], InsertDate[%s], InsertTime[%s], CancelTime[%s], ExecResult[%c], ClearingPartID[%s], SequenceNo[%d], BranchID[%s], reserve2[%s], MacAddress[%s], ExchangeInstID[%s], IPAddress[%s]",
			, ExchangeOptionSelfClose->VolumeExchangeOptionSelfClose->RequestID, ExchangeOptionSelfClose->BusinessUnit, ExchangeOptionSelfClose->HedgeFlag, ExchangeOptionSelfClose->OptSelfCloseFlag, ExchangeOptionSelfClose->OptionSelfCloseLocalID, ExchangeOptionSelfClose->ExchangeID, ExchangeOptionSelfClose->ParticipantID, ExchangeOptionSelfClose->ClientID, ExchangeOptionSelfClose->reserve1, ExchangeOptionSelfClose->TraderID, ExchangeOptionSelfClose->InstallID, ExchangeOptionSelfClose->OrderSubmitStatus, ExchangeOptionSelfClose->NotifySequence, ExchangeOptionSelfClose->TradingDay, ExchangeOptionSelfClose->SettlementID, ExchangeOptionSelfClose->OptionSelfCloseSysID, ExchangeOptionSelfClose->InsertDate, ExchangeOptionSelfClose->InsertTime, ExchangeOptionSelfClose->CancelTime, ExchangeOptionSelfClose->ExecResult, ExchangeOptionSelfClose->ClearingPartID, ExchangeOptionSelfClose->SequenceNo, ExchangeOptionSelfClose->BranchID, ExchangeOptionSelfClose->reserve2, ExchangeOptionSelfClose->MacAddress, ExchangeOptionSelfClose->ExchangeInstID, ExchangeOptionSelfClose->IPAddress);
	}
}

void WriteQryOptionSelfCloseAction(CThostFtdcQryOptionSelfCloseActionField* QryOptionSelfCloseAction)
{
	if(QryOptionSelfCloseAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryOptionSelfCloseActionField: , BrokerID[%s]InvestorID[%s], ExchangeID[%s]",
			, QryOptionSelfCloseAction->BrokerIDQryOptionSelfCloseAction->InvestorID, QryOptionSelfCloseAction->ExchangeID);
	}
}

void WriteExchangeOptionSelfCloseAction(CThostFtdcExchangeOptionSelfCloseActionField* ExchangeOptionSelfCloseAction)
{
	if(ExchangeOptionSelfCloseAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExchangeOptionSelfCloseActionField: , ExchangeID[%s]OptionSelfCloseSysID[%s], ActionFlag[%c], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], OptionSelfCloseLocalID[%s], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], BranchID[%s], reserve1[%s], MacAddress[%s], reserve2[%s], OptSelfCloseFlag[%c], IPAddress[%s], ExchangeInstID[%s]",
			, ExchangeOptionSelfCloseAction->ExchangeIDExchangeOptionSelfCloseAction->OptionSelfCloseSysID, ExchangeOptionSelfCloseAction->ActionFlag, ExchangeOptionSelfCloseAction->ActionDate, ExchangeOptionSelfCloseAction->ActionTime, ExchangeOptionSelfCloseAction->TraderID, ExchangeOptionSelfCloseAction->InstallID, ExchangeOptionSelfCloseAction->OptionSelfCloseLocalID, ExchangeOptionSelfCloseAction->ActionLocalID, ExchangeOptionSelfCloseAction->ParticipantID, ExchangeOptionSelfCloseAction->ClientID, ExchangeOptionSelfCloseAction->BusinessUnit, ExchangeOptionSelfCloseAction->OrderActionStatus, ExchangeOptionSelfCloseAction->UserID, ExchangeOptionSelfCloseAction->BranchID, ExchangeOptionSelfCloseAction->reserve1, ExchangeOptionSelfCloseAction->MacAddress, ExchangeOptionSelfCloseAction->reserve2, ExchangeOptionSelfCloseAction->OptSelfCloseFlag, ExchangeOptionSelfCloseAction->IPAddress, ExchangeOptionSelfCloseAction->ExchangeInstID);
	}
}

void WriteSyncDelaySwap(CThostFtdcSyncDelaySwapField* SyncDelaySwap)
{
	if(SyncDelaySwap)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSyncDelaySwapField: , DelaySwapSeqNo[%s]BrokerID[%s], InvestorID[%s], FromCurrencyID[%s], FromAmount[%f], FromFrozenSwap[%f], FromRemainSwap[%f], ToCurrencyID[%s], ToAmount[%f], IsManualSwap[%d], IsAllRemainSetZero[%d]",
			, SyncDelaySwap->DelaySwapSeqNoSyncDelaySwap->BrokerID, SyncDelaySwap->InvestorID, SyncDelaySwap->FromCurrencyID, SyncDelaySwap->FromAmount, SyncDelaySwap->FromFrozenSwap, SyncDelaySwap->FromRemainSwap, SyncDelaySwap->ToCurrencyID, SyncDelaySwap->ToAmount, SyncDelaySwap->IsManualSwap, SyncDelaySwap->IsAllRemainSetZero);
	}
}

void WriteQrySyncDelaySwap(CThostFtdcQrySyncDelaySwapField* QrySyncDelaySwap)
{
	if(QrySyncDelaySwap)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQrySyncDelaySwapField: , BrokerID[%s]DelaySwapSeqNo[%s]",
			, QrySyncDelaySwap->BrokerIDQrySyncDelaySwap->DelaySwapSeqNo);
	}
}

void WriteInvestUnit(CThostFtdcInvestUnitField* InvestUnit)
{
	if(InvestUnit)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInvestUnitField: , BrokerID[%s]InvestorID[%s], InvestUnitID[%s], InvestorUnitName[%s], InvestorGroupID[%s], CommModelID[%s], MarginModelID[%s], AccountID[%s], CurrencyID[%s]",
			, InvestUnit->BrokerIDInvestUnit->InvestorID, InvestUnit->InvestUnitID, InvestUnit->InvestorUnitName, InvestUnit->InvestorGroupID, InvestUnit->CommModelID, InvestUnit->MarginModelID, InvestUnit->AccountID, InvestUnit->CurrencyID);
	}
}

void WriteQryInvestUnit(CThostFtdcQryInvestUnitField* QryInvestUnit)
{
	if(QryInvestUnit)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryInvestUnitField: , BrokerID[%s]InvestorID[%s], InvestUnitID[%s]",
			, QryInvestUnit->BrokerIDQryInvestUnit->InvestorID, QryInvestUnit->InvestUnitID);
	}
}

void WriteSecAgentCheckMode(CThostFtdcSecAgentCheckModeField* SecAgentCheckMode)
{
	if(SecAgentCheckMode)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSecAgentCheckModeField: , InvestorID[%s]BrokerID[%s], CurrencyID[%s], BrokerSecAgentID[%s], CheckSelfAccount[%d]",
			, SecAgentCheckMode->InvestorIDSecAgentCheckMode->BrokerID, SecAgentCheckMode->CurrencyID, SecAgentCheckMode->BrokerSecAgentID, SecAgentCheckMode->CheckSelfAccount);
	}
}

void WriteSecAgentTradeInfo(CThostFtdcSecAgentTradeInfoField* SecAgentTradeInfo)
{
	if(SecAgentTradeInfo)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSecAgentTradeInfoField: , BrokerID[%s]BrokerSecAgentID[%s], InvestorID[%s], LongCustomerName[%s]",
			, SecAgentTradeInfo->BrokerIDSecAgentTradeInfo->BrokerSecAgentID, SecAgentTradeInfo->InvestorID, SecAgentTradeInfo->LongCustomerName);
	}
}

void WriteMarketData(CThostFtdcMarketDataField* MarketData)
{
	if(MarketData)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcMarketDataField: , TradingDay[%s]reserve1[%s], ExchangeID[%s], reserve2[%s], LastPrice[%f], PreSettlementPrice[%f], PreClosePrice[%f], PreOpenInterest[%f], OpenPrice[%f], HighestPrice[%f], LowestPrice[%f], Volume[%d], Turnover[%f], OpenInterest[%f], ClosePrice[%f], SettlementPrice[%f], UpperLimitPrice[%f], LowerLimitPrice[%f], PreDelta[%f], CurrDelta[%f], UpdateTime[%s], UpdateMillisec[%d], ActionDay[%s], InstrumentID[%s], ExchangeInstID[%s]",
			, MarketData->TradingDayMarketData->reserve1, MarketData->ExchangeID, MarketData->reserve2, MarketData->LastPrice, MarketData->PreSettlementPrice, MarketData->PreClosePrice, MarketData->PreOpenInterest, MarketData->OpenPrice, MarketData->HighestPrice, MarketData->LowestPrice, MarketData->Volume, MarketData->Turnover, MarketData->OpenInterest, MarketData->ClosePrice, MarketData->SettlementPrice, MarketData->UpperLimitPrice, MarketData->LowerLimitPrice, MarketData->PreDelta, MarketData->CurrDelta, MarketData->UpdateTime, MarketData->UpdateMillisec, MarketData->ActionDay, MarketData->InstrumentID, MarketData->ExchangeInstID);
	}
}

void WriteMarketDataBase(CThostFtdcMarketDataBaseField* MarketDataBase)
{
	if(MarketDataBase)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcMarketDataBaseField: , TradingDay[%s]PreSettlementPrice[%f], PreClosePrice[%f], PreOpenInterest[%f], PreDelta[%f]",
			, MarketDataBase->TradingDayMarketDataBase->PreSettlementPrice, MarketDataBase->PreClosePrice, MarketDataBase->PreOpenInterest, MarketDataBase->PreDelta);
	}
}

void WriteMarketDataStatic(CThostFtdcMarketDataStaticField* MarketDataStatic)
{
	if(MarketDataStatic)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcMarketDataStaticField: , OpenPrice[%f]HighestPrice[%f], LowestPrice[%f], ClosePrice[%f], UpperLimitPrice[%f], LowerLimitPrice[%f], SettlementPrice[%f], CurrDelta[%f]",
			, MarketDataStatic->OpenPriceMarketDataStatic->HighestPrice, MarketDataStatic->LowestPrice, MarketDataStatic->ClosePrice, MarketDataStatic->UpperLimitPrice, MarketDataStatic->LowerLimitPrice, MarketDataStatic->SettlementPrice, MarketDataStatic->CurrDelta);
	}
}

void WriteMarketDataLastMatch(CThostFtdcMarketDataLastMatchField* MarketDataLastMatch)
{
	if(MarketDataLastMatch)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcMarketDataLastMatchField: , LastPrice[%f]Volume[%d], Turnover[%f], OpenInterest[%f]",
			, MarketDataLastMatch->LastPriceMarketDataLastMatch->Volume, MarketDataLastMatch->Turnover, MarketDataLastMatch->OpenInterest);
	}
}

void WriteMarketDataBestPrice(CThostFtdcMarketDataBestPriceField* MarketDataBestPrice)
{
	if(MarketDataBestPrice)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcMarketDataBestPriceField: , BidPrice1[%f]BidVolume1[%d], AskPrice1[%f], AskVolume1[%d]",
			, MarketDataBestPrice->BidPrice1MarketDataBestPrice->BidVolume1, MarketDataBestPrice->AskPrice1, MarketDataBestPrice->AskVolume1);
	}
}

void WriteMarketDataBid23(CThostFtdcMarketDataBid23Field* MarketDataBid23)
{
	if(MarketDataBid23)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcMarketDataBid23Field: , BidPrice2[%f]BidVolume2[%d], BidPrice3[%f], BidVolume3[%d]",
			, MarketDataBid23->BidPrice2MarketDataBid23->BidVolume2, MarketDataBid23->BidPrice3, MarketDataBid23->BidVolume3);
	}
}

void WriteMarketDataAsk23(CThostFtdcMarketDataAsk23Field* MarketDataAsk23)
{
	if(MarketDataAsk23)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcMarketDataAsk23Field: , AskPrice2[%f]AskVolume2[%d], AskPrice3[%f], AskVolume3[%d]",
			, MarketDataAsk23->AskPrice2MarketDataAsk23->AskVolume2, MarketDataAsk23->AskPrice3, MarketDataAsk23->AskVolume3);
	}
}

void WriteMarketDataBid45(CThostFtdcMarketDataBid45Field* MarketDataBid45)
{
	if(MarketDataBid45)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcMarketDataBid45Field: , BidPrice4[%f]BidVolume4[%d], BidPrice5[%f], BidVolume5[%d]",
			, MarketDataBid45->BidPrice4MarketDataBid45->BidVolume4, MarketDataBid45->BidPrice5, MarketDataBid45->BidVolume5);
	}
}

void WriteMarketDataAsk45(CThostFtdcMarketDataAsk45Field* MarketDataAsk45)
{
	if(MarketDataAsk45)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcMarketDataAsk45Field: , AskPrice4[%f]AskVolume4[%d], AskPrice5[%f], AskVolume5[%d]",
			, MarketDataAsk45->AskPrice4MarketDataAsk45->AskVolume4, MarketDataAsk45->AskPrice5, MarketDataAsk45->AskVolume5);
	}
}

void WriteMarketDataUpdateTime(CThostFtdcMarketDataUpdateTimeField* MarketDataUpdateTime)
{
	if(MarketDataUpdateTime)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcMarketDataUpdateTimeField: , reserve1[%s]UpdateTime[%s], UpdateMillisec[%d], ActionDay[%s], InstrumentID[%s]",
			, MarketDataUpdateTime->reserve1MarketDataUpdateTime->UpdateTime, MarketDataUpdateTime->UpdateMillisec, MarketDataUpdateTime->ActionDay, MarketDataUpdateTime->InstrumentID);
	}
}

void WriteMarketDataExchange(CThostFtdcMarketDataExchangeField* MarketDataExchange)
{
	if(MarketDataExchange)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcMarketDataExchangeField: , ExchangeID[%s]",
			, MarketDataExchange->ExchangeID);
	}
}

void WriteSpecificInstrument(CThostFtdcSpecificInstrumentField* SpecificInstrument)
{
	if(SpecificInstrument)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSpecificInstrumentField: , reserve1[%s]InstrumentID[%s]",
			, SpecificInstrument->reserve1SpecificInstrument->InstrumentID);
	}
}

void WriteInstrumentStatus(CThostFtdcInstrumentStatusField* InstrumentStatus)
{
	if(InstrumentStatus)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInstrumentStatusField: , ExchangeID[%s]reserve1[%s], SettlementGroupID[%s], reserve2[%s], InstrumentStatus[%c], TradingSegmentSN[%d], EnterTime[%s], EnterReason[%c], ExchangeInstID[%s], InstrumentID[%s]",
			, InstrumentStatus->ExchangeIDInstrumentStatus->reserve1, InstrumentStatus->SettlementGroupID, InstrumentStatus->reserve2, InstrumentStatus->InstrumentStatus, InstrumentStatus->TradingSegmentSN, InstrumentStatus->EnterTime, InstrumentStatus->EnterReason, InstrumentStatus->ExchangeInstID, InstrumentStatus->InstrumentID);
	}
}

void WriteQryInstrumentStatus(CThostFtdcQryInstrumentStatusField* QryInstrumentStatus)
{
	if(QryInstrumentStatus)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryInstrumentStatusField: , ExchangeID[%s]reserve1[%s], ExchangeInstID[%s]",
			, QryInstrumentStatus->ExchangeIDQryInstrumentStatus->reserve1, QryInstrumentStatus->ExchangeInstID);
	}
}

void WriteInvestorAccount(CThostFtdcInvestorAccountField* InvestorAccount)
{
	if(InvestorAccount)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInvestorAccountField: , BrokerID[%s]InvestorID[%s], AccountID[%s], CurrencyID[%s]",
			, InvestorAccount->BrokerIDInvestorAccount->InvestorID, InvestorAccount->AccountID, InvestorAccount->CurrencyID);
	}
}

void WritePositionProfitAlgorithm(CThostFtdcPositionProfitAlgorithmField* PositionProfitAlgorithm)
{
	if(PositionProfitAlgorithm)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcPositionProfitAlgorithmField: , BrokerID[%s]AccountID[%s], Algorithm[%c], Memo[%s], CurrencyID[%s]",
			, PositionProfitAlgorithm->BrokerIDPositionProfitAlgorithm->AccountID, PositionProfitAlgorithm->Algorithm, PositionProfitAlgorithm->Memo, PositionProfitAlgorithm->CurrencyID);
	}
}

void WriteDiscount(CThostFtdcDiscountField* Discount)
{
	if(Discount)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcDiscountField: , BrokerID[%s]InvestorRange[%c], InvestorID[%s], Discount[%f]",
			, Discount->BrokerIDDiscount->InvestorRange, Discount->InvestorID, Discount->Discount);
	}
}

void WriteQryTransferBank(CThostFtdcQryTransferBankField* QryTransferBank)
{
	if(QryTransferBank)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryTransferBankField: , BankID[%s]BankBrchID[%s]",
			, QryTransferBank->BankIDQryTransferBank->BankBrchID);
	}
}

void WriteTransferBank(CThostFtdcTransferBankField* TransferBank)
{
	if(TransferBank)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTransferBankField: , BankID[%s]BankBrchID[%s], BankName[%s], IsActive[%d]",
			, TransferBank->BankIDTransferBank->BankBrchID, TransferBank->BankName, TransferBank->IsActive);
	}
}

void WriteQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField* QryInvestorPositionDetail)
{
	if(QryInvestorPositionDetail)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryInvestorPositionDetailField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			, QryInvestorPositionDetail->BrokerIDQryInvestorPositionDetail->InvestorID, QryInvestorPositionDetail->reserve1, QryInvestorPositionDetail->ExchangeID, QryInvestorPositionDetail->InvestUnitID, QryInvestorPositionDetail->InstrumentID);
	}
}

void WriteInvestorPositionDetail(CThostFtdcInvestorPositionDetailField* InvestorPositionDetail)
{
	if(InvestorPositionDetail)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInvestorPositionDetailField: , reserve1[%s]BrokerID[%s], InvestorID[%s], HedgeFlag[%c], Direction[%c], OpenDate[%s], TradeID[%s], Volume[%d], OpenPrice[%f], TradingDay[%s], SettlementID[%d], TradeType[%c], reserve2[%s], ExchangeID[%s], CloseProfitByDate[%f], CloseProfitByTrade[%f], PositionProfitByDate[%f], PositionProfitByTrade[%f], Margin[%f], ExchMargin[%f], MarginRateByMoney[%f], MarginRateByVolume[%f], LastSettlementPrice[%f], SettlementPrice[%f], CloseVolume[%d], CloseAmount[%f], TimeFirstVolume[%d], InvestUnitID[%s], SpecPosiType[%c], InstrumentID[%s], CombInstrumentID[%s]",
			, InvestorPositionDetail->reserve1InvestorPositionDetail->BrokerID, InvestorPositionDetail->InvestorID, InvestorPositionDetail->HedgeFlag, InvestorPositionDetail->Direction, InvestorPositionDetail->OpenDate, InvestorPositionDetail->TradeID, InvestorPositionDetail->Volume, InvestorPositionDetail->OpenPrice, InvestorPositionDetail->TradingDay, InvestorPositionDetail->SettlementID, InvestorPositionDetail->TradeType, InvestorPositionDetail->reserve2, InvestorPositionDetail->ExchangeID, InvestorPositionDetail->CloseProfitByDate, InvestorPositionDetail->CloseProfitByTrade, InvestorPositionDetail->PositionProfitByDate, InvestorPositionDetail->PositionProfitByTrade, InvestorPositionDetail->Margin, InvestorPositionDetail->ExchMargin, InvestorPositionDetail->MarginRateByMoney, InvestorPositionDetail->MarginRateByVolume, InvestorPositionDetail->LastSettlementPrice, InvestorPositionDetail->SettlementPrice, InvestorPositionDetail->CloseVolume, InvestorPositionDetail->CloseAmount, InvestorPositionDetail->TimeFirstVolume, InvestorPositionDetail->InvestUnitID, InvestorPositionDetail->SpecPosiType, InvestorPositionDetail->InstrumentID, InvestorPositionDetail->CombInstrumentID);
	}
}

void WriteTradingAccountPassword(CThostFtdcTradingAccountPasswordField* TradingAccountPassword)
{
	if(TradingAccountPassword)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTradingAccountPasswordField: , BrokerID[%s]AccountID[%s], Password[%s], CurrencyID[%s]",
			, TradingAccountPassword->BrokerIDTradingAccountPassword->AccountID, TradingAccountPassword->Password, TradingAccountPassword->CurrencyID);
	}
}

void WriteMDTraderOffer(CThostFtdcMDTraderOfferField* MDTraderOffer)
{
	if(MDTraderOffer)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcMDTraderOfferField: , ExchangeID[%s]TraderID[%s], ParticipantID[%s], Password[%s], InstallID[%d], OrderLocalID[%s], TraderConnectStatus[%c], ConnectRequestDate[%s], ConnectRequestTime[%s], LastReportDate[%s], LastReportTime[%s], ConnectDate[%s], ConnectTime[%s], StartDate[%s], StartTime[%s], TradingDay[%s], BrokerID[%s], MaxTradeID[%s], MaxOrderMessageReference[%s]",
			, MDTraderOffer->ExchangeIDMDTraderOffer->TraderID, MDTraderOffer->ParticipantID, MDTraderOffer->Password, MDTraderOffer->InstallID, MDTraderOffer->OrderLocalID, MDTraderOffer->TraderConnectStatus, MDTraderOffer->ConnectRequestDate, MDTraderOffer->ConnectRequestTime, MDTraderOffer->LastReportDate, MDTraderOffer->LastReportTime, MDTraderOffer->ConnectDate, MDTraderOffer->ConnectTime, MDTraderOffer->StartDate, MDTraderOffer->StartTime, MDTraderOffer->TradingDay, MDTraderOffer->BrokerID, MDTraderOffer->MaxTradeID, MDTraderOffer->MaxOrderMessageReference);
	}
}

void WriteQryMDTraderOffer(CThostFtdcQryMDTraderOfferField* QryMDTraderOffer)
{
	if(QryMDTraderOffer)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryMDTraderOfferField: , ExchangeID[%s]ParticipantID[%s], TraderID[%s]",
			, QryMDTraderOffer->ExchangeIDQryMDTraderOffer->ParticipantID, QryMDTraderOffer->TraderID);
	}
}

void WriteQryNotice(CThostFtdcQryNoticeField* QryNotice)
{
	if(QryNotice)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryNoticeField: , BrokerID[%s]",
			, QryNotice->BrokerID);
	}
}

void WriteNotice(CThostFtdcNoticeField* Notice)
{
	if(Notice)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcNoticeField: , BrokerID[%s]Content[%s], SequenceLabel[%s]",
			, Notice->BrokerIDNotice->Content, Notice->SequenceLabel);
	}
}

void WriteUserRight(CThostFtdcUserRightField* UserRight)
{
	if(UserRight)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcUserRightField: , BrokerID[%s]UserID[%s], UserRightType[%c], IsForbidden[%d]",
			, UserRight->BrokerIDUserRight->UserID, UserRight->UserRightType, UserRight->IsForbidden);
	}
}

void WriteQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField* QrySettlementInfoConfirm)
{
	if(QrySettlementInfoConfirm)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQrySettlementInfoConfirmField: , BrokerID[%s]InvestorID[%s], AccountID[%s], CurrencyID[%s]",
			, QrySettlementInfoConfirm->BrokerIDQrySettlementInfoConfirm->InvestorID, QrySettlementInfoConfirm->AccountID, QrySettlementInfoConfirm->CurrencyID);
	}
}

void WriteLoadSettlementInfo(CThostFtdcLoadSettlementInfoField* LoadSettlementInfo)
{
	if(LoadSettlementInfo)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcLoadSettlementInfoField: , BrokerID[%s]",
			, LoadSettlementInfo->BrokerID);
	}
}

void WriteBrokerWithdrawAlgorithm(CThostFtdcBrokerWithdrawAlgorithmField* BrokerWithdrawAlgorithm)
{
	if(BrokerWithdrawAlgorithm)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcBrokerWithdrawAlgorithmField: , BrokerID[%s]WithdrawAlgorithm[%c], UsingRatio[%f], IncludeCloseProfit[%c], AllWithoutTrade[%c], AvailIncludeCloseProfit[%c], IsBrokerUserEvent[%d], CurrencyID[%s], FundMortgageRatio[%f], BalanceAlgorithm[%c]",
			, BrokerWithdrawAlgorithm->BrokerIDBrokerWithdrawAlgorithm->WithdrawAlgorithm, BrokerWithdrawAlgorithm->UsingRatio, BrokerWithdrawAlgorithm->IncludeCloseProfit, BrokerWithdrawAlgorithm->AllWithoutTrade, BrokerWithdrawAlgorithm->AvailIncludeCloseProfit, BrokerWithdrawAlgorithm->IsBrokerUserEvent, BrokerWithdrawAlgorithm->CurrencyID, BrokerWithdrawAlgorithm->FundMortgageRatio, BrokerWithdrawAlgorithm->BalanceAlgorithm);
	}
}

void WriteTradingAccountPasswordUpdateV1(CThostFtdcTradingAccountPasswordUpdateV1Field* TradingAccountPasswordUpdateV1)
{
	if(TradingAccountPasswordUpdateV1)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTradingAccountPasswordUpdateV1Field: , BrokerID[%s]InvestorID[%s], OldPassword[%s], NewPassword[%s]",
			, TradingAccountPasswordUpdateV1->BrokerIDTradingAccountPasswordUpdateV1->InvestorID, TradingAccountPasswordUpdateV1->OldPassword, TradingAccountPasswordUpdateV1->NewPassword);
	}
}

void WriteTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField* TradingAccountPasswordUpdate)
{
	if(TradingAccountPasswordUpdate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTradingAccountPasswordUpdateField: , BrokerID[%s]AccountID[%s], OldPassword[%s], NewPassword[%s], CurrencyID[%s]",
			, TradingAccountPasswordUpdate->BrokerIDTradingAccountPasswordUpdate->AccountID, TradingAccountPasswordUpdate->OldPassword, TradingAccountPasswordUpdate->NewPassword, TradingAccountPasswordUpdate->CurrencyID);
	}
}

void WriteQryCombinationLeg(CThostFtdcQryCombinationLegField* QryCombinationLeg)
{
	if(QryCombinationLeg)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryCombinationLegField: , reserve1[%s]LegID[%d], reserve2[%s], CombInstrumentID[%s], LegInstrumentID[%s]",
			, QryCombinationLeg->reserve1QryCombinationLeg->LegID, QryCombinationLeg->reserve2, QryCombinationLeg->CombInstrumentID, QryCombinationLeg->LegInstrumentID);
	}
}

void WriteQrySyncStatus(CThostFtdcQrySyncStatusField* QrySyncStatus)
{
	if(QrySyncStatus)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQrySyncStatusField: , TradingDay[%s]",
			, QrySyncStatus->TradingDay);
	}
}

void WriteCombinationLeg(CThostFtdcCombinationLegField* CombinationLeg)
{
	if(CombinationLeg)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcCombinationLegField: , reserve1[%s]LegID[%d], reserve2[%s], Direction[%c], LegMultiple[%d], ImplyLevel[%d], CombInstrumentID[%s], LegInstrumentID[%s]",
			, CombinationLeg->reserve1CombinationLeg->LegID, CombinationLeg->reserve2, CombinationLeg->Direction, CombinationLeg->LegMultiple, CombinationLeg->ImplyLevel, CombinationLeg->CombInstrumentID, CombinationLeg->LegInstrumentID);
	}
}

void WriteSyncStatus(CThostFtdcSyncStatusField* SyncStatus)
{
	if(SyncStatus)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSyncStatusField: , TradingDay[%s]DataSyncStatus[%c]",
			, SyncStatus->TradingDaySyncStatus->DataSyncStatus);
	}
}

void WriteQryLinkMan(CThostFtdcQryLinkManField* QryLinkMan)
{
	if(QryLinkMan)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryLinkManField: , BrokerID[%s]InvestorID[%s]",
			, QryLinkMan->BrokerIDQryLinkMan->InvestorID);
	}
}

void WriteLinkMan(CThostFtdcLinkManField* LinkMan)
{
	if(LinkMan)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcLinkManField: , BrokerID[%s]InvestorID[%s], PersonType[%c], IdentifiedCardType[%c], IdentifiedCardNo[%s], PersonName[%s], Telephone[%s], Address[%s], ZipCode[%s], Priority[%d], UOAZipCode[%s], PersonFullName[%s]",
			, LinkMan->BrokerIDLinkMan->InvestorID, LinkMan->PersonType, LinkMan->IdentifiedCardType, LinkMan->IdentifiedCardNo, LinkMan->PersonName, LinkMan->Telephone, LinkMan->Address, LinkMan->ZipCode, LinkMan->Priority, LinkMan->UOAZipCode, LinkMan->PersonFullName);
	}
}

void WriteQryBrokerUserEvent(CThostFtdcQryBrokerUserEventField* QryBrokerUserEvent)
{
	if(QryBrokerUserEvent)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryBrokerUserEventField: , BrokerID[%s]UserID[%s], UserEventType[%c]",
			, QryBrokerUserEvent->BrokerIDQryBrokerUserEvent->UserID, QryBrokerUserEvent->UserEventType);
	}
}

void WriteBrokerUserEvent(CThostFtdcBrokerUserEventField* BrokerUserEvent)
{
	if(BrokerUserEvent)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcBrokerUserEventField: , BrokerID[%s]UserID[%s], UserEventType[%c], EventSequenceNo[%d], EventDate[%s], EventTime[%s], UserEventInfo[%s], InvestorID[%s], reserve1[%s], InstrumentID[%s]",
			, BrokerUserEvent->BrokerIDBrokerUserEvent->UserID, BrokerUserEvent->UserEventType, BrokerUserEvent->EventSequenceNo, BrokerUserEvent->EventDate, BrokerUserEvent->EventTime, BrokerUserEvent->UserEventInfo, BrokerUserEvent->InvestorID, BrokerUserEvent->reserve1, BrokerUserEvent->InstrumentID);
	}
}

void WriteQryContractBank(CThostFtdcQryContractBankField* QryContractBank)
{
	if(QryContractBank)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryContractBankField: , BrokerID[%s]BankID[%s], BankBrchID[%s]",
			, QryContractBank->BrokerIDQryContractBank->BankID, QryContractBank->BankBrchID);
	}
}

void WriteContractBank(CThostFtdcContractBankField* ContractBank)
{
	if(ContractBank)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcContractBankField: , BrokerID[%s]BankID[%s], BankBrchID[%s], BankName[%s]",
			, ContractBank->BrokerIDContractBank->BankID, ContractBank->BankBrchID, ContractBank->BankName);
	}
}

void WriteInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField* InvestorPositionCombineDetail)
{
	if(InvestorPositionCombineDetail)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInvestorPositionCombineDetailField: , TradingDay[%s]OpenDate[%s], ExchangeID[%s], SettlementID[%d], BrokerID[%s], InvestorID[%s], ComTradeID[%s], TradeID[%s], reserve1[%s], HedgeFlag[%c], Direction[%c], TotalAmt[%d], Margin[%f], ExchMargin[%f], MarginRateByMoney[%f], MarginRateByVolume[%f], LegID[%d], LegMultiple[%d], reserve2[%s], TradeGroupID[%d], InvestUnitID[%s], InstrumentID[%s], CombInstrumentID[%s]",
			, InvestorPositionCombineDetail->TradingDayInvestorPositionCombineDetail->OpenDate, InvestorPositionCombineDetail->ExchangeID, InvestorPositionCombineDetail->SettlementID, InvestorPositionCombineDetail->BrokerID, InvestorPositionCombineDetail->InvestorID, InvestorPositionCombineDetail->ComTradeID, InvestorPositionCombineDetail->TradeID, InvestorPositionCombineDetail->reserve1, InvestorPositionCombineDetail->HedgeFlag, InvestorPositionCombineDetail->Direction, InvestorPositionCombineDetail->TotalAmt, InvestorPositionCombineDetail->Margin, InvestorPositionCombineDetail->ExchMargin, InvestorPositionCombineDetail->MarginRateByMoney, InvestorPositionCombineDetail->MarginRateByVolume, InvestorPositionCombineDetail->LegID, InvestorPositionCombineDetail->LegMultiple, InvestorPositionCombineDetail->reserve2, InvestorPositionCombineDetail->TradeGroupID, InvestorPositionCombineDetail->InvestUnitID, InvestorPositionCombineDetail->InstrumentID, InvestorPositionCombineDetail->CombInstrumentID);
	}
}

void WriteParkedOrder(CThostFtdcParkedOrderField* ParkedOrder)
{
	if(ParkedOrder)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcParkedOrderField: , BrokerID[%s]InvestorID[%s], reserve1[%s], OrderRef[%s], UserID[%s], OrderPriceType[%c], Direction[%c], CombOffsetFlag[%s], CombHedgeFlag[%s], LimitPrice[%f], VolumeTotalOriginal[%d], TimeCondition[%c], GTDDate[%s], VolumeCondition[%c], MinVolume[%d], ContingentCondition[%c], StopPrice[%f], ForceCloseReason[%c], IsAutoSuspend[%d], BusinessUnit[%s], RequestID[%d], UserForceClose[%d], ExchangeID[%s], ParkedOrderID[%s], UserType[%c], Status[%c], ErrorID[%d], ErrorMsg[%s], IsSwapOrder[%d], AccountID[%s], CurrencyID[%s], ClientID[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			, ParkedOrder->BrokerIDParkedOrder->InvestorID, ParkedOrder->reserve1, ParkedOrder->OrderRef, ParkedOrder->UserID, ParkedOrder->OrderPriceType, ParkedOrder->Direction, ParkedOrder->CombOffsetFlag, ParkedOrder->CombHedgeFlag, ParkedOrder->LimitPrice, ParkedOrder->VolumeTotalOriginal, ParkedOrder->TimeCondition, ParkedOrder->GTDDate, ParkedOrder->VolumeCondition, ParkedOrder->MinVolume, ParkedOrder->ContingentCondition, ParkedOrder->StopPrice, ParkedOrder->ForceCloseReason, ParkedOrder->IsAutoSuspend, ParkedOrder->BusinessUnit, ParkedOrder->RequestID, ParkedOrder->UserForceClose, ParkedOrder->ExchangeID, ParkedOrder->ParkedOrderID, ParkedOrder->UserType, ParkedOrder->Status, ParkedOrder->ErrorID, ParkedOrder->ErrorMsg, ParkedOrder->IsSwapOrder, ParkedOrder->AccountID, ParkedOrder->CurrencyID, ParkedOrder->ClientID, ParkedOrder->InvestUnitID, ParkedOrder->reserve2, ParkedOrder->MacAddress, ParkedOrder->InstrumentID, ParkedOrder->IPAddress);
	}
}

void WriteParkedOrderAction(CThostFtdcParkedOrderActionField* ParkedOrderAction)
{
	if(ParkedOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcParkedOrderActionField: , BrokerID[%s]InvestorID[%s], OrderActionRef[%d], OrderRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], OrderSysID[%s], ActionFlag[%c], LimitPrice[%f], VolumeChange[%d], UserID[%s], reserve1[%s], ParkedOrderActionID[%s], UserType[%c], Status[%c], ErrorID[%d], ErrorMsg[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			, ParkedOrderAction->BrokerIDParkedOrderAction->InvestorID, ParkedOrderAction->OrderActionRef, ParkedOrderAction->OrderRef, ParkedOrderAction->RequestID, ParkedOrderAction->FrontID, ParkedOrderAction->SessionID, ParkedOrderAction->ExchangeID, ParkedOrderAction->OrderSysID, ParkedOrderAction->ActionFlag, ParkedOrderAction->LimitPrice, ParkedOrderAction->VolumeChange, ParkedOrderAction->UserID, ParkedOrderAction->reserve1, ParkedOrderAction->ParkedOrderActionID, ParkedOrderAction->UserType, ParkedOrderAction->Status, ParkedOrderAction->ErrorID, ParkedOrderAction->ErrorMsg, ParkedOrderAction->InvestUnitID, ParkedOrderAction->reserve2, ParkedOrderAction->MacAddress, ParkedOrderAction->InstrumentID, ParkedOrderAction->IPAddress);
	}
}

void WriteQryParkedOrder(CThostFtdcQryParkedOrderField* QryParkedOrder)
{
	if(QryParkedOrder)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryParkedOrderField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			, QryParkedOrder->BrokerIDQryParkedOrder->InvestorID, QryParkedOrder->reserve1, QryParkedOrder->ExchangeID, QryParkedOrder->InvestUnitID, QryParkedOrder->InstrumentID);
	}
}

void WriteQryParkedOrderAction(CThostFtdcQryParkedOrderActionField* QryParkedOrderAction)
{
	if(QryParkedOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryParkedOrderActionField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			, QryParkedOrderAction->BrokerIDQryParkedOrderAction->InvestorID, QryParkedOrderAction->reserve1, QryParkedOrderAction->ExchangeID, QryParkedOrderAction->InvestUnitID, QryParkedOrderAction->InstrumentID);
	}
}

void WriteRemoveParkedOrder(CThostFtdcRemoveParkedOrderField* RemoveParkedOrder)
{
	if(RemoveParkedOrder)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRemoveParkedOrderField: , BrokerID[%s]InvestorID[%s], ParkedOrderID[%s], InvestUnitID[%s]",
			, RemoveParkedOrder->BrokerIDRemoveParkedOrder->InvestorID, RemoveParkedOrder->ParkedOrderID, RemoveParkedOrder->InvestUnitID);
	}
}

void WriteRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField* RemoveParkedOrderAction)
{
	if(RemoveParkedOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRemoveParkedOrderActionField: , BrokerID[%s]InvestorID[%s], ParkedOrderActionID[%s], InvestUnitID[%s]",
			, RemoveParkedOrderAction->BrokerIDRemoveParkedOrderAction->InvestorID, RemoveParkedOrderAction->ParkedOrderActionID, RemoveParkedOrderAction->InvestUnitID);
	}
}

void WriteInvestorWithdrawAlgorithm(CThostFtdcInvestorWithdrawAlgorithmField* InvestorWithdrawAlgorithm)
{
	if(InvestorWithdrawAlgorithm)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInvestorWithdrawAlgorithmField: , BrokerID[%s]InvestorRange[%c], InvestorID[%s], UsingRatio[%f], CurrencyID[%s], FundMortgageRatio[%f]",
			, InvestorWithdrawAlgorithm->BrokerIDInvestorWithdrawAlgorithm->InvestorRange, InvestorWithdrawAlgorithm->InvestorID, InvestorWithdrawAlgorithm->UsingRatio, InvestorWithdrawAlgorithm->CurrencyID, InvestorWithdrawAlgorithm->FundMortgageRatio);
	}
}

void WriteQryInvestorPositionCombineDetail(CThostFtdcQryInvestorPositionCombineDetailField* QryInvestorPositionCombineDetail)
{
	if(QryInvestorPositionCombineDetail)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryInvestorPositionCombineDetailField: , BrokerID[%s]InvestorID[%s], reserve1[%s], ExchangeID[%s], InvestUnitID[%s], CombInstrumentID[%s]",
			, QryInvestorPositionCombineDetail->BrokerIDQryInvestorPositionCombineDetail->InvestorID, QryInvestorPositionCombineDetail->reserve1, QryInvestorPositionCombineDetail->ExchangeID, QryInvestorPositionCombineDetail->InvestUnitID, QryInvestorPositionCombineDetail->CombInstrumentID);
	}
}

void WriteMarketDataAveragePrice(CThostFtdcMarketDataAveragePriceField* MarketDataAveragePrice)
{
	if(MarketDataAveragePrice)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcMarketDataAveragePriceField: , AveragePrice[%f]",
			, MarketDataAveragePrice->AveragePrice);
	}
}

void WriteVerifyInvestorPassword(CThostFtdcVerifyInvestorPasswordField* VerifyInvestorPassword)
{
	if(VerifyInvestorPassword)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcVerifyInvestorPasswordField: , BrokerID[%s]InvestorID[%s], Password[%s]",
			, VerifyInvestorPassword->BrokerIDVerifyInvestorPassword->InvestorID, VerifyInvestorPassword->Password);
	}
}

void WriteUserIP(CThostFtdcUserIPField* UserIP)
{
	if(UserIP)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcUserIPField: , BrokerID[%s]UserID[%s], reserve1[%s], reserve2[%s], MacAddress[%s], IPAddress[%s], IPMask[%s]",
			, UserIP->BrokerIDUserIP->UserID, UserIP->reserve1, UserIP->reserve2, UserIP->MacAddress, UserIP->IPAddress, UserIP->IPMask);
	}
}

void WriteTradingNoticeInfo(CThostFtdcTradingNoticeInfoField* TradingNoticeInfo)
{
	if(TradingNoticeInfo)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTradingNoticeInfoField: , BrokerID[%s]InvestorID[%s], SendTime[%s], FieldContent[%s], SequenceSeries[%d], SequenceNo[%d], InvestUnitID[%s]",
			, TradingNoticeInfo->BrokerIDTradingNoticeInfo->InvestorID, TradingNoticeInfo->SendTime, TradingNoticeInfo->FieldContent, TradingNoticeInfo->SequenceSeries, TradingNoticeInfo->SequenceNo, TradingNoticeInfo->InvestUnitID);
	}
}

void WriteTradingNotice(CThostFtdcTradingNoticeField* TradingNotice)
{
	if(TradingNotice)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTradingNoticeField: , BrokerID[%s]InvestorRange[%c], InvestorID[%s], SequenceSeries[%d], UserID[%s], SendTime[%s], SequenceNo[%d], FieldContent[%s], InvestUnitID[%s]",
			, TradingNotice->BrokerIDTradingNotice->InvestorRange, TradingNotice->InvestorID, TradingNotice->SequenceSeries, TradingNotice->UserID, TradingNotice->SendTime, TradingNotice->SequenceNo, TradingNotice->FieldContent, TradingNotice->InvestUnitID);
	}
}

void WriteQryTradingNotice(CThostFtdcQryTradingNoticeField* QryTradingNotice)
{
	if(QryTradingNotice)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryTradingNoticeField: , BrokerID[%s]InvestorID[%s], InvestUnitID[%s]",
			, QryTradingNotice->BrokerIDQryTradingNotice->InvestorID, QryTradingNotice->InvestUnitID);
	}
}

void WriteQryErrOrder(CThostFtdcQryErrOrderField* QryErrOrder)
{
	if(QryErrOrder)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryErrOrderField: , BrokerID[%s]InvestorID[%s]",
			, QryErrOrder->BrokerIDQryErrOrder->InvestorID);
	}
}

void WriteErrOrder(CThostFtdcErrOrderField* ErrOrder)
{
	if(ErrOrder)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcErrOrderField: , BrokerID[%s]InvestorID[%s], reserve1[%s], OrderRef[%s], UserID[%s], OrderPriceType[%c], Direction[%c], CombOffsetFlag[%s], CombHedgeFlag[%s], LimitPrice[%f], VolumeTotalOriginal[%d], TimeCondition[%c], GTDDate[%s], VolumeCondition[%c], MinVolume[%d], ContingentCondition[%c], StopPrice[%f], ForceCloseReason[%c], IsAutoSuspend[%d], BusinessUnit[%s], RequestID[%d], UserForceClose[%d], ErrorID[%d], ErrorMsg[%s], IsSwapOrder[%d], ExchangeID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], ClientID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			, ErrOrder->BrokerIDErrOrder->InvestorID, ErrOrder->reserve1, ErrOrder->OrderRef, ErrOrder->UserID, ErrOrder->OrderPriceType, ErrOrder->Direction, ErrOrder->CombOffsetFlag, ErrOrder->CombHedgeFlag, ErrOrder->LimitPrice, ErrOrder->VolumeTotalOriginal, ErrOrder->TimeCondition, ErrOrder->GTDDate, ErrOrder->VolumeCondition, ErrOrder->MinVolume, ErrOrder->ContingentCondition, ErrOrder->StopPrice, ErrOrder->ForceCloseReason, ErrOrder->IsAutoSuspend, ErrOrder->BusinessUnit, ErrOrder->RequestID, ErrOrder->UserForceClose, ErrOrder->ErrorID, ErrOrder->ErrorMsg, ErrOrder->IsSwapOrder, ErrOrder->ExchangeID, ErrOrder->InvestUnitID, ErrOrder->AccountID, ErrOrder->CurrencyID, ErrOrder->ClientID, ErrOrder->reserve2, ErrOrder->MacAddress, ErrOrder->InstrumentID, ErrOrder->IPAddress);
	}
}

void WriteErrorConditionalOrder(CThostFtdcErrorConditionalOrderField* ErrorConditionalOrder)
{
	if(ErrorConditionalOrder)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcErrorConditionalOrderField: , BrokerID[%s]InvestorID[%s], reserve1[%s], OrderRef[%s], UserID[%s], OrderPriceType[%c], Direction[%c], CombOffsetFlag[%s], CombHedgeFlag[%s], LimitPrice[%f], VolumeTotalOriginal[%d], TimeCondition[%c], GTDDate[%s], VolumeCondition[%c], MinVolume[%d], ContingentCondition[%c], StopPrice[%f], ForceCloseReason[%c], IsAutoSuspend[%d], BusinessUnit[%s], RequestID[%d], OrderLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve2[%s], TraderID[%s], InstallID[%d], OrderSubmitStatus[%c], NotifySequence[%d], TradingDay[%s], SettlementID[%d], OrderSysID[%s], OrderSource[%c], OrderStatus[%c], OrderType[%c], VolumeTraded[%d], VolumeTotal[%d], InsertDate[%s], InsertTime[%s], ActiveTime[%s], SuspendTime[%s], UpdateTime[%s], CancelTime[%s], ActiveTraderID[%s], ClearingPartID[%s], SequenceNo[%d], FrontID[%d], SessionID[%d], UserProductInfo[%s], StatusMsg[%s], UserForceClose[%d], ActiveUserID[%s], BrokerOrderSeq[%d], RelativeOrderSysID[%s], ZCETotalTradedVolume[%d], ErrorID[%d], ErrorMsg[%s], IsSwapOrder[%d], BranchID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], reserve3[%s], MacAddress[%s], InstrumentID[%s], ExchangeInstID[%s], IPAddress[%s]",
			, ErrorConditionalOrder->BrokerIDErrorConditionalOrder->InvestorID, ErrorConditionalOrder->reserve1, ErrorConditionalOrder->OrderRef, ErrorConditionalOrder->UserID, ErrorConditionalOrder->OrderPriceType, ErrorConditionalOrder->Direction, ErrorConditionalOrder->CombOffsetFlag, ErrorConditionalOrder->CombHedgeFlag, ErrorConditionalOrder->LimitPrice, ErrorConditionalOrder->VolumeTotalOriginal, ErrorConditionalOrder->TimeCondition, ErrorConditionalOrder->GTDDate, ErrorConditionalOrder->VolumeCondition, ErrorConditionalOrder->MinVolume, ErrorConditionalOrder->ContingentCondition, ErrorConditionalOrder->StopPrice, ErrorConditionalOrder->ForceCloseReason, ErrorConditionalOrder->IsAutoSuspend, ErrorConditionalOrder->BusinessUnit, ErrorConditionalOrder->RequestID, ErrorConditionalOrder->OrderLocalID, ErrorConditionalOrder->ExchangeID, ErrorConditionalOrder->ParticipantID, ErrorConditionalOrder->ClientID, ErrorConditionalOrder->reserve2, ErrorConditionalOrder->TraderID, ErrorConditionalOrder->InstallID, ErrorConditionalOrder->OrderSubmitStatus, ErrorConditionalOrder->NotifySequence, ErrorConditionalOrder->TradingDay, ErrorConditionalOrder->SettlementID, ErrorConditionalOrder->OrderSysID, ErrorConditionalOrder->OrderSource, ErrorConditionalOrder->OrderStatus, ErrorConditionalOrder->OrderType, ErrorConditionalOrder->VolumeTraded, ErrorConditionalOrder->VolumeTotal, ErrorConditionalOrder->InsertDate, ErrorConditionalOrder->InsertTime, ErrorConditionalOrder->ActiveTime, ErrorConditionalOrder->SuspendTime, ErrorConditionalOrder->UpdateTime, ErrorConditionalOrder->CancelTime, ErrorConditionalOrder->ActiveTraderID, ErrorConditionalOrder->ClearingPartID, ErrorConditionalOrder->SequenceNo, ErrorConditionalOrder->FrontID, ErrorConditionalOrder->SessionID, ErrorConditionalOrder->UserProductInfo, ErrorConditionalOrder->StatusMsg, ErrorConditionalOrder->UserForceClose, ErrorConditionalOrder->ActiveUserID, ErrorConditionalOrder->BrokerOrderSeq, ErrorConditionalOrder->RelativeOrderSysID, ErrorConditionalOrder->ZCETotalTradedVolume, ErrorConditionalOrder->ErrorID, ErrorConditionalOrder->ErrorMsg, ErrorConditionalOrder->IsSwapOrder, ErrorConditionalOrder->BranchID, ErrorConditionalOrder->InvestUnitID, ErrorConditionalOrder->AccountID, ErrorConditionalOrder->CurrencyID, ErrorConditionalOrder->reserve3, ErrorConditionalOrder->MacAddress, ErrorConditionalOrder->InstrumentID, ErrorConditionalOrder->ExchangeInstID, ErrorConditionalOrder->IPAddress);
	}
}

void WriteQryErrOrderAction(CThostFtdcQryErrOrderActionField* QryErrOrderAction)
{
	if(QryErrOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryErrOrderActionField: , BrokerID[%s]InvestorID[%s]",
			, QryErrOrderAction->BrokerIDQryErrOrderAction->InvestorID);
	}
}

void WriteErrOrderAction(CThostFtdcErrOrderActionField* ErrOrderAction)
{
	if(ErrOrderAction)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcErrOrderActionField: , BrokerID[%s]InvestorID[%s], OrderActionRef[%d], OrderRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], OrderSysID[%s], ActionFlag[%c], LimitPrice[%f], VolumeChange[%d], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], OrderLocalID[%s], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], StatusMsg[%s], reserve1[%s], BranchID[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], ErrorID[%d], ErrorMsg[%s], InstrumentID[%s], IPAddress[%s]",
			, ErrOrderAction->BrokerIDErrOrderAction->InvestorID, ErrOrderAction->OrderActionRef, ErrOrderAction->OrderRef, ErrOrderAction->RequestID, ErrOrderAction->FrontID, ErrOrderAction->SessionID, ErrOrderAction->ExchangeID, ErrOrderAction->OrderSysID, ErrOrderAction->ActionFlag, ErrOrderAction->LimitPrice, ErrOrderAction->VolumeChange, ErrOrderAction->ActionDate, ErrOrderAction->ActionTime, ErrOrderAction->TraderID, ErrOrderAction->InstallID, ErrOrderAction->OrderLocalID, ErrOrderAction->ActionLocalID, ErrOrderAction->ParticipantID, ErrOrderAction->ClientID, ErrOrderAction->BusinessUnit, ErrOrderAction->OrderActionStatus, ErrOrderAction->UserID, ErrOrderAction->StatusMsg, ErrOrderAction->reserve1, ErrOrderAction->BranchID, ErrOrderAction->InvestUnitID, ErrOrderAction->reserve2, ErrOrderAction->MacAddress, ErrOrderAction->ErrorID, ErrOrderAction->ErrorMsg, ErrOrderAction->InstrumentID, ErrOrderAction->IPAddress);
	}
}

void WriteQryExchangeSequence(CThostFtdcQryExchangeSequenceField* QryExchangeSequence)
{
	if(QryExchangeSequence)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryExchangeSequenceField: , ExchangeID[%s]",
			, QryExchangeSequence->ExchangeID);
	}
}

void WriteExchangeSequence(CThostFtdcExchangeSequenceField* ExchangeSequence)
{
	if(ExchangeSequence)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcExchangeSequenceField: , ExchangeID[%s]SequenceNo[%d], MarketStatus[%c]",
			, ExchangeSequence->ExchangeIDExchangeSequence->SequenceNo, ExchangeSequence->MarketStatus);
	}
}

void WriteQryMaxOrderVolumeWithPrice(CThostFtdcQryMaxOrderVolumeWithPriceField* QryMaxOrderVolumeWithPrice)
{
	if(QryMaxOrderVolumeWithPrice)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryMaxOrderVolumeWithPriceField: , BrokerID[%s]InvestorID[%s], reserve1[%s], Direction[%c], OffsetFlag[%c], HedgeFlag[%c], MaxVolume[%d], Price[%f], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			, QryMaxOrderVolumeWithPrice->BrokerIDQryMaxOrderVolumeWithPrice->InvestorID, QryMaxOrderVolumeWithPrice->reserve1, QryMaxOrderVolumeWithPrice->Direction, QryMaxOrderVolumeWithPrice->OffsetFlag, QryMaxOrderVolumeWithPrice->HedgeFlag, QryMaxOrderVolumeWithPrice->MaxVolume, QryMaxOrderVolumeWithPrice->Price, QryMaxOrderVolumeWithPrice->ExchangeID, QryMaxOrderVolumeWithPrice->InvestUnitID, QryMaxOrderVolumeWithPrice->InstrumentID);
	}
}

void WriteQryBrokerTradingParams(CThostFtdcQryBrokerTradingParamsField* QryBrokerTradingParams)
{
	if(QryBrokerTradingParams)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryBrokerTradingParamsField: , BrokerID[%s]InvestorID[%s], CurrencyID[%s], AccountID[%s]",
			, QryBrokerTradingParams->BrokerIDQryBrokerTradingParams->InvestorID, QryBrokerTradingParams->CurrencyID, QryBrokerTradingParams->AccountID);
	}
}

void WriteBrokerTradingParams(CThostFtdcBrokerTradingParamsField* BrokerTradingParams)
{
	if(BrokerTradingParams)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcBrokerTradingParamsField: , BrokerID[%s]InvestorID[%s], MarginPriceType[%c], Algorithm[%c], AvailIncludeCloseProfit[%c], CurrencyID[%s], OptionRoyaltyPriceType[%c], AccountID[%s]",
			, BrokerTradingParams->BrokerIDBrokerTradingParams->InvestorID, BrokerTradingParams->MarginPriceType, BrokerTradingParams->Algorithm, BrokerTradingParams->AvailIncludeCloseProfit, BrokerTradingParams->CurrencyID, BrokerTradingParams->OptionRoyaltyPriceType, BrokerTradingParams->AccountID);
	}
}

void WriteQryBrokerTradingAlgos(CThostFtdcQryBrokerTradingAlgosField* QryBrokerTradingAlgos)
{
	if(QryBrokerTradingAlgos)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryBrokerTradingAlgosField: , BrokerID[%s]ExchangeID[%s], reserve1[%s], InstrumentID[%s]",
			, QryBrokerTradingAlgos->BrokerIDQryBrokerTradingAlgos->ExchangeID, QryBrokerTradingAlgos->reserve1, QryBrokerTradingAlgos->InstrumentID);
	}
}

void WriteBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField* BrokerTradingAlgos)
{
	if(BrokerTradingAlgos)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcBrokerTradingAlgosField: , BrokerID[%s]ExchangeID[%s], reserve1[%s], HandlePositionAlgoID[%c], FindMarginRateAlgoID[%c], HandleTradingAccountAlgoID[%c], InstrumentID[%s]",
			, BrokerTradingAlgos->BrokerIDBrokerTradingAlgos->ExchangeID, BrokerTradingAlgos->reserve1, BrokerTradingAlgos->HandlePositionAlgoID, BrokerTradingAlgos->FindMarginRateAlgoID, BrokerTradingAlgos->HandleTradingAccountAlgoID, BrokerTradingAlgos->InstrumentID);
	}
}

void WriteQueryBrokerDeposit(CThostFtdcQueryBrokerDepositField* QueryBrokerDeposit)
{
	if(QueryBrokerDeposit)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQueryBrokerDepositField: , BrokerID[%s]ExchangeID[%s]",
			, QueryBrokerDeposit->BrokerIDQueryBrokerDeposit->ExchangeID);
	}
}

void WriteBrokerDeposit(CThostFtdcBrokerDepositField* BrokerDeposit)
{
	if(BrokerDeposit)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcBrokerDepositField: , TradingDay[%s]BrokerID[%s], ParticipantID[%s], ExchangeID[%s], PreBalance[%f], CurrMargin[%f], CloseProfit[%f], Balance[%f], Deposit[%f], Withdraw[%f], Available[%f], Reserve[%f], FrozenMargin[%f]",
			, BrokerDeposit->TradingDayBrokerDeposit->BrokerID, BrokerDeposit->ParticipantID, BrokerDeposit->ExchangeID, BrokerDeposit->PreBalance, BrokerDeposit->CurrMargin, BrokerDeposit->CloseProfit, BrokerDeposit->Balance, BrokerDeposit->Deposit, BrokerDeposit->Withdraw, BrokerDeposit->Available, BrokerDeposit->Reserve, BrokerDeposit->FrozenMargin);
	}
}

void WriteQryCFMMCBrokerKey(CThostFtdcQryCFMMCBrokerKeyField* QryCFMMCBrokerKey)
{
	if(QryCFMMCBrokerKey)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryCFMMCBrokerKeyField: , BrokerID[%s]",
			, QryCFMMCBrokerKey->BrokerID);
	}
}

void WriteCFMMCBrokerKey(CThostFtdcCFMMCBrokerKeyField* CFMMCBrokerKey)
{
	if(CFMMCBrokerKey)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcCFMMCBrokerKeyField: , BrokerID[%s]ParticipantID[%s], CreateDate[%s], CreateTime[%s], KeyID[%d], CurrentKey[%s], KeyKind[%c]",
			, CFMMCBrokerKey->BrokerIDCFMMCBrokerKey->ParticipantID, CFMMCBrokerKey->CreateDate, CFMMCBrokerKey->CreateTime, CFMMCBrokerKey->KeyID, CFMMCBrokerKey->CurrentKey, CFMMCBrokerKey->KeyKind);
	}
}

void WriteCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField* CFMMCTradingAccountKey)
{
	if(CFMMCTradingAccountKey)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcCFMMCTradingAccountKeyField: , BrokerID[%s]ParticipantID[%s], AccountID[%s], KeyID[%d], CurrentKey[%s]",
			, CFMMCTradingAccountKey->BrokerIDCFMMCTradingAccountKey->ParticipantID, CFMMCTradingAccountKey->AccountID, CFMMCTradingAccountKey->KeyID, CFMMCTradingAccountKey->CurrentKey);
	}
}

void WriteQryCFMMCTradingAccountKey(CThostFtdcQryCFMMCTradingAccountKeyField* QryCFMMCTradingAccountKey)
{
	if(QryCFMMCTradingAccountKey)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryCFMMCTradingAccountKeyField: , BrokerID[%s]InvestorID[%s]",
			, QryCFMMCTradingAccountKey->BrokerIDQryCFMMCTradingAccountKey->InvestorID);
	}
}

void WriteBrokerUserOTPParam(CThostFtdcBrokerUserOTPParamField* BrokerUserOTPParam)
{
	if(BrokerUserOTPParam)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcBrokerUserOTPParamField: , BrokerID[%s]UserID[%s], OTPVendorsID[%s], SerialNumber[%s], AuthKey[%s], LastDrift[%d], LastSuccess[%d], OTPType[%c]",
			, BrokerUserOTPParam->BrokerIDBrokerUserOTPParam->UserID, BrokerUserOTPParam->OTPVendorsID, BrokerUserOTPParam->SerialNumber, BrokerUserOTPParam->AuthKey, BrokerUserOTPParam->LastDrift, BrokerUserOTPParam->LastSuccess, BrokerUserOTPParam->OTPType);
	}
}

void WriteManualSyncBrokerUserOTP(CThostFtdcManualSyncBrokerUserOTPField* ManualSyncBrokerUserOTP)
{
	if(ManualSyncBrokerUserOTP)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcManualSyncBrokerUserOTPField: , BrokerID[%s]UserID[%s], OTPType[%c], FirstOTP[%s], SecondOTP[%s]",
			, ManualSyncBrokerUserOTP->BrokerIDManualSyncBrokerUserOTP->UserID, ManualSyncBrokerUserOTP->OTPType, ManualSyncBrokerUserOTP->FirstOTP, ManualSyncBrokerUserOTP->SecondOTP);
	}
}

void WriteCommRateModel(CThostFtdcCommRateModelField* CommRateModel)
{
	if(CommRateModel)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcCommRateModelField: , BrokerID[%s]CommModelID[%s], CommModelName[%s]",
			, CommRateModel->BrokerIDCommRateModel->CommModelID, CommRateModel->CommModelName);
	}
}

void WriteQryCommRateModel(CThostFtdcQryCommRateModelField* QryCommRateModel)
{
	if(QryCommRateModel)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryCommRateModelField: , BrokerID[%s]CommModelID[%s]",
			, QryCommRateModel->BrokerIDQryCommRateModel->CommModelID);
	}
}

void WriteMarginModel(CThostFtdcMarginModelField* MarginModel)
{
	if(MarginModel)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcMarginModelField: , BrokerID[%s]MarginModelID[%s], MarginModelName[%s]",
			, MarginModel->BrokerIDMarginModel->MarginModelID, MarginModel->MarginModelName);
	}
}

void WriteQryMarginModel(CThostFtdcQryMarginModelField* QryMarginModel)
{
	if(QryMarginModel)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryMarginModelField: , BrokerID[%s]MarginModelID[%s]",
			, QryMarginModel->BrokerIDQryMarginModel->MarginModelID);
	}
}

void WriteEWarrantOffset(CThostFtdcEWarrantOffsetField* EWarrantOffset)
{
	if(EWarrantOffset)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcEWarrantOffsetField: , TradingDay[%s]BrokerID[%s], InvestorID[%s], ExchangeID[%s], reserve1[%s], Direction[%c], HedgeFlag[%c], Volume[%d], InvestUnitID[%s], InstrumentID[%s]",
			, EWarrantOffset->TradingDayEWarrantOffset->BrokerID, EWarrantOffset->InvestorID, EWarrantOffset->ExchangeID, EWarrantOffset->reserve1, EWarrantOffset->Direction, EWarrantOffset->HedgeFlag, EWarrantOffset->Volume, EWarrantOffset->InvestUnitID, EWarrantOffset->InstrumentID);
	}
}

void WriteQryEWarrantOffset(CThostFtdcQryEWarrantOffsetField* QryEWarrantOffset)
{
	if(QryEWarrantOffset)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryEWarrantOffsetField: , BrokerID[%s]InvestorID[%s], ExchangeID[%s], reserve1[%s], InvestUnitID[%s], InstrumentID[%s]",
			, QryEWarrantOffset->BrokerIDQryEWarrantOffset->InvestorID, QryEWarrantOffset->ExchangeID, QryEWarrantOffset->reserve1, QryEWarrantOffset->InvestUnitID, QryEWarrantOffset->InstrumentID);
	}
}

void WriteQryInvestorProductGroupMargin(CThostFtdcQryInvestorProductGroupMarginField* QryInvestorProductGroupMargin)
{
	if(QryInvestorProductGroupMargin)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryInvestorProductGroupMarginField: , BrokerID[%s]InvestorID[%s], reserve1[%s], HedgeFlag[%c], ExchangeID[%s], InvestUnitID[%s], ProductGroupID[%s]",
			, QryInvestorProductGroupMargin->BrokerIDQryInvestorProductGroupMargin->InvestorID, QryInvestorProductGroupMargin->reserve1, QryInvestorProductGroupMargin->HedgeFlag, QryInvestorProductGroupMargin->ExchangeID, QryInvestorProductGroupMargin->InvestUnitID, QryInvestorProductGroupMargin->ProductGroupID);
	}
}

void WriteInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField* InvestorProductGroupMargin)
{
	if(InvestorProductGroupMargin)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInvestorProductGroupMarginField: , reserve1[%s]BrokerID[%s], InvestorID[%s], TradingDay[%s], SettlementID[%d], FrozenMargin[%f], LongFrozenMargin[%f], ShortFrozenMargin[%f], UseMargin[%f], LongUseMargin[%f], ShortUseMargin[%f], ExchMargin[%f], LongExchMargin[%f], ShortExchMargin[%f], CloseProfit[%f], FrozenCommission[%f], Commission[%f], FrozenCash[%f], CashIn[%f], PositionProfit[%f], OffsetAmount[%f], LongOffsetAmount[%f], ShortOffsetAmount[%f], ExchOffsetAmount[%f], LongExchOffsetAmount[%f], ShortExchOffsetAmount[%f], HedgeFlag[%c], ExchangeID[%s], InvestUnitID[%s], ProductGroupID[%s]",
			, InvestorProductGroupMargin->reserve1InvestorProductGroupMargin->BrokerID, InvestorProductGroupMargin->InvestorID, InvestorProductGroupMargin->TradingDay, InvestorProductGroupMargin->SettlementID, InvestorProductGroupMargin->FrozenMargin, InvestorProductGroupMargin->LongFrozenMargin, InvestorProductGroupMargin->ShortFrozenMargin, InvestorProductGroupMargin->UseMargin, InvestorProductGroupMargin->LongUseMargin, InvestorProductGroupMargin->ShortUseMargin, InvestorProductGroupMargin->ExchMargin, InvestorProductGroupMargin->LongExchMargin, InvestorProductGroupMargin->ShortExchMargin, InvestorProductGroupMargin->CloseProfit, InvestorProductGroupMargin->FrozenCommission, InvestorProductGroupMargin->Commission, InvestorProductGroupMargin->FrozenCash, InvestorProductGroupMargin->CashIn, InvestorProductGroupMargin->PositionProfit, InvestorProductGroupMargin->OffsetAmount, InvestorProductGroupMargin->LongOffsetAmount, InvestorProductGroupMargin->ShortOffsetAmount, InvestorProductGroupMargin->ExchOffsetAmount, InvestorProductGroupMargin->LongExchOffsetAmount, InvestorProductGroupMargin->ShortExchOffsetAmount, InvestorProductGroupMargin->HedgeFlag, InvestorProductGroupMargin->ExchangeID, InvestorProductGroupMargin->InvestUnitID, InvestorProductGroupMargin->ProductGroupID);
	}
}

void WriteQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField* QueryCFMMCTradingAccountToken)
{
	if(QueryCFMMCTradingAccountToken)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQueryCFMMCTradingAccountTokenField: , BrokerID[%s]InvestorID[%s], InvestUnitID[%s]",
			, QueryCFMMCTradingAccountToken->BrokerIDQueryCFMMCTradingAccountToken->InvestorID, QueryCFMMCTradingAccountToken->InvestUnitID);
	}
}

void WriteCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField* CFMMCTradingAccountToken)
{
	if(CFMMCTradingAccountToken)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcCFMMCTradingAccountTokenField: , BrokerID[%s]ParticipantID[%s], AccountID[%s], KeyID[%d], Token[%s]",
			, CFMMCTradingAccountToken->BrokerIDCFMMCTradingAccountToken->ParticipantID, CFMMCTradingAccountToken->AccountID, CFMMCTradingAccountToken->KeyID, CFMMCTradingAccountToken->Token);
	}
}

void WriteQryProductGroup(CThostFtdcQryProductGroupField* QryProductGroup)
{
	if(QryProductGroup)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryProductGroupField: , reserve1[%s]ExchangeID[%s], ProductID[%s]",
			, QryProductGroup->reserve1QryProductGroup->ExchangeID, QryProductGroup->ProductID);
	}
}

void WriteProductGroup(CThostFtdcProductGroupField* ProductGroup)
{
	if(ProductGroup)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcProductGroupField: , reserve1[%s]ExchangeID[%s], reserve2[%s], ProductID[%s], ProductGroupID[%s]",
			, ProductGroup->reserve1ProductGroup->ExchangeID, ProductGroup->reserve2, ProductGroup->ProductID, ProductGroup->ProductGroupID);
	}
}

void WriteBulletin(CThostFtdcBulletinField* Bulletin)
{
	if(Bulletin)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcBulletinField: , ExchangeID[%s]TradingDay[%s], BulletinID[%d], SequenceNo[%d], NewsType[%s], NewsUrgency[%c], SendTime[%s], Abstract[%s], ComeFrom[%s], Content[%s], URLLink[%s], MarketID[%s]",
			, Bulletin->ExchangeIDBulletin->TradingDay, Bulletin->BulletinID, Bulletin->SequenceNo, Bulletin->NewsType, Bulletin->NewsUrgency, Bulletin->SendTime, Bulletin->Abstract, Bulletin->ComeFrom, Bulletin->Content, Bulletin->URLLink, Bulletin->MarketID);
	}
}

void WriteQryBulletin(CThostFtdcQryBulletinField* QryBulletin)
{
	if(QryBulletin)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryBulletinField: , ExchangeID[%s]BulletinID[%d], SequenceNo[%d], NewsType[%s], NewsUrgency[%c]",
			, QryBulletin->ExchangeIDQryBulletin->BulletinID, QryBulletin->SequenceNo, QryBulletin->NewsType, QryBulletin->NewsUrgency);
	}
}

void WriteMulticastInstrument(CThostFtdcMulticastInstrumentField* MulticastInstrument)
{
	if(MulticastInstrument)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcMulticastInstrumentField: , TopicID[%d]reserve1[%s], InstrumentNo[%d], CodePrice[%f], VolumeMultiple[%d], PriceTick[%f], InstrumentID[%s]",
			, MulticastInstrument->TopicIDMulticastInstrument->reserve1, MulticastInstrument->InstrumentNo, MulticastInstrument->CodePrice, MulticastInstrument->VolumeMultiple, MulticastInstrument->PriceTick, MulticastInstrument->InstrumentID);
	}
}

void WriteQryMulticastInstrument(CThostFtdcQryMulticastInstrumentField* QryMulticastInstrument)
{
	if(QryMulticastInstrument)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryMulticastInstrumentField: , TopicID[%d]reserve1[%s], InstrumentID[%s]",
			, QryMulticastInstrument->TopicIDQryMulticastInstrument->reserve1, QryMulticastInstrument->InstrumentID);
	}
}

void WriteAppIDAuthAssign(CThostFtdcAppIDAuthAssignField* AppIDAuthAssign)
{
	if(AppIDAuthAssign)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcAppIDAuthAssignField: , BrokerID[%s]AppID[%s], DRIdentityID[%d]",
			, AppIDAuthAssign->BrokerIDAppIDAuthAssign->AppID, AppIDAuthAssign->DRIdentityID);
	}
}

void WriteReqOpenAccount(CThostFtdcReqOpenAccountField* ReqOpenAccount)
{
	if(ReqOpenAccount)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqOpenAccountField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], Gender[%c], CountryCode[%s], CustType[%c], Address[%s], ZipCode[%s], Telephone[%s], MobilePhone[%s], Fax[%s], EMail[%s], MoneyAccountStatus[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], InstallID[%d], VerifyCertNoFlag[%c], CurrencyID[%s], CashExchangeCode[%c], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], TID[%d], UserID[%s], LongCustomerName[%s]",
			, ReqOpenAccount->TradeCodeReqOpenAccount->BankID, ReqOpenAccount->BankBranchID, ReqOpenAccount->BrokerID, ReqOpenAccount->BrokerBranchID, ReqOpenAccount->TradeDate, ReqOpenAccount->TradeTime, ReqOpenAccount->BankSerial, ReqOpenAccount->TradingDay, ReqOpenAccount->PlateSerial, ReqOpenAccount->LastFragment, ReqOpenAccount->SessionID, ReqOpenAccount->CustomerName, ReqOpenAccount->IdCardType, ReqOpenAccount->IdentifiedCardNo, ReqOpenAccount->Gender, ReqOpenAccount->CountryCode, ReqOpenAccount->CustType, ReqOpenAccount->Address, ReqOpenAccount->ZipCode, ReqOpenAccount->Telephone, ReqOpenAccount->MobilePhone, ReqOpenAccount->Fax, ReqOpenAccount->EMail, ReqOpenAccount->MoneyAccountStatus, ReqOpenAccount->BankAccount, ReqOpenAccount->BankPassWord, ReqOpenAccount->AccountID, ReqOpenAccount->Password, ReqOpenAccount->InstallID, ReqOpenAccount->VerifyCertNoFlag, ReqOpenAccount->CurrencyID, ReqOpenAccount->CashExchangeCode, ReqOpenAccount->Digest, ReqOpenAccount->BankAccType, ReqOpenAccount->DeviceID, ReqOpenAccount->BankSecuAccType, ReqOpenAccount->BrokerIDByBank, ReqOpenAccount->BankSecuAcc, ReqOpenAccount->BankPwdFlag, ReqOpenAccount->SecuPwdFlag, ReqOpenAccount->OperNo, ReqOpenAccount->TID, ReqOpenAccount->UserID, ReqOpenAccount->LongCustomerName);
	}
}

void WriteReqCancelAccount(CThostFtdcReqCancelAccountField* ReqCancelAccount)
{
	if(ReqCancelAccount)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqCancelAccountField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], Gender[%c], CountryCode[%s], CustType[%c], Address[%s], ZipCode[%s], Telephone[%s], MobilePhone[%s], Fax[%s], EMail[%s], MoneyAccountStatus[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], InstallID[%d], VerifyCertNoFlag[%c], CurrencyID[%s], CashExchangeCode[%c], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], TID[%d], UserID[%s], LongCustomerName[%s]",
			, ReqCancelAccount->TradeCodeReqCancelAccount->BankID, ReqCancelAccount->BankBranchID, ReqCancelAccount->BrokerID, ReqCancelAccount->BrokerBranchID, ReqCancelAccount->TradeDate, ReqCancelAccount->TradeTime, ReqCancelAccount->BankSerial, ReqCancelAccount->TradingDay, ReqCancelAccount->PlateSerial, ReqCancelAccount->LastFragment, ReqCancelAccount->SessionID, ReqCancelAccount->CustomerName, ReqCancelAccount->IdCardType, ReqCancelAccount->IdentifiedCardNo, ReqCancelAccount->Gender, ReqCancelAccount->CountryCode, ReqCancelAccount->CustType, ReqCancelAccount->Address, ReqCancelAccount->ZipCode, ReqCancelAccount->Telephone, ReqCancelAccount->MobilePhone, ReqCancelAccount->Fax, ReqCancelAccount->EMail, ReqCancelAccount->MoneyAccountStatus, ReqCancelAccount->BankAccount, ReqCancelAccount->BankPassWord, ReqCancelAccount->AccountID, ReqCancelAccount->Password, ReqCancelAccount->InstallID, ReqCancelAccount->VerifyCertNoFlag, ReqCancelAccount->CurrencyID, ReqCancelAccount->CashExchangeCode, ReqCancelAccount->Digest, ReqCancelAccount->BankAccType, ReqCancelAccount->DeviceID, ReqCancelAccount->BankSecuAccType, ReqCancelAccount->BrokerIDByBank, ReqCancelAccount->BankSecuAcc, ReqCancelAccount->BankPwdFlag, ReqCancelAccount->SecuPwdFlag, ReqCancelAccount->OperNo, ReqCancelAccount->TID, ReqCancelAccount->UserID, ReqCancelAccount->LongCustomerName);
	}
}

void WriteReqChangeAccount(CThostFtdcReqChangeAccountField* ReqChangeAccount)
{
	if(ReqChangeAccount)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqChangeAccountField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], Gender[%c], CountryCode[%s], CustType[%c], Address[%s], ZipCode[%s], Telephone[%s], MobilePhone[%s], Fax[%s], EMail[%s], MoneyAccountStatus[%c], BankAccount[%s], BankPassWord[%s], NewBankAccount[%s], NewBankPassWord[%s], AccountID[%s], Password[%s], BankAccType[%c], InstallID[%d], VerifyCertNoFlag[%c], CurrencyID[%s], BrokerIDByBank[%s], BankPwdFlag[%c], SecuPwdFlag[%c], TID[%d], Digest[%s], LongCustomerName[%s]",
			, ReqChangeAccount->TradeCodeReqChangeAccount->BankID, ReqChangeAccount->BankBranchID, ReqChangeAccount->BrokerID, ReqChangeAccount->BrokerBranchID, ReqChangeAccount->TradeDate, ReqChangeAccount->TradeTime, ReqChangeAccount->BankSerial, ReqChangeAccount->TradingDay, ReqChangeAccount->PlateSerial, ReqChangeAccount->LastFragment, ReqChangeAccount->SessionID, ReqChangeAccount->CustomerName, ReqChangeAccount->IdCardType, ReqChangeAccount->IdentifiedCardNo, ReqChangeAccount->Gender, ReqChangeAccount->CountryCode, ReqChangeAccount->CustType, ReqChangeAccount->Address, ReqChangeAccount->ZipCode, ReqChangeAccount->Telephone, ReqChangeAccount->MobilePhone, ReqChangeAccount->Fax, ReqChangeAccount->EMail, ReqChangeAccount->MoneyAccountStatus, ReqChangeAccount->BankAccount, ReqChangeAccount->BankPassWord, ReqChangeAccount->NewBankAccount, ReqChangeAccount->NewBankPassWord, ReqChangeAccount->AccountID, ReqChangeAccount->Password, ReqChangeAccount->BankAccType, ReqChangeAccount->InstallID, ReqChangeAccount->VerifyCertNoFlag, ReqChangeAccount->CurrencyID, ReqChangeAccount->BrokerIDByBank, ReqChangeAccount->BankPwdFlag, ReqChangeAccount->SecuPwdFlag, ReqChangeAccount->TID, ReqChangeAccount->Digest, ReqChangeAccount->LongCustomerName);
	}
}

void WriteReqTransfer(CThostFtdcReqTransferField* ReqTransfer)
{
	if(ReqTransfer)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqTransferField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], InstallID[%d], FutureSerial[%d], UserID[%s], VerifyCertNoFlag[%c], CurrencyID[%s], TradeAmount[%f], FutureFetchAmount[%f], FeePayFlag[%c], CustFee[%f], BrokerFee[%f], Message[%s], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], RequestID[%d], TID[%d], TransferStatus[%c], LongCustomerName[%s]",
			, ReqTransfer->TradeCodeReqTransfer->BankID, ReqTransfer->BankBranchID, ReqTransfer->BrokerID, ReqTransfer->BrokerBranchID, ReqTransfer->TradeDate, ReqTransfer->TradeTime, ReqTransfer->BankSerial, ReqTransfer->TradingDay, ReqTransfer->PlateSerial, ReqTransfer->LastFragment, ReqTransfer->SessionID, ReqTransfer->CustomerName, ReqTransfer->IdCardType, ReqTransfer->IdentifiedCardNo, ReqTransfer->CustType, ReqTransfer->BankAccount, ReqTransfer->BankPassWord, ReqTransfer->AccountID, ReqTransfer->Password, ReqTransfer->InstallID, ReqTransfer->FutureSerial, ReqTransfer->UserID, ReqTransfer->VerifyCertNoFlag, ReqTransfer->CurrencyID, ReqTransfer->TradeAmount, ReqTransfer->FutureFetchAmount, ReqTransfer->FeePayFlag, ReqTransfer->CustFee, ReqTransfer->BrokerFee, ReqTransfer->Message, ReqTransfer->Digest, ReqTransfer->BankAccType, ReqTransfer->DeviceID, ReqTransfer->BankSecuAccType, ReqTransfer->BrokerIDByBank, ReqTransfer->BankSecuAcc, ReqTransfer->BankPwdFlag, ReqTransfer->SecuPwdFlag, ReqTransfer->OperNo, ReqTransfer->RequestID, ReqTransfer->TID, ReqTransfer->TransferStatus, ReqTransfer->LongCustomerName);
	}
}

void WriteRspTransfer(CThostFtdcRspTransferField* RspTransfer)
{
	if(RspTransfer)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRspTransferField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], InstallID[%d], FutureSerial[%d], UserID[%s], VerifyCertNoFlag[%c], CurrencyID[%s], TradeAmount[%f], FutureFetchAmount[%f], FeePayFlag[%c], CustFee[%f], BrokerFee[%f], Message[%s], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], RequestID[%d], TID[%d], TransferStatus[%c], ErrorID[%d], ErrorMsg[%s], LongCustomerName[%s]",
			, RspTransfer->TradeCodeRspTransfer->BankID, RspTransfer->BankBranchID, RspTransfer->BrokerID, RspTransfer->BrokerBranchID, RspTransfer->TradeDate, RspTransfer->TradeTime, RspTransfer->BankSerial, RspTransfer->TradingDay, RspTransfer->PlateSerial, RspTransfer->LastFragment, RspTransfer->SessionID, RspTransfer->CustomerName, RspTransfer->IdCardType, RspTransfer->IdentifiedCardNo, RspTransfer->CustType, RspTransfer->BankAccount, RspTransfer->BankPassWord, RspTransfer->AccountID, RspTransfer->Password, RspTransfer->InstallID, RspTransfer->FutureSerial, RspTransfer->UserID, RspTransfer->VerifyCertNoFlag, RspTransfer->CurrencyID, RspTransfer->TradeAmount, RspTransfer->FutureFetchAmount, RspTransfer->FeePayFlag, RspTransfer->CustFee, RspTransfer->BrokerFee, RspTransfer->Message, RspTransfer->Digest, RspTransfer->BankAccType, RspTransfer->DeviceID, RspTransfer->BankSecuAccType, RspTransfer->BrokerIDByBank, RspTransfer->BankSecuAcc, RspTransfer->BankPwdFlag, RspTransfer->SecuPwdFlag, RspTransfer->OperNo, RspTransfer->RequestID, RspTransfer->TID, RspTransfer->TransferStatus, RspTransfer->ErrorID, RspTransfer->ErrorMsg, RspTransfer->LongCustomerName);
	}
}

void WriteReqRepeal(CThostFtdcReqRepealField* ReqRepeal)
{
	if(ReqRepeal)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqRepealField: , RepealTimeInterval[%d]RepealedTimes[%d], BankRepealFlag[%c], BrokerRepealFlag[%c], PlateRepealSerial[%d], BankRepealSerial[%s], FutureRepealSerial[%d], TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], InstallID[%d], FutureSerial[%d], UserID[%s], VerifyCertNoFlag[%c], CurrencyID[%s], TradeAmount[%f], FutureFetchAmount[%f], FeePayFlag[%c], CustFee[%f], BrokerFee[%f], Message[%s], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], RequestID[%d], TID[%d], TransferStatus[%c], LongCustomerName[%s]",
			, ReqRepeal->RepealTimeIntervalReqRepeal->RepealedTimes, ReqRepeal->BankRepealFlag, ReqRepeal->BrokerRepealFlag, ReqRepeal->PlateRepealSerial, ReqRepeal->BankRepealSerial, ReqRepeal->FutureRepealSerial, ReqRepeal->TradeCode, ReqRepeal->BankID, ReqRepeal->BankBranchID, ReqRepeal->BrokerID, ReqRepeal->BrokerBranchID, ReqRepeal->TradeDate, ReqRepeal->TradeTime, ReqRepeal->BankSerial, ReqRepeal->TradingDay, ReqRepeal->PlateSerial, ReqRepeal->LastFragment, ReqRepeal->SessionID, ReqRepeal->CustomerName, ReqRepeal->IdCardType, ReqRepeal->IdentifiedCardNo, ReqRepeal->CustType, ReqRepeal->BankAccount, ReqRepeal->BankPassWord, ReqRepeal->AccountID, ReqRepeal->Password, ReqRepeal->InstallID, ReqRepeal->FutureSerial, ReqRepeal->UserID, ReqRepeal->VerifyCertNoFlag, ReqRepeal->CurrencyID, ReqRepeal->TradeAmount, ReqRepeal->FutureFetchAmount, ReqRepeal->FeePayFlag, ReqRepeal->CustFee, ReqRepeal->BrokerFee, ReqRepeal->Message, ReqRepeal->Digest, ReqRepeal->BankAccType, ReqRepeal->DeviceID, ReqRepeal->BankSecuAccType, ReqRepeal->BrokerIDByBank, ReqRepeal->BankSecuAcc, ReqRepeal->BankPwdFlag, ReqRepeal->SecuPwdFlag, ReqRepeal->OperNo, ReqRepeal->RequestID, ReqRepeal->TID, ReqRepeal->TransferStatus, ReqRepeal->LongCustomerName);
	}
}

void WriteRspRepeal(CThostFtdcRspRepealField* RspRepeal)
{
	if(RspRepeal)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRspRepealField: , RepealTimeInterval[%d]RepealedTimes[%d], BankRepealFlag[%c], BrokerRepealFlag[%c], PlateRepealSerial[%d], BankRepealSerial[%s], FutureRepealSerial[%d], TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], InstallID[%d], FutureSerial[%d], UserID[%s], VerifyCertNoFlag[%c], CurrencyID[%s], TradeAmount[%f], FutureFetchAmount[%f], FeePayFlag[%c], CustFee[%f], BrokerFee[%f], Message[%s], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], RequestID[%d], TID[%d], TransferStatus[%c], ErrorID[%d], ErrorMsg[%s], LongCustomerName[%s]",
			, RspRepeal->RepealTimeIntervalRspRepeal->RepealedTimes, RspRepeal->BankRepealFlag, RspRepeal->BrokerRepealFlag, RspRepeal->PlateRepealSerial, RspRepeal->BankRepealSerial, RspRepeal->FutureRepealSerial, RspRepeal->TradeCode, RspRepeal->BankID, RspRepeal->BankBranchID, RspRepeal->BrokerID, RspRepeal->BrokerBranchID, RspRepeal->TradeDate, RspRepeal->TradeTime, RspRepeal->BankSerial, RspRepeal->TradingDay, RspRepeal->PlateSerial, RspRepeal->LastFragment, RspRepeal->SessionID, RspRepeal->CustomerName, RspRepeal->IdCardType, RspRepeal->IdentifiedCardNo, RspRepeal->CustType, RspRepeal->BankAccount, RspRepeal->BankPassWord, RspRepeal->AccountID, RspRepeal->Password, RspRepeal->InstallID, RspRepeal->FutureSerial, RspRepeal->UserID, RspRepeal->VerifyCertNoFlag, RspRepeal->CurrencyID, RspRepeal->TradeAmount, RspRepeal->FutureFetchAmount, RspRepeal->FeePayFlag, RspRepeal->CustFee, RspRepeal->BrokerFee, RspRepeal->Message, RspRepeal->Digest, RspRepeal->BankAccType, RspRepeal->DeviceID, RspRepeal->BankSecuAccType, RspRepeal->BrokerIDByBank, RspRepeal->BankSecuAcc, RspRepeal->BankPwdFlag, RspRepeal->SecuPwdFlag, RspRepeal->OperNo, RspRepeal->RequestID, RspRepeal->TID, RspRepeal->TransferStatus, RspRepeal->ErrorID, RspRepeal->ErrorMsg, RspRepeal->LongCustomerName);
	}
}

void WriteReqQueryAccount(CThostFtdcReqQueryAccountField* ReqQueryAccount)
{
	if(ReqQueryAccount)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqQueryAccountField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], FutureSerial[%d], InstallID[%d], UserID[%s], VerifyCertNoFlag[%c], CurrencyID[%s], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], RequestID[%d], TID[%d], LongCustomerName[%s]",
			, ReqQueryAccount->TradeCodeReqQueryAccount->BankID, ReqQueryAccount->BankBranchID, ReqQueryAccount->BrokerID, ReqQueryAccount->BrokerBranchID, ReqQueryAccount->TradeDate, ReqQueryAccount->TradeTime, ReqQueryAccount->BankSerial, ReqQueryAccount->TradingDay, ReqQueryAccount->PlateSerial, ReqQueryAccount->LastFragment, ReqQueryAccount->SessionID, ReqQueryAccount->CustomerName, ReqQueryAccount->IdCardType, ReqQueryAccount->IdentifiedCardNo, ReqQueryAccount->CustType, ReqQueryAccount->BankAccount, ReqQueryAccount->BankPassWord, ReqQueryAccount->AccountID, ReqQueryAccount->Password, ReqQueryAccount->FutureSerial, ReqQueryAccount->InstallID, ReqQueryAccount->UserID, ReqQueryAccount->VerifyCertNoFlag, ReqQueryAccount->CurrencyID, ReqQueryAccount->Digest, ReqQueryAccount->BankAccType, ReqQueryAccount->DeviceID, ReqQueryAccount->BankSecuAccType, ReqQueryAccount->BrokerIDByBank, ReqQueryAccount->BankSecuAcc, ReqQueryAccount->BankPwdFlag, ReqQueryAccount->SecuPwdFlag, ReqQueryAccount->OperNo, ReqQueryAccount->RequestID, ReqQueryAccount->TID, ReqQueryAccount->LongCustomerName);
	}
}

void WriteRspQueryAccount(CThostFtdcRspQueryAccountField* RspQueryAccount)
{
	if(RspQueryAccount)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRspQueryAccountField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], FutureSerial[%d], InstallID[%d], UserID[%s], VerifyCertNoFlag[%c], CurrencyID[%s], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], RequestID[%d], TID[%d], BankUseAmount[%f], BankFetchAmount[%f], LongCustomerName[%s]",
			, RspQueryAccount->TradeCodeRspQueryAccount->BankID, RspQueryAccount->BankBranchID, RspQueryAccount->BrokerID, RspQueryAccount->BrokerBranchID, RspQueryAccount->TradeDate, RspQueryAccount->TradeTime, RspQueryAccount->BankSerial, RspQueryAccount->TradingDay, RspQueryAccount->PlateSerial, RspQueryAccount->LastFragment, RspQueryAccount->SessionID, RspQueryAccount->CustomerName, RspQueryAccount->IdCardType, RspQueryAccount->IdentifiedCardNo, RspQueryAccount->CustType, RspQueryAccount->BankAccount, RspQueryAccount->BankPassWord, RspQueryAccount->AccountID, RspQueryAccount->Password, RspQueryAccount->FutureSerial, RspQueryAccount->InstallID, RspQueryAccount->UserID, RspQueryAccount->VerifyCertNoFlag, RspQueryAccount->CurrencyID, RspQueryAccount->Digest, RspQueryAccount->BankAccType, RspQueryAccount->DeviceID, RspQueryAccount->BankSecuAccType, RspQueryAccount->BrokerIDByBank, RspQueryAccount->BankSecuAcc, RspQueryAccount->BankPwdFlag, RspQueryAccount->SecuPwdFlag, RspQueryAccount->OperNo, RspQueryAccount->RequestID, RspQueryAccount->TID, RspQueryAccount->BankUseAmount, RspQueryAccount->BankFetchAmount, RspQueryAccount->LongCustomerName);
	}
}

void WriteFutureSignIO(CThostFtdcFutureSignIOField* FutureSignIO)
{
	if(FutureSignIO)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcFutureSignIOField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], InstallID[%d], UserID[%s], Digest[%s], CurrencyID[%s], DeviceID[%s], BrokerIDByBank[%s], OperNo[%s], RequestID[%d], TID[%d]",
			, FutureSignIO->TradeCodeFutureSignIO->BankID, FutureSignIO->BankBranchID, FutureSignIO->BrokerID, FutureSignIO->BrokerBranchID, FutureSignIO->TradeDate, FutureSignIO->TradeTime, FutureSignIO->BankSerial, FutureSignIO->TradingDay, FutureSignIO->PlateSerial, FutureSignIO->LastFragment, FutureSignIO->SessionID, FutureSignIO->InstallID, FutureSignIO->UserID, FutureSignIO->Digest, FutureSignIO->CurrencyID, FutureSignIO->DeviceID, FutureSignIO->BrokerIDByBank, FutureSignIO->OperNo, FutureSignIO->RequestID, FutureSignIO->TID);
	}
}

void WriteRspFutureSignIn(CThostFtdcRspFutureSignInField* RspFutureSignIn)
{
	if(RspFutureSignIn)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRspFutureSignInField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], InstallID[%d], UserID[%s], Digest[%s], CurrencyID[%s], DeviceID[%s], BrokerIDByBank[%s], OperNo[%s], RequestID[%d], TID[%d], ErrorID[%d], ErrorMsg[%s], PinKey[%s], MacKey[%s]",
			, RspFutureSignIn->TradeCodeRspFutureSignIn->BankID, RspFutureSignIn->BankBranchID, RspFutureSignIn->BrokerID, RspFutureSignIn->BrokerBranchID, RspFutureSignIn->TradeDate, RspFutureSignIn->TradeTime, RspFutureSignIn->BankSerial, RspFutureSignIn->TradingDay, RspFutureSignIn->PlateSerial, RspFutureSignIn->LastFragment, RspFutureSignIn->SessionID, RspFutureSignIn->InstallID, RspFutureSignIn->UserID, RspFutureSignIn->Digest, RspFutureSignIn->CurrencyID, RspFutureSignIn->DeviceID, RspFutureSignIn->BrokerIDByBank, RspFutureSignIn->OperNo, RspFutureSignIn->RequestID, RspFutureSignIn->TID, RspFutureSignIn->ErrorID, RspFutureSignIn->ErrorMsg, RspFutureSignIn->PinKey, RspFutureSignIn->MacKey);
	}
}

void WriteReqFutureSignOut(CThostFtdcReqFutureSignOutField* ReqFutureSignOut)
{
	if(ReqFutureSignOut)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqFutureSignOutField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], InstallID[%d], UserID[%s], Digest[%s], CurrencyID[%s], DeviceID[%s], BrokerIDByBank[%s], OperNo[%s], RequestID[%d], TID[%d]",
			, ReqFutureSignOut->TradeCodeReqFutureSignOut->BankID, ReqFutureSignOut->BankBranchID, ReqFutureSignOut->BrokerID, ReqFutureSignOut->BrokerBranchID, ReqFutureSignOut->TradeDate, ReqFutureSignOut->TradeTime, ReqFutureSignOut->BankSerial, ReqFutureSignOut->TradingDay, ReqFutureSignOut->PlateSerial, ReqFutureSignOut->LastFragment, ReqFutureSignOut->SessionID, ReqFutureSignOut->InstallID, ReqFutureSignOut->UserID, ReqFutureSignOut->Digest, ReqFutureSignOut->CurrencyID, ReqFutureSignOut->DeviceID, ReqFutureSignOut->BrokerIDByBank, ReqFutureSignOut->OperNo, ReqFutureSignOut->RequestID, ReqFutureSignOut->TID);
	}
}

void WriteRspFutureSignOut(CThostFtdcRspFutureSignOutField* RspFutureSignOut)
{
	if(RspFutureSignOut)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRspFutureSignOutField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], InstallID[%d], UserID[%s], Digest[%s], CurrencyID[%s], DeviceID[%s], BrokerIDByBank[%s], OperNo[%s], RequestID[%d], TID[%d], ErrorID[%d], ErrorMsg[%s]",
			, RspFutureSignOut->TradeCodeRspFutureSignOut->BankID, RspFutureSignOut->BankBranchID, RspFutureSignOut->BrokerID, RspFutureSignOut->BrokerBranchID, RspFutureSignOut->TradeDate, RspFutureSignOut->TradeTime, RspFutureSignOut->BankSerial, RspFutureSignOut->TradingDay, RspFutureSignOut->PlateSerial, RspFutureSignOut->LastFragment, RspFutureSignOut->SessionID, RspFutureSignOut->InstallID, RspFutureSignOut->UserID, RspFutureSignOut->Digest, RspFutureSignOut->CurrencyID, RspFutureSignOut->DeviceID, RspFutureSignOut->BrokerIDByBank, RspFutureSignOut->OperNo, RspFutureSignOut->RequestID, RspFutureSignOut->TID, RspFutureSignOut->ErrorID, RspFutureSignOut->ErrorMsg);
	}
}

void WriteReqQueryTradeResultBySerial(CThostFtdcReqQueryTradeResultBySerialField* ReqQueryTradeResultBySerial)
{
	if(ReqQueryTradeResultBySerial)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqQueryTradeResultBySerialField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], Reference[%d], RefrenceIssureType[%c], RefrenceIssure[%s], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], CurrencyID[%s], TradeAmount[%f], Digest[%s], LongCustomerName[%s]",
			, ReqQueryTradeResultBySerial->TradeCodeReqQueryTradeResultBySerial->BankID, ReqQueryTradeResultBySerial->BankBranchID, ReqQueryTradeResultBySerial->BrokerID, ReqQueryTradeResultBySerial->BrokerBranchID, ReqQueryTradeResultBySerial->TradeDate, ReqQueryTradeResultBySerial->TradeTime, ReqQueryTradeResultBySerial->BankSerial, ReqQueryTradeResultBySerial->TradingDay, ReqQueryTradeResultBySerial->PlateSerial, ReqQueryTradeResultBySerial->LastFragment, ReqQueryTradeResultBySerial->SessionID, ReqQueryTradeResultBySerial->Reference, ReqQueryTradeResultBySerial->RefrenceIssureType, ReqQueryTradeResultBySerial->RefrenceIssure, ReqQueryTradeResultBySerial->CustomerName, ReqQueryTradeResultBySerial->IdCardType, ReqQueryTradeResultBySerial->IdentifiedCardNo, ReqQueryTradeResultBySerial->CustType, ReqQueryTradeResultBySerial->BankAccount, ReqQueryTradeResultBySerial->BankPassWord, ReqQueryTradeResultBySerial->AccountID, ReqQueryTradeResultBySerial->Password, ReqQueryTradeResultBySerial->CurrencyID, ReqQueryTradeResultBySerial->TradeAmount, ReqQueryTradeResultBySerial->Digest, ReqQueryTradeResultBySerial->LongCustomerName);
	}
}

void WriteRspQueryTradeResultBySerial(CThostFtdcRspQueryTradeResultBySerialField* RspQueryTradeResultBySerial)
{
	if(RspQueryTradeResultBySerial)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRspQueryTradeResultBySerialField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], ErrorID[%d], ErrorMsg[%s], Reference[%d], RefrenceIssureType[%c], RefrenceIssure[%s], OriginReturnCode[%s], OriginDescrInfoForReturnCode[%s], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], CurrencyID[%s], TradeAmount[%f], Digest[%s]",
			, RspQueryTradeResultBySerial->TradeCodeRspQueryTradeResultBySerial->BankID, RspQueryTradeResultBySerial->BankBranchID, RspQueryTradeResultBySerial->BrokerID, RspQueryTradeResultBySerial->BrokerBranchID, RspQueryTradeResultBySerial->TradeDate, RspQueryTradeResultBySerial->TradeTime, RspQueryTradeResultBySerial->BankSerial, RspQueryTradeResultBySerial->TradingDay, RspQueryTradeResultBySerial->PlateSerial, RspQueryTradeResultBySerial->LastFragment, RspQueryTradeResultBySerial->SessionID, RspQueryTradeResultBySerial->ErrorID, RspQueryTradeResultBySerial->ErrorMsg, RspQueryTradeResultBySerial->Reference, RspQueryTradeResultBySerial->RefrenceIssureType, RspQueryTradeResultBySerial->RefrenceIssure, RspQueryTradeResultBySerial->OriginReturnCode, RspQueryTradeResultBySerial->OriginDescrInfoForReturnCode, RspQueryTradeResultBySerial->BankAccount, RspQueryTradeResultBySerial->BankPassWord, RspQueryTradeResultBySerial->AccountID, RspQueryTradeResultBySerial->Password, RspQueryTradeResultBySerial->CurrencyID, RspQueryTradeResultBySerial->TradeAmount, RspQueryTradeResultBySerial->Digest);
	}
}

void WriteReqDayEndFileReady(CThostFtdcReqDayEndFileReadyField* ReqDayEndFileReady)
{
	if(ReqDayEndFileReady)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqDayEndFileReadyField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], FileBusinessCode[%c], Digest[%s]",
			, ReqDayEndFileReady->TradeCodeReqDayEndFileReady->BankID, ReqDayEndFileReady->BankBranchID, ReqDayEndFileReady->BrokerID, ReqDayEndFileReady->BrokerBranchID, ReqDayEndFileReady->TradeDate, ReqDayEndFileReady->TradeTime, ReqDayEndFileReady->BankSerial, ReqDayEndFileReady->TradingDay, ReqDayEndFileReady->PlateSerial, ReqDayEndFileReady->LastFragment, ReqDayEndFileReady->SessionID, ReqDayEndFileReady->FileBusinessCode, ReqDayEndFileReady->Digest);
	}
}

void WriteReturnResult(CThostFtdcReturnResultField* ReturnResult)
{
	if(ReturnResult)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReturnResultField: , ReturnCode[%s]DescrInfoForReturnCode[%s]",
			, ReturnResult->ReturnCodeReturnResult->DescrInfoForReturnCode);
	}
}

void WriteVerifyFuturePassword(CThostFtdcVerifyFuturePasswordField* VerifyFuturePassword)
{
	if(VerifyFuturePassword)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcVerifyFuturePasswordField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], AccountID[%s], Password[%s], BankAccount[%s], BankPassWord[%s], InstallID[%d], TID[%d], CurrencyID[%s]",
			, VerifyFuturePassword->TradeCodeVerifyFuturePassword->BankID, VerifyFuturePassword->BankBranchID, VerifyFuturePassword->BrokerID, VerifyFuturePassword->BrokerBranchID, VerifyFuturePassword->TradeDate, VerifyFuturePassword->TradeTime, VerifyFuturePassword->BankSerial, VerifyFuturePassword->TradingDay, VerifyFuturePassword->PlateSerial, VerifyFuturePassword->LastFragment, VerifyFuturePassword->SessionID, VerifyFuturePassword->AccountID, VerifyFuturePassword->Password, VerifyFuturePassword->BankAccount, VerifyFuturePassword->BankPassWord, VerifyFuturePassword->InstallID, VerifyFuturePassword->TID, VerifyFuturePassword->CurrencyID);
	}
}

void WriteVerifyCustInfo(CThostFtdcVerifyCustInfoField* VerifyCustInfo)
{
	if(VerifyCustInfo)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcVerifyCustInfoField: , CustomerName[%s]IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], LongCustomerName[%s]",
			, VerifyCustInfo->CustomerNameVerifyCustInfo->IdCardType, VerifyCustInfo->IdentifiedCardNo, VerifyCustInfo->CustType, VerifyCustInfo->LongCustomerName);
	}
}

void WriteVerifyFuturePasswordAndCustInfo(CThostFtdcVerifyFuturePasswordAndCustInfoField* VerifyFuturePasswordAndCustInfo)
{
	if(VerifyFuturePasswordAndCustInfo)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcVerifyFuturePasswordAndCustInfoField: , CustomerName[%s]IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], AccountID[%s], Password[%s], CurrencyID[%s], LongCustomerName[%s]",
			, VerifyFuturePasswordAndCustInfo->CustomerNameVerifyFuturePasswordAndCustInfo->IdCardType, VerifyFuturePasswordAndCustInfo->IdentifiedCardNo, VerifyFuturePasswordAndCustInfo->CustType, VerifyFuturePasswordAndCustInfo->AccountID, VerifyFuturePasswordAndCustInfo->Password, VerifyFuturePasswordAndCustInfo->CurrencyID, VerifyFuturePasswordAndCustInfo->LongCustomerName);
	}
}

void WriteDepositResultInform(CThostFtdcDepositResultInformField* DepositResultInform)
{
	if(DepositResultInform)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcDepositResultInformField: , DepositSeqNo[%s]BrokerID[%s], InvestorID[%s], Deposit[%f], RequestID[%d], ReturnCode[%s], DescrInfoForReturnCode[%s]",
			, DepositResultInform->DepositSeqNoDepositResultInform->BrokerID, DepositResultInform->InvestorID, DepositResultInform->Deposit, DepositResultInform->RequestID, DepositResultInform->ReturnCode, DepositResultInform->DescrInfoForReturnCode);
	}
}

void WriteReqSyncKey(CThostFtdcReqSyncKeyField* ReqSyncKey)
{
	if(ReqSyncKey)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqSyncKeyField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], InstallID[%d], UserID[%s], Message[%s], DeviceID[%s], BrokerIDByBank[%s], OperNo[%s], RequestID[%d], TID[%d]",
			, ReqSyncKey->TradeCodeReqSyncKey->BankID, ReqSyncKey->BankBranchID, ReqSyncKey->BrokerID, ReqSyncKey->BrokerBranchID, ReqSyncKey->TradeDate, ReqSyncKey->TradeTime, ReqSyncKey->BankSerial, ReqSyncKey->TradingDay, ReqSyncKey->PlateSerial, ReqSyncKey->LastFragment, ReqSyncKey->SessionID, ReqSyncKey->InstallID, ReqSyncKey->UserID, ReqSyncKey->Message, ReqSyncKey->DeviceID, ReqSyncKey->BrokerIDByBank, ReqSyncKey->OperNo, ReqSyncKey->RequestID, ReqSyncKey->TID);
	}
}

void WriteRspSyncKey(CThostFtdcRspSyncKeyField* RspSyncKey)
{
	if(RspSyncKey)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRspSyncKeyField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], InstallID[%d], UserID[%s], Message[%s], DeviceID[%s], BrokerIDByBank[%s], OperNo[%s], RequestID[%d], TID[%d], ErrorID[%d], ErrorMsg[%s]",
			, RspSyncKey->TradeCodeRspSyncKey->BankID, RspSyncKey->BankBranchID, RspSyncKey->BrokerID, RspSyncKey->BrokerBranchID, RspSyncKey->TradeDate, RspSyncKey->TradeTime, RspSyncKey->BankSerial, RspSyncKey->TradingDay, RspSyncKey->PlateSerial, RspSyncKey->LastFragment, RspSyncKey->SessionID, RspSyncKey->InstallID, RspSyncKey->UserID, RspSyncKey->Message, RspSyncKey->DeviceID, RspSyncKey->BrokerIDByBank, RspSyncKey->OperNo, RspSyncKey->RequestID, RspSyncKey->TID, RspSyncKey->ErrorID, RspSyncKey->ErrorMsg);
	}
}

void WriteNotifyQueryAccount(CThostFtdcNotifyQueryAccountField* NotifyQueryAccount)
{
	if(NotifyQueryAccount)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcNotifyQueryAccountField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], FutureSerial[%d], InstallID[%d], UserID[%s], VerifyCertNoFlag[%c], CurrencyID[%s], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], RequestID[%d], TID[%d], BankUseAmount[%f], BankFetchAmount[%f], ErrorID[%d], ErrorMsg[%s], LongCustomerName[%s]",
			, NotifyQueryAccount->TradeCodeNotifyQueryAccount->BankID, NotifyQueryAccount->BankBranchID, NotifyQueryAccount->BrokerID, NotifyQueryAccount->BrokerBranchID, NotifyQueryAccount->TradeDate, NotifyQueryAccount->TradeTime, NotifyQueryAccount->BankSerial, NotifyQueryAccount->TradingDay, NotifyQueryAccount->PlateSerial, NotifyQueryAccount->LastFragment, NotifyQueryAccount->SessionID, NotifyQueryAccount->CustomerName, NotifyQueryAccount->IdCardType, NotifyQueryAccount->IdentifiedCardNo, NotifyQueryAccount->CustType, NotifyQueryAccount->BankAccount, NotifyQueryAccount->BankPassWord, NotifyQueryAccount->AccountID, NotifyQueryAccount->Password, NotifyQueryAccount->FutureSerial, NotifyQueryAccount->InstallID, NotifyQueryAccount->UserID, NotifyQueryAccount->VerifyCertNoFlag, NotifyQueryAccount->CurrencyID, NotifyQueryAccount->Digest, NotifyQueryAccount->BankAccType, NotifyQueryAccount->DeviceID, NotifyQueryAccount->BankSecuAccType, NotifyQueryAccount->BrokerIDByBank, NotifyQueryAccount->BankSecuAcc, NotifyQueryAccount->BankPwdFlag, NotifyQueryAccount->SecuPwdFlag, NotifyQueryAccount->OperNo, NotifyQueryAccount->RequestID, NotifyQueryAccount->TID, NotifyQueryAccount->BankUseAmount, NotifyQueryAccount->BankFetchAmount, NotifyQueryAccount->ErrorID, NotifyQueryAccount->ErrorMsg, NotifyQueryAccount->LongCustomerName);
	}
}

void WriteTransferSerial(CThostFtdcTransferSerialField* TransferSerial)
{
	if(TransferSerial)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTransferSerialField: , PlateSerial[%d]TradeDate[%s], TradingDay[%s], TradeTime[%s], TradeCode[%s], SessionID[%d], BankID[%s], BankBranchID[%s], BankAccType[%c], BankAccount[%s], BankSerial[%s], BrokerID[%s], BrokerBranchID[%s], FutureAccType[%c], AccountID[%s], InvestorID[%s], FutureSerial[%d], IdCardType[%c], IdentifiedCardNo[%s], CurrencyID[%s], TradeAmount[%f], CustFee[%f], BrokerFee[%f], AvailabilityFlag[%c], OperatorCode[%s], BankNewAccount[%s], ErrorID[%d], ErrorMsg[%s]",
			, TransferSerial->PlateSerialTransferSerial->TradeDate, TransferSerial->TradingDay, TransferSerial->TradeTime, TransferSerial->TradeCode, TransferSerial->SessionID, TransferSerial->BankID, TransferSerial->BankBranchID, TransferSerial->BankAccType, TransferSerial->BankAccount, TransferSerial->BankSerial, TransferSerial->BrokerID, TransferSerial->BrokerBranchID, TransferSerial->FutureAccType, TransferSerial->AccountID, TransferSerial->InvestorID, TransferSerial->FutureSerial, TransferSerial->IdCardType, TransferSerial->IdentifiedCardNo, TransferSerial->CurrencyID, TransferSerial->TradeAmount, TransferSerial->CustFee, TransferSerial->BrokerFee, TransferSerial->AvailabilityFlag, TransferSerial->OperatorCode, TransferSerial->BankNewAccount, TransferSerial->ErrorID, TransferSerial->ErrorMsg);
	}
}

void WriteQryTransferSerial(CThostFtdcQryTransferSerialField* QryTransferSerial)
{
	if(QryTransferSerial)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryTransferSerialField: , BrokerID[%s]AccountID[%s], BankID[%s], CurrencyID[%s]",
			, QryTransferSerial->BrokerIDQryTransferSerial->AccountID, QryTransferSerial->BankID, QryTransferSerial->CurrencyID);
	}
}

void WriteNotifyFutureSignIn(CThostFtdcNotifyFutureSignInField* NotifyFutureSignIn)
{
	if(NotifyFutureSignIn)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcNotifyFutureSignInField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], InstallID[%d], UserID[%s], Digest[%s], CurrencyID[%s], DeviceID[%s], BrokerIDByBank[%s], OperNo[%s], RequestID[%d], TID[%d], ErrorID[%d], ErrorMsg[%s], PinKey[%s], MacKey[%s]",
			, NotifyFutureSignIn->TradeCodeNotifyFutureSignIn->BankID, NotifyFutureSignIn->BankBranchID, NotifyFutureSignIn->BrokerID, NotifyFutureSignIn->BrokerBranchID, NotifyFutureSignIn->TradeDate, NotifyFutureSignIn->TradeTime, NotifyFutureSignIn->BankSerial, NotifyFutureSignIn->TradingDay, NotifyFutureSignIn->PlateSerial, NotifyFutureSignIn->LastFragment, NotifyFutureSignIn->SessionID, NotifyFutureSignIn->InstallID, NotifyFutureSignIn->UserID, NotifyFutureSignIn->Digest, NotifyFutureSignIn->CurrencyID, NotifyFutureSignIn->DeviceID, NotifyFutureSignIn->BrokerIDByBank, NotifyFutureSignIn->OperNo, NotifyFutureSignIn->RequestID, NotifyFutureSignIn->TID, NotifyFutureSignIn->ErrorID, NotifyFutureSignIn->ErrorMsg, NotifyFutureSignIn->PinKey, NotifyFutureSignIn->MacKey);
	}
}

void WriteNotifyFutureSignOut(CThostFtdcNotifyFutureSignOutField* NotifyFutureSignOut)
{
	if(NotifyFutureSignOut)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcNotifyFutureSignOutField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], InstallID[%d], UserID[%s], Digest[%s], CurrencyID[%s], DeviceID[%s], BrokerIDByBank[%s], OperNo[%s], RequestID[%d], TID[%d], ErrorID[%d], ErrorMsg[%s]",
			, NotifyFutureSignOut->TradeCodeNotifyFutureSignOut->BankID, NotifyFutureSignOut->BankBranchID, NotifyFutureSignOut->BrokerID, NotifyFutureSignOut->BrokerBranchID, NotifyFutureSignOut->TradeDate, NotifyFutureSignOut->TradeTime, NotifyFutureSignOut->BankSerial, NotifyFutureSignOut->TradingDay, NotifyFutureSignOut->PlateSerial, NotifyFutureSignOut->LastFragment, NotifyFutureSignOut->SessionID, NotifyFutureSignOut->InstallID, NotifyFutureSignOut->UserID, NotifyFutureSignOut->Digest, NotifyFutureSignOut->CurrencyID, NotifyFutureSignOut->DeviceID, NotifyFutureSignOut->BrokerIDByBank, NotifyFutureSignOut->OperNo, NotifyFutureSignOut->RequestID, NotifyFutureSignOut->TID, NotifyFutureSignOut->ErrorID, NotifyFutureSignOut->ErrorMsg);
	}
}

void WriteNotifySyncKey(CThostFtdcNotifySyncKeyField* NotifySyncKey)
{
	if(NotifySyncKey)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcNotifySyncKeyField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], InstallID[%d], UserID[%s], Message[%s], DeviceID[%s], BrokerIDByBank[%s], OperNo[%s], RequestID[%d], TID[%d], ErrorID[%d], ErrorMsg[%s]",
			, NotifySyncKey->TradeCodeNotifySyncKey->BankID, NotifySyncKey->BankBranchID, NotifySyncKey->BrokerID, NotifySyncKey->BrokerBranchID, NotifySyncKey->TradeDate, NotifySyncKey->TradeTime, NotifySyncKey->BankSerial, NotifySyncKey->TradingDay, NotifySyncKey->PlateSerial, NotifySyncKey->LastFragment, NotifySyncKey->SessionID, NotifySyncKey->InstallID, NotifySyncKey->UserID, NotifySyncKey->Message, NotifySyncKey->DeviceID, NotifySyncKey->BrokerIDByBank, NotifySyncKey->OperNo, NotifySyncKey->RequestID, NotifySyncKey->TID, NotifySyncKey->ErrorID, NotifySyncKey->ErrorMsg);
	}
}

void WriteQryAccountregister(CThostFtdcQryAccountregisterField* QryAccountregister)
{
	if(QryAccountregister)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryAccountregisterField: , BrokerID[%s]AccountID[%s], BankID[%s], BankBranchID[%s], CurrencyID[%s]",
			, QryAccountregister->BrokerIDQryAccountregister->AccountID, QryAccountregister->BankID, QryAccountregister->BankBranchID, QryAccountregister->CurrencyID);
	}
}

void WriteAccountregister(CThostFtdcAccountregisterField* Accountregister)
{
	if(Accountregister)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcAccountregisterField: , TradeDay[%s]BankID[%s], BankBranchID[%s], BankAccount[%s], BrokerID[%s], BrokerBranchID[%s], AccountID[%s], IdCardType[%c], IdentifiedCardNo[%s], CustomerName[%s], CurrencyID[%s], OpenOrDestroy[%c], RegDate[%s], OutDate[%s], TID[%d], CustType[%c], BankAccType[%c], LongCustomerName[%s]",
			, Accountregister->TradeDayAccountregister->BankID, Accountregister->BankBranchID, Accountregister->BankAccount, Accountregister->BrokerID, Accountregister->BrokerBranchID, Accountregister->AccountID, Accountregister->IdCardType, Accountregister->IdentifiedCardNo, Accountregister->CustomerName, Accountregister->CurrencyID, Accountregister->OpenOrDestroy, Accountregister->RegDate, Accountregister->OutDate, Accountregister->TID, Accountregister->CustType, Accountregister->BankAccType, Accountregister->LongCustomerName);
	}
}

void WriteOpenAccount(CThostFtdcOpenAccountField* OpenAccount)
{
	if(OpenAccount)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcOpenAccountField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], Gender[%c], CountryCode[%s], CustType[%c], Address[%s], ZipCode[%s], Telephone[%s], MobilePhone[%s], Fax[%s], EMail[%s], MoneyAccountStatus[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], InstallID[%d], VerifyCertNoFlag[%c], CurrencyID[%s], CashExchangeCode[%c], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], TID[%d], UserID[%s], ErrorID[%d], ErrorMsg[%s], LongCustomerName[%s]",
			, OpenAccount->TradeCodeOpenAccount->BankID, OpenAccount->BankBranchID, OpenAccount->BrokerID, OpenAccount->BrokerBranchID, OpenAccount->TradeDate, OpenAccount->TradeTime, OpenAccount->BankSerial, OpenAccount->TradingDay, OpenAccount->PlateSerial, OpenAccount->LastFragment, OpenAccount->SessionID, OpenAccount->CustomerName, OpenAccount->IdCardType, OpenAccount->IdentifiedCardNo, OpenAccount->Gender, OpenAccount->CountryCode, OpenAccount->CustType, OpenAccount->Address, OpenAccount->ZipCode, OpenAccount->Telephone, OpenAccount->MobilePhone, OpenAccount->Fax, OpenAccount->EMail, OpenAccount->MoneyAccountStatus, OpenAccount->BankAccount, OpenAccount->BankPassWord, OpenAccount->AccountID, OpenAccount->Password, OpenAccount->InstallID, OpenAccount->VerifyCertNoFlag, OpenAccount->CurrencyID, OpenAccount->CashExchangeCode, OpenAccount->Digest, OpenAccount->BankAccType, OpenAccount->DeviceID, OpenAccount->BankSecuAccType, OpenAccount->BrokerIDByBank, OpenAccount->BankSecuAcc, OpenAccount->BankPwdFlag, OpenAccount->SecuPwdFlag, OpenAccount->OperNo, OpenAccount->TID, OpenAccount->UserID, OpenAccount->ErrorID, OpenAccount->ErrorMsg, OpenAccount->LongCustomerName);
	}
}

void WriteCancelAccount(CThostFtdcCancelAccountField* CancelAccount)
{
	if(CancelAccount)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcCancelAccountField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], Gender[%c], CountryCode[%s], CustType[%c], Address[%s], ZipCode[%s], Telephone[%s], MobilePhone[%s], Fax[%s], EMail[%s], MoneyAccountStatus[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], InstallID[%d], VerifyCertNoFlag[%c], CurrencyID[%s], CashExchangeCode[%c], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], TID[%d], UserID[%s], ErrorID[%d], ErrorMsg[%s], LongCustomerName[%s]",
			, CancelAccount->TradeCodeCancelAccount->BankID, CancelAccount->BankBranchID, CancelAccount->BrokerID, CancelAccount->BrokerBranchID, CancelAccount->TradeDate, CancelAccount->TradeTime, CancelAccount->BankSerial, CancelAccount->TradingDay, CancelAccount->PlateSerial, CancelAccount->LastFragment, CancelAccount->SessionID, CancelAccount->CustomerName, CancelAccount->IdCardType, CancelAccount->IdentifiedCardNo, CancelAccount->Gender, CancelAccount->CountryCode, CancelAccount->CustType, CancelAccount->Address, CancelAccount->ZipCode, CancelAccount->Telephone, CancelAccount->MobilePhone, CancelAccount->Fax, CancelAccount->EMail, CancelAccount->MoneyAccountStatus, CancelAccount->BankAccount, CancelAccount->BankPassWord, CancelAccount->AccountID, CancelAccount->Password, CancelAccount->InstallID, CancelAccount->VerifyCertNoFlag, CancelAccount->CurrencyID, CancelAccount->CashExchangeCode, CancelAccount->Digest, CancelAccount->BankAccType, CancelAccount->DeviceID, CancelAccount->BankSecuAccType, CancelAccount->BrokerIDByBank, CancelAccount->BankSecuAcc, CancelAccount->BankPwdFlag, CancelAccount->SecuPwdFlag, CancelAccount->OperNo, CancelAccount->TID, CancelAccount->UserID, CancelAccount->ErrorID, CancelAccount->ErrorMsg, CancelAccount->LongCustomerName);
	}
}

void WriteChangeAccount(CThostFtdcChangeAccountField* ChangeAccount)
{
	if(ChangeAccount)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcChangeAccountField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], Gender[%c], CountryCode[%s], CustType[%c], Address[%s], ZipCode[%s], Telephone[%s], MobilePhone[%s], Fax[%s], EMail[%s], MoneyAccountStatus[%c], BankAccount[%s], BankPassWord[%s], NewBankAccount[%s], NewBankPassWord[%s], AccountID[%s], Password[%s], BankAccType[%c], InstallID[%d], VerifyCertNoFlag[%c], CurrencyID[%s], BrokerIDByBank[%s], BankPwdFlag[%c], SecuPwdFlag[%c], TID[%d], Digest[%s], ErrorID[%d], ErrorMsg[%s], LongCustomerName[%s]",
			, ChangeAccount->TradeCodeChangeAccount->BankID, ChangeAccount->BankBranchID, ChangeAccount->BrokerID, ChangeAccount->BrokerBranchID, ChangeAccount->TradeDate, ChangeAccount->TradeTime, ChangeAccount->BankSerial, ChangeAccount->TradingDay, ChangeAccount->PlateSerial, ChangeAccount->LastFragment, ChangeAccount->SessionID, ChangeAccount->CustomerName, ChangeAccount->IdCardType, ChangeAccount->IdentifiedCardNo, ChangeAccount->Gender, ChangeAccount->CountryCode, ChangeAccount->CustType, ChangeAccount->Address, ChangeAccount->ZipCode, ChangeAccount->Telephone, ChangeAccount->MobilePhone, ChangeAccount->Fax, ChangeAccount->EMail, ChangeAccount->MoneyAccountStatus, ChangeAccount->BankAccount, ChangeAccount->BankPassWord, ChangeAccount->NewBankAccount, ChangeAccount->NewBankPassWord, ChangeAccount->AccountID, ChangeAccount->Password, ChangeAccount->BankAccType, ChangeAccount->InstallID, ChangeAccount->VerifyCertNoFlag, ChangeAccount->CurrencyID, ChangeAccount->BrokerIDByBank, ChangeAccount->BankPwdFlag, ChangeAccount->SecuPwdFlag, ChangeAccount->TID, ChangeAccount->Digest, ChangeAccount->ErrorID, ChangeAccount->ErrorMsg, ChangeAccount->LongCustomerName);
	}
}

void WriteSecAgentACIDMap(CThostFtdcSecAgentACIDMapField* SecAgentACIDMap)
{
	if(SecAgentACIDMap)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSecAgentACIDMapField: , BrokerID[%s]UserID[%s], AccountID[%s], CurrencyID[%s], BrokerSecAgentID[%s]",
			, SecAgentACIDMap->BrokerIDSecAgentACIDMap->UserID, SecAgentACIDMap->AccountID, SecAgentACIDMap->CurrencyID, SecAgentACIDMap->BrokerSecAgentID);
	}
}

void WriteQrySecAgentACIDMap(CThostFtdcQrySecAgentACIDMapField* QrySecAgentACIDMap)
{
	if(QrySecAgentACIDMap)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQrySecAgentACIDMapField: , BrokerID[%s]UserID[%s], AccountID[%s], CurrencyID[%s]",
			, QrySecAgentACIDMap->BrokerIDQrySecAgentACIDMap->UserID, QrySecAgentACIDMap->AccountID, QrySecAgentACIDMap->CurrencyID);
	}
}

void WriteUserRightsAssign(CThostFtdcUserRightsAssignField* UserRightsAssign)
{
	if(UserRightsAssign)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcUserRightsAssignField: , BrokerID[%s]UserID[%s], DRIdentityID[%d]",
			, UserRightsAssign->BrokerIDUserRightsAssign->UserID, UserRightsAssign->DRIdentityID);
	}
}

void WriteBrokerUserRightAssign(CThostFtdcBrokerUserRightAssignField* BrokerUserRightAssign)
{
	if(BrokerUserRightAssign)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcBrokerUserRightAssignField: , BrokerID[%s]DRIdentityID[%d], Tradeable[%d]",
			, BrokerUserRightAssign->BrokerIDBrokerUserRightAssign->DRIdentityID, BrokerUserRightAssign->Tradeable);
	}
}

void WriteDRTransfer(CThostFtdcDRTransferField* DRTransfer)
{
	if(DRTransfer)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcDRTransferField: , OrigDRIdentityID[%d]DestDRIdentityID[%d], OrigBrokerID[%s], DestBrokerID[%s]",
			, DRTransfer->OrigDRIdentityIDDRTransfer->DestDRIdentityID, DRTransfer->OrigBrokerID, DRTransfer->DestBrokerID);
	}
}

void WriteFensUserInfo(CThostFtdcFensUserInfoField* FensUserInfo)
{
	if(FensUserInfo)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcFensUserInfoField: , BrokerID[%s]UserID[%s], LoginMode[%c]",
			, FensUserInfo->BrokerIDFensUserInfo->UserID, FensUserInfo->LoginMode);
	}
}

void WriteCurrTransferIdentity(CThostFtdcCurrTransferIdentityField* CurrTransferIdentity)
{
	if(CurrTransferIdentity)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcCurrTransferIdentityField: , IdentityID[%d]",
			, CurrTransferIdentity->IdentityID);
	}
}

void WriteLoginForbiddenUser(CThostFtdcLoginForbiddenUserField* LoginForbiddenUser)
{
	if(LoginForbiddenUser)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcLoginForbiddenUserField: , BrokerID[%s]UserID[%s], reserve1[%s], IPAddress[%s]",
			, LoginForbiddenUser->BrokerIDLoginForbiddenUser->UserID, LoginForbiddenUser->reserve1, LoginForbiddenUser->IPAddress);
	}
}

void WriteQryLoginForbiddenUser(CThostFtdcQryLoginForbiddenUserField* QryLoginForbiddenUser)
{
	if(QryLoginForbiddenUser)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryLoginForbiddenUserField: , BrokerID[%s]UserID[%s]",
			, QryLoginForbiddenUser->BrokerIDQryLoginForbiddenUser->UserID);
	}
}

void WriteTradingAccountReserve(CThostFtdcTradingAccountReserveField* TradingAccountReserve)
{
	if(TradingAccountReserve)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcTradingAccountReserveField: , BrokerID[%s]AccountID[%s], Reserve[%f], CurrencyID[%s]",
			, TradingAccountReserve->BrokerIDTradingAccountReserve->AccountID, TradingAccountReserve->Reserve, TradingAccountReserve->CurrencyID);
	}
}

void WriteQryLoginForbiddenIP(CThostFtdcQryLoginForbiddenIPField* QryLoginForbiddenIP)
{
	if(QryLoginForbiddenIP)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryLoginForbiddenIPField: , reserve1[%s]IPAddress[%s]",
			, QryLoginForbiddenIP->reserve1QryLoginForbiddenIP->IPAddress);
	}
}

void WriteQryIPList(CThostFtdcQryIPListField* QryIPList)
{
	if(QryIPList)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryIPListField: , reserve1[%s]IPAddress[%s]",
			, QryIPList->reserve1QryIPList->IPAddress);
	}
}

void WriteQryUserRightsAssign(CThostFtdcQryUserRightsAssignField* QryUserRightsAssign)
{
	if(QryUserRightsAssign)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryUserRightsAssignField: , BrokerID[%s]UserID[%s]",
			, QryUserRightsAssign->BrokerIDQryUserRightsAssign->UserID);
	}
}

void WriteReserveOpenAccountConfirm(CThostFtdcReserveOpenAccountConfirmField* ReserveOpenAccountConfirm)
{
	if(ReserveOpenAccountConfirm)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReserveOpenAccountConfirmField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], Gender[%c], CountryCode[%s], CustType[%c], Address[%s], ZipCode[%s], Telephone[%s], MobilePhone[%s], Fax[%s], EMail[%s], MoneyAccountStatus[%c], BankAccount[%s], BankPassWord[%s], InstallID[%d], VerifyCertNoFlag[%c], CurrencyID[%s], Digest[%s], BankAccType[%c], BrokerIDByBank[%s], TID[%d], AccountID[%s], Password[%s], BankReserveOpenSeq[%s], BookDate[%s], BookPsw[%s], ErrorID[%d], ErrorMsg[%s]",
			, ReserveOpenAccountConfirm->TradeCodeReserveOpenAccountConfirm->BankID, ReserveOpenAccountConfirm->BankBranchID, ReserveOpenAccountConfirm->BrokerID, ReserveOpenAccountConfirm->BrokerBranchID, ReserveOpenAccountConfirm->TradeDate, ReserveOpenAccountConfirm->TradeTime, ReserveOpenAccountConfirm->BankSerial, ReserveOpenAccountConfirm->TradingDay, ReserveOpenAccountConfirm->PlateSerial, ReserveOpenAccountConfirm->LastFragment, ReserveOpenAccountConfirm->SessionID, ReserveOpenAccountConfirm->CustomerName, ReserveOpenAccountConfirm->IdCardType, ReserveOpenAccountConfirm->IdentifiedCardNo, ReserveOpenAccountConfirm->Gender, ReserveOpenAccountConfirm->CountryCode, ReserveOpenAccountConfirm->CustType, ReserveOpenAccountConfirm->Address, ReserveOpenAccountConfirm->ZipCode, ReserveOpenAccountConfirm->Telephone, ReserveOpenAccountConfirm->MobilePhone, ReserveOpenAccountConfirm->Fax, ReserveOpenAccountConfirm->EMail, ReserveOpenAccountConfirm->MoneyAccountStatus, ReserveOpenAccountConfirm->BankAccount, ReserveOpenAccountConfirm->BankPassWord, ReserveOpenAccountConfirm->InstallID, ReserveOpenAccountConfirm->VerifyCertNoFlag, ReserveOpenAccountConfirm->CurrencyID, ReserveOpenAccountConfirm->Digest, ReserveOpenAccountConfirm->BankAccType, ReserveOpenAccountConfirm->BrokerIDByBank, ReserveOpenAccountConfirm->TID, ReserveOpenAccountConfirm->AccountID, ReserveOpenAccountConfirm->Password, ReserveOpenAccountConfirm->BankReserveOpenSeq, ReserveOpenAccountConfirm->BookDate, ReserveOpenAccountConfirm->BookPsw, ReserveOpenAccountConfirm->ErrorID, ReserveOpenAccountConfirm->ErrorMsg);
	}
}

void WriteReserveOpenAccount(CThostFtdcReserveOpenAccountField* ReserveOpenAccount)
{
	if(ReserveOpenAccount)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReserveOpenAccountField: , TradeCode[%s]BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], Gender[%c], CountryCode[%s], CustType[%c], Address[%s], ZipCode[%s], Telephone[%s], MobilePhone[%s], Fax[%s], EMail[%s], MoneyAccountStatus[%c], BankAccount[%s], BankPassWord[%s], InstallID[%d], VerifyCertNoFlag[%c], CurrencyID[%s], Digest[%s], BankAccType[%c], BrokerIDByBank[%s], TID[%d], ReserveOpenAccStas[%c], ErrorID[%d], ErrorMsg[%s]",
			, ReserveOpenAccount->TradeCodeReserveOpenAccount->BankID, ReserveOpenAccount->BankBranchID, ReserveOpenAccount->BrokerID, ReserveOpenAccount->BrokerBranchID, ReserveOpenAccount->TradeDate, ReserveOpenAccount->TradeTime, ReserveOpenAccount->BankSerial, ReserveOpenAccount->TradingDay, ReserveOpenAccount->PlateSerial, ReserveOpenAccount->LastFragment, ReserveOpenAccount->SessionID, ReserveOpenAccount->CustomerName, ReserveOpenAccount->IdCardType, ReserveOpenAccount->IdentifiedCardNo, ReserveOpenAccount->Gender, ReserveOpenAccount->CountryCode, ReserveOpenAccount->CustType, ReserveOpenAccount->Address, ReserveOpenAccount->ZipCode, ReserveOpenAccount->Telephone, ReserveOpenAccount->MobilePhone, ReserveOpenAccount->Fax, ReserveOpenAccount->EMail, ReserveOpenAccount->MoneyAccountStatus, ReserveOpenAccount->BankAccount, ReserveOpenAccount->BankPassWord, ReserveOpenAccount->InstallID, ReserveOpenAccount->VerifyCertNoFlag, ReserveOpenAccount->CurrencyID, ReserveOpenAccount->Digest, ReserveOpenAccount->BankAccType, ReserveOpenAccount->BrokerIDByBank, ReserveOpenAccount->TID, ReserveOpenAccount->ReserveOpenAccStas, ReserveOpenAccount->ErrorID, ReserveOpenAccount->ErrorMsg);
	}
}

void WriteAccountProperty(CThostFtdcAccountPropertyField* AccountProperty)
{
	if(AccountProperty)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcAccountPropertyField: , BrokerID[%s]AccountID[%s], BankID[%s], BankAccount[%s], OpenName[%s], OpenBank[%s], IsActive[%d], AccountSourceType[%c], OpenDate[%s], CancelDate[%s], OperatorID[%s], OperateDate[%s], OperateTime[%s], CurrencyID[%s]",
			, AccountProperty->BrokerIDAccountProperty->AccountID, AccountProperty->BankID, AccountProperty->BankAccount, AccountProperty->OpenName, AccountProperty->OpenBank, AccountProperty->IsActive, AccountProperty->AccountSourceType, AccountProperty->OpenDate, AccountProperty->CancelDate, AccountProperty->OperatorID, AccountProperty->OperateDate, AccountProperty->OperateTime, AccountProperty->CurrencyID);
	}
}

void WriteQryCurrDRIdentity(CThostFtdcQryCurrDRIdentityField* QryCurrDRIdentity)
{
	if(QryCurrDRIdentity)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryCurrDRIdentityField: , DRIdentityID[%d]",
			, QryCurrDRIdentity->DRIdentityID);
	}
}

void WriteCurrDRIdentity(CThostFtdcCurrDRIdentityField* CurrDRIdentity)
{
	if(CurrDRIdentity)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcCurrDRIdentityField: , DRIdentityID[%d]",
			, CurrDRIdentity->DRIdentityID);
	}
}

void WriteQrySecAgentCheckMode(CThostFtdcQrySecAgentCheckModeField* QrySecAgentCheckMode)
{
	if(QrySecAgentCheckMode)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQrySecAgentCheckModeField: , BrokerID[%s]InvestorID[%s]",
			, QrySecAgentCheckMode->BrokerIDQrySecAgentCheckMode->InvestorID);
	}
}

void WriteQrySecAgentTradeInfo(CThostFtdcQrySecAgentTradeInfoField* QrySecAgentTradeInfo)
{
	if(QrySecAgentTradeInfo)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQrySecAgentTradeInfoField: , BrokerID[%s]BrokerSecAgentID[%s]",
			, QrySecAgentTradeInfo->BrokerIDQrySecAgentTradeInfo->BrokerSecAgentID);
	}
}

void WriteReqUserAuthMethod(CThostFtdcReqUserAuthMethodField* ReqUserAuthMethod)
{
	if(ReqUserAuthMethod)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqUserAuthMethodField: , TradingDay[%s]BrokerID[%s], UserID[%s]",
			, ReqUserAuthMethod->TradingDayReqUserAuthMethod->BrokerID, ReqUserAuthMethod->UserID);
	}
}

void WriteRspUserAuthMethod(CThostFtdcRspUserAuthMethodField* RspUserAuthMethod)
{
	if(RspUserAuthMethod)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRspUserAuthMethodField: , UsableAuthMethod[%d]",
			, RspUserAuthMethod->UsableAuthMethod);
	}
}

void WriteReqGenUserCaptcha(CThostFtdcReqGenUserCaptchaField* ReqGenUserCaptcha)
{
	if(ReqGenUserCaptcha)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqGenUserCaptchaField: , TradingDay[%s]BrokerID[%s], UserID[%s]",
			, ReqGenUserCaptcha->TradingDayReqGenUserCaptcha->BrokerID, ReqGenUserCaptcha->UserID);
	}
}

void WriteRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField* RspGenUserCaptcha)
{
	if(RspGenUserCaptcha)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRspGenUserCaptchaField: , BrokerID[%s]UserID[%s], CaptchaInfoLen[%d], CaptchaInfo[%s]",
			, RspGenUserCaptcha->BrokerIDRspGenUserCaptcha->UserID, RspGenUserCaptcha->CaptchaInfoLen, RspGenUserCaptcha->CaptchaInfo);
	}
}

void WriteReqGenUserText(CThostFtdcReqGenUserTextField* ReqGenUserText)
{
	if(ReqGenUserText)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqGenUserTextField: , TradingDay[%s]BrokerID[%s], UserID[%s]",
			, ReqGenUserText->TradingDayReqGenUserText->BrokerID, ReqGenUserText->UserID);
	}
}

void WriteRspGenUserText(CThostFtdcRspGenUserTextField* RspGenUserText)
{
	if(RspGenUserText)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRspGenUserTextField: , UserTextSeq[%d]",
			, RspGenUserText->UserTextSeq);
	}
}

void WriteReqUserLoginWithCaptcha(CThostFtdcReqUserLoginWithCaptchaField* ReqUserLoginWithCaptcha)
{
	if(ReqUserLoginWithCaptcha)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqUserLoginWithCaptchaField: , TradingDay[%s]BrokerID[%s], UserID[%s], Password[%s], UserProductInfo[%s], InterfaceProductInfo[%s], ProtocolInfo[%s], MacAddress[%s], reserve1[%s], LoginRemark[%s], Captcha[%s], ClientIPPort[%d], ClientIPAddress[%s]",
			, ReqUserLoginWithCaptcha->TradingDayReqUserLoginWithCaptcha->BrokerID, ReqUserLoginWithCaptcha->UserID, ReqUserLoginWithCaptcha->Password, ReqUserLoginWithCaptcha->UserProductInfo, ReqUserLoginWithCaptcha->InterfaceProductInfo, ReqUserLoginWithCaptcha->ProtocolInfo, ReqUserLoginWithCaptcha->MacAddress, ReqUserLoginWithCaptcha->reserve1, ReqUserLoginWithCaptcha->LoginRemark, ReqUserLoginWithCaptcha->Captcha, ReqUserLoginWithCaptcha->ClientIPPort, ReqUserLoginWithCaptcha->ClientIPAddress);
	}
}

void WriteReqUserLoginWithText(CThostFtdcReqUserLoginWithTextField* ReqUserLoginWithText)
{
	if(ReqUserLoginWithText)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqUserLoginWithTextField: , TradingDay[%s]BrokerID[%s], UserID[%s], Password[%s], UserProductInfo[%s], InterfaceProductInfo[%s], ProtocolInfo[%s], MacAddress[%s], reserve1[%s], LoginRemark[%s], Text[%s], ClientIPPort[%d], ClientIPAddress[%s]",
			, ReqUserLoginWithText->TradingDayReqUserLoginWithText->BrokerID, ReqUserLoginWithText->UserID, ReqUserLoginWithText->Password, ReqUserLoginWithText->UserProductInfo, ReqUserLoginWithText->InterfaceProductInfo, ReqUserLoginWithText->ProtocolInfo, ReqUserLoginWithText->MacAddress, ReqUserLoginWithText->reserve1, ReqUserLoginWithText->LoginRemark, ReqUserLoginWithText->Text, ReqUserLoginWithText->ClientIPPort, ReqUserLoginWithText->ClientIPAddress);
	}
}

void WriteReqUserLoginWithOTP(CThostFtdcReqUserLoginWithOTPField* ReqUserLoginWithOTP)
{
	if(ReqUserLoginWithOTP)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqUserLoginWithOTPField: , TradingDay[%s]BrokerID[%s], UserID[%s], Password[%s], UserProductInfo[%s], InterfaceProductInfo[%s], ProtocolInfo[%s], MacAddress[%s], reserve1[%s], LoginRemark[%s], OTPPassword[%s], ClientIPPort[%d], ClientIPAddress[%s]",
			, ReqUserLoginWithOTP->TradingDayReqUserLoginWithOTP->BrokerID, ReqUserLoginWithOTP->UserID, ReqUserLoginWithOTP->Password, ReqUserLoginWithOTP->UserProductInfo, ReqUserLoginWithOTP->InterfaceProductInfo, ReqUserLoginWithOTP->ProtocolInfo, ReqUserLoginWithOTP->MacAddress, ReqUserLoginWithOTP->reserve1, ReqUserLoginWithOTP->LoginRemark, ReqUserLoginWithOTP->OTPPassword, ReqUserLoginWithOTP->ClientIPPort, ReqUserLoginWithOTP->ClientIPAddress);
	}
}

void WriteReqApiHandshake(CThostFtdcReqApiHandshakeField* ReqApiHandshake)
{
	if(ReqApiHandshake)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqApiHandshakeField: , CryptoKeyVersion[%s]",
			, ReqApiHandshake->CryptoKeyVersion);
	}
}

void WriteRspApiHandshake(CThostFtdcRspApiHandshakeField* RspApiHandshake)
{
	if(RspApiHandshake)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRspApiHandshakeField: , FrontHandshakeDataLen[%d]FrontHandshakeData[%s], IsApiAuthEnabled[%d]",
			, RspApiHandshake->FrontHandshakeDataLenRspApiHandshake->FrontHandshakeData, RspApiHandshake->IsApiAuthEnabled);
	}
}

void WriteReqVerifyApiKey(CThostFtdcReqVerifyApiKeyField* ReqVerifyApiKey)
{
	if(ReqVerifyApiKey)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcReqVerifyApiKeyField: , ApiHandshakeDataLen[%d]ApiHandshakeData[%s]",
			, ReqVerifyApiKey->ApiHandshakeDataLenReqVerifyApiKey->ApiHandshakeData);
	}
}

void WriteDepartmentUser(CThostFtdcDepartmentUserField* DepartmentUser)
{
	if(DepartmentUser)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcDepartmentUserField: , BrokerID[%s]UserID[%s], InvestorRange[%c], InvestorID[%s]",
			, DepartmentUser->BrokerIDDepartmentUser->UserID, DepartmentUser->InvestorRange, DepartmentUser->InvestorID);
	}
}

void WriteQueryFreq(CThostFtdcQueryFreqField* QueryFreq)
{
	if(QueryFreq)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQueryFreqField: , QueryFreq[%d]",
			, QueryFreq->QueryFreq);
	}
}

void WriteAuthForbiddenIP(CThostFtdcAuthForbiddenIPField* AuthForbiddenIP)
{
	if(AuthForbiddenIP)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcAuthForbiddenIPField: , reserve1[%s]IPAddress[%s]",
			, AuthForbiddenIP->reserve1AuthForbiddenIP->IPAddress);
	}
}

void WriteQryAuthForbiddenIP(CThostFtdcQryAuthForbiddenIPField* QryAuthForbiddenIP)
{
	if(QryAuthForbiddenIP)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryAuthForbiddenIPField: , reserve1[%s]IPAddress[%s]",
			, QryAuthForbiddenIP->reserve1QryAuthForbiddenIP->IPAddress);
	}
}

void WriteSyncDelaySwapFrozen(CThostFtdcSyncDelaySwapFrozenField* SyncDelaySwapFrozen)
{
	if(SyncDelaySwapFrozen)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcSyncDelaySwapFrozenField: , DelaySwapSeqNo[%s]BrokerID[%s], InvestorID[%s], FromCurrencyID[%s], FromRemainSwap[%f], IsManualSwap[%d]",
			, SyncDelaySwapFrozen->DelaySwapSeqNoSyncDelaySwapFrozen->BrokerID, SyncDelaySwapFrozen->InvestorID, SyncDelaySwapFrozen->FromCurrencyID, SyncDelaySwapFrozen->FromRemainSwap, SyncDelaySwapFrozen->IsManualSwap);
	}
}

void WriteUserSystemInfo(CThostFtdcUserSystemInfoField* UserSystemInfo)
{
	if(UserSystemInfo)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcUserSystemInfoField: , BrokerID[%s]UserID[%s], ClientSystemInfoLen[%d], ClientSystemInfo[%s], reserve1[%s], ClientIPPort[%d], ClientLoginTime[%s], ClientAppID[%s], ClientPublicIP[%s]",
			, UserSystemInfo->BrokerIDUserSystemInfo->UserID, UserSystemInfo->ClientSystemInfoLen, UserSystemInfo->ClientSystemInfo, UserSystemInfo->reserve1, UserSystemInfo->ClientIPPort, UserSystemInfo->ClientLoginTime, UserSystemInfo->ClientAppID, UserSystemInfo->ClientPublicIP);
	}
}

void WriteAuthUserID(CThostFtdcAuthUserIDField* AuthUserID)
{
	if(AuthUserID)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcAuthUserIDField: , BrokerID[%s]AppID[%s], UserID[%s], AuthType[%c]",
			, AuthUserID->BrokerIDAuthUserID->AppID, AuthUserID->UserID, AuthUserID->AuthType);
	}
}

void WriteAuthIP(CThostFtdcAuthIPField* AuthIP)
{
	if(AuthIP)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcAuthIPField: , BrokerID[%s]AppID[%s], IPAddress[%s]",
			, AuthIP->BrokerIDAuthIP->AppID, AuthIP->IPAddress);
	}
}

void WriteQryClassifiedInstrument(CThostFtdcQryClassifiedInstrumentField* QryClassifiedInstrument)
{
	if(QryClassifiedInstrument)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryClassifiedInstrumentField: , InstrumentID[%s]ExchangeID[%s], ExchangeInstID[%s], ProductID[%s], TradingType[%c], ClassType[%c]",
			, QryClassifiedInstrument->InstrumentIDQryClassifiedInstrument->ExchangeID, QryClassifiedInstrument->ExchangeInstID, QryClassifiedInstrument->ProductID, QryClassifiedInstrument->TradingType, QryClassifiedInstrument->ClassType);
	}
}

void WriteQryCombPromotionParam(CThostFtdcQryCombPromotionParamField* QryCombPromotionParam)
{
	if(QryCombPromotionParam)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcQryCombPromotionParamField: , ExchangeID[%s]InstrumentID[%s]",
			, QryCombPromotionParam->ExchangeIDQryCombPromotionParam->InstrumentID);
	}
}

void WriteCombPromotionParam(CThostFtdcCombPromotionParamField* CombPromotionParam)
{
	if(CombPromotionParam)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcCombPromotionParamField: , ExchangeID[%s]InstrumentID[%s], CombHedgeFlag[%s], Xparameter[%f]",
			, CombPromotionParam->ExchangeIDCombPromotionParam->InstrumentID, CombPromotionParam->CombHedgeFlag, CombPromotionParam->Xparameter);
	}
}

