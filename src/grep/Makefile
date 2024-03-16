Target = s21_grep
CC = gcc
II = -Wall -Wextra -Werror -std=c11

all:$(Target)

$(Target): 
	$(CC) $(II) -o s21_grep s21_grep.c

rebuild: clean all

clean:
	rm -rf s21_grep
