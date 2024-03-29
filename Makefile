NAME = minishell
SRCS = ./parcing/allocation_free/creation1.c ./parcing/allocation_free/my_malloc.c main.c ./parcing/add_in_list/plant_4.c\
       ./parcing/add_in_list/plant_3.c ./parcing/add_in_list/plant_1.c ./parcing/add_in_list/plant_2.c \
	   ./parcing/add_in_list/spaces.c ./parcing/syntax_error/utile_1.c ./parcing/allocation_free/creation2.c \
	   ./parcing/add_in_list/plants.c ./parcing/allocation_free/creation3.c ./parcing/syntax_error/utile_2.c \
	   ./parcing/syntax_error/utile_3.c  ./parcing/syntax_error/utile_4.c ./parcing/syntax_error/utile_6.c ./execution/execute_utils_3.c \
	   ./execution/execute_utils_1.c ./execution/execution.c ./execution/execute_utils_4.c ./execution/execute_utils.c ./execution/execute_utils_2.c ./execution/utils_2.c \
	   ./execution/execute.c ./execution/pipe.c ./execution/or.c ./execution/subshell.c \
	   ./execution/and.c ./execution/redir_out_utils_4.c ./execution/redir_out_utils.c ./execution/redir_out_utils_2.c \
	   ./execution/redir_out.c ./parcing/syntax_error/utile_5.c ./parcing/syntax_error/utile_8.c \
	   ./builtins/env_parser_utils.c ./builtins/env_utils.c ./builtins/cd.c ./builtins/echo.c ./builtins/export_checker.c \
	   ./builtins/env_parser.c ./parcing/syntax_error/utile_9.c ./parcing/syntax_error/utile_11.c\
	    ./builtins/export_utils.c ./builtins/export.c ./builtins/ft_split.c ./builtins/ft_strlcpy.c ./parcing/syntax_error/utile_7.c \
	   ./builtins/pwd.c ./builtins/unset.c ./builtins/utils.c \
	   ./expanding/expand_utils.c ./expanding/check.c ./expanding/expand.c ./expanding/ft_itoa.c ./execution/utils_3.c ./execution/utils_4.c ./execution/utils.c \
	   ./execution/wild_utils.c ./execution/wildcard.c ./execution/wild.c \
	   ./builtins/env.c ./builtins/cd_utils.c ./builtins/builtins_utils.c ./builtins/builtins_utils_1.c ./builtins/builtins.c ./parcing/syntax_error/utile_10.c \

OBJS    = $(SRCS:.c=.o)

READLINE_LIB = $(shell brew --prefix readline)/lib
READLINE_INC = $(shell brew --prefix readline)/include

CFLAGS 	=   -Wall -Wextra -Werror
RM 		= @rm -f
all : $(NAME)

$(NAME):$(OBJS)
	@echo "Linking $(NAME)"
	@$(CC)  $(CFLAGS) -o $(NAME) $(OBJS) -lreadline -L $(READLINE_LIB)

%.o : %.c
	@echo "Compiling $<"
	@$(CC)  $(CFLAGS) -c $< -o $@ -I  $(READLINE_INC)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean
