#include <iostream>
#include <numeric>
using namespace std;

int T=1;
void roundrobin(int proc, int *jobs, int *jobstart, int *jobfinish);//q0
void shortestjobfirst1(int proc, int *jobs, int *jobstart, int *jobfinish);
void shortestjobfirst2(int proc, int *jobs, int *jobstart, int *jobfinish);//q1
void fifo(int proc, int *jobs, int *jobstart, int *jobfinish);//q3
void starttime(int proc,int *jobs,int *jobstart);
int findmin(int proc,int *jobs);

int findmin(int proc,int *jobs){
    int min = 0,flag=0;
    for(int j=0;j<proc;j++){
        if((jobs[j]!=0)){
            min=j;
            flag=1;
            break;
        }
    }
    for(int i=0;i<proc;i++){
        if(jobs[i]!=0 && jobs[i]<jobs[min]) {
            min = i;
        }
    }
    return min;
}

void starttime(int proc,int *jobs,int *jobstart){
    int k=0,m=0;
    while (k<20)
    {
        if(proc>20){
            if(jobstart[m]==0 && jobs[m]!=0){
                jobstart[m]=T;
                k++;
            }
            m++;
            if(m>=proc){
                break;
            }
        }
        else {
            if(jobstart[m]==0 && jobs[m]!=0){
                jobstart[m]=T;
                k++;
            }
            m++;
            if(m>=proc){
                break;
            }
        }
    }
}

void roundrobin(int proc,int *jobs,int *jobstart,int *jobfinish){
    int sum=0,k=0, i=0;
    starttime(proc,jobs,jobstart);
    while((accumulate(jobs,jobs+proc,sum)!=0) && k<20)
    {
        if(proc>20)
        {
            if(jobs[i]!=0)
            {
                T++;
                jobs[i] -= 1;
                if(jobs[i]==0){
                    jobfinish[i]=T;
                }
                k++;
            }
            i++;
            if(i==proc){
                i=0;
            }
            
        }

        else
        {
            if(jobs[i]!=0)
            {
                T++;
                jobs[i]-=1;
                if(jobs[i]==0){
                    jobfinish[i]=T;
                }
                k++;
            }
            i++;
            if(i==proc){
                i=0;
            }
        }
    
    }

    cout<<"---------RR--------- ";
    for(int i=0;i<proc;i++){
        cout<<jobs[i]<<"\t";
    }
    cout<<endl;

}
void shortestjobfirst1(int proc, int *jobs, int *jobstart, int *jobfinish)
{
    int round=20,sum=0;
    while (round>0 && (accumulate(jobs,jobs+proc,sum)!=0)) {
        int min= findmin(proc,jobs);
        if(jobstart[min]==0 && jobs[min]!=0){ // not start -> start
            jobstart[min]=T;
        }
        if(jobs[min]<=round) {
            T+=jobs[min];
            round-=jobs[min];
            jobs[min]=0;
            jobfinish[min]=T;
        }
        else if(jobs[min]>round){
            jobs[min]-=round;
            T+=round;
            round=0;
        }
    }
    cout<<"--------SJF1-------- ";
    for(int i=0;i<proc;i++){
        cout<<jobs[i]<<"\t";
    }
    cout<<endl;
}

void shortestjobfirst2(int proc, int *jobs, int *jobstart, int *jobfinish)
{

    int round=20,sum=0;
    while (round>0 && (accumulate(jobs,jobs+proc,sum)!=0))
    {
        int min= findmin(proc,jobs);
        if(jobstart[min]==0 && jobs[min]!=0){ // not start -> start
            jobstart[min]=T;
        }
        if(jobs[min]<=round) {
            T+=jobs[min];
            round-=jobs[min];
            jobs[min]=0;
            jobfinish[min]=T;
        }
        else if(jobs[min]>round){
            jobs[min]-=round;
            T+=round;
            round=0;
        }
    }
    cout<<"--------SJF2-------- ";
    for(int i=0;i<proc;i++){
        cout<<jobs[i]<<"\t";
    }
    cout<<endl;
}

void fifo(int proc, int *jobs, int *jobstart, int *jobfinish){
    int round=20,i=0;
    while(round>0){
        if(jobstart[i]==0 && jobs[i]!=0) { // not start -> start
            jobstart[i] = T;
        }
        if(jobs[i]==0){
            i++;
        }

        else if(jobs[i]<=round){
            T+=jobs[i];
            round-=jobs[i];
            jobs[i]=0;
            jobfinish[i]=T;
            i++;
        }
        else if(jobs[i]>round){
            jobs[i]-=round;
            T+=round;
            round=0;
        }
    }
    cout<<"--------FCFS-------- ";
    for(int i=0;i<proc;i++){
        cout<<jobs[i]<<"\t";
    }
    cout<<endl;
}

int main()
{
    cout<<"q0-Round Robin(RR)"<<endl;
    cout<<"q1-Shortest Job First(SJF)"<<endl;
    cout<<"q2-Shortest Job First(SJF)"<<endl;
    cout<<"q3-First-In-First-Out(FIFO)"<<endl<<endl;

    int arr[4],proc;

    cout<<"Input total number of processors. ";
    cin>>proc;

    int *jobs=new int[proc] ();
    int *jobstart =new int[proc] ();
    int *jobsfinish =new int[proc] ();
    int prioArr[4];

    for(int i=0;i<proc;i++){
        cin>>jobs[i];
    }
    int copy[proc];
    for(int i=0;i<proc;i++){
        copy[i]=jobs[i];
    }
    cout<<endl;
    for(int i=0;i<4;i++){
        cout<<"Enter Priority for q "<<i<<" :";
        cin>>arr[i];//priority array
    }
    cout<<endl<<endl;
    cout<<"-----Burst Time-----";
    for(int i=0;i<proc;i++){
        cout<<jobs[i]<<"\t";
    }
    cout<<endl;
    for(int i=0;i<4;i++){
        if(arr[i]==1){
            prioArr[0]=i;
        }
        else if(arr[i]==2){
            prioArr[1]=i;
        }
        else if(arr[i]==3){
            prioArr[2]=i;
        }
        else if(arr[i]==4){
            prioArr[3]=i;
        }
    }
    int i=0,sum=0;

    while(accumulate(jobs,jobs+proc,sum)!=0)//GET SUM OF NUMBER OF BURST TIME ,WHEN TOTAL BURST TIME BECOME 0 LOOP WILL BE TERMINATED.
    {

        if(prioArr[i]==0){
            roundrobin(proc,jobs,jobstart,jobsfinish);
            i++;
        }
        else if(prioArr[i]==1){
            shortestjobfirst1(proc,jobs,jobstart,jobsfinish);
            i++;

        }
        else if(prioArr[i]==2){
            shortestjobfirst2(proc,jobs,jobstart,jobsfinish);
            i++;
        }
        else if(prioArr[i]==3){
            fifo(proc,jobs,jobstart,jobsfinish);
            i++;

        }
        if(i==4){
            i=0;
        }

    }
    cout<<endl<<endl;
    cout<<"-----Burst Time-----"<<"\t";
    for(int i=0;i<proc;i++){
        cout<<copy[i]<<" ";
    }
    cout<<endl;
    cout<<"--Turnaround Time---"<<"\t";
    for(int i=0;i<proc;i++){
        cout<<jobsfinish[i]-jobstart[i]<<" ";
    }
    cout<<endl;
    cout<<"----Waiting Time----"<<"\t";
    for(int i=0;i<proc;i++){
        cout<<jobsfinish[i]-jobstart[i]-copy[i]<<" ";
    }
    cout<<endl;
    
}

