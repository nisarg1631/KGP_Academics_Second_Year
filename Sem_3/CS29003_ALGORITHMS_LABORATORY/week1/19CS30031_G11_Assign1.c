/*
Name: Nisarg Upadhyaya
Roll Number: 19CS30031
Department: Computer Science and Engineering
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE{
	int data;
	struct _NODE *add;
}node;

void traverse_from_front_to_end(node *head){
	node *prev=NULL, *it=head;
	while(it!=NULL){
		printf("%d ",it->data);
		node *temp=it;
		it=((unsigned long long)(it->add))^((unsigned long long)prev);
		prev=temp;
	}
	printf("\n");
}

void traverse_from_end_to_front(node *tail){
	node *prev=NULL, *it=tail;
	while(it!=NULL){
		printf("%d ",it->data);
		node *temp=it;
		it=((unsigned long long)(it->add))^((unsigned long long)prev);
		prev=temp;
	}
	printf("\n");
}

void add_node(node **head, node **tail, int val){
	node *new=(node *)malloc(sizeof(node));
	new->data=val;
	if(*head==NULL){
		// this is the insertion of first element, both prev and next are NULL
		new->add=((unsigned long long)NULL)^((unsigned long long)NULL);
		*head=*tail=new;
	}
	else{
		// insertion of subsequent elements, by changing add of last element and updating tail with newly added element
		node *temp=(*tail)->add;
		temp=((unsigned long long)temp)^((unsigned long long)NULL);
		temp=((unsigned long long)temp)^((unsigned long long)new);
		(*tail)->add=temp;
		new->add=((unsigned long long)(*tail))^((unsigned long long)NULL);
		(*tail)=new;
	}
}

void reverse(node **head, node **tail){
	// swapping head and tail does the job
	node *temp=*tail;
	*tail=*head;
	*head=temp;
}

void alternate(node **head, node **tail){
	node *prev=*head;
	node *it=((unsigned long long)(prev->add))^((unsigned long long)NULL);
	if(it==NULL) return;
	while((((unsigned long long)(it->add))^((unsigned long long)prev))!=NULL){
		// storing original positions in temporary variables to assign new positions at the end
		node *new_it=((unsigned long long)((*tail)->add))^((unsigned long long)NULL);
		node *new_prev=*tail;
		node *new_tail=it;
		node *temp;
		// changing add of prev
		temp=prev->add;
		temp=((unsigned long long)temp)^((unsigned long long)it);
		temp=((unsigned long long)temp)^((unsigned long long)new_prev);
		prev->add=temp;
		// changing add of it
		temp=it->add;
		temp=((unsigned long long)temp)^((unsigned long long)prev);
		temp=((unsigned long long)temp)^((unsigned long long)NULL);
		it->add=temp;
		// changing add of tail
		temp=(*tail)->add;
		temp=((unsigned long long)temp)^((unsigned long long)NULL);
		temp=((unsigned long long)temp)^((unsigned long long)prev);
		(*tail)->add=temp;
		// assigning new positions
		it=new_it;
		prev=new_prev;
		(*tail)=new_tail;
	}
}

int main(){
	// initialising doubly linked list with head and tail set to NULL
	node *head=NULL, *tail=NULL;
	int n;
	printf("Enter value of n: ");
	scanf("%d",&n);
	printf("Enter %d integers between -100 to 100: ",n);
	for(int i=0; i<n; i++){
		int data;
		scanf("%d",&data);
		add_node(&head,&tail,data);
	}
	// traversing linked list in both directions (part 1)
	printf("List traversed from front to end: ");
	traverse_from_front_to_end(head);
	printf("List traversed from end to front: ");
	traverse_from_end_to_front(tail);
	// reversing the linked list (part 2)
	reverse(&head,&tail);
	printf("Reversed list traversed from front to end: ");
	traverse_from_front_to_end(head);
	// alternating the linked list (part 3)
	alternate(&head,&tail);
	printf("Alternated list traversed from front to end: ");
	traverse_from_front_to_end(head);
	return 0;
}