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

#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cout<<"Enter number of processes\t: ";
    cin>>n;
    int p[n], a[n], b[n], c[n], t[n], w[n];

    cout<<"Enter Process ID, Arrival Time and Burst Time for each..."<<endl;
    for(int i = 0; i < n; i++)
        cin>>p[i]>>a[i]>>b[i];
    
    int sum = 0, temp = 0;
    for(int i = 0; i < n - 1; i++)
        for(int j = 0; j < n - i - 1; j++)
            if(a[j] > a[j + 1]){
                swap(a[j], a[j + 1]);
                swap(b[j], b[j + 1]);
                swap(p[j], p[j + 1]);
            }
    cout<<endl;
    for(int i = 0; i < n; i++){
        // cout<<p[i]<<" "<<a[i]<<" "<<b[i]<<endl;
        if(sum < a[i] && i)
            sum += a[i];
        sum += b[i];
        c[i] = sum;
        t[i] = c[i] - a[i];
        temp += t[i];
    }

    // for(int i = 0; i < n; i++)
    //     cout<<c[i]<<endl;

    sum = temp;
    temp = 0;

    for(int i = 0; i < n; i++){
        w[i] = t[i] - b[i];
        temp += w[i];
    }

    for(int i = -1; i < n; i++){
        for(int j = 0; j < 6; j++){
            if(i == -1){
                if(j == 0)
                    cout<<"   Process\t";
                else if(j == 1)
                    cout<<"   Arrival Time\t";
                else if(j == 2)
                    cout<<"   Burst Time\t";
                else if(j == 3)
                    cout<<"   Completion Time\t";
                else if(j == 4)
                    cout<<"   Turn Around Time\t";
                else
                    cout<<"   Waiting Time\t";
            }
            else{
                if(j == 0)
                    cout<<"\t"<<p[i]<<"\t";
                else if(j == 1)
                    cout<<"\t"<<setw(2)<<a[i]<<"\t";
                else if(j == 2)
                    cout<<"\t"<<setw(2)<<b[i]<<"\t";
                else if(j == 3)
                    cout<<"\t"<<setw(2)<<c[i]<<"\t";
                else if(j == 4)
                    cout<<"\t\t"<<setw(2)<<t[i]<<"\t";
                else
                    cout<<"\t\t"<<setw(2)<<w[i]<<"\t";
            }
        }
        cout<<endl;
    }

    cout<<"Average Turn Around Time is: "<<float(sum)/float(n)<<endl;
    cout<<"Average Waiting Time is: "<<float(temp)/float(n)<<endl;

    return 0;
}

/* TERMINAL
PS D:\Junior\Study\Operating-System> g++ -o Lab3P2.exe ./Lab3P2.cpp
PS D:\Junior\Study\Operating-System> .\Lab3P2.exe
Enter number of processes       : 4
Enter Process ID, Arrival Time and Burst Time for each...
1 0 10
2 1 6
3 3 2
4 5 4

   Process         Arrival Time    Burst Time      Completion Time         Turn Around Time        Waiting Time
        1                0              10              10                      10                       0
        2                1               6              16                      15                       9
        3                3               2              18                      15                      13
        4                5               4              22                      17                      13
Average Turn Around Time is: 14.25
Average Waiting Time is: 8.75
*/