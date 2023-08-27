/* Write a program to find out Average Waiting Time
and Turn Around Time of n given processes with their
Burst Time through SJF Preemptive Algorithm
    Process     Arrival Time     Burst Time
    '''''''     ''''''''''''     ''''''''''
       1             0                8
       2             1                4
       3             2                9
       4             3                5
*/

#include <bits/stdc++.h>
using namespace std;
struct Process{
    int pid; // Process ID
    int bt;  // Burst Time
    int art; // Arrival Time
};

void findWaitingTime(Process proc[], int n, int wt[]){
    int rem[n];
    for (int i = 0; i < n; i++)
        rem[i] = proc[i].bt;
    vector<int> Gantt;
    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0;
    bool check = false;
    while (complete != n){
        for (int j = 0; j < n; j++)
            if ((proc[j].art <= t) && (rem[j] < minm) && rem[j] > 0){
                minm = rem[j];
                shortest = j;
                check = true;
            }
        if (check == false){
            Gantt.push_back(0);
            t++;
            continue;
        }
        minm = --rem[shortest];
        if (rem[shortest] == 0){
            minm = INT_MAX;
            complete++;
            check = false;
            wt[shortest] = t + 1 - proc[shortest].bt - proc[shortest].art;
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        Gantt.push_back(proc[shortest].pid);
        t++;
    }
    cout<<endl<<"Process Sequence: ";
    for(auto i : Gantt)
        cout<<i<<" ";
    cout<<endl;
}

void findTurnAroundTime(Process proc[], int n, int wt[], int tat[]){
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}

void findavgTime(Process proc[], int n){
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTime(proc, n, wt);
    findTurnAroundTime(proc, n, wt, tat);
    cout << "Processes " << "   Arrival time  " << " Burst time " << " Waiting time " << " Turn around time\n";
    for (int i = 0; i < n; i++){
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << proc[i].pid << "\t\t" << proc[i].art << "\t\t" << proc[i].bt << "\t\t " << wt[i] << "\t\t " << tat[i] << endl;
    }
    cout << "\nAverage waiting time = " << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
}

int main(){
    int n;
    cout<<"Enter total number of Processes: ";
    cin>>n;
    Process proc[n];
    cout<<"Enter ProcessID, Arrival Time and Burst Time"<<endl;
    for(int i = 0; i < n; i++){
        cout<<"S.N."<<(i + 1)<<": ";
        cin>>proc[i].pid>>proc[i].art>>proc[i].bt;
    }
    findavgTime(proc, n);
    return 0;
}

/* TERMINAL
PS D:\Junior\Study\Operating-System> g++ -o .\SJF_Preemptive_Scheduling.exe .\SJF_Preemptive_Scheduling.cpp
PS D:\Junior\Study\Operating-System> .\SJF_Preemptive_Scheduling.exe
Enter total number of Processes: 4
Enter ProcessID, Arrival Time and Burst Time
S.N.1: 1 0 8
S.N.2: 2 1 4 
S.N.3: 3 2 9
S.N.4: 4 3 5

Process Sequence: 1 2 2 2 2 4 4 4 4 4 1 1 1 1 1 1 1 3 3 3 3 3 3 3 3 3
Processes    Arrival time   Burst time  Waiting time  Turn around time
 1              0               8                9               17
 2              1               4                0               4
 3              2               9                15              24
 4              3               5                2               7

Average waiting time = 6.5
Average turn around time = 13
*/