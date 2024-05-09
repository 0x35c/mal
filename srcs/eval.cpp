#include "Env.hpp"
#include <iostream>

static MalType *eval_ast(MalType *ast, Env &env);
static MalType *def(MalList *ast, Env &env);
static MalType *let(MalList *ast, Env &env);

static MalType *def(MalList *ast, Env &env)
{
	if (ast->list[1]->type != MalType::SYMBOL)
		throw std::invalid_argument("not a symbol as first arg");
	const auto first = static_cast<MalSymbol *>(ast->list[1].get());
	const auto second = EVAL(ast->list[2].get(), env);
	env.set(first->value, second);
	return eval_ast(second, env);
}

static MalType *let(MalList *ast, Env &env)
{
	const auto list = dynamic_cast<MalList *>(ast->list[1].get());
	if (!list)
		throw std::invalid_argument(
		    "can't let* without a list as argument");
	// NOTE might need to put actual vectors
	Env new_env = Env(&env, StringVec{}, NULL);
	const auto size = list->list.size();
	for (std::size_t i = 0; i < size - (size % 2); i += 2) {
		const auto first =
		    static_cast<MalSymbol *>(list->list[i].get());
		const auto second = std::unique_ptr<MalType>(
		    eval_ast(list->list[i + 1].get(), new_env));
		new_env.set(first->value, second.get());
	}
	return EVAL(ast->list[2].get(), new_env);
}

MalType *EVAL(MalType *ast, Env &env)
{
	if (ast->type == MalType::LIST) {
		MalList *list = static_cast<MalList *>(ast);
		if (list->empty())
			return new MalNil;
		if (list->list[0]->type == MalType::SYMBOL) {
			MalSymbol *symbol =
			    static_cast<MalSymbol *>(list->list[0].get());
			if (symbol->value == "def!")
				return def(list, env);
			if (symbol->value == "let*")
				return let(list, env);
		}
		auto copy = std::unique_ptr<MalList>(
		    static_cast<MalList *>(eval_ast(list, env)));
		if (copy->list[0]->type == MalType::FUNC) {
			return static_cast<MalFunc *>(copy->list[0].get())
			    ->apply(copy.get());
		}
	}
	return (eval_ast(ast, env));
}

static MalType *eval_ast(MalType *ast, Env &env)
{
	switch (ast->type) {
	case MalType::SYMBOL: {
		auto symbol = static_cast<MalSymbol *>(ast)->value;
		return env.get(symbol)->dup();
	}
	case MalType::LIST: {
		MalList *list = static_cast<MalList *>(ast);
		auto copy = new MalList{};
		for (auto &e : list->list)
			copy->add(EVAL(e.get(), env));
		return copy;
	}
	default:
		return ast->dup();
	}
}
