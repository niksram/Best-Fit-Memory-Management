//S NIKHIL RAM
//PES1201801972

#include"header.h"
#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#pragma pack(push,1)		// I have used this inorder to remove the packing use by the struct book for the variable bool.

char* p=NULL;
int size=0;

typedef struct Book
{
	char* next;			//It points to the next location location in the array 'p' where  the next block starts (next book structure)
	int cap;			//shows the usable capacity of the current block
	bool booli;			//booli is the flag variable which indicates whether the block is allocated or free
}Book;

void allocate(int n)
{
	if(n>sizeof(Book))	//This condition prevents allocation of memory where no book_structure or only 1 book_structure -
	{					//- alone can be allocated.
		p=(char*)malloc(n*sizeof(char));
		Book* book=(Book*)(p);
		book->next=NULL;
		book->booli=0;
		book->cap=n-sizeof(Book);
		size=n*sizeof(char);
	}
	else
	{
		printf("memory insufficient to accomodate a book log along with free usable space\n");
		exit(0);
	}
}

void* mymalloc(int sz)
{
	int min=INT_MAX;
	char* minpoint=NULL;
	char* x=p;
	Book* book;
	int flag=0,decider=1;
	while(x) //This loop is used to find the minimum chunk in the page available which can accomodate the users necessary space
	{
		book=(Book*)(x);
		if(!book->booli && book->cap<min && book->cap >=sz )
		{
				min=book->cap;
				minpoint=x;	//minpoint stores the pointer to the suitable block which can be utilised
				flag=1;		//flag is made 1 if the chunk is available for usage
				decider=1;	//decider is 1 if the buffer is too small to make it a free space. Hence its given as buffer to the user -
							//- this is when the remaining free space cannot accomodate a book_structure or only 1 book_structure alone.
		}
		x=book->next;
	}
	if( (int)(min - sizeof(Book)) > (int)(sz)) // i have typecasted 'int' here as it was passing through the if eventhough the condition was wrong.
	{
		decider=0;		//decider is 0 when there is enough space left after allocation for having an independent free memory block
	}
	if(flag)
	{
		book=(Book*)(minpoint);
		book->booli=1;
		if(!decider)	//if decider is 0, then the remaining space in the block after allocation can be made into a free block -
		{				//- with its own book_structure
			Book* new=(Book*)(minpoint+sz+sizeof(Book)); //the book new
			Book* nbook=NULL;
			new->booli=0;
			new->next=book->next;
			book->next=minpoint+sz+sizeof(Book);
			new->cap=book->cap-sz-sizeof(Book);
			book->cap=sz;
		}
		char* ptr=minpoint+sizeof(Book);
		return ptr;
	}
	else
		return NULL;
}

void myfree(void *b)
{
	char* x=p;
	Book* pbook=NULL;	//previous book_structure of the current block
	Book* book=NULL;	//the current blocks book_structure
	Book* nbook=NULL;	//the next book_structure of the current block
	int flag=0;
	while(x && !flag)	//This loop is to ensure whether the given pointer is the head pointer of the allocated blocks.
	{
		pbook=book;
		book=(Book*)(x);
		if(x+sizeof(Book)==b && book->booli)
			flag=1;
		x=book->next;
	}
	if(!flag)	//If the entered pointer is invalid, then it exits (if b is not NULL)
	{
		if(!b)
			return; //If pointer is NULL, then it just ignores
		printf("pointer to the block is invalid\n");
		exit(0);
	}
	book->booli=0;
	if(book->next)
		nbook=(Book*)(book->next);
	if(pbook && !pbook->booli)		//if the previous block is free, then its merged with the current
	{
		pbook->next=book->next;
		pbook->cap+=(sizeof(Book)+book->cap);
		book=pbook;
	}
	if(nbook && !nbook->booli)		//if the next block is free, then its merged with the current
	{
		book->next=nbook->next;
		book->cap+=(nbook->cap+sizeof(Book));
	}
}

void print_book()
{
	printf("size of the book is %d bytes\n",sizeof(Book));	//prints the size of book_structure in bytes
}

void display_mem_map()
{
	char* x=p;
	Book* book;
	while(x)
	{
		book=(Book*)(x);
		printf("%d\t%d\tBook\n",x-p,sizeof(Book)); 						//prints start point and the size of the book
		if(book->booli)													//prints start point and the size of the block along with its status
			printf("%d\t%d\tAllocated\n",x-p+sizeof(Book),book->cap);
		else
			printf("%d\t%d\tFree\n",x-p+sizeof(Book),book->cap);
		x=book->next;
	}
}