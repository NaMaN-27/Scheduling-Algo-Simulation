#include <iostream>
#include <bits/stdc++.h>
#include <iomanip>
#include <queue>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
using namespace std;


class Resource{
    
    
    public:
    mutex * mtx;
    int res_no;
    
    Resource(int res){
        
        res_no=res;
        mtx = new std::mutex();
    }
    void lock_mutex(mutex * mt){
        cout<< "|" << "Res. " << res_no << " Acquired" << "|" << endl; 
        mt->lock();
    }
    void unlock_mutex(mutex * mt){
        cout<< "|" << "Res. " << res_no << " Deallocated" << "|" << endl;
        mt->unlock();
    }
};
class PCB {
    // process control block and process class 
    public :
    std::map<std::string, std::string> metadata;
    int process_no;
    int priority;
    int burst_time;
    int arrival_time;
    bool state;
    bool type;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int interrupt_ar_time;
    int interrupt_bt_time;
    
    Resource *max_resources;
    int no_res;
    public :
    PCB(int process,int prior,int bt,int at,bool st,bool ty,int res_no,Resource re[],int inter_time=0,int interbt=3){
        process_no=process;
        priority=prior;
        burst_time=bt;
        remaining_time=bt;
        arrival_time=at;
        state=st;
        type=ty;
        max_resources=re;
        no_res=res_no;
        if(ty==true){
            interrupt_ar_time=inter_time;
            interrupt_bt_time=interbt;
            
        }
        
    }
};
void ExecuteThread(PCB &temp){
    
    auto nowTime = std::chrono::system_clock::now(); 
    
    
    std::time_t sleepTime = 
            std::chrono::system_clock::to_time_t(nowTime);
    
    // Convert to current time zone
    tm myLocalTime = *localtime(&sleepTime);
    
    
    cout<<"Executed Process "<<temp.process_no<<" At"<<"  ";
    cout << "TIME -> " <<myLocalTime.tm_hour << ":";
    cout << myLocalTime.tm_min << ":";
    cout  << myLocalTime.tm_sec << "    ||   ";
    cout<<"Remaining Burst Time : "<<temp.remaining_time<<"\n";
            
}
void swap(PCB *xp, PCB *yp) { 
    PCB temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
void selectionSort(PCB pro[]) 
{ 
   int i, j, min_idx; 
    
    for (i = 0; i < 6; i++) 
    { 
        // Find the minimum element in unsorted array 
        min_idx = i; 
        for (j = i+1; j < 6; j++) 
        if (pro[j].arrival_time < pro[min_idx].arrival_time) 
            min_idx = j; 
        swap(&pro[i],&pro[min_idx]);

    } 
}
void bankers_check(PCB pro[]);
void preemt(PCB &temp){
    for (int x=0;x<temp.no_res;x++){
               (temp.max_resources+x)->unlock_mutex((temp.max_resources+x)->mtx);
            }


}
void round_robin(PCB pro[]){
    int k=0;
    int robin=0;
    int completed=0;
    int prev_value=0;
    int processes=6;
    queue<int> ready;
    bool a=true;
    int time_quant=3;
    
    
    k=pro[0].arrival_time;//setting k to arrival time of first process 
    
    ready.push(0);// pushing first process in the queue 
    cout<<"STARTING THE PREEMPTIVE KERNEL USING ROUND ROBIN SCHEDULING ";
    auto nowTime = std::chrono::system_clock::now(); 
    std::time_t sleepTime = 
            std::chrono::system_clock::to_time_t(nowTime);
    tm myLocalTime = *localtime(&sleepTime);
    cout<<"AT "<<"  ";
    cout << "TIME -> " <<myLocalTime.tm_hour << ":";
    cout << myLocalTime.tm_min << ":";
    cout  << myLocalTime.tm_sec <<"\n\n\n";
    std::this_thread::sleep_for (std::chrono::seconds(k));// waiting for first process 
    
    while(a){
        
        
        
        
        if(!ready.empty())
        {   //process available in ready queue 
        
            robin=ready.front();
            //allocating resources 
            for (int x=0;x<pro[robin].no_res;x++){
                (pro[robin].max_resources+x)->lock_mutex((pro[robin].max_resources+x)->mtx);
           }
           
           if(pro[robin].interrupt_ar_time<pro[robin].burst_time-pro[robin].remaining_time+time_quant && pro[robin].type){
               
               
               prev_value=k;
               int time_push=pro[robin].interrupt_ar_time-(pro[robin].burst_time-pro[robin].remaining_time);
               pro[robin].remaining_time=pro[robin].remaining_time - time_push;
               std::this_thread::sleep_for (std::chrono::seconds(time_push));
               ExecuteThread(pro[robin]);
               k=k+pro[robin].interrupt_bt_time+time_push;
               pro[robin].type=false;
               cout<<"Interrupt Occured In Process "<<pro[robin].process_no<<".  Resolving Interrrupt In "<<pro[robin].interrupt_bt_time<<"Sec"<<"\n";
               preemt(pro[robin]);
               ready.pop();
               std::this_thread::sleep_for (std::chrono::seconds(pro[robin].interrupt_bt_time));
               
           }
            
            
            
            else if (pro[robin].remaining_time<=time_quant & pro[robin].remaining_time>0){
                
                int time_sleep=pro[robin].remaining_time;
                
                prev_value=k;
                k=k+pro[robin].remaining_time;// adding time required to complete 
                pro[robin].remaining_time=0;
                ExecuteThread(pro[robin]);
                std::this_thread::sleep_for (std::chrono::seconds(time_sleep));
               
                cout<<"Completed Process "<<pro[robin].process_no<<"\n";
                //completing the process 
                
                pro[robin].turnaround_time=k-pro[robin].arrival_time;//setting the turnaround time and waiting time 
                
                pro[robin].waiting_time=pro[robin].turnaround_time-pro[robin].burst_time;
               
                completed=completed+1;
                ready.pop();// removing the element 
                preemt(pro[robin]);//finishing the process by setting the values 
                

            }
            else{
                
                
                pro[robin].remaining_time=pro[robin].remaining_time-time_quant;
                ExecuteThread(pro[robin]);
                std::this_thread::sleep_for (std::chrono::seconds(time_quant));
                preemt(pro[robin]);//preemting the process 
                prev_value=k;
                k=k+time_quant;
                ready.pop();// removing the element 
            }
        
        for (int i=1; i<6;i++)//finding process which came in last window 
        {

            
            if(pro[i].arrival_time>prev_value & pro[i].arrival_time<=k  & pro[i].remaining_time!=0)
                {
                    
                ready.push(i);//pushing elements that arrived in last window 
                }
        }
        if(pro[robin].remaining_time>0){
            
            ready.push(robin);// pushing last executed element again if it did not finish 
        }
        
        }
        else// cpu idle sitting thats why incrementing time by 1 unit
        {
            k=k+1;
            for (int i=1; i<processes;i++)//finding the process that came in the last window 
        {
             if(pro[robin].arrival_time>prev_value & pro[robin].arrival_time<=k  & pro[robin].remaining_time!=0)
                {
                ready.push(i);//pushing elements that arrived in last window 
                }
        }
        }
       
      if(completed==6)
        {
            a=false;
        }
    }
    }
void print_results(PCB pro[],int no_process){
        
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
            << "W.T "
            << left
            << setw(5)
            << "F.T"
            << left
            << setw(5)
            << "T.T"
            << endl;

 for (int i = 0; i < no_process; i++)
    {
        cout
            << left
            << setw(12)
            << pro[i].process_no
            << left
            << setw(5)
            << pro[i].arrival_time
            << left
            << setw(5)
            << pro[i].burst_time
            << left
            << setw(10)
            << pro[i].waiting_time
            << left
            << setw(5)
            << pro[i].arrival_time+pro[i].turnaround_time
            << left
            << setw(5)
            << pro[i].turnaround_time
            << endl;
    }
    }



int main(){
    // object creation
    Resource r1(1);
    Resource r2(2);
    Resource r3(3);
    Resource r4(4);
    Resource r5(5);
    Resource r6(6);
    Resource r7(7);

    // array of resource objects 

    Resource res[2]={r6,r4};
    Resource res1[3]={r1,r2,r3};
    Resource res2[3]={r1,r2,r7};
    Resource res3[1]={r5};
    Resource res4[5]={r1,r2,r5,r3,r7};
    Resource res5[2]={r1,r7};

    PCB p1(1,3,8,1,true,false,2,res );
    PCB p2(2,1,15,5,true,true,3,res1,5,4);
    PCB p3(3,8,2,6,true,false,3,res2);
    PCB p4(4,6,6,3,true,false,1,res3);
    PCB p5(5,8,4,2,true,false,5,res4);
    PCB p6(6,7,8,4,true,false,2,res5);
    PCB pro[6]={p1,p2,p3,p4,p5,p6};
    int len = sizeof(pro)/sizeof(pro[0]);
    
    bankers_check(pro);
    selectionSort(pro);
    
    std::thread th1 (round_robin,pro);
    th1.join();
    cout<<"\n\n";
    
    //TIME
    auto nowTime = std::chrono::system_clock::now(); 
    std::time_t sleepTime = 
            std::chrono::system_clock::to_time_t(nowTime);
    tm myLocalTime = *localtime(&sleepTime);
    
    
    cout<<"ALL PROCESSES EXECUTED SUCCESSFULLY BY"<<"  ";
    cout << "TIME -> " <<myLocalTime.tm_hour << ":";
    cout << myLocalTime.tm_min << ":";
    cout  << myLocalTime.tm_sec <<"\n\n\n";
    
    
    cout<<"THE GANTT CHART IS AS FOLLOWS : "<<"\n\n";
    print_results(pro,len);
    
    
}


void bankers_check(PCB pro[]){
    int  i, j, k;
    int n = 5, m=7;
  int alloc[n][m];
  for( i=0;i<n;i++){
      for( j=0;j<m;j++){
        alloc[i][j] = 2;
  }
  }
  
  int max[n][m];
  
  for(i=0;i<n;i++){
    PCB temp = pro[i];
    for( j=0;j<m;j++){
        max[i][j] = 2;
  }
    for (int x=0;x<temp.no_res;x++){
               max[i][(temp.max_resources+x)->res_no] += 1;
            }  
  }
 
  int avail[m]; // Available Resources
  for( j=0;j<m;j++){
        avail[j] = 3;
  }
 
  int f[n], ans[n], ind = 0;
  for (k = 0; k < n; k++) {
    f[k] = 0;
  }
  int need[n][m];
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++)
      need[i][j] = max[i][j] - alloc[i][j];
  }
  int y = 0;
  for (k = 0; k < 5; k++) {
    for (i = 0; i < n; i++) {
      if (f[i] == 0) {
 
        int flag = 0;
        for (j = 0; j < m; j++) {
          if (need[i][j] > avail[j]){
            flag = 1;
            break;
          }
        }
 
        if (flag == 0) {
          ans[ind++] = i;
          for (y = 0; y < m; y++)
            avail[y] += alloc[i][y];
          f[i] = 1;
        }
      }
    }
  }
   
  int flag = 1;
   
  // To check if sequence is safe or not
  for(int i = 0;i<n;i++)
  {
        if(f[i]==0)
      {
        //flag = 0;
        cout << "The given sequence is not safe";
        break;
      }
  }
 
  if(flag==1)
  {
    cout << "Following is the SAFE Sequence" << endl;
      for (i = 0; i < n - 1; i++)
        cout << " P" << ans[i] << " ->";
      cout << " P" << ans[n - 1] <<endl;
  }
}