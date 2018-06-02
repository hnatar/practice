#include <iostream>
#include "hashtable.h"

int main(int argc, char *argv[]) {
	HashTable my_map(1);
	// insert
	for(auto &s: {"Foo, Bar", "BAZ", "do", "you", "dare challenge", "XAN", "?"}) {
		my_map.insert(s);
	}
	for(auto &s: {"Foo, Bar", "BAZ", "do", "you", "dare challenge", "XAN", "?"}) {
		my_map.insert(s);
	}
	// check
	for(auto &s: {"Foo", "foo", "Foo, Bar"}) {
		std::cout << s << ": " << my_map.exists(s) << std::endl;
	}
	// re-hash
	my_map.rehash();
	// check
	for(auto &s: {"Foo", "foo", "Foo, Bar", "BAZ"}) {
		std::cout << s << ": " << my_map.exists(s) << std::endl;
	}
	return 0;
}