#include "MalEnv.hpp"
#include <stdexcept>

MalEnv::MalEnv(MalEnv *outer) : m_outer(outer)
{
	this->set("+", new MalFunc([](MalType *a, MalType *b) -> MalType * {
			  const MalNumber *x = dynamic_cast<MalNumber *>(a);
			  const MalNumber *y = dynamic_cast<MalNumber *>(b);
			  if (!x || !y)
				  throw std::invalid_argument(
				      "not a number on symbol '+'");
			  return new MalNumber(x->value + y->value);
		  }));
	this->set("-", new MalFunc([](MalType *a, MalType *b) -> MalType * {
			  const MalNumber *x = dynamic_cast<MalNumber *>(a);
			  const MalNumber *y = dynamic_cast<MalNumber *>(b);
			  if (!x || !y)
				  throw std::invalid_argument(
				      "not a number on symbol '-'");
			  return new MalNumber(x->value - y->value);
		  }));
	this->set("*", new MalFunc([](MalType *a, MalType *b) -> MalType * {
			  const MalNumber *x = dynamic_cast<MalNumber *>(a);
			  const MalNumber *y = dynamic_cast<MalNumber *>(b);
			  if (!x || !y)
				  throw std::invalid_argument(
				      "not a number on symbol '*'");
			  return new MalNumber(x->value * y->value);
		  }));
	this->set("/", new MalFunc([](MalType *a, MalType *b) -> MalType * {
			  const MalNumber *x = dynamic_cast<MalNumber *>(a);
			  const MalNumber *y = dynamic_cast<MalNumber *>(b);
			  if (!x || !y)
				  throw std::invalid_argument(
				      "not a number on symbol '/'");
			  return new MalNumber(x->value / y->value);
		  }));
};

MalType *MalEnv::set(const String &key, MalType *value)
{
	m_map.insert(std::make_pair(key, value));
	return value;
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
		throw std::invalid_argument("symbol not found");
	return value;
}
