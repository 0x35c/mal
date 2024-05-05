#include "MalEnv.hpp"
#include <stdexcept>

MalEnv::MalEnv()
{
	m_map["+"] = new MalFunc([](MalType *a, MalType *b) -> MalType * {
		const MalNumber *x = dynamic_cast<MalNumber *>(a);
		const MalNumber *y = dynamic_cast<MalNumber *>(b);
		if (!x || !y)
			throw std::invalid_argument(
			    "not a number on symbol '+'");
		return new MalNumber(x->value + y->value);
	});
	m_map["-"] = new MalFunc([](MalType *a, MalType *b) -> MalType * {
		const MalNumber *x = dynamic_cast<MalNumber *>(a);
		const MalNumber *y = dynamic_cast<MalNumber *>(b);
		if (!x || !y)
			throw std::invalid_argument(
			    "not a number on symbol '-'");
		return new MalNumber(x->value - y->value);
	});
	m_map["*"] = new MalFunc([](MalType *a, MalType *b) -> MalType * {
		const MalNumber *x = dynamic_cast<MalNumber *>(a);
		const MalNumber *y = dynamic_cast<MalNumber *>(b);
		if (!x || !y)
			throw std::invalid_argument(
			    "not a number on symbol '*'");
		return new MalNumber(x->value * y->value);
	});
	m_map["/"] = new MalFunc([](MalType *a, MalType *b) -> MalType * {
		const MalNumber *x = dynamic_cast<MalNumber *>(a);
		const MalNumber *y = dynamic_cast<MalNumber *>(b);
		if (!x || !y)
			throw std::invalid_argument(
			    "not a number on symbol '/'");
		return new MalNumber(x->value / y->value);
	});
};

MalType *MalEnv::find(const String &symbol)
{
	if (m_map.find(symbol) != m_map.end())
		return (m_map[symbol]);
	return NULL;
};
