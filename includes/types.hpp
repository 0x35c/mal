#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

typedef std::string String;

class MalType
{
      public:
	typedef MalType *(*SymbolFuncPtr)(MalType *, MalType *);
	virtual ~MalType(){};

	enum Type { NUMBER, SYMBOL, NIL, TRUE, FALSE, STRING, LIST, FUNC };

	Type type;

	virtual String str(bool print_readably) const = 0;
};

class MalNumber : public MalType
{
      public:
	int value;

	MalNumber() = delete;
	MalNumber(int n) : value(n)
	{
		type = MalType::Type::NUMBER;
	};

	virtual ~MalNumber(){};

	virtual String str(bool) const
	{
		return std::to_string(value);
	};
};

class MalSymbol : public MalType
{
      public:
	String value;

	MalSymbol() = delete;
	MalSymbol(const String &s) : value(s)
	{
		type = MalType::Type::SYMBOL;
	};

	virtual ~MalSymbol(){};

	virtual String str(bool) const
	{
		return value;
	};
};

class MalNil : public MalType
{
      public:
	MalNil()
	{
		type = MalType::Type::NIL;
	};

	virtual ~MalNil(){};

	virtual String str(bool) const
	{
		return "NIL";
	};
};

class MalTrue : public MalType
{
      public:
	MalTrue()
	{
		type = MalType::Type::TRUE;
	};

	virtual ~MalTrue(){};

	virtual String str(bool) const
	{
		return "TRUE";
	};
};

class MalFalse : public MalType
{
      public:
	MalFalse()
	{
		type = MalType::Type::FALSE;
	};

	virtual ~MalFalse(){};

	virtual String str(bool) const
	{
		return "FALSE";
	};
};

class MalString : public MalType
{
      public:
	String value;

	MalString() = delete;
	MalString(const String &s) : value(s)
	{
		type = MalType::Type::STRING;
	};

	virtual ~MalString(){};

	virtual String str(bool print_readably) const
	{
		if (!print_readably)
			return value;
		String readable;
		std::size_t i = 1;
		while (i < value.length() - 1) {
			if (value[i] == '\\') {
				i++;
				if (value.at(i) == 'n') {
					readable += '\n';
					i++;
				} else if (value.at(i) == '\\') {
					readable += '\\';
					i++;
				}
				continue;
			}
			readable += value[i];
			i++;
		}
		return readable;
	};
};

class MalList : public MalType
{
      public:
	std::vector<MalType *> list;

	MalList()
	{
		type = MalType::Type::LIST;
	};

	virtual ~MalList()
	{
		for (auto it : list)
			delete it;
	};

	virtual String str(bool print_readably) const
	{
		String s = "(";
		for (auto it : list) {
			s += it->str(print_readably) + " ";
		};
		if (s.at(s.length() - 1) == ' ')
			s.erase(s.length() - 1, 1);
		s += ")";
		return s;
	};

	void add(MalType *e)
	{
		list.push_back(e);
	}

	bool empty() const
	{
		return list.size() == 0;
	}
};

class MalFunc : public MalType
{
      public:
	MalType::SymbolFuncPtr func;

	MalFunc() = delete;
	MalFunc(MalType::SymbolFuncPtr fn) : func(fn)
	{
		type = MalType::Type::FUNC;
	};

	virtual ~MalFunc(){};

	MalType *apply(MalType *a, MalType *b) const
	{
		return func(a, b);
	}

	virtual String str(bool) const
	{
		return "im a function now";
	};
};
