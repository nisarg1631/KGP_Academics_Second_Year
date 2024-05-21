#include<iostream>
using namespace std;

struct node{
    int vertex;
    struct node *next;
};

struct Graph{
    int numVertices;
    struct node **adjLists;
};

class graph_utils{
    public:
        Graph G;
        
        graph_utils(int n){
            G.numVertices=n;
            G.adjLists=new struct node*[n];
            for(int i=0; i<n; i++){
                G.adjLists[i]=NULL;
            }
        }

        void add_edge_dir(int src, int dest){
            struct node* new_node=new struct node;
            new_node->vertex=dest;
            new_node->next=G.adjLists[src];
            G.adjLists[src]=new_node;
        }

        void add_edge_undir(int n1, int n2){
            add_edge_dir(n1,n2);
            add_edge_dir(n2,n1);
        }

        void print(){
            for(int i=0; i<G.numVertices; i++){
                cout<<"Node "<<i<<" ";
                struct node *it=G.adjLists[i];
                while(it!=NULL){
                    cout<<"-> "<<it->vertex<<" ";
                    it=it->next;
                }
                cout<<'\n';
            }
        }
};

int main(){
    int n,e;
    cin>>n>>e;
    graph_utils mygraph(n);
    int u,v;
    while(e--){
        cin>>u>>v;
        mygraph.add_edge_undir(u,v);
    }
    mygraph.print();
    return 0;
}