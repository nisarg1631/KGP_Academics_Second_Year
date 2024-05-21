#include <iostream>
using namespace std;

class heap{
    public:
        int *arr, max_size, curr_size;

        //by default set max_size to 1000
        heap(){
            max_size=1000;
            curr_size=0;
            arr=new int[max_size+1];
        }
        //set max size as demanded
        heap(int n){
            max_size=n;
            curr_size=0;
            arr=new int[max_size+1];
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
            int largest=index;
            if(l<=curr_size && arr[l]>arr[largest])
                largest=l;
            if(r<=curr_size && arr[r]>arr[largest])
                largest=r;
            if(largest!=index){
                swap(arr[index],arr[largest]);
                heapify(largest);
            }
        }

        int get_max(){
            return arr[1];
        }

        int delete_max(){
            if(curr_size<1){
                cout<<"Heap Underflow"<<endl;
                return -1;
            }
            int maximum=arr[1];
            arr[1]=arr[curr_size];
            curr_size--;
            heapify(1);
            return maximum;
        }

        void insert(int val){
            if(curr_size==max_size){
                cout<<"Heap Overflow"<<endl;
                return;
            }
            curr_size++;
            arr[curr_size]=val;
            int i=curr_size;
            while(i>1 && arr[parent(i)]<arr[i]){
                swap(arr[i],arr[parent(i)]);
                i=parent(i);
            }
        }
};

int main(){
    heap pq;
    int cnt=0;
    while(1){
        int n;
        cin>>n;
        if(n==-1) break;
        pq.insert(n);
        cout<<"Max so far: "<<pq.get_max()<<endl;
        cnt++;
    }
    while(cnt--)
        cout<<pq.delete_max()<<" ";
    cout<<endl;
    cout<<pq.delete_max()<<endl;
    return 0;
}