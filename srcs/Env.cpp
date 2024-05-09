#include "Env.hpp"

Env::Env(Env *outer, const StringVec &binds, MalList *exprs) : m_outer(outer)
{
	if (binds.empty() && !exprs)
		return;
	if (!exprs)
		throw std::invalid_argument("exprs is null");
	for (std::size_t i = 0; i < binds.size(); i++) {
		set(binds[i], exprs->list[i].get());
	}
};

Env::~Env(){};

void Env::set(const String &key, MalType *value)
{
	m_map.insert_or_assign(key, std::unique_ptr<MalType>(value));
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
	return env->m_map[symbol].get();
}
