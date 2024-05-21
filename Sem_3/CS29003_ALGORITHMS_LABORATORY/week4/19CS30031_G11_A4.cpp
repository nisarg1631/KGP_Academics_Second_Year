#include <iostream>
#include <bits/stdc++.h>
#include <limits.h>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define MAXLEN 40
#define INTMAX 0x7fffffff

ifstream in("log.txt");
ofstream out("output.txt");

struct symbols{
    int pr, fr;
    char ch[2];
};

void swap(symbols *s1, symbols *s2){
    symbols temp=*s1;
    *s1=*s2;
    *s2=temp;
}

void sortarr(symbols freq[]){
    int index, minfr, minpr;
    for(int i=0; i<36; i++){
        minfr=INT_MAX;
        index=i;
        for(int j=i; j<36; j++){
            if(freq[j].fr<minfr){
                minfr=freq[j].fr;
                minpr=freq[j].pr;
                index=j;
            }
            else if(freq[j].fr==minfr){
                if(freq[j].pr<minpr){
                    minpr=freq[j].pr;
                    index=j;
                }
            }
        }
        swap(freq[i],freq[index]);
    }
}

class huffman{
    
    public:

        struct node{
            char *symbol;
            int frequency, pr;
            node *next, *left, *right;
            node(){
                left=right=NULL;
            }
        };

        node *root;
        int supercnt;

        huffman(){
            root=NULL;
            supercnt=0;
        }

        void insert_end(symbols *s){
            node *temp=new node;
            temp->symbol=s->ch;
            temp->frequency=s->fr;
            temp->pr=s->pr;
            temp->next=NULL;

            if(root==NULL){
                root=temp;
                return;
            }

            node *it=root;
            while(it->next!=NULL)
                it=it->next;
            it->next=temp;
        }

        //1 if s1 is greater than s2
        int compare(node *s1, node *s2){
            if(s1->frequency > s2->frequency) return 1;
            else if(s1->frequency==s2->frequency){
                if((s1->pr)<0 && (s2->pr)<0){
                    if(s1->pr < s2->pr) return 1;
                    else return 0;
                }
                else{
                    if(s1->pr > s2->pr) return 1;
                    else return 0;
                }
            }
            return 0;
        }

        void insert_pos(node *s){
            //less than root
            if(!compare(s,root)){
                s->next=root;
                root=s;
            }
            //otherwise
            node *prev=root, *curr=root->next;
            while(curr!=NULL){
                if(!compare(s,curr)){
                    prev->next=s;
                    s->next=curr;
                    return;
                }
                prev=curr;
                curr=curr->next;
            }
            prev->next=s;
            s->next=NULL;
        }

        void create_symbol(char **sym){
            int len=0;
            int cnt=supercnt;
            while(cnt){
                len++;
                cnt/=10;
            }
            cnt=supercnt;
            *sym=new char[len+2];
            (*sym)[len+1]='\0';
            (*sym)[0]='N';
            while(len){
                (*sym)[len]=char('0'+(cnt%10));
                cnt/=10;
                len--;
            }
        }

        void create_tree(){
                supercnt++;
                //in case only two nodes are there
                if(root->next->next==NULL){
                    node *n1=root;
                    node *n2=root->next;
                    node *super=new node;
                    super->left=n1;
                    super->right=n2;
                    create_symbol(&(super->symbol));
                    super->frequency=(n1->frequency+n2->frequency);
                    super->pr=(-supercnt);
                    root=super;
                    root->next=NULL;
                }
                //otherwise
                else{
                    node *n1=root;
                    node *n2=root->next;
                    root=(root->next)->next;
                    node *super=new node;
                    super->left=n1;
                    super->right=n2;
                    create_symbol(&(super->symbol));
                    super->frequency=((n1->frequency)+(n2->frequency));
                    super->pr=(-supercnt);
                    insert_pos(super);
                }
        }

        void tree(){
             while(root->next!=NULL){
                 create_tree();
             }
        }

        void init(symbols s[]){
            for(int i=0; i<36; i++)
                insert_end(&s[i]);
        }

        void preorder(node *src){
            if(src==NULL) return;
            out<<src->symbol<<" ("<<src->frequency<<") ,";
            preorder(src->left);
            preorder(src->right);
        }

        void print_list(){
            node *it=root;
            while(it!=NULL){
                out<<it->symbol<<"="<<it->frequency<<", ";
                it=it->next;
            }
            out<<endl;
        }

        void get_code(node *src, char buffer[], char codes[][MAXLEN]){
            if(src->left==NULL && src->right==NULL){
                if(src->pr>=0){
                    int it=0;
                    while(buffer[it]!='\0'){
                        codes[src->pr][it]=buffer[it];
                        it++;
                    } 
                    codes[src->pr][it]='\0';
                }
                return;
            }
            char l[MAXLEN], r[MAXLEN];
            //left turn
            int it=0;
            while(buffer[it]!='\0'){
                l[it]=buffer[it];
                it++;
            }
            l[it]='0'; it++; l[it]='\0';
            get_code(src->left, l, codes);
            //right turn
            it=0;
            while(buffer[it]!='\0'){
                l[it]=buffer[it];
                it++;
            }
            l[it]='1'; it++; l[it]='\0';
            get_code(src->right, r, codes);
        }
        
};

int main(){
    symbols freq[MAXLEN];
    for(int i=0; i<36; i++){
        freq[i].pr=i;
        if(i<=25){
            freq[i].ch[0]=char(freq[i].pr+'a');
        }
        else{
            freq[i].ch[0]=char(freq[i].pr-26+'0');
        }
        freq[i].ch[1]='\0';
        freq[i].fr=0;
    }
    int rep;
    in>>rep;
    while(rep--){
        char word[MAXLEN];
        in>>word;
        for(auto i:word){
            if(i=='\0') break;
            if(i>='a' && i<='z') freq[i-'a'].fr++;
            else freq[i-'0'+26].fr++;
        }
    }
    for(int i=0; i<36; i++){
        out<<freq[i].ch<<"="<<freq[i].fr;
        if(i!=35) out<<", ";
    }
    out<<endl;
    sortarr(freq);
    huffman H;
    H.init(freq);
    H.tree();
    H.preorder(H.root);
    char codes[36][MAXLEN];
    char buffer[MAXLEN];
    buffer[0]='\0';
    H.get_code(H.root, buffer, codes);
    for(int i=0; i<36; i++){
        out<<codes[i]<<endl;
    }
    return 0;
}