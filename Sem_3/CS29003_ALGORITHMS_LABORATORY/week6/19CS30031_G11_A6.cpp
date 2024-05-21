/*
    Name: Nisarg Upadhyaya
    Roll No: 19CS30031
    CS29003 ALGORITHMS LABORATORY
    Assignment 6 (Greedy Algorithms)
*/

#include<iostream>
#include<fstream>

#define MAXTIME 100000

using namespace std;

struct interval{
    int start, end;
};

//utility function to get max of two numbers
int max(int num1, int num2){
	return (num1>num2 ? num1 : num2); 
}
//utility function to get min of two numbers
int min(int num1, int num2){
	return (num1<num2 ? num1 : num2); 
}

//utility function to swap two numbers
void swap(int* num1, int* num2){
    int temp=*num1;
    *num1=*num2;
    *num2=temp;
}

/*
    greedy function to check if for a specific order of visits, 
    it is possible for people to visit with a minimum time interval between two visits=gap,
    returns true if possible otherwise false,
    GREEDY: assign the first person the start of his interval,
            second person onwards start checking if (visit_time_of_previous_person + gap) > (end_time_of_current_person)
            if this holds true then it is not possible to maintain minimum time interval of gap, return false,
            otherwise assign the current person the next best slot of visit, i.e.,
            either his start_time or visit_time_of_previous_person + gap, whichever is maximum,
            if all person can be assigned times this way of visit then return true
*/
bool isValid(interval* data, int n, int* order, int gap){
    int prev=data[order[0]].start;
    for(int i=1; i<n; i++){
        if(data[order[i]].end<(prev+gap)){
            return false;
        }
        else{
            prev=max(data[order[i]].start, prev+gap);
        }
    }
    return true;
}

/*
    this function fetches the best possible minimum time interval using binary search,
    initial range [min_start_time, max_end_time]
    binary search on this interval using the above greedy function,
    if mid returns true then check from mid+1 to r,
    else check from l to mid-1
*/
int get_max_gap(interval* data, int n, int* order){
    int l=MAXTIME,r=0;
    for(int i=0; i<n; i++){
        l=min(l,data[i].start);
        r=max(r,data[i].end);
    }
    int ans=0;
    while(l<=r){
        int mid=(l+r)/2;
        if(isValid(data, n, order, mid)){
            ans=mid;
            l=mid+1;
        }
        else r=mid-1;
    }
    return ans;
}

/*
    this function gets the optimal value of minimum time interval 
    for a specific order of visit using the above get_max_gap function,
    if the current optimal is better than optimal_so_far then current optimal is set as answer,
    and the best order of visits is updated with the current order of visits
*/
void schedule_visits(int* order, int n, int ind, int* best, int* ans, interval* data){
    if(ind==1){
        int curr=get_max_gap(data,n,order);
        if(curr>(*ans)){
            *ans=curr;
            for(int i=0; i<n; i++){
                best[i]=order[i];
            }
        }
        return;
    }
    for(int i=0; i<ind; i++){
        schedule_visits(order,n,ind-1,best,ans,data);
        if(ind%2) swap(&order[0],&order[ind-1]);
        else swap(&order[i],&order[ind-1]);
    }
}

int main(){
    ifstream in("input1.txt");
    ofstream out("output1.txt");

    int n;
    in>>n;
    interval* data=new interval[n];
    int* order=new int[n];
    int* best_order= new int[n];
    for(int i=0; i<n; i++){
        in>>data[i].start>>data[i].end;
        data[i].start*=60;
        data[i].end*=60;
        order[i]=i;
        best_order[i]=i;
    }

    int ans=0;
    schedule_visits(order,n,n,best_order,&ans,data);

    out<<ans/60<<":";
    if((ans%60)>9) out<<ans%60<<endl;
    else out<<"0"<<ans%60<<endl;
    for(int i=0; i<n; i++) out<<best_order[i]<<" ";
    out<<endl;

    in.close();
    out.close();
    return 0;
}