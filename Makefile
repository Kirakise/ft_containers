all:
	clang++ -std=c++98 -pedantic -ferror-limit=5 -Wall -Wextra -Werror srcs/main.cpp -o ftcont
	clang++ -std=c++98 -pedantic -ferror-limit=5 -Wall -Wextra -Werror srcs/main2.cpp -o stdcont
	./ftcont > file1
	./stdcont > file2
	-diff file1 file2 > diff.txt
	rm file1
	rm file2
clean:
	rm ftcont stdcont diff.txt
re: clean all
