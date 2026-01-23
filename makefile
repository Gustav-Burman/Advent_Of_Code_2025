NAME_01   := 01/main.exe

#  INGREDIENTS
DIRS    := 01 02
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
