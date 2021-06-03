#ifndef __base64_h__
#define __base64_h__


void Base64Encode(const unsigned char* src, int srcLen, unsigned char* dest, int& destLen);

void Base64Decode(const unsigned char* src, int srcLen, unsigned char* dest, int& destLen);



#endif // !__base64_h__
