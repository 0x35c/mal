#include "MalEnv.hpp"

MalEnv::MalEnv()
{
	m_map.insert(
	    std::make_pair("+", new MalFunc([](MalType *a, MalType *b) {
				   return dynamic_cast<MalType *>(new MalNumber(
				       std::atoi(a->str(true).c_str()) +
				       std::atoi(b->str(true).c_str())));
			   })));
	m_map.insert(
	    std::make_pair("-", new MalFunc([](MalType *a, MalType *b) {
				   return dynamic_cast<MalType *>(new MalNumber(
				       std::atoi(a->str(true).c_str()) -
				       std::atoi(b->str(true).c_str())));
			   })));
	m_map.insert(
	    std::make_pair("*", new MalFunc([](MalType *a, MalType *b) {
				   return dynamic_cast<MalType *>(new MalNumber(
				       std::atoi(a->str(true).c_str()) *
				       std::atoi(b->str(true).c_str())));
			   })));
	m_map.insert(
	    std::make_pair("/", new MalFunc([](MalType *a, MalType *b) {
				   return dynamic_cast<MalType *>(new MalNumber(
				       std::atoi(a->str(true).c_str()) /
				       std::atoi(b->str(true).c_str())));
			   })));
};

MalType *MalEnv::find(const String &symbol)
{
	if (m_map.find(symbol) != m_map.end())
		return (m_map[symbol]);
	return NULL;
};
