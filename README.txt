P038 - Spam/Ham Classification


Group members:
Anjali Poornima Karri: 201611132
Chadalavada Mounika: 201611117
Karuturi Sri Harshitha: 201611133
Parkhi Mohan: 201601061

The project is a system that classifies emails as spam or ham based on some predefined Blacklisted words (the user also has the option to remove or add words of his choice). The blacklisted words also have weights, eg. "credit cards" has the weight 48% but "free" has weight 97% as a percentage based on their respective usage in spam mails. The user's email is classified as a spam or ham mail based on the density of the keywords in the Blacklist.

The data structures used are:
A binary search tree is used to insert all the Blacklisted words (files were created as database based on different sectors of society having different words/ phrases as Blacklisted ones) from the particular file into the binary tree. The tree is traversed to check if the Blacklisted words are present in the user's input mail and if present - frequency of that word is incremented. A binary tree is used because it supports fast storage, retrieval and deletion methods.
Trie data structure is used to store all the articles (eg. is, am, are, the, etc) and non-key words which will not be counted (if present in the input mail) while calculating the spam density of the user's mail and deciding whether it's a spam or ham. Trie data structure is used so that looking up data becomes faster and it provides alphabetical ordering.

The main function begins with inserting all the articles from file "words.txt" into the trie data structure. Then the opcode menu is displayed that gives the user 7 options namely:
1. View the blacklisted words
2. Search if a word/ phrase exists in the Blacklist
3. Check if the user's input mail is a spam or a ham
4. Edit the weight of any Blacklisted word/ phrase
5. Add a word/ phrase to the Blacklist with weight
6. Delete a word/ phrase from the Blacklist
7. Exit the portal
The user should select a valid opcode to proceed.
This is followed by a calling function - selection (runs on loop till 7 is chosen) - that calls the particular functions to perform the respective opcode tasks.

func1(): Displaying the blacklisted words of a particular sector
Begins with calling function: printMenu() that asks the user to enter which sector of society his email belongs to from the list provided. A '.txt' extension is added by the code and words/ phrases from that particular file are loaded into the binary tree by calling constuctBinary(). The tree is then traversed through pre-order and all Blacklisted words and phrases are displayed to the user with their respective weight.

func2(): Searching if a word/ phrase is present in the Blacklist
Begins with calling function: printMenu() - same as above to store all Blacklisted words/ phrases into the binary tree of chosen sector by calling constuctBinary(). The program then asks the user to enter the word or phrase they want to check and tells if it is a part of the Blacklist or not.

func3(): Check whether the user's input mail is a spam or ham
Begins same as above by calling function printMenu() to store all Blacklisted words/ phrases into the binary tree of chosen sector by calling constuctBinary(). Then a recursive function searchWord() is called that calls searchFile inside it which checks if the words/ phrases present in the binary tree are present in the user's input mail. If present - the frequency of that word is increased (the structure of tree consists of the word/ phrase, it's weight and it's frequency that has been initialised to zero).
Then a function called wordCount() is called that internally counts all words of the user's input mail and then subtracts the occurances of articles stored into the trie and returns final count without articles. The returned value is multiplied by hundred because the weight of the words stored in the database files (based on different sectors) are stored as a percentage.
Then a function called densityOfSpam() is called that travels the tree through pre-order traversal and sums the (weight*frequency) of each word/ phrase and returns the final value.
Finally the percentage of totalWordsDensity/SpamDensity*100 is calculated. If the percentage is above 5% then it is a spam mail, else it is a ham mail.

func4(): Edit the weight of any Blacklisted word/ phase
Begins by calling printMenu() and storing all words/ phrases of the chosen sector file into the binary tree by calling constuctBinary().
The program asks the user which word's weight he would like to edit.
If the word exists in the Blacklist - their desired weight is asked and appropriate changes are made in the binary tree and the database sector file.
If the word doesn't exist in the database - the user is asked if they would like to add that word into the Blacklist (y/n?)
If 'y' then the desired weight of the word is asked and it is added to the binary tree by calling modify() and the database sector file is rewritten by calling rewriteModified().

func5(): Add a word/ phrase into the Blacklist with desired weight
Starts by calling printMenu() and storing all words/ phrases of the chosen sector file into the binary tree by calling constuctBinary().
The program asks the user to enter the word they wish to add to the Blacklist. Function searchForGiven() is called which checks if the entered word already exists in the Blacklist or not. If word already exists, program tells the user that the word is already present in the Blacklist. Otherwise, the user is asked the desired weight of the word and it is added to the binary tree by calling modify() and the database sector file is rewritten by calling rewriteModified().

func6(): Delete a word/ phrase from the Blacklist
Starts by calling printMenu() and storing all words/ phrases of the chosen sector file into the binary tree by calling constuctBinary().
The program asks the user to enter the word to be deleted from the Blacklist. Function searchForGiven() is called which checks if the entered word exists in the Blacklist or not. If no such word exists, program tells the user that no such word exists in the Blacklist. Otherwise, the database sector file is rewritten by calling the function rewrite(). Hence the database sector file is edited and the desired user's word has now been removed.

func7():
Used to exit the portal

All tasks have been completed.
Task 1: To separate words/ phrases in the email and eliminate punctuation marks, non-content keywords and articles.
Task 2: Creating a Blacklist and giving the user the facility to add, remove, edit weight of any Blacklisted word.
Task 3: Find the density of the Blacklisted words in the email and tell if it is a spam or a ham.
