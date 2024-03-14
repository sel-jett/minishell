NAME = minishell
SRCS = ./parcing/allocation_free/creation1.c ./parcing/allocation_free/my_malloc.c main.c \
       ./parcing/add_in_list/plant_3.c ./parcing/add_in_list/plant_1.c ./parcing/add_in_list/plant_2.c \
	   ./parcing/add_in_list/spaces.c ./parcing/syntax_error/utile_1.c ./parcing/allocation_free/creation2.c \
	   ./parcing/add_in_list/plants.c ./parcing/allocation_free/creation3.c ./parcing/syntax_error/utile_2.c \
	   ./parcing/syntax_error/utile_3.c  ./parcing/syntax_error/affiche.c ./parcing/syntax_error/utile_4.c \
	   ./execution/execution.c ./execution/execute.c ./execution/pipe.c ./execution/or.c ./execution/subshell.c \
	   ./execution/and.c ./execution/redir_out.c \
	   ./builtins/cd.c ./builtins/echo.c ./builtins/export_checker.c ./builtins/env_parser.c \
	   ./builtins/export.c ./builtins/ft_split.c ./builtins/ft_strlcpy.c \
	   ./builtins/pwd.c ./builtins/unset.c ./builtins/utils.c ./builtins/ft_sort_list.c \
	   ./expanding/expand.c ./execution/utils.c ./expanding/ft_itoa.c

OBJS    = $(SRCS:.c=.o)
# READLINE_LIB = $(shell brew --prefix readline)/lib
# READLINE_INC = $(shell brew --prefix readline)/include
CFLAGS 	=   -Wall -Wextra -Werror -fsanitize=address -g
RM 		= @rm -f
all : $(NAME) clean

$(NAME):$(OBJS)
	@echo "Linking $(NAME)"
	@$(CC)  $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

%.o : %.c
	@echo "Compiling $<"
	@$(CC)  $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
fclean : clean
	$(RM) $(NAME)
re:fclean all
