/*
This is a program of "book shop"

This program is having several function by using double link list.

It provides some basic functions like adding books to record, deleting from record, 
printing the book list, seaching from the record and updating the current record.

In addidtion, we also created some additional function. For example, to clean the whole record by 1-click, 
to input and output a file called 'record.DAT' in the root of C Drive 
and to use several key words for searching or sorting the record.

We assume that the title and the ISBN of every books are unique 
that means there will not have same title and ISBN of different books.
However, author and type can be found in differnt books.


Created by
Leo Kong Chi Wai 11650109
Angus Li Hoi Leong 11652012
Sunny Leung Chung Hang 11651628

Finished on 5th April 2013
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct record
{
	char author[21];
	char title[51];
	double price;
	int quantity;
	char ISBN[14];
	int type;
	int time;
	record* next;
	record* previous;
} Node;

void instructions(void);
void addbook (Node**, int*);
void deletebook (Node**, int*);
void printbooklist (Node*, int, int);
void searchbook (Node**);
void clean (Node**, int*);
void inout (Node**, int*);
void update (Node**);
void sort (Node**, int);

int main()
{
	Node* pFirst = NULL;
	int input, adjust, counting = 0;

	do
	{
		instructions();
		printf("Please input your choice: ");
		scanf(" %d", &input);

	
		switch (input)
		{
		case 1:
			addbook (&pFirst, &counting);
			break;
		case 2:
			printbooklist (pFirst, counting, input);
			if (counting > 0)
				deletebook (&pFirst, &counting);
			break;
		case 3:
			if (counting > 0)
			{
				do
				{
					printf("Do you want to adjust the order of the book lisk first?\n(1=YES and 2=NO): ");
					scanf(" %d", &adjust);
					if (adjust < 1 || adjust > 2)
						printf("Sorry! Input Error! Try Again!\n\n");
					if (adjust == 1)
						sort (&pFirst, input);
					if (adjust == 2)
						printf("\nThere may not have a meaningful order!\n");
				}while (adjust < 1 || adjust > 2);
			}
			printbooklist (pFirst, counting, input);
			break;
		case 4:
			if (counting > 0)
				searchbook (&pFirst);
			else
				printbooklist (pFirst, counting, input);
			break;
		case 5:
			if (counting > 0)
				clean(&pFirst, &counting);
			else
				printbooklist (pFirst, counting, input);
			break;
		case 6:
			printbooklist (pFirst, counting, input);
			if (counting > 0)
				update (&pFirst);
			break;
		case 7:
			if (counting > 0)
				sort (&pFirst, input);
			else
				printbooklist (pFirst, counting, input);
			break;
		case 8:
			inout (&pFirst, &counting);
			break;
		case 0:
			printf( "Thank you for using! \n\n" );
			break;
		default:
				printf("Sorry! Input Error! Try Again!\n\n");
			break;
		}

	}while (input != 0);

	return 0;
}

void instructions (void)
{
	printf("WELCOME TO THE BOOK SHOP SYSTEM OF HKBU CIE 2013. \n");
	printf("*******************************************************************************\n");
	printf("1) To Add a new book to the list. \n");
	printf("2) To Delet a book from the list \n");
	printf("3) To Display the current book list & Order. \n");
	printf("4) To Search from the list & Order. \n");
	printf("5) To Clean all of the list. \n");
	printf("6) To Update current book list. \n");
	printf("7) To Adjust sorting by different method. \n");
	printf("8) To Input or Output record. \n");
	printf("0) To Exit. \n");
	printf("*******************************************************************************\n");
}

void addbook (Node** pFirst, int* counting)
{
	Node* pNew;
	int count = *counting, contin, addcount=0; 
	bool end=false;

	do
	{
		pNew = (Node*) malloc (sizeof(Node));
		printf("\nPlease enter the name of the book (max. 50): ");
		scanf(" ");
		gets(pNew->title);
		printf("Please enter the author of [%s] (max. 20): ", pNew->title);
		scanf(" ");
		gets(pNew->author);
		printf("Please enter the price of [%s]: ", pNew->title);
		scanf(" %lf", &(pNew->price));
		printf("Please enter the quantity of [%s]: ", pNew->title);
		scanf(" %d", &(pNew->quantity));
		printf("Please enter the 13-DIGI ISBN of [%s]: ", pNew->title);
		scanf(" ");
		gets(pNew->ISBN);
		printf("Please enter the tpye code of [%s]: ", pNew->title);
		scanf(" %d", &(pNew->type));
		printf("\n");
		pNew->time = count+1;


		if (*pFirst == NULL)
		{
			pNew->previous = NULL;
			pNew->next = NULL;
			*pFirst = pNew;
		}

		else
		{
			Node* pLoc;
			pLoc = *pFirst;
			while(pLoc->next != NULL)
				pLoc = pLoc->next;
			pNew->next = NULL;
			pNew->previous = pLoc;
			pLoc->next = pNew;
		}

		count++;
		addcount++;

		do
		{
			printf("Do you want to add more books?\n(1=YES and 2=NO): ");
			scanf(" %d", &contin);
			if (contin < 1 || contin > 2)
				printf("Sorry! Input Error! Try Again!\n\n");
			if (contin == 2)
			{
				end = true;
				if (addcount < 2)
					printf("You added %d record.\n\n", addcount);
				else
					printf("You added %d records.\n\n", addcount);
			}
		}while (contin < 1 || contin > 2);
	}while (!end);
	*counting = count;
}

void printbooklist (Node* pFirst, int counting, int input)
{
	Node* pLoc;
	int yesno, order;
	double price;
	char ISBN[14];
	pLoc = pFirst;
	
	if (pLoc == NULL)
		printf("Sorry! The book list is empty now!\n\n");
	else
	{
		if (counting <2)
			printf("\nThere is %d record.\n", counting);
		else
			printf("\nThere are %d records.\n", counting);
		printf("****************************The List of Book Record****************************\n");
		printf("Title                Author          Price   Quantity    Type     ISBN\n");
		printf("*******************************************************************************\n");
		do
		{
			printf("%-20s %-15s %5.2lf  %-11d %-8d %s\n", pLoc->title, pLoc->author, pLoc->price, pLoc->quantity, pLoc->type, pLoc->ISBN);
			pLoc = pLoc->next;
		}while (pLoc != NULL);
		printf("\nEnd of Record.\n\n");
			
		if (input == 3)
		{
			do
			{
				printf("Do you want to order?\n(1=YES and 2=NO): ");
				scanf(" %d", &yesno);
				if (yesno <1 || yesno >2)
					printf("Sorry! Input Error! Try Again!\n\n");
				if (yesno == 1)
				{
					pLoc = pFirst;
					printf("Please enter the ISBN from the above list: ");
					scanf(" ");
					gets(ISBN);
					while (pLoc != NULL && strcmp(pLoc->ISBN, ISBN) != 0)
						pLoc = pLoc->next;
					if (pLoc == NULL)
						printf("Sorry! There is no [%s] of ISBN of the book.\n\n", ISBN);
					else if (strcmp(pLoc->ISBN, ISBN) == 0)
					{
						if (pLoc->quantity <=0)
								printf("Sorry! [%s] is out of stock.\n\n", pLoc->title);
						else
						{
							do
							{
								printf("How many do you want to order? ");
								scanf(" %d", &order);
								if (order < 1)
									printf("The number of order cannot less than 1! Try Again!\n\n");
								if (order > pLoc->quantity)
									printf("[%s] only has %d in stock! Try Again!\n\n", pLoc->title, pLoc->quantity);
								if (!(order < 1 || order > pLoc->quantity))
								{
									pLoc->quantity = pLoc->quantity - order;
									price = order * pLoc->price;
									printf("The total cost is $%5.2lf.\n", price);
									printf("It is ordered!\n\n");
									break;
								}
							}while (order < 1 || order > pLoc->quantity);
						}
					}
				}
				if (yesno == 2)
				{
					printf("Back to main menu\n\n");
					break;
				}
			}while (yesno <1 || yesno >2);
		}
		
	}
}

void deletebook (Node** pFirst, int* counting)
{
	Node* pLoc;
	int count = *counting;
	char ISBN[14];
	int yesno;
	pLoc = *pFirst;
	do 
	{
		printf("Do you still want to delete?\n(1=YES and 2=NO): ");
		scanf(" %d", &yesno);
		if (yesno == 1)
		{
			printf("Please enter the ISBN from the above list: ");
			scanf(" ");
			gets(ISBN);

			while (pLoc != NULL && strcmp(pLoc->ISBN, ISBN) != 0)
				pLoc = pLoc->next;

			if (pLoc == NULL)
				printf("Sorry! There is no [%s] of ISBN of the book.\n\n", ISBN);

			else if (strcmp(pLoc->ISBN, ISBN) == 0)
			{
				if (pLoc->previous == NULL)
				{
					if (pLoc->next != NULL)
					{
						*pFirst = pLoc->next;
						(*pFirst)->previous = NULL;
					}
					else
						*pFirst = NULL;
				}

				if (pLoc->previous != NULL)
				{
					if (pLoc->next != NULL)
					{
						(pLoc->previous)->next = pLoc->next;
						(pLoc->next)->previous = pLoc->previous;
					}
					else
					{
						(pLoc->previous)->next = NULL;
					}
				}		
				*counting = --count;
				printf("The book [%s] is deleted.\n\n", pLoc->title);
				pLoc = NULL;
			}
		}
		if (yesno == 2)
		{
			printf("Back to main menu\n\n");
			break;
		}

		if (yesno < 1 || yesno > 2)
			printf("Sorry! Input Error! Try Again!\n\n");

	}while (yesno < 1 || yesno > 2);
}

void searchbook (Node** pFirst)
{
	int choice, order, yesno;
	double price;
	Node *pLoc;
	char author[21];
	int type;
	char title[51]; //unique element
	char ISBN[14]; //unique element

	do
	{
		printf("You can search by the following elements: \n");
		printf("1) Title\n");
		printf("2) Author\n");
		printf("3) ISBN Code\n");
		printf("4) Type Code\n");
		printf("What is your choice? ");
		scanf(" %d", &choice);
		if (choice > 4 || choice <1)
			printf("Sorry! Input Error! Try Again!\n\n");
	}while (choice > 4 || choice <1);

	if (choice == 1)
	{
		printf("Please enter the Title: ");
		scanf(" ");
		gets(title);
		pLoc = *pFirst;
		while (pLoc != NULL && strcmp(pLoc->title, title) != 0)
			pLoc = pLoc->next;
		if (pLoc == NULL)
			printf("Sorry! There is no book called [%s].\n\n", title);
		else if (strcmp(pLoc->title, title) == 0)
		{
			printf("****************************The Searching Result*******************************\n");
			printf("Title                Author          Price   Quantity    Type     ISBN\n");
			printf("*******************************************************************************\n");
			printf("%-20s %-15s %5.2lf  %-11d %-8d %s\n", pLoc->title, pLoc->author, pLoc->price, pLoc->quantity, pLoc->type, pLoc->ISBN);
			do
			{
				printf("\nDo you want to order it?\n(1=YES and 2=NO): ");
				scanf(" %d", &yesno);
				if (yesno <1 || yesno >2)
					printf("Sorry! Input Error! Try Again!\n\n");
				if (yesno == 1 && pLoc->quantity>0)
				{
					do
					{
						printf("How many do you want to order? ");
						scanf(" %d", &order);
						if (order < 1)
							printf("The number of order cannot less than 1! Try Again!\n\n");
						if (order > pLoc->quantity)
							printf("[%s] only has %d in stock! Try Again!\n\n", pLoc->title, pLoc->quantity);
						if (!(order < 1 || order > pLoc->quantity))
						{
							pLoc->quantity = pLoc->quantity - order;
							price = order * pLoc->price;
							printf("The total cost is $%5.2lf.\n", price);
							printf("It is ordered!\n\n");
							break;
						}
					}while (order < 1 || order > pLoc->quantity);
				}
				if (yesno == 1 && pLoc->quantity <=0)
					printf("Sorry! [%s] is out of stock.\n\n", pLoc->title);
				if (yesno == 2)
				{
					printf("Back to main menu\n\n");
					break;
				}
			}while (yesno <1 || yesno >2);
		}
	}

	if (choice == 2)
	{
		printf("Please enter the Author: ");
		scanf(" ");
		gets(author);
		pLoc = *pFirst;
		while (pLoc != NULL && strcmp(pLoc->author, author) != 0)
			pLoc = pLoc->next;
		if (pLoc == NULL)
			printf("Sorry! There is no book of [%s].\n\n", author);
		else if (strcmp(pLoc->author, author) == 0)
		{
			printf("****************************The Searching Result*******************************\n");
			printf("Title                Author          Price   Quantity    Type     ISBN\n");
			printf("*******************************************************************************\n");
			do
			{
				if (strcmp(pLoc->author, author) == 0)
					printf("%-20s %-15s %5.2lf  %-11d %-8d %s\n", pLoc->title, pLoc->author, pLoc->price, pLoc->quantity, pLoc->type, pLoc->ISBN);
				pLoc = pLoc->next;
			}while(pLoc != NULL);
			do
			{
				printf("\nDo you want to order?\n(1=YES and 2=NO): ");
				scanf(" %d", &yesno);
				if (yesno <1 || yesno >2)
					printf("Sorry! Input Error! Try Again!\n\n");
				if (yesno == 1)
				{
					pLoc = *pFirst;
					printf("Please enter the ISBN from the above list: ");
					scanf(" ");
					gets(ISBN);
					while (pLoc != NULL && strcmp(pLoc->ISBN, ISBN) != 0)
						pLoc = pLoc->next;
					if (pLoc == NULL)
						printf("Sorry! There is no [%s] of ISBN of the book.\n\n", ISBN);
					else if (strcmp(pLoc->ISBN, ISBN) == 0)
					{
						if (pLoc->quantity <=0)
							printf("Sorry! [%s] is out of stock.\n\n", pLoc->title);
						else
						{
							do
							{
								printf("How many do you want to order? ");
								scanf(" %d", &order);
								if (order < 1)
									printf("The number of order cannot less than 1! Try Again!\n\n");
								if (order > pLoc->quantity)
									printf("[%s] only has %d in stock! Try Again!\n\n", pLoc->title, pLoc->quantity);
								if (!(order < 1 || order > pLoc->quantity))
								{
									pLoc->quantity = pLoc->quantity - order;
									price = order * pLoc->price;
									printf("The total cost is $%5.2lf.\n", price);
									printf("It is ordered!\n\n");
									break;
								}
							}while (order < 1 || order > pLoc->quantity);
						}
					}
				}
				if (yesno == 2)
				{
					printf("Back to main menu\n\n");
					break;
				}
			}while (yesno <1 || yesno >2);
		}
	}

	if (choice == 3)
	{
		printf("Please enter the ISBN Code: ");
		scanf(" ");
		gets(ISBN);
		pLoc = *pFirst;
		while (pLoc != NULL && strcmp(pLoc->ISBN, ISBN) != 0)
			pLoc = pLoc->next;
		if (pLoc == NULL)
			printf("Sorry! There is no [%s] of ISBN of the book.\n\n", ISBN);
		else if (strcmp(pLoc->ISBN, ISBN) == 0)
		{
			printf("****************************The Searching Result*******************************\n");
			printf("Title                Author          Price   Quantity    Type     ISBN\n");
			printf("*******************************************************************************\n");
			printf("%-20s %-15s %5.2lf  %-11d %-8d %s\n", pLoc->title, pLoc->author, pLoc->price, pLoc->quantity, pLoc->type, pLoc->ISBN);
			do
			{
				printf("\nDo you want to order it?\n(1=YES and 2=NO): ");
				scanf(" %d", &yesno);
				if (yesno <1 || yesno >2)
					printf("Sorry! Input Error! Try Again!\n\n");
				if (yesno == 1 && pLoc->quantity>0)
				{
					do
					{
						printf("How many do you want to order? ");
						scanf(" %d", &order);
						if (order < 1)
							printf("The number of order cannot less than 1! Try Again!\n\n");
						if (order > pLoc->quantity)
							printf("[%s] only has %d in stock! Try Again!\n\n", pLoc->title, pLoc->quantity);
						if (!(order < 1 || order > pLoc->quantity))
						{
							pLoc->quantity = pLoc->quantity - order;
							price = order * pLoc->price;
							printf("The total cost is $%5.2lf.\n", price);
							printf("It is ordered!\n\n");
							break;
						}
					}while (order < 1 || order > pLoc->quantity);
				}
				if (yesno == 1 && pLoc->quantity <=0)
				printf("Sorry! [%s] is out of stock.\n\n", pLoc->title);
				if (yesno == 2)
				{
					printf("Back to main menu\n\n");
					break;
				}
			}while (yesno <1 || yesno >2);
		}
	}

	if (choice == 4)
	{
		printf("Please enter the Type Code: ");
		scanf(" %d", &type);
		pLoc = *pFirst;
		while (pLoc != NULL && pLoc->type != type)
			pLoc = pLoc->next;
		if (pLoc == NULL)
			printf("Sorry! There is no book of type %d.\n\n", type);
		else if (pLoc->type == type)
		{
			printf("****************************The Searching Result*******************************\n");
			printf("Title                Author          Price   Quantity    Type     ISBN\n");
			printf("*******************************************************************************\n");
			do
			{
				if (pLoc->type == type)
					printf("%-20s %-15s %5.2lf  %-11d %-8d %s\n", pLoc->title, pLoc->author, pLoc->price, pLoc->quantity, pLoc->type, pLoc->ISBN);
				pLoc = pLoc->next;
			}while (pLoc != NULL);
			do
			{
				printf("\nDo you want to order?\n(1=YES and 2=NO): ");
				scanf(" %d", &yesno);
				if (yesno <1 || yesno >2)
					printf("Sorry! Input Error! Try Again!\n\n");
				if (yesno == 1)
				{
					pLoc = *pFirst;
					printf("Please enter the ISBN from the above list: ");
					scanf(" ");
					gets(ISBN);
					while (pLoc != NULL && strcmp(pLoc->ISBN, ISBN) != 0)
						pLoc = pLoc->next;
					if (pLoc == NULL)
						printf("Sorry! There is no [%s] of ISBN of the book.\n\n", ISBN);
					else if (strcmp(pLoc->ISBN, ISBN) == 0)
					{
						if (pLoc->quantity <=0)
							printf("Sorry! [%s] is out of stock.\n\n", pLoc->title);
						else
						{
							do
							{
								printf("How many do you want to order? ");
								scanf(" %d", &order);
								if (order < 1)
									printf("The number of order cannot less than 1! Try Again!\n\n");
								if (order > pLoc->quantity)
									printf("[%s] only has %d in stock! Try Again!\n\n", pLoc->title, pLoc->quantity);
								if (!(order < 1 || order > pLoc->quantity))
								{
									pLoc->quantity = pLoc->quantity - order;
									price = order * pLoc->price;
									printf("The total cost is $%5.2lf.\n", price);
									printf("It is ordered!\n\n");
									break;
								}
							}while (order < 1 || order > pLoc->quantity);
						}
					}
				}
				if (yesno == 2)
				{
					printf("Back to main menu\n\n");
					break;
				}
			}while (yesno <1 || yesno >2);
		}

	}
}

void clean (Node** pFirst, int* counting)
{
	int choice;
	do
	{
		printf("This action will void the current book list, are you sure?\n(1=YES and 2=NO): ");
		scanf(" %d", &choice);
		if (choice < 1 || choice  > 2)
			printf("Sorry! Input Error! Try Again!\n\n");
		if (choice == 2)
		{
			printf("Back to main menu\n\n");
			break;
		}
		if (choice == 1)
		{
			*pFirst = NULL;
			*counting = 0;
			printf("The list is cleaned!\n\n");
		}
	}while (choice < 1 || choice  > 2);
}

void inout (Node** pFirst, int* counting)
{
	int choice, yesno, count;
	FILE* saving;
	FILE* testing;
	Node* pNew;
	Node* pLoc;

	do
	{
		printf("1) Input record\n");
		printf("2) Output record\n");
		printf("3) Back\n");
		printf("What is your choice? ");
		scanf(" %d", &choice);
		if (choice < 1 || choice > 3)
			printf("Sorry! Input Error! Try Again!\n\n");
		if (choice == 1)
		{
			saving = fopen("C://record.DAT", "r");
			if (saving == NULL)
				printf("Sorry! There is no previous record.\n\n");
			else
			{
				if (*pFirst != NULL)
				{
					do
					{
						printf("This action will void the current book list, are you sure?\n(1=YES and 2=NO): ");
						scanf(" %d", &yesno);
						if (yesno < 1 || yesno > 2)
							printf("Sorry! Input Error! Try Again!\n\n");
						if (yesno == 2)
						{
							printf("Back to main menu\n\n");
							break;
						}
						if (yesno == 1)
						{
							*pFirst = NULL;
							count = 0;
							do
							{
								pNew = (Node*) malloc (sizeof(Node));
								fscanf(saving, " %[^\n]\n", &pNew->title);
								fscanf(saving, " %[^\n]\n", &pNew->author);
								fscanf(saving, " %lf\n", &pNew->price);
								fscanf(saving, " %d\n", &pNew->quantity);
								fscanf(saving, " %d\n", &pNew->type);
								fscanf(saving, " %[^\n]\n", &pNew->ISBN);
								fscanf(saving, " %d\n", &pNew->time);
								count++;

								if (*pFirst == NULL)
								{
									pNew->previous = NULL;
									pNew->next = NULL;
									*pFirst = pNew;
								}
								else
								{
									pLoc = *pFirst;
									while(pLoc->next !=NULL)
										pLoc = pLoc->next;
									pNew->next = NULL;
									pNew->previous = pLoc;
									pLoc->next = pNew;
								}
							}while (!feof(saving));
							fclose(saving);
							*counting = count;
							printf("The record is inputed.\n\n");
						}
					}while (yesno < 1 || yesno > 2);
				}
				else
				{
					count = 0;
					do
					{
						pNew = (Node*) malloc (sizeof(Node));
						fscanf(saving, " %[^\n]\n", &pNew->title);
						fscanf(saving, " %[^\n]\n", &pNew->author);
						fscanf(saving, " %lf\n", &pNew->price);
						fscanf(saving, " %d\n", &pNew->quantity);
						fscanf(saving, " %d\n", &pNew->type);
						fscanf(saving, " %[^\n]\n", &pNew->ISBN);
						fscanf(saving, " %d\n", &pNew->time);

						count++;
	
						if (*pFirst == NULL)
						{
							pNew->previous = NULL;
							pNew->next = NULL;
							*pFirst = pNew;
						}
						else
						{
							pLoc = *pFirst;
							while(pLoc->next !=NULL)
								pLoc = pLoc->next;
							pNew->next = NULL;
							pNew->previous = pLoc;
							pLoc->next = pNew;
						}

					}while (!feof(saving));
					fclose(saving);
					*counting = count;
					printf("The record is inputed.\n\n");
				}
			}
			fclose(saving);
		}
		if (choice == 2)
		{
			if (*pFirst == NULL)
			{
				printf("Sorry! The book list is empty now!\n\n");
				break;
			}
			else
			{
				testing = fopen("C://record.DAT", "r");
				if (testing == NULL)
				{
					saving = fopen("C://record.DAT", "w");
					pLoc = *pFirst;
					while (pLoc != NULL)
					{
						fprintf(saving, "%s\n", pLoc->title);
						fprintf(saving, "%s\n", pLoc->author);
						fprintf(saving, "%lf\n", pLoc->price);
						fprintf(saving, "%d\n", pLoc->quantity);
						fprintf(saving, "%d\n", pLoc->type);
						fprintf(saving, "%s\n", pLoc->ISBN);
						fprintf(saving, "%d\n", pLoc->time);
						pLoc = pLoc->next;
					}
					fclose(saving);
					printf("The record is saved at C drive.\n\n");
				}
				else
				{
					do
					{
						printf("This action will update and void the current record, are you sure?\n(1=YES and 2=NO): ");
						scanf(" %d", &yesno);
						if (yesno < 1 || yesno > 2)
							printf("Sorry! Input Error! Try Again!\n\n");
						if (yesno == 1)
						{
							saving = fopen("C://record.DAT", "w");
							pLoc = *pFirst;
							while (pLoc != NULL)
							{
								fprintf(saving, "%s\n", pLoc->title);
								fprintf(saving, "%s\n", pLoc->author);
								fprintf(saving, "%lf\n", pLoc->price);
								fprintf(saving, "%d\n", pLoc->quantity);
								fprintf(saving, "%d\n", pLoc->type);
								fprintf(saving, "%s\n", pLoc->ISBN);
								fprintf(saving, "%d\n", pLoc->time);
								pLoc = pLoc->next;
							}
						fclose(saving);
						printf("The record is saved at C drive.\n\n");
						}
						if (yesno == 2)
						{
							printf("Back to main menu\n\n");
							break;
						}
					}while(yesno < 1 || yesno > 2);
				}
				fclose(testing);
			}
		}

		if (choice == 3)
		{
			printf("Back to main menu\n\n");
			break;
		}

	}while (choice < 1 || choice > 3);
}

void update (Node** pFirst)
{
	Node* pLoc;
	int choice, yesno, quantity;
	double price;
	char ISBN[14];

	do
	{
		printf("Do you still want to update?\n(1=YES and 2=NO): ");
		scanf(" %d", &yesno);
		if (yesno < 1 || yesno > 2)
			printf("Sorry! Input Error! Try Again!\n\n");
		if (yesno == 2)
			printf("Back to main menu\n\n");
		if (yesno == 1)
		{
			printf("Please enter the ISBN from the above list: ");
			scanf(" ");
			gets(ISBN);
			pLoc = *pFirst;
			while (pLoc != NULL && strcmp(pLoc->ISBN, ISBN) != 0)
				pLoc = pLoc->next;

			if (pLoc == NULL)
				printf("Sorry! There is no [%s] of ISBN of the book.\n\n", ISBN);

			else if (strcmp(pLoc->ISBN, ISBN) == 0)
			{
				do
				{
					printf("1)Update price\n");
					printf("2)Update quantity\n");
					printf("Your choice: ");
					scanf(" %d", &choice);
					if (choice < 1 || choice > 2)
						printf("Sorry! Input Error! Try Again!\n\n");
					if (choice == 1)
					{
						printf("What is the most updated price of [%s]? ", pLoc->title);
						scanf(" %lf", &price);
						pLoc->price = price;
						printf("The price of [%s] is updated to [$%5.2lf]!\n\n", pLoc->title, price);
					}
					if (choice == 2)
					{
						printf("What is the most updated quantity of [%s]? ", pLoc->title);
						scanf(" %d", &quantity);
						pLoc->quantity = quantity;
						printf("The quantity of [%s] is updated to [%d]!\n\n", pLoc->title, quantity);
					}
				}while (choice < 1 || choice > 2);
			}
		}
	}while (yesno < 1 || yesno > 2);
}

void sort (Node** pFirst, int input)
{
	int AD, sort;
	do
	{
		printf("1) Title\n");
		printf("2) Author\n");
		printf("3) Price\n");
		printf("4) Quantity\n");
		printf("5) ISBN\n");
		printf("6) Type\n");
		printf("7) Adding Time\n");
		printf("8) Back\n");
		printf("Which of the sorting method do you want? ");
		scanf(" %d", &sort);

		if (sort == 8 && input == 7)
		{
			printf("Back to main menu\n\n");
			break;
		}
		if (sort < 1 || sort > 8)
			printf("Sorry! Input Error! Try Again!\n\n");

		if (sort == 1)
		{
			do
			{
				printf("1)Ascending or 2)Descending? ");
				scanf(" %d", &AD);
				if (AD < 1 || AD > 2)
					printf("Sorry! Input Error! Try Again!\n\n");
				if (AD == 1)
				{
					Node *current, *cur;
					for(current = *pFirst; current->next != NULL; current = current->next)
					{
						Node *minimum = current;
						for(cur = current ; cur != NULL; cur = cur->next)
						{
							if(minimum->title[0] > cur->title[0]) 
							{
								minimum = cur;
							}
							if(minimum->title[0] == cur->title[0])
							{
								if(minimum->title[1] > cur->title[1])
									minimum = cur;
							}
							if(minimum->title[0] == cur->title[0] && minimum->title[1] == cur->title[1])
							{
								if(minimum->title[2] > cur->title[2])
									minimum = cur;
							}
						}
						if(minimum != current)
						{
							Node *current_previous, *current_next, *min_previous, *min_next;

							// Initialize them
							current_next = current->next;
							min_previous = minimum->previous;
							min_next = minimum->next;
							current_previous = current->previous;
	
							if(current_previous == NULL)
							{
								// Change the First Node
								*pFirst = minimum;
							}
							if(current->next == minimum)
							{
								// Nodes are Adjacent
								minimum->previous = current_previous;
								minimum->next = current;

								current->previous = minimum;
								current->next = min_next;

								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							else
							{
								minimum->previous = current_previous;
								minimum->next = current_next;

								current->previous = min_previous;
								current->next = min_next;

									if(current_next)
								{
									current_next->previous = minimum;
								}
								if(min_previous)
								{
									min_previous->next = current;
								}
								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							current = minimum;
						}
					}
				}
				
				if (AD == 2)
				{
					Node *current, *cur;
					for(current = *pFirst; current->next != NULL; current = current->next)
					{
						Node *minimum = current;
						for(cur = current ; cur != NULL; cur = cur->next)
						{
							if(minimum->title[0] < cur->title[0]) 
							{
								minimum = cur;
							}
							if(minimum->title[0] == cur->title[0])
							{
								if(minimum->title[1] < cur->title[1])
									minimum = cur;
							}
							if(minimum->title[0] == cur->title[0] && minimum->title[1] == cur->title[1])
							{
								if(minimum->title[2] < cur->title[2])
									minimum = cur;
							}
						}
						if(minimum != current)
						{
							Node *current_previous, *current_next, *min_previous, *min_next;

							// Initialize them
							current_next = current->next;
							min_previous = minimum->previous;
							min_next = minimum->next;
							current_previous = current->previous;
	
							if(current_previous == NULL)
							{
								// Change the First Node
								*pFirst = minimum;
							}
							if(current->next == minimum)
							{
								// Nodes are Adjacent
								minimum->previous = current_previous;
								minimum->next = current;

								current->previous = minimum;
								current->next = min_next;

								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							else
							{
								minimum->previous = current_previous;
								minimum->next = current_next;

								current->previous = min_previous;
								current->next = min_next;

									if(current_next)
								{
									current_next->previous = minimum;
								}
								if(min_previous)
								{
									min_previous->next = current;
								}
								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							current = minimum;
						}
					}
				}
			}while (AD < 1 || AD > 2);
		}

		if (sort == 2)
		{
			do
			{
				printf("1)Ascending or 2)Descending? ");
				scanf(" %d", &AD);
				if (AD < 1 || AD > 2)
					printf("Sorry! Input Error! Try Again!\n\n");
				if (AD == 1)
				{
					Node *current, *cur;
					for(current = *pFirst; current->next != NULL; current = current->next)
					{
						Node *minimum = current;
						for(cur = current ; cur != NULL; cur = cur->next)
						{
							if(minimum->author[0] > cur->author[0]) 
							{
								minimum = cur;
							}
							if(minimum->author[0] == cur->author[0])
							{
								if(minimum->author[1] > cur->author[1])
									minimum = cur;
							}
							if(minimum->author[0] == cur->author[0] && minimum->author[1] == cur->author[1])
							{
								if(minimum->author[2] > cur->author[2])
									minimum = cur;
							}
						}
						if(minimum != current)
						{
							Node *current_previous, *current_next, *min_previous, *min_next;

							// Initialize them
							current_next = current->next;
							min_previous = minimum->previous;
							min_next = minimum->next;
							current_previous = current->previous;
	
							if(current_previous == NULL)
							{
								// Change the First Node
								*pFirst = minimum;
							}
							if(current->next == minimum)
							{
								// Nodes are Adjacent
								minimum->previous = current_previous;
								minimum->next = current;

								current->previous = minimum;
								current->next = min_next;

								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							else
							{
								minimum->previous = current_previous;
								minimum->next = current_next;

								current->previous = min_previous;
								current->next = min_next;

									if(current_next)
								{
									current_next->previous = minimum;
								}
								if(min_previous)
								{
									min_previous->next = current;
								}
								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							current = minimum;
						}
					}
				}
				
				if (AD == 2)
				{
					Node *current, *cur;
					for(current = *pFirst; current->next != NULL; current = current->next)
					{
						Node *minimum = current;
						for(cur = current ; cur != NULL; cur = cur->next)
						{
							if(minimum->author[0] < cur->author[0]) 
							{
								minimum = cur;
							}
							if(minimum->author[0] == cur->author[0])
							{
								if(minimum->author[1] < cur->author[1])
									minimum = cur;
							}
							if(minimum->author[0] == cur->author[0] && minimum->author[1] == cur->author[1])
							{
								if(minimum->author[2] < cur->author[2])
									minimum = cur;
							}
						}
						if(minimum != current)
						{
							Node *current_previous, *current_next, *min_previous, *min_next;

							// Initialize them
							current_next = current->next;
							min_previous = minimum->previous;
							min_next = minimum->next;
							current_previous = current->previous;
	
							if(current_previous == NULL)
							{
								// Change the First Node
								*pFirst = minimum;
							}
							if(current->next == minimum)
							{
								// Nodes are Adjacent
								minimum->previous = current_previous;
								minimum->next = current;

								current->previous = minimum;
								current->next = min_next;

								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							else
							{
								minimum->previous = current_previous;
								minimum->next = current_next;

								current->previous = min_previous;
								current->next = min_next;

									if(current_next)
								{
									current_next->previous = minimum;
								}
								if(min_previous)
								{
									min_previous->next = current;
								}
								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							current = minimum;
						}
					}
				}
			}while (AD < 1 || AD > 2);
		}

		if (sort == 3)
		{
			do
			{
				printf("1)Ascending or 2)Descending? ");
				scanf(" %d", &AD);
				if (AD < 1 || AD > 2)
					printf("Sorry! Input Error! Try Again!\n\n");
				if (AD == 1)
				{
					Node *current, *cur;
					for(current = *pFirst; current->next != NULL; current = current->next)
					{
						Node *minimum = current;
						for(cur = current ; cur != NULL; cur = cur->next)
						{
							if(minimum->price > cur->price) 
							{
								minimum = cur;
							}
							if(minimum->price == cur->price)
							{
								if(minimum->title[0] > cur->title[0])
									minimum = cur;
							}
							if(minimum->price == cur->price && minimum->title[0] == cur->title[0])
							{
								if(minimum->title[1] > cur->title[1])
									minimum = cur;
							}
							if(minimum->price == cur->price && minimum->title[0] == cur->title[0] && minimum->title[1] == cur->title[1])
							{
								if(minimum->title[2] > cur->title[2])
									minimum = cur;
							}
						}
						if(minimum != current)
						{
							Node *current_previous, *current_next, *min_previous, *min_next;

							// Initialize them
							current_next = current->next;
							min_previous = minimum->previous;
							min_next = minimum->next;
							current_previous = current->previous;
	
							if(current_previous == NULL)
							{
								// Change the First Node
								*pFirst = minimum;
							}
							if(current->next == minimum)
							{
								// Nodes are Adjacent
								minimum->previous = current_previous;
								minimum->next = current;

								current->previous = minimum;
								current->next = min_next;

								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							else
							{
								minimum->previous = current_previous;
								minimum->next = current_next;

								current->previous = min_previous;
								current->next = min_next;

									if(current_next)
								{
									current_next->previous = minimum;
								}
								if(min_previous)
								{
									min_previous->next = current;
								}
								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							current = minimum;
						}
					}
				}
				
				if (AD == 2)
				{
					Node *current, *cur;
					for(current = *pFirst; current->next != NULL; current = current->next)
					{
						Node *minimum = current;
						for(cur = current ; cur != NULL; cur = cur->next)
						{
							if(minimum->price < cur->price) 
							{
								minimum = cur;
							}
							if(minimum->price == cur->price)
							{
								if(minimum->title[0] > cur->title[0])
									minimum = cur;
							}
							if(minimum->price == cur->price && minimum->title[0] == cur->title[0])
							{
								if(minimum->title[1] > cur->title[1])
									minimum = cur;
							}
							if(minimum->price == cur->price && minimum->title[0] == cur->title[0] && minimum->title[1] == cur->title[1])
							{
								if(minimum->title[2] > cur->title[2])
									minimum = cur;
							}
						}
						if(minimum != current)
						{
							Node *current_previous, *current_next, *min_previous, *min_next;

							// Initialize them
							current_next = current->next;
							min_previous = minimum->previous;
							min_next = minimum->next;
							current_previous = current->previous;
	
							if(current_previous == NULL)
							{
								// Change the First Node
								*pFirst = minimum;
							}
							if(current->next == minimum)
							{
								// Nodes are Adjacent
								minimum->previous = current_previous;
								minimum->next = current;

								current->previous = minimum;
								current->next = min_next;

								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							else
							{
								minimum->previous = current_previous;
								minimum->next = current_next;

								current->previous = min_previous;
								current->next = min_next;

									if(current_next)
								{
									current_next->previous = minimum;
								}
								if(min_previous)
								{
									min_previous->next = current;
								}
								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							current = minimum;
						}
					}
				}
			}while (AD < 1 || AD > 2);
		}

		if (sort == 4)
		{
			do
			{
				printf("1)Ascending or 2)Descending? ");
				scanf(" %d", &AD);
				if (AD < 1 || AD > 2)
					printf("Sorry! Input Error! Try Again!\n\n");
				if (AD == 1)
				{
					Node *current, *cur;
					for(current = *pFirst; current->next != NULL; current = current->next)
					{
						Node *minimum = current;
						for(cur = current ; cur != NULL; cur = cur->next)
						{
							if(minimum->quantity > cur->quantity) 
							{
								minimum = cur;
							}
							if(minimum->quantity == cur->quantity)
							{
								if(minimum->title[0] > cur->title[0])
									minimum = cur;
							}
							if(minimum->quantity == cur->quantity && minimum->title[0] == cur->title[0])
							{
								if(minimum->title[1] > cur->title[1])
									minimum = cur;
							}
							if(minimum->quantity == cur->quantity && minimum->title[0] == cur->title[0] && minimum->title[1] == cur->title[1])
							{
								if(minimum->title[2] > cur->title[2])
									minimum = cur;
							}
						}
						if(minimum != current)
						{
							Node *current_previous, *current_next, *min_previous, *min_next;

							// Initialize them
							current_next = current->next;
							min_previous = minimum->previous;
							min_next = minimum->next;
							current_previous = current->previous;
	
							if(current_previous == NULL)
							{
								// Change the First Node
								*pFirst = minimum;
							}
							if(current->next == minimum)
							{
								// Nodes are Adjacent
								minimum->previous = current_previous;
								minimum->next = current;

								current->previous = minimum;
								current->next = min_next;

								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							else
							{
								minimum->previous = current_previous;
								minimum->next = current_next;

								current->previous = min_previous;
								current->next = min_next;

									if(current_next)
								{
									current_next->previous = minimum;
								}
								if(min_previous)
								{
									min_previous->next = current;
								}
								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							current = minimum;
						}
					}
				}
				
				if (AD == 2)
				{
					Node *current, *cur;
					for(current = *pFirst; current->next != NULL; current = current->next)
					{
						Node *minimum = current;
						for(cur = current ; cur != NULL; cur = cur->next)
						{
							if(minimum->quantity < cur->quantity) 
							{
								minimum = cur;
							}
							if(minimum->quantity == cur->quantity)
							{
								if(minimum->title[0] > cur->title[0])
									minimum = cur;
							}
							if(minimum->quantity == cur->quantity && minimum->title[0] == cur->title[0])
							{
								if(minimum->title[1] > cur->title[1])
									minimum = cur;
							}
							if(minimum->quantity == cur->quantity && minimum->title[0] == cur->title[0] && minimum->title[1] == cur->title[1])
							{
								if(minimum->title[2] > cur->title[2])
									minimum = cur;
							}
						}
						if(minimum != current)
						{
							Node *current_previous, *current_next, *min_previous, *min_next;

							// Initialize them
							current_next = current->next;
							min_previous = minimum->previous;
							min_next = minimum->next;
							current_previous = current->previous;
	
							if(current_previous == NULL)
							{
								// Change the First Node
								*pFirst = minimum;
							}
							if(current->next == minimum)
							{
								// Nodes are Adjacent
								minimum->previous = current_previous;
								minimum->next = current;

								current->previous = minimum;
								current->next = min_next;

								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							else
							{
								minimum->previous = current_previous;
								minimum->next = current_next;

								current->previous = min_previous;
								current->next = min_next;

									if(current_next)
								{
									current_next->previous = minimum;
								}
								if(min_previous)
								{
									min_previous->next = current;
								}
								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							current = minimum;
						}
					}
				}
			}while (AD < 1 || AD > 2);
		}

		if (sort == 5)
		{
			do
			{
				printf("1)Ascending or 2)Descending? ");
				scanf(" %d", &AD);
				if (AD < 1 || AD > 2)
					printf("Sorry! Input Error! Try Again!\n\n");
				if (AD == 1)
				{
					Node *current, *cur;
					for(current = *pFirst; current->next != NULL; current = current->next)
					{
						Node *minimum = current;
						for(cur = current ; cur != NULL; cur = cur->next)
						{
							if(minimum->ISBN[0] > cur->ISBN[0]) 
							{
								minimum = cur;
							}
							if(minimum->ISBN[0] == cur->ISBN[0])
							{
								if(minimum->ISBN[1] > cur->ISBN[1])
									minimum = cur;
							}
							if(minimum->ISBN[0] == cur->ISBN[0] && minimum->ISBN[1] == cur->ISBN[1])
							{
								if(minimum->ISBN[2] > cur->ISBN[2])
									minimum = cur;
							}
						}
						if(minimum != current)
						{
							Node *current_previous, *current_next, *min_previous, *min_next;

							// Initialize them
							current_next = current->next;
							min_previous = minimum->previous;
							min_next = minimum->next;
							current_previous = current->previous;
	
							if(current_previous == NULL)
							{
								// Change the First Node
								*pFirst = minimum;
							}
							if(current->next == minimum)
							{
								// Nodes are Adjacent
								minimum->previous = current_previous;
								minimum->next = current;

								current->previous = minimum;
								current->next = min_next;

								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							else
							{
								minimum->previous = current_previous;
								minimum->next = current_next;

								current->previous = min_previous;
								current->next = min_next;

									if(current_next)
								{
									current_next->previous = minimum;
								}
								if(min_previous)
								{
									min_previous->next = current;
								}
								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							current = minimum;
						}
					}
				}
				
				if (AD == 2)
				{
					Node *current, *cur;
					for(current = *pFirst; current->next != NULL; current = current->next)
					{
						Node *minimum = current;
						for(cur = current ; cur != NULL; cur = cur->next)
						{
							if(minimum->ISBN[0] < cur->ISBN[0]) 
							{
								minimum = cur;
							}
							if(minimum->ISBN[0] == cur->ISBN[0])
							{
								if(minimum->ISBN[1] < cur->ISBN[1])
									minimum = cur;
							}
							if(minimum->ISBN[0] == cur->ISBN[0] && minimum->ISBN[1] == cur->ISBN[1])
							{
								if(minimum->ISBN[2] < cur->ISBN[2])
									minimum = cur;
							}
						}
						if(minimum != current)
						{
							Node *current_previous, *current_next, *min_previous, *min_next;

							// Initialize them
							current_next = current->next;
							min_previous = minimum->previous;
							min_next = minimum->next;
							current_previous = current->previous;
	
							if(current_previous == NULL)
							{
								// Change the First Node
								*pFirst = minimum;
							}
							if(current->next == minimum)
							{
								// Nodes are Adjacent
								minimum->previous = current_previous;
								minimum->next = current;

								current->previous = minimum;
								current->next = min_next;

								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							else
							{
								minimum->previous = current_previous;
								minimum->next = current_next;

								current->previous = min_previous;
								current->next = min_next;

									if(current_next)
								{
									current_next->previous = minimum;
								}
								if(min_previous)
								{
									min_previous->next = current;
								}
								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							current = minimum;
						}
					}
				}
			}while (AD < 1 || AD > 2);
		}

		if (sort == 6)
		{
			do
			{
				printf("1)Ascending or 2)Descending? ");
				scanf(" %d", &AD);
				if (AD < 1 || AD > 2)
					printf("Sorry! Input Error! Try Again!\n\n");
				if (AD == 1)
				{
					Node *current, *cur;
					for(current = *pFirst; current->next != NULL; current = current->next)
					{
						Node *minimum = current;
						for(cur = current ; cur != NULL; cur = cur->next)
						{
							if(minimum->type > cur->type) 
							{
								minimum = cur;
							}
							if(minimum->type == cur->type)
							{
								if(minimum->title[0] > cur->title[0])
									minimum = cur;
							}
							if(minimum->type == cur->type && minimum->title[0] == cur->title[0])
							{
								if(minimum->title[1] > cur->title[1])
									minimum = cur;
							}
							if(minimum->type == cur->type && minimum->title[0] == cur->title[0] && minimum->title[1] == cur->title[1])
							{
								if(minimum->title[2] > cur->title[2])
									minimum = cur;
							}
						}
						if(minimum != current)
						{
							Node *current_previous, *current_next, *min_previous, *min_next;

							// Initialize them
							current_next = current->next;
							min_previous = minimum->previous;
							min_next = minimum->next;
							current_previous = current->previous;
	
							if(current_previous == NULL)
							{
								// Change the First Node
								*pFirst = minimum;
							}
							if(current->next == minimum)
							{
								// Nodes are Adjacent
								minimum->previous = current_previous;
								minimum->next = current;

								current->previous = minimum;
								current->next = min_next;

								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							else
							{
								minimum->previous = current_previous;
								minimum->next = current_next;

								current->previous = min_previous;
								current->next = min_next;

									if(current_next)
								{
									current_next->previous = minimum;
								}
								if(min_previous)
								{
									min_previous->next = current;
								}
								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							current = minimum;
						}
					}
				}
				
				if (AD == 2)
				{
					Node *current, *cur;
					for(current = *pFirst; current->next != NULL; current = current->next)
					{
						Node *minimum = current;
						for(cur = current ; cur != NULL; cur = cur->next)
						{
							if(minimum->type < cur->type) 
							{
								minimum = cur;
							}
							if(minimum->type == cur->type)
							{
								if(minimum->title[0] > cur->title[0])
									minimum = cur;
							}
							if(minimum->type == cur->type && minimum->title[0] == cur->title[0])
							{
								if(minimum->title[1] > cur->title[1])
									minimum = cur;
							}
							if(minimum->type == cur->type && minimum->title[0] == cur->title[0] && minimum->title[1] == cur->title[1])
							{
								if(minimum->title[2] > cur->title[2])
									minimum = cur;
							}
						}
						if(minimum != current)
						{
							Node *current_previous, *current_next, *min_previous, *min_next;

							// Initialize them
							current_next = current->next;
							min_previous = minimum->previous;
							min_next = minimum->next;
							current_previous = current->previous;
	
							if(current_previous == NULL)
							{
								// Change the First Node
								*pFirst = minimum;
							}
							if(current->next == minimum)
							{
								// Nodes are Adjacent
								minimum->previous = current_previous;
								minimum->next = current;

								current->previous = minimum;
								current->next = min_next;

								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							else
							{
								minimum->previous = current_previous;
								minimum->next = current_next;

								current->previous = min_previous;
								current->next = min_next;

									if(current_next)
								{
									current_next->previous = minimum;
								}
								if(min_previous)
								{
									min_previous->next = current;
								}
								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							current = minimum;
						}
					}
				}
			}while (AD < 1 || AD > 2);
		}

		if (sort == 7)
		{
			do
			{
				printf("1)Ascending or 2)Descending? ");
				scanf(" %d", &AD);
				if (AD < 1 || AD > 2)
					printf("Sorry! Input Error! Try Again!\n\n");
				if (AD == 1)
				{
					Node *current, *cur;
					for(current = *pFirst; current->next != NULL; current = current->next)
					{
						Node *minimum = current;
						for(cur = current ; cur != NULL; cur = cur->next)
						{
							if(minimum->time > cur->time) 
							{
								minimum = cur;
							}
						}
						if(minimum != current)
						{
							Node *current_previous, *current_next, *min_previous, *min_next;

							// Initialize them
							current_next = current->next;
							min_previous = minimum->previous;
							min_next = minimum->next;
							current_previous = current->previous;
	
							if(current_previous == NULL)
							{
								// Change the First Node
								*pFirst = minimum;
							}
							if(current->next == minimum)
							{
								// Nodes are Adjacent
								minimum->previous = current_previous;
								minimum->next = current;

								current->previous = minimum;
								current->next = min_next;

								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							else
							{
								minimum->previous = current_previous;
								minimum->next = current_next;

								current->previous = min_previous;
								current->next = min_next;

									if(current_next)
								{
									current_next->previous = minimum;
								}
								if(min_previous)
								{
									min_previous->next = current;
								}
								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							current = minimum;
						}
					}
				}
				
				if (AD == 2)
				{
					Node *current, *cur;
					for(current = *pFirst; current->next != NULL; current = current->next)
					{
						Node *minimum = current;
						for(cur = current ; cur != NULL; cur = cur->next)
						{
							if(minimum->time < cur->time) 
							{
								minimum = cur;
							}
						}
						if(minimum != current)
						{
							Node *current_previous, *current_next, *min_previous, *min_next;

							// Initialize them
							current_next = current->next;
							min_previous = minimum->previous;
							min_next = minimum->next;
							current_previous = current->previous;
	
							if(current_previous == NULL)
							{
								// Change the First Node
								*pFirst = minimum;
							}
							if(current->next == minimum)
							{
								// Nodes are Adjacent
								minimum->previous = current_previous;
								minimum->next = current;

								current->previous = minimum;
								current->next = min_next;

								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							else
							{
								minimum->previous = current_previous;
								minimum->next = current_next;

								current->previous = min_previous;
								current->next = min_next;

									if(current_next)
								{
									current_next->previous = minimum;
								}
								if(min_previous)
								{
									min_previous->next = current;
								}
								if(min_next)
								{
									min_next->previous = current;
								}
								if(current_previous)
								{
									current_previous->next = minimum;
								}
							}
							current = minimum;
						}
					}
				}
			}while (AD < 1 || AD > 2);
		}
	}while (sort < 1 || sort > 8);
	if (sort < 8 && sort > 0)
	{
		printf("\nThe book list is sorted by ");
		if (sort == 1)
			printf("title ");
		if (sort == 2)
			printf("author ");
		if (sort == 3)
			printf("price ");
		if (sort == 4)
			printf("quantity ");
		if (sort == 5)
			printf("ISBN ");		
		if (sort == 6)
			printf("type ");
		if (sort == 7)
			printf("adding time ");
		if (AD == 1)
			printf("in ascending order.\n");
		if (AD == 2)
			printf("in descending order.\n");
		if (input == 7)
			printf("Please use function 3 in main menu to check it.\n\n");
	}
}
