#include "hash_dictionary.hpp"

// prime test for use in add
#include <cmath>
bool isprime(std::size_t index) {
    
    if ((index == 2) || (index == 3)) {
        return true;
    }
    if ((index % 2) == 0 || (index % 3) == 0) {
        return false;
    }
    std::size_t i = 5;
    while (i * i <= index) {
        if ((index % i) == 0 || (index % (i + 2) == 0)) {
            return false;
        }
        i += 6;
    }
    return true;
}

template <typename KeyType, typename ValueType, typename HashType>
HashDictionary<KeyType, ValueType, HashType>::HashDictionary(
                                                             HashType hash, std::size_t initial_capacity, float load_factor) {
    m_hash = hash;
    m_load_factor = load_factor;
    m_capacity = initial_capacity;
    m_size = 0;
    m_data = new KeyValueType[m_capacity];
}

template <typename KeyType, typename ValueType, typename HashType>
HashDictionary<KeyType, ValueType, HashType>::HashDictionary(
                                                             const HashDictionary &rhs) {
    
    m_load_factor = rhs.load_factor;
    m_capacity = rhs.m_capacity;
    m_size = rhs.m_size;
    m_data = new KeyValueType[m_capacity];
    for (std::size_t i = 0; i < m_size; ++i) {
        m_data[i] = rhs.m_data[i];
    }
}

template <typename KeyType, typename ValueType, typename HashType>
HashDictionary<KeyType, ValueType, HashType>::HashDictionary(
                                                             HashDictionary &&rhs) {
    std::swap(m_load_factor, rhs.m_load_factor);
    std::swap(m_capacity, rhs.m_capacity);
    std::swap(m_size, rhs.m_size);
    std::swap(m_data, rhs.m_data);
}

template <typename KeyType, typename ValueType, typename HashType>
HashDictionary<KeyType, ValueType, HashType>::~HashDictionary() {
    delete[] m_data;
}

template <typename KeyType, typename ValueType, typename HashType>
HashDictionary<KeyType, ValueType, HashType> &
HashDictionary<KeyType, ValueType, HashType>::operator=(
                                                        const HashDictionary &rhs) {
    
    if (this == &rhs)
        return *this;
    
    if (m_capacity != rhs.m_capacity) {
        delete[] m_data;
        m_capacity = rhs.m_capacity;
        m_data = new KeyValueType[m_capacity];
    }
    m_size = rhs.m_size;
    for (std::size_t i = 0; i < m_size; ++i) {
        m_data[i] = rhs.m_data[i];
    }
    
    return *this;
}

template <typename KeyType, typename ValueType, typename HashType>
HashDictionary<KeyType, ValueType, HashType> &
HashDictionary<KeyType, ValueType, HashType>::operator=(HashDictionary &&rhs) {
    
    // tear down current instance, make empty
    delete[] m_data;
    m_data = nullptr;
    m_capacity = 0;
    m_size = 0;
    
    // steal contents of rhs
    std::swap(m_load_factor, rhs.m_load_factor);
    std::swap(m_capacity, rhs.m_capacity);
    std::swap(m_size, rhs.m_size);
    std::swap(m_data, rhs.m_data);
    
    return *this;
}

template <typename KeyType, typename ValueType, typename HashType>
bool HashDictionary<KeyType, ValueType, HashType>::isEmpty() const {
    
    return m_size == 0;
}

template <typename KeyType, typename ValueType, typename HashType>
std::size_t HashDictionary<KeyType, ValueType, HashType>::size() const {
    
    return m_size;
}

template <typename KeyType, typename ValueType, typename HashType>
void HashDictionary<KeyType, ValueType, HashType>::add(const KeyType &key,
                                                       const ValueType &value)
{
    // hash the key
    std::size_t index = m_hash(key) % m_capacity;

    // do linear probing
    std::size_t numprobes = 0;
    while (m_data[index].filled && (numprobes < m_capacity)) {
        if (m_data[index].key == key) {
            throw std::logic_error("Duplicate key in HashDictionary::add");
        }

        index = (index + 1) % m_capacity;
        numprobes += 1;
    }
    if (numprobes == m_capacity) {
        throw std::logic_error("Too many probes in HashDictionary::add");
    }

    // test if we need to reallocate
    if (m_load_factor * m_capacity < m_size) {

        // find next prime > 2*m_capacity
        // there are better ways to do this
        std::size_t newcap = 2 * m_capacity;
        while (!isprime(newcap)) {
            newcap += 1;
        }

        // allocate
        KeyValueType* temp = new KeyValueType[newcap];

        // rehash all entries
        for (std::size_t i = 0; i < m_capacity; ++i) {
            if (m_data[i].filled) {
                // hash into new array
                std::size_t newindex = m_hash(m_data[i].key) % newcap;
                // do linear probing
                std::size_t numprobes = 0;
                while (temp[newindex].filled && (numprobes < newcap)) {
                    newindex = (newindex + 1) % newcap;
                    numprobes += 1;
                }
                temp[newindex].filled = true;
                temp[newindex].key = m_data[i].key;
                temp[newindex].value = m_data[i].value;
            }
        }

        // cleanup
        delete[] m_data;
        m_data = temp;
        m_capacity = newcap;
    }

    // insert the key-value pair
    m_data[index].filled = true;
    m_data[index].key = key;
    m_data[index].value = value;
    m_size += 1;
      

}

template <typename KeyType, typename ValueType, typename HashType>
void HashDictionary<KeyType, ValueType, HashType>::remove(const KeyType &key) {
    
    //TODO implement the remove method...
    if (!contains(key)) {
        throw std::logic_error("Nonexistant key in HashDictionary::remove");
    }

    // do linear probing
    std::size_t index = m_hash(key) % m_capacity;
    std::size_t numprobes = 0;
    while (m_data[index].filled && (numprobes < m_capacity)) {
        if (m_data[index].key == key) {
            break;
        }
        index = (index + 1) % m_capacity;
            numprobes += 1;
    }
    if (numprobes == m_capacity) {
        throw std::logic_error("Too many probes in HashDictionary::remove");
    }
    //we should now have found the index to be removed.

    m_data[index].filled = false;

    m_size--;



}

template <typename KeyType, typename ValueType, typename HashType>
void HashDictionary<KeyType, ValueType, HashType>::clear() {
    
    m_size = 0;
    for (std::size_t i = 0; i < m_capacity; ++i) {
        m_data[i].filled = false;
    }
}

template <typename KeyType, typename ValueType, typename HashType>
ValueType
HashDictionary<KeyType, ValueType, HashType>::get(const KeyType &key) const
{
    
    // hash the key
    std::size_t index = m_hash(key) % m_capacity;
    
    // do linear probing
    std::size_t numprobes = 0;
    while (m_data[index].filled && (numprobes < m_capacity)) {
        if (m_data[index].key == key) {
            break;
        }
        index = (index + 1) % m_capacity;
        numprobes += 1;
    }
    if (numprobes == m_capacity) {
        throw std::logic_error("Too many probes in HashDictionary::get");
    }
    
    if (!m_data[index].filled) {
        throw std::logic_error("Nonexistant key in HashDictionary::get");
    }
    
    return m_data[index].value;
}

template <typename KeyType, typename ValueType, typename HashType>
bool HashDictionary<KeyType, ValueType, HashType>::contains(
                                                            const KeyType &key) const
{
    // hash the key
    std::size_t index = m_hash(key) % m_capacity;
    
    // do linear probing
    std::size_t numprobes = 0;
    while (m_data[index].filled && (numprobes < m_capacity)) {
        if (m_data[index].key == key) {
            break;
        }
        index = (index + 1) % m_capacity;
        numprobes += 1;
    }
    if (numprobes == m_capacity) {
        throw std::logic_error("Too many probes in HashDictionary::contains");
    }
    
    return m_data[index].filled;
}
