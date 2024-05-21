#include<iostream>
#include<fstream>
#include<string.h>
#include<assert.h>

#define MAXLEN 200
#define ALPHABET 30

using namespace std;

class type1{
    public:
        int len, *elems, last;

        type1(){}
        type1(int _len, int* temp){
            len=_len-1;
            elems=new int[len];
            for(int i=0; i<len; i++){
                elems[i]=temp[i];
            }
            last=temp[len];
        }

        bool check(bool* arr){
            bool flag=true;
            for(int i=0; i<len; i++){
                flag&=arr[elems[i]];
            }
            return (flag ? arr[last]:true);
        }

};

class type2{
    public:
        int len, *elems;
        
        type2(){}
        type2(int _len, int* temp){
            len=_len;
            elems=new int[len];
            for(int i=0; i<len; i++){
                elems[i]=temp[i];
            }
        }

        bool check(bool* arr){
            bool flag=true;
            for(int i=0; i<len; i++){
                flag&=arr[elems[i]];
            }
            return (flag ? false:true);
        }

};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, n1, n2;
    in>>n; in.get();
    n1=n2=0;
    char clauses[n][MAXLEN];
    for(int i=0; i<n; i++){
        in.getline(clauses[i],MAXLEN);
        if(!strncmp(clauses[i],"NEG",3)) n2++;
        else if(strncmp(clauses[i],"IMP",3)) n1++;
    }
    
    bool literal[ALPHABET]={false};
    bool ispresent[ALPHABET]={false};
    type1 **list1=new type1*[n1];
    type2 **list2=new type2*[n2];
    int it1,it2;
    it1=it2=0;

    /*parsing start*/
    for(int i=0; i<n; i++){
        if(!strncmp(clauses[i],"IMP",3)){
            ispresent[clauses[i][4]-'a']=literal[clauses[i][4]-'a']=true;
            //out<<clauses[i][4]<<endl;
        }
        else if(!strncmp(clauses[i],"NEG",3)){
            int temp[ALPHABET];
            int len=0;
            for(int j=0; j<strlen(clauses[i]); j++){
                if((clauses[i][j]>='a') && (clauses[i][j]<='z')){
                    temp[len++]=clauses[i][j]-'a';
                    ispresent[clauses[i][j]-'a']=true;
                }
            }
            //create new formula 2
            list2[it2++]=new type2(len, temp);
        }
        else{
            int temp[ALPHABET];
            int len=0;
            for(int j=0; j<strlen(clauses[i]); j++){
                if((clauses[i][j]>='a') && (clauses[i][j]<='z')){
                    temp[len++]=clauses[i][j]-'a';
                    ispresent[clauses[i][j]-'a']=true;
                }
            }
            //create new formula 1
            list1[it1++]=new type1(len, temp);
        }
    }
    /*parsing end*/

    bool done=false;
    while(!done){
        done=true;
        for(int i=0; i<n1; i++){
            if(!(list1[i]->check(literal))){
                done=false;
                literal[list1[i]->last]=true;
            }
        }
    }

    done=false;
    for(int i=0; i<n2; i++){
        if(!(list2[i]->check(literal))){
            done=true;
            out<<"unsatisfiable"<<endl;
            break;
        }
    }
    if(!done){
        for(int i=0; i<26; i++){
            if(ispresent[i]){
                out<<char(i+'a')<<" = "<<(literal[i] ? "true":"false")<<endl;
            }
        }
        out<<"satisfiable"<<endl;
    }

    /*assert((it1==n1)&&(it2==n2));
    for(int i=0; i<n1; i++){
        for(int j=0; j<list1[i]->len; j++){
            out<<char(list1[i]->elems[j]+'a')<<" ";
        }
        out<<char(list1[i]->last+'a')<<endl;
    }
    for(int i=0; i<n2; i++){
        for(int j=0; j<list2[i]->len; j++){
            out<<char(list2[i]->elems[j]+'a')<<" ";
        }
        out<<endl;
    }*/

    in.close();
    out.close();
    return 0;
}