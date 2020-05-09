# Makefile
# http://acm.cs.cityu.edu.hk/oj2/index.php/tag?name=&tags%5B%5D=assignment_2020b

FILESPARS	= $(wildcard parser/src/*.c)
FILESSRC	= $(wildcard src/*.c)
CC			= g++
CFLAGS		= -static -std=c++0x
OBJPARS		= $(FILESPARS:parser/src/%.c=build/%.o)
OBJSRC		= $(FILESSRC:src/%.c=build/%.o)
OBJ 		= $(OBJPARS) $(OBJSRC) 


TIMEOUT_CMD = timeout 5s
OUTPUT_FILE  = output.log
CONCAT_LOG  = >> $(OUTPUT_FILE)

OUTPUT_FILE_ASS  = output_ass.log
CONCAT_LOG_ASS  = >> $(OUTPUT_FILE_ASS)

.PHONY: all
all:assignment doing #completed doing 

assignment: assfinal_A assfinal_B assfinal_C assfinal_D assfinal_E assfinal_F 
assignment_old: ass02_A ass02_B ass02_C ass02_D ass02_E ass02_F ass01_F ass01_D ass01_bfs_problem run_assignment_problem # w1_problem1 w1_problem2 sum_problem lpd_problem w1_runall #doc
completed: 683_problem 108_problem 110_problem 142_problem 165_problem 168_problem 185_problem 192_problem 194_problem 251_problem 318_problem 381_problem 438_problem 449_problem 676_problem 688_problem run_completed_problems
doing: 212_problem 570_problem 621_problem 22_problem 462_problem 689_problem 381_problem 676_problem 362_problem 693_problem 190_problem 248_problem 222_problem 78_problem run_problems_current 



assfinal_A: Problems/Assignments/final/problem_A.c
		$(CC) $(CFLAGS) $< -o $@
assfinal_B: Problems/Assignments/final/problem_B.c
		$(CC) $(CFLAGS) $< -o $@
assfinal_C: Problems/Assignments/final/problem_C.c
		$(CC) $(CFLAGS) $< -o $@
assfinal_D: Problems/Assignments/final/problem_D.c
		$(CC) $(CFLAGS) $< -o $@
assfinal_E: Problems/Assignments/final/problem_E.c
		$(CC) $(CFLAGS) $< -o $@
assfinal_F: Problems/Assignments/final/problem_F.c
		$(CC) $(CFLAGS) $< -o $@



ass02_A: Problems/Assignments/old/ass02_A.c
		$(CC) $(CFLAGS) $< -o $@
ass02_B: Problems/Assignments/old/ass02_B.c
		$(CC) $(CFLAGS) $< -o $@
ass02_C: Problems/Assignments/old/ass02_C.c
		$(CC) $(CFLAGS) $< -o $@
ass02_D: Problems/Assignments/old/ass02_D.c
		$(CC) $(CFLAGS) $< -o $@
ass02_E: Problems/Assignments/old/ass02_E.c
		$(CC) $(CFLAGS) $< -o $@
ass02_F: Problems/Assignments/old/ass02_F.c
		$(CC) $(CFLAGS) $< -o $@

ass01_bfs_problem: Problems/Assignments/old/A01-bfs-easy.c
		$(CC) $(CFLAGS) $< -o $@
ass01_F: Problems/Assignments/old/A01-F.c
		$(CC) $(CFLAGS) $< -o $@
ass01_D: Problems/Assignments/old/A01-D.c
		$(CC) $(CFLAGS) $< -o $@







22_problem: Problems/22-prime.c
		$(CC) $(CFLAGS) $< -o $@
212_problem: Problems/212-bigmod.c
		$(CC) $(CFLAGS) $< -o $@
570_problem: Problems/570-highscore.c
		$(CC) $(CFLAGS) $< -o $@
689_problem: Problems/689-trends.c
		$(CC) $(CFLAGS) $< -o $@
438_problem: Problems/438-party.c
		$(CC) $(CFLAGS) $< -o $@
78_problem: Problems/78-largest-subsequence.c
		$(CC) $(CFLAGS) $< -o $@
190_problem: Problems/190-equation.c
		$(CC) $(CFLAGS) $< -o $@
248_problem: Problems/248-intersection.c
		$(CC) $(CFLAGS) $< -o $@
222_problem: Problems/222-simple-calculation.c
		$(CC) $(CFLAGS) $< -o $@
362_problem: Problems/362-winger-trials.c
		$(CC) $(CFLAGS) $< -o $@
449_problem: Problems/449-beach.c
		$(CC) $(CFLAGS) $< -o $@
693_problem: Problems/693-tower-of-hanoi.c
		$(CC) $(CFLAGS) $< -o $@
462_problem: Problems/462-euler.c
		$(CC) $(CFLAGS) $< -o $@
621_problem: Problems/621-rebuilding.c
		$(CC) $(CFLAGS) $< -o $@
683_problem: Problems/683-nuts.c
		$(CC) $(CFLAGS) $< -o $@




# DONE
194_problem: Problems/Accepted/194-eight-queens.c
		$(CC) $(CFLAGS) $< -o $@
381_problem: Problems/Accepted/381-hexadecimal.c
		$(CC) $(CFLAGS) $< -o $@
192_problem: Problems/Accepted/192-mobile.c
		$(CC) $(CFLAGS) $< -o $@
688_problem: Problems/Accepted/688-chess.c
		$(CC) $(CFLAGS) $< -o $@
142_problem: Problems/Accepted/142-friends.c
		$(CC) $(CFLAGS) $< -o $@
251_problem: Problems/Accepted/251-how-many-islands.c
		$(CC) $(CFLAGS) $< -o $@
110_problem: Problems/Accepted/110-longest-word.c
		$(CC) $(CFLAGS) $< -o $@
676_problem: Problems/Accepted/676-capital.c
		$(CC) $(CFLAGS) $< -o $@
185_problem: Problems/Accepted/185-dictionnary.c
		$(CC) $(CFLAGS) $< -o $@
108_problem: Problems/Accepted/108-birthday.c
		$(CC) $(CFLAGS) $< -o $@
168_problem: Problems/Accepted/168-networking.c
		$(CC) $(CFLAGS) $< -o $@
318_problem: Problems/Accepted/318-obstacle-course.c
		$(CC) $(CFLAGS) $< -o $@
165_problem: Problems/Accepted/165-frogger.c
		$(CC) $(CFLAGS) $< -o $@

###################

run_completed_problems:
	@echo '' > $(OUTPUT_FILE)
	@echo 'ACCEPTED PROBLEMS' $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 438 - Party *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./438_problem < Input/438-party.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 194 - Eight Queens *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./194_problem < Input/194-8queens.test $(CONCAT_LOG)
	@echo '* End Problem *'  $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 449 - Beach Length *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./449_problem < Input/449-beach.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 381 - Hexadecimal *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./381_problem < Input/381-hexadecimal.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 168 - Networking *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./168_problem < Input/168-networking.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 192 - Mobile *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./192_problem < Input/192-mobile.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 142 - Friends *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./142_problem < Input/142-friends.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 676 - Capital *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./676_problem < Input/676-capital.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 110 - Longest Word *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./110_problem < Input/110-longest-word.test $(CONCAT_LOG)
	@echo ''  $(CONCAT_LOG)
	@echo '* Problem 251 - How Many Islands *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./251_problem < Input/251-how-many-islands.test $(CONCAT_LOG)
	@echo ''  $(CONCAT_LOG)
	@echo '* Problem 185 - Dictionnary *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./185_problem < Input/185-dictionnary.test  $(CONCAT_LOG)
	@echo ''  $(CONCAT_LOG)
	@echo '* Problem 688 - Chess *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./688_problem < Input/688-chess.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 318 - Obstacle Course *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./318_problem < Input/318-obstacles.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 108 - Birthday *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./108_problem < Input/108-birthday.test $(CONCAT_LOG)
	@echo ''  $(CONCAT_LOG)
	@echo '* Problem 165 - Frogger *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./165_problem < Input/165-frogger.test $(CONCAT_LOG)
	@echo ''  $(CONCAT_LOG)
	@echo '* Problem 693 - Nuts *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./683_problem < Input/683-nuts.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)







run_problems_current:
	@echo '' > $(OUTPUT_FILE)
	@echo '' $(CONCAT_LOG)
	@echo 'UNFINISHED PROBLEMS' $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 212 - Big Mod *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./212_problem < Input/212-bigmod.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 248 - Intersection *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./248_problem < Input/248-intersection.test $(CONCAT_LOG)
	# @echo '' $(CONCAT_LOG)
	# @echo '* Problem 570 - Highscore *' $(CONCAT_LOG)
	# @$(TIMEOUT_CMD) ./570_problem < Input/570-highscore.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 621 - Rebuilding *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./621_problem < Input/621-rebuilding.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 693 - Hanoi *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./693_problem < Input/693-hanoi.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 22 - Prime Path *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./22_problem < Input/22-prime.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 462 - Euler *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./462_problem < Input/462-euler.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 689 - Trends *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./689_problem < Input/689-trends.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 190 - Equation *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./190_problem < Input/190-equation.test $(CONCAT_LOG)
	@echo '' $(CONCAT_LOG)
	@echo '* Problem 78 - Largest Subsequence *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./78_problem < Input/78-largest-subsequence.test $(CONCAT_LOG)
	@echo ''  $(CONCAT_LOG)
	@echo '* Problem 222 - Simple Calculation II *' $(CONCAT_LOG)
	@$(TIMEOUT_CMD) ./222_problem < Input/222-calculation.test $(CONCAT_LOG)
	@echo '* End Problem *'  $(CONCAT_LOG)






















run_assignment_problem:
	@echo '' > $(OUTPUT_FILE_ASS)
	@echo 'ASSIGNMENT PROBLEMS' $(CONCAT_LOG_ASS)
	@echo '' $(CONCAT_LOG_ASS)
	@echo '* Problem A *' $(CONCAT_LOG_ASS)
	@$(TIMEOUT_CMD) ./assfinal_A < Input/assfinal_A.test $(CONCAT_LOG_ASS)
	@echo '' $(CONCAT_LOG_ASS)
	@echo '* Problem B *' $(CONCAT_LOG_ASS)
	@$(TIMEOUT_CMD) ./assfinal_B < Input/assfinal_B.test $(CONCAT_LOG_ASS)
	@echo '' $(CONCAT_LOG_ASS)
	@echo '* Problem C *' $(CONCAT_LOG_ASS)
	@$(TIMEOUT_CMD) ./assfinal_C < Input/assfinal_C.test $(CONCAT_LOG_ASS)
	@echo '' $(CONCAT_LOG_ASS)
	@echo '* Problem D *' $(CONCAT_LOG_ASS)
	@$(TIMEOUT_CMD) ./assfinal_D < Input/assfinal_D.test $(CONCAT_LOG_ASS)
	@echo '' $(CONCAT_LOG_ASS)
	@echo '* Problem E *' $(CONCAT_LOG_ASS)
	@$(TIMEOUT_CMD) ./assfinal_E < Input/assfinal_E.test $(CONCAT_LOG_ASS)
	@echo '' $(CONCAT_LOG_ASS)
	@echo '* Problem F *' $(CONCAT_LOG_ASS)
	@$(TIMEOUT_CMD) ./assfinal_F < Input/assfinal_F.test $(CONCAT_LOG_ASS)

problems_doing:
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
	rm -f ass*_*
	# rm -f output.log
	rm -f output*.log