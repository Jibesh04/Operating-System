#include <stdio.h>

int main(){
	int a;
	// In C, function takes argument from R.H.S. so first line of fork() will give appropriate process type
	printf("%s\tReturn Value: %d\n", a == 0 ? "child process" : "parent process", a = fork());
	// But this is not correct as value of a is first checked then assigned
	printf("Return Value: %d\t%s\n", a = fork(), a == 0 ? "child process" : "parent process");
	return 0;
}


/* TERMINAL
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ gcc -o Lab1P2.exe Lab1P2.c
Lab1P2.c: In function ‘main’:
Lab1P2.c:5:92: warning: implicit declaration of function ‘fork’ [-Wimplicit-function-declaration]
    5 |         printf("%s\tReturn Value: %d\n",  a == 0 ? "child process" : "parent process", a = fork());
      |                                                                                            ^~~~
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ ./Lab1P2.exe
parent process	Return Value: 770728
child process	Return Value: 0
Return Value: 770729	parent process
Return Value: 0	parent process
Return Value: 770730	child process
Return Value: 0	child process
*/
