#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct bstree{			// structure of binary tree
	char word[30];
	int weight, freq;
	struct bstree *left, *right;
}BSTREE;
typedef struct trie{			// trie data structure
    int isLeaf;     
    struct trie *children[26];
} TRIE;
BSTREE *createNode(){				
	BSTREE *p=(BSTREE*)malloc(sizeof(BSTREE));
	p->left=NULL;
	p->right=NULL;
	p->freq=0;
	return p;	
}
BSTREE *insert(char str[],BSTREE *root, int weight){		//inserts words from database social file into binary tree
	BSTREE *p=createNode();
	strcpy(p->word,str);
	p->weight = weight;
	if(root==NULL) root=p;
	else{
		BSTREE *q=root,*prev;
		while(q!=NULL){
			if(strcmp(q->word,str)>=0){
				prev=q;
				q=q->right;
			}
			else{
				prev=q;
				q=q->left;
			}
		}
		if(strcmp(prev->word,str)>=0) prev->right=p;
		else prev->left=p;
	}
	return root;
}
BSTREE *constructBinary(char filename[],BSTREE *root){
	FILE *fp=fopen(filename,"r");
	char str[30],ch;
	int i=0, weight=0;
	while(fscanf(fp,"%c",&ch)>=1){
		if((ch>='a' && ch<='z') || ch==' ') str[i++]=ch;		// stores each word
		if(ch>='0' && ch<='9') weight = weight*10 + ch - 48;		// calculates weight given in social database file
		if(ch=='\n' || ch==EOF){
			str[i-1]='\0';
			i=0;
			root=insert(str,root, weight);			// inserts word and weight into binary tree
			weight = 0;					// weight reset to zero for next word
		}
	}
	fclose(fp);
	return root;
}
void printBstree(BSTREE *node){
	if(node!=NULL){
		printBstree(node->left);
		printf("%s, weight=%d\n",node->word,node->weight);
		printBstree(node->right);
	}
}
char opcodeMenu(void){
	char a;	
	int opcode,q;
	printf("------------------------------------------------------------------------------\n");
	printf("Enter the code of Enquiry from  the menu below :\n\n");
	printf("1 : View the blacklisted words\n");
	printf("2 : Search for a blacklisted word \n");
	printf("3 : Check for the spam mail\n");
	printf("4 : Edit the weight of a blacklisted word\n");
	printf("5 : Add a word\n");
	printf("6 : Delete a word\n");
	printf("7 : Exit the portal\n");
	printf("------------------------------------------------------------------------------\n");
	printf("Enter your response :\n");
	scanf("%d",&opcode);
	while(opcode<1 || opcode>7){
		printf("Please enter a valid number!\n");
		scanf("%d", &opcode);
	}
	return opcode;
}
void printMenu(char filename[],char extension[]){		// prints all social areas from which mails can be received
	printf("\nEnter the type of mail from the below menu:\n\n");
	printf("-> Commerce\n");
	printf("-> Employment\n");
	printf("-> Financial\n");
	printf("-> General\n");
	printf("-> Marketing\n");
	printf("-> Medical\n");
	printf("\nYour response:\n");
	scanf("%s",filename);
	getchar();
	if(filename[0]>='A' && filename[0]<='Z') filename[0]=filename[0]+32;
	int i,len=strlen(filename);
	filename[len++]='.';
	filename[len++]='t';
	filename[len++]='x';
	filename[len++]='t';
	filename[len]='\0';
	// '.txt' extension is added to chosen social database and that particular filename's content will later be stored into the Blacklist
}
void func1(void){		// View the Blacklisted words
	char filename[100],extension[10],mail[20],add[20],delete[20],opcode;
	BSTREE *root=NULL;
	FILE *fp;
	printMenu(filename,extension);
	root=constructBinary(filename,root);	// constructs btree with the social database file
	printf("\nThe Blacklisted words are: \n");
	printBstree(root);			// prints btree
	
	return;
}
//Uncomment this for individual Task 1 ----->   OPCODE  1

/*

void selection(int opcode,TRIE *trie){
	int op;	
	switch(opcode){
		case 1:
			func1();
			break;
		case 2:
	//		func2();	
			break;
		case 3:
	//		func3(trie);
			break;
		case 4:
	//		func4();
			break;
		case 5:
	//		func5();
			break;
		case 6:
	//		func6();
			break;
		case 7:
	//		func7();
			break;
	}
	op=opcodeMenu();
	selection(op,trie);
	return;
}


int main(){
	int opcode,i;
	FILE *fp,*fp1;
	TRIE *root=NULL;
	fp =fopen("words.txt", "r");
	char str[20],c;
	root=readFile(fp,root);
	opcode=opcodeMenu();
	selection(opcode,root);
	return 0;
}

*/
