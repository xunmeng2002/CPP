#pragma once
#include <stack>
#include "OperateFuncs.h"


class Calculator
{
public:
	
	double Parse(const char* expression);

private:
	bool IsValid(char oper);
	bool IsOperator(char oper);
	bool IsNumber(char oper);
	int GetPriorityLevel(char oper);
	void Calculate();
	double Calculate(char oper, double x, double y);

private:
	std::stack<double> m_Parameters;
	std::stack<char> m_Operators;

	char m_NumBuff[64];
	char m_ErrorMessage[128];
};

