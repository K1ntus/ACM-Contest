
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
#include <stddef.h>


using namespace std;

#define MAX_CHAR 100
#define MAX_ELEMS 10
#define MIN_ELEMS 1

#define __PRECISION__ 0.00001
bool fgreater(long double a, long double b) {
    return fabs(fabs(a)-fabs(b)) > __PRECISION__;
}


int main (void){
    char tmp_buffer[MAX_CHAR];
    long double result = 0.0;

    char *eof_checker;
    int consecutive_case = 0;

    while(eof_checker = fgets(tmp_buffer, MAX_CHAR, stdin)) {
        if(!eof_checker) break;
        else if(!strcmp(tmp_buffer, "\n")) continue;
        else if(eof_checker[0] == EOF) break;
        else
            if(consecutive_case > 0) printf("\n");// && tmp_buffer[0] != EOF) printf("\n");
            else consecutive_case = 1;

        char * buffer = (char *) malloc(MAX_CHAR * sizeof(char));
        strcpy(buffer, tmp_buffer);

        for(int j = 0; j < MAX_ELEMS; j++){
            if(buffer[0] == '\n') break;
            // result += strtold(buffer, &buffer);
            result += strtod(buffer, &buffer);
            // printf("Value is : %Lf\n", result);
        }
        long double saving_result = result * 10000.0;
        saving_result = floor(saving_result);
        saving_result = trunc(saving_result);
        long double tmp_result = result * 10000.0;
        if (fgreater(tmp_result, saving_result)){
            // printf("Result is: %Lf, other one is: %Lf\n", tmp_result, saving_result);
            saving_result += 1;
        } 
        result = saving_result / 10000.0; 
            // printf("Final Value is : %.4Lf\n", result);
        fprintf(stdout, "%.4Lf\n", result);// (long double) ((long int) floorl( 10000*(result))) / 10000);

        result = 0.0;


        
        // char * tok = strtok(buffer, " ");
        
        // int j = 0;
        // while (tok != NULL && tok != "\n" && j < MAX_ELEMS) {
        //     if(tok != 0x0)
        //         result += strtold(tok, NULL);
        //     tok = strtok (NULL, " ");
        //     j++;
        // }
        
        // result *= 10000;
        // printf("previous result:%Lf\n", result);
        
        // long double final_result = floor(result * 10000.0)/10000.0;
        // if(final_result < result){

        //     printf("Current result: %Lf\nRounded result: %Lf\n", final_result, result);
        //     final_result += 0.0001;
        // }
        // // printf("%Lf->", result);
        // long double tmp_result = floorl(result);
        // if (tmp_result < result) {
        //     tmp_result+=1;
        // }
        // result = tmp_result;
        // result = truncl(result);
        // // printf("%Lf->", result);
        // result = result / 10000.0;
        // // result /= 10000;
        // char res_buffer[1024];
        // sprintf(res_buffer, "%Lf\n", final_result);
        // int i = 0;
        // while(res_buffer[i] != '.' && i < 10){
        //     printf("%c", res_buffer[i]);
        //     i+=1;
        // }
        
        // for(; i < 4; i++) {
        //     printf("%c", res_buffer[i]);
        // }
        // printf("\n");
        // // std::cout.unsetf ( std::ios::floatfield );                // floatfield not set
        // // std::cout.precision(4);
        // // std::cout << final_result << '\n';

        // std::cout.unsetf ( std::ios::floatfield );  
        // cout.precision(4);
        // double tmp = dround(result,4);
        // // if(result - tmp >0) tmp += 0.0001;
        // cout << fixed << tmp << endl;
        // long long tmp_result = ( (long long) (ceil(result * 10000)));
        // tmp_result = trunc(tmp_result);
        // // if(tmp_result < result) tmp_result += 0.0001;
        // result =(long double) (tmp_result / 10000.0);
        // std::cout << prd(result,4) << std::endl;
        // truncl(result);
        // // result = result / 10000.0;
        // double dround(double val, int dp)
        // fprintf(stdout, "%.4Lf\n", result);// (long double) ((long int) floorl( 10000*(result))) / 10000);
        result = 0.0;

        // free(tok);
        // free(buffer);
    }
    
    return EXIT_SUCCESS;
}