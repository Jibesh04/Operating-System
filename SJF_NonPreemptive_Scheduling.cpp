/* Write a program to find out Average Waiting Time
and Turn Around Time of n given processes with their
Burst Time through SJF NonPreemptive Algorithm
    Process     Arrival Time     Burst Time
    '''''''     ''''''''''''     ''''''''''
       1             1                3
       2             2                4
       3             1                2
       4             4                4
*/

#include <iostream>
#include <iomanip>

#define PID 0
#define ArrT 1 
#define BurstT 2
#define CompT 3
#define TAT 4
#define WaitT 5
#define RespT 6

using namespace std;

void arrivalSort(int data[][7], int n, int Param){
    for(int i = 0; i < n - 1; i++)
        for(int j = 0; j < n - i - 1; j++)
            if(data[j][Param] > data[j + 1][Param])
                for(int k = 0; k < 7; k++)
                    swap(data[j][k], data[j + 1][k]);
}

void evaluateTimeSJFNP(int data[][7], int n, float & av_TAT, float & av_WT){
    arrivalSort(data, n, ArrT);
    int temp, val, tat = 0, wt = 0;
    // data[0][CompT] = data[0][ArrT] + data[0][BurstT];
    // data[0][TAT] = data[0][CompT] - data[0][ArrT];
    // data[0][WaitT] = data[0][TAT] - data[0][BurstT];
    for(int i = 0; i < n; i++) {
        if(i)
            temp = data[i - 1][CompT];
        else
            temp = data[i][ArrT];
        int low = data[i][BurstT];
        for(int j = i; j < n; j++) {
           if(temp >= data[j][ArrT] && low >= data[j][BurstT]) {
              low = data[j][BurstT];
              val = j;
           }
        }
        data[val][CompT] = temp + data[val][BurstT];
        data[val][TAT] = data[val][CompT] - data[val][ArrT];
        data[val][WaitT] = data[val][TAT] - data[val][BurstT];
        tat += data[val][TAT];
        wt += data[val][WaitT];
        for(int k = 0; k < 7; k++) 
            swap(data[val][k], data[i][k]);
   }
   data[0][RespT] = 0;
   for(int i = 1; i < n; i++)
        data[i][RespT] = data[i - 1][CompT] - data[i][ArrT];
   av_TAT = (float)tat/(float)n;
   av_WT = (float)wt/(float)n;
}

void printTable(int data[][7], int n){
    cout<<setw(4)<<"P ID"<<"    "<<setw(6)<<"Arr T"<<"   "<<setw(5)<<"Brst T"<<"  ";
    cout<<setw(6)<<"Comp T"<<"  "<<setw(4)<<"TA T"<<"    "<<setw(6)<<"Wait T"<<"  "<<setw(6)<<"Resp T"<<endl;
    for(int i = 0; i < n; i++){
        cout<<setw(4)<<data[i][PID]<<"\t"<<setw(4)<<data[i][ArrT]<<"\t"<<setw(4)<<data[i][BurstT]<<"\t";
        cout<<setw(4)<<data[i][CompT]<<"\t"<<setw(4)<<data[i][TAT]<<"\t"<<setw(4)<<data[i][WaitT]<<"\t"<<setw(4)<<data[i][RespT]<<endl;
    }
}

int main(){
    int n;
    cout<<"Enter total number of Processes: ";
    cin>>n;

    int data[n][7];
    cout<<"Enter Process ID, Arrival Time and Burst Time"<<endl;
    for(int i = 0; i < n; i++){
        cout<<"S.N."<<(i + 1)<<": ";
        cin>>data[i][PID]>>data[i][ArrT]>>data[i][BurstT];
    }

    float av_TAT, av_WT;
    evaluateTimeSJFNP(data, n, av_TAT, av_WT);
    printTable(data, n);
    cout<<"Average Turn Around Time: "<<av_TAT<<endl;
    cout<<"Average Waiting Time: "<<av_WT<<endl;
    return 0;
}

/* TERMINAL

PS D:\Junior\Study\Operating-System> g++ -o .\SJF_NonPreemptive_Scheduling.exe .\SJF_NonPreemptive_Scheduling.cpp
PS D:\Junior\Study\Operating-System> .\SJF_NonPreemptive_Scheduling.exe
Enter total number of Processes: 4
Enter Process ID, Arrival Time and Burst Time
S.N.1: 1 1 3
S.N.2: 2 2 4
S.N.3: 3 1 2
S.N.4: 4 4 4
P ID     Arr T   Brst T  Comp T  TA T    Wait T  Resp T
   3       1       2       3       2       0       0
   1       1       3       6       5       2       2
   4       4       4      10       6       2       2
   2       2       4      14      12       8       8
Average Turn Around Time: 6.25
Average Waiting Time: 3
*/