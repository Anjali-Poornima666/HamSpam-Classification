#include"133-assign12.c"

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
//>>>>>>>>

//Uncomment this for individual Task 3 SubPart-2 ----->   OPCODE  5 , 6 AND 7

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
	//		func3(trie);
			break;
		case 4:
	//		func4();
			break;
		case 5:
			func5();
			break;
		case 6:
			func6();
			break;
		case 7:
			func7();
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

