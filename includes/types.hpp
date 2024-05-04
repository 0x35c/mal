#pragma once

#include <string>
#include <vector>

typedef std::string String;

class MalType
{
      public:
	virtual ~MalType(){};

	enum Type { NUMBER, SYMBOL, NIL, TRUE, FALSE, STRING, LIST };

	Type type;

	virtual String str(bool print_readably) const = 0;
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

	virtual String str(bool) const
	{
		return std::to_string(value);
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

	virtual String str(bool print_readably) const
	{
		if (!print_readably)
			return value;
		String readable;
		std::size_t i = 1;
		while (i < value.length() - 2) {
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

	virtual String str(bool print_readably) const
	{
		String s = "(";
		for (auto it : list) {
			s += it->str(print_readably) + " ";
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
