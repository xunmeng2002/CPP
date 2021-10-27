#include "FixAuditTrailWriter.h"
#include "AccountInfo.h"
#include "Utility.h"
#include "TimeUtility.h"
#include <Windows.h>
#include <process.h>
#include <iostream>


FixAuditTrailWriter FixAuditTrailWriter::m_Instance;

FixAuditTrailWriter::FixAuditTrailWriter()
	:m_File(nullptr)
{

}
FixAuditTrailWriter::~FixAuditTrailWriter()
{
	if (m_File)
	{
		fclose(m_File);
	}
	m_File = nullptr;
}
FixAuditTrailWriter& FixAuditTrailWriter::GetInstance()
{
	return m_Instance;
}
bool FixAuditTrailWriter::Init()
{
	if (!AccountInfo::GetInstance().RecordFixAuditTrail)
	{
		return true;
	}
	char timeBuff[32];
	auto t = time(nullptr);
	strftime(timeBuff, 32, "%Y%m%d-%H%M%S", localtime(&t));
	m_FileName = "log\\" + AccountInfo::GetInstance().FixAuditTrailFileName + "." + timeBuff + ".csv";
	if (m_File)
	{
		fclose(m_File);
	}
	m_File = fopen(m_FileName.c_str(), "a+");

	WriteFixAuditTrailHeader();
	return true;
}
void FixAuditTrailWriter::WriteFixAuditTrailRecord(FixAuditTrail* fixAuditTrail)
{
	auto record = fixAuditTrail->ToString();
	fwrite(record, strlen(record), 1, m_File);
	fflush(m_File);
}
void FixAuditTrailWriter::WriteFixAuditTrailHeader()
{
	fwrite(FixAuditTrailHeader, sizeof(FixAuditTrailHeader) - 1, 1, m_File);
	fflush(m_File);
}