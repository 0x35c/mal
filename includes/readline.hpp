#pragma once

#include <stdio.h>

#include <readline/history.h>
#include <readline/readline.h>

#include "types.hpp"

bool Readline(String prompt, String &output);
