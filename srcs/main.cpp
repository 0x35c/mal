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

void init_env(MalEnv &env)
{
	env.set("+", new MalFunc([](MalType *a, MalType *b) -> MalType * {
			const MalNumber *x = dynamic_cast<MalNumber *>(a);
			const MalNumber *y = dynamic_cast<MalNumber *>(b);
			if (!x || !y)
				throw std::invalid_argument(
				    "not a number on symbol '+'");
			return new MalNumber(x->value + y->value);
		}));
	env.set("-", new MalFunc([](MalType *a, MalType *b) -> MalType * {
			const MalNumber *x = dynamic_cast<MalNumber *>(a);
			const MalNumber *y = dynamic_cast<MalNumber *>(b);
			if (!x || !y)
				throw std::invalid_argument(
				    "not a number on symbol '-'");
			return new MalNumber(x->value - y->value);
		}));
	env.set("*", new MalFunc([](MalType *a, MalType *b) -> MalType * {
			const MalNumber *x = dynamic_cast<MalNumber *>(a);
			const MalNumber *y = dynamic_cast<MalNumber *>(b);
			if (!x || !y)
				throw std::invalid_argument(
				    "not a number on symbol '*'");
			return new MalNumber(x->value * y->value);
		}));
	env.set("/", new MalFunc([](MalType *a, MalType *b) -> MalType * {
			const MalNumber *x = dynamic_cast<MalNumber *>(a);
			const MalNumber *y = dynamic_cast<MalNumber *>(b);
			if (!x || !y)
				throw std::invalid_argument(
				    "not a number on symbol '/'");
			return new MalNumber(x->value / y->value);
		}));
}

static void rep(const String &s)
{
	MalEnv env;
	init_env(env);
	try {
		const auto e = EVAL(READ(s), env);
		if (e)
			std::cout << PRINT(e) << std::endl;
		else
			std::cerr << "error during execution"
				  << std::endl; // TODO better error handling
		delete e;
	} catch (std::invalid_argument e) {
		std::cerr << "error during execution: " << e.what()
			  << std::endl;
	}
}

int main(void)
{
	String s;
	while (Readline(String{std::getenv("USER")} + "> ", s))
		rep(s);
	return 0;
}
