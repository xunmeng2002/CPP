#include "Calculator.h"




double Calculator::Parse(const char* expression)
{
	try
	{
		while (*expression != '\0')
		{
			if (*expression == ' ')
			{
				expression++;
				continue;
			}
			if (!IsValid(*expression))
			{
				sprintf(m_ErrorMessage, "InValid Operator [%c]\n", *expression);
				throw std::exception(m_ErrorMessage);
			}
			if (IsNumber(*expression))
			{
				const char* numStart = expression;
				while (IsNumber(*++expression));

				memset(m_NumBuff, 0, sizeof(m_NumBuff));
				memcpy(m_NumBuff, numStart, expression - numStart);
				double f = atof(m_NumBuff);
				m_Parameters.push(f);
				continue;
			}
			if (IsOperator(*expression))
			{
				while (!m_Operators.empty() && GetPriorityLevel(m_Operators.top()) >= GetPriorityLevel(*expression))
				{
					Calculate();
				}
				m_Operators.push(*expression);
			}
			else if (*expression == '(')
			{
				m_Operators.push(*expression);
			}
			else if (*expression == ')')
			{
				while (!m_Operators.empty() && m_Operators.top() != '(')
				{
					Calculate();
				}
				if (m_Operators.empty() || m_Operators.top() != '(')
				{
					sprintf(m_ErrorMessage, "brackets do not match.\n");
					throw std::exception(m_ErrorMessage);
				}
				else
				{
					m_Operators.pop();
				}
			}
			expression++;
		}
		while (!m_Operators.empty())
		{
			Calculate();
		}
		return m_Parameters.top();
	}
	catch (std::exception ex)
	{
		printf("Error occurs: %s\n", ex.what());
	}
	return -1;
}
void Calculator::Clear()
{
	while (!m_Parameters.empty())
	{
		m_Parameters.pop();
	}
	while (!m_Operators.empty())
	{
		m_Operators.pop();
	}

	memset(m_NumBuff, 0, sizeof(m_NumBuff));
	memset(m_ErrorMessage, 0, sizeof(m_ErrorMessage));
}


bool Calculator::IsValid(char oper)
{
	if (oper == '+' || oper == '-' || oper == '*' || oper == '/' || oper == '(' || oper == ')')
	{
		return true;
	}
	if ((oper >= '0' && oper <= '9') || oper == '.')
	{
		return true;
	}
	return false;
}
bool Calculator::IsOperator(char oper)
{
	return oper == '+' || oper == '-' || oper == '*' || oper == '/';
}
bool Calculator::IsNumber(char oper)
{
	return (oper >= '0' && oper <= '9') || oper == '.';
}
int Calculator::GetPriorityLevel(char oper)
{
	int priorState = -1;
	switch (oper)
	{
	case '(':
		priorState = 0;	//左括号优先级最低
		break;
	case '+':
	case '-':
		priorState = 1;	//加减的优先级低，置1
		break;
	case '/':
	case '*':
		priorState = 2;    //乘除的优先级高，置2
		break;
	default:
		break;
	}
	return  priorState;
}

void Calculator::Calculate()
{
	char oper = m_Operators.top();
	m_Operators.pop();

	double y = m_Parameters.top();
	m_Parameters.pop();
	double x = m_Parameters.top();
	m_Parameters.pop();

	double z = Calculate(oper, x, y);
	m_Parameters.push(z);
}
double Calculator::Calculate(char oper, double x, double y)
{
	switch (oper)
	{
	case '+':
		return add(x, y);
	case '-':
		return sub(x, y);
	case '*':
		return mul(x, y);
	case '/':
		return div(x, y);
	}
	
	return -1;
}