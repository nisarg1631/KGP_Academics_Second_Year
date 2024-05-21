/*
    Name: Nisarg Upadhyaya
    Roll No: 19CS30031
*/

#include <iostream>
using namespace std;

#define MAX_SIZE 100

typedef struct _job{
    int jobId;
    int startTime;
    int jobLength;
    int remLength;

    _job(){
        jobId=startTime=jobLength=remLength=-1;
    }
    _job(int id, int arrival, int length){
        jobId=id;
        startTime=arrival;
        jobLength=remLength=length;
    }
}job;

/* UTILITY FUNCTIONS FOR JOBS */
void swap(job& j1, job& j2){
    job temp=j1;
    j1=j2;
    j2=temp;
}

//compare two jobs
//returns true if j1 has lesser remaining time
//if tie still persists returns true if j1 has lower id
bool isSmallerThan(job j1, job j2){
    if(j1.remLength!=j2.remLength)
        return j1.remLength<j2.remLength;
    else
        return j1.jobId<j2.jobId;
}
/* UTILITY FUNCTIONS FOR JOBS */

typedef struct _heap{
    job list[MAX_SIZE];
    int numJobs;
}heap;

/* UTILITY FUNCTIONS FOR HEAPS */
int parent(int index){
    return (index/2);
}
int left(int index){
    return (2*index);
}
int right(int index){
    return ((2*index)+1);
}
void heapify(heap *H, int index){
    int l=left(index);
    int r=right(index);
    int smallest=index;
    if(l<=(H->numJobs) && isSmallerThan((H->list)[l],(H->list)[smallest]))
        smallest=l;
    if(r<=(H->numJobs) && isSmallerThan((H->list)[r],(H->list)[smallest]))
        smallest=r;
    if(smallest!=index){
        swap((H->list)[index],(H->list)[smallest]);
        heapify(H,smallest);
    }
}
/* UTILITY FUNCTIONS FOR HEAPS */

void initHeap(heap *H){
    H->numJobs=0;
}

void insertJob(heap *H, job j){
    (H->numJobs)++;
    (H->list)[H->numJobs]=j;
    int i=(H->numJobs);
    while(i>1 && isSmallerThan((H->list)[i],(H->list)[parent(i)])){
        swap((H->list)[i],(H->list)[parent(i)]);
        i=parent(i);
    }
}

int extractMinJob(heap *H, job *j){
    if((H->numJobs)<1){
        return -1;
    }
    job minimum=(H->list)[1];
    (H->list)[1]=(H->list)[H->numJobs];
    (H->numJobs)--;
    heapify(H,1);
    *j=minimum;
    return 0;
}

//counting sort to sort jobs according to start time
//stores jobs in 2d array sorted where ith row stores with start time = i
//count[i] stores the number of jobs present in ith row
//time complexity O(n) - requires single scan through jobList
void count_sort(job *jobList, int n, job **sorted, int *count){
    for(int i=0; i<n; i++){
        sorted[jobList[i].startTime][count[jobList[i].startTime]]=jobList[i];
        count[jobList[i].startTime]++;
    }
}

void scheduler(job *jobList, int n){
    //get max start time among all jobs
    int max_start_time=0;
    for(int i=0; i<n; i++)
        max_start_time=max(max_start_time,jobList[i].startTime);
    
    //create 2d array sorted to store jobs according to their start times
    //create count array to keep track of number of jobs starting at a particular time
    job **sorted=new job*[max_start_time+1];
    int *count=new int[max_start_time+1];
    for(int i=0; i<=max_start_time; i++){
        sorted[i]=new job[MAX_SIZE];
        count[i]=0;
    }

    //call to count_sort
    count_sort(jobList,n,sorted,count);

    //create turnaround array to keep track of turnaround times for each job
    int *turnaround=new int[n+1];
    int sys_clock=0;
    int processed=0;

    //create heap to store jobs according to priority
    heap *H=new heap;
    initHeap(H);

    cout<<"Jobs scheduled at each timestep are:\n";
    //process jobs until no job remains
    while(processed!=n){
        //add all jobs whose start time = current time
        if(sys_clock<=max_start_time){
            for(int i=0; i<count[sys_clock]; i++){
                insertJob(H, sorted[sys_clock][i]);
            }
        }
        //get current job to process from heap
        job curr;
        if(extractMinJob(H,&curr)==0){
            cout<<curr.jobId<<" ";
            //if job appeared for first time then set its turnaround time
            if(curr.jobLength==curr.remLength){
                turnaround[curr.jobId]=sys_clock-curr.startTime;
            }
            //reduce remLength by one
            curr.remLength--;
            //if remLength is not 0 insert it back to the heap
            if(curr.remLength!=0){
                insertJob(H,curr);
            }
            //otherwise the job is processed
            else{
                processed++;
            }
        }
        else{
            cout<<-1<<" ";
        }
        //increment time step
        sys_clock++;
    }
    int sum=0;
    for(int i=1; i<=n; i++)
        sum+=turnaround[i];
    cout<<"\nAverage Turnaround Time is "<<((double)sum)/n;
    cout<<endl;  
}

int main(){
    int n;
    cout<<"Enter no. of jobs (n): ";
    cin>>n;
    int id, arrival, length;
    job *jobs=new job[n];
    cout<<"Enter the jobs:"<<endl;
    for(int i=0; i<n; i++){
        cin>>id>>arrival>>length;
        jobs[i]=job(id,arrival,length);
    }
    scheduler(jobs,n);
    return 0;
}