/* Write a program to find average turn around time and average
waiting time from given data as followed:
    Process     Burst Time
    '''''''     ''''''''''
      P1            24
      P2             3
      P3             3 */

#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    int n;
    cout<<"Enter total number of Processes: ";
    cin>>n;
    int ProcessID[n], BurstT[n];
    cout<<"Enter ProcessID and Burst Time"<<endl;
    for(int i = 0; i < n; i++){
        cout<<"S.N."<<(i + 1)<<": ";
        cin>>ProcessID[i]>>BurstT[i];
    }
    int ArrT[n] = {0}, CompT[n], TAT[n], WaitT[n], RespT[n], temp = 0;
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
    return 0;
}

/* TERMINAL
PS D:\Junior\Study\Operating-System> g++ -o .\Scheduling_nonAlgo.exe .\Scheduling_nonAlgo.cpp
PS D:\Junior\Study\Operating-System> .\Scheduling_nonAlgo.exe
Enter total number of Processes: 3
Enter ProcessID and Burst Time
S.N.1: 1 24
S.N.2: 2 3
S.N.3: 3 3
P ID    Brst T  Arr T   Comp T  TA T    Wait T  Resp T
   1      24       0      24      24       0       0
   2       3       0      27      27      24      24
   3       3       0      30      30      27      27
*/