#include<stdio.h>
#include<stdlib.h>
#include<string.h>  //For using strcpy & strcmp

//Structure of the nodes
struct node
{
    char name[50];
    char number[15];
    struct node *next;
};

//Insertion fucntion. 
struct node *insert(struct node *head, char getName[], char getNumber[])
{
    struct node *newNode, *temp;
    newNode=(struct node *) malloc(sizeof(struct node));

    if(newNode == NULL)
        printf("No Enough Memory..!!");
    else
    {
        strcpy(newNode->name, getName);
        strcpy(newNode->number, getNumber);
        //Insertion at the Beginning
        newNode->next=head;
        head=newNode;
        printf("\tContact Added..!!");
    }
    return head;
}

//Insertion Sorting
struct node *sortContact(struct node *head)
{ 
    struct node *sorted, *temp,*curr, *nextCurr;
    sorted=temp=curr=nextCurr=NULL;

    curr=head;
    while(curr != NULL)
    {
        nextCurr= curr->next;
        temp=sorted;

        //CASE 1: Insert at the begining
        if(sorted == NULL || strcmp(curr->name, sorted->name) < 0)
        {
            curr->next=sorted;
            sorted=curr;
        }
        //CASE 2: At the MIDDLE or END
        else
        {
            //Traverse the list until u find the place to insert the node
            while(temp->next != NULL && strcmp( temp->next->name,curr->name) < 0)
                temp=temp->next;

            curr->next=temp->next;
            temp->next=curr;
        }
        curr=nextCurr;
    }
    head=sorted;
    return head;
}

//Deletion Function
struct node *deleteContact(struct node *head, char getName[])
{
    struct node *pre, *temp=head;

    if(head==NULL)
        printf("Contact is Empty..!!");
    else
    {
        //Desire node is 1st node
        if(strcmp(head->name,getName) == 0)
        {
            head=head->next;
            free(temp);
            printf("%s contact deleted..!!",getName);
        }
        else
        {
            //Traverse the list until  linked list is empty and desire node is found
            while(temp != NULL && strcmp(temp->name,getName) != 0)
            {
                pre=temp;
                temp=temp->next;
            }

            //Desire node doesn't exist
            if(temp == NULL)
            {
                printf("Contact doesn't exist");
            }
            else
            {
                pre->next= temp->next;
                free(temp);
                printf("%s contact deleted..!!",getName);
            }
        }
    }
    return head;
}

//Display Funtion
void display(struct node *head)
{
    struct node *temp=head;

    if(head==NULL)
        printf("Contact is Empty..!!");
    else
    {
        while(temp != NULL)
        {
            printf("[%s : %s ] ->",temp->name,temp->number);
            temp=temp->next;
        }
        printf("NULL");
    }
}

int main()
{
    struct node *head=NULL;
    char getName[50], getNumber[15];
    int choice;

    while(1)
    {
        printf("\n\n\t--------------- PHONE BOOK MENU ---------------\n1.Add Contact\n2.Display Contacts\n3.Delete Contact\n4.Sort Contacts\n5.Exit\nEnter your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            printf("\nEnter the name:");
            scanf("%s",getName);
            printf("\nEnter the phone number:");
            scanf("%s",getNumber);
            head=insert(head,getName,getNumber);
            break;
            
            case 2:
            display(head);
            break;
            
            case 3:
            printf("\nEnter the name:");
            scanf("%s",getName);
            head=deleteContact(head,getName);
            break;
            
            case 4:
            printf("Sorted Contacts: \n");
            head=sortContact(head);
            display(head);
            break;

            case 5:
            printf("Exiting the program!!");
            struct node *temp ,*temp1;
            temp=head;
            while(temp != NULL)
            {
                temp1=temp->next;
                free(temp);
                temp=temp1;
            }
            exit(0);
            
            default:
            printf("Invalid Choice..!!");

        }
    }
    return 0;
}