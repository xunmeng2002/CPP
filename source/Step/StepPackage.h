#ifndef STEP_PACKAGE_H
#define STEP_PACKAGE_H

#include <map>
#include <vector>
#include <string>
#include "DataStruct.h"

#define STRUCT_SEPARATOR 30
#define FIELD_SEPARATOR 31

#define STEP_HEADER_LEN 12
#define STEP_MAX_FIELD_LEN 1024

int ChangeEndian(int x);

struct StepHeader
{
	char Mark[4];
	int TID;
	int BodyLength;

	void ToStream(char* buff);
	void FromStream(const char* buff);
	bool CheckHeader();
};

class CacheList;
class StepPackage
{
public:
	StepPackage();
	~StepPackage();

	void SetTID(int tid);
	void MakePackage();
	bool ParsePackage();
	void AppendBaseRecord(std::map<int, std::string>& record);
	void AppendRecord(std::map<int, std::string>& record);
	void SetBaseRecord(BaseRecord* baseRecord);
	template<class T>
	void AddRecord(T record);
	const char* GetData(int& len);
	void PushBack(const char* data, int len);
	bool PopFront(int len);
	bool IsEmpty();

private:
	bool ParseHeader();
	bool ParseBaseRecord();
private:
	StepHeader* m_Header;
	std::map<int, std::string> m_BaseRecord;
	

	BaseRecord* m_BaseRecord;
	std::vector<std::map<int, std::string>> m_Records;
	char* m_FieldBuffer;
	char* m_HeaderBuffer;
	CacheList* m_CacheList;
};

#endif
