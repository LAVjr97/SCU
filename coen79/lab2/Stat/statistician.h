#ifndef STATS_H
#define STATS_H
#include <iostream>

namespace coen79_lab2
{
    	class statistician{
        	public:
            		statistician();

            		void next(double r);
            		void reset();
            		int length() const;
            		double sum() const;
            		double mean()const;
            		double minimum() const;
            		double maximum() const;

            		friend statistician operator + (const statistician& s1, const statistician& s2);
            		friend statistician operator * (double scale, const statistician &s); 

        	private:
            		double total; 
            		int size;
            		double min;
            		double max;
            		double avg;
	};    
	bool operator == (const statistician &s1, const statistician &s2);
}
#endif
