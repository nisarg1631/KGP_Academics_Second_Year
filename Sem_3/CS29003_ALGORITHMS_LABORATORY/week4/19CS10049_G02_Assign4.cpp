#include<bits/stdc++.h>
using namespace std;

const int max_word = 100;
const int max_len = 100;
const int max_depth = 100;

struct Node{
    char *symbol;
    int frequency;
    Node *next;
    Node *left;
    Node *right;
};

int compare(char s1[], char s2[]){              // If s1 > s2 in precedence
    if(s1[0]=='N' && s2[0]=='N'){
        int l1 = 0, l2 = 0;
        while(s1[l1]!='\0'){
            l1++;
        }
        while(s2[l2]!='\0'){
            l2++;
        }
        if(l1>l2){
            return 1;
        }
        if(l1<l2){
            return 0;
        }
        l1 = 0;
        l2 = 0;
        while(s1[l1]!='\0'){
            if(s1[l1]>s2[l2]){
                return 1;
            }
            if(s1[l1]< s2[l2]){
                return 0;
            }
            l1++;
            l2++;
        }
    }
    if(s1[0]=='N'){
        return 0;
    }
    if(s2[0]=='N'){
        return 1;
    }
    
    if(s1[0]>='0' && s1[0]<='9'){
        if(s2[0]>='0' && s2[0]<='9'){
            if(s1[0]>s2[0]){
                return 1;
            }
            return 0;
        }
        return 1;
    }
    if(s1[0]>='a' && s1[0]<='z'){
        if(s2[0]>='a' && s2[0]<='z'){
            if(s1[0]>s2[0]){
                return 1;
            }
            return 0;
        }
        return 0;
    }
}

void insert(Node **root, int fre, char sym[], Node *left, Node *right){
    Node *newnode = new Node;
    newnode->frequency = fre;
    newnode->symbol = new char[50];
    newnode->left = left;
    newnode->right = right;
    int i=0;
    while(sym[i]!='\0'){
        newnode->symbol[i] = sym[i];
        i++;
    }
    newnode->symbol[i] = '\0';
    if(*root == NULL){
        *root = newnode;
        newnode->next = NULL;
        return;
    }
    Node *temp = *root;
    Node *prev = *root;
    while(temp!=NULL && fre > temp->frequency){
        prev = temp;
        temp = temp->next;
    }
    while(temp!=NULL && temp->frequency == fre && compare(sym, temp->symbol)){    
        prev = temp;
        temp = temp->next;
    }
    if(temp==(*root)){
        newnode->next = *root;
        *root = newnode;
        return;
    }
    prev->next = newnode;
    newnode->next = temp;
    return;
}

void preorder(Node *root){
    if(root==NULL){
        return;
    }
    
}

void tree_traverse(Node *root, char C[], char H[][max_depth]){
    if(root->left==NULL && root->right==NULL){
        if(root->symbol[0] <='z' && root->symbol[0]>='a'){
            int curr = root->symbol[0] - 'a';
            int i=0;
            while(C[i]!='\0'){
                H[curr][i] = C[i];
                i++;
            }
        }
        else{
            int curr = root->symbol[0] - '0' + 26;
            int i=0;
            while(C[i]!='\0'){
                H[curr][i] = C[i];
                i++;
            }
        }
        return;
    }
    char t1[max_depth];
    char t2[max_depth];
    int i=0;
    while(C[i]!='\0'){
        t1[i] = C[i];
        i++;
    }
    t1[i++] = '0';
    t1[i] = '\0'; 
    tree_traverse(root->left, t1, H);
    i=0;
    while(C[i]!='\0'){
        t2[i] = C[i];
        i++;
    }
    t2[i++] = '1';
    t2[i] = '\0'; 
    tree_traverse(root->right, t2, H);
    return;
}

int main(){
    ifstream log;
    log.open("log.txt");
    int count;
    log>>count;
    char words[max_word][max_len];
    for(int i=0;i<count;i++){
        log>>words[i];
    }
    log.close();
    
    int freq[36] = {0};
    for(int i=0;i<count;i++){
        int j=0;
        while(words[i][j]!='\0'){
            if(words[i][j]>='a' && words[i][j]<='z'){
                freq[words[i][j]-'a']++;
            }
            else{
                freq[words[i][j]-'0'+26]++;
            }
            j++;
        }
    }
    ofstream out;
    out.open("output.txt");
    for(int i=0;i<36;i++){
        if(i<26){
            out<<"("<<(char)('a'+i)<<" = "<<freq[i]<<") ";
        }
        else{
            out<<"("<<i-26<<" = "<<freq[i]<<") ";
        }
    }
    out<<"\n";
    // Part 2
    Node *root = NULL;
    for(int i=0;i<36;i++){
        char sym0[50];
        sym0[0] = (i<26)?(char)('a'+i):(char)('0'+i-26);
        sym0[1] = '\0';
        insert(&root, freq[i], sym0, NULL, NULL);
    }
    int count1 = 1;
    while(root->next!=NULL){
        Node *t1 = root;
        Node *t2 = root->next;
        root = (root->next)->next;
        char sym0[50];
        sym0[0] = 'N';
        int i=1;
        char r_count[50];
        int j=0;
        int temp = count1;
        while(temp!=0){
            r_count[j++] = temp%10;
            temp/=10;
        }
        j--;
        while(j>=0){
            int a = r_count[j];
            sym0[i] = a+'0';
            i++;
            j--;
        }
        sym0[i] = '\0';
        count1++;
        insert(&root, t1->frequency + t2->frequency, sym0, t1, t2);
    }
    char H[36][max_depth];
    char C[max_depth];
    C[0] = '\0';
    tree_traverse(root, C, H);
    for(int i=0;i<36;i++){
        cout<<H[i]<<endl;
    }
    out.close();
    return 0;
}