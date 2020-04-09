#include "ParseSystemInfo.h"
#include <map>

using namespace std;

map<string, string> StepValues;
map<string, FUNCTION*> StepFuncs;

string StringCat(vector<Node*> nodes)
{
	string result = "";
	for (auto node : nodes)
	{
		result += node->GetValue();
	}
	return result;
}
string IfNull(vector<Node*> nodes)
{
	if (nodes.size() != 3)
	{
		return "";
	}
	auto condition = nodes[0]->GetValue();
	auto first = nodes[1]->GetValue();
	auto second = nodes[2]->GetValue();
	if (!condition.empty())
	{
		return first;
	}
	return second;
}


std::string Node::GetValue()
{
	if (NodeType == NodeType::CONST_VALUE)
	{
		return NodeName;
	}
	else if (NodeType == NodeType::FIELD)
	{
		return StepValues[NodeName];
	}
	else if (NodeType == NodeType::FUNCTION)
	{
		return StepFuncs[NodeName](Children);
	}
	return "";
}

void Init()
{
	string key = "STEP_IP";
	string value = "192.168.6.78";
	StepValues[key] = value;
	key = "STEP_MAC";
	value = "F4-8E-38-83-E2-3D";
	StepValues[key] = value;
	key = "STEP_LOCAL_MAC";
	value = "F4-8E-38-83-E2-4E";
	StepValues[key] = value;

	key = "STRING";
	StepFuncs[key] = StringCat;
	key = "IFNULL";
	StepFuncs[key] = IfNull;
}
void PrintNode(Node* head, int depth)
{
	string indent(depth * 2, '-');
	printf("%sNodeType[%d], NodeName[%s]\n", indent.c_str(), head->NodeType, head->NodeName.c_str());
	depth++;
	for (auto node : head->Children)
	{
		PrintNode(node, depth);
	}
}

bool StartsWith(std::string src, std::string sub)
{
	return src.find(sub) == 0;
}
bool EndsWith(std::string src, std::string sub)
{
	return src.rfind(sub) == (src.length() - sub.length());
}

std::string Lstrip(const std::string& s)
{
	if (s.front() != ' ')
		return s;
	for (auto index = 0u; index < s.size(); index++)
	{
		if (s[index] != ' ')
		{
			return s.substr(index);
		}
	}
	return s;
}
std::string Rstrip(const std::string& s)
{
	if (s.back() != ' ')
		return s;
	for (auto index = s.size() - 1; index >= 0; index--)
	{
		if (s[index] != ' ')
		{
			return s.substr(0, index + 1);
		}
	}
	return s;
}
std::string Strip(const std::string& s)
{
	string newString = Lstrip(s);
	return Rstrip(newString);
}
std::string StripQuote(const std::string& src)
{
	if (StartsWith(src, "\"") && EndsWith(src, "\""))
	{
		return src.substr(1, src.size() - 2);
	}
	return src;
}

std::vector<std::string> Split(const std::string& s, const std::string& separator)
{
	vector<string> result;
	int pos;
	string temp = s;
	while ((pos = temp.find_first_of(separator)) != temp.npos)
	{
		if (pos > 0)
		{
			result.push_back(temp.substr(0, pos));
		}
		temp = temp.substr(pos + separator.length());
	}
	if (temp.length() > 0)
	{
		result.push_back(temp);
	}
	return std::move(result);
}
std::vector<std::string> Split(const std::string& s, char separator)
{
	vector<string> result;
	int pos;
	string temp = s;
	while ((pos = temp.find_first_of(separator)) != temp.npos)
	{
		if (pos > 0)
		{
			result.push_back(temp.substr(0, pos));
		}
		temp = temp.substr(pos + 1);
	}
	if (temp.length() > 0)
	{
		result.push_back(temp);
	}
	return std::move(result);
}


std::string GetParamString(const std::string& src, size_t& endIndex)
{
	int start = 0;
	for (size_t index = 0; index < src.size(); index++)
	{
		if (src[index] == '(')
		{
			start = index + 1;
			break;
		}
	}
	auto count = 1u;
	for (size_t index = start + 1; index < src.size(); index++)
	{
		if (src[index] == '(')
		{
			count++;
			continue;
		}
		if (src[index] == ')')
		{
			count--;
			if (count == 0)
			{
				endIndex = index;
				break;
			}
			continue;
		}
	}
	return src.substr(start, endIndex - start);
}
std::string GetNextNodeString(const std::string& src, size_t& endIndex, char op)
{
	if (StartsWith(src, "$STEP"))
	{
		endIndex = src.find(op, 1);
		return src.substr(0, endIndex);
	}
	if (StartsWith(src, "$"))
	{
		GetParamString(src, endIndex);
		endIndex += 1;
		return src.substr(0, endIndex);
	}
	endIndex = src.find(op);
	return src.substr(0, endIndex);
}
std::string GetTopLevelNextNodeString(const std::string& src, size_t& endIndex)
{
	return GetNextNodeString(src, endIndex, '$');
}
std::string GetParamNextNodeString(const std::string& src, size_t& endIndex)
{
	return GetNextNodeString(src, endIndex, ',');
}

void ParseParam(std::string src, Node* parent)
{
	size_t index;
	while (!src.empty())
	{
		Node* node = new Node();
		parent->Children.push_back(node);
		auto dest = GetParamNextNodeString(src, index);
		ParseNode(dest, node);
		if (index == src.npos || index >= src.size())
		{
			src = "";
		}
		else
		{
			src = src.substr(index + 1);
			src = Lstrip(src);
		}
	}
}
void ParseNode(std::string src, Node* node)
{
	src = Strip(src);
	src = StripQuote(src);
	if (StartsWith(src, "$STEP"))
	{
		node->NodeType = NodeType::FIELD;
		node->NodeName = src.substr(1);
	}
	else if (StartsWith(src, "$"))
	{
		node->NodeType = NodeType::FUNCTION;
		auto index = src.find('(');
		node->NodeName = src.substr(1, index - 1);
		size_t endIndex;
		auto paramString = GetParamString(src, endIndex);
		ParseParam(paramString, node);
	}
	else
	{
		node->NodeType = NodeType::CONST_VALUE;
		node->NodeName = src;
	}
}
std::string ParseSystemInfo(std::string src)
{
	std::vector<Node*> headNodes;
	size_t index;
	src = Strip(src);
	while (src.size() > 0)
	{
		auto dest = GetTopLevelNextNodeString(src, index);
		src = src.substr(index);

		Node* head = new Node();
		ParseNode(dest, head);
		headNodes.push_back(head);
	}
	for (auto node : headNodes)
	{
		PrintNode(node, 0);
	}

	string result = "";
	for (auto node : headNodes)
	{
		result += node->GetValue();
	}
	return result;
}