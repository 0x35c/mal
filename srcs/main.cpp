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
		auto in = std::unique_ptr<MalType>(READ(s));
		auto out = std::unique_ptr<MalType>(EVAL(in.get(), env));
		if (out.get())
			std::cout << PRINT(out.get()) << std::endl;
		else
			std::cerr << "error during execution"
				  << std::endl; // TODO better error handling
	} catch (std::invalid_argument &e) {
		std::cerr << "error during execution: " << e.what()
			  << std::endl;
	}
}

static void init_env(StringVec &binds, MalList *exprs)
{
	binds.push_back("+");
	exprs->add(new MalFunc([](MalList *list) -> MalType * {
		int ret = 0;
		for (std::size_t i = 1; i < list->list.size(); i++) {
			const auto e = list->list[i].get();
			if (e->type != MalType::NUMBER)
				throw std::invalid_argument(
				    "not a number on symbol '+'");
			ret += static_cast<MalNumber *>(e)->value;
		}
		return new MalNumber(ret);
	}));
	binds.push_back("-");
	exprs->add(new MalFunc([](MalList *list) -> MalType * {
		int ret = 0;
		for (std::size_t i = 1; i < list->list.size(); i++) {
			const auto e = list->list[i].get();
			if (e->type != MalType::NUMBER)
				throw std::invalid_argument(
				    "not a number on symbol '-'");
			const auto nb = static_cast<MalNumber *>(e)->value;
			if (i == 1)
				ret = nb;
			else
				ret -= nb;
		}
		return new MalNumber(ret);
	}));
	binds.push_back("*");
	exprs->add(new MalFunc([](MalList *list) -> MalType * {
		int ret = 0;
		for (std::size_t i = 1; i < list->list.size(); i++) {
			const auto e = list->list[i].get();
			if (e->type != MalType::NUMBER)
				throw std::invalid_argument(
				    "not a number on symbol '*'");
			if (i == 1)
				ret = 1;
			ret *= static_cast<MalNumber *>(e)->value;
		}
		return new MalNumber(ret);
	}));
	binds.push_back("/");
	exprs->add(new MalFunc([](MalList *list) -> MalType * {
		int ret = 0;
		for (std::size_t i = 1; i < list->list.size(); i++) {
			const auto e = list->list[i].get();
			if (e->type != MalType::NUMBER)
				throw std::invalid_argument(
				    "not a number on symbol '/'");
			const auto nb = static_cast<MalNumber *>(e)->value;
			if (i != 1 && nb == 0)
				return new MalNil();
			if (i == 1)
				ret = nb;
			else
				ret /= nb;
		}
		return new MalNumber(ret);
	}));
}

int main(void)
{
	String s;
	StringVec binds;
	auto exprs = std::unique_ptr<MalList>(new MalList());
	init_env(binds, exprs.get());
	Env env(NULL, binds, exprs.get());
	while (Readline(String{std::getenv("USER")} + "> ", s))
		rep(s, env);
	rl_uninitialize();
	return 0;
}
