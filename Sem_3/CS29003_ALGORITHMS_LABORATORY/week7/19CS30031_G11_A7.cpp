/*
    Name: Nisarg Upadhyaya
    Roll No: 19CS30031
*/

#include<iostream>
#include<stdlib.h>

using namespace std;

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

void findtreasure(node*** grid, bool** H, bool** V, int m, int n){
    int cnt=0, flag, row, col;
    while(cnt!=((m*n)-1)){

        //if m is 1 then only vertical walls exist
        if(m==1){
            flag=0;
        }
        //else if n is 1 then only horizontal walls exist
        else if(n==1){
            flag=1;
        }
        //else randomly decide to remove horizontal wall or vertical
        else{
            flag=rand()%2;
        }

        //if flag is 1 then horizontal else vertical
        if(flag){
            //horizontal range from [0,m-2] and [0,n-1]
            row=rand()%(m-1);
            col=rand()%n;
            //remove wall if it is not removed and the cells adjacent to wall are not connected
            if(H[row][col] && (grid[row][col]->find_set() != grid[row+1][col]->find_set())){
                H[row][col]=false;
                grid[row][col]->merge_set(grid[row+1][col]);
                cnt++;
            }
        }
        else{
            //vertical range from [0,m-1] and [0,n-2]
            row=rand()%m;
            col=rand()%(n-1);
            //remove wall if it is not removed and the cells adjacent to wall are not connected
            if(V[row][col] && (grid[row][col]->find_set() != grid[row][col+1]->find_set())){
                V[row][col]=false;
                grid[row][col]->merge_set(grid[row][col+1]);
                cnt++;
            }
        }
    }
}

void printgrid(bool** H, bool** V, int m, int n){
    //printing upper wall
    cout<<'\t';
    for(int i=0; i<n; i++){
        cout<<"+";
        cout<<(i ? "---" : "   ");
    }
    cout<<"+"<<endl;
    //print rest of the grid
    int flag=0, hrow=0, vrow=0;
    while(flag != ((2*m)-1)){
        cout<<'\t';
        //if flag is odd we have to print horizontal walls
        if(flag%2){
            for(int i=0; i<n; i++){
                cout<<"+";
                cout<<(H[hrow][i] ? "---" : "   ");
            }
            cout<<"+"<<endl;
            hrow++;
        }
        //if flag is even we have to print vertical walls
        else{
            cout<<"|   ";
            for(int i=0; i<n-1; i++){
                cout<<(V[vrow][i] ? "|" : " ");
                cout<<"   ";
            }
            if(vrow != (m-1)) cout<<"|";
            cout<<endl;
            vrow++;
        }
        flag++;
    }
    //printing bottom wall
    cout<<'\t';
    for(int i=0; i<n; i++)
        cout<<"+---";
    cout<<"+\n"<<endl;
}

int main(int argc, char* argv[]){
    srand((unsigned int)time(NULL));

    //getting m and n from command line arguments
    int m, n;
    //if insufficient arguments passed 
    if(argc<3){
        m=n=10;
    }
    else{
        m=atoi(argv[1]);
        n=atoi(argv[2]);
    }

    //creating m*n grid and initialising each chamber as singleton set
    node ***grid=new node**[m];
    for(int i=0; i<m; i++){
        grid[i]=new node*[n];
        for(int j=0; j<n; j++){
            grid[i][j]=new node();
        }
    }

    //H_init and V_init store initial wall data, H and V are passed to findtreasure and store final wall data
    bool **H, **H_init, **V, **V_init;
    H_init=new bool*[m-1];
    H=new bool*[m-1];
    V_init=new bool*[m];
    V=new bool*[m];
    for(int i=0; i<m-1; i++){
        H_init[i]=new bool[n];
        H[i]=new bool[n];
        for(int j=0; j<n; j++)
            H_init[i][j]=H[i][j]=true;
    }
    for(int i=0; i<m; i++){
        V_init[i]=new bool[n-1];
        V[i]=new bool[n-1];
        for(int j=0; j<n-1; j++)
            V_init[i][j]=V[i][j]=true;
    }

    findtreasure(grid, H, V, m, n);

    if(grid[0][0]->find_set() == grid[m-1][n-1]->find_set())
        cout<<"The final chamber can be reached from the start chamber.\n"<<endl;
    else //this should not happen, a path will always be generated
        cout<<"The final chamber can't be reached from the start chamber.\n"<<endl;

    cout<<"Initial Grid\n"<<endl;
    printgrid(H_init, V_init, m, n);
    cout<<"Final Grid\n"<<endl;
    printgrid(H, V ,m, n);

    return 0;
}