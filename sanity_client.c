#include <stdio.h>
#include "header.h"
int main()
{
    allocate(100);
    char* a=mymalloc(32*sizeof(char));
    display_mem_map();
    printf("\n");    
    char* b=mymalloc(10*sizeof(char));
    display_mem_map();
    printf("\n");   
    char* c=mymalloc(30*sizeof(char));
    display_mem_map();
    printf("\n");   
    myfree(a);
    display_mem_map();
    printf("\n");  
    myfree(c);
    display_mem_map();
    printf("\n"); 
    char* d=mymalloc(8*sizeof(char));
    display_mem_map();
    printf("\n");   
}
