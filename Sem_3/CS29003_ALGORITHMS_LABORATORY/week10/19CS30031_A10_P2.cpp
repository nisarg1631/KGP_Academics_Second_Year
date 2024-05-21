/*
    Name: Nisarg Upadhyaya
    Roll No: 19CS30031
*/

#include <iostream>
#include <fstream>
using namespace std;

typedef struct _hashing{
    int key;
    struct _hashing *next, *head;
}hasht;

int gethash(int n, int size){
    return (n%size);
}

void init_hashtable(hasht *H, int size){
    for(int i=0; i<size; i++)
        H[i].next=NULL;
}

void add_entry(hasht *ptable, hasht *ctable, int counter, int portfolio, int size){
    int index;
    hasht *it, *prev;
    //adding to portfolio table
    index=gethash(portfolio,size);
    prev=ptable+index;
    it=prev->next;
    while(it!=NULL){
        if((it->key)==portfolio){
            int pos=gethash(counter,size);
            //adding to second level hash table
            (it->head)[pos].key=counter;
            break;
        }
        prev=it;
        it=it->next;
    }
    //new secondary table
    if(it==NULL){
        hasht *newentry=new hasht;
        newentry->next=NULL;
        newentry->key=portfolio;
        //creating second level hash table
        newentry->head=new hasht[size];
        for(int i=0; i<size; i++)
            (newentry->head)[i].key=-1;
        int pos=gethash(counter,size);
        //adding to second level hash table
        (newentry->head)[pos].key=counter;
        prev->next=newentry;
    }
    //adding to counterparty table
    index=gethash(counter,size);
    it=ctable+index;
    prev=it;
    it=it->next;
    while(it!=NULL){
        if((it->key)==counter){
            int pos=gethash(portfolio,size);
            //adding to second level hash table
            (it->head)[pos].key=portfolio;
            break;
        }
        prev=it;
        it=it->next;
    }
    if(it==NULL){
        hasht *newentry=new hasht;
        newentry->next=NULL;
        newentry->key=counter;
        //creating second level hash table
        newentry->head=new hasht[size];
        for(int i=0; i<size; i++)
            (newentry->head)[i].key=-1;
        int pos=gethash(portfolio,size);
        //adding to second level hash table
        (newentry->head)[pos].key=portfolio;
        prev->next=newentry;
    }
}

void delete_entry(hasht *ptable, hasht *ctable, int counter, int size){
    int index,i;
    hasht *it, *prev;
    //array to store portfolios of counterparty to be deleted
    int dcnt=0;
    int darr[100];
    //deleting from counterparty table
    index=gethash(counter,size);
    it=ctable+index;
    prev=it;
    it=it->next;
    while(it!=NULL){
        if((it->key)==counter)
            break;
        prev=it;
        it=it->next;
    }
    if(it!=NULL){
        prev->next=it->next;
        //store all elements to be deleted before deleting
        i=0;
        hasht *it2=it->head;
        while(i<size){
            darr[dcnt++]=it2[i].key;
            it2[i].key=-1;
            i++;
        }
        delete it;
    }
    //delete from portfolio table
    for(int i=0; i<dcnt; i++){
        index=gethash(darr[i],size);
        it=ptable+index;
        prev=it;
        it=it->next;
        while(it!=NULL){
            if((it->key)==darr[i])
                break;
            prev=it;
            it=it->next;
        }
        if(it!=NULL){
            //using secondary hashing to directly get position of counterparty to be deleted
            hasht *it2=it->head;
            it2[gethash(counter,size)].key=-1;
        }
    }
}

void print_table(hasht *table, int size, char c, ofstream &out){
    //going through primary hash table
    for(int i=0; i<size; i++){
        bool empty=true;
        hasht *it1=table[i].next;
        while(it1!=NULL){
            int curr=it1->key;
            hasht *it2=it1->head;
            //going through secondary hash table
            for(int j=0; j<size; j++){
                if(it2[j].key!=-1){
                    out<<c<<" "<<i<<" "<<curr<<" "<<it2[j].key<<endl;
                    empty=false;
                }
            }
            it1=it1->next;
        }
        if(empty){
            out<<c<<" "<<i<<" "<<-1<<" "<<-1<<endl;
        }
    }
}

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");
    int size, tc;
    in>>size>>tc;

    hasht *ptable=new hasht[size];
    hasht *ctable=new hasht[size];
    init_hashtable(ptable,size);
    init_hashtable(ctable,size);

    char op;
    int counter, portfolio;
    while(tc--){
        in>>op;
        if(op=='+'){
            in>>counter>>portfolio;
            add_entry(ptable, ctable, counter, portfolio, size);
        }
        if(op=='-'){
            in>>counter;
            delete_entry(ptable, ctable, counter, size);
        }
    }
    print_table(ptable,size,'p',out);
    print_table(ctable,size,'c',out);

    in.close();
    out.close();
    return 0;
}