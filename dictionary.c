/****************************************************************************
 * dictionary.c
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define word_length 47
#define hash_size 27

#include "dictionary.h"

//establishes my node type/struct type
typedef struct node{
      char word[word_length];
      int order;
      struct node *next;
      }node;
      
node *myarray[hash_size];
//recursive function to be called in "unload"
void delete(node *ptr)
{   

    if(ptr->next == NULL)
    {
         
        free(ptr);
    }
    else
    {
        delete(ptr->next);
        free(ptr);
     }
    
}




unsigned int counter = -1;

int the_word_order = 0;
/*
 * Returns true if word is in dictionary else false.
 */

bool
check(const char *word, int right_word_order)
{   //assigns values of const char to an array that can be 
    //modified.
    char lowercase[word_length];
    
    for(int i = 0; i < strlen(word); i++)
    {
        lowercase[i] = word[i];    
    }
    /*makes each letter lowercase */
    for(int i = 0; i < strlen(word); i++)
    {

        if (lowercase[i] <= 90 && lowercase[i] >= 65)
        {
            lowercase[i] = (lowercase[i] - 'A' + 'a');
        }      
    }
   
    lowercase[strlen(word)] = '\0';
    /*very basic hash function used */
    int n = (lowercase[0] % hash_size); 
    /*malloc memory for pointers */
    node *findptr; /*= malloc(sizeof(node));*/
    findptr = myarray[n];
    while(findptr!=NULL)
    {   //check to see if the word is spelled property
        //also check to see if the order is correct
 
        if(strcmp(lowercase,findptr->word) == 0 && (findptr->order == right_word_order))
        {
            
            return true;
            
        }
        //move on to each element in the linked list 
        //if the two strings are not identical
        else
        {
            findptr = findptr->next;
        }
    }

    return false;
}


/*
 * Loads dictionary into memory.  Returns true if successful else false.
 */

bool
load(const char *dictionary)
{
    //loads dictionary
    FILE *dict = fopen(dictionary,"r");
    //checks to see if the pointer is NULL
    if(dict == NULL) 
    {
        printf("Could not open the file\n");
        return false;
    
    } 
    //assigns values to hash table
    for(int i = 0; i < hash_size; i++)
    {
        myarray[i] = NULL; 
     }
     //inserts dictionary words into hash table
     while(!feof(dict))
     {        
        node *newnodeptr = malloc(sizeof(node));
        fscanf(dict, "%s", newnodeptr->word); 
        newnodeptr->order = the_word_order;
        int n = (newnodeptr->word[0] % hash_size); 
       //assigns words to location based on the items in hash
       //table         
        if(myarray[n]==NULL)
        {
            myarray[n] = newnodeptr;
            newnodeptr->next = NULL;
            counter++;
        }
        else
        {
            newnodeptr->next = myarray[n];
            myarray[n] = newnodeptr;
            //counter variable is incremented.
            counter++;
        }
        the_word_order++;

     }
     
     fclose(dict);
     return true;
 
}


/*
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */

unsigned int
size(void)
{
    //returns counter variable from load
    return counter;
}


/*
 * Unloads dictionary from memory.  Returns true if successful else false.
 */

bool
unload(void)
{
   
    for(int i = 0; i < hash_size; i++)
    {   //checks if pointer is NULL
        if(myarray[i] != NULL)
       {
            delete(myarray[i]);                
        }    
        
    }    
    

    return true;
}

