/* Priority Preemptive */
#include <iostream>
#include <vector>
#include <queue>
// #include <limits.h>
using namespace std;

struct Process{
	int pid, arr, bt, idx;
	bool inQueue = false;	
};

int comp(const void* P1, const void* P2){
	int t1 = ((Process *)P1) -> arr;
	int t2 = ((Process *)P2) -> arr;
	return t1 - t2;
}

void PrintProc(Process P[], int n, int comp[], int tat[], int wt[]){
	cout<<"PID\tArr\tBt\tComp\tTAT\tWT"<<endl;
	for(int i = 0; i < n; i++)
		cout<<P[i].pid<<"\t"<<P[i].arr<<"\t"<<P[i].bt<<"\t"<<comp[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<endl;
}

void evaluateTimeRR(Process P[], int n, int q, float & av_WT, float & av_TAT){
	qsort(P, n, sizeof(P[0]), comp);
	vector<int> Gantt;
	queue<Process> rq;
	int rem[n], comp[n], tat[n], wt[n];
	for(int i = 0; i < n; i++){
		P[i].idx = i;
		rem[i] = P[i].bt;
	}
	int i = 0, t = P[0].arr;
	int n_cmp = 0;
	Process curr;
	rq.push(P[0]);
	P[0].inQueue = true;
	/*
	while(n_cmp < n){
		cout<<P[i].pid<<" considered"<<endl;
		if(!rem[i] || P[i].arr > t){
			i = (i + 1) % n;
			continue;
		}
		if(rem[i] < q){
			t += rem[i];
			comp[i] = t;
			rem[i] = 0;
			n_cmp++;
		}
		else{
			t += q;
			rem[i] -= q;
			if(!rem[i]){
				comp[i] = t;
				n_cmp++;		
			}
		}
		cout<<"Time: "<<t<<" : Process: "<<P[i].pid<<endl;
		Gantt.push_back(P[i].pid);
		i = (i + 1) % n;
	} */
	while(!rq.empty()){
		curr = rq.front();
		rq.pop();
		curr.inQueue = false;
		i = curr.idx;
		for(int j = 0; j < n; j++)
			if(P[j].arr <= t + min(rem[i], q) && P[j].inQueue == false){
				P[j].inQueue = true;
				rq.push(P[j]);
			}
		if(rem[i] < q){
			t += rem[i];
			comp[i] = t;
			rem[i] = 0;
		}
		else{
			t += q;
			rem[i] -= q;
			if(!rem[i])
				comp[i] = t;
			else{
				curr.inQueue = true;
				rq.push(curr);		
			}
		}
		Gantt.push_back(P[i].pid);
	}
	for(int i = 0; i < n; i++){
		tat[i] = comp[i] - P[i].arr;
		wt[i] = tat[i] - P[i].bt;
		av_WT += (float)wt[i];
		av_TAT += (float)tat[i];
	}
	av_WT /= (float)n;
	av_TAT /= (float)n;
	cout<<"Gantt Chart: | ";
	for(auto Proc : Gantt)
		cout<<Proc<<" | ";
	cout<<endl;
	PrintProc(P, n, comp, tat, wt);
}

int main(){
	int n, q;
	cout<<"Enter the number of Processes: ";
	cin>>n;
	Process P[n];
	cout<<"Enter the Process ID, Arrival Time and Burst Time"<<endl;
	for(int i = 0; i < n; i++){
		cout<<"S.N."<<(i + 1)<<": ";
		cin>>P[i].pid>>P[i].arr>>P[i].bt;
	}
	cout<<"Enter Time Quantum: ";
	cin>>q;
	float av_WT = 0, av_TAT = 0;
	evaluateTimeRR(P, n, q, av_WT, av_TAT);
	cout<<"\nAverage Waiting Time: "<<av_WT;
	cout<<"\nAverage Turn Around Time: "<<av_TAT<<endl;
	return 0;
}


/* TERMINAL
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ g++ -o RoundRobin.exe ./RoundRobin.cpp 
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ ./RoundRobin.exe 
Enter the number of Processes: 4
Enter the Process ID, Arrival Time and Burst Time
S.N.1: 1 0 5
S.N.2: 2 1 4
S.N.3: 3 2 2
S.N.4: 4 4 1
Enter Time Quantum: 2
Gantt Chart: | 1 | 2 | 3 | 1 | 4 | 2 | 1 | 
PID	Arr	Bt	Comp	TAT	WT
1	0	5	12	12	7
2	1	4	11	10	6
3	2	2	6	4	2
4	4	1	9	5	4

Average Waiting Time: 4.75
Average Turn Around Time: 7.75
*/


/*
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ ./RoundRobin.exe 
Enter the number of Processes: 3
Enter the Process ID, Arrival Time and Burst Time
S.N.1: 1 0 10
S.N.2: 2 0 5
S.N.3: 3 0 2
Enter Time Quantum: 2
Gantt Chart: | 1 | 2 | 3 | 1 | 2 | 1 | 2 | 1 | 1 | 
PID	Arr	Bt	Comp	TAT	WT
1	0	10	17	17	7
2	0	5	13	13	8
3	0	2	6	6	4

Average Waiting Time: 6.33333
Average Turn Around Time: 12

*/

/*
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ ./RoundRobin.exe 
Enter the number of Processes: 6
Enter the Process ID, Arrival Time and Burst Time
S.N.1: 1 5 5
S.N.2: 2 4 6
S.N.3: 3 3 7
S.N.4: 4 1 9
S.N.5: 5 2 2
S.N.6: 6 6 3
Enter Time Quantum: 3
Gantt Chart: | 4 | 5 | 3 | 2 | 4 | 1 | 6 | 3 | 2 | 4 | 1 | 3 | 
PID	Arr	Bt	Comp	TAT	WT
4	1	9	30	29	20
5	2	2	6	4	2
3	3	7	33	30	23
2	4	6	27	23	17
1	5	5	32	27	22
6	6	3	21	15	12

Average Waiting Time: 16
Average Turn Around Time: 21.3333
*/
