#include "MalEnv.hpp"
#include "Reader.hpp"
#include "printer.hpp"
#include "readline.hpp"

static MalType *READ(const String &s)
{
	return read_str(s);
}

static const String PRINT(MalType *ast)
{
	return pr_str(ast, true);
}

static void rep(const String &s, MalEnv &env)
{
	try {
		const auto e = EVAL(READ(s), env);
		if (e)
			std::cout << PRINT(e) << std::endl;
		else
			std::cerr << "error during execution"
				  << std::endl; // TODO better error handling
	} catch (std::invalid_argument &e) {
		std::cerr << "error during execution: " << e.what()
			  << std::endl;
	}
}

int main(void)
{
	String s;
	MalEnv env(NULL);
	while (Readline(String{std::getenv("USER")} + "> ", s))
		rep(s, env);
	return 0;
}
