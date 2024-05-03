#pragma once

#include <string>
#include <vector>

typedef std::string String;

class MalType
{
      public:
	virtual ~MalType(){};

	enum Type { SYMBOL, LIST, STRING, NUMBER };

	Type type;

	virtual String str() const = 0;
};

class MalNumber : public MalType
{
      private:
	int value;

      public:
	MalNumber(int n) : value(n)
	{
		type = MalType::Type::NUMBER;
	};

	virtual ~MalNumber(){};

	virtual String str() const
	{
		// thanks kdx (kind ugly tho ngl)
		char buf[64] = {};
		snprintf(buf, sizeof(buf) - 1, "%d", value);
		return buf;
	};
};

class MalSymbol : public MalType
{
      private:
	String value;

      public:
	MalSymbol(const String &s) : value(s)
	{
		type = MalType::Type::SYMBOL;
	};

	virtual ~MalSymbol(){};

	virtual String str() const
	{
		return value;
	};
};

// Not implemented yet, tbd
class MalString : public MalType
{
      private:
	String value;

      public:
	MalString(const String &s) : value(s)
	{
		type = MalType::Type::STRING;
	};

	virtual ~MalString(){};

	virtual String str() const
	{
		return value;
	};
};

class MalList : public MalType
{
      private:
	std::vector<MalType *> list;

      public:
	MalList()
	{
		type = MalType::Type::LIST;
	};

	virtual ~MalList()
	{
		for (auto it : list)
			delete it;
	};

	virtual String str() const
	{
		String s = "(";
		for (auto it : list) {
			s += it->str() + " ";
		};
		s.erase(s.length() - 1, 1);
		s += ")";
		return s;
	};

	void add(MalType *e)
	{
		list.push_back(e);
	}
};
