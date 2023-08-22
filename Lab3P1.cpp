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
  cout<<"Enter number of processes\t: ";
  cin>>n;
  int p[n], a[n], b[n], c[n], t[n], w[n];

  for(int i = 0; i < n; i++)
    a[i] = 0; // Arrival Time Probably

  cout<<"Enter Process number and Burst Time for each..."<<endl;
  for(int i = 0; i < n; i++)
    cin>>p[i]>>b[i];

  int sum = 0, temp = 0;
  for(int i = 0; i < n; i++){
    sum += b[i];
    c[i] = sum;
    t[i] = sum;
    temp += sum;
  }

  sum = temp;
  temp = 0;
  for(int i = 0; i < n; i++){
    w[i] = t[i] - b[i];
    temp += w[i];
  }

  /*
  float avg_wt=temp/float(sum);
  float avg_at=c[0]/float((a[0]+w[0]));
  printf("Average Waiting Time : %.5f",avg_wt );
  printf("\n");
  printf("Average Turn Around Time : %.5f ",avg_at);
  return 0; 
  */

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
PS D:\Junior\Study\Operating-System> g++ -o Lab3P1.exe .\Lab3P1.cpp
PS D:\Junior\Study\Operating-System> ./Lab3P1.exe
Enter number of processes       : 3
Enter Process number and Burst Time for each...
1 24
2 3
3 3
   Process         Arrival Time    Burst Time      Completion Time         Turn Around Time        Waiting Time
        1                0              24              24                      24                       0
        2                0               3              27                      27                      24
        3                0               3              30                      30                      27
Average Turn Around Time is: 27
Average Waiting Time is: 17
*/