#include<stdio.h>

int tower(int no,char a,char b,char c, int nb_steps);

int main() {
    int no;
    printf("Enter total number of disks:");
    scanf("%d",&no);
    int res = tower(no,'A','B','C', 0);

    printf("%d move required\n");
    return 0;
}

int tower(int no,char a,char b,char c, int nb_steps) {
    if(no>0) {
        tower(no-1,a,c,b, nb_steps +1);
        printf("%c->%c\n",a,c);
        tower(no-1,b,a,c, nb_steps + 1);
    }

    return nb_steps;
}