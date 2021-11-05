#include "CryptoppEncode.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/hmac.h"
#include "cryptopp/sha.h"
#include "cryptopp/base64.h"
#include "cryptopp/filters.h"
#include "cryptopp/config_int.h"
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

std::string GetCanonicalReq(const FixReqLogonField& reqLogon)
{
	std::string canonicalRequest = reqLogon.MsgSeqNum;
    if (reqLogon.SenderCompID.length() > 0)
    {
        canonicalRequest += "\n" + reqLogon.SenderCompID;
    }
    if (reqLogon.SenderSubID.length() > 0)
    {
        canonicalRequest += "\n" + reqLogon.SenderSubID;
    }
    if (reqLogon.SendingTime.length() > 0)
    {
        canonicalRequest += "\n" + reqLogon.SendingTime;
    }
    if (reqLogon.TargetSubID.length() > 0)
    {
        canonicalRequest += "\n" + reqLogon.TargetSubID;
    }
    if (reqLogon.HeartBtInt.length() > 0)
    {
        canonicalRequest += "\n" + reqLogon.HeartBtInt;
    }
    if (reqLogon.SenderLocationID.length() > 0)
    {
        canonicalRequest += "\n" + reqLogon.SenderLocationID;
    }
    if (reqLogon.LastMsgSeqNumProcessed.length() > 0)
    {
        canonicalRequest += "\n" + reqLogon.LastMsgSeqNumProcessed;
    }
    if (reqLogon.ApplicationSystemName.length() > 0)
    {
        canonicalRequest += "\n" + reqLogon.ApplicationSystemName;
    }
    if (reqLogon.ApplicationSystemVersion.length() > 0)
    {
        canonicalRequest += "\n" + reqLogon.ApplicationSystemVersion;
    }
    if (reqLogon.ApplicationSystemVendor.length() > 0)
    {
        canonicalRequest += "\n" + reqLogon.ApplicationSystemVendor;
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
		HMAC<SHA256> hmac((unsigned char*)decoded_key.c_str(), decoded_key.size());

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