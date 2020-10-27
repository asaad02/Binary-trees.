/**
 * @file tree.c
 * @author Abdullah Saad | 1043850 | asaad02@uoguelph.ca
 * @date october 20th 2020
 * @brief File containing the function definitions and implementations of a Tree 
 **/

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include <string.h>

/* This function allocate memory for performance structure and set function elements to zero */
struct Performance *newPerformance()
{
    // allocate memory for a performance struct 

    struct Performance *newPerformance = (struct Performance *) malloc( sizeof (struct Performance));

    //print an error message to the standard error stream and exit if the malloc function fails.
    if(newPerformance == NULL){
        fprintf(stderr,"%s","Memory allocation for structure performance has failed\n");
        exit(0);
    }
    
    // set zero to reads, writes, malloc , free 
    newPerformance -> reads = 0;
    newPerformance -> writes = 0;
    newPerformance -> mallocs = 0;
    newPerformance -> frees = 0;

    // return the address of the new function.
    return newPerformance;
}

/* This function to add a node to a pointer */
void attachNode( struct Performance*performance, struct Node**node_ptr,void *src, unsigned int width )
{
    /* malloc a new struct Node structure */
    struct Node *newNode = (struct Node *) malloc( sizeof ( struct Node ));

     //print an error message to the standard error stream and exit if the malloc function fails.
    if(newNode == NULL){
        fprintf(stderr,"%s","Memory allocation for newNode structure has failed\n");
        exit(0);
    }

    /* allocate width bytes of data and stored in data address*/
    newNode -> data = malloc(width);



    //print an error message to the standard error stream and exit if the malloc function fails.
    if(newNode -> data == NULL){
        fprintf(stderr,"%s","Memory allocation for data in the newNode has failed\n");
        exit(0);
    }

    //copy width bytes of data from the parameter src to the address data in the new Node structure
    memcpy( newNode-> data, src  , width );



    /* set the lower and higher pointers in the structure to Null */
    newNode -> lt = NULL;
    newNode -> gte = NULL;

    // store the address of structure in the head pointer
    *node_ptr= newNode;

    // increment mallocs at performance struct 
    performance -> mallocs++;


    // increment writes at performance struct 
    performance -> writes++;
}

/*This function should return the value returned by the function pointed to by thecomparfunction pointe */
int comparNode( struct Performance *performance, struct Node**node_ptr, int (*compar)(const void *, const void *),void *target)
{
    //comparsion between two source of data 
    int i = compar(target,(*node_ptr)->data);
            
    
    // increment reads at performance struct 
    performance -> reads++;
    return i;
}

/* Determine the next node in the tree to visit */
struct Node**next( struct Performance *performance, struct Node**node_ptr, int direction)
{
    /* If the tree is empty it should print an error message to the standard error stream and exit*/
    if(*node_ptr == NULL){
        fprintf(stderr,"%s","The tree is Empty in next  \n");
        exit(0);
    }

    if ( direction < 0 ){ // if direction less than zero return the address of the lt pointer 


        //increment reads at performance struct 
        performance -> reads++;

        // return the address of the lt node pointer
        return &((*node_ptr)->lt);
        
    }
     if( direction >= 0 ){

         // increment reads at performance struct 
        performance -> reads++;
        
         // return the address of the gte node pointer
        return &((*node_ptr)->gte) ;
    }

    return NULL;
}


/* Copy data from a node in the treeinto dest */
void readNode( struct Performance *performance, struct Node **node_ptr, void *dest, unsigned int width )
{
    /* If the tree is empty it should print an error message to the standard error stream and exit*/
    if(*node_ptr == NULL){
        fprintf(stderr,"%s","The tree is Empty in readNode \n");
        exit(0);
    }

    //copy width bytes of data from the parameter newNode data to dest
    memcpy( dest, (*node_ptr)-> data  , width );

    //increment reads
    performance ->reads++;
}


/* Remove an item from a tree consisting of only one node */
void detachNode(struct Performance *performance, struct Node **node_ptr)
{
    /* If the tree is empty it should print an error message to the standard error stream and exit*/
    if(*node_ptr == NULL){
        fprintf(stderr,"%s","The tree is  Empty in the detachNode function \n");
        exit(0);
    }

    // if statement if to test if lt nad gta pointer is NULL
    if(((*node_ptr)->lt == NULL) && ((*node_ptr)->gte == NULL)){
    
        //increment performance by 1
        performance ->frees++;
        //free data 
        free((*node_ptr)->data);
        //free structure 
        free(*node_ptr);
        // update the pointer to be NULL
        *node_ptr = NULL;
    }
    // frees should be increment 
    //performance ->frees++;


}


/* Check if the pointer pointed to by node_ptr is NULL */
int isEmpty( struct Performance *performance, struct Node** node_ptr )
{
     // if statement  if the head pointer is empty return 1
    if(*node_ptr == NULL){
        
        return (1);
    }

    // if not empty return 0 
    return (0);

}


/* Add an item to the tree at the appropriate spot */
void addItem( struct Performance *performance, struct Node **node_ptr,int (*compar)(const void *, const void *),void *src, unsigned int width )
{
    struct Node ** curruntNode = node_ptr; //create temporory pointer to hold the node_ptr

    // while loop calling the next function until isempty return true 
    while (isEmpty(performance,curruntNode) != 1)
    {


        int i = comparNode( performance, curruntNode,  compar,src);
        // store next pointer inside the current node
        curruntNode = next(performance,curruntNode,i);
    }

    // Add the item at the end of the tree 
    attachNode(performance,curruntNode,src ,width); 

    
}

/* This function willremove all theitems from the tree */
void freeTree( struct Performance *performance, struct Node **node_ptr)
{
    struct Node **curruntNode1 = node_ptr;//create temporory pointer to hold the node_ptr
    
    // check if the pointer is null
    if(*curruntNode1 == NULL){
        return;
    }
    
    // if statement
    if(curruntNode1 && *curruntNode1){
        struct Node ** left = next(performance,curruntNode1,+1);
        struct Node ** right = next(performance,curruntNode1,-1);
        freeTree(performance,&(*left));
        freeTree(performance,&(*right));
        detachNode(performance, &(*curruntNode1));
    }

    return;


}


/* This function will search for an item in the tree */
int searchItem( struct Performance *performance, struct Node **node_ptr,int (*compar)(const void *, const void *),void *target, unsigned int width ){

    
    struct Node ** curruntNode = node_ptr; //create temporory pointer to hold the node_ptr

    
    
    while (isEmpty(performance,curruntNode) != 1)
    {

    if(compar((*curruntNode)->data,target)==0){

    readNode( performance, curruntNode, target, width );

    return (1);
    }
    int b = comparNode( performance, curruntNode, compar,target);
    curruntNode = next( performance, curruntNode, b);


    }

    return (0) ;




}

