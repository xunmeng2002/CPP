#include "ItsFields.h"
#include "Logger.h"


!!travel!!
!!travel!!
Its!!@name!!::Its!!@name!!()
	:ProtocolType("!!@protocolType!!")
{
	memset(m_Buff, 0, sizeof(m_Buff));
}
Its!!@name!!::Its!!@name!!(const vector<string>& items)
{
	memset(m_Buff, 0, sizeof(m_Buff));
!!entry items!!
!!travel!!
	!!@name!! = items[!!$pumpid!!];
!!leave!!
!!leave!!
}
int Its!!@name!!::ToString(char* buff, int size)
{
	return snprintf(buff, size, "Its!!@name!!: !!entry items!!!!travel!!!!@name!![%s] !!leave!!"!!travel!!, !!@name!!.c_str()!!leave!!!!leave!!);
}
int Its!!@name!!::ToStream(char* buff, int size)
{
	return snprintf(buff, size, "!!entry items!!!!travel!!%s|!!leave!!"!!travel!!, !!@name!!.c_str()!!leave!!!!leave!!);
}
string Its!!@name!!::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_Its!!@name!!(!!entry items!!!!travel!!!!@name!! char(!!@len!!), !!leave!!!!leave!!!!entry primarykey!!PRIMARY KEY(!!travel!!!!if pumpid > 0:!!!!inc indent!!, !!dec indent!!!!@name!!!!leave!!!!leave!!));";
}
string Its!!@name!!::InsertSql()
{
	::memset(m_Buff, 0, sizeof(m_Buff));
	snprintf(m_Buff, 4096, "REPLACE INTO t_Its!!@name!! VALUES(!!entry items!!!!travel!!!!if pumpid > 0:!!!!inc indent!!, !!dec indent!!\"%s\"!!leave!!);"!!travel!!, !!@name!!.c_str()!!leave!!!!leave!!);
	return string(m_Buff);
}
int Its!!@name!!::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	auto field = new Its!!@name!!();
!!entry items!!
!!travel!!
	field->!!@name!! = colValues[!!$pumpid!!];
!!leave!!
!!leave!!

	((ItsMdbCallback*)callback)->SelectIts!!@name!!Callback(field);
	return 0;
}

!!leave!!
!!leave!!
