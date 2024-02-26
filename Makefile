NAME = minishell
SRCS = ./parcing/allocation_free/creation1.c ./parcing/allocation_free/my_malloc.c main.c \
       ./parcing/add_in_list/plant_3.c ./parcing/add_in_list/plant_1.c ./parcing/add_in_list/plant_2.c \
	   ./parcing/add_in_list/spaces.c ./parcing/syntax_error/utile_1.c ./parcing/allocation_free/creation2.c \
	   ./parcing/add_in_list/plants.c ./parcing/allocation_free/creation3.c ./parcing/syntax_error/utile_2.c \
	   ./parcing/syntax_error/utile_3.c  ./parcing/syntax_error/affiche.c ./parcing/syntax_error/utile_4.c
  OBJS    = $(SRCS:.c=.o)
READLINE_LIB = $(shell brew --prefix readline)/lib
READLINE_INC = $(shell brew --prefix readline)/include
CFLAGS 	=   -Wall -Wextra -Werror -g
RM 		= @rm -f
all : $(NAME) clean

$(NAME):$(OBJS)
	$(CC) -o $(NAME) $(OBJS) -L $(READLINE_LIB) -lreadline

%.o : %.c 
	$(CC) $(CFLAGS) -I $(READLINE_INC) -c $< -o $@

clean:
	$(RM) $(OBJS)
fclean : clean
	$(RM) $(NAME)
re:fclean all