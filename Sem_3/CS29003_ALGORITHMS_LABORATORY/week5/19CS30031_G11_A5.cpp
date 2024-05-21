#include <iostream>
#include <fstream>
using namespace std;

/* Approach (time complexity O(n*c*c), space complexity O(n*c))

-> dp[i][j] represents maximum probability upto reaction i with total j units catalyst used
-> dp[i][j] = maximum of (dp[i-1][j-k]*e[i][k]) over all k from 1 to j
-> Base cases
    a. If 0 units of catalyst are used then probability is 0, i.e., dp[i][0]=0 for all i from 1 to n
    b. For reaction one, maximum probability = given probability ,i.e., dp[1][j]=e[1][j] for all j from 1 to C
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

    double dp[n+1][c+1];

    //if 0 units of catalyst used in any reaction then probaility is 0
    for(int i=1; i<=n; i++){
        dp[i][0]=0;
    }
    //for first reaction max probability = given probability
    for(int i=1; i<=c; i++){
        dp[1][i]=cat[1][i];
    }
    //fill rest of the table
    for(int i=2; i<=n; i++){
        for(int j=1; j<=c; j++){
            dp[i][j]=-1;
            for(int k=1; k<=j; k++){
               dp[i][j]=max(dp[i][j], dp[i-1][j-k]*cat[i][k]);
            }
        }
    }

    out<<dp[n][c]<<endl;

    //retrieval, initial limit is C, check for how many units of C used in reaction i we are getting the optimal value dp[i][limit], store this, and reduce limit by that value and repeat the same for previous row
    int limit=c, cnt[n+1];
    for(int i=n; i>=2; i--){
        for(int j=1; j<=limit; j++){
            if((dp[i-1][limit-j]*cat[i][j])==dp[i][limit]){
                cnt[i]=j;
                limit-=j;
                break;
            }
        }
    }
    cnt[1]=limit;
    for(int i=1; i<=n; i++) out<<"reaction "<<i<<" : "<<cnt[i]<<endl;

    in.close();
    out.close();
    return 0;
}

//P.S. I first submitted solution based on old approach below, but then I found even more efficient approach which I ultimately used

/* Approach 1 (old) (time complexity n*c*c*c, space complexity n*c*c)

-> dp[i][j][k] represents maximum probability upto reaction i when j units of catalyst are used for reaction i and total units used till that point are k
-> dp[i][j][k] = maximum of (dp[i-1][x][k-j]*e[i][j]) over all x from 1 to k-j
-> Base cases
    a. If 0 units of catalyst are used then probability is 0 ,i.e., dp[i][0][k]=0 for all i,k
    b. For reaction one, units used at that point=total units used ,i.e., dp[1][j][j]=e[1][j] for all j from 1 to C
*/
