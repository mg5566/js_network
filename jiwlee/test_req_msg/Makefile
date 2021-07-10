all:
	clang++ -Wall -Wextra -Werror -std=c++98 -pedantic *.cpp -o test
	./test sample.conf

debug:
	clang++ -Wall -Wextra -Werror -g -fsanitize=address *.cpp 
	./test sample.conf

clean:
	rm test error.log 
