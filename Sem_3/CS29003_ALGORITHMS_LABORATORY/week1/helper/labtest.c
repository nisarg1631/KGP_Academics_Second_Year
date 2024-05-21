#include <stdio.h>
#include <stdlib.h>

typedef struct _CHAR{
	char data;
	struct _CHAR *next;
}character;

typedef struct _LINE_LIST{
	character **start;
	int size;
	struct _LINE_LIST *next;
}linelist;

typedef struct _TEXT_BUFFER{
	linelist **head;
	int size;
}text;

//inserts character before char_num th position, to add at end pass 0
int insertChar(text *document, int line_num, int char_num, char input){
	if((document->size)<line_num||line_num<1){
		return 0;
	}
	else{
		linelist *line_it=*(document->head);
		int count=0;
		while(line_it!=NULL){
			count++;
			if(count==line_num)
				break;
			else
				line_it=line_it->next;
		}
		if(char_num<0||char_num>(line_it->size)){
			return 0;
		}
		else{
			character *new=(character *)malloc(sizeof(character));
			new->data=input;
			char_num--;
			if(char_num==0){
				new->next=*(line_it->start);
				*(line_it->start)=new;
			}
			else if(char_num==-1){
				if(*(line_it->start)==NULL){
					new->next=*(line_it->start);
					*(line_it->start)=new;
				}
				else{
					character *char_it=*(line_it->start);
					while(char_it->next!=NULL)
						char_it=char_it->next;
					char_it->next=new;
					new->next=NULL;
				}
			}
			else{
				int count=0;
				character *char_it=*(line_it->start);
				while(char_it!=NULL){
					count++;
					if(count==char_num){
						new->next=char_it->next;
						char_it->next=new;
					}
					else
						char_it=char_it->next;
				}
			}
			(line_it->size)++;
			return 1;
		}
	}
}

int insertLine(text *document, int line_num, char input[]){
	if((document->size)<line_num||line_num<0){
		return 0;
	}
	else{
		linelist *new=(linelist *)malloc(sizeof(linelist));
		new->start=(character **)malloc(sizeof(character *));
		*(new->start)=NULL;
		new->size=0;
		if(line_num==0){
			new->next=*(document->head);
			*(document->head)=new;
		}
		else{
			linelist *it=*(document->head);
			int count=0;
			while(it!=NULL){
				count++;
				if(count==line_num){
					new->next=it->next;
					it->next=new;
				}
				else
					it=it->next;
			}
		}
		(document->size)++;
		for(int i=0;input[i]!='\0';i++){
			insertChar(document,line_num+1,0,input[i]);
		}
		return 1;
	}
}

int readFile(text *document, char filename[]){
	FILE *fptr=fopen(filename,"r");
	if(fptr==NULL){
		printf("Error in loading input file.\n");
		return 0;
	}
	else
		printf("Input file successfully loaded.\n");
	
	
	char str[1000];

	document->head=(linelist **)malloc(sizeof(linelist *));
	*(document->head)=NULL;
	
	while(!(feof(fptr))){
		fscanf(fptr,"%[^\n]",str);
		fgetc(fptr);
		insertLine(document,document->size,str);
	}

	fclose(fptr);
	return 1;
}

int deleteChar(text *document,int line_num, int char_num){
	if((document->size)<line_num||line_num<1){
		return 0;
	}
	else{
		linelist *line_it=*(document->head);
		int count=0;
		while(line_it!=NULL){
			count++;
			if(count==line_num)
				break;
			else
				line_it=line_it->next;
		}
		if(char_num>(line_it->size)||char_num<1){
			return 0;
		}
		else{
			character *it,*prev;
			it=prev=*(line_it->start);
			int count=0;
			while(it!=NULL){
				count++;
				if(count==char_num){
					if(it==*(line_it->start))
						*(line_it->start)=it->next;
					else
						prev->next=it->next;
					
					free(it);
					return 1;
				}
				else{
					prev=it;
					it=it->next;
				}
			}
		}
	}
}

int deleteLine(text *document,int line_num){
	if((document->size)<line_num||line_num<1){
		return 0;
	}
	else{
		linelist *it,*prev;
		it=prev=*(document->head);
		int count=0;
		while(it!=NULL){
			count++;
			if(count==line_num){
				if(it==*(document->head))
					*(document->head)=it->next;
				else
					prev->next=it->next;
				
				free(it);
				return 1;
			}
			else{
				prev=it;
				it=it->next;
			}
		}
	}
}

int displayText(text *document){
	if(document->size==0){
		return 0;
	}
	else{
		linelist *line_it=*(document->head);
		while(line_it!=NULL){
			character *char_it=*(line_it->start);
			while(char_it!=NULL){
				printf("%c",char_it->data);
				char_it=char_it->next;
			}
			printf("\n");
			line_it=line_it->next;
		}
		return 1;
	}
}

int writeFile(text *document, char filename[]){
	if(document->size==0){
		return 0;
	}
	else{
		FILE *fptr=fopen(filename,"w");
		
		if(fptr==NULL){
			printf("Error in creating output file.\n");
			return 0;
		}
		else
			printf("Output file successfully created.\n");

		linelist *line_it=*(document->head);
		while(line_it!=NULL){
			character *char_it=*(line_it->start);
			while(char_it!=NULL){
				fprintf(fptr,"%c",char_it->data);
				char_it=char_it->next;
			}
			fprintf(fptr,"\n");
			line_it=line_it->next;
		}
		return 1;
	}
}

int main(){
	text *doc=(text *)malloc(sizeof(text));
	doc->size=0;
	int opt;

	while(1){
		printf("Choose operation from given list:\n");
		printf("1> Read file\n");
		printf("2> Display content\n");
		printf("3> Insert line\n");
		printf("4> Insert character\n");
		printf("5> Delete line\n");
		printf("6> Delete character\n");
		printf("7> Write file\n");
		printf("8> Exit\n");

		scanf("%d",&opt);
		getchar();

		if(opt==1){
			char filename[100];
			printf("Enter filename: ");
			scanf("%s",filename);
			getchar();
			readFile(doc,filename);
		}

		else if(opt==2){
			displayText(doc);
		}

		else if(opt==3){
			char line[1000];
			int temp;
			printf("Enter contents of line: ");
			scanf("%[^\n]",line);
			getchar();
			printf("Enter line number after which to add: ");
			scanf("%d",&temp);
			getchar();
			int value=insertLine(doc,temp,line);
			if(value==0)
				printf("Invalid Request.\n");
			else	
				printf("Line added.\n");
		}

		else if(opt==4){
			char line;
			int temp1,temp2;
			printf("Enter character: ");
			scanf("%c",line);
			getchar();
			printf("Enter line number after which to add: ");
			scanf("%d",&temp1);
			getchar();
			printf("Enter character number before which to add: ");
			scanf("%d",&temp2);
			getchar();
			int value=insertChar(doc,temp1,temp2,line);
			if(value==0)
				printf("Invalid Request.\n");
			else	
				printf("Character added.\n");
		}

		else if(opt==5){
			int temp1;
			printf("Enter line number: ");
			scanf("%d",&temp1);
			getchar();
			int value=deleteLine(doc,temp1);
			if(value==0)
				printf("Invalid Request.\n");
			else	
				printf("Line removed.\n");
		}

		else if(opt==6){
			int temp1,temp2;
			printf("Enter line number: ");
			scanf("%d",&temp1);
			getchar();
			printf("Enter character number: ");
			scanf("%d",&temp2);
			getchar();
			int value=deleteChar(doc,temp1,temp2);
			if(value==0)
				printf("Invalid Request.\n");
			else	
				printf("Character removed.\n");
		}

		else if(opt==7){
			char filename[100];
			printf("Enter filename: ");
			scanf("%s",filename);
			getchar();
			writeFile(doc,filename);
		}
		
		else if(opt==8){
			printf("Bye\n");
			break;
		}

		else
			printf("Enter a valid option.\n");
	}
	return 0;
}