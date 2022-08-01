# make file for building single source file programs.

CC = clnag
CXX = clang++
VPATH = src

programs = main

run: all
	./$(programs)

all: $(programs)

clean:
	rm -f $(programs)

# how to refer to each prerquisites and run a command for?
# (i.e., foreach prerequisites)
# p: $(programs)
#     echo $%
