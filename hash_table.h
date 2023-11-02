/******************************************************************************

element_address = offset + element_index
offset - memory address of a first element of an array (or just memory address of an array itself)


Hash table:
Hash Table contains a array of pointers
Every pointer points to specific location of arrays of primitve types like: string, int, char etc.
Pointer is integer number, which always take up the same amount of space, so type of data of pointed variable is not important for managing Hash table array.

Hash tables get their name from a trick called hashing, 
which lets them translate an arbitrary key into an integer number that can work as an index in a regular array.
It lets user's search for a thing in array by it's name (key) instead of an index.


HashTable array should be dynamic (stl)

Dereference value
// m_hash_array[hashed_key] is same as (m_offset + hashed_key)

*******************************************************************************/
#include <iostream>
#include <stdexcept>


#define CAPACITY 100 // Size of the HashTable.


class HashTable
{
    private:
        // hash_array holds pointers, that points to any place in memory
        int** m_hash_array;
        int** m_offset;
        int m_size;
        void allocate_memory();
        
    public:
        HashTable();
        ~HashTable() = default;
        int hash(char* key);
        int get(char* key);
        void insert(char* key, int value); // put key and value in array, overload for any type of value
        void remove(char* key);
        void erase();
        void item_info(char* key);
};