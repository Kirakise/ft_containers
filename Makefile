all:
	g++ -g -Wall -Wextra -Werror main.cpp
clean:
	rm a.out
re: clean all
