/**
 * @file tree.c
 * @author Abdullah Saad | 1043850 | asaad02@uoguelph.ca
 * @date october 20th 2020
 * @brief File containing the function prototypes of a  Tree 
 **/

/* This structure represent the node in the tree */
struct Node
{
    void *data;         // pointer to data stored at the node
    struct Node *lt;    //lt pointer less than the current node 
    struct Node *gte;   // gte pointer to grater or equal to corrent node
};

/* structure to measure the performance of the code and Algorithms in tree.*/
struct Performance
{
    unsigned int reads;     /*  how many reads operations    */
    unsigned int writes;    /*  how many writes operations   */
    unsigned int mallocs;   /*  haw many maloocs operation   */
    unsigned int frees;     /*  how many frees operations    */
};

/* this function allocate memory for the performance struct and return the address of the the structure */
struct Performance *newPerformance();

/* This function to add a node to a pointer */
void attachNode( struct Performance *performance, struct Node **node_ptr,void *src, unsigned int width );

/*This function should return the value returned by the function pointed to by thecomparfunction pointe */
int comparNode( struct Performance *performance, struct Node**node_ptr, int (*compar)(const void *, const void *),void *target);

/* Determine the next node in the tree to visit */
struct Node**next( struct Performance *performance, struct Node **node_ptr, int direction);

/* Copy data from a node in the treeinto dest */
void readNode( struct Performance *performance, struct Node **node_ptr, void *dest, unsigned int width );

/* Remove an item from a tree consisting of only one node */
void detachNode(struct Performance *performance, struct Node **node_ptr);

/* Check if the pointer pointed to by node_ptr is NULL */
int isEmpty( struct Performance *performance, struct Node **node_ptr );


/* Add an item to the tree at the appropriate spot */
void addItem( struct Performance *performance, struct Node **node_ptr,int (*compar)(const void *, const void *),void *src, unsigned int width );

/* This function willremove all theitems from the tree */
void freeTree( struct Performance *performance, struct Node **node_ptr);

/* This function will search for an item in the tree */
int searchItem( struct Performance *performance, struct Node **node_ptr,int (*compar)(const void *, const void *),void *target, unsigned int width );

