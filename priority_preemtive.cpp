#include <iostream>
#include <bits/stdc++.h>
#include <iomanip>

using namespace std;


int main()
{
    freopen("input.txt","r",stdin);

    freopen("output.txt","w",stdout);
    int processes;
    cin>>processes;
    int k=0;
    int time_quant=1;
    int maxindex=0;
    int max=0;
    bool a =true;
    int completed=0;
    
    
int  mat[processes][6];
int  wt[processes];
int  turntime[processes];

    for (int i = 0; i < processes; i++) {
        
        //id
        cin >> mat[i][0];
        //arrival time
        cin >> mat[i][1];
        //burst time 
        cin >> mat[i][2];
        //priority
        cin >> mat[i][3];

        mat[i][4]=mat[i][2];
        mat[i][5]=mat[i][3];
    }   
    cout<<"PRIORITY WITH PREEMTION"<<endl;
while(a){
    max=INT_MAX;
    maxindex=0;
//lopping for no of process till time k 
for (int i=0;i<processes;i++){
    
    //finding process with min priority
    if (mat[i][1]<=k){
        if(mat[i][3]<max & mat[i][3]>0){
                max=mat[i][3];
                maxindex=i;
            }
    }
    
}
if(max==INT_MAX){
    k=k+1;
    continue;
}
mat[maxindex][2]=mat[maxindex][2]-1;// executing process for 1 unit 
k=k+1;


// checking if process has finished ie burst time =0
if(mat[maxindex][2]==0){
    int wttime;
    int turnaround;
    turnaround=k-mat[maxindex][1];
    wttime=turnaround-mat[maxindex][4];
    wt[maxindex]=wttime;
    turntime[maxindex]=turnaround;
    completed=completed+1;
    mat[maxindex][3]=-1;

}
//break condition if all process finish 
if(completed==processes){
    a=false;
}

}
//printing the results
cout
            << left
            << setw(12)
            << "PROCESS ID"
            << left
            << setw(5)
            << "A.T"
            << left
            << setw(5)
            << "B.T"
            << left
            << setw(10)
            << "PRIORITY"
            << left
            << setw(10)
            << "W.T "
            << left
            << setw(5)
            << "F.T"
            << left
            << setw(5)
            << "T.T"
            << endl;

 for (int i = 0; i < processes; i++)
    {
        cout
            << left
            << setw(12)
            << mat[i][0]
            << left
            << setw(5)
            << mat[i][1]
            << left
            << setw(5)
            << mat[i][4]
            << left
            << setw(10)
            << mat[i][5]
            << left
            << setw(10)
            << wt[i]
            << left
            << setw(5)
            << mat[i][1]+turntime[i]
            << left
            << setw(5)
            << turntime[i]
            << endl;
    }
}
