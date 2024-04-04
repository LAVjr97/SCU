#include <cassert>
#include "statistician.h" 

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2{
	statistician::statistician(){
        	size = 0;
        	total = 0;
    	}

    void statistician::next (double r){
    	if(size == 0){
        	size++;
        	total = r; 
        	min = r; 
        	max = r;
			//cout << "flag";
        }
		else{
			//cout << size;
			size++;
 			total += r;
        	if(r < min)
            	min = r;
        	if(r > max)
            	max = r;
		}
    }
    
    void statistician::reset(){
    	size = 0;
    	total = 0;
    }
	
	int statistician::length() const{
		assert(size > 0);
		return size;
	}
	
	double statistician::sum() const{
		assert(size > 0);
		return total;
	}
	
    double statistician::mean() const{
    	assert(size > 0);
	   	return (total/size);
    }

    double statistician::minimum() const{
        assert(size > 0);
        return min;
    }	

    double statistician::maximum() const{
    	assert(size > 0);
    	return max;
    }

    statistician operator +(const statistician &s1, const statistician &s2){
		statistician addition;
        
		if(s1.length() == 0)
            return s2;
        if(s2.length() == 0)
        	return s1;
		
    	addition.size = s1.length() + s2.length();
        addition.total = s1.sum() + s2.sum();

    	if(s1.minimum() < s2.minimum())
            addition.min = s1.minimum();
    	else
            addition.min = s2.minimum();
        if(s1.maximum() >  s2.maximum())
			addition.max = s1.maximum();
		else
			addition.max = s2.maximum();
		return addition;
    }

    statistician operator *(double scale, const statistician &s){
        statistician mult;
	
        if(s.length() == 0)
            		return s;

        mult.size = s.length();
        mult.total = scale * s.length();

        if(scale < 0){
			mult.max = scale * s.minimum();
			mult.min = scale * s.maximum();
        }else{
        	mult.max = scale * s.maximum();
			mult.min = scale * s.minimum(); 
      	}

        return mult;
    }

    bool operator ==(const statistician &s1, const statistician &s2){
        if(s1.length() != s2.length())
            return false;
        if(s1.length() == 0 || s2.length() == 0)
          	return true;
       	if((s1.length() == s2.length()) && (s1.sum() == s2.sum()) && (s1.mean() == s2.mean()) && (s1.minimum() == s2.minimum()) && (s1.maximum() == s2.maximum()))
			return true;

	}    	
}
