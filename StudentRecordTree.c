#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Structure of the each student details
struct node{
    int sRoll;              //BST key (unique for comparing)
    char sName[50];         //Stores the name of the student
    float sAvg;           //Stores the marks of the student
    struct node *left;     //Stores the location of left child
    struct node *right;     //Stores the location of right child
};

//Insert new student record into the exiting tree
struct node *insert(struct node *root, char name[], int roll, float avg, int *success)
{
    struct node *newNode;
    newNode= (struct node *) malloc(sizeof(struct node));
    if(newNode == NULL)  
        *success=0;     //if no memory space has been allocated then return
    else
    {
        //Prepare the node
        strcpy(newNode->sName, name);    //copy the content of the name into sName 
        newNode->sRoll= roll;   //Copy roll number
        newNode->sAvg= avg;    //copy avg marks
        newNode->left= newNode->right= NULL;

        if(root == NULL)
            root= newNode;  //New node will become the 1st node
        else
        {
            struct node *temp=root;
            //traverse the tree to find position
            while(1)
            {
                //If same roll number is entered twice
                if(temp->sRoll == roll)
                {
                    *success = 2;   //duplicate value found
                    free(newNode);   //free up memeory of dublicated value node
                    return root;
                }
                //If the upcoming roll number is small then goes to left
                else if(roll < temp->sRoll )
                {
                    if(temp->left == NULL)
                    {
                        temp->left = newNode;   //newNode will become left child
                        break;                  //break infinite loop
                    }
                    temp=temp->left;           //Keep going left
                }
                //if roll number is greater then goes to right
                else
                {
                    if(temp->right == NULL)
                    {
                        temp->right= newNode;   //Becomes the right child
                        break;                 //breake the loop
                    } 
                    temp=temp->right;         //Keep traversing
                }
            }
        }
        *success = 1;     //Insertion happened successfull
    }
    return root;
}

//Delete function to deleted desire student
struct node *deleteSt(struct node *root, int key, int *success)
{
    struct node *temp=root, *parent= NULL;

    //Tree is empty
    if(root == NULL)
        *success=0;
    else
    {
        //Find the key node
        while( temp != NULL && temp->sRoll != key )
        {
            parent=temp;
            
            if(key < temp->sRoll)
                temp=temp->left;
            else
                temp=temp->right;
        }

        //Step 1:If student detail doesn't exist
        if(temp == NULL)
        {   
            *success= -1;
            return root;
        }
        //Step 2: Have 2 childs
        else if( temp->left != NULL && temp->right != NULL)
        {
            struct node *succ=temp->right;
            struct node *succparent=temp;

            //find the inorder successor
            while(succ->left != NULL)
            {   
                succparent=succ; 
                succ=succ->left;
            }

            //Copy successor data 
            strcpy(temp->sName, succ->sName);
            temp->sRoll= succ->sRoll;
            temp->sAvg= succ->sAvg;

            //Delete successor insead of temp
            temp=succ;
            parent=succparent;    
        }
        
        // Step 3: Node has 0 or 1 child
        struct node *child=NULL;
        if(temp->left == NULL)
            child= temp->right;
        else
            child= temp->left;

        //Step 4: Delete root node
        if(parent == NULL)
        {
            free(temp);
            *success = 1;
            return child;
        }
        
        //step 5: Delete non-root node
        if(parent->left == temp)
            parent->left=child;
        else
            parent->right=child;

        free(temp);
        *success=1;  
    }
    return root;
}

//Funtion to search & update the detail of a student
/*This funtion will return the address of the key node if found else return NULL */
struct node *search(struct node *root, int key)
{
    struct node *temp=root;

    while(temp != NULL)
    {
        //Key value found
        if(temp->sRoll == key)
            return temp;
        
        //Traverse the tree to find the student 
        if( key < temp->sRoll)
            temp=temp->left;
        else
            temp=temp->right;
    }
    return NULL;  //if the student detail doesnt exist's
}

//Display all the students
void display(struct node *root)
{
    if(root != NULL)
    {
        display(root->left);
        printf("\n%d        \t%s \t%f",root->sRoll,root->sName,root->sAvg);
        display(root->right);
    }
}

//Funtion to free up the dynamically alllocated memory space
void freetree(struct node *root)
{
    if(root == NULL)
        return;

    freetree(root->left);
    freetree(root->right);
    free(root);
}

//Main Function
int main()
{
    char name[50], buff[10];        //Student name, buffer string
    int roll,ch,key, success=0;        //Student roll number, user choice, function report(success/failure)
    float avg;                    //Student avarage marks
    
    struct node *root= NULL;      //Root pointer of the tree

    //Infinite loop for MENU display
    while(1)
    {
        printf("\n\n\t\tMENU\n1. Add new student\n2. Search Student\n3. Delete Student\n4. Display All Students\n5. Update Student\n6. Exit\n\tEnter your choice:");
        fgets(buff, sizeof(buff), stdin);            //Takes the your choice in string fomat
        ch= atoi(buff);                             //atoi -> ASCII to INT
        switch(ch)
        {
            case 1:
                printf("\nEnter the name of the student:");
                fgets(name, sizeof(name), stdin);          //Takes input form the user
                name[strcspn(name , "\n")]= '\0';          //Replace the new line with null terminator
                printf("Enter Roll Number:");
                scanf("%d",&roll);                         //Student roll number  
                printf("Enter average marks:");
                scanf("%f",&avg);                          //Student avg marks
                getchar();  // <- Clear the buffer
                root= insert(root, name, roll, avg, &success);  //Function calling

                //Checking is insertion was successfull or not
                if(success == 1)
                    printf("Details of student %d has be registered successfully..!!",roll);
                else if(success == 2)
                    printf("Student with same roll number already exist..!!");
                else
                    printf("New student record can't be added becoz memory is full");
            break;

            case 2:
                printf("Enter the roll number:");
                scanf("%d",&key);
                getchar();  // <- Clear the buffer
                //Tree is empty
                if(root == NULL)  
                    printf("Student record is empty..");
                else
                {   
                    struct node *found= search(root,key);
                    /*Check the detail of the student exist's or not
                    if exist's then print its content*/
        
                    if(found)   //non null pointer is true in c
                    {   //if the student is found then print its details
                        printf("\nRoll No.\tName\tAverage marks");
                        printf("\n------------------------------------");
                        printf("\n%d        \t%s \t%f",found->sRoll,found->sName,found->sAvg);
                    }else
                        printf("Student details doesn't exist");
                }
            break;

            case 3:
                printf("Enter the roll no. :");
                scanf("%d",&key);
                getchar();  // <-Clear buffer
                root = deleteSt(root,key,&success);

                //Check deletion was successful or not
                if(success)
                    printf("Detail of %d has been deleted successfully",key);
                else if(success == -1)
                    printf("Error...\nStudent having roll no.%d doesn't exist..!!");
                else if( success == 0)
                    printf("Student tree is empty");
            break;

            case 4:
                if( root == NULL)
                    printf("Student record is empty..!!");
                else
                {
                    printf("\nRoll No.\tName\tAverage marks");
                    printf("\n------------------------------------");
                    display(root);
                }
            break;

            case 5:
                printf("Enter the roll number:");
                scanf("%d",&key);
                getchar();   // <-clear buffer
                printf("\n\nDISCLAIMER: You can't update the roll number of a student\nEnter new update name of the student:");
                fgets(name, sizeof(name), stdin);     //takes the input
                name[strcspn( name, "\n" )] = '\0';  //change new line with null terminator
                printf("Enter new update name of the avg marks:");
                scanf("%f",&avg);
                getchar();  // <- Clear the buffer
                //Tree is empty
                if(root == NULL)  
                    printf("Student record is empty..");
                else
                {   
                    struct node *found= search(root,key);
                    /*Check the detail of the student exist's or not
                    if exist's then print its content*/
        
                    if(found)   //non null pointer is true in c
                    {   //if the student is found then update and print their details
                        strcpy(found->sName,name);
                        found->sAvg=avg;
                        printf("\nRoll No.\tName\tAverage marks");
                        printf("\n------------------------------------");
                        printf("\n%d        \t%s \t%f",found->sRoll,found->sName,found->sAvg);
                    }else
                        printf("Student details doesn't exist");
                }
            break;

            case 6:
                if(root)  //If tree isn't empty then
                    freetree(root);   //Free allocated memory spaces
                printf("Exiting the program..!");
                exit(0);
            break;

            default:
                printf("Error..\nInvalid choice, try again..!!");
        }
    }
    return 0;
}