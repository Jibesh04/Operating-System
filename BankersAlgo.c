/* 30.10.23 P2: Banker's Algorithm */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int needSatisfied(int* need, int n){
	for(int i = 0; i < n; i++)
		if(need[i])
			return 0;
	return 1;
}

int isLessthan(int* need, int* work, int n){
	for(int i = 0; i < n; i++)
		if(need[i] > work[i])
			return 0;
	return 1;
}

int addTo(int* alloc, int* work, int n){
	for(int i = 0; i < n; i++)
		work[i] += alloc[i];
}

int allFinished(int* finish, int n){
	for(int i = 0; i < n; i++)
		if(finish[i] == 0)
			return 0;
	return 1;
}

int main(){
	int nP; // number of processes
	printf("Enter number of Processes: ");
	scanf("%d", &nP);
	int nR; // number of resource types
	printf("Enter number of Resource Types: ");
	scanf("%d", &nR);
	int avI[nR]; // Available initial resources
	printf("Enter number of Available initial resources of\n");
	for(int i = 0; i < nR; i++){\
		printf("Type %d: ", i + 1);
		scanf("%d", &avI[i]);
	}
	int work[nR]; // work
	for(int i = 0; i < nR; i++)
		work[i] = avI[i];
	int maxN[nP][nR]; // max need
	printf("Enter maximum need of each resource type for\n");
	for(int i = 0; i < nP; i++){
		printf("Process %d: ", i + 1);
		for(int j = 0; j < nR; j++)
			scanf("%d", &maxN[i][j]);
	}
	int alloc[nP][nR]; // allocation
	printf("Enter allocation of each resource type for\n");
	for(int i = 0; i < nP; i++){
		printf("Process %d: ", i + 1);
		for(int j = 0; j < nR; j++){
			scanf("%d", &alloc[i][j]);
			work[j] -= alloc[i][j];	
		}
	}
	int need[nP][nR]; // need
	for(int i = 0; i < nP; i++)
		for(int j = 0; j < nR; j++)
			need[i][j] = maxN[i][j] - alloc[i][j];
	int finish[nP]; // finish
	// int nPendingP; // Pending Processes
	for(int i = 0; i < nP; i++)
		if(needSatisfied(need[i], nR))
			finish[i] = 1;
		else{
			finish[i] = 0;
			// nPendingP++;	
		}
	printf("Running Banker's Algorithm\n");
	int flag = 0, cnt, idx = 0;
	while(1){
		if(finish[idx] == 0 && isLessthan(need[idx], work, nR)){
			flag = 0;
			addTo(alloc[idx], work, nR);
			finish[idx] = 1;
			// nPendingP--;
			// flag = nPendingP;
			memset(need[idx], 0, sizeof(need[idx]));
			printf("Finished Process %d\nWork: ", idx + 1);
			for(int i = 0; i < nR; i++)
				printf("%d\t", work[i]);
			printf("\n");
			if(allFinished(finish, nP))
				break;
		}
		else{
			idx = (idx + 1) % nP;
			while(finish[idx])
				idx = (idx + 1) % nP;
			flag++;
		}
		if(flag == nP)
			break;
	}
	if(flag){
		printf("Deadlock is Detected\n");
		printf("Need Matrix\n");
		for(int i = 0; i < nP; i++){
			printf("Process %d isFinished? %s\n", i + 1, finish[i] == 0 ? "No" : "Yes");
			for(int j = 0; j < nR; j++)
				printf("%d\t", need[i][j]);
			printf("\n");	
		}
	}
	else
		printf("There is no Deadlock\n");
	return 0;
}

/* TERMINAL
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ gcc -o deadlockDetect.exe deadlockDetect.c 
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ ./deadlockDetect.exe 
Enter number of Processes: 5
Enter number of Resource Types: 3
Enter number of Available initial resources of
Type 1: 10
Type 2: 5
Type 3: 7
Enter maximum need of each resource type for
Process 1: 7 5 3
Process 2: 3 2 2
Process 3: 9 0 2
Process 4: 2 2 2
Process 5: 4 3 3
Enter allocation of each resource type for
Process 1: 0 1 0
Process 2: 2 0 0
Process 3: 3 0 2
Process 4: 2 1 1
Process 5: 0 0 2
Running Banker's Algorithm
Finished Process 2
Work: 5	3	2	
Finished Process 4
Work: 7	4	3	
Finished Process 5
Work: 7	4	5	
Finished Process 1
Work: 7	5	5	
Finished Process 3
Work: 10	5	7	
There is no Deadlock
*/
