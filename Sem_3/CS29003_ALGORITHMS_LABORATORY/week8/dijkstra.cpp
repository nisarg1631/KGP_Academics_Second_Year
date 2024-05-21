#include<iostream>
#include<climits>
using namespace std;

int* dijkstra(int n, int **W, int s){
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
    int rep=n-1;
    while(rep--){
        int buff=INT_MAX, near;
        for(int i=1; i<=n; i++){
            if(!visited[i] && dist[i]<=buff){
                buff=dist[i];
                near=i;
            }
        }
        visited[near]=true;
        for(int i=1; i<=n; i++){
            if(!visited[i] && W[near][i]!=INT_MAX && dist[near]!=INT_MAX){
                if((dist[near]+W[near][i])<dist[i]){
                    dist[i]=dist[near]+W[near][i];
                    parent[i]=near;
                }
            }
        }
    }
    return dist;
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
    }
    cin>>s;
    int *ans=dijkstra(n, W, s);
    for(int i=1; i<=n; i++){
        if(ans[i]!=INT_MAX) cout<<ans[i]<<" ";
        else cout<<-1<<" ";
    }
    cout<<endl;
    return 0;
}