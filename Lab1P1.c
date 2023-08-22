#include <stdio.h>

int main(){
	printf("Oh my Supreme Lord!\n");
	fork();
	printf("Shree Ganeshaaya Namah!\n");
	fork();
	printf("Save us!\n");
	return 0;
}

/* TERMINAL
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ gcc -o Lab1P1.exe Lab1P1.c
Lab1P1.c: In function ‘main’:
Lab1P1.c:5:9: warning: implicit declaration of function ‘fork’ [-Wimplicit-function-declaration]
    5 |         fork();
      |         ^~~~
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ ./Lab1P1.exe
Oh my Supreme Lord!
Shree Ganeshaaya Namah!
Shree Ganeshaaya Namah!
Save us!
Save us!
Save us!
Save us!
*/
