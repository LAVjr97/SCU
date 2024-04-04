// FILE: node.cpp
// Names: Luis Villalta, Rahul Rani, Dev gupta

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr){
    // Library facilities used: cstdlib
		const node *cursor;
		size_t answer;

		answer = 0;
		for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
	    	++answer;

		return answer;
	}
	
    void list_head_insert(node*& head_ptr, const node::value_type& entry){
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry){
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target){
    // Library facilities used: cstdlib
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target){
    // Library facilities used: cstdlib
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position){
    // Library facilities used: cassert, cstdlib
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position){
    // Library facilities used: cassert, cstdlib
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr){
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr){
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr){
    // Library facilities used: cstdlib

    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr){
    // Library facilities used: cstdlib

    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

	//Pre: start_ptr != NULL or start_ptr != NULL
	//Post: insert a the given head, and update tail, goes through the rest of the list by using start,
	//		and inserts at the tail of the new list
    void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr){
		head_ptr = NULL;
		tail_ptr = NULL;

		if((start_ptr == NULL) || (start_ptr == end_ptr)){
			return;
		}

		list_head_insert(head_ptr, start_ptr -> data());  //insert head
		tail_ptr = head_ptr;

		while(start_ptr -> link() != end_ptr){	//go through the rest of the list
			start_ptr = start_ptr -> link();	//moves start
			list_insert(tail_ptr, start_ptr -> data()); //insert at tail of new list
	
			tail_ptr = tail_ptr -> link(); //update tail
		}
	}

	//Post: returns the count after iterating through the array and looks for the target and updates C
    size_t list_occurrences(node* head_ptr, const node::value_type& target){
		size_t c = 0;
		node* p;

		if(head_ptr == NULL) //count = 0;
			return c;

		for(p = head_ptr; p != NULL; p = p -> link()) //goes through the list searching for the target
			if(p -> data() == target)
				c++;

		return c;
	}

	//Pre: Position is greater than 0, position is less than the length of the list from the start of the headptr
	//Post: inserts the entry at the head if the position is 1, or inserts at the rest of the list
    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position){
		assert((position > 0) && (position <= list_length(head_ptr) + 1));

		if(position == 1) //insert at head
			list_head_insert(head_ptr, entry);
		else 	//insert in the list @position 
			list_insert(list_locate(head_ptr, position - 1), entry);
	}

	//Pre: headptr != NULL, position is greater than 0, and position <= list length
	//Post: return the the data that is being removed
    node::value_type list_remove_at(node*& head_ptr, size_t position){
		assert((head_ptr != NULL) && (position > 0) && (position <= list_length(head_ptr) + 1));
		node::value_type d;

		if(position == 1){ 	//@head
			d = head_ptr -> data();

			list_head_remove(head_ptr);
		}else{			//not @head
			node *p = list_locate(head_ptr, position - 1);
			d = p -> data();

			list_remove(p);
		}
		return d;
	}

	//Pre: Start is >= to 1, start is <= finish, and finish <= list_length(starting from the head pointer)
	//Post: Return null if the list is empty, else, find the nodes where start and finish are and use the list_piece 
	//		function to create a copy and return the new lists head. 
    node* list_copy_segment(node* head_ptr, size_t start, size_t finish){
		assert((1 <= start) && (start <= finish) && (finish <= list_length(head_ptr)));

		if(head_ptr == NULL) //empty, nothing to copy
			return NULL;
		
		node *startp = list_locate(head_ptr, start); //finds the start and end node at positions
		node *endp = list_locate(head_ptr, finish + 1); 
		node *head = NULL;
		node *tail = NULL;

		list_piece(startp, endp, head, tail); //new pointer from startp to endp

		return head;
	}

	//Post: Prints the list depending if the list is empty or if there's multiple nodes
    void list_print (const node* head_ptr){
		//cout<< "Flag before if" << endl;
		if(head_ptr == NULL){	//list is empty
			cout << endl;
			//cout<< "Flag in print if" << endl;
			return; 
		}

		while(head_ptr != NULL){  
			cout << head_ptr -> data();

			if(head_ptr -> link() != NULL) //there's a node after head_ptr
				cout<< ", ";

			head_ptr = head_ptr -> link();
		}

		cout << endl;
	}
	//Pre:	head_ptr != NULL
	//Post:	Iterates through the list and finds duplicates by using two pointers, one pointer is the one being checked
	//		against and the pointer moved through the rest of the list.
	void list_remove_dups(node* head_ptr){
		assert(head_ptr != NULL);

		node *p = head_ptr;
		node *check = p;
		node *dupe;
		
		while(p != NULL){   //p goes through list
			check = p;		
			while(check -> link() != NULL){ //from p onwards, check if the data == p -> data
				if(p -> data() == check -> data()){
					dupe = check;
					list_remove(dupe);
				}else{
					check = check -> link();
				}
			}
			p = p -> link();
		}
	}

	//Citation for detect_loop: https://www.geeksforgeeks.org/detect-loop-in-a-linked-list/#
	//Pre: head_ptr != NULL
	//Post: Using the "Floyd’s Cycle-Finding Algorithm" of using 2 different pointers, to itereated through the list
	//		and find the loop. 
    node* list_detect_loop (node* head_ptr){
		assert(head_ptr != NULL);

		node *slowp = head_ptr, *fastp = head_ptr; 

		while((fastp != NULL) && (fastp -> link() != NULL)){ //fast is what looks for the loop, stops if it doesnt loop
			slowp = slowp -> link();
			fastp = fastp -> link() -> link();

			if(slowp == fastp) //breaks if they meet
				break;
		}

		slowp = head_ptr;			//sets slow to start
		while(slowp != fastp){		// stops when slow == fast
			slowp = slowp -> link(); 
			fastp = fastp -> link();
		}

		return slowp;
	}
}
