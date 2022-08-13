# make file for building single source file programs.

CC = clnag
CXX = clang++
CXXFLAGS = -std=c++20 -stdlib=libc++ -lfmt
VPATH = src

programs = main

run: all
	./$(programs)

all: $(programs)

clean:
	rm -f $(programs)

# how to refer to each perquisite and run a command for?
# (i.e., foreach prerequisites)
# p: $(programs)
#     echo $%
