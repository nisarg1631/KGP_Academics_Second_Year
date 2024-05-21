/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Assignment 12(a)*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE{
	int data;
	struct _NODE *next;
}node;

void display(node *head){
	node *it=head;
	printf("----Elements in list----\n");
	while(it!=NULL){
		printf("%d ",it->data);
		it=it->next;
	}
	printf("\n");
}

int search(node *head, int input){
	node *it=head;
	while(it!=NULL){
		if(it->data==input)
			return 1;
		else
			it=it->next;
	}
	return 0;
}

node *insert_beg(node *head, int input){
	node *new=(node *)malloc(sizeof(node));
	new->data=input;
	new->next=head;
	printf("Element added.\n");
	return new;
}

node *insert_end(node *head, int input){
	node *new=(node *)malloc(sizeof(node));
	new->data=input;
	new->next=NULL;

	if(head==NULL){
		printf("Element added.\n");
		return new;
	}

	node *it=head;
	while(it->next!=NULL)
		it=it->next;
	it->next=new;
	
	printf("Element added.\n");
	return head;
}

node *insert_pos(node *head, int input, int pos){
	if(pos==0)
		return insert_beg(head,input);
	
	node *new=(node *)malloc(sizeof(node));
	new->data=input;

	node *it=head;
	int count=0;
	while(it!=NULL){
		count++;
		if(count==pos){
			node *temp;
			new->next=it->next;
			it->next=new;
			printf("Element added.\n");
			return head;
		}
		else
			it=it->next;
	}

	printf("%d nodes do not exist in the list. The list has only %d nodes.\n",pos,count);
	return head;
}

node *delete(node *head, int input){
	node *it,*prev;
	it=prev=head;

	while(it!=NULL){
		if(it->data==input){
			if(it==head)
				head=it->next;
			else
				prev->next=it->next;
			
			it->next=NULL;
			free(it);
			printf("The first occurence of %d found was removed.\n",input);
			return head;
		}
		else{
			prev=it;
			it=it->next;
		}
	}

	printf("Element %d does not exist.\n",input);
	return head;
}

int main(){
	node *head=NULL;
	int opt;

	while(1){
		printf("Choose operation from given list:\n");
		printf("1> Insert an element x at the beginning of the list\n");
		printf("2> Insert an element x at the end of the list\n");
		printf("3> Insert an element x after i nodes in the list\n");
		printf("4> Search for an element x\n");
		printf("5> Delete a specific element x\n");
		printf("6> Display the list\n");
		printf("7> Exit\n");

		scanf("%d",&opt);

		if(opt==1){
			int temp;
			printf("Enter element (x) to add: ");
			scanf("%d",&temp);
			head=insert_beg(head,temp);
		}

		else if(opt==2){
			int temp;
			printf("Enter element (x) to add: ");
			scanf("%d",&temp);
			head=insert_end(head,temp);
		}

		else if(opt==3){
			int temp1, temp2;
			printf("Enter element (x) to add: ");
			scanf("%d",&temp1);
			printf("Enter position (i): ");
			scanf("%d",&temp2);
			head=insert_pos(head,temp1,temp2);
		}

		else if(opt==4){
			int temp;
			printf("Enter element (x) to search: ");
			scanf("%d",&temp);
			if(search(head,temp))
				printf("Element found in list.\n");
			else
				printf("Element not found in list.\n");
		}

		else if(opt==5){
			int temp;
			printf("Enter element (x) to delete: ");
			scanf("%d",&temp);
			head=delete(head,temp);
		}

		else if(opt==6){
			display(head);
		}

		else if(opt==7){
			printf("Bye\n");
			break;
		}

		else
			printf("Enter a valid option.\n");
	}
	return 0;
}
