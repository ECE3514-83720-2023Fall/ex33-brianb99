
#ifndef ABSTRACT_DICTIONARY_HPP
#define ABSTRACT_DICTIONARY_HPP

// KeyType must be partially ordered
// ValueType must support copy 
template <typename KeyType, typename ValueType>
class AbstractDictionary
{
public:

    // return true if dict is empty, else false
    virtual bool isEmpty() const = 0;

    // return number of key-value pairs in the dict
    virtual std::size_t size() const = 0;

    // add an item to the dict
    // throws std::logic_error on duplicate key
    virtual void add(const KeyType& key, const ValueType& value) = 0;

    // remove key-value from the dict
    // throws std::logic_error if dict is empty
    virtual void remove(const KeyType& key) = 0;

    // remove all key-values from the dict
    virtual void clear() = 0;

    // get a copy of value associated with key
    // throws std::logic_error if entry does not exist
    virtual ValueType get(const KeyType& key) const = 0;

    // return true if dict contains key
    virtual bool contains(const KeyType& key) const = 0;

};


#endif // ABSTRACT_DICTIONARY_HPP
