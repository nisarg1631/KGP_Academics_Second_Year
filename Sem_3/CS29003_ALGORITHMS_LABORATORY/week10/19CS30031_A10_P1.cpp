/*
    Name: Nisarg Upadhyaya
    Roll No: 19CS30031
*/

#include <iostream>
#include <fstream>
using namespace std;

typedef struct _data{
    int value;
    struct _data *next;
}val;

typedef struct _hashing{
    int key;
    val *head;
    struct _hashing *next;
}hasht;

int gethash(int n, int size){
    return (n%size);
}

void init_hashtable(hasht *H, int size){
    for(int i=0; i<size; i++)
        H[i].next=NULL;
}

void add_data(hasht *loc, int newval){
    val *it=loc->head;
    val *prev;
    while(it!=NULL){
        prev=it;
        it=it->next;
    }
    val *newnode=new val;
    newnode->next=NULL;
    newnode->value=newval;
    prev->next=newnode;
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
            add_data(it,counter);
            break;
        }
        prev=it;
        it=it->next;
    }
    if(it==NULL){
        hasht *newentry=new hasht;
        newentry->next=NULL;
        newentry->key=portfolio;
        newentry->head=new val;
        newentry->head->next=NULL;
        newentry->head->value=counter;
        prev->next=newentry;
    }
    //adding to counterparty table
    index=gethash(counter,size);
    it=ctable+index;
    prev=it;
    it=it->next;
    while(it!=NULL){
        if((it->key)==counter){
            add_data(it,portfolio);
            break;
        }
        prev=it;
        it=it->next;
    }
    if(it==NULL){
        hasht *newentry=new hasht;
        newentry->next=NULL;
        newentry->key=counter;
        newentry->head=new val;
        newentry->head->next=NULL;
        newentry->head->value=portfolio;
        prev->next=newentry;
    }
}

void delete_entry(hasht *ptable, hasht *ctable, int counter, int size){
    int index;
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
        val *it2=it->head;
        val *it3;
        while(it2!=NULL){
            it3=it2->next;
            darr[dcnt++]=it2->value;
            delete it2;
            it2=it3;
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
            val *it2=it->head;
            val *it3=it2;
            while(it2!=NULL){
                if((it2->value)==counter){
                    if(it2==it3){
                        it->head=it2->next;
                        delete it2;
                    }
                    else{
                        it3->next=it2->next;
                        delete it2;
                    }
                    break;
                }
                it3=it2;
                it2=it2->next;
            }
            //remove portfolio if it becomes empty
            if((it->head)==NULL){
                prev->next=it->next;
                delete it;
            }
        }
    }
}

void print_table(hasht *table, int size, char c, ofstream &out){
    for(int i=0; i<size; i++){
        if(table[i].next==NULL){
            out<<c<<" "<<i<<" "<<-1<<" "<<-1<<endl;
        }
        else{
            hasht *it1=table[i].next;
            while(it1!=NULL){
                int curr=it1->key;
                val *it2=it1->head;
                while(it2!=NULL){
                    out<<c<<" "<<i<<" "<<curr<<" "<<(it2->value)<<endl;
                    it2=it2->next;
                }
                it1=it1->next;
            }
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