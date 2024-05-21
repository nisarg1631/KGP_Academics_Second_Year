#include <iostream>
using namespace std;

class mxsize{
    
    private:

        int** create_matrix(){
            int **arr=new int*[rows];
            for(int i=0; i<rows; i++) arr[i]=new int[cols];
            return arr;
        }

        void destroy_matrix(int **arr){
            for(int i=0; i<rows; i++) delete[] arr[i];
            delete[] arr;
        }

        void max_size_square(){
            int **dp=create_matrix();

            for(int i=0; i<rows; i++) dp[i][0]=mat[i][0];
            for(int i=0; i<cols; i++) dp[0][i]=mat[0][i];

            for(int i=1; i<rows; i++){
                for(int j=1; j<cols; j++){
                    if(mat[i][j]) dp[i][j]=min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1]))+1;
                    else dp[i][j]=0;
                }
            }

            sqlen=0;
            for(int i=0; i<rows; i++){
                for(int j=0; j<cols; j++){
                    if(dp[i][j]>sqlen){
                        sqlen=dp[i][j];
                        sqbottom=i;
                        sqright=j;
                    }
                }
            }
            
            destroy_matrix(dp);
        }

        void max_size_rectangle(){
            int **dp_height, **dp_left, **dp_right;
            dp_height=create_matrix();
            dp_left=create_matrix();
            dp_right=create_matrix();

            int prev;
            //set height dp values for first row
            for(int j=0; j<cols; j++){
                dp_height[0][j]=mat[0][j];
            }
            //set left dp values for first row
            prev=-1;
            for(int j=0; j<cols; j++){
                if(!mat[0][j]){
                    prev=j;
                }
                dp_left[0][j]=j-prev;
            }
            //set right dp values for first row
            prev=cols;
            for(int j=cols-1; j>=0; j--){
                if(!mat[0][j]){
                    prev=j;
                }
                dp_right[0][j]=prev-j;
            }
            //set height dp values for the remaining matrix
            for(int i=1; i<rows; i++){
                for(int j=0; j<cols; j++){
                    if(!mat[i][j]){
                        dp_height[i][j]=0;
                    }
                    else{
                        dp_height[i][j]=dp_height[i-1][j]+1;
                    }
                }
            }
            //set left dp values for the remaining matrix
            for(int i=1; i<rows; i++){
                prev=-1;
                for(int j=0; j<cols; j++){
                    if(!mat[i][j]){
                        prev=j;
                        dp_left[i][j]=0;
                    }
                    else{
                        if(!mat[i-1][j]) dp_left[i][j]=j-prev;
                        else dp_left[i][j]=min(dp_left[i-1][j], j-prev);
                    }
                }
            }
            //set right dp values for the remaining matrix
            for(int i=1; i<rows; i++){
                prev=cols;
                for(int j=cols-1; j>=0; j--){
                    if(!mat[i][j]){
                        prev=j;
                        dp_right[i][j]=0;
                    }
                    else{
                        if(!mat[i-1][j]) dp_right[i][j]=prev-j;
                        else dp_right[i][j]=min(dp_right[i-1][j], prev-j);
                    }
                }
            }

            //calculate best area
            for(int i=0; i<rows; i++){
                for(int j=0; j<cols; j++){
                    int curr=dp_height[i][j]*(dp_left[i][j]+dp_right[i][j]-1);
                    if(curr>rec_area){
                        rec_area=curr;
                        rec_top=i-dp_height[i][j]+1;
                        rec_bottom=i;
                        rec_left=j-dp_left[i][j]+1;
                        rec_right=j+dp_right[i][j]-1;
                    }
                }
            }

            destroy_matrix(dp_height);
            destroy_matrix(dp_left);
            destroy_matrix(dp_right);
        }

    public:
        int **mat, rows, cols;
        int sqlen, sqbottom, sqright;
        int rec_area, rec_top, rec_bottom, rec_left, rec_right;
        mxsize(){
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
            sqlen=sqbottom=sqright=0;
            max_size_square();
            cout<<"Square: "<<sqlen<<" "<<sqbottom<<" "<<sqright<<'\n';
            rec_area=rec_top=rec_bottom=rec_left=rec_right=0;
            max_size_rectangle();
            cout<<"Rectangle: "<<rec_area<<" "<<"from ("<<rec_top<<", "<<rec_left<<") to ("<<rec_bottom<<", "<<rec_right<<").\n";
        }
        ~mxsize(){
            for(int i=0; i<rows; i++) delete[] mat[i];
            delete[] mat;
        }

};

int main(){
    mxsize();
    return 0;
}