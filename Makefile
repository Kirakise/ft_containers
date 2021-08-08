all:
	clang++ -g -std=c++98 -pedantic -ferror-limit=5 -Wall -Wextra -Werror main.cpp -o ftcont
	clang++ -g -std=c++98 -pedantic -ferror-limit=5 -Wall -Wextra -Werror main2.cpp -o stdcont
clean:
	rm a.out
re: clean all
