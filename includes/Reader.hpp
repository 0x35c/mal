#pragma once

#include "types.hpp"

class Reader
{
      private:
	StringVec m_tokens;
	std::size_t m_position = 0;

      public:
	Reader() = delete;
	Reader(StringVec tokens) : m_tokens(tokens){};
	~Reader(){};

	String peek() const
	{
		if (m_position < m_tokens.size())
			return m_tokens[m_position];
		return {};
	};
	String next()
	{
		++m_position;
		return (peek());
	};
};

StringVec tokenize(const String &s);

MalType *read_str(const String &s);
