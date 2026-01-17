NAME_01   := 01/main.exe

#  INGREDIENTS
DIRS    := 01
.PHONY: $(DIRS)
$(DIRS): %: %/main.exe

CC      := g++
CFLAGS  := -Wall -Werror -Wextra

SRCS    := main.cpp
# OBJS    := 01/main.o
LIB_OBJ := lib/lib.o

EXES    := $(addsuffix /main.exe, $(DIRS))
OBJS    := $(addsuffix /main.o, $(DIRS))

#  UTENSILS
RM     := rm -f
MAKEFLAGS += --no-print-directory

all: $(EXES)

# Link rule
%/main.exe: %/main.o $(LIB_OBJ)
	$(CC) $^ -o $@

# Compile rule
%/main.o: $(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@


# Clean
clean:
	$(RM) $(OBJS) $(LIB_OBJ)

fclean: clean
	$(RM) $(EXES)

re: fclean all



# all: $(NAME)
# $(NAME): $(OBJS)
# 	$(CC) $(OBJS) -o $(NAME)

# 01: $(NAME_01)
# $(NAME_01): $(OBJS_01)
# 	$(CC) $(OBJS_01) -o $(NAME_01)

# clean:
# 	$(RM) $(OBJS)

# fclean: clean
# 	$(RM) $(NAME)

# re:
# 	$(MAKE) fclean
# 	$(MAKE) all

# .PHONY: clean fclean