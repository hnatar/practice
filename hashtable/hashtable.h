/*	hash table for strings */

#ifndef __simple_hashtable__
#define __simple_hashtable__

#include <iostream>
#include <vector>
#include <list>
#include <string>

class HashTable
{
	private:
		std::vector< std::list<std::string> > a;
		int polynomial_hash(const std::string, const int);
		int _inserts_since_grow;
	public:
		HashTable(int);
		void insert(std::string);
		bool exists(std::string);
		void rehash();
};

HashTable::HashTable(int num_buckets) {
	/* set the number of buckets */
	a.resize(num_buckets);
	_inserts_since_grow = 0;
}

int HashTable::polynomial_hash(const std::string s, const int p) {
	int v = 0;
	for(auto i = s.rbegin(); i!=s.rend(); i++) {
		v = p*v + (*i);
	}
	return v;
}

void HashTable::insert(std::string s) {
	int index = polynomial_hash(s, 31) % a.size();
	a[index].push_back(s);
	_inserts_since_grow++;
	if( _inserts_since_grow > float(a.size()) ) {
		rehash();
	}
}

bool HashTable::exists(std::string s) {
	int index = polynomial_hash(s, 31) % a.size();
	for(auto &candidate: a[index]) {
		if(candidate == s) {
			return true;
		}
	}
	return false;
}

void HashTable::rehash() {
	std::vector< std::string > collect;
	// get all the strings in the hashmap
	for(auto &list_string: a) {
		for(auto &s: list_string) {
			collect.push_back(s);
		}
	}
	// clean current map
	for(auto &ll: a) ll.clear();
	a.resize( 2*a.size() );
	// re-insert
	std::cout << "growing hashtable, size = " << a.size() << std::endl;
	for(auto &s: collect) {
		insert(s);
	}
	_inserts_since_grow = 0;
}

#endif