/* Write a program using fork system call to create
a hierarchy of three processes such that P2 is child
of P1 and P1 is child of P */

#include <stdio.h>

int main(){
    // P
    printf("Root Process ID: %d\n", getpid());
    // P1 and P2
    if(fork() == 0){
        printf("Process ID: %d is child of %d\n", getpid(), getppid());
        if(fork() == 0)
            printf("Process ID: %d is child of %d\n", getpid(), getppid());
        else
            exit(0);
    }
    return 0;
}

/* TERMINAL
Root Process ID: 85
Process ID: 86 is child of 85
Process ID: 87 is child of 86
*/