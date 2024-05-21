/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Assignment: 3
Group: 11
*/

#include <iostream>
using namespace std;

typedef struct _point{
    int x,y;
    _point(){
        x=-1;
        y=-1;
    }
    _point(int _x, int _y){
        x=_x;
        y=_y;
    }
}point;

/*Queue Implementation*/
typedef struct{
    point *arr;
    int size, start_id, end_id;
}queue;

void init_queue(queue *q, int sz){
    q->arr=new point[sz];
    q->size=sz;
    q->start_id=-1;
    q->end_id=0;
}

int isEmpty_queue(queue q){
    if(q.start_id<q.end_id)
        return 1;
    else
        return 0;
}

void enqueue(queue *q, point input){
    (q->start_id)++;
    (q->arr)[q->start_id]=input;
}

point dequeue(queue *q){
    if(isEmpty_queue(*q))
        return point(-1,-1);
    (q->end_id)++;
    return (q->arr)[(q->end_id)-1];
}

/*Stack Implementation*/
typedef struct _LIFO{
    point data;
    struct _LIFO *next;
}stack;

void push(stack **top, point input){
	stack *new_elem=new stack;
	new_elem->data=input;
	new_elem->next=*top;
	*top=new_elem;
}

point pop(stack **top){
	if(*top==NULL)
		return point(-1,-1);
	else{
		stack *temp;
		point value;
		temp=(*top);
		value=(*top)->data;
		*top=(*top)->next;
		free(temp);
		return value;
	}	
}

int isEmpty_stack(stack *top){
	if(top==NULL)
		return 1;
	else
		return 0;
}

/*Grid Implementation*/
char** create_grid(int a, int b, int n, point *unstable){
    char **grid=new char*[a];
    for(int i=0; i<a; i++)
        grid[i]=new char[b];
    for(int i=0; i<a; i++)
        for(int j=0; j<b; j++)
            grid[i][j]='*';
    for(int i=0; i<n; i++)
        grid[unstable[i].x][unstable[i].y]='-';
    return grid;
}

void print_grid(int a, int b, char **grid){
    for(int i=0; i<a; i++){
        for(int j=0; j<b; j++)
            cout<<grid[i][j];
        cout<<'\n';
    }
}

/*Strategy 1*/
int bfs_strategy(int a, int b, char **grid, point src, point dst){
    bool **visited=new bool*[a];
    for(int i=0; i<a; i++)
        visited[i]=new bool[b];
    for(int i=0; i<a; i++)
        for(int j=0; j<b; j++)
            visited[i][j]=false;
    queue q;
    init_queue(&q,(a*b)+5);
    enqueue(&q,src);
    visited[src.x][src.y]=true;
    while(!isEmpty_queue(q)){
        point curr=dequeue(&q);
        if((curr.x==dst.x)&&(curr.y==dst.y))
            return 1;
        if(((curr.x-1)>=0) && (grid[curr.x-1][curr.y]=='*') && (!visited[curr.x-1][curr.y])){
            visited[curr.x-1][curr.y]=1;
            enqueue(&q,point(curr.x-1,curr.y));
        }
        if(((curr.x+1)<a) && (grid[curr.x+1][curr.y]=='*') && (!visited[curr.x+1][curr.y])){
            visited[curr.x+1][curr.y]=1;
            enqueue(&q,point(curr.x+1,curr.y));
        }
        if(((curr.y-1)>=0) && (grid[curr.x][curr.y-1]=='*') && (!visited[curr.x][curr.y-1])){
            visited[curr.x][curr.y-1]=1;
            enqueue(&q,point(curr.x,curr.y-1));
        }
        if(((curr.y+1)<b) && (grid[curr.x][curr.y+1]=='*') && (!visited[curr.x][curr.y+1])){
            visited[curr.x][curr.y+1]=1;
            enqueue(&q,point(curr.x,curr.y+1));
        }
    }
    return 0;
}

/*Strategy 2*/
void dfs_strategy(int a, int b, char **grid, point src, point dst){
    bool **visited=new bool*[a];
    for(int i=0; i<a; i++)
        visited[i]=new bool[b];
    for(int i=0; i<a; i++)
        for(int j=0; j<b; j++)
            visited[i][j]=false;
    stack *top=NULL;
    point curr=src;
    push(&top,curr);
    while((curr.x!=dst.x)||(curr.y!=dst.y)){
        visited[curr.x][curr.y]=true;
        if(((curr.x-1)>=0) && (grid[curr.x-1][curr.y]=='*') && (!visited[curr.x-1][curr.y])){
            push(&top,point(curr.x-1,curr.y));
        }
        else if(((curr.x+1)<a) && (grid[curr.x+1][curr.y]=='*') && (!visited[curr.x+1][curr.y])){
            push(&top,point(curr.x+1,curr.y));
        }
        else if(((curr.y-1)>=0) && (grid[curr.x][curr.y-1]=='*') && (!visited[curr.x][curr.y-1])){
            push(&top,point(curr.x,curr.y-1));
        }
        else if(((curr.y+1)<b) && (grid[curr.x][curr.y+1]=='*') && (!visited[curr.x][curr.y+1])){
            push(&top,point(curr.x,curr.y+1));
        }
        else{
            pop(&top);
        }
        curr=top->data;
    }
    stack *path=NULL;
    while(!isEmpty_stack(top)){
        push(&path,pop(&top));
    }
    while(!isEmpty_stack(path)){
        curr=pop(&path);
        cout<<"("<<curr.x<<", "<<curr.y<<") ";
    }
    cout<<'\n';
}

int main(){
    int a,b,n;
    cin>>a>>b>>n;
    point *unstable=new point[n];
    for(int i=0; i<n; i++)
        cin>>unstable[i].x;
    for(int i=0; i<n; i++)
        cin>>unstable[i].y;
    point src, dst;
    cin>>src.x>>src.y>>dst.x>>dst.y;
    char **grid=create_grid(a,b,n,unstable);
    cout<<"Grid of Stones is:"<<'\n';
    print_grid(a,b,grid);
    if(bfs_strategy(a,b,grid,src,dst)){
        cout<<"Path Exists"<<'\n';
        dfs_strategy(a,b,grid,src,dst);
    }
    else{
        cout<<"No Path Exists"<<'\n';
    }
    return 0;
}