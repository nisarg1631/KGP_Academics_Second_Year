#include <iostream>
#include <fstream>
using namespace std;

/* Approach (time complexity n*c*c*c)

-> dp[i][j][k] represents maximum probability upto reaction i when j units of catalyst are used for reaction i and total units used till that point are k
-> dp[i][j][k] = maximum of (dp[i-1][x][k-j]*e[i][j]) over all x from 0 to k-j
-> Base cases
    a. If 0 units of catalyst are used then probability is 0 ,i.e., dp[i][0][k]=0 for all i,k
    b. For reaction one, units used at that point=total units used ,i.e., dp[1][j][j]=e[1][j] for all j from 1 to C
*/
int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n,c;
    in>>n>>c;

    double cat[n+1][c+1];
    for(int i=1; i<=n; i++){
        for(int j=1; j<=c; j++){
            in>>cat[i][j];
        }
    }

    double dp[n+1][c+1][c+1];

    for(int i=0; i<=n; i++){
        for(int j=0; j<=c; j++){
            for(int k=0; k<=c; k++){
                dp[i][j][k]=0;
            }
        }
    }

    //if 0 units of catalyst used in any reaction then probaility is 0
    for(int i=1; i<=n; i++){
        for(int k=0; k<=c; k++){
            dp[i][0][k]=0;
        }
    }
    //for first reaction units used is equal to total units till that point
    for(int i=1; i<=c; i++){
        dp[1][i][i]=cat[1][i];
    }
    //fill rest of the table
    for(int i=2; i<=n; i++){
        for(int j=1; j<=c; j++){
            for(int k=j; k<=c; k++){
                dp[i][j][k]=-1;
                for(int l=0; l<=(k-j); l++){
                    dp[i][j][k]=max(dp[i][j][k], dp[i-1][l][k-j]*cat[i][j]);
                }
            }
        }
    }

    double best=-1;
    for(int j=1; j<=c; j++){
        best=max(best, dp[n][j][c]);
    }
    out<<best<<endl;

    //retrieval
    int limit=c, curr, cnt[n+1];
    for(int i=n; i>=1; i--){
        best=-1;
        curr=0;
        for(int j=1; j<=limit; j++){
            if(dp[i][j][limit]>best){
                best=dp[i][j][limit];
                curr=j;
            }
        }
        cnt[i]=curr;
        limit-=curr;
    }
    for(int i=1; i<=n; i++) out<<"reaction "<<i<<" : "<<cnt[i]<<endl;
    return 0;
}