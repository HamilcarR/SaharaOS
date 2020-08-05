#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <stdint.h>
#include <stdarg.h> 
#include <stddef.h>
#include "heap.h"
/*implements various utility functions and data structures*/


//simple linked list and double 
/**********************************************************/

typedef struct list_node_t list_node_t; 
typedef struct linked_list_t linked_list_t; 




struct list_node_t{
	void* data ; 
	list_node_t * next; 
	list_node_t * prev; 

};



struct linked_list_t{
	list_node_t* begin ; 
	size_t size; 
	list_node_t* end ; 

};





linked_list_t* linked_list_create(); 
void linked_list_free(linked_list_t* list);
void linked_list_free_node(list_node_t* node); 
list_node_t* linked_list_get(linked_list_t* , size_t i) ; 
list_node_t* linked_list_add_end(linked_list_t* list , list_node_t* node); 
list_node_t* linked_list_add_begin(linked_list_t* list , list_node_t* node); 
list_node_t* linked_list_create_node(void* data) ; 
list_node_t* linked_list_pop_node(linked_list_t* list , size_t i); 


/**********************************************************/

/* sorted tree */

typedef struct binary_tree_t binary_tree_t ; 
typedef struct tree_node_t tree_node_t ; 

struct tree_node_t{
	void* data ; 
	tree_node_t * right; 
	tree_node_t * left ; 
}; 


struct binary_tree_t{
	tree_node_t * root ; 
	size_t size ; 	
}; 





binary_tree_t* binary_tree_create() ; 
tree_node_t* binary_tree_add(binary_tree_t* tree , tree_node_t* node , int (*compare_function)(void* X , void* Y));

//subtree is of struct tree_node_t , but is linked with other nodes
binary_tree_t* binary_tree_add_subtree(binary_tree_t* tree , tree_node_t* subtree , int (*compare_function) (void* X , void*Y)); 
tree_node_t* binary_tree_node_create(void* data);
tree_node_t* binary_tree_node_remove(binary_tree_t* tree , tree_node_t* node , int (*compare_function)(void* X , void*Y)); 
void binary_tree_functor_DFS(binary_tree_t* tree , void (*functor) (void*)); 



















/**********************************************************/




/**********************************************************/





#endif
