/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Assignment 12(c) - Queues implementation using linked list*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _FIFO{
	int data;
	struct _FIFO *next;
}queue;

void display_front(queue *ptr){
	if(ptr==NULL)
		printf("No data.\n");
	else
		printf("Front element: %d\n",ptr->data);
}

void display_rear(queue *ptr){
	if(ptr==NULL)
		printf("No data.\n");
	else
		printf("Rear element: %d\n",ptr->data);
}

void enqueue(queue **front, queue **rear, int input){
	queue *new=(queue *)malloc(sizeof(queue));
	if(new==NULL){
		printf("Queue overflow.\n");
	}
	else{
		new->data=input;
		new->next=NULL;
		if(*front==NULL)
			*front=*rear=new;
		else{
			(*rear)->next=new;
			*rear=new;
		}
		printf("Element enqueued.\n");
	}
}

void dequeue(queue **front, queue **rear){
	if(*front==NULL)
		printf("Queue underflow.\n");
	else{
		queue *temp;
		int value;
		temp=(*front);
		value=(*front)->data;
		if(*front==*rear)
			*rear=NULL;
		*front=(*front)->next;
		free(temp);
		printf("%d removed from queue.\n",value);
	}	
}

int main(){
	queue *front,*rear;
	front=rear=NULL;
	int opt;

	while(1){
		printf("Choose operation from given list:\n");
		printf("1> Add element to queue\n");
		printf("2> Remove element from queue\n");
		printf("3> Show front element of queue\n");
		printf("4> Show rear element of queue\n");
		printf("5> Exit\n");

		scanf("%d",&opt);

		if(opt==1){
			int temp;
			printf("Enter element to enqueue: ");
			scanf("%d",&temp);
			enqueue(&front,&rear,temp);
		}

		else if(opt==2){
			dequeue(&front,&rear);
		}

		else if(opt==3){
			display_front(front);
		}

		else if(opt==4){
			display_rear(rear);
		}

		else if(opt==5){
			printf("Bye\n");
			break;
		}

		else
			printf("Enter a valid option.\n");
	}
	return 0;
}