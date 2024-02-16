NAME = minishell
SRCS = ./parcing/allocation_free/creation.c ./parcing/allocation_free/my_malloc.c main.c \
       ./parcing/add_in_list/plant_3.c ./parcing/add_in_list/plant_1.c ./parcing/add_in_list/plant_2.c \
	   ./parcing/add_in_list/spaces.c ./parcing/syntax_error/utile_1.c
OBJS    = $(SRCS:.c=.o)
CFLAGS 	=   -Wall -Wextra -Werror
RM 		= @rm -f
all : $(NAME) clean

$(NAME):$(OBJS)
	$(CC)  -o $(NAME) $(OBJS) -lreadline
%.o : %.c 
	$(CC)  $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
fclean : clean
	$(RM) $(NAME)
re:fclean all