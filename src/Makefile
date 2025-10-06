CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11 -D_USE_MATH_DEFINES


all:
	$(CC) $(FLAGS) graph.c stek.c func_and_op.c -o ../build/graph -lm
	../build/graph


clean: 
	rm -rf *.o ../build/graph

rebuild: 
	clean all
