/*
    Name: Nisarg Upadhyaya
    Roll No: 19CS30031
*/

#include <iostream>
using namespace std;

#define MAX_SIZE 100

typedef struct _jobpair{
    int jobid_from, jobid_to;
}jobpair;

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
    int id_index[MAX_SIZE]; //array to store index of particular job id in heap
    int numJobs;
}newheap;

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
void heapify(newheap *H, int index){
    int l=left(index);
    int r=right(index);
    int smallest=index;
    if(l<=(H->numJobs) && isSmallerThan((H->list)[l],(H->list)[smallest]))
        smallest=l;
    if(r<=(H->numJobs) && isSmallerThan((H->list)[r],(H->list)[smallest]))
        smallest=r;
    if(smallest!=index){
        swap((H->list)[index],(H->list)[smallest]);
        swap((H->id_index)[(H->list)[index].jobId],(H->id_index)[(H->list)[smallest].jobId]);
        heapify(H,smallest);
    }
}
/* UTILITY FUNCTIONS FOR HEAPS */

void initHeap(newheap *H){
    H->numJobs=0;
    for(int i=0; i<MAX_SIZE; i++){
        (H->id_index)[i]=0;
    }
}

void insertJob(newheap *H, job j){
    (H->numJobs)++;
    (H->list)[H->numJobs]=j;
    (H->id_index)[j.jobId]=(H->numJobs);
    int i=(H->numJobs);
    while(i>1 && isSmallerThan((H->list)[i],(H->list)[parent(i)])){
        swap((H->list)[i],(H->list)[parent(i)]);
        swap((H->id_index)[(H->list)[i].jobId],(H->id_index)[(H->list)[parent(i)].jobId]);
        i=parent(i);
    }
}

int extractMinJob(newheap *H, job *j){
    if((H->numJobs)<1){
        return -1;
    }
    job minimum=(H->list)[1];
    (H->list)[1]=(H->list)[H->numJobs];
    (H->id_index)[(H->list)[H->numJobs].jobId]=1;
    (H->numJobs)--;
    heapify(H,1);
    (H->id_index)[minimum.jobId]=0;
    *j=minimum;
    return 0;
}

void decreaseKey(newheap *H, int jid){
    int i=(H->id_index)[jid];
    if(i){
        ((H->list)[i].remLength)/=2;
        ((H->list)[i].jobLength)/=2;
        while(i>1 && isSmallerThan((H->list)[i],(H->list)[parent(i)])){
            swap((H->list)[i],(H->list)[parent(i)]);
            swap((H->id_index)[(H->list)[i].jobId],(H->id_index)[(H->list)[parent(i)].jobId]);
            i=parent(i);
        }
    }
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

void newScheduler(job *jobList, int n, jobpair *pairList, int m){
    //store dependency pairs in 2d array
    int related[MAX_SIZE][MAX_SIZE];
    int cnt[MAX_SIZE];
    for(int i=0; i<MAX_SIZE; i++)
        cnt[i]=0;
    for(int i=0; i<m; i++){
        related[pairList[i].jobid_from][cnt[pairList[i].jobid_from]]=pairList[i].jobid_to;
        cnt[pairList[i].jobid_from]++;
    }
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
    //create started array to check if a job has been started yet
    bool *started=new bool[n+1];
    for(int i=0; i<=n; i++)
        started[i]=false;
    int sys_clock=0;
    int processed=0;

    //create newheap to store jobs according to priority
    newheap *H=new newheap;
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
        //get current job to process from newheap
        job curr;
        if(extractMinJob(H,&curr)==0){
            cout<<curr.jobId<<" ";
            //if job appeared for first time then set its turnaround time
            if(curr.jobLength==curr.remLength){
                started[curr.jobId]=true;
                turnaround[curr.jobId]=sys_clock-curr.startTime;
            }
            //reduce remLength by one
            curr.remLength--;
            //if remLength is not 0 insert it back to the newheap
            if(curr.remLength!=0){
                insertJob(H,curr);
            }
            //otherwise the job is processed
            else{
                processed++;
                //update dependency
                for(int i=0; i<cnt[curr.jobId]; i++){
                    if(!started[related[curr.jobId][i]])
                        decreaseKey(H,related[curr.jobId][i]);
                }
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
    cout<<"Enter the number of dependency pairs"<<endl;
    int m;
    cin>>m;
    jobpair *pairlist=new jobpair[m];
    cout<<"Enter the dependency pairs"<<endl;
    for(int i=0; i<m; i++)
        cin>>pairlist[i].jobid_from>>pairlist[i].jobid_to;
    newScheduler(jobs,n,pairlist,m);
    return 0;
}