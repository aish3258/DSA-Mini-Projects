#include<stdio.h>
#include<stdlib.h>
#include<string.h>  //for strcpy( i.e.String copy)

//Structure of each node
struct node{
    char name[20];      //Conatain the name of page we have visited
    struct node *next;  //pointer to next node
    struct node *pre;   //pointer to preivious node
};


//Function Declaration
struct node *newPage(struct node *head, struct node *curr,char page[]);
struct node *back(struct node *head, struct node *curr);
struct node *forward(struct node *curr);
void display(struct node *head);

int main()
{
    int ch;
    char page[20];
    struct node *curr=NULL;  //Have address of current open website
    struct node *head=NULL;
    struct node *new= (struct node *) malloc(sizeof(struct node));
    strcpy(new->name,"Google");
    new->next= new->pre=NULL;
    head=new;   //1st website will be always Google
    curr=new;

    while(1)
    {
        printf("\n\n\t\tMENU\n1. Visit New Page\n2. Back\n3. Forward\n4. Show Current Page\n5. Show Full History\n6. Exit\n\n\tEnter your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
            printf("Enter name of page: ");
            scanf("%s",page);
            curr=newPage(head,curr,page);
            break;

            case 2:
            curr=back(head,curr);
            break;

            case 3:
            curr=forward(curr);
            break;

            case 4:
            printf("\nCurrently viewing: %s",curr->name);
            break;

            case 5:
            printf("\nYour whole browsing history:-\n");
            display(head);
            break;

            case 6:
            struct node *temp=head, *temp1;
            while(temp != NULL)
            {
                temp1=temp;
                temp=temp->next;
                free(temp1);
            }
            head=NULL;
            printf("\n\tExiting the program..!!");
            exit(0);
            
            default:
                printf("Invalid Choice..!!");

        }
    }
    return 0;
}

struct node *newPage(struct node *head, struct node *curr, char page[])
{
    struct node *new;
    
    if(curr->next != NULL)
    {
        /*if the conditiom becomes true then definately we have came backward and we have to insert a new page.To do that we have to delete exsiting forward pages.*/

        struct node *temp=curr->next, *temp1;
        while(temp != NULL)
        {
            temp1= temp;
            temp=temp->next;
            free(temp1);
        }
        curr->next=NULL; //Breaking the link for safety
    }

    new=(struct node *) malloc(sizeof(struct node));
    if(new==NULL)
    {
        printf("Memory is full..!!");
        return curr;
    }

    strcpy(new->name,page);
    new->next=NULL;
    curr->next=new;
    new->pre=curr;
    curr=curr->next;
    printf("Visited page: %s\nCurrent page: %s",curr->name,curr->name);
    return curr;
}


struct node *back(struct node *head, struct node *curr)
{
    if(curr->pre == NULL)
        printf("No previous page available.\nCurrent page: %s",curr->name);
    else
    {
        curr=curr->pre;
        printf("Moved Back.\nCurrent page: %s",curr->name);
    }
    return curr;
}


struct node *forward(struct node *curr)
{
    if(curr->next == NULL)
        printf("No forward page available\nCurrent page: %s",curr->name);
    else
    {
        curr=curr->next;
        printf("Moved forward\nCurrent page: %s",curr->name);
    }
    return curr;
}

void display(struct node *head)
{
    struct node *temp=head->next;
    printf("[Google]");   //Google is by default 1st page so will be printed always.
    while(temp != NULL)
    {
        printf(" -> [%s]",temp->name);
        temp=temp->next;
    }
}