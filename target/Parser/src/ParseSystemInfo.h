#include <vector>
#include <string>
#pragma once

enum class NodeType
{
	CONST_VALUE,
	FIELD,
	FUNCTION,
};

struct Node
{
	NodeType NodeType;
	std::string NodeName;

	std::vector<Node*> Children;

	std::string GetValue();
};

typedef std::string FUNCTION(std::vector<Node*>);

void Init();
void PrintNode(Node* head, int depth);

bool StartsWith(std::string src, std::string sub);
bool EndsWith(std::string src, std::string sub);

std::string Lstrip(const std::string& src);
std::string Rstrip(const std::string& src);
std::string Strip(const std::string& src);
std::string StripQuote(const std::string& src);

std::vector<std::string> Split(const std::string& src, const std::string& separator);
std::vector<std::string> Split(const std::string& src, char separator);



std::string GetParamString(const std::string& src, size_t& endIndex);
std::string GetNextNodeString(const std::string& src, size_t& endIndex, char op);
std::string GetTopLevelNextNodeString(const std::string& src, size_t& endIndex);
std::string GetParamNextNodeString(const std::string& src, size_t& endIndex);

void ParseParam(std::string src, Node* parent);
void ParseNode(std::string src, Node* node);
std::string ParseSystemInfo(std::string src);
