#include <iostream>
using namespace std;

struct job{
    int id, burst, remaining, arrival, priority;

    job(){
        id=burst=remaining=arrival=priority=-1;
    }
    job(int _id, int _burst, int _arrival, int _priority){
        id=_id;
        burst=remaining=_burst;
        arrival=_arrival;
        priority=_priority;
    }

    /*
        function to tie break if two jobs have same priority
        returns true if current job has lesser remaining time
        if tie still persists returns true if current job has lower id
    */
    bool isSmallerThan(job j){
        if(remaining!=j.remaining)
            return remaining<j.remaining;
        else
            return id<j.id;
    }
};

void swap(job& j1, job& j2){
    job temp=j1;
    j1=j2;
    j2=temp;
}

class min_heap{
    public:
        job *arr;
        int max_size, curr_size;

        //by default set max_size to 1000
        min_heap(){
            max_size=1000;
            curr_size=0;
            arr=new job[max_size+1];
        }
        //set max size as demanded
        min_heap(int n){
            max_size=n;
            curr_size=0;
            arr=new job[max_size+1];
        }

        int parent(int index){
            return (index/2);
        }
        int left(int index){
            return (2*index);
        }
        int right(int index){
            return ((2*index)+1);
        }

        void heapify(int index){
            int l=left(index);
            int r=right(index);
            int smallest=index;
            if(l<=curr_size && arr[l].isSmallerThan(arr[smallest]))
                smallest=l;
            if(r<=curr_size && arr[r].isSmallerThan(arr[smallest]))
                smallest=r;
            if(smallest!=index){
                swap(arr[index],arr[smallest]);
                heapify(smallest);
            }
        }

        job get_min(){
            return arr[1];
        }

        job extract_min(){
            if(curr_size<1){
                cout<<"Heap Underflow"<<endl;
                return job();
            }
            job minimum=arr[1];
            arr[1]=arr[curr_size];
            curr_size--;
            heapify(1);
            return minimum;
        }

        void insert(job j){
            if(curr_size==max_size){
                cout<<"Heap Overflow"<<endl;
                return;
            }
            curr_size++;
            arr[curr_size]=j;
            int i=curr_size;
            while(i>1 && arr[i].isSmallerThan(arr[parent(i)])){
                swap(arr[i],arr[parent(i)]);
                i=parent(i);
            }
        }
};

int main(){
    int sys_clock, completed;
    int n;
    cin>>n;
    int id, arrival, burst, priority;
    job *jobs=new job[n];
    for(int i=0; i<n; i++){
        cin>>id>>arrival>>burst>>priority;
        jobs[i]=job(id,burst,arrival,priority);
    }

    min_heap *processes=new min_heap[6];
    int *st_time=new int[n+1];
    int *en_time=new int[n+1];

    sys_clock=completed=0;
    while(completed!=n){
        //add new jobs which arrive
        for(int i=0; i<n; i++){
            if(jobs[i].arrival==sys_clock){
                processes[jobs[i].priority].insert(jobs[i]);
            }
        }

        //run job according to priority
        

        //increase system time by one
        sys_clock++;
    }

    return 0;
}