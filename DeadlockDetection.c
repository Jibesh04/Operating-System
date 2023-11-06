/* 30.10.23 P1: Deadlock Detection */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX 10

int nP, nR;
int request[MAX][MAX], alloc[MAX][MAX];
int available[MAX];

void inputMat(char * stmt, int mat[MAX][MAX]){
	printf("%s", stmt);
	for(int i = 0; i < nP; i++)
		for(int j = 0; j < nR; j++)
			scanf("%d", &mat[i][j]);
}

void inputArr(char * stmt, int arr[MAX]){
	printf("%s", stmt);
	for(int i = 0; i < nR; i++)
		scanf("%d", &arr[i]);
}

void detectDeadlock(){
	int finish[nP];
	memset(finish, 0, sizeof(finish));
	int flag;
	for(int i = 0; i < nP; i++){
		flag = 1;
		for(int j = 0; j < nR; j++)
			if(alloc[i][j]){
				flag = 0;
				break;
			}
		if(flag)
			finish[i] = 1;
	}
	int work[nR];
	memcpy(work, available, sizeof(available));
	for(int i = 0; i < nP; i++)
		for(int j = 0; j < nR; j++)
			work[j] -= alloc[i][j];	
	for(int i = 0; i < nP; i++){
		if(!finish[i]){
			flag = 1;
			for(int j = 0; j < nR; j++)
				if(request[i][j] > work[j]){
					flag = 0;
					break;
				}
			if(flag){
				finish[i] = 1;
				printf("Process %d is finished\n", i + 1);
				for(int j = 0; j < nR; j++){
					work[j] += alloc[i][j];
					request[i][j] = 0;
				}
				i = -1;
			}
		}
	}
	flag = 1;
	for(int i = 0; i < nP; i++)
		for(int j = 0; j < nR; j++)
			if(request[i][j]){
				printf("Process %d is not finished\n", i + 1);
				flag = 0;
				break;
			}
	if(flag)
		printf("The System is in Safe State\n");
	else
		printf("The System is in Deadlock\n");
}

int main(){
	printf("Enter number of Processes: ");
	scanf("%d", &nP);
	printf("Enter number of Resource Types: ");
	scanf("%d", &nR);
	inputMat("Enter request matrix\n", request);
	inputMat("Enter allocation matrix\n", alloc);
	inputArr("Enter available instances of each resource type: ", available);
	detectDeadlock();
	return 0;
}

/* TERMINAL
PS D:\Junior\Study\Operating-System> gcc -o DeadlockDetection.exe ./DeadlockDetection.c
PS D:\Junior\Study\Operating-System> .\DeadlockDetection.exe
Enter number of Processes: 5
Enter number of Resource Types: 3
Enter request matrix
0 0 0
2 0 2
0 0 0
1 0 0
0 0 2
Enter allocation matrix
0 1 0
2 0 0 
3 0 3
2 1 1
0 0 2
Enter available instances of each resource type: 7 2 6
Process 1 is finished
Process 3 is finished
Process 2 is finished
Process 4 is finished
Process 5 is finished
The System is in Safe State
*/