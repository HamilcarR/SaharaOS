#include "../includes/data_struct.h"






linked_list_t* linked_list_create(){
	linked_list_t* list =  (linked_list_t*) kmalloc(sizeof(linked_list_t)) ; 
	list->begin = NULL ; 
	list->end = NULL ; 
	list->size = 0 ; 
	return list ; 
}


/**********************************************************/

void linked_list_free(linked_list_t* list){

	list_node_t* ptr ; 
	while( (ptr = list->begin) && ptr != NULL){
		list_node_t* next = ptr->next ; 
		kfree(ptr) ; 
		list->begin = next ; 

	}
	list->size = 0 ; 
	kfree(list) ; 
}

/**********************************************************/

void linked_list_free_node(list_node_t* node){
	kfree(node) ; 
}


 


/**********************************************************/


list_node_t* linked_list_get(linked_list_t* list, size_t i) {
	list_node_t* ptr = list->begin ; 
	size_t j = 0 ; 
	while(ptr->next && j != i)
		ptr = ptr->next ; 
	if(i == j) 
		return ptr ;
	else
		return NULL ; 

}


/**********************************************************/

list_node_t* linked_list_add_end(linked_list_t* list , list_node_t* node){
	if(list == NULL)
		return NULL ; 
	if(node == NULL)
		return NULL ; 
	if(!list->begin)
		list->begin = node;

	node->prev = list->end ; 
	list->end->next = node ; 
	list->end = node ; 
	list->size += 1 ; 
	node->next = NULL ; 
	return node ; 

}


/**********************************************************/

list_node_t* linked_list_add_begin(linked_list_t* list , list_node_t* node){
	if(list == NULL) 
		return NULL ; 
	if(node == NULL) 
		return NULL  ;
	if(!list->end)
		list->end = node ; 
	node->prev = NULL ; 
	node->next = list->begin; 
	list->begin = node ; 
	list->size ++ ; 
	return node ; 


}

/**********************************************************/
list_node_t* linked_list_create_node(void* data){
	list_node_t* node = (list_node_t*) kmalloc(sizeof(list_node_t)); 
	node->data = data ;
	node->next = NULL ;
	node->prev = NULL ; 
	return node ; 


}



/**********************************************************/
list_node_t* linked_list_pop_node(linked_list_t* list , size_t i){
	if(i >= list->size)
		return NULL ; 
	if(i == 0){
		list_node_t* begin = list->begin ; 
		list->begin = begin->next ;
		list->begin->prev = NULL ; 
		list->size-- ; 
		return begin ; 
	}

	list_node_t* node = list->begin; 
	unsigned int x = 0 ; 
	
	while(x != i - 1) 
		node=node->next ; 
	if(node->next->next == NULL){
		list->end = node; 
		list->size-- ; 
		node->next = NULL ; 
		return node->next ; 
	}
	list_node_t* ret = node->next ; 
	node->next = node->next->next ;
	node->next->next->prev = node->next ; 
	list->size-- ; 
	return ret ; 


}

/**********************************************************/

/*binary tree implementation*/
/***********************************************************************************************************/

binary_tree_t* binary_tree_create(){
	binary_tree_t* b= (binary_tree_t*) kmalloc(sizeof(binary_tree_t)) ; 
	b->root = NULL ;
	b->size = 0 ; 
	return b ; 
}



/**********************************************************/

tree_node_t* binary_tree_node_create(void* data){
	tree_node_t* node = (tree_node_t*) kmalloc(sizeof(tree_node_t)) ; 
	node->data = data ; 
	node->right = NULL ; 
	node->left = NULL ; 

}


/**********************************************************/
void tree_rec_add(tree_node_t* root , tree_node_t* node , int (*compare_function)(void* X , void* Y)){
		if(compare_function(root->data , node->data) == -1){ //node->data < root->data 
			if(root->left != NULL)
				tree_rec_add(root->left , node , compare_function) ; 	
			else{
				root->left = node ; 
				node->left = NULL ; 
				node->right = NULL ; 
			}
		}
		else {// node->data >= root->data
			if(root->right != NULL)
				tree_rec_add(root->right , node , compare_function) ; 
			else{
				root->right = node ; 
				node->left = NULL ; 
				node->right = NULL ; 

			}

		}



}

tree_node_t* binary_tree_add(binary_tree_t* tree , tree_node_t* node , int (*compare_function)(void* X, void* Y)){
	if(tree == NULL)
		return NULL ; 
	if(tree->root == NULL){
		tree->root = node ; 
		node->left = NULL ; 
		node->right = NULL ; 
		return node ; 
	}
	
	tree_rec_add(tree->root , node , compare_function);
	tree->size++ ;
	return node ; 

}

/**********************************************************/


void tree_traverseDFS(tree_node_t* root , void (*functor)(void* X)){
	functor(root->data) ; 	
	if(root->left != NULL)
		tree_traverseDFS(root->left , functor) ; 
	if(root->right != NULL)
		tree_traverseDFS(root->right , functor); 




}




void binary_tree_functor_DFS(binary_tree_t* tree , void (*functor)(void* X)){
	if(tree != NULL && tree->root != NULL)
		tree_traverseDFS(tree->root , functor) ;


}


/**********************************************************/

void rec_add_subtree(binary_tree_t* tree , tree_node_t* subtree , int (*compare_function)(void* X , void* Y)){
		if(subtree != NULL){
			tree_node_t* left = subtree->left ; 
			tree_node_t* right = subtree->right ;
			binary_tree_add(tree , subtree , compare_function); 
			rec_add_subtree(tree , left , compare_function);
			rec_add_subtree(tree , right , compare_function) ; 


		}

}




binary_tree_t* binary_tree_add_subtree(binary_tree_t * tree , tree_node_t* subtree , int (*compare_function)(void* X , void* Y)){
		if(tree == NULL)
			return NULL ; 
		if(subtree == NULL)
			return tree ; 

		rec_add_subtree(tree , subtree , compare_function); 
		return tree ; 


}
/**********************************************************/
tree_node_t* rec_remove(tree_node_t* root , tree_node_t* node , int (*compare_function)(void* X , void* Y)){

	if(root->left == node){
		tree_node_t* left_sub_tree = node->left ; 
		tree_node_t* right_sub_tree = node->right ; 
		root->left = NULL ; 
		binary_tree_t tree ; 
		tree.root = root ;
		
		binary_tree_add_subtree(&tree , left_sub_tree , compare_function); 
		binary_tree_add_subtree(&tree , right_sub_tree , compare_function); 
		return node ; 
	}
	if(root->right == node){
		tree_node_t* left_sub_tree = node->left ; 
		tree_node_t* right_sub_tree = node->right ; 
		root->right = NULL ; 
		binary_tree_t tree ; 
		tree.root = root ; 
		binary_tree_add_subtree(&tree , left_sub_tree , compare_function); 
		binary_tree_add_subtree(&tree , right_sub_tree , compare_function); 
		return node ; 

	}

	if(root->left != NULL)
		return rec_remove(root->left , node , compare_function); 
	if(root->right != NULL)
		return rec_remove(root->right , node , compare_function); 
	return NULL ; 
}





tree_node_t* binary_tree_node_remove(binary_tree_t* tree, tree_node_t* node , int (*compare_function)(void* X , void *Y)){
	if(tree == NULL)
		return NULL ; 
	if(tree->root == NULL)
		return NULL ; 
	if(node == NULL)
		return NULL ; 
	if(tree->root == node){
		tree_node_t* left_sub_tree = node->left ; 
		tree_node_t* right_sub_tree = node->right ; 
		node->left = NULL ; 
		node->right = NULL ; 
		tree->size-- ;
		tree->root = NULL ; 
		binary_tree_add_subtree(tree , left_sub_tree , compare_function); 
		binary_tree_add_subtree(tree , right_sub_tree , compare_function); 
		return node ; 

	}
 	tree_node_t* ret =  rec_remove(tree->root , node , compare_function) ; 
	if(ret)
		tree->size--; 
	return ret ; 
	
}









































