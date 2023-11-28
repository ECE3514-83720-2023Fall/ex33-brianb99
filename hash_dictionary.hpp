#ifndef HASH_DICTIONARY_HPP
#define HASH_DICTIONARY_HPP

#include "abstract_dictionary.hpp"

// KeyType must have equality comparison defined
// HashType must be function-like hash(const KeyType & k) returning a
// std::size_t
template <typename KeyType, typename ValueType, typename HashType>
class HashDictionary : public AbstractDictionary<KeyType, ValueType> {
public:
  // default constructor
  HashDictionary(HashType hash, std::size_t initial_capacity = 97,
                 float load_factor = 0.75);

  // copy constructor
  HashDictionary(const HashDictionary &rhs);

  // move constructor
  HashDictionary(HashDictionary &&rhs);

  // destructor
  ~HashDictionary();

  // copy assignment
  HashDictionary &operator=(const HashDictionary &rhs);

  // move assignment
  HashDictionary &operator=(HashDictionary &&rhs);

  // return true if dict is empty, else false
  bool isEmpty() const;

  // return number of key-value pairs in the dict
  std::size_t size() const;

  // add an item to the dict
  // throws std::bad_alloc
  void add(const KeyType &key, const ValueType &value);

  // remove key-value from the dict
  // throws std::logic_error if dict is empty
  void remove(const KeyType &key);

  // remove all key-values from the dict
  void clear();

  // get a copy of value assocaited with key
  // throws std::logic_error if entry does not exist
  ValueType get(const KeyType &key) const;

  // return true if dict contains key
  bool contains(const KeyType &key) const;

private:
  struct KeyValueType {
    bool filled = false;
    KeyType key;
    ValueType value;

    KeyValueType() : key(KeyType()), value(ValueType()) {}

    KeyValueType(const KeyType &k) : key(k), value(ValueType()) {}

    KeyValueType(const KeyType &k, const ValueType &v) : key(k), value(v) {}

    bool operator==(const KeyValueType &rhs) const { return key == rhs.key; }
  };

  HashType m_hash;

  float m_load_factor;
  std::size_t m_capacity = 0;
  std::size_t m_size = 0;
  KeyValueType *m_data = nullptr;
};

#include "hash_dictionary.tpp"

#endif
