#include <iostream>
#include <limits.h>
using namespace std;

class dp{
    
    private:

        int** create_matrix(){
            int **arr=new int*[caps+1];
            for(int i=0; i<caps+1; i++) arr[i]=new int[tubes+1];
            return arr;
        }

        void destroy_matrix(int **arr){
            for(int i=0; i<caps+1; i++) delete[] arr[i];
            delete[] arr;
        }

        void run_dp(){
            //checking for 0 caps doesnt make sense, set values to 0
            for(int i=0; i<=tubes; i++) mat[0][i]=0;
            //for a single caps, in worst case number of tests is same as number of tubes
            for(int i=0; i<=tubes; i++) mat[1][i]=i;
            //for 0 tubes no test is conducted and for 1 tube a single test gives the result
            for(int i=1; i<=caps; i++){
                mat[i][0]=0;
                mat[i][1]=1;
            }
            //dynamic programming
            for(int i=2; i<=caps; i++){
                for(int j=2; j<=tubes; j++){
                    mat[i][j]=INT_MAX;
                    for(int k=1; k<=j; k++){
                        mat[i][j]=min(1+max(mat[i-1][k-1], mat[i][j-k]), mat[i][j]);
                    }
                }
            }
        }

    public:

        int **mat, caps, tubes;

        dp(){
            cin>>caps>>tubes;
            mat=create_matrix();
            run_dp();
            cout<<mat[caps][tubes]<<'\n';
        }
        ~dp(){
            destroy_matrix(mat);
        }

};

int main(){
    int tc;
    cin>>tc;
    while(tc--){
        dp();
    }
    return 0;
}