#include "CryptoppEncode.h"
#include "cryptlib.h"
#include "hmac.h"
#include "sha.h"
#include "base64.h"
#include "filters.h"
#include "config_int.h"
#include "Logger.h"
#include <stdio.h>
#include <cstdlib>


using CryptoPP::Exception;
using CryptoPP::HMAC;
using CryptoPP::SHA256;
using CryptoPP::Base64URLEncoder;
using CryptoPP::Base64URLDecoder;
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::HashFilter;

using namespace std;

std::string GetCanonicalReq(const FIX::Message& logonMsg)
{
	std::string canonicalRequest;

	FIX::StringField msgSeqNum(34);
	if (logonMsg.getHeader().isSetField(msgSeqNum))
	{
		logonMsg.getHeader().getField(msgSeqNum);
		canonicalRequest = canonicalRequest + msgSeqNum.getValue() + "\n";
	}

	FIX::StringField senderCompID(49);
	if (logonMsg.getHeader().isSetField(senderCompID))
	{
		logonMsg.getHeader().getField(senderCompID);
		canonicalRequest = canonicalRequest + senderCompID.getValue() + "\n";
	}

	FIX::StringField senderSubID(50);
	if (logonMsg.getHeader().isSetField(senderSubID))
	{
		logonMsg.getHeader().getField(senderSubID);
		canonicalRequest = canonicalRequest + senderSubID.getValue() + "\n";
	}

	FIX::StringField senderTime(52);
	if (logonMsg.getHeader().isSetField(senderTime))
	{
		logonMsg.getHeader().getField(senderTime);
		canonicalRequest = canonicalRequest + senderTime.getValue() + "\n";
	}

	FIX::StringField targetSubID(57);
	if (logonMsg.getHeader().isSetField(targetSubID))
	{
		logonMsg.getHeader().getField(targetSubID);
		canonicalRequest = canonicalRequest + targetSubID.getValue() + "\n";
	}

	FIX::StringField heartBtInt(108);
	if (logonMsg.isSetField(heartBtInt))
	{
		logonMsg.getField(heartBtInt);
		canonicalRequest = canonicalRequest + heartBtInt.getValue() + "\n";
	}

	FIX::StringField senderLocationID(142);
	if (logonMsg.getHeader().isSetField(senderLocationID))
	{
		logonMsg.getHeader().getField(senderLocationID);
		canonicalRequest = canonicalRequest + senderLocationID.getValue() + "\n";
	}

	FIX::StringField lastMsgSeqSumProcessed(369);
	if (logonMsg.getHeader().isSetField(lastMsgSeqSumProcessed))
	{
		logonMsg.getHeader().getField(lastMsgSeqSumProcessed);
		canonicalRequest = canonicalRequest + lastMsgSeqSumProcessed.getValue() + "\n";
	}

	FIX::StringField applicationSystemName(1603);
	if (logonMsg.isSetField(applicationSystemName))
	{
		logonMsg.getField(applicationSystemName);
		canonicalRequest = canonicalRequest + applicationSystemName.getValue() + "\n";
	}

	FIX::StringField tradingSystemVersion(1604);
	if (logonMsg.isSetField(tradingSystemVersion))
	{
		logonMsg.getField(tradingSystemVersion);
		canonicalRequest = canonicalRequest + tradingSystemVersion.getValue() + "\n";
	}

	FIX::StringField applicationSystemVendor(1605);
	if (logonMsg.isSetField(applicationSystemVendor))
	{
		logonMsg.getField(applicationSystemVendor);
		canonicalRequest = canonicalRequest + applicationSystemVendor.getValue();
	}

	WRITE_LOG(LogLevel::Debug, "CanonicalRequest: [%s]", canonicalRequest.c_str());
	return canonicalRequest;
}

string calculateHMAC(string& key, string& canonicalRequest)
{

    string decoded_key, calculatedHmac, encodedHmac;

    try
    {
        // Decode the key since it is base64url encoded
        StringSource(key, true, new Base64URLDecoder(new StringSink(decoded_key)));

        // Calculate HMAC
        HMAC<SHA256> hmac((byte*)decoded_key.c_str(), decoded_key.size());

        StringSource(canonicalRequest, true, new HashFilter(hmac, new StringSink(calculatedHmac)));
    }
    catch (const CryptoPP::Exception& e)
    {
        cerr << e.what() << endl;
        exit(1);
    }

    // base64url encode the HMAC and strip padding
    StringSource(calculatedHmac, true, new Base64URLEncoder(new StringSink(encodedHmac)));

    return encodedHmac;
}