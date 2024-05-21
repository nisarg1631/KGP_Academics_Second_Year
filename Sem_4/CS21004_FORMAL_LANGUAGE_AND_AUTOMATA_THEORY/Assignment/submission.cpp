#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct NFA{
    /*
    *   n = number of states  
    *   m = size of alphabet
    *   S = start states
    *   F = final states
    *   delta = transition function
    */
    uint32_t n, m, S, F, **delta;
    NFA() : n(0U), m(0U), S(0U), F(0U) {};
};

struct DFA{
    /*
    *   n = number of states  
    *   m = size of alphabet
    *   s = start state
    *   F = final states
    *   cntF = number of final states
    *   delta = transition function
    */
    uint32_t n, m, s, *F, cntF, **delta;
    DFA() : n(0U), m(0U), s(0U), cntF(0U) {};
    void init(){
        F = new uint32_t[(n+31)/32];
        for(int i=0; i<(n+31)/32; i++)
            F[i] = 0;
        delta = new uint32_t *[n];
        for(int i=0; i<n; i++){
            delta[i] = new uint32_t[m];
            for(int j=0; j<m; j++)
                delta[i][j] = 0;
        }
    }
};

void setBit(uint32_t &num, const int pos){
    num |= (1U<<pos);
}
void setBit(uint32_t *arr, const int pos){
    setBit(arr[pos/32],pos%32);
}

bool isSet(const uint32_t num, const int pos){
    return (num & (1U<<pos));
}
bool isSet(const uint32_t *arr, const int pos){
    return isSet(arr[pos/32],pos%32);
}

void printNFA(const NFA &N){
    ofstream out("output.txt",ios_base::app);
    out<<"\tNumber of states: "<<N.n<<endl;
    out<<"\tInput alphabet: {";
    for(int i=0; i<N.m; i++){
        i>0 ? out<<","<<i : out<<i;
    } out<<"}"<<endl;
    int cnt=0;
    out<<"\tStart states: {";
    for(int i=0; i<N.n; i++){
        if(isSet(N.S,i))
            cnt++>0 ? out<<","<<i : out<<i;
    } out<<"}"<<endl;
    cnt=0;
    out<<"\tFinal states: {";
    for(int i=0; i<N.n; i++){
        if(isSet(N.F,i))
            cnt++>0 ? out<<","<<i : out<<i;
    } out<<"}"<<endl;
    out<<"\tTransition function:"<<endl;
    for(int i=0; i<N.n; i++){
        for(int j=0; j<N.m; j++){
            cnt=0;
            out<<"\t\tDelta("<<i<<","<<j<<") = {";
            for(int k=0; k<N.n; k++){
                if(isSet(N.delta[i][j],k))
                    cnt++>0 ? out<<","<<k : out<<k;
            } out<<"}"<<endl;
        }
    }
    out.close();
}

void printDFA(const DFA &D){
    ofstream out("output.txt",ios_base::app);
    out<<"\tNumber of states: "<<D.n<<endl;
    out<<"\tInput alphabet: {";
    for(int i=0; i<D.m; i++){
        i>0 ? out<<","<<i : out<<i;
    } out<<"}"<<endl;
    out<<"\tStart state: "<<D.s<<endl;
    int cnt=0;
    out<<"\t"<<D.cntF; D.cntF==1 ? out<<" final state: " : out<<" final states: ";
    if(D.cntF<100){
        out<<"{";
        for(int i=0; i<D.n; i++){
            if(isSet(D.F,i))
                cnt++>0 ? out<<","<<i : out<<i;
        } out<<"}"<<endl;
    }
    else
        out<<"Skipped"<<endl;
    out<<"\tTransition function:";
    if(D.n<100){
        out<<endl<<"\ta\\p|";
        for(int i=0; i<D.n; i++)
            out<<setw(3)<<i;
        out<<endl<<"\t---+";
        for(int i=0; i<D.n; i++)
            out<<"---";
        for(int i=0; i<D.m; i++){
            out<<endl<<"\t"<<setw(2)<<i<<" |";
            for(int j=0; j<D.n; j++)
                out<<setw(3)<<D.delta[j][i];
        }
        out<<endl;
    }
    else
        out<<" Skipped"<<endl;
    out.close();
}

void readNFA(NFA &N, const char *filename){
    ifstream in(filename);
    int pos;

    in>>N.n>>N.m;

    in>>pos;
    while(pos!=-1){
        setBit(N.S, pos);
        in>>pos;
    }

    in>>pos;
    while(pos!=-1){
        setBit(N.F, pos);
        in>>pos;
    }

    N.delta = new uint32_t *[N.n];
    for(int i=0; i<N.n; i++){
        N.delta[i] = new uint32_t[N.m];
        for(int j=0; j<N.m; j++)
            N.delta[i][j] = 0;
    }

    int p, a;
    in>>p;
    while(p!=-1){
        in>>a>>pos;
        setBit(N.delta[p][a], pos);
        in>>p;
    }

    in.close();
    ofstream out("output.txt");
    out<<"+++ Input NFA"<<endl;
    out.close();
    printNFA(N);
}

void subsetcons(DFA &D, const NFA &N){
    D.n = (1U << N.n);
    D.m = N.m;
    D.s = N.S;
    D.init();

    for(int i=0; i<D.n; i++){
        for(int j=0; j<32; j++){
            if(isSet(i,j) && isSet(N.F,j)){
                setBit(D.F,i);
                D.cntF++;
                break;
            }
        }
    }

    for(int i=0; i<D.n; i++){
        for(int j=0; j<D.m; j++){
            for(int k=0; k<32; k++)
                if(isSet(i,k))
                    D.delta[i][j] |= N.delta[k][j];
        }
    }

    ofstream out("output.txt",ios_base::app);
    out<<endl<<"+++ Converted DFA"<<endl;
    out.close();
    printDFA(D);
}

void dfs(uint32_t state, uint32_t *R, const DFA &D){
    setBit(R,state);
    for(int i=0; i<D.m; i++)
        if(!isSet(R,D.delta[state][i]))
            dfs(D.delta[state][i],R,D);
}

void findreachable(uint32_t *&R, const DFA &D){
    R = new uint32_t[(D.n+31)/32];
    for(int i=0; i<(D.n+31)/32; i++)
        R[i] = 0;
    dfs(D.s,R,D);
}

void rmunreachable(DFA &D_, const DFA &D, const uint32_t *R){
    uint32_t *remap = new uint32_t[D.n];
    for(int i=0; i<D.n; i++){
        remap[i]=0;
        if(isSet(R,i))
            remap[i]=D_.n++;
    }
    D_.m=D.m;
    D_.s=remap[D.s];
    D_.init();

    for(int i=0; i<D.n; i++){
        if(isSet(R,i)){
            if(isSet(D.F,i)){
                setBit(D_.F,remap[i]);
                D_.cntF++;
            }
            for(int j=0; j<D.m; j++){
                D_.delta[remap[i]][j]=remap[D.delta[i][j]];
            }
        }
    }

    ofstream out("output.txt",ios_base::app);
    out<<endl<<"+++ Reduced DFA after removing unreachable states"<<endl;
    out.close();
    printDFA(D_);

    delete[] remap;
}

void findequiv(uint32_t **&M, const DFA &D){
    M = new uint32_t*[D.n];
    for(int i=0; i<D.n; i++){
        M[i] = new uint32_t[D.n];
        for(int j=0; j<D.n; j++)
            M[i][j] = 0;
    }

    for(int i=0; i<D.n; i++){
        for(int j=i+1; j<D.n; j++)
            if((isSet(D.F,i) && !isSet(D.F,j)) || (!isSet(D.F,i) && isSet(D.F,j)))
                M[i][j] = 1;
    }

    bool done=false;
    while(!done){
        done=true;
        for(int i=0; i<D.n; i++){
            for(int j=i+1; j<D.n; j++)
                if(!M[i][j]){
                    for(int k=0; k<D.m; k++)
                        if(M[D.delta[i][k]][D.delta[j][k]] || M[D.delta[j][k]][D.delta[i][k]]){
                            M[i][j] = 1;
                            done=false;
                            break;
                        }
                }
        }
    }
}

void collapse(DFA &D_, const DFA &D, const uint32_t *const *M){
    uint32_t *remap = new uint32_t[D.n];
    for(int i=0; i<D.n; i++)
        remap[i]=i;

    ofstream out("output.txt",ios_base::app);
    out<<endl<<"+++ Equivalent states"<<endl;
    for(int i=0; i<D.n; i++){
        if(remap[i]==i){
            remap[i]=D_.n;
            out<<"\tGroup "<<setw(2)<<D_.n<<": {"<<i;
            for(int j=i+1; j<D.n; j++)
                if(!M[i][j]){
                    remap[j]=D_.n;
                    out<<","<<j;
                }
            out<<"}"<<endl;
            D_.n++;
        }
    }
    D_.m=D.m;
    D_.s=remap[D.s];
    D_.init();

    for(int i=0, curr=0; i<D.n; i++){
        if(isSet(D.F,i) && !isSet(D_.F,remap[i])){
            setBit(D_.F,remap[i]);
            D_.cntF++;
        }
        if(remap[i]==curr){
            for(int j=0; j<D_.m; j++)
                D_.delta[curr][j]=remap[D.delta[i][j]];
            curr++;
        }
    }

    out<<endl<<"+++ Reduced DFA after collapsing equivalent states"<<endl;
    out.close();
    printDFA(D_);

    delete[] remap;
}

int main(){
    char filename[100];
    cout<<"Enter filename: "; cin>>filename;

    NFA N;
    DFA D, D_, D__;
    uint32_t *reachable;
    uint32_t **minimization;

    readNFA(N,filename);
    subsetcons(D,N);
    findreachable(reachable,D);

    ofstream out("output.txt",ios_base::app);
    out<<endl<<"+++ Reachable states: ";
    int cnt=0;
    out<<"{";
    for(int i=0; i<D.n; i++){
        if(isSet(reachable,i))
            cnt++>0 ? out<<","<<i : out<<i;
    } out<<"}"<<endl;
    out.close();

    rmunreachable(D_,D,reachable);
    findequiv(minimization,D_);
    collapse(D__,D_,minimization);

    cout<<"Ouput written to output.txt"<<endl;
    return 0;
}