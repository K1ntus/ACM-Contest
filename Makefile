# Makefile
# http://acm.cs.cityu.edu.hk/oj2/index.php/tag?name=&tags%5B%5D=assignment_2020b

FILESPARS	= $(wildcard parser/src/*.c)
FILESSRC	= $(wildcard src/*.c)
CC			= g++
CFLAGS		= -lm -static
OBJPARS		= $(FILESPARS:parser/src/%.c=build/%.o)
OBJSRC		= $(FILESSRC:src/%.c=build/%.o)
OBJ 		= $(OBJPARS) $(OBJSRC) 

.PHONY: all
all:clean_problems 190_problem 248_problem problems_runall# clean_week1 w1_problem1 w1_problem2 sum_problem lpd_problem w1_runall #doc


190_problem: Problems/190-equation.c
		$(CC) $(CFLAGS) $< -o $@

248_problem: Problems/248-intersection.c
		$(CC) $(CFLAGS) $< -o $@



problems_runall:
	@echo ''
	@echo '* Problem 190 - Equations *'
	#@./190_problem
	@echo ''
	@echo '* Problem 248 - Intersections *'
	@./248_problem

w1_problem1: Week1/countprime_3.c #$(OBJ) 
		$(CC) $(CFLAGS) $< -o $@

w1_problem2: Week1/countprime_4.c  #$(OBJ) 
		$(CC) $(CFLAGS) $< -o $@
sum_problem: Week1/sum.c  #$(OBJ) 
		$(CC) $(CFLAGS) $< -o $@
lpd_problem: Week1/LPD.c  #$(OBJ) 
		$(CC) $(CFLAGS) $< -o $@

# .PHONY: doc
# doc:
# 		doxygen doxygen.config
# 		rm -f doc.html
# 		ln -s doc/html/files.html doc.html


w1_runall:
	# @echo ''
	# @echo '* Problem 1 *'
	# @./w1_problem1

	# @echo ''
	# @echo '* Problem 2 *'
	# @./w1_problem2

	@echo ''
	@echo '* Problem 3 - Sum *'
	@./sum_problem Week1/sum_input_file

	@echo ''
	@echo '* Problem 4 - Longest Prime *'
	@./lpd_problem Week1/lpd_input_file
	#sum_input_file


.PHONY: clean

clean_problems:
	rm -f *_problem
clean_week1:
	rm -f w1_*

clean:
		rm -f build/*.o *~ parser/Lexer.c parser/Lexer.h parser/Parser.c parser/Parser.h equalPath graphParser Z3Example doc.html
		rm -rf doc
		rm -rf output
		rm -f w1_*