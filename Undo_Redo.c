/*I am implementing the Undo and Redo Funtion by Stack using Linked List Data Structre.

Core points:
Rule 1: Performing a new action
    When user performs a new action:
    Push action onto Undo stack
    Clear the Redo stack
    ❗ Why clear redo?
    Because once you do something new, old redo history becomes invalid.

🔹 Rule 2: Undo operation
    Wen user presses Undo:
    Pop top action from Undo stack
    Push it onto Redo stack
    Apply reverse of that action (conceptually)
    If Undo stack is empty → nothing to undo.

🔹 Rule 3: Redo operation
    When user presses Redo:
    Pop top action from Redo stack
    Push it back onto Undo stack
    Re-apply the action
    If Redo stack is empty → nothing to redo.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Structure of node 
struct node 
{
    char action[50];   //Stores the action like "Type A" , "Delete A"
    struct node *next; //Pointer field to next node 
};

//Structure of stack
struct stack{
    struct node *undo;   //Undo stack head pointer
    struct node *redo;   //Redo stack head pointer
};


//Add New Action Funtion
struct stack *addAction(struct stack *s, char action[])
{
    struct node *newNode, *temp, *temp1;

    //When new action is added Redo stack will become empty (for more detail see RULE 1)
    if(s->redo != NULL)
    {
        temp=s->redo;
        while(temp != NULL)  //Until redo stack is empty
        {
            temp1=temp->next;
            free(temp);       //Free memory
            temp=temp1;       //traverse the linked list
        }
        s->redo=NULL;  //Reset the pointer for betterment of me and chat gpt😂😉
    }

    //Allocate new memory for the new node by malloc funtion
    newNode=(struct node *) malloc(sizeof(struct node));
    
    // If memeory is full then return
    if(newNode == NULL)
        printf("Stack Overflow");
    else
    {
        //Prepair the node and insert new node at the begining and top element is pointer by  "undo"(head of undo stack) pointer
        strcpy(newNode->action, action);
        newNode->next=s->undo;
        s->undo=newNode;
    }
    return s;
}

//Undo Operation Funtion
struct stack *UndoOperation(struct stack *s)
{
    if(s->undo == NULL)
        printf("Nothing to undo..!!");
    else
    {
        struct node *temp= s->undo;
        s->undo= s->undo->next;
        temp->next=s->redo;
        s->redo=temp;
        printf("Undo Performed : %s\n",temp->action);
    }
    return s;
}

//Redo Operation funtion
struct stack *RedoOperation(struct stack *s)
{
  if(s->redo == NULL)
    printf("Nothing to redo");
    else
    {
        struct node *temp=s->redo;
        s->redo=s->redo->next;
        temp->next=s->undo;
        s->undo=temp;
        printf("Redo Performed: %s\n",temp->action);
    }
    return s;
}

//Display Funtion 
void display(struct node *n)
{
    struct node *temp=n;
    while(temp)
    {
        printf("[%s]\n",temp->action);
        temp=temp->next;
    }
}

//Mian Funtion
int main()
{
    char action[50];   //Stores tha action
    char buf[10];      //Stores the user choice (using this instead of scanf)
    int ch;

    //Allocating memory to store the undo & redo stack head pointer address
    struct stack *s =(struct stack *) malloc(sizeof(struct stack));
    
    //Initialize stacks
    s->undo=NULL;
    s->redo=NULL;

    while(1)
    {
        printf("\n\n\tMENU\n1. Perform New Action\n2. Undo\n3. Redo\n4. Show Undo Stack\n5. Show Redo Stack\n6. Exit\n\tEnter your choice: ");
        fgets(buf, sizeof(buf), stdin);   //takes the user input in string value.
        ch= atoi(buf);    //atoi -> ASCII to INT

        switch(ch)
        {
            case 1:
                printf("Enter the action action:"); 
                fgets(action,50,stdin);  //Takes the input from the keyboard adn store into variable
                action[strcspn(action, "\n")]= '\0';  //Replace the new line with null-terminator from the string
                s=addAction(s,action);
                printf("Action %s added.",action);
            break;

            case 2:
                s=UndoOperation(s);
            break;

            case 3:
                s=RedoOperation(s);
            break;

            case 4:
                if(s->undo == NULL)
                    printf("Undo stack underflow..!!");
                else
                {
                    printf("Undo Stack:\n");
                    display(s->undo);
                }
            break;

            case 5:
                if(s->redo == NULL)
                    printf("Redo stack underflow..!!");
                else
                {
                    printf("Redo Stack:\n");
                    display(s->redo);
                }
            break;

            case 6:
                struct node *temp, *temp1;

                //Free up memory used by Undo stack
                temp=s->undo;
                while(temp != NULL)
                {
                    temp1=temp->next;
                    free(temp);
                    temp=temp1;
                } 
                s->undo=NULL;

                //Free up memory used by Redo stack
                temp=s->redo;
                while(temp != NULL)
                {
                    temp1=temp->next;
                    free(temp);
                    temp=temp1;
                }
                s->redo=NULL;
                printf("Exiting the program..!!");
                exit(0);
            break;

            default:
            printf("Error..!!!\nInvalid choice..!!");
        }
    }
    return 0;
}

/*--------------------IMPORTANT-----------------------

While I take input by scanf contain space. It leaves an the space and the next word in the buffer so we will be using fgets()

SYNTAX:
fgets(buffer, size, stdin);
buffer -> varibale name
size -> string size
stdin -> standard input (keyboard)

--------VERY IMP-------------
1.When every we use scanf() before fgets() we have to clear the buffer using getchar() (return char from the buffer). 
    WHY..???
becoz everytime scanf() function leaves the '\n' (new line) into the buffer but this also didnt work i was facing some more issue so we will be taking input as a stirng and then we will convert it to integer using atoi(string_name) i.e. ASCII to int.


2.Usually fgets() conatin the '\n' (new line) into the input so we replace that 
'\n\' (new line)  ->  '\0' (null-terminator) by using strcspn() i.e. string complement span.

SYNATX:
size_t strcspn(const char *str1, const char *str2);
    Ex: strcspn(action, \n);
strcspn(str1, str2) returns the index of the first occurrence of any character from str2 in str1.   (simply index return karta hai)
*/