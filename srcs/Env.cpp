#include "Env.hpp"
#include <stdexcept>

Env::Env(Env *outer) : m_outer(outer){};

Env::~Env(){
    /* for (auto e : m_map) */
    /* 	delete e.second; */
};

void Env::set(const String &key, MalType *value)
{
	m_map.insert_or_assign(key, value);
}

Env *Env::find(const String &symbol)
{
	for (auto env = this; env; env = env->m_outer) {
		if (env->m_map.contains(symbol))
			return env;
	}
	return NULL;
};

MalType *Env::get(const String &symbol)
{
	Env *env = this->find(symbol);
	if (!env)
		throw std::invalid_argument("symbol not found");
	return env->m_map[symbol];
}
