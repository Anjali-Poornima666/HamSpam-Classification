#include"117-assign12.c"

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

void rewrite(FILE *fp,BSTREE *node,char delete[]){	// rewrites the social database file without the word to be deleted
	if(node!=NULL){
		rewrite(fp,node->left, delete);
		if(strcmp(node->word,delete)!=0) fprintf(fp,"%s %d\n",node->word, node->weight);
		rewrite(fp,node->right, delete);
	}
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

//COMMENT THIS WHILE TESTING INDIVIDUAL FILE.


//Uncomment this for individual Task 2 SubPart-1 ----->   OPCODE  3 And OPCODE  4

/*

void selection(int opcode,TRIE *trie){
	int op;	
	switch(opcode){
		case 1:
	//		func1();
			break;
		case 2:
	//		func2();	
			break;
		case 3:
			func3(trie);
			break;
		case 4:
			func4();
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

