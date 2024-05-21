/*
    Name: Nisarg Upadhyaya
    Roll No: 19CS30031
*/

#include<iostream>
#include<fstream>

using namespace std;

class member{
    public:
        int data;
        int rank;
        member* parent;

        member(int data) : data(data), rank(0), parent(this) {}
        
        //find set with path compression
        member* find_set(){
            if(parent == this) return this;
            else{
                parent=parent->find_set();
                return parent;
            }
        }

        //union set with union by rank
        void union_set(member* other){
            member *curr_set, *other_set;
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

bool print_path(member*** chip, int n, bool** visited, int x, int y, ofstream &out){
    visited[x][y]=true;
    if(x==0 && y==0){
        out<<"("<<x<<", "<<y<<")";
        return true;
    }

    if(x>0 && (chip[x-1][y]->data) && (!visited[x-1][y]) && print_path(chip, n, visited, x-1, y, out)){
        out<<" -> ("<<x<<", "<<y<<")";
        return true;
    }
    if(y>0 && (chip[x][y-1]->data) && (!visited[x][y-1]) && print_path(chip, n, visited, x, y-1, out)){
        out<<" -> ("<<x<<", "<<y<<")";
        return true;
    }
    if(x<n-1 && (chip[x+1][y]->data) && (!visited[x+1][y]) && print_path(chip, n, visited, x+1, y, out)){
        out<<" -> ("<<x<<", "<<y<<")";
        return true;
    }
    if(y<n-1 && (chip[x][y+1]->data) && (!visited[x][y+1]) && print_path(chip, n, visited, x, y+1, out)){
        out<<" -> ("<<x<<", "<<y<<")";
        return true;
    }
    
    return false;
}

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, temp;
    in>>n;

    member ***chip=new member**[n];
    for(int i=0; i<n; i++){
        chip[i]=new member*[n];
        for(int j=0; j<n; j++){
            in>>temp;
            chip[i][j]=new member(temp);
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i>0 && chip[i][j]->data && chip[i-1][j]->data)
                chip[i][j]->union_set(chip[i-1][j]);
            if(j<n-1 && chip[i][j]->data && chip[i][j+1]->data)
                chip[i][j]->union_set(chip[i][j+1]);
        }
    }

    //bool found=false;
    bool **visited=new bool*[n];
    for(int i=0; i<n; i++){
        visited[i]=new bool[n];
        for(int j=0; j<n; j++)
            visited[i][j]=false;
    }
    for(int i=0; i<n; i++){
        if(chip[n-1][i]->data && (chip[0][0]->find_set() == chip[n-1][i]->find_set())){
            out<<"Path found"<<endl;
            print_path(chip, n, visited, n-1, i, out);
            out<<endl;
            return 0;
            //found=true;
            //break;
        }
    }

    out<<"Not found"<<endl;
    //out << (found ? "Path found" : "Path not found") << '\n';

    in.close();
    out.close();
    return 0;
}