// FILE: company.cpp
// Names: Luis Villalta, Rahul Rani, Dev Gupta
// CLASS implemented: company (see company.h for documentation)


#include <cassert>
#include "company.h"
#include "node.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

using namespace std;

namespace coen79_lab7
{
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }

    //Pre: company name exists
    //Post: head and tail ptr's are assigned NULL, and company name is copied
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);

        this -> company_name = company_name;
        head_ptr = NULL;
        tail_ptr = NULL;
    }
    
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);

        *this = src;    //using overloaded '=' to copy src, to this
    }
    
    //Post: Returns "this" after copying the company name and array
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);

        company_name = src.get_name();  
        list_copy(src.get_head(), head_ptr, tail_ptr);  //copy the list

        return *this;
    }
    
    //Post: Clears the linked list 
    company::~company(){
        list_clear(head_ptr);   //use list clear 
    }
    
    
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    //Pre: product name exists
    //Post: Returns false if item already exists, returns true after inserting the name and price at the head or tail
    bool company::insert(const std::string& product_name, const float& price) {
         
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name))    //returns false if item already exists
            return false;

        else if (head_ptr == NULL)
            list_init(head_ptr, tail_ptr, product_name, price); //if the list is empty
        
        else
            list_tail_insert(tail_ptr, product_name, price);    //else, insert at the end of the list
        
        return true;
    }

    //Pre: Product name exists
    //Post: Returns true if the name is deleted, returns false if the name doesn't exist
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);

        node *remove_ptr, *temp = head_ptr;

        remove_ptr = list_search(head_ptr, product_name); //uses list search to return node that has product_name

        if(remove_ptr == NULL)  //product name doesn't exist
            return false;   

        while(temp -> getLink()  != remove_ptr)     //places a temp pointer to the node just before remove
            temp -> setLink(temp -> getLink());
    
        temp -> setLink(remove_ptr -> getLink()); //updates temp node's link
        delete remove_ptr; 

        return true;
    }
    
    
}
