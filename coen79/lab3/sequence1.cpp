#include "sequence1.h"

using namespace std;
using namespace coen79_lab3;

namespace coen79_lab3{ 
    sequence::sequence(){ 
        current_index = 0; 
        used = 0;
    }
    
    void sequence::start(){
        current_index = 0;
    }

    sequence::value_type sequence::current() const{
        assert(is_item() == true);
        return data[current_index];
    }

    void sequence::advance(){
        assert(size() < CAPACITY);
        if(current_index != (CAPACITY - 1))
            current_index++;
    }

    void sequence::insert_front(value_type &entry){
        assert(size() < CAPACITY);
        int i;

        for(i = used; i >= 0; i--)
            data[i] = data[i - 1];
        data[0] = entry; 
        current_index = 0;
        used++;
    }

    void sequence::remove_front(){
        assert(is_item() == true);
        int i;

        for(i = 0; i < used - 1; i++)
            data[i] = data[i + 1];
        used--;
    }

    void sequence::attach_back(value_type &entry){
            assert(size() < CAPACITY);
            
            data[used] = entry; 
            current_index = used;
            used++;
    }

    void sequence::end(){
        current_index = used - 1; 
    }

    sequence::size_type sequence::size() const{
        return used;
    }

    bool sequence::is_item() const{
        return (current_index < used);
    }

    sequence::value_type operator [](sequence::size_type index) const{
        assert(index < size());

        return data[index];
    }

    sequence operator +=(sequence &lhs, sequence &rhs){
        assert(lhs.size() + rhs.size() < lhs.CAPACITY);
        int i;
        rhs.start();

        for(i = 0; i < rhs.size() - 1; i++){
            lhs.attach_back(rhs.current());
            rhs.advance();
        }

        return lhs;
    }

    sequence operator +(const sequence &lhs, const sequence &rhs){
        assert(lhs.size() + rhs.size() < lhs.CAPACITY);
        int i;
        sequence ns(lhs);
        sequence old(rhs);
        old.start();

        for(i = 0; i < old.size(); i++){
            ns.attach_back(old.current());
            old.advance();
        }
        return ns;

    }



}