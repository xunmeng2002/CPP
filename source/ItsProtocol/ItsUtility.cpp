#include "ItsUtility.h"
#include "command_id.h"


void GetItsItems(const char* buff, const char* end, vector<string>& items)
{
	const char* p = buff;
	const char* pEnd = nullptr;
	while (p <= end)
	{
		pEnd = GetItsItemEnd(p, end);
		if (pEnd == nullptr)
		{
			break;
		}
		else
		{
			items.push_back(string(p, pEnd));
			p = pEnd + 1;
		}
	}
	if (p < end)
	{
		items.push_back(string(p, end));
	}
}

const char* GetItsItemEnd(const char* buff, const char* end, char op)
{
	const char* p = buff;
	while (p <= end)
	{
		if (*p == op)
		{
			return p;
		}
		p++;
	}
	return nullptr;
}

bool CheckItsMessage(const vector<string>& items)
{
	if (items.size() < 2 || items[0] != "R")
	{
		return false;
	}
	int cmd = atoi(items[1].c_str());
	switch (cmd)
	{
	case CMS_CID_INSERT_ORDER:
		if (items.size() < 26)
		{
			return false;
		}
		break;
	case CMS_CID_CANCEL_ORDER:
		if (items.size() < 16)
		{
			return false;
		}
		break;
	default:
		return false;
	}
	return true;
}
