#include "catch.hpp"

#include "hash_dictionary.hpp"

#include <iostream> // for debugging
#include <sstream>  // for std::ostringstream
#include <string>   // for std::string

typedef unsigned int KeyType;
typedef std::string ValueType;
typedef std::size_t (*FunctionType)(const KeyType &key);
typedef HashDictionary<KeyType, ValueType, FunctionType> DictionaryType;



TEST_CASE("Basic Tests", "[Dictionary]") {
	//To DO
  
}

TEST_CASE("Test large Dictionary", "[Dictionary]") {
	//To Do
  
}

