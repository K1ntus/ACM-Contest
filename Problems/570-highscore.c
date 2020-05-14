/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 121294
 * Submitted at:  2020-05-01 22:52:09
 *
 * User ID:       834
 * Username:      40128550
 * Problem ID:    570
 * Problem Name:  High Score
 */

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

#define __SIZE_ALPHA__ 26
#define __FIRST_CHAR__ 'A'
#define __LAST__CHAR__ 'Z'

#define __INFINITY__ 999999

#define __NO_DIRECTION__ 0

#define __FORWARD__  1
#define __BACKWARD__ 2

#define __LEFT__  3
#define __RIGHT__ 4


static char alphabet[__SIZE_ALPHA__] = {
    // C->Z 23
    // C->Z 3
    'A','B','C','D','E',
    'F','G','H','I','J',
    'K','L','M','N','O',
    'P','Q','R','S','T',
    'U','V','W','X','Y',
    'Z'};

int NextLetter(int current_letter_position, int move_type);
int NextPosition(int current_position, int size_name, int move_type);
char * InitScoreName(int size);
int CharToDigit(char current_char);
int SolveScoreboard(char * user_name, char * score_name, const int size, int nb_move, int current_position, int direction,int prev_pos, int prev_prev_pos);



int bestscore = __INFINITY__-1;


int main (void) {
    int __nb_people__; 

    string line;
    getline(cin, line);
    stringstream myString(line);
    myString >> __nb_people__;


    for(int people_number = 0; people_number < __nb_people__; people_number++){
        bestscore = __INFINITY__;
        getline(cin, line);

        int __size_name = line.size();
        stringstream myString(line);

        char * nickname = (char *) malloc(sizeof(char) * __size_name);
        myString >> nickname;

        char * scorename = InitScoreName(__size_name);

        int res = SolveScoreboard(nickname, scorename, __size_name, 0, 0, 0, __NO_DIRECTION__, __NO_DIRECTION__) - 1;
        // if(res < 0) { res = 0; }

        // res = res - 1;
        // if(res%2 == 0) { res = res - 1;}
        // if(res < 0) { res = 0; }
        printf("%d\n", res);
        // printf("RES:%d\n", res);
        // printf("------------------------------------------\n");
    }

    return EXIT_SUCCESS;
}




int returnMinValue(int left, int right);
void ResetLetterAtPosition(char * array, int pos);
int NbMovesToSolvePosition(char requested_char, char current_char);
int SimulateNextMove(char * user_name, char* score_name, int size, int nb_move, int position, int score, int prev_pos, int prev_prev_pos);
int heuristic(char * score_name, int position, int score);

int SolveScoreboard(char * user_name, char * score_name, const int size, int nb_move, int current_position, int current_score, int prev_pos, int prev_prev_pos) {       
    if(current_position > size || current_position < 0) { return __INFINITY__; }
    if(nb_move > 2*size) { return __INFINITY__; }

    if(strcmp(user_name, score_name) == 0) {
        // printf("Find similar word depth %d\n", nb_moves);
        // printf("---\ninput: [%s]\ncomparaison: [%s]\n---\n", user_name, score_name);
        // score_name[current_position] = 'A';
        return heuristic(score_name, current_position, current_score);
    }

    current_score += NbMovesToSolvePosition(user_name[current_position], score_name[current_position]) + 1;
    score_name[current_position] = user_name[current_position];

    if(current_score  >= bestscore) {
        ResetLetterAtPosition(score_name, current_position);
        return __INFINITY__;
    }

    int res = SimulateNextMove(user_name, score_name, size, nb_move+1, current_position, current_score, prev_pos, prev_prev_pos);
    ResetLetterAtPosition(score_name, current_position);

    return res;
}




int heuristic(char * score_name, int position, int score) {
        if(score  >= bestscore) {
            ResetLetterAtPosition(score_name, position);
            return __INFINITY__;
        }

        bestscore = score;
        if(bestscore == 2) { return 2;}
        if(bestscore == 1) { return 2;}
        if(bestscore == 0) { return 1;}
        return bestscore - 1;
}


int SimulateNextMove(char * user_name, char* score_name, int size, int nb_move, int position, int score, int prev_pos, int prev_prev_pos) {

    int position_left =  NextPosition(position, size, __LEFT__); 
    int position_right =  NextPosition(position, size, __RIGHT__); 
    int nb_move_left = __INFINITY__;
    int nb_move_right = __INFINITY__;
    
    if(prev_prev_pos == __LEFT__) {
        if(prev_pos == __RIGHT__) {
            //DONOT LEFT
            nb_move_right = SolveScoreboard(user_name, score_name, size, nb_move, position_right, score, __RIGHT__, prev_pos);
        } else {
            nb_move_left  = SolveScoreboard(user_name, score_name, size, nb_move, position_left, score, __LEFT__, prev_pos);
            nb_move_right = SolveScoreboard(user_name, score_name, size, nb_move, position_right, score, __RIGHT__, prev_pos);
        }
    } else if(prev_prev_pos == __RIGHT__) {
        if(prev_pos == __LEFT__) {
            //DONOT RIGHT
            nb_move_left  = SolveScoreboard(user_name, score_name, size, nb_move, position_left, score, __LEFT__, prev_pos);
        } else {
            nb_move_left  = SolveScoreboard(user_name, score_name, size, nb_move, position_left, score, __LEFT__, prev_pos);
            nb_move_right = SolveScoreboard(user_name, score_name, size, nb_move, position_right, score, __RIGHT__, prev_pos);
        }
    } else {
            nb_move_left  = SolveScoreboard(user_name, score_name, size, nb_move, position_left, score, __LEFT__, prev_pos);
            nb_move_right = SolveScoreboard(user_name, score_name, size, nb_move, position_right, score, __RIGHT__, prev_pos);
    }

    // printf("Comparing at depth %d: %d + %d.\n", nb_moves + 1, current_score, nb_moves_required);
    // nb_move_left  = SolveScoreboard(user_name, score_name, size, position_left, score, __LEFT__, prev_pos);
    // nb_move_right = SolveScoreboard(user_name, score_name, size, position_right, score, __RIGHT__, prev_pos);

    return returnMinValue(nb_move_left, nb_move_right);
}


int CharToDigit(char current_char) {
    switch(current_char) {
        case 'A':
            return 0;
        case 'B':
            return 1;
        case 'C':
            return 2;
        case 'D':
            return 3;
        case 'E':
            return 4;
        case 'F':
            return 5;
        case 'G':
            return 6;
        case 'H':
            return 7;
        case 'I':
            return 8;
        case 'J':
            return 9;
        case 'K':
            return 10;
        case 'L':
            return 11;
        case 'M':
            return 12;
        case 'N':
            return 13;
        case 'O':
            return 14;
        case 'P':
            return 15;
        case 'Q':
            return 16;
        case 'R':
            return 17;
        case 'S':
            return 18;
        case 'T':
            return 19;
        case 'U':
            return 20;
        case 'V':
            return 21;
        case 'W':
            return 22;
        case 'X':
            return 23;
        case 'Y':
            return 24;
        case 'Z':
            return 25;
        default:
            return 26;
    }
    return 26;
}



int NbMovesToSolvePosition(char requested_char, char current_char) {
    int id_req_char = CharToDigit(requested_char);
    int id_cur_char = CharToDigit(current_char);
    int offset_requested_char = __SIZE_ALPHA__ - id_req_char;



    int nbmove_left = offset_requested_char + id_cur_char;
    int nbmove_right = id_req_char - id_cur_char;

    return returnMinValue(nbmove_left, nbmove_right);
}

void ResetLetterAtPosition(char * array, int pos) {
    array[pos] = __FIRST_CHAR__;
}

int NextLetter(int current_letter_position, int move_type) {    // Forward|Backward
    if(move_type == __FORWARD__) {
        current_letter_position++;
    } else {
        current_letter_position--;
    }
    if(alphabet[current_letter_position] > __SIZE_ALPHA__ - 1) {
        current_letter_position = 0;
    } else if (alphabet[current_letter_position] < 0) {
        current_letter_position = __SIZE_ALPHA__ - 1;
    }

    return current_letter_position;
}

int NextPosition(int current_position, int size_name, int move_type) { // Left|Right
    if(move_type == __LEFT__) {
        current_position -=1;
    } else {
        current_position +=1;
    }

    if(current_position < 0) {
        current_position = size_name;
    } else if (current_position > size_name) {
        current_position = 0;
    }

    return current_position;
}



char * InitScoreName(int size) {
    char * array = (char *) malloc(sizeof(char) * size);

    for(int i = 0; i < size; i++) {
        array[i] = __FIRST_CHAR__;
    }

    return array;
}



int returnMinValue(int left, int right) {
    if(left < right) {
        return left;
    }
    return right;
}