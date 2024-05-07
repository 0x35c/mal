#include "Reader.hpp"
#include "utils.hpp"

static MalType *read_form(Reader &reader);
static MalType *read_list(Reader &reader);
static MalType *read_atom(Reader &reader);

MalType *read_str(const String &s)
{
	std::vector<String> tokens = tokenize(s);
	/* for (auto e : tokens) */
	/* 	std::cout << e << std::endl; */
	Reader reader(tokens);
	return (read_form(reader));
}

static MalType *read_form(Reader &reader)
{
	if (reader.peek()[0] == '(')
		return read_list(reader);
	return read_atom(reader);
}

static MalType *read_list(Reader &reader)
{
	auto list = new MalList{};
	reader.next();
	while (!reader.peek().empty() && reader.peek()[0] != ')') {
		list->add(read_form(reader));
	}
	if (reader.peek().empty())
		throw std::invalid_argument("missing ')' operand");
	reader.next();
	return list;
}

static MalType *read_atom(Reader &reader)
{
	const String tok = reader.peek();
	reader.next();
	if (is_digit(tok[0]))
		return new MalNumber(std::atoi(tok.c_str()));
	else if (tok[0] == '"')
		return new MalString(tok);
	else if (tok == "true")
		return new MalTrue;
	else if (tok == "false")
		return new MalFalse;
	else if (tok.empty())
		return new MalNil;
	else
		return new MalSymbol(tok);
}
