# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulayus <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 11:40:22 by ulayus            #+#    #+#              #
#    Updated: 2024/03/15 13:37:44 by ulayus           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := mal

SRCS := main.cpp\
		readline.cpp\
		tokenizer.cpp\
		utils.cpp\
		reader.cpp\
		printer.cpp\
		eval.cpp\
		Env.cpp

CC := g++

CFLAGS := -Wall -Wextra -Werror -Wshadow -g -iquote includes --std=c++20 #-O2

LIBS := -lreadline

OBJS := $(addprefix objs/, $(SRCS:.cpp=.o))

all: $(NAME) 

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LIBS)

objs/%.o: srcs/%.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf objs
	rm -f $(NAME)

re:
	make clean
	make all

run:
	@./$(NAME)

.PHONY: all clean re
