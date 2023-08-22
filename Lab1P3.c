#include <stdio.h>

int main(){
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sum = 0;
	if(fork() == 0){
		for(int i = 0; i < sizeof(arr)/sizeof(int); i++)
			if(arr[i]&1)
				sum += arr[i];
		printf("From child process with ID %d evaluated sum of odd elements: %d\n", getpid(), sum);
	}
	else{
		for(int i = 0; i < sizeof(arr)/sizeof(int); i++)
			if(!(arr[i]&1))
				sum += arr[i];
		printf("From parent process with ID %d evaluated sum of even elements: %d\n", getppid(), sum);
	}
	return 0;
}

/* TERMINAL
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ gcc -o Lab1P3.exe Lab1P3.c
Lab1P3.c: In function ‘main’:
Lab1P3.c:5:12: warning: implicit declaration of function ‘fork’ [-Wimplicit-function-declaration]
    5 |         if(fork() == 0){
      |            ^~~~
Lab1P3.c:9:93: warning: implicit declaration of function ‘getpid’ [-Wimplicit-function-declaration]
    9 |                 printf("From child process with ID %d evaluated sum of odd elements: %d\n", getpid(), sum);
      |                                                                                             ^~~~~~
Lab1P3.c:15:95: warning: implicit declaration of function ‘getppid’ [-Wimplicit-function-declaration]
   15 |                 printf("From parent process with ID %d evaluated sum of even elements: %d\n", getppid(), sum);
      |                                                                                               ^~~~~~~
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ ./Lab1P3.exe
From parent process with ID 770381 evaluated sum of even elements: 30
From child process with ID 770820 evaluated sum of odd elements: 25
*/
