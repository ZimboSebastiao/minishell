CC = cc
AR = ar
ARFLAGS = rcs
FLAGS = -Wall -Wextra -Werror -I includes
      
SRC := $(shell find . -type f -name "*.c")
OBJECTS = $(SRC:.c=.o)

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJECTS)

%.o: %.c libft.h
	$(CC) $(FLAGS) -c $< -o $@

.PHONY: all clean fclean re

clean: 
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
