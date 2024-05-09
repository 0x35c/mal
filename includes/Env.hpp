#pragma once

#include "types.hpp"
#include <map>

typedef std::map<String, std::unique_ptr<MalType>> EnvMap;
typedef MalVec::iterator MalIter;

class Env
{
      private:
	EnvMap m_map{};
	Env *m_outer;

      public:
	// might change that later
	Env() = delete;
	Env(Env *outer, const StringVec &binds, MalList *exprs);

	~Env();

	void set(const String &key, MalType *value);
	Env *find(const String &symbol);
	MalType *get(const String &symbol);
};

MalType *EVAL(MalType *ast, Env &env);
