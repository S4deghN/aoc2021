# make file for building single source file programs.

CC = clnag
CXX = clang++
CXXFLAGS = -std=c++11 -stdlib=libc++ -lfmt
VPATH = src

programs = part2

run: all
	./$(programs)

all: $(programs)

clean:
	rm -f $(programs)

# how to refer to each prerquisites and run a command for?
# (i.e., foreach prerequisites)
# p: $(programs)
#     echo $%
