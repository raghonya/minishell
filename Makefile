NAME	=	minishell

CFLAGS	=	-Wall -Wextra -Werror

f		=	-fsanitize=address -g

DEP		=	Makefile includes/minishell.h

SRCSDIR	=	srcs/*

OBJDIR	=	obj

SRCS	=	srcs/builtins/builtin_export.c \
			srcs/builtins/builtin_unset.c \
			srcs/builtins/builtin_echo.c \
			srcs/builtins/builtin_exit.c \
			srcs/builtins/builtin_env.c \
			srcs/builtins/builtin_pwd.c \
			srcs/builtins/builtin_cd.c \
			srcs/expand/expand_funcs.c \
			srcs/expand/var_name.c \
			srcs/expand/expand_heredoc.c \
			srcs/expand/expand.c \
			srcs/paths/paths.c \
			srcs/check/check_symbols.c \
			srcs/check/errors.c \
			srcs/check/split_wout_quotes.c \
			srcs/redirection/heredoc_funcs.c \
			srcs/redirection/redirections.c \
			srcs/redirection/io_control.c \
			srcs/execution/find_commands.c \
			srcs/execution/execute_multi.c \
			srcs/execution/clear_quotes.c \
			srcs/execution/execute_one.c \
			srcs/execution/exit_status.c \
			srcs/main/initialization.c \
			srcs/main/minishell.c \
			srcs/signals/signals.c

OBJS	=	obj/builtin_export.o \
			obj/builtin_unset.o \
			obj/builtin_echo.o \
			obj/builtin_exit.o \
			obj/builtin_env.o \
			obj/builtin_pwd.o \
			obj/builtin_cd.o \
			obj/expand_funcs.o \
			obj/var_name.o \
			obj/expand_heredoc.o \
			obj/expand.o \
			obj/initialization.o \
			obj/paths.o \
			obj/check_symbols.o \
			obj/errors.o \
			obj/find_command.o \
			obj/minishell.o \
			obj/split_wout_quotes.o \
			obj/redirections.o \
			obj/io_control.o \
			obj/heredoc_funcs.o \
			obj/execute_multi.o \
			obj/clear_quotes.o \
			obj/execute_one.o \
			obj/exit_status.o \
			obj/signals.o
			
LIB		=	./libft

IFLAGS	=	-I$(LIB) -Iincludes -Ireadline-raghonya/include

LFLAGS	=	-L$(LIB) -lft -Lreadline-raghonya/lib -lreadline

# cd readline-master && ./configure --prefix=`find $HOME -name readline-raghonya -type d 2>/dev/null` && make clean && make && make install && cd ..

CMD		=	$(MAKECMDGOALS)

ifeq ($(shell uname -s), Linux)
	IFLAGS	=	-I$(LIB) -Iincludes
	LFLAGS	=	-L$(LIB) -lft -lreadline
endif

ifeq ($(MAKECMDGOALS), bonus)
	CMD = all
endif

all: objdir libs $(NAME)

objdir:
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCSDIR)/%.c $(DEP)
	$(CC) $(CFLAGS) $(f) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(f) $(IFLAGS) $(LFLAGS) -o $(NAME)

clean: libs
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

libs:
	@echo "Helper libs"
	@$(MAKE) $(CMD) -C $(LIB)

re:	fclean all

.PHONY: all clean fclean re libs
