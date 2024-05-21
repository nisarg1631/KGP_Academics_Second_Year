/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Group: 11
Assignment: 2
*/

#include "assign2.h"

//utility function to get max of two numbers
int max(int num1, int num2){
	return (num1>num2 ? num1 : num2); 
}

//utility class to store point array, and with utility functions to perform the merge subroutine
class collection{
	public:
		Point* point_arr;
		int len;
		
		//constructor, allocates enough memory to store the points, and initialises length to 0
		collection(int maxlen){
			point_arr=new Point[maxlen];
			len=0;
		}

		//utility function to add point, if the heights are same then we skip it, is the coordinates are same we update max heigth, else we normally add the point to the array
		void add_point(Point data){
			if(len>0){
				Point &prev=point_arr[len-1];
				if(prev.y==data.y){
					return;
				}
				if(prev.x==data.x){
					prev.y=max(prev.y,data.y);
					return;
				}
			}
			point_arr[len++]=data;
		}
		
		//utility function to merge two arrays, similar to the mergesort subroutine, we traverse the lists simultaneously and add the point with lower x coordinate using the add_point function
		collection* merge(collection *data){
			int lenl, lenr;
			
			lenl=len;
			lenr=data->len;
			collection *ans=new collection(lenl+lenr);
			
			int h_left=0, h_right=0, itl, itr;
			for(itl=0, itr=0; itl<lenl && itr<lenr;){
				int xl=point_arr[itl].x;
				int xr=data->point_arr[itr].x;
				Point to_add;
				if(xl<xr){
					h_left=point_arr[itl].y;
					to_add.x=xl;
					to_add.y=max(h_left,h_right);
					ans->add_point(to_add);
					itl++;
				}
				else{
					h_right=data->point_arr[itr].y;
					to_add.x=xr;
					to_add.y=max(h_left,h_right);
					ans->add_point(to_add);
					itr++;
				}
			}

			while(itl<lenl){
				ans->add_point(point_arr[itl]);
				itl++;
			}
			while(itr<lenr){
				ans->add_point(data->point_arr[itr]);
				itr++;
			}

			return ans;
		}
};

//divide function, recursively calls the left and right halves followed by merge, base case: single building
collection* dnc(Box boxes[], int l, int r){
	if(l==r){
		collection *ans=new collection(2);
		ans->point_arr[0].x=boxes[l].left;
		ans->point_arr[0].y=boxes[l].ht;
		ans->point_arr[1].x=boxes[l].right;
		ans->point_arr[1].y=0;
		ans->len=2;
		return ans;
	}

	int mid=(l+r)/2;
	
	collection *left=dnc(boxes,l,mid);
	collection *right=dnc(boxes,mid+1,r);
	collection *ans=left->merge(right);

	delete left;
	delete right;
	return ans;
}

Point* findOutLine(Box boxes[], int size, int &outputsize){
	Point* point_array;
	collection *ans=dnc(boxes, 0, size-1);
	outputsize=ans->len;
	point_array=ans->point_arr;
	point_array[outputsize-1].y=0;
	return point_array;
}

int main(){
	process();
	return 0;
}