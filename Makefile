NAME = philosophers
SORCES = main.c \
			utils.c \
			init.c \
			routine.c \
			routine_utils.c
# HELPERS = $(addprefix helpers/, ft_atoi.c \
#  			ft_putstr_fd.c \
# 			ft_strlen.c )

HELPERS = helpers/ft_atoi.c \
			helpers/ft_putstr_fd.c \
			helpers/ft_strlen.c
OBJS := $(SORCES:.c=.o)
HELPERS_OBJS := $(HELPERS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread 
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

$(NAME): $(OBJS) $(HELPERS_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(HELPERS_OBJS) -o $(NAME)

clean:
	rm -f $(OBJS) $(HELPERS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


