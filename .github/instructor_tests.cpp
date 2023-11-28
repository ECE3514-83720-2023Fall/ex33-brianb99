#include "../catch.hpp"

#include "../hash_dictionary.hpp"

#include <iostream> // for debugging
#include <sstream>  // for std::ostringstream
#include <string>   // for std::string

typedef unsigned int KeyType;
typedef std::string ValueType;
typedef std::size_t (*FunctionType)(const KeyType &key);
typedef HashDictionary<KeyType, ValueType, FunctionType> DictionaryType;

// a trivial hash function
std::size_t hash(const KeyType &key) { return key; }

TEST_CASE("Basic Tests", "[Dictionary]") {

  DictionaryType dict(hash);

  REQUIRE(dict.isEmpty());
  REQUIRE(dict.size() == 0);

  REQUIRE_NOTHROW(dict.add(32, "thirty-two"));
  REQUIRE_FALSE(dict.isEmpty());
  REQUIRE(dict.size() == 1);

  REQUIRE(dict.contains(32));
  REQUIRE(dict.get(32) == "thirty-two");

  REQUIRE_NOTHROW(dict.add(9, "nine"));
  REQUIRE_FALSE(dict.isEmpty());
  REQUIRE(dict.size() == 2);

  REQUIRE(dict.contains(32));
  REQUIRE(dict.get(32) == "thirty-two");
  REQUIRE(dict.contains(9));
  REQUIRE(dict.get(9) == "nine");

  REQUIRE_NOTHROW(dict.remove(9));
  REQUIRE(dict.contains(32));
  REQUIRE(dict.get(32) == "thirty-two");
  REQUIRE_FALSE(dict.contains(9));
  REQUIRE_THROWS_AS(dict.get(9), std::logic_error);

  REQUIRE_NOTHROW(dict.remove(32));
  REQUIRE_FALSE(dict.contains(32));
  REQUIRE_THROWS_AS(dict.get(32), std::logic_error);

  REQUIRE_THROWS_AS(dict.remove(1223), std::logic_error);

  REQUIRE(dict.isEmpty());
  REQUIRE(dict.size() == 0);

  REQUIRE_THROWS_AS(dict.remove(1223), std::logic_error);
}

TEST_CASE("Test large Dictionary", "[Dictionary]") {

  DictionaryType dict(hash);

  for (KeyType k = 0; k < 2000; k++) {
    std::ostringstream ss;
    ss << k;
    INFO(k);
    REQUIRE_NOTHROW(dict.add(k, ss.str()));
  }

  REQUIRE_FALSE(dict.contains(3000));
  REQUIRE_THROWS(dict.get(3000));
  REQUIRE_THROWS(dict.remove(3000));

  for (KeyType k = 0; k < 2000; k++) {
    std::ostringstream ss;
    ss << k;
    INFO(k);
    REQUIRE(dict.contains(k));
    REQUIRE(dict.get(k) == ss.str());
  }

  for (KeyType k = 0; k < 2000; k++) {
    REQUIRE_NOTHROW(dict.remove(k));
    REQUIRE_FALSE(dict.contains(k));
    REQUIRE_THROWS(dict.get(k));
  }

  REQUIRE_FALSE(dict.contains(3000));
  REQUIRE_THROWS(dict.get(3000));
  REQUIRE_THROWS(dict.remove(3000));
}
