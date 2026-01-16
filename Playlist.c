#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

//Struct of the Circular Doubly Linked List (default looping)
struct node
{
    char song[50];       //Contain the name of the song
    struct node *pre;    //Address of previous node
    struct node *next;   //Address of the next node
};

//Structure of the playlist 
struct  playlist
{
    struct node *head;    //Head pointer of the circular doubly linked list
    struct node *curr;   //Point to the currently playing song
    struct node *tail;   //Point to the last node by which insertion becomes O(1)
    int flag;            //To check that funtion executed or not
};

//Funtion to add New Song
struct playlist *addSong(struct playlist *p, char name[])
{
    struct node *newNode= (struct node *) malloc(sizeof(struct node));
    p->flag=0;

    if(newNode==NULL)
        p->flag=0;       //insertion didn't happended becoz memory is full
    else
    {
        //Prepare the node
        strcpy(newNode->song,name);
        newNode->next=newNode->pre=NULL;

        if(p->head ==  NULL)
        {
            newNode->next=newNode;
            newNode->pre=newNode;
            p->head=newNode;
            p->tail=newNode;
            p->curr=newNode;
        }
        else
        {
            newNode->pre=p->tail;
            newNode->next=p->head;
            p->tail->next=newNode;
            p->head->pre=newNode;
            p->tail=newNode;
        }
        p->flag=1;   //Insertion happended
    }
    return p;     //return playlist
}


//Delete current Song
struct playlist *deletesong(struct playlist *p)
{
    p->flag=0;
    //Playlist is empty
    if(p->curr== NULL)
        p->flag=0;
    else
    {
        //Case 1: There is only SINGLE SONG in playlist
        if(p->head == p->tail )
        {    
            free(p->curr);
            p->head=p->tail=p->curr=NULL;
        }
        //Case 2: Current is the starting song.
        else if(p->head == p->curr)
        {
            
            p->head=p->head->next;
            p->head->pre=p->tail;
            p->tail->next=p->head;
            free(p->curr);
            p->curr=p->head;
        }
        //Case 3: Current node is the last song.
        else if(p->curr == p->tail)
        {
            p->tail=p->tail->pre;
            p->tail->next=p->head;
            p->head->pre=p->tail;
            free(p->curr);
            p->curr=p->head;
        }
        //Case 4: Current is a middle song.
        else
        {
            struct node *temp=p->curr;
            p->curr->pre->next=p->curr->next;
            p->curr->next->pre=p->curr->pre;
            p->curr=p->curr->next;
            free(temp);
        }
        p->flag=1;        
    }
    return p;
}

//Shuffe the playlist 
struct playlist *shuffle(struct playlist *p)
{
    struct node *temp=p->head;
    int len=0;   //Store lenght of the playlist

    //Find the lenght of the playlist
    do
    {
        len++;
        temp=temp->next;
    } while (temp != p->head);

    //If playlist has more than one song then only shuffle can be happen
    if(len > 1)
    {
        int steps= rand() % len;    //Generates random number within the length of the playlist

        for(int i = steps; i != 0; i--)
        {
            p->curr= p->curr->next;
        }
    }
    return p;
}

//Display Funtion
void display(struct playlist *p)
{
    struct node *temp=p->head;
    do
    {
        printf("-> [%s]  ",temp->song);
        temp=temp->next;
    }while(temp != p->head);
}

//Free memory taken by nodes function
struct playlist *freeplaylist(struct playlist *p)
{
    struct node *temp,*temp1;
    
    //Break the circular links
    p->tail->next=NULL;
    p->head->pre=NULL;

    //Free memory
    temp=p->head;
    while(temp != NULL)
    {
        temp1=temp->next;
        free(temp);
        temp=temp1;
    }

    //Reset the pointers
    p->head=p->tail=p->curr=NULL;
    return p;
}

//Main funtion
int main()
{
    //srand() sets randomness, rand() generates numbers, % controls range
    //random numbers are generated using rand(), and to avoid repeating sequences we seed it once using srand(time(NULL)).
    srand(time(NULL));

    //Object of playist and memory allocation 
    struct playlist *p= (struct playlist *) malloc(sizeof(struct playlist));
    if(p==NULL)
    {
        printf("Not enought space.. \nExiting the program..!!");
        exit(0);
    } 
    //Pointers initilization
    p->curr=p->tail=p->head=NULL;
    p->flag=0;

    char name[50];   //Takes song name form the user
    char buff[10];       //Menu choice input
    int ch;

    while(1)
    {
        //Menu Displayed to the user
        printf("\n\n\t----------MENU----------\n1. Add Song\n2.Show Current Song\n3. Play Next\n4. Play Previous\n5. Delete Current Song\n6. Show Playlist\n7. Shuffle\n8. Exit\n\tEnter your choice:");
        fgets(buff, sizeof(buff), stdin);   //Takes choice string input
        ch=atoi(buff);                      //Convert string input to int

        switch(ch)   //Switch Cases
        {
            case 1:
                printf("Enter Song name to add:");
                fgets(name,  sizeof(name),  stdin);   //Takes the input
                name[strcspn(name,"\n")]= '\0';       //Replace \n to \0
                p=addSong(p,name);                    //Add New Song funtion calling

                //If new song get added then
                if(p->flag)
                    printf("song added into playlist\nCurrently Playing:%s.",p->curr->song);
                else
                    printf("New playlist can't be added..!!");
            break;

            case 2:
                if(p->curr == NULL)
                    printf("Playlist is empty..!!");
                else
                    printf("Currently Playing:%s",p->curr->song);
            break;

            case 3:
                if(p->curr == NULL)
                    printf("Playlist is empty..!!");
                else
                {    
                    p->curr=p->curr->next;
                    printf("Playing next song:%s",p->curr->song);
                }
            break;

            case 4:
                if(p->curr == NULL)
                    printf("Playlist is empty..!!");
                else
                {    
                    p->curr=p->curr->pre;
                    printf("Playing perivious song:%s",p->curr->song);
                }
            break;

            case 5:
                p=deletesong(p);   //Delete funtion calling 

                //If deletion happens then
                if(p->flag)
                {    printf("Current song removed from playlist..\n");

                    if(p->curr != NULL)
                        printf("Currently Playing:%s",p->curr->song);
                    else
                        printf("No current song is being played..!!");
                }
                else
                    printf("Playlist is empty,nothing to delete..!!");
            break;

            case 6:
                if(p->head==NULL)
                    printf("Playlist is empty..!!");
                else
                {
                    printf("Head  ");
                    display(p);
                }
            break;

            case 7:
                if(p->head != NULL)
                {    p=shuffle(p);
                    printf("After Shuffle..\nCurrently Playing:%s",p->curr->song);
                }
                else
                    printf("Playlist is empty... \nCan't do shuffline");

            break;

            case 8:
                //Free all the allocated memory
                p=freeplaylist(p);
                free(p);    //Free memory used by playlist struct.
                printf("Exiting the program..!!");
                exit(0);   
            break;

            default:
            printf("Error.! Invalid chocie.!!");
        }
    }
    return 0;
}