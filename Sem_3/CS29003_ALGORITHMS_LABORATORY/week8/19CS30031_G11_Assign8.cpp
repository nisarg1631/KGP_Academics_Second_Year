/*
    Name: Nisarg Upadhyaya
    Roll No: 19CS30031
*/

#include <iostream>
#include <climits>
using namespace std;

int** create_2d_array(int sz){
    int **arr=new int*[sz];
    for(int i=0; i<sz; i++)
        arr[i]=new int[sz];
    return arr;
}

void reset_visited(int **visited, int sz){
    for(int i=0; i<sz; i++){
        for(int j=0; j<sz; j++)
            visited[i][j]=0;
    }
}

int leastTimeDijkstra(int n, int sx, int sy, int fx, int fy, int max_time, int **grid){
    int dist[n][n];
    bool visited[n][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            visited[i][j]=false;
            dist[i][j]=max_time;
        }
    }
    //source vertex at 0 distance
    dist[sx][sy]=0;
    visited[sx][sy]=true;

    //update adjacent neighbours
    if(sx>0 && !visited[sx-1][sy]){
        dist[sx-1][sy]=max(grid[sx-1][sy],dist[sx][sy]);
    }
    if(sy>0 && !visited[sx][sy-1]){
        dist[sx][sy-1]=max(grid[sx][sy-1],dist[sx][sy]);
    }
    if(sx<n-1 && !visited[sx+1][sy]){
        dist[sx+1][sy]=max(grid[sx+1][sy],dist[sx][sy]);
    }
    if(sy<n-1 && !visited[sx][sy+1]){
        dist[sx][sy+1]=max(grid[sx][sy+1],dist[sx][sy]);
    }

    int rep=(n*n)-1;
    while(rep--){
        int buff=max_time, nearx, neary;
        //getting the minimum time for current iteration
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(!visited[i][j] && dist[i][j]<=buff){
                    buff=dist[i][j];
                    nearx=i;
                    neary=j;
                }
            }
        }
        visited[nearx][neary]=true;
        //updating adjacent neighbours
        if(nearx>0 && !visited[nearx-1][neary]){
            dist[nearx-1][neary]=min(dist[nearx-1][neary],max(grid[nearx-1][neary],dist[nearx][neary]));
        }
        if(neary>0 && !visited[nearx][neary-1]){
            dist[nearx][neary-1]=min(dist[nearx][neary-1],max(grid[nearx][neary-1],dist[nearx][neary]));
        }
        if(nearx<n-1 && !visited[nearx+1][neary]){
            dist[nearx+1][neary]=min(dist[nearx+1][neary],max(grid[nearx+1][neary],dist[nearx][neary]));
        }
        if(neary<n-1 && !visited[nearx][neary+1]){
            dist[nearx][neary+1]=min(dist[nearx][neary+1],max(grid[nearx][neary+1],dist[nearx][neary]));
        }
    }
    return dist[fx][fy];
}

//dfs to check connectivity
bool dfs(int n, int x, int y, int fx, int fy, int t, int **grid, int **visited, int **nextstep){
    visited[x][y]=true;
    if(x==fx && y==fy)
        return true;
    if((x>0) && (max(grid[x-1][y],t)<=t) && (!visited[x-1][y]) && dfs(n,x-1,y,fx,fy,t,grid,visited,nextstep)){
        nextstep[x][y]=1;
        return true;
    }
    if((y<n-1) && (max(grid[x][y+1],t)<=t) && (!visited[x][y+1]) && dfs(n,x,y+1,fx,fy,t,grid,visited,nextstep)){
        nextstep[x][y]=2;
        return true;
    }
    if((x<n-1) && (max(grid[x+1][y],t)<=t) && (!visited[x+1][y]) && dfs(n,x+1,y,fx,fy,t,grid,visited,nextstep)){
        nextstep[x][y]=3;
        return true;
    }
    if((y>0) && (max(grid[x][y-1],t)<=t) && (!visited[x][y-1]) && dfs(n,x,y-1,fx,fy,t,grid,visited,nextstep)){
        nextstep[x][y]=4;
        return true;
    }
    return false;
}

void getmintime(int n, int sx, int sy, int fx, int fy, int max_time, int **grid){
    //create visited 2d array to keep track of nodes which have been processed
    /*
        create nextstep 2d array to keep track of path on which to move
        nextstep=1 -> (i,j) to (i-1,j)
        nextstep=2 -> (i,j) to (i,j+1)
        nextstep=3 -> (i,j) to (i+1,j)
        nextstep=4 -> (i,j) to (i,j-1)
    */
    int **visited=create_2d_array(n);
    int **nextstep=create_2d_array(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            visited[i][j]=0;
            nextstep[i][j]=0;
        }
    }
    //binary search for optimal time value
    int ans=0, l=0, r=max_time;
    while(l<=r){
        int mid=(l+r)/2;
        if(dfs(n,sx,sy,fx,fy,mid,grid,visited,nextstep)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
        reset_visited(visited,n);
    }
    //print path and optimal time
    cout<<"Minimum time taken is: "<<ans<<endl;
    cout<<"The path to reach from ("<<sx<<", "<<sy<<") to ("<<fx<<", "<<fy<<") is:"<<endl;
    int currx=sx, curry=sy, cnt=1;
    while(currx!=fx || curry!=fy){
        cout<<"("<<currx<<", "<<curry<<"), ";
        cnt++;
        int step=nextstep[currx][curry];
        if(step==1)
            currx--;
        else if(step==2)
            curry++;
        else if(step==3)
            currx++;
        else
            curry--;
    }
    cout<<"("<<currx<<", "<<curry<<")"<<endl;
    cout<<"The number of blocks traversed are: "<<cnt<<endl;
}

int main(){
    //input
    int n,sx,sy,fx,fy,max_time;
    max_time=-1;
    cin>>n;
    int **grid=create_2d_array(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin>>grid[i][j];
            max_time=max(max_time, grid[i][j]);
        }
    }
    cin>>sx>>sy>>fx>>fy;
    getmintime(n, sx, sy, fx, fy, max_time, grid);
    cout<<"From Dijkstra's Algorithm minimum time is: ";
    cout<<leastTimeDijkstra(n,sx,sy,fx,fy,max_time,grid)<<endl;
    return 0;
}