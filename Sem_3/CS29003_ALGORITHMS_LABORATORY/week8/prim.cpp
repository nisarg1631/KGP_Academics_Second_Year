#include<iostream>
#include<climits>
using namespace std;

struct edge{
    int src,dst,weight;
    edge() : src(0), dst(0), weight(0) {}
    edge(int src, int dst, int weight) : src(src), dst(dst), weight(weight) {}

    void printedge(){
        cout<<"Source: "<<src<<", Destination: "<<dst<<", Weight: "<<weight<<endl;
    }
};

edge* prim(int n, int **W, int s){
    edge *mst=new edge[n-1];
    int *dist=new int[n+1];
    bool visited[n+1];
    int parent[n+1];

    for(int i=1; i<=n; i++){
        visited[i]=false;
        parent[i]=-1;
        dist[i]=W[s][i];
        if(W[s][i]!=INT_MAX)
            parent[i]=s;
    }
    parent[s]=0;
    dist[s]=0;
    visited[s]=true;

    int it=0;
    while(it!=n-1){
        int buff=INT_MAX, near;
        for(int i=1; i<=n; i++){
            if(!visited[i] && dist[i]<=buff){
                buff=dist[i];
                near=i;
            }
        }
        mst[it++]=edge(parent[near],near,dist[near]);
        visited[near]=true;
        for(int i=1; i<=n; i++){
            if(!visited[i] && W[near][i]!=INT_MAX){
                if(W[near][i]<dist[i]){
                    dist[i]=W[near][i];
                    parent[i]=near;
                }
            }
        }
    }
    return mst;
}

int main(){
    int n,e,s;
    cin>>n>>e;
    int **W=new int*[n+1];
    for(int i=0; i<n+1; i++)
        W[i]=new int[n+1];
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(i==j) W[i][j]=0;
            else W[i][j]=INT_MAX;
        }
    }
    int u,v,w;
    for(int i=0; i<e; i++){
        cin>>u>>v>>w;
        W[u][v]=min(W[u][v],w);
        W[v][u]=min(W[v][u],w);
    }
    cin>>s;
    edge *ans=prim(n, W, s);
    for(int i=0; i<n-1; i++){
        ans[i].printedge();
    }
    cout<<endl;
    return 0;
}