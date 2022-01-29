#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
/* Define Functions*/
int cnum=0;
void clearInput(void);
void addNewroom(void);
void listAll(void);
void deleteroom(void);
void modifyroom(void);
int findroom(void);
int prompt(void);
int findnum (int);
/* Define Structures*/
typedef struct room {
    int number;        /*unique account number*/
    char name[20];     /*contains name*/
    char aadhar[15];    /*contains aadhar number*/
    char email[20];           /*contains email address*/
    struct room *next; /*next is used to navigate through structures.*/
    int count;   
    } Room;
Room *firstc,*currentc,*newc; /*pointers*/
int main()
{
   
    char ch;
   

    do
    {
	fflush(stdin);
	puts("\nWelcome To The hotel Database");
	puts("-- -----------------------------");
	puts("1 - Add a new room details");
	puts("2 - Delete history of room details");
	puts("3 - List all room and room details");
	puts("4 - Modify room details");
	puts("5 - Find a room detail by name");
	puts("-- -----------------------------");
	puts("Q - Save and quit\n");
	printf("\tYour choice:");
	ch = getchar();
	    ch = toupper(ch);/*changes user input case to upper case*/
	switch(ch)     
	{
	    case '1':
		puts("Add a new room details \n");
		fflush(stdin);
		addNewroom();
		break;
	    case '2':
		puts("Delete a room details \n");
		deleteroom();
		break;
	    case '3':
		puts("List all room details \n");
		listAll();
		break;
	    case '4':
		puts("Modify a room details \n");
		modifyroom();
		break;
	    case '5':
		puts("Find a room by name\n");
		findroom();
		break;
	    case 'Q':
		puts("Save and quit\n");

		default:
		break;
	}
    }
    while(ch != 'Q');
    currentc = firstc;
    if(currentc == NULL)
	    return(0);		
            /*closes data file*/
    return(0);
}
void addNewroom(void)
{
    newc = (struct room *)malloc(sizeof(struct room));
    if(firstc==NULL)
	firstc = currentc = newc;
    else
    {
	currentc = firstc;    
	while(currentc->next != NULL)
            currentc = currentc->next;
	currentc->next = newc;  
	currentc = newc;       
    }
    cnum++;
    printf("%27s: %5i\n","room number",cnum);
    currentc->number = cnum;    /*cnum is used to give unique room numbers*/
    printf("%27s: ","Enter customer name");
    gets(currentc->name);
    printf("%27s: ","Enter contact aadhar number");
    gets(currentc->aadhar);
    printf("%27s: ","Enter contact email");
    gets(currentc->email);
    printf("********  room details added  ******** ");
    currentc->count=0;
    currentc->next = NULL;
}
void listAll(void) /* list all room details function*/
{
    if(firstc==NULL)
	puts("There are no room details to display!"); 
    else
    {
	    printf("%6s %-20s %-15s %-15s\n","Acct#","Name","aadhar","Email");
	puts("------ -------------------- ------------- -------------------");
	currentc=firstc;
	do
	{
		printf("%6d: %-20s %-15s %-20s\n",\
		currentc->number,\
		currentc->name,\
		currentc->aadhar,\
		currentc->email);
		/*prints values of number, name, aadhar and email*/
	}
	while((currentc=currentc->next) != NULL);
    }
}
void deleteroom(void)     /*delete contact function */
{
    int record;
    struct room *previousa=firstc;
    if(firstc==NULL)
    {
	puts("There are no room details to delete!");
	return;
    }
    listAll();		/* show all records*/
    printf("Enter room number to delete: ");
    scanf("%d",&record);
    currentc = firstc;
	if(currentc->number==record)
	{
		firstc=currentc->next;
		free(currentc);
	    printf("room deatils %d deleted!\n",record);
	    return;
	}
	currentc=currentc->next;
    while(currentc != NULL)
    {
	if(currentc->number == record)
	{
	   previousa->next=currentc->next;
	free(currentc);
	    printf("room deatils %d deleted!\n",record);
	    return;
	}
	else
	{
	    currentc = currentc->next;
		previousa=previousa->next;
	}
    }
    printf("room details %d not found!\n",record);
 }
void modifyroom(void)   /*modify contact function*/
{
    int record, result;
    if(firstc==NULL)
    {
	puts("There are no room details to modify!");
	return;
    }

    listAll();		/* show all records */
    printf("Enter room account number to modify or change: ");
    scanf("%d",&record);  
    result = findnum(record);
    if( result >0 ){
	    printf("Contact no %d:\n",currentc->number);
	    printf("Name: %s\n",currentc->name);
	    if(prompt())
		    gets(currentc->name);
	    printf("aadhar: %s\n",currentc->aadhar);
	    if(prompt())
		    gets(currentc->aadhar);
	    printf("Email: %s\n",currentc->email);
	    if(prompt())
		    gets(currentc->email);
	    return;
	}
    printf("room details %d was not found!\n",record);
}
int findnum (int recordnum)
{
    int record;
    record = recordnum;
    currentc = firstc;
    while(currentc != NULL)
    {
	if(currentc->number == record)
	     {
	   return 1;
	 }
	else
	{
	    currentc = currentc->next;
	}
    }
    return -1;
}
int findroom(void) /* find contact function*/
{
     char buff[20];
     if(firstc==NULL)
	{
	puts("There are no room details to find!");
	    return 1;
    }
    printf("Enter room name: ");
    fflush(stdin);/*clears any text from the input stream*/
    gets(buff);
    currentc = firstc;
    while(currentc != NULL)
    {
	if( strcmp(currentc->name, buff) == 0 )
	    {
			printf("%6s %-20s %-15s %-15s\n","Acct#","Name","aadhar","Email");
			/*prints table titles*/
	    printf("%6d: %-20s %-15s %-20s\n",\
	    currentc->number,\
	    currentc->name,\
	    currentc->aadhar,\
	    currentc->email);
			return 0;
	   }
		else
		{         currentc = currentc->next;      }
    }
    printf("contact %s was not found!\n",buff);
	  return 1;
}
int prompt(void)
{
	char ch;
    fflush(stdin);
	printf("Update? (Y to update any other key to not)");
	ch = getchar();
	ch = toupper(ch);
	fflush(stdin);
	if(ch == 'Y')
	{
		printf("Enter new value: ");
		return(1);
	}
	else
		return(0);
}
