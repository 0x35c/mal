#include "Reader.hpp"
#include "printer.hpp"
#include "readline.hpp"

MalType *READ(const String &s)
{
	return read_str(s);
}

MalType *EVAL(MalType *e)
{
	return e;
}

const String PRINT(MalType *e)
{
	return pr_str(e);
}

void rep(const String &s)
{
	const auto e = EVAL(READ(s));
	std::cout << e->str() << std::endl;
	delete e;
}

int main(void)
{
	String s;
	while (Readline(String{std::getenv("USER")} + "> ", s))
		rep(s);
	return 0;
}
