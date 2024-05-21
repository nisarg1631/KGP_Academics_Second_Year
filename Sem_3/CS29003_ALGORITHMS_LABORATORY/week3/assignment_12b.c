/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
Machine Number: 54
*/

/*Assignment 12(b) - Stacks implementation using linked list*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _LIFO{
	int data;
	struct _LIFO *next;
}stack;

void top(stack *top){
	if(top==NULL)
		printf("No data.\n");
	else
		printf("Top element: %d\n",top->data);
}

void push(stack **top, int input){
	stack *new=(stack *)malloc(sizeof(stack));
	if(new==NULL){
		printf("Stack overflow.\n");
	}
	else{
		new->data=input;
		new->next=*top;
		*top=new;
		printf("Element pushed.\n");
	}
}

void pop(stack **top){
	if(*top==NULL)
		printf("Stack underflow.\n");
	else{
		stack *temp;
		int value;
		temp=(*top);
		value=(*top)->data;
		*top=(*top)->next;
		free(temp);
		printf("%d removed from stack.\n",value);
	}	
}

int main(){
	stack *stack_top=NULL;
	int opt;

	while(1){
		printf("Choose operation from given list:\n");
		printf("1> Push element to stack\n");
		printf("2> Pop element from stack\n");
		printf("3> Show top element of stack\n");
		printf("4> Exit\n");

		scanf("%d",&opt);

		if(opt==1){
			int temp;
			printf("Enter element to push: ");
			scanf("%d",&temp);
			push(&stack_top,temp);
		}

		else if(opt==2){
			pop(&stack_top);
		}

		else if(opt==3){
			top(stack_top);
		}

		else if(opt==4){
			printf("Bye\n");
			break;
		}

		else
			printf("Enter a valid option.\n");
	}
	return 0;
}