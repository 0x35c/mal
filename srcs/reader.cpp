#include "Reader.hpp"
#include <iostream>

MalType *read_str(const String &s)
{
	std::vector<String> tokens;
	try {
		tokens = tokenize(s);
	} catch (std::out_of_range e) {
		std::cout << "Invalid format: " << e.what() << std::endl;
		return (NULL);
	}
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
	while (reader.peek()[0] != ')') {
		list->add(read_form(reader));
	}
	reader.next();
	return list;
}

static MalType *read_atom(Reader &reader)
{
	const String tok = reader.peek();
	reader.next();
	if (tok[0] <= '9' && tok[0] >= '0')
		return new MalNumber(std::atoi(tok.c_str()));
	else
		return new MalSymbol(tok);
}
