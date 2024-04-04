//FILE: sequence.cpp
//Names: Luis Villalta, Rahul Rani, Dev gupta

#include "node.h"
#include "sequence.h"

using namespace std;

namespace coen79_lab6{

    //Post: default constructor
    sequence::sequence(){
        init();
    }

    //Post: copy constructor
    sequence::sequence(const sequence &source){
        init();

        *this = source;
    }

    //Post: destructs the sequence and reinitializes the pointers
    sequence::~sequence(){ //deletes list
        list_clear(head_ptr);
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;
    }

    //pre: precursor points to front of list
	//post: set cursor equal to head pointer
    void sequence::start(){ //sets the cursor at the start of the list
        cursor = head_ptr;
        precursor = NULL;
    }

    //pre: if empty, return NULL
	//post: if not, precursor points to tail - 1
    void sequence::end(){
        if(many_nodes == 0) //empty
            return; 
        
        cursor = tail_ptr;

        if(head_ptr == tail_ptr) //only 1 in list
            precursor = NULL;
        else 
            precursor = list_locate(head_ptr, many_nodes - 1); //assigns second to last as pre
        
    }

    //pre: asserts item exists
	//post: set precursor to cursor, then cursor is set to the next link
    void sequence::advance(){   //moves cursor through the list
        assert(is_item());

        precursor = cursor; 
        cursor = cursor -> link();
    }

    //pre: if empty or no current item, insert to front of list: set tail to front if no tail present
	//post: if list not empty and item exists, insert to precursor and point precursor to cursor
    void sequence::insert(const value_type& entry){
        if((is_item() == false) || (precursor == NULL)){ //empty list
            list_head_insert(head_ptr, entry); 
            
            if(tail_ptr == NULL) //if tail hasn't been updated
               tail_ptr = head_ptr;

            cursor = head_ptr; 
            precursor = NULL; 
            many_nodes++; 
        }
        else{
            list_insert(precursor, entry); //insert @precursor 
            cursor = precursor -> link();  //update cursor to be after the new precursor
            many_nodes++;
        }
    }
    //pre: if empty, insert to head pointer, set cursor to head and precursor is null, increment many_nodes
	//post: if cursor equal to null, insert at tail, set precursor to tail and tail set to next link, then cursor = tail (increment many nodes)
	//      else, insert at cursor, set precursor to cursor: if cursor = tail,
    //      set it to next link then cursor to next link (increment many nodes after)
    void sequence::attach(const value_type &entry){
        if(head_ptr == NULL){               //empty list
            list_head_insert(head_ptr, entry);

            tail_ptr = head_ptr;
            cursor = head_ptr;
            precursor = NULL;
        } 
        else if(cursor == NULL){            //cursor is at the end (precursor exists)
            list_insert(tail_ptr, entry);

            cursor = tail_ptr -> link();
            precursor = tail_ptr;
            tail_ptr = tail_ptr -> link();

        }else{           //cursor is somewhere in the middle
            list_insert(cursor, entry); 

            precursor = cursor;
            cursor = cursor -> link();
            if(cursor -> link() == NULL)  //if cursor is the new last node
                tail_ptr = cursor; 

        }

        many_nodes++;
    }

    //pre: calls start() and its sets all things to null
	//post: checks for self assignment 
    void sequence::operator =(const sequence &source){
        list_copy(source.head_ptr, head_ptr, tail_ptr);
        many_nodes = source.many_nodes; 

        start();
        node* temp = source.head_ptr;

        while(temp != source.cursor){  //sets current cursor to the source's cursor position
            advance();                 
            temp = temp -> link();
        }
    }

    //pre: initially checks that cursor points to something first
	//post: removes head and sets all to NULL
    void sequence::remove_current(){ 
        assert(is_item());

        if(cursor == head_ptr){
            if(head_ptr == tail_ptr){ //cursor is the only node in the list
                list_head_remove(head_ptr); 

                head_ptr = NULL;        //update variables
                tail_ptr = NULL;
                cursor = NULL;
                precursor = NULL;
            }else{                      //list is greater than 1 node but cursor is the first node
                list_head_remove(head_ptr); 

                cursor = head_ptr; //updates cursor
            }
        }
        else if(cursor == tail_ptr){      //cursor is the last item in list
                list_remove(precursor); 

                cursor = NULL;          
                tail_ptr = precursor;
        }else{  //cursor is in the middle of the list 
            list_remove(precursor);

            cursor = cursor -> link();
        }

        many_nodes--;
    }  

    //Post: returns the number of nodes in the seq
    sequence::size_type sequence::size() const{
        return many_nodes;
    }


    //Post: returns true if there is an item pointed to by the cursor
    bool sequence::is_item() const{
        if(cursor != NULL) //checks if cursor node exists
            return true;
        else
            return false;
    }

    //Post: returns the data pointed to by the cursor
    sequence::value_type sequence::current() const{ //returns data at cursor 
        assert(is_item());

        return cursor -> data(); 
    }

    //Post: set all pointers to NULL
    void sequence::init(){
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;
    }

}