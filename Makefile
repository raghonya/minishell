NAME	=	minishell

CFLAGS	=	#-Wall -Wextra -Werror

f		=	#-fsanitize=address -g

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
			srcs/expand/expand.c \
			srcs/env/init_env.c \
			srcs/paths/paths.c \
			srcs/check/check_symbols.c \
			srcs/check/errors.c \
			srcs/check/find_commands.c \
			srcs/check/split_wout_quotes.c \
			srcs/redirection/redirections.c \
			srcs/main/minishell.c 
			
LIB		=	./libft

IFLAGS	=	-I$(LIB) -Iincludes

LFLAGS	=	-L$(LIB) -lft -lreadline

OBJS	=	obj/builtin_export.o \
			obj/builtin_unset.o \
			obj/builtin_echo.o \
			obj/builtin_exit.o \
			obj/builtin_env.o \
			obj/builtin_pwd.o \
			obj/builtin_cd.o \
			obj/expand_funcs.o \
			obj/var_name.o \
			obj/expand.o \
			obj/init_env.o \
			obj/paths.o \
			obj/check_symbols.o \
			obj/errors.o \
			obj/find_commands.o \
			obj/minishell.o \
			obj/split_wout_quotes.o \
			obj/redirections.o

CMD		=	$(MAKECMDGOALS)

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
	rm -f $(NAME)

libs:
	@echo "Helper libs"
	@$(MAKE) $(CMD) -C $(LIB)

re:	fclean all

.PHONY: all clean fclean re libs
