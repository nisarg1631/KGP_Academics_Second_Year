#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE{
	int x,y;
	struct _NODE *next;
}node;

void display(node *head){
	node *it=head;
	printf("List contains: ");
	if(head==NULL)
		printf("Empty");
	while(it!=NULL){
		if(it->next==NULL)
			printf("(%d,%d)",it->x,it->y);
		else
			printf("(%d,%d)->",it->x,it->y);
		it=it->next;
	}
	printf("\n");
}

void insert_pos(node **head, int input_x, int input_y, int pos){
	if(pos==0){
		node *new=(node *)malloc(sizeof(node));
		new->x=input_x;
		new->y=input_y;
		new->next=*head;
		*head=new;
	}
	else{
		node *new=(node *)malloc(sizeof(node));
		new->x=input_x;
		new->y=input_y;

		node *it=*head;
		int count=0;
		while(it!=NULL){
			count++;
			if(count==pos){
				node *temp;
				new->next=it->next;
				it->next=new;
			}
			else
				it=it->next;
		}
	}
}

void insert(node **head, int input_x, int input_y){
	if(*head==NULL){
		node *new=(node *)malloc(sizeof(node));
		new->x=input_x;
		new->y=input_y;
		new->next=*head;
		*head=new;
		return;
	}
	node *it=*head;
	int count=0;
	while(it!=NULL){
		count++;
		if(input_x<it->x){
			insert_pos(head,input_x,input_y,count-1);
			return;
		}
		else if(input_x==it->x){
			if(input_y<it->y){
				insert_pos(head,input_x,input_y,count-1);
				return;
			}
			else if(input_y==it->y){
				printf("Coordinates already exist.\n");
				return;
			}
			else
				it=it->next;
		}
		else
			it=it->next;
	}
	insert_pos(head,input_x,input_y,count);
}

int main(){
	node *head=NULL;
	int x,y;

	printf("Enter integer coordinates to add to list. Enter 0,0 to terminate input.\n");
	printf("Enter x and y (space separated): ");
	scanf("%d %d",&x,&y);
	while(x!=0||y!=0){
		insert(&head,x,y);
		display(head);
		scanf("%d %d",&x,&y);
	}
	printf("Input terminated.\n");
	return 0;
}