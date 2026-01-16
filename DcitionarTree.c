#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Structure of each node
struct node 
{
    char DicWord[30];    //Stores the key word (BST Key)
    char DicMeaning[500];   //store the meaning of the word
    struct node *left;     //Store the address of left child
    struct node *right;     //Store the address of right child
};

//Funtion to insert new word into the tree
struct node *insert(struct node *root, char word[], char meaning[], int *success)
{
    //Base Conditon
    if(root == NULL)
    {
        struct node *newNode= (struct node *) malloc(sizeof(struct node));

        //Memroy overflow
        if(newNode == NULL)
        {
            *success = 0;
            return NULL;
        }

        //Prepare the node
        strcpy(newNode->DicWord, word);
        strcpy(newNode->DicMeaning, meaning);
        newNode->left= newNode->right = NULL;

        *success = 1;   //insertion was successfull
        return newNode;
    }

    //Stores the value of key (greater or smaller than root node) 
    int cmp= strcmp(word, root->DicWord);

    //dublicate key
    if(cmp == 0)
    {
        *success = -1;
        return root;
    }

    // Go to left subtree
    if(cmp < 0)
        root->left = insert(root->left, word, meaning, success);
    else   //goes to right subtree
        root->right = insert(root->right, word, meaning, success);
        
    return root;
}


//Funtion to search a word into existing dictionary
//if the key node is found then it will return the address of the key node else NULL value
struct node *search(struct node *root , char key[])
{
    if( root == NULL || strcmp(root->DicWord , key ) == 0)
        return root;

    //goes to left
    if( strcmp( key , root->DicWord) < 0)
        return search(root->left, key);
    else   //goes right
        return search(root->right , key);
}

//Funtion to delete a word form the dictionary tree
struct node *deleteNode(struct node *root, char key[], int *success)
{
    //Base case
    if(root == NULL)
    {   
        *success = -1;   //key node didn't exist
        return root;
    }

    //compare and if key value is smaller then root then goes to left
    else if(strcmp(key , root->DicWord) < 0)
        root->left= deleteNode(root->left, key, success);

    else if(strcmp( key , root->DicWord ) > 0)   //else goes to right
        root->right = deleteNode(root->right, key, success);

    else
    {
        *success = 1;  //deletion will happen

        // Case 1 & 2: node with 0 or 1 child
        if(root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        
        // Case 3: node with 2 children
        struct node *succ=root->right;
        
        //Find the inorder successor
        while( succ->left != NULL)
            succ=succ->left;
        
        //Copy the data of successor node to root node
        strcpy(root->DicWord, succ->DicWord);
        strcpy(root->DicMeaning, succ->DicMeaning);

        //delete the inorder successor
        root->right= deleteNode(root->right, succ->DicWord, success);
    }
    return root;
}


//Funtion to display the dictionar content
void display( struct node *root)
{
    if( root != NULL)
    {
        display(root->left);
        printf("-> %s : %s\n",root->DicWord,root->DicMeaning);
        display(root->right);
    }
}

//Funtion to free up memry space
void freenode(struct node *root)
{
    if(root == NULL)
        return;
    
    freenode(root->left);
    freenode(root->right);
    free(root);
}

//Mian Funtion
int main()
{
    char word[30], meaning[500], key[30];        
    int roll,ch, success=0; 

    struct node *root= NULL;      //Root pointer of the tree

    //Infinite loop for MENU display
    while(1)
    {
        printf("\n\n\t\t----------------------DICTIONARY MENU---------------------\n1. Add new word\n2. Search Word\n3. Delete word\n4. Display Dictionary\n5. Exit\n\tEnter your choice:");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                printf("Enter the word:");  
                scanf("%s",word);                           //Takes the word from the user
                getchar();    // <-clear the string buffer
                printf("Enter meaning of %s:",word);
                fgets(meaning, sizeof(meaning), stdin);     //Takes the meaning from the user
                meaning[strcspn(meaning, "\n" )] = '\0';    //replacing \n with \0
                success = 0;                                //Restting success variable
                root= insert(root,word,meaning,&success);   //Insert funtion calling

                //Success status of the function
                if(success == 1)
                    printf("New word %s has been added into disctionary..!!",word);
                else if(success == -1)
                    printf("Word %s already exits into the dictionary..");
                else
                    printf("New word can't be added becoz memory overflows..");
            break;

            case 2:
                //If tree isnt null then do the searching
                if(root != NULL)
                {
                    printf("Enter the word to search:");
                    scanf("%s", key);
                    //Store the address of the key word node return by the search funtion
                    struct node *found= search(root, key);

                    //if key word found
                    if(found != NULL)
                        printf("\n\nWord:- %s\nMeaning:- %s",key,found->DicMeaning);
                    else  //if key word didn't exist
                        printf("following word doesn't exist into dictionary..");
                }
                else  //else print tree is empty
                    printf("Dictionary is empty...\nCan't do searching..!!\n\n");
            break;

            case 3:
                if(root != NULL)
                {
                    printf("Enter the word to search:");
                    scanf("%s", key);
                    success=0;
                    root=deleteNode(root, key, &success);

                    //Was deletion of node successfull?
                    if(success == 1)
                        printf("%s word has been removed from the dictionary..!!",key);
                    else
                        printf("Word didn't exist into dictionary..!!");
                }
                else
                    printf("Dictionary is emtpy..\nNothing to delete");
            break;

            case 4:
                if(root == NULL)
                    printf("Dictionary is empty.. Nothing to display..!!");
                else
                {   
                    printf("\n\n----Dictionary Contents-------\n");
                    display( root );
                }
            break;

            case 5:
                if( root != NULL)
                    freenode(root);   //Free up the memory space occupied by the nodes
                printf("Exiting the program..!!");
                exit(0);
            break;

            default:
                printf("\nError..\nInavlid choice..!!");

        }
    }
    return 0;
}