# Makefile
# http://acm.cs.cityu.edu.hk/oj2/index.php/tag?name=&tags%5B%5D=assignment_2020b

FILESPARS	= $(wildcard parser/src/*.c)
FILESSRC	= $(wildcard src/*.c)
CC			= g++
CFLAGS		= -static -std=c++0x
OBJPARS		= $(FILESPARS:parser/src/%.c=build/%.o)
OBJSRC		= $(FILESSRC:src/%.c=build/%.o)
OBJ 		= $(OBJPARS) $(OBJSRC) 
OUTPUT_FILE  = output.log
CONCAT_LOG  = >> $(OUTPUT_FILE)

OUTPUT_FILE_ASS  = output_ass.log
CONCAT_LOG_ASS  = >> $(OUTPUT_FILE_ASS)

.PHONY: all
all:graph_sample_problem 165_problem 676_problem 362_problem 449_problem 693_problem 185_problem 251_problem 318_problem 688_problem 438_problem 194_problem 110_problem 190_problem 248_problem 222_problem 78_problem problems_current #ass02_A ass02_B ass02_C ass02_D ass02_E ass02_F ass01_F ass01_D ass01_bfs_problem# clean_week1 w1_problem1 w1_problem2 sum_problem lpd_problem w1_runall #doc

ass02_A: Problems/Assignments/ass02_A.c
		$(CC) $(CFLAGS) $< -o $@
ass02_B: Problems/Assignments/ass02_B.c
		$(CC) $(CFLAGS) $< -o $@
ass02_C: Problems/Assignments/ass02_C.c
		$(CC) $(CFLAGS) $< -o $@
ass02_D: Problems/Assignments/ass02_D.c
		$(CC) $(CFLAGS) $< -o $@
ass02_E: Problems/Assignments/ass02_E.c
		$(CC) $(CFLAGS) $< -o $@
ass02_F: Problems/Assignments/ass02_F.c
		$(CC) $(CFLAGS) $< -o $@

ass01_bfs_problem: Problems/Assignments/A01-bfs-easy.c
		$(CC) $(CFLAGS) $< -o $@
ass01_F: Problems/Assignments/A01-F.c
		$(CC) $(CFLAGS) $< -o $@
ass01_D: Problems/Assignments/A01-D.c
		$(CC) $(CFLAGS) $< -o $@


165_problem: Problems/165-frogger.c
		$(CC) $(CFLAGS) $< -o $@
438_problem: Problems/438-party.c
		$(CC) $(CFLAGS) $< -o $@
78_problem: Problems/78-largest-subsequence.c
		$(CC) $(CFLAGS) $< -o $@
190_problem: Problems/190-equation.c
		$(CC) $(CFLAGS) $< -o $@
194_problem: Problems/194-eight-queens.c
		$(CC) $(CFLAGS) $< -o $@
248_problem: Problems/248-intersection.c
		$(CC) $(CFLAGS) $< -o $@
222_problem: Problems/222-simple-calculation.c
		$(CC) $(CFLAGS) $< -o $@
318_problem: Problems/318-obstacle-course.c
		$(CC) $(CFLAGS) $< -o $@
362_problem: Problems/362-winger-trials.c
		$(CC) $(CFLAGS) $< -o $@
449_problem: Problems/449-beach.c
		$(CC) $(CFLAGS) $< -o $@
688_problem: Problems/688-chess.c
		$(CC) $(CFLAGS) $< -o $@
693_problem: Problems/693-tower-of-hanoi.c
		$(CC) $(CFLAGS) $< -o $@

# DONE
251_problem: Problems/Accepted/251-how-many-islands.c
		$(CC) $(CFLAGS) $< -o $@
110_problem: Problems/Accepted/110-longest-word.c
		$(CC) $(CFLAGS) $< -o $@
676_problem: Problems/Accepted/676-capital.c
		$(CC) $(CFLAGS) $< -o $@
185_problem: Problems/Accepted/185-dictionnary.c
		$(CC) $(CFLAGS) $< -o $@

###################
problems_current:

	@echo '' > $(OUTPUT_FILE_ASS)
	@echo 'ASSIGNMENT PROBLEMS' $(CONCAT_LOG_ASS)
	@echo '' $(CONCAT_LOG_ASS)
	@echo '* Problem A *' $(CONCAT_LOG_ASS)
	@./ass02_A < Input/ass02_A.test $(CONCAT_LOG_ASS)
	@echo '' $(CONCAT_LOG_ASS)
	@echo '* Problem B *' $(CONCAT_LOG_ASS)
	@./ass02_B < Input/ass02_B.test $(CONCAT_LOG_ASS)
	@echo '' $(CONCAT_LOG_ASS)
	@echo '* Problem C *' $(CONCAT_LOG_ASS)
	@./ass02_C < Input/ass02_C.test $(CONCAT_LOG_ASS)
	@echo '' $(CONCAT_LOG_ASS)
	@echo '* Problem D *' $(CONCAT_LOG_ASS)
	@./ass02_D < Input/ass02_D.test $(CONCAT_LOG_ASS)
	@echo '' $(CONCAT_LOG_ASS)
	@echo '* Problem E *' $(CONCAT_LOG_ASS)
	@./ass02_E < Input/ass02_E.test $(CONCAT_LOG_ASS)
	@echo '' $(CONCAT_LOG_ASS)
	@echo '* Problem F *' $(CONCAT_LOG_ASS)
	@./ass02_F < Input/ass02_F.test $(CONCAT_LOG_ASS)


	@echo '' > $(OUTPUT_FILE)
	@echo 'ACCEPTED PROBLEMS' $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 676 - Capital *' $(CONCAT_LOG)
	@./676_problem < Input/676-capital.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 110 - Longest Word *' $(CONCAT_LOG)
	@./110_problem < Input/110-longest-word.test $(CONCAT_LOG)
	@echo ''  $(CONCAT_LOG)
	@echo '* Problem 251 - How Many Islands *' $(CONCAT_LOG)
	@./251_problem < Input/251-how-many-islands.test $(CONCAT_LOG)
	@echo ''  $(CONCAT_LOG)
	@echo '* Problem 185 - Dictionnary *' $(CONCAT_LOG)
	@./185_problem < Input/185-dictionnary.test  $(CONCAT_LOG)
	@echo ''  $(CONCAT_LOG)


	@echo '' $(CONCAT_LOG)
	@echo 'UNFINISHED PROBLEMS' $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 165 - Frogger *' $(CONCAT_LOG)
	@./165_problem < Input/165-frogger.test $(CONCAT_LOG)
	@echo '* End Problem *'  $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 449 - Beach Length *' $(CONCAT_LOG)
	@./449_problem < Input/449-beach.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 78 - Largest Subsequence *' $(CONCAT_LOG)
	@./78_problem < Input/78-largest-subsequence.test $(CONCAT_LOG)
	@echo ''  $(CONCAT_LOG)
	@echo '* Problem 222 - Simple Calculation II *' $(CONCAT_LOG)
	@./222_problem < Input/222-calculation.test $(CONCAT_LOG)
	@echo ''  $(CONCAT_LOG)
	@echo '* Problem 688 - Chess *' $(CONCAT_LOG)
	@./688_problem < Input/688-chess.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 438 - Party *' $(CONCAT_LOG)
	@./438_problem < Input/438-party.test $(CONCAT_LOG)
	@echo '* End Problem *'  $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 194 - Eight Queens *' $(CONCAT_LOG)
	@./194_problem < Input/194-8queens.test $(CONCAT_LOG)
	@echo '* End Problem *'  $(CONCAT_LOG)

	@echo '* Problem 362 - Winger Trial *' $(CONCAT_LOG)
	@./362_problem < Input/362-winger-trial.test $(CONCAT_LOG)
	@echo '* End Problem *'  $(CONCAT_LOG)

problems_doing:
	# @echo '' > $(OUTPUT_FILE_ASS)
	# @echo 'ASSIGNMENT PROBLEMS' $(CONCAT_LOG_ASS)
	# @echo '' $(CONCAT_LOG_ASS)
	# @./ass01_bfs_problem < Input/a01-bfs.test $(CONCAT_LOG)
	# # @echo '' $(CONCAT_LOG_ASS)
	# # @./ass01_F < Input/ass01_F.test $(CONCAT_LOG)
	# @echo '' $(CONCAT_LOG_ASS)
	# @./ass01_D < Input/ass01_D.test # $(CONCAT_LOG)





	
	# @echo ''
	# @echo '* Problem 693 - Towers Of Hanoi *'
	# @./693_problem
	# @echo ''
	# @echo '* Problem 78 - Largest Subsequence *'
	# # @./78_problem
	# @echo ''
	# @echo '* Problem 190 - Equations *'
	# @./190_problem
	# @echo ''
	# @echo '* Problem 318 - Obstacle Course *'
	# @./318_problem
	@echo ''
	@echo '* Problem 194 - Eight Queens *'
	@./194_problem
	@echo ''
	@echo '* Problem 190 - Equations *'
	@./190_problem
	@echo ''
	@echo '* Problem 248 - Intersections *'
	@./248_problem
	@echo ''
	@echo '* Problem 78 - Largest Subsequence *'
	@./78_problem
	@echo ''


w1_problem1: Week1/countprime_3.c #$(OBJ) 
		$(CC) $(CFLAGS) $< -o $@

w1_problem2: Week1/countprime_4.c  #$(OBJ) 
		$(CC) $(CFLAGS) $< -o $@
sum_problem: Week1/sum.c  #$(OBJ) 
		$(CC) $(CFLAGS) $< -o $@
lpd_problem: Week1/LPD.c  #$(OBJ) 
		$(CC) $(CFLAGS) $< -o $@

graph_sample_problem: Problems/Sample/sample_program_graphs.c
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
	rm -f *_problem
	# rm -f output.log
	rm -f output*.log