// FILE: keyed_bag.cpp
// CLASS IMPLEMENTED: keyed_bag (see keyed_bag.h for documentation)
//
//
//
//
// INVARIANT for the keyed_bag class:
//   1. The number of items in the keyed_bag is in the member variable used;
//   2. For an empty keyed_bag, we do not care what is stored in any of data; for a
//      non-empty keyed_bag the items in the keyed_bag are stored in data[0] through
//      data[used-1], and we don't care what's in the rest of data.


#include <algorithm> // Provides copy function
#include <cassert>   // Provides assert function
#include "keyed_bag.h"
#include <iostream>

using namespace std;

namespace coen79_lab4{

    const keyed_bag::size_type keyed_bag::CAPACITY;

    bool keyed_bag::erase(const key_type& key){
        assert(used > 0 && has_key(key));
        int i, j; 

        for(i = 0; i < used; i++)
            if(keys[i] == key){
                for(j = i; j < used - 1; i++){
                    keys[j] = keys[j + 1];
                    data[j] = data[j + 1];
                }
                return true;
            }

        return false;
    }

    void keyed_bag::insert(const value_type& entry, const key_type& key){
        assert(size() < CAPACITY && has_key(key) == false);
        
        keys[used] = key;
        data[used] = entry;
        used++;
    }

    void keyed_bag::operator +=(const keyed_bag& addend){
        assert(size() + addend.size() < CAPACITY);
        int i;

        for(i = 0; i < addend.used; i++)
            if(has_key(addend.keys[i])){
                keys[used] = addend.keys[i];
                data[used] = addend.data[i];
                used++;
            }
    }

    bool keyed_bag::has_key(const key_type& key) const{
        int i;

        for(i = 0; i < CAPACITY; i++)
            if(key == keys[i])
                return true;

        return false;
    }

    keyed_bag::value_type keyed_bag::get(const keyed_bag::key_type& key) const{
        assert(has_key(key));
        int i;

        for(i = 0; i < used; i++)
            if(key == keys[i])
                return data[i];
        return NULL; 
    }

    keyed_bag::size_type keyed_bag::size() const{
        return used;
    }

    keyed_bag::size_type keyed_bag::count(const value_type& target) const{
        int i;
        size_type c;

        for(i = 0; i < CAPACITY; i++)
            if(target == data[i])
                c++;
                cout << c;
        return c;
    }

    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2){
        assert(b1.size() + b2.size() < b1.CAPACITY);
        keyed_bag nb;

        nb += b1;
        nb += b2;

        return nb;
    }

    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const{
        int i; 

        for(i = 0; i < otherBag.used; i++)
            if(has_key(otherBag.keys[i]))
                return true;

        return false; 
    }
}
