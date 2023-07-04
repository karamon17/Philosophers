NAME = philo_bonus

SRC = src
OBJ = obj

SRCS = $(wildcard $(SRC)/*.c)

OBJS = $(subst $(SRC), $(OBJ), $(SRCS:.c=.o))

HEADER = ./includes/philo_bonus.h

CFLAGS = -Wall -Wextra -Werror -g
IFLAGS	=	-I./includes/

$(OBJ)/%.o: $(SRC)/%.c $(HEADER) Makefile
	cc $(CFLAGS) $(IFLAGS) -c $< -o $@

all: $(NAME)

$(OBJ):
		@mkdir -p $(OBJ)

$(NAME): $(HEADER) $(OBJ) $(OBJS)
	cc $(CFLAGS) $(OBJS) $(IFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:	all clean fclean re