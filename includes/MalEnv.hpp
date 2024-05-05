#pragma once

#include "types.hpp"
#include <map>

class MalEnv
{
      private:
	typedef std::map<String, MalType *> EnvMap;
	EnvMap m_map;

      public:
	MalEnv();

	~MalEnv(){};

	MalType *find(const String &symbol);
};

MalType *eval_ast(MalType *ast, MalEnv env);
MalType *EVAL(MalType *ast, MalEnv env);
