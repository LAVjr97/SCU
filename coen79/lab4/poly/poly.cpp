// FILE: poly.cpp
//
// 
// 
//
//
// NOTE: current_degree is always equal to the largest exponent with a non-zero
//          coefficient. If all coeficients are 0.0, then current_degree is 0.

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <climits>
#include "poly.h"

using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4
{
    // CONSTANTS
    const unsigned int polynomial::MAXIMUM_DEGREE;

    // HELPER FUNCTIONS
    void polynomial::update_current_degree(){
        int i, cur = 0; 

        for(i = 0; i < MAXIMUM_DEGREE; i++){
            if(coef[i] != 0)
                cur = i;
        } 

        current_degree = cur;
    }

    // CONSTRUCTOR
	polynomial::polynomial(double c, unsigned int exponent){
        assert(exponent <= MAXIMUM_DEGREE);
        clear(); 
        coef[exponent] = c;
        current_degree = exponent;
    }

	// MODIFICATION MEMBER FUNCTIONS
	void polynomial::assign_coef(double coefficient, unsigned int exponent){
        assert(exponent <= MAXIMUM_DEGREE);
        coef[exponent] = coefficient; 
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent){
        assert(exponent <= MAXIMUM_DEGREE);
        coef[exponent] += amount;

    }

	void polynomial::clear( ){
        int i;

        for(i = 0; i < MAXIMUM_DEGREE; i++)
            coef[i] = 0;

        current_degree = 0;
    }

	// // CONSTANT MEMBER FUNCTIONS
    polynomial polynomial::antiderivative( ) const{
        assert(degree() < MAXIMUM_DEGREE);
        int i;
        polynomial anti;

        for(i = 0; i < MAXIMUM_DEGREE - 1; i++)
            anti.coef[i + 1] = coef[i] / i + 1;
        
        anti.coef[0] = 0;
        anti.update_current_degree();
        return anti;
    }

	double polynomial::coefficient(unsigned int exponent) const{
        if(exponent > MAXIMUM_DEGREE)
            return 0;
        else
            return coef[exponent];
        
    }

    double polynomial::definite_integral(double x0, double x1) const{
        polynomial anti = antiderivative(); 
        
        double def = anti.eval(x0) - anti.eval(x1);
        
        return def;
    }

	polynomial polynomial::derivative( ) const{
        assert(degree() < MAXIMUM_DEGREE);
        int i; 
        polynomial der;
        
        for(i = 0; i < MAXIMUM_DEGREE - 1; i++)
            der.coef[i] = coef[i + 1] * (i + 1);

        der.update_current_degree();
        return der; 
    }

	double polynomial::eval(double x) const{
        int i;
        double sum;

        for(i = 0; i < MAXIMUM_DEGREE - 1; i++)
            sum += (pow(x, i) * coef[i]);

        return sum;
    }

    bool polynomial::is_zero( ) const{
        if(coef[current_degree] == coef[0]) 
            return true;
        else
            return false;
    }

	unsigned int polynomial::next_term(unsigned int e) const{
        int i;
        
        for(i = e + 1; i < MAXIMUM_DEGREE - 1; i++)
            if(coef[i] != 0)
                return i;

        return 0;
    }

	unsigned int polynomial::previous_term(unsigned int e) const{
        int i;

        for(i = e - 1; i > 0; i--)
            if(coef[i] != 0)
                return i;

        return 0;
    }
    
    // // NON-MEMBER BINARY OPERATORS
    polynomial operator +(const polynomial& p1, const polynomial& p2){
        int i;
        polynomial np; 

        for(i = 0; i < np.MAXIMUM_DEGREE; i++)
            np.add_to_coef(p1.coefficient(i) + p2.coefficient(i), i);
        
        np.update_current_degree();
        return np;
    }

    polynomial operator -(const polynomial& p1, const polynomial& p2){
        int i;
        polynomial np; 

        for(i = 0; i < np.MAXIMUM_DEGREE; i++)
            np.add_to_coef(p1.coefficient(i) - p2.coefficient(i), i);
        
        np.update_current_degree();
        return np;
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2){
        //for *, need to check the MAXIMUM_DEGREE
        assert(p1.degree() + p2.degree() < p1.MAXIMUM_DEGREE);
        polynomial np;
        int i, j;

        for(i = 0; i <= p1.degree(); j++)
            for(j = 0; j <= p2.degree(); j++)
                np.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i + j);

        np.update_current_degree();
        return np;
    }

    // NON-MEMBER OUTPUT FUNCTIONS
    std::ostream& operator << (std::ostream& out, const polynomial& p){
       int i;

       out << fixed; 
       out << setprecision(1);

        for(i = p.degree(); i >= 0; i--){
            if(p.degree() == 0)
                cout << p.coefficient(i);
            
            else if(p.coefficient(i) != 0){
                
                if(i == p.degree()){
                    if(i > 1)
                        out << p.coefficient(i) << " ";
                    else if(i == 1)
                        out << p.coefficient(i) << "x ";
                    else 
                        out << p.coefficient(i) << " ";
                }

                else if( i < p.degree() && i > 1){
                    if(p.coefficient(i) > 0)
                        out << "- " << p.coefficient(i) * -1;
                    else 
                        out << "+ " << p.coefficient(i);
                    out << "x " << i << " "; 
                }

                else if(i == 0){
                    if(p.coefficient(i) < 0)
                        out << "- " << p.coefficient(i) * -1;
                    else
                        out << "+ " << p.coefficient(i);
                }

                else if(i == 1){
                    if(p.coefficient(i) < 0)
                        out << "- " << p.coefficient(i) * -1;
                    else
                        out << "+ " << appp.coefficient(i);
                    out << "x ";
                }
            }
        }
    }
}
