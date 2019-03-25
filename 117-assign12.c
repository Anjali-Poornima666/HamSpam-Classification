#include"061-assign12.c"

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
bool searchForGiven(BSTREE *node,char add[]){	// checks if word is present in the Blacklist (btree) or not
	while(node!=NULL){
		
		if(strcmp(node->word,add)>0) node=node->right;
		else if(strcmp(node->word,add)<0) node=node->left;
		else return 1;	
	}
	return 0;
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
//Uncomment this for individual Task 2 ----->   OPCODE  2

/*

void selection(int opcode,TRIE *trie){
	int op;	
	switch(opcode){
		case 1:
	//		func1();
			break;
		case 2:
			func2();	
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
