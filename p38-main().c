#include"132-assign12.c"
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
