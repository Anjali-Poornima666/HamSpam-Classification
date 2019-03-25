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
int C2I(char ch){
	return (int)ch - (int)'a';
}
TRIE *getNode(void){		
    TRIE *cnode = NULL;
    cnode = (TRIE *)malloc(sizeof(TRIE));
    if (cnode){
        int i;
        cnode->isLeaf = false; 
        for (i = 0; i < 26; i++) cnode->children[i] = NULL;
    }
    return cnode;
}
void inserttrie(TRIE *root,char key[]){	// insert words/ phrases into trie
    int level, index, length;
    length = strlen(key);
    TRIE *cnode = root; 
    for (level = 0; level < length; level++) {
        index = C2I(key[level]);
        if (!cnode->children[index]) cnode->children[index] = getNode();
        cnode = cnode->children[index];
    }
    cnode->isLeaf = 1;	// proper word
}
int y=0;
int search(TRIE *root, const char *key){	// returns the number of articles/ non-key words present in the user's input mail
    int level, length, index;
    length = strlen(key);
    TRIE *trie = root;
    for (level = 0; level < length; level++){
        index = C2I(key[level]);
        if (!trie->children[index]) break;
        trie = trie->children[index];
    }
    if(level==length) y++;		// incrementing count
    return y;
}
TRIE* readFile(FILE *fp,TRIE *root)		// reads 'words.txt' and inserts articles/ non-keywords in trie
{
    root = getNode(); 
    int i,count=0;
    int l;
    char str[50];
	fp =fopen("words.txt", "r");
	while((fscanf(fp,"%s",str))>0){
		l=strlen(str);
		for(i=0;i<l;i++){
			if(str[i]>=65 && str[i]<=90)
			str[i]=str[i]+32;		// if capital - convert to small
		}
        		inserttrie(root,str);
	}
	return root;
}
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
BSTREE *searchFile(char mail[],BSTREE *node){			// If word matches in user's input mail and the Blacklist - frequency of word is increased
	FILE *fp=fopen(mail,"r");
	char c,store[20];
	int index=0,length=strlen(node->word);
	while(fscanf(fp,"%c",&c)>=1){
		if(c>='A' && c<='Z') c=c+32;
		if((c>=97 && c<=122) || c==' ' ||c=='.' ||c=='?' ||c=='!' ||c==',' || c=='(' || c==')' || c=='-' || c=='/'){
			if(c==node->word[index]) index++;
			else if(index==length){
				node->freq++;
				index=0;
			}	
			else if(c!=node->word[index]) index=0;
		}
	}
	fclose(fp);
	return node;	
}
void searchWord(char mail[],BSTREE *node){		// recursive function to check if the word is present in the Blacklist or not
	if(node!=NULL){
		node=searchFile(mail,node);		
		searchWord(mail,node->left);		
		searchWord(mail,node->right);
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
bool searchForGiven(BSTREE *node,char add[]){	// checks if word is present in the Blacklist (btree) or not
	while(node!=NULL){
		
		if(strcmp(node->word,add)>0) node=node->right;
		else if(strcmp(node->word,add)<0) node=node->left;
		else return 1;	
	}
	return 0;
}
void rewrite(FILE *fp,BSTREE *node,char delete[]){	// rewrites the social database file without the word to be deleted
	if(node!=NULL){
		rewrite(fp,node->left, delete);
		if(strcmp(node->word,delete)!=0) fprintf(fp,"%s %d\n",node->word, node->weight);
		rewrite(fp,node->right, delete);
	}
}

int generalCount(char fname[],TRIE *trie)	// counts total number of words common in the user's input mail and trie
{
	TRIE *root=trie;
	FILE *fp1=fopen(fname,"r");
       	int i=0;
       	char c,str[20];
       	while(fscanf(fp1,"%c",&c)>=1){
		if(c==' ' ||c=='.' ||c=='?' ||c=='!' ||c==',' || c=='(' || c==')' || c=='-' || c=='/' || c=='\n'){
			str[i]='\0';
			y=search(root,str);
			i=0;
		}
		else{
			if(c>='A' && c<='Z')
				c=c+32;
			str[i++]=c;
		}
		}
		fclose(fp1);
		return y;
}

int wordCount(char fname[],TRIE *trie){
	FILE *fp=fopen(fname,"r");
	int count=0;
	char c;
	while(fscanf(fp,"%c",&c)>=1){
		if(c==' ' ||c=='.' ||c=='?' ||c=='!' ||c==',' || c=='(' || c==')' || c=='-' || c=='/'){
			count++;		// counts total number of words in user's input mail
			fseek(fp,1,SEEK_CUR);
			fscanf(fp,"%c",&c);
			if(c==' ' ||c=='.' ||c=='?' ||c=='!' ||c==',' || c=='(' || c==')' || c=='-' || c=='/') count--;
			fseek(fp,-1,SEEK_CUR);
		}		
	}
	int k=generalCount(fname,trie);	// returns count of words present in the user's input mail and in trie
	return count-k;		// returns useful wordcount density
}

int densityOfSpam(BSTREE *root, int num){
	if(root!=NULL){
		num = densityOfSpam(root->left, num);
		num = num + (root->freq)*(root->weight);
		num = densityOfSpam(root->right, num);
	}
	return num;	// returns density of words present in the Blacklist matching with user's input mail
}
void modify(BSTREE *node,char *A,int w){	// modifies weight of the word in social database file

	if(node!=NULL){
		if(strcmp(node->word,A)==0){
		node->weight=w;
		}
		modify(node->left,A,w);
		modify(node->right,A,w);
	}
	
}
void rewriteModified(FILE *fp,BSTREE *node){		// rewrites social database file
	if(node!=NULL){
		rewriteModified(fp,node->left);
		fprintf(fp,"%s %d\n",node->word, node->weight);
		rewriteModified(fp,node->right);
	}
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
void func2(void){		// Search if a word is present in the Blacklist or not
	char filename[100],extension[10],mail[20],word[20],opcode;
	int k;
	BSTREE *root=NULL;
	FILE *fp;
	printMenu(filename,extension);
	root=constructBinary(filename,root);
	printf("Enter the blacklisted word to be searched :\n");
	scanf("%[^\n]s",word);
	k=searchForGiven(root,word);	// returns 1 if word is present in the Blacklist (btree)
	if(k==1) printf("The given word is in the blacklisted words...\n");
	else printf("The given word is NOT in the blacklisted words...\n");
	return;
}
void func3(TRIE *trie){		// Check if the mail is a spam or a ham
	char filename[100],extension[10],mail[20],add[20],delete[20],opcode;
	BSTREE *root=NULL;
	FILE *fp;
	printMenu(filename,extension);
	printf("Enter the name of mail :\n");
	scanf("%s",mail);
	root=constructBinary(filename,root);
	searchWord(mail,root);			// increments frequency if word is present in user's input mail
	int totalWordsDensity = wordCount(mail,trie)*100;	// (totalWords - articles)*100
	int spamDensity = densityOfSpam(root, 0);		// (spam weight * frequency)
	float percentage = ((float)spamDensity/(float)totalWordsDensity)*100;		// percentage to check whether spam or ham
	if(percentage>5) printf("******** THE GIVEN MAIL IS A SPAM ********\n");
	else printf("******** THE GIVEN MAIL IS A HAM ********\n");
	return;
}
void func4(void){		// edit the weight of a Blacklisted word

	char filename[100],extension[10],mail[20],add[20],delete[20],opcode,option;
	int p,weight;
	BSTREE *root=NULL;
	FILE *fp;
	printMenu(filename,extension);
	root=constructBinary(filename,root);
	printBstree(root);
	printf("Enter the word for which the weight has to be edited :\n");
	scanf("%[^\n]s", add);
	getchar();
	p=searchForGiven(root,add);
	if(p==0){
		printf("The word you entered is not in the Blacklist\nDo you want to add it to the Blacklist?y/n\n");
		
		scanf("%c",&option);
		getchar();
		if(option=='y' || option=='Y'){	// to add new word
			printf("Enter the weight of the word :\n");
			scanf("%d", &weight);
			root=insert(add,root, weight);	// word added into btree
			fp=fopen(filename,"a");
			fprintf(fp,"%s %d\n",add, weight);	// word added into database social file
			printf("%s has been added to the Blacklist with weight %d\n",add, weight);
			fclose(fp);
		}
		else if(option=='n' || option =='N') return;
	}
	else{
		printf("Enter the modified weight :\n");
		scanf("%d",&p);
		modify(root,add,p);	// modify weight in btree
		printBstree(root);
		fp=fopen(filename,"w");
		rewriteModified(fp,root);	// rewrite in social database file
		fclose(fp);
	}
	return ;
}
void func5(void){		// add a word in the Blacklist
	char filename[100],extension[10],mail[20],add[20],delete[20];
	int p,opcode;
	BSTREE *root=NULL;
	FILE *fp;
	printMenu(filename,extension);
	root=constructBinary(filename,root);
	printBstree(root);
	printf("Enter the word to be added in the Blacklist :\n");
	scanf("%[^\n]s", add);
	getchar();
	p=searchForGiven(root,add);	// checks if word is already present
	if(p==1) printf("The word you entered is already in the Blacklist\n");
	else{
		int weight;
		printf("Please enter the weight of the word :\n");
		scanf("%d", &weight);
		root=insert(add,root, weight);	// inserted into btree
		fp=fopen(filename,"a");
		fprintf(fp,"%s %d\n",add, weight);	// written into social database file
		printf("%s has been added to the Blacklist with weight %d\n",add, weight);
		fclose(fp);
	}

	return;
}
void func6(void){		// delete a word from the Blacklist
	char filename[100],extension[10],mail[20],add[20],delete[20];
	int p,opcode;
	BSTREE *root=NULL;
	FILE *fp;
	printMenu(filename,extension);
	root=constructBinary(filename,root);	
	printf("Enter the word to be deleted from the Blacklist :\n");
	scanf("%[^\n]s", delete);
	getchar();
	p=searchForGiven(root, delete);		// checks if word is present in the Blacklist
	if(p==0) printf("No such word exists in the Blacklist\n");
	else{
		fp=fopen(filename,"w");
		rewrite(fp,root, delete);		// rewrites social database file without the word to be deleted
		fclose(fp);
		printf("%s has been deleted from the Blacklist\n", delete);
	}
	return;
}
void func7(void){		// used to exit the portal
	exit(1);return;
}
void selection(int opcode,TRIE *trie){
	int op;	
	switch(opcode){
		case 1:
			func1();		// Displaying the Blacklisted words of that social database file
			break;
		case 2:
			func2();		// Search if a word/ phrase exists in the Blacklist
			break;
		case 3:
			func3(trie);	// Check if the user's input mail is a spam or a ham
			break;
		case 4:
			func4();		// Edit the weight of any Blacklisted word/ phrase
			break;
		case 5:
			func5();		// Add a word/ phrase to the Blacklist with weight
			break;
		case 6:
			func6();		// Delete a word/ phrase from the Blacklist
			break;
		case 7:
			func7();		// Exit the portal
			break;
	}
	y=0;
	op=opcodeMenu();
	selection(op,trie);	// loops until 7 is chosen to exit
	return;
}
int main(){
	int opcode,i;
	FILE *fp,*fp1;
	TRIE *root=NULL;
	fp =fopen("words.txt", "r");
	char str[20],c;
	root=readFile(fp,root);	// stores content of 'words.txt' into trie
	opcode=opcodeMenu();	// Asks user which functionality they want to use
	selection(opcode,root);	// Loops till exit portal option is chosen
	return 0;
}
