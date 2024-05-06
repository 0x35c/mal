#pragma once

#include "types.hpp"
#include <map>

typedef std::map<String, MalType *> EnvMap;

class MalEnv
{
      private:
	EnvMap m_map;
	MalEnv *m_outer;

      public:
	// might change that later
	MalEnv() = delete;
	MalEnv(MalEnv *outer);

	~MalEnv(){};

	MalType *set(const String &key, MalType *value);
	MalType *find(const String &symbol);
	MalType *get(const String &symbol);
};

MalType *EVAL(MalType *ast, MalEnv &env);
