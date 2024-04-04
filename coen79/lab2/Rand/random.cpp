#include "random.h"

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2{	
	rand_gen::rand_gen(int set_seed, int set_multiplier, int set_increment, int set_modulus){
		seed = seed;
		multiplier = multiplier;
		increment = increment;
		modulus = modulus;
	}
	
	void rand_gen::set_seed(int new_seed){
		int seed;
		seed = (multiplier * new_seed + increment) % modulus;
	}

	int rand_gen::next(){
		return seed;
	}

	void rand_gen::print_info(){
		cout << "Seed: " << seed << "\n";
		cout << "Multiplier: " << multiplier << "\n";
		cout << "Increment: " << increment << "\n"; 	
		cout << "Modulus: " << modulus << "\n";
		cout << "Next: " << seed << "\n";
	}
} 
