NAME	=	minishell

CFLAGS	=	#-Wall -Wextra -Werror

f		=	-fsanitize=address -g

DEP		=	Makefile includes/minishell.h

# SRCSDIR	=	src

OBJDIR	=	obj

SRCS	=	$(wildcard srcs/*.c)
			
LIB		=	./libft

IFLAGS	=	-I$(LIB) -Iincludes

LFLAGS	=	-L$(LIB) -lft -lreadline

OBJS	=	$(SRCS:srcs/%.c=$(OBJDIR)/%.o)

CMD		=	$(MAKECMDGOALS)

ifeq ($(MAKECMDGOALS), bonus)
	CMD = all
endif

all: objdir libs $(NAME)

objdir:
	@echo $(OBJS)
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: srcs/%.c $(DEP)
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
