#pragma once

#include "types.hpp"

class Reader
{
      private:
	std::vector<String> m_tokens;
	std::size_t m_position = 0;

      public:
	Reader() = delete;
	Reader(std::vector<String> tokens) : m_tokens(tokens){};
	~Reader(){};

	String peek() const
	{
		if (m_position < m_tokens.size())
			return m_tokens[m_position];
		return {};
	};
	String next()
	{
		m_position++;
		return (peek());
	};
};

std::vector<String> tokenize(const String &s);

MalType *read_str(const String &s);
static MalType *read_form(Reader &reader);
static MalType *read_list(Reader &reader);
static MalType *read_atom(Reader &reader);
