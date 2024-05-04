#pragma once

#include "types.hpp"
#include <map>

typedef int (*SymbolFuncPtr)(int, int);

class MalEnv
{
      private:
	typedef std::map<String, SymbolFuncPtr> EnvMap;
	EnvMap m_map;

      public:
	MalEnv()
	{
		m_map.insert(std::pair<String, SymbolFuncPtr>(
		    "+", [](int a, int b) { return a + b; }));
		m_map.insert(std::pair<String, SymbolFuncPtr>(
		    "-", [](int a, int b) { return a - b; }));
		m_map.insert(std::pair<String, SymbolFuncPtr>(
		    "*", [](int a, int b) { return a * b; }));
		m_map.insert(std::pair<String, SymbolFuncPtr>(
		    "/", [](int a, int b) { return a / b; }));
	};

	~MalEnv(){};

	SymbolFuncPtr find(const String &symbol)
	{
		if (m_map.find(symbol) != m_map.end())
			return (m_map[symbol]);
		return NULL;
	};
};

MalType *eval_ast(MalType *ast, MalEnv env);
