
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 50

typedef struct {
    char array[50];
    int top;
} stack_struct;

void push(stack_struct *stack, char value) {
    if(stack->top < MAX_LINES)
        stack->top +=1;
    else{
        fprintf(stderr, "Stack OVerflow\n");
        exit(EXIT_FAILURE);
    }
    stack->array[stack->top] = value;
}

char pop (stack_struct * stack){
    if(stack->top < 0){
        fprintf(stderr, "Stack Underflow\n");
        exit(EXIT_FAILURE);
    }

    char res = stack->array[stack->top];
    stack->top-=1;
    return res;
}

char isAlpha(char c)
{
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                      "abcdefghijklmnopqrstuvwxyz";
    char *letter = alphabet;

    while(*letter != '\0' && *letter != c)
        ++letter;

    if (*letter)
        return 1;

    return 0;
}

char isDigit(char c)
{
        if (c >= '0' && c <= '9')
                return c;
        else
                return 0;
}
int main (void){
    int number_of_tests = 0;
    // fprintf(stderr, "Number of tests to run: ");
    scanf("%d", &number_of_tests);
    // fprintf(stderr, "There will be %d Tests Case.\n", number_of_tests);


    stack_struct stack;
    stack.top = 0;

    char input_equation[MAX_LINES] = "";
    // push(&stack, '(');
    for(int i = 1; i < MAX_LINES-1; i++){
        input_equation[0] = '(';
        char c;
        int res = scanf("%c", &c);
        if(res == EOF || res ==0) {
            input_equation[i] = ')';
            input_equation[i+1] = '\0';
            break;
        }else{
            input_equation[i] = c;
        }
            
    }
    // strcat(input_equation, ')');
    printf("Input equation is: %s\n", input_equation);


    char equation[MAX_LINES];
    int i = 0;
    for(int nb_test = 0; nb_test < number_of_tests; nb_test++){
        // fprintf(stderr, "** Test %d over %d**\n", nb_test+1, number_of_tests);

        for(int j = 0; j < MAX_LINES+1; j++){
            equation[j] = '\0';
        }
        int priority = 0;
        int position = 0;

        char current_word = input_equation[position];
        do {
            position++;
            if(current_word == '('){
                priority++;
                // fprintf(stderr, "Priority +1\n");

                push(&stack, current_word);
            } else if (isDigit(current_word) || isAlpha(current_word)) {
                    printf("adding %c at indice %d!\nEquation is: %s\n", current_word, i, equation);

                    equation[i] = current_word;
                    i++;

            } else if (current_word == '*' || current_word == '/'){
                char op_res = pop(&stack);
                // while(op_res == '*' || op_res == '/') {
                    printf("adding %c at indice %d!\nEquation is: %s\n", current_word, i, equation);
                    equation[i] = op_res;
                    i++;
                //     op_res = pop(&stack);
                // }
                // push(&stack, op_res);
                push(&stack, op_res);
            } else if (current_word == '+' || current_word == '-'){
                char op_res = pop(&stack);
                // while(op_res == '+' || op_res == '-') {
                    equation[i] = op_res;
                    printf("adding %c at indice %d!\nEquation is: %s\n", current_word, i, equation);

                    i++;
                //     op_res = pop(&stack);
                // }
                // push(&stack, op_res);
                push(&stack, op_res);
            // } else if (current_word == '\n') {
            //     break;
                // fprintf(stderr, "????");
            } else if(current_word == ')') {
                priority--;
                // fprintf(stderr, "Priority -1\n");
                char res;
                while((res = pop(&stack)) != '(') {
                    
                    equation[i] = res;
                    i++;
                }
            } else {
            }

            // equation[position] = current_word;
            // position +=1;
            // printf("%s\n", equation);

        } while((current_word = input_equation[position]) != EOF);
        printf("%s\n", equation);


    }


    return 0;
}