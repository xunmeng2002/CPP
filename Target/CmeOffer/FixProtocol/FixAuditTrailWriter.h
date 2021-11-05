#pragma once
#include <string>
#include "FixAuditTrail.h"

using namespace std;


class FixAuditTrailWriter
{
	FixAuditTrailWriter();
	~FixAuditTrailWriter();
public:
	static FixAuditTrailWriter& GetInstance();
	bool Init();
	void WriteFixAuditTrailRecord(FixAuditTrail* fixAuditTrail);

private:
	void WriteFixAuditTrailHeader();

private:
	static FixAuditTrailWriter m_Instance;

	string m_FileName;
	FILE* m_File;
};
