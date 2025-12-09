NAME   := main.exe

#  INGREDIENTS
SRCS   := main.c
OBJS   := main.o

CC     := g++
CFLAGS := -Wall -Werror -Wextra


#  UTENSILS
RM     := rm -f
MAKEFLAGS += --no-print-directory

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: clean fclean