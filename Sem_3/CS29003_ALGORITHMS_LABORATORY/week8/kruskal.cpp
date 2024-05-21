#include <iostream>
using namespace std;

struct edge{
    int src,dst,weight;
    edge() : src(0), dst(0), weight(0) {}
    edge(int src, int dst, int weight) : src(src), dst(dst), weight(weight) {}

    void printedge(){
        cout<<"Source: "<<src<<", Destination: "<<dst<<", Weight: "<<weight<<endl;
    }
};

class node{
    public:
        int rank;
        node* parent;

        node(){
            make_set();
        }

        //make set initializing to singleton set
        void make_set(){
            rank=0;
            parent=this;
        }
        
        //find set with path compression
        node* find_set(){
            if(parent == this) return this;
            else{
                parent=parent->find_set();
                return parent;
            }
        }

        //union set with union by rank
        void merge_set(node* other){
            node *curr_set, *other_set;
            curr_set=this->find_set();
            other_set=other->find_set();

            if(curr_set != other_set){
                if(curr_set->rank == other_set->rank){
                    other_set->parent=curr_set;
                    (curr_set->rank)++;
                }
                else if(curr_set->rank > other_set->rank)
                    other_set->parent=curr_set;
                else
                    curr_set->parent=other_set;
            }
        }
};

node** dsu(int n){
    node** S=new node*[n];
    for(int i=0; i<n; i++)
        S[i]=new node();
    return S;
}

/*
    compare(element a, element b)
    returns true if a is strictly greater b
*/
bool compare(edge a, edge b){
    return (a.weight>b.weight);
}

void merge(edge *arr, int l, int mid, int r){
    int nl=mid-l+1, nr=r-mid;
    edge *left=new edge[nl];
    edge *right=new edge[nr];

    for(int i=0; i<nl; i++)
        left[i]=arr[l+i];
    for(int i=0; i<nr; i++)
        right[i]=arr[mid+1+i];
    
    int itl=0, itr=0, it=l;
    while(itl<nl && itr<nr){
        if(compare(left[itl],right[itr])){
            arr[it]=right[itr];
            itr++;
        }
        else{
            arr[it]=left[itl];
            itl++;
        }
        it++;
    }
    while(itl<nl){
        arr[it]=left[itl];
        itl++, it++;
    }
    while(itr<nr){
        arr[it]=right[itr];
        itr++, it++;
    }

    delete[] left;
    delete[] right;
}

void mergesort(edge *arr, int l, int r){
    if(l<r){
        int mid=(l+r)/2;
        mergesort(arr,l,mid);
        mergesort(arr,mid+1,r);
        merge(arr,l,mid,r);
    }
}

edge* kruskal(int n, int e, edge *arr){
    node **vertex=dsu(n);
    edge *mst=new edge[n-1];
    mergesort(arr,0,e-1);
    int it=0, i=0;
    while(it!=n-1){
        if(vertex[arr[i].src]->find_set()!=vertex[arr[i].dst]->find_set()){
            mst[it++]=arr[i];
            vertex[arr[i].src]->merge_set(vertex[arr[i].dst]);
        }
        i++;
    }
    return mst;
}

int main(){
    int n,e;
    cin>>n>>e;
    edge *arr=new edge[e];
    int u,v,w;
    for(int i=0; i<e; i++){
        cin>>u>>v>>w;
        arr[i]=edge(u,v,w);
    }
    edge *mst=kruskal(n,e,arr);
    for(int i=0; i<n-1; i++){
        mst[i].printedge();
    }
    return 0;
}