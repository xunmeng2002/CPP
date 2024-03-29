﻿// Base64Test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

static const char* g_Codes = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
static const unsigned char g_Decodes[256] =
{
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255,  62, 255, 255, 255,  63,
     52,  53,  54,  55,  56,  57,  58,  59,  60,  61, 255, 255,
    255, 254, 255, 255, 255,   0,   1,   2,   3,   4,   5,   6,
      7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,
     19,  20,  21,  22,  23,  24,  25, 255, 255, 255, 255, 255,
    255,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,
     37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,
     49,  50,  51, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255
};

void Base64Encode(const unsigned char* src, int srcLen, unsigned char* dest, int& destLen)
{
    unsigned char* p = dest;
    int remainder = srcLen % 3;
    for (auto i = 0; i < srcLen - remainder; i+= 3)
    {
        *p++ = g_Codes[src[i] >> 2];
        *p++ = g_Codes[((src[i] & 3) << 4) + (src[i + 1] >> 4)];
        *p++ = g_Codes[((src[i + 1] & 0xF) << 2) + (src[i + 2] >> 6)];
        *p++ = g_Codes[src[i + 2] & 0x3F];
    }
    
    if (remainder > 0)
    {
        unsigned char a = 0, b = 0;
        a = src[srcLen - remainder];
        if (remainder > 1)
        {
            b = src[srcLen - remainder + 1];
        }
        *p++ = g_Codes[a >> 2];
        *p++ = g_Codes[((a & 3) << 4) + (b >> 4)];
        if (remainder > 1)
        {
            *p++ = g_Codes[(b & 0xf) << 2];
        }
        else
        {
            *p++ = '=';
        }
        *p++ = '=';
    }
    *p = 0;
    destLen = p - dest;
}
void Base64Decode(const unsigned char* src, int srcLen, unsigned char* dest, int& destLen)
{
    int remainder = srcLen % 4;
    unsigned char* p = dest;
    unsigned char value;
    for (auto i = 0; i < srcLen - remainder; i += 4)
    {
        value = g_Decodes[src[i]] << 2;
        value += g_Decodes[src[i + 1]] >> 4;
        *p++ = value;
        if (src[i + 2] != '=')
        {
            value = g_Decodes[src[i + 1]] << 4;
            value += g_Decodes[src[i + 2]] >> 2;
            *p++ = value;
        }
        if (src[i + 3] != '=')
        {
            value = g_Decodes[src[i + 2]] << 6;
            value += g_Decodes[src[i + 3]];
            *p++ = value;
        }
    }
    *p = '\0';
    destLen = p - dest;
}




int main()
{
    unsigned char a[] = "123";
    unsigned char b[] = "1234";
    unsigned char c[] = "12345";

    unsigned char* d = new unsigned char[128];
    unsigned char* e = new unsigned char[128];
    unsigned char* f = new unsigned char[128];

    int len1, len2, len3;
    Base64Encode(a, strlen((const char*)a), d, len1);
    Base64Encode(b, strlen((const char*)b), e, len2);
    Base64Encode(c, strlen((const char*)c), f, len3);

    unsigned char* h = new unsigned char[128];
    unsigned char* i = new unsigned char[128];
    unsigned char* j = new unsigned char[128];
    int len4, len5, len6;
    Base64Decode(d, len1, h, len4);
    Base64Decode(e, len2, i, len5);
    Base64Decode(f, len3, j, len6);

    std::cout << d << "[" << len1 << "]" << endl;
    std::cout << e << "[" << len2 << "]" << endl;
    std::cout << f << "[" << len3 << "]" << endl;

    std::cout << h << "[" << len4 << "]" << endl;
    std::cout << i << "[" << len5 << "]" << endl;
    std::cout << j << "[" << len6 << "]" << endl;

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件