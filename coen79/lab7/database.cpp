// FILE: database.cpp
// Names: Luis Villalta, Rahul Rani, Dev Gupta 
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"
#include "company.h"
#include "node.h"
#include <algorithm>


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

using namespace std;

namespace coen79_lab7
{
    //postcondition: set used_slots to 0, allocated slots to initial capacity, 
    //               company_array to new company[aloc_slots] (reserving data)
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    //postcondition: creates database of companies based on source
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);

        *this = src; //using overloaded = operator
    }
    
    //postcondition: returns database equal to database on right of equal sign
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);
        cout << "copying elements of database...";

        delete [] company_array;

        aloc_slots = rhs.aloc_slots;       //copy variables
        used_slots = rhs.used_slots;
        company_array = new company[rhs.aloc_slots]; //new array

        copy(rhs.company_array, rhs.company_array + rhs.used_slots, company_array); //copies rhs to new array

        return *this; //return this instance
    }
    
    //postcondition: clears database that activates functions, sets slots to 0
    database::~database(){
        aloc_slots = 0;
        used_slots = 0;

        delete [] company_array;
    }
    
    //precondition: calls debug function for reserving elements
    //postcondition: allocates memory for database so more companies can be stored in array 
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Canít allocate less than we are using.
        
        aloc_slots = new_capacity; 
        company *nc = new company[aloc_slots]; //new array

        copy(company_array, company_array + used_slots, nc); //copies old array to new array

        delete [] company_array;

        company_array = nc; //assigns the new array to pointer
    }
    
    //precondition: asserts that an entry name provided / length > 0
    //postcondition: inserts a company into array based on string entry, 
    //               return true if company inserted, false if not
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }
        
        if(used_slots == aloc_slots)   //if dynamic array is full, reserve 1 more space, alloc is updated in reserve
            reserve(aloc_slots + 1);
        
        company ins = company(entry); //create new linked list

        company_array[used_slots] = ins; 
        used_slots++;

        return true;
    }
    
    //precondition: assert company/product name given
    //postcondition: inserts new product to the given company using provided company name, 
    //               product name/price. returns true if inserted, false otherwise
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);

        size_type pos = search_company(company); //gets company's position

        if(pos != COMPANY_NOT_FOUND){                //if it exists
            company_array[pos].insert(product_name, price);     //insert
            return true;
        }else 
            return false;
        
    }
    
    //postcondition: removes company from array based on given company name, 
    //               iterates down 1 position to fill array gap
    bool database::erase_company(const std::string &company) {
        
        size_type company_index = search_company(company), i;

        if(company_index != COMPANY_NOT_FOUND){     //if company exists
            for(i = company_index; i < used_slots - 1; i++)    //goes through the array shifting the companies
                company_array[i] = company_array[i + 1];       
            used_slots--;
            return true;
        }else  
            return false;
    
    }
    
    //precondition: asserts there is a provided company name and product name
    //postcondition: erases item from company's list of products using product 
    //               name/given company. returns true if something is deleted, false otherwise
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);

        
        node *p;
        size_type pos = search_company(cName); //checks if company exists first

        if(pos != COMPANY_NOT_FOUND){        //if company exists
            company_array[pos].erase(pName);       //erase the pName at that position
            return true; 
        }else
            return false; 

    }
    
    
    //precondition: assert company name provided
    //postcondition: returns position of given company if it exists
    //               in the array, else returns COMPANY_NOT_FOUND
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);
        size_type i;

        for(i = 0; i < used_slots ; i++)   //goes through the array
            if(company_array[i].get_name() == company)      //if the name exists, return the position
                return i;
        

        return COMPANY_NOT_FOUND;

    }
    

    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }else{
            std::cout << "Printing the products of " << cName << ":"<< std::endl;
            company_array[c_index].print_items();
            std::cout << std::endl;
        
            return true;
        }
    }
    
    
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
