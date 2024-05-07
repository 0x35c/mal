#include "Env.hpp"
#include <iostream>

static MalType *eval_ast(MalType *ast, Env &env);
static MalType *def(MalList *ast, Env &env);
static MalType *let(MalList *ast, Env &env);

static MalType *def(MalList *ast, Env &env)
{
	if (ast->list[1]->type != MalType::SYMBOL)
		throw std::invalid_argument("not a symbol as first arg");
	const auto first = static_cast<MalSymbol *>(ast->list[1]);
	const auto second = EVAL(ast->list[2], env);
	env.set(first->value, second);
	return eval_ast(second, env);
}

static MalType *let(MalList *ast, Env &env)
{
	const auto list = dynamic_cast<MalList *>(ast->list[1]);
	if (!list)
		throw std::invalid_argument(
		    "can't let* without a list as argument");
	Env new_env = new Env(&env);
	const auto size = list->list.size();
	for (std::size_t i = 0; i < size - (size % 2); i += 2) {
		const auto first = static_cast<MalSymbol *>(list->list[i]);
		const auto second = eval_ast(list->list[i + 1], new_env);
		new_env.set(first->value, second);
	}
	return EVAL(ast->list[2], new_env);
}

MalType *EVAL(MalType *ast, Env &env)
{
	if (ast->type == MalType::LIST) {
		MalList *list = static_cast<MalList *>(ast);
		if (list->empty())
			return new MalNil;
		if (list->list[0]->type == MalType::SYMBOL) {
			MalSymbol *symbol =
			    static_cast<MalSymbol *>(list->list[0]);
			if (symbol->value == "def!")
				return def(list, env);
			if (symbol->value == "let*")
				return let(list, env);
		}
		MalList *new_list =
		    dynamic_cast<MalList *>(eval_ast(list, env));
		if (new_list->list[0]->type == MalType::FUNC) {
			MalFunc *func =
			    static_cast<MalFunc *>(new_list->list[0]);
			if (func)
				return func->apply(new_list->list[1],
				                   new_list->list[2]);
		}
	}
	return (eval_ast(ast, env));
}

static MalType *eval_ast(MalType *ast, Env &env)
{
	switch (ast->type) {
	case MalType::SYMBOL:
		return env.get(static_cast<MalSymbol *>(ast)->value);
	case MalType::LIST: {
		MalList *list = static_cast<MalList *>(ast);
		auto copy = new MalList;
		for (std::size_t i = 0; i < list->list.size(); ++i)
			copy->add(EVAL(list->list[i], env));
		return copy;
	}
	default:
		return ast;
	}
}
