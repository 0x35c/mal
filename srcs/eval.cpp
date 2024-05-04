#include "Environment.hpp"

MalType *eval_ast(MalType *ast, MalEnv env)
{
	MalSymbol *symbol = dynamic_cast<MalSymbol *>(ast);
	if (symbol) {
	}
	return NULL;
}
