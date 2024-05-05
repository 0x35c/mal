#include "MalEnv.hpp"
#include <stdexcept>

MalEnv::MalEnv() : m_outer(NULL){};

MalEnv::MalEnv(const EnvMap &outer)
{
	m_outer = new MalEnv();
	m_outer->m_map = outer;
};

void MalEnv::set(const String &key, MalType *value)
{
	m_map.insert(std::make_pair(key, value));
}

MalType *MalEnv::find(const String &symbol)
{
	for (auto env = this; env; env = env->m_outer) {
		if (env->m_map.find(symbol) != env->m_map.end())
			return (env->m_map[symbol]);
	}
	return NULL;
};

MalType *MalEnv::get(const String &symbol)
{
	const auto value = find(symbol);
	if (!value)
		std::invalid_argument("symbol not found");
	return value;
}
