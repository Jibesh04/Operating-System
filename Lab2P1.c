/* Write a program using fork system call
to create two child of a same process */

#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("Root Process ID: %d\n", getpid());
    for(int i = 0; i < 2; i++){
        int a = fork();
        if(a == 0){
            printf("Parent ID: %d\tCurrent Process ID: %d\n", getppid(), getpid());
            exit(0);
        }
    }
    return 0;
}

/* TERMINAL
Root Process ID: 4703
Parent ID: 4703	Current Process ID: 4704
Parent ID: 4703	Current Process ID: 4705
*/