// FCFS Scheduling
/* Write a program to find out Average Waiting Time
and Turn Around Time of n given processes with their
Burst Time through FCFS Algorithm
    Process     Arrival Time     Burst Time
    '''''''     ''''''''''''     ''''''''''
       1             0               10
       2             1                6
       3             3                2
       4             5                4
 */

#include <iostream>
#include <iomanip>
using namespace std;

float average(int arr[], int n){
    int sum = 0;
    for(int i = 0; i < n; i++)
        sum += arr[i];
    return (float)sum / (float)n;
}

int main(){
    int n;
    cout<<"Enter total number of Processes: ";
    cin>>n;
    int ProcessID[n], BurstT[n], ArrT[n];
    cout<<"Enter ProcessID, Arrival Time and Burst Time"<<endl;
    for(int i = 0; i < n; i++){
        cout<<"S.N."<<(i + 1)<<": ";
        cin>>ProcessID[i]>>ArrT[i]>>BurstT[i];
    }

    for(int i = 0; i < n - 1; i++)
        for(int j = 0; j < n - i - 1; j++)
            if(ArrT[j] > ArrT[j + 1]){
                swap(ProcessID[j], ProcessID[j + 1]);
                swap(BurstT[j], BurstT[j + 1]);
                swap(ArrT[j], ArrT[j + 1]);
            }

    int CompT[n], TAT[n], WaitT[n], RespT[n], temp = 0;
    RespT[0] = 0;
    for(int i = 0; i < n; i++){
        temp += BurstT[i];
        CompT[i] = temp;
        TAT[i] = temp - ArrT[i];
        WaitT[i] = TAT[i] - BurstT[i];
        if(i)
            RespT[i] = CompT[i - 1] - ArrT[i];
    }
    cout<<setw(4)<<"P ID"<<"    "<<setw(6)<<"Brst T"<<"  "<<setw(5)<<"Arr T"<<"   ";
    cout<<setw(6)<<"Comp T"<<"  "<<setw(4)<<"TA T"<<"    "<<setw(6)<<"Wait T"<<"  "<<setw(6)<<"Resp T"<<endl;
    for(int i = 0; i < n; i++){
        cout<<setw(4)<<ProcessID[i]<<"\t"<<setw(4)<<BurstT[i]<<"\t"<<setw(4)<<ArrT[i]<<"\t";
        cout<<setw(4)<<CompT[i]<<"\t"<<setw(4)<<TAT[i]<<"\t"<<setw(4)<<WaitT[i]<<"\t"<<setw(4)<<RespT[i]<<endl;
    }

    cout<<"Average Turn Around Time: "<<average(TAT, n)<<endl;
    cout<<"Average Waiting Time: "<<average(WaitT, n)<<endl;
    return 0;
}

/* TERMINAL
PS D:\Junior\Study\Operating-System> g++ -o .\FCFS_Scheduling.exe .\FCFS_Scheduling.cpp
PS D:\Junior\Study\Operating-System> .\FCFS_Scheduling.exe
Enter total number of Processes: 4
Enter ProcessID, Arrival Time and Burst Time
S.N.1: 1 0 10
S.N.2: 2 1 6
S.N.3: 3 3 2
S.N.4: 4 5 4
P ID    Brst T  Arr T   Comp T  TA T    Wait T  Resp T
   1      10       0      10      10       0       0
   2       6       1      16      15       9       9
   3       2       3      18      15      13      13
   4       4       5      22      17      13      13
Average Turn Around Time: 14.25
Average Waiting Time: 8.75
*/