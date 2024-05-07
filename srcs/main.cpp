#include "Env.hpp"
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

static void rep(const String &s, Env &env)
{
	try {
		const auto e = EVAL(READ(s), env);
		if (e)
			std::cout << PRINT(e) << std::endl;
		else
			std::cerr << "error during execution"
				  << std::endl; // TODO better error handling
		delete e;
	} catch (std::invalid_argument &e) {
		std::cerr << "error during execution: " << e.what()
			  << std::endl;
	}
}

static void init_env(StringVec &binds, MalVec &exprs)
{
	binds.push_back("+");
	exprs.push_back(new MalFunc([](MalType *a, MalType *b) -> MalType * {
		const MalNumber *x = dynamic_cast<MalNumber *>(a);
		const MalNumber *y = dynamic_cast<MalNumber *>(b);
		if (!x || !y)
			throw std::invalid_argument(
			    "not a number on symbol '+'");
		return new MalNumber(x->value + y->value);
	}));
	binds.push_back("-");
	exprs.push_back(new MalFunc([](MalType *a, MalType *b) -> MalType * {
		const MalNumber *x = dynamic_cast<MalNumber *>(a);
		const MalNumber *y = dynamic_cast<MalNumber *>(b);
		if (!x || !y)
			throw std::invalid_argument(
			    "not a number on symbol '-'");
		return new MalNumber(x->value - y->value);
	}));
	binds.push_back("*");
	exprs.push_back(new MalFunc([](MalType *a, MalType *b) -> MalType * {
		const MalNumber *x = dynamic_cast<MalNumber *>(a);
		const MalNumber *y = dynamic_cast<MalNumber *>(b);
		if (!x || !y)
			throw std::invalid_argument(
			    "not a number on symbol '*'");
		return new MalNumber(x->value * y->value);
	}));
	binds.push_back("/");
	exprs.push_back(new MalFunc([](MalType *a, MalType *b) -> MalType * {
		const MalNumber *x = dynamic_cast<MalNumber *>(a);
		const MalNumber *y = dynamic_cast<MalNumber *>(b);
		if (!x || !y)
			throw std::invalid_argument(
			    "not a number on symbol '/'");
		return new MalNumber(x->value / y->value);
	}));
}

int main(void)
{
	String s;
	MalVec exprs;
	StringVec binds;
	init_env(binds, exprs);
	Env env(NULL, binds, exprs);
	while (Readline(String{std::getenv("USER")} + "> ", s))
		rep(s, env);
	return 0;
}
