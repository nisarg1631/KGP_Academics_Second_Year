#include <iostream>
#include <limits.h>
using namespace std;

class mxsum{

    private:
        void linear_max_dp(int *arr, int &st, int &en, int &best){
            best=-1;
            int curr=0, start=0;
            for(int i=0; i<rows; i++){
                curr+=arr[i];
                if(curr<0){
                    curr=0;
                    start=i+1;
                }
                if(curr>best){
                    best=curr;
                    st=start;
                    en=i;
                }
            }
            //in case all numbers are negative we select the best of them
            if(best==-1){
                best=arr[0];
                st=en=0;
                for(int i=1; i<rows; i++){
                    if(arr[i]>best){
                        best=arr[i];
                        st=en=i;
                    }
                }
            }
        }

        void rectangle_max(){
            int *arr=new int[10];
            for(int l=0; l<cols; l++){
                for(int i=0; i<rows; i++)
                    arr[i]=0;
                for(int r=l; r<cols; r++){
                    for(int i=0; i<rows; i++)
                        arr[i]+=mat[i][r];
                    int sum, start, end;
                    linear_max_dp(arr, start, end, sum);
                    if(sum>max_sum){
                        max_sum=sum;
                        left=l;
                        right=r;
                        top=start;
                        bottom=end;
                    }
                }
            }
            delete[] arr;
        }

    public:
        int **mat, rows, cols;
        int max_sum, left, right, top, bottom;
        mxsum(){
            cout<<"Enter number of rows: ";
            cin>>rows;
            cout<<"Enter number of columns: ";
            cin>>cols;
            mat=new int*[rows];
            for(int i=0; i<rows; i++) mat[i]=new int[cols];
            cout<<"Enter m*n matrix: ";
            for(int i=0; i<rows; i++)
                for(int j=0; j<cols; j++)
                    cin>>mat[i][j];
            max_sum=INT_MIN;
            left=right=top=bottom=0;
            rectangle_max();
            cout<<"MAX SUM IS: "<<max_sum<<'\n';
            cout<<"From ("<<top<<", "<<left<<") to ("<<bottom<<", "<<right<<").\n";
        }
        ~mxsum(){
            for(int i=0; i<rows; i++) delete[] mat[i];
            delete[] mat;
        }

};

int main(){
    mxsum();
    return 0;
}