#include "../includes/types.hpp"
#include <iostream>

const String &READ(const String &input);
const String &EVAL(const String &ast);
const String &PRINT(const String &ast);
const String &rep(const String &ast);

const String &READ(const String &input)
{
	return (input);
}

const String &EVAL(const String &ast)
{
	return (ast);
}

const String &PRINT(const String &ast)
{
	return (ast);
}

const String &rep(const String &ast)
{
	return READ(EVAL(PRINT(ast)));
}

int main_loop(void)
{
	std::string input;
	std::cout << std::getenv("USER") << "> ";
	while (std::getline(std::cin, input)) {
		std::cout << rep(input) << std::endl;
		std::cout << std::getenv("USER") << "> ";
	}
	return (0);
}
