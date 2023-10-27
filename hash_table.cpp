/******************************************************************************

element_address = offset + (element_size + element_index)
offset - memory address of a first element of an array (or just memory address of an array itself)

Hash Table abstract
Hash table contains:
Array of pointers (Pointers are integer numbers, which always take up the same amount of space)
Every pointer points to specific location of arrays of primitve types like
String array, int array, char array etc.

Hash tables get their name from a trick called hashing, 
which lets them translate an arbitrary key into an integer number that can work as an index in a regular array.
So you can search for a thing in array by it's name (key) instead of an index.

HashTable array should be dynamic (stl)

*******************************************************************************/

#include <iostream>


#define CAPACITY 10 // Size of the HashTable.
#define INITIAL_IDX 0  // test index


class HashTable
{
    private:
        int* m_hash_array[CAPACITY];
        int** m_offset;   // memory address of an pointers array
        int m_size;
        
        
    public:
        HashTable();
        int hash(std::string key);
        void insert(std::string key, int value); // put key and value in array, overload for any type of value
        int get(std::string key);
        void print_debug();
};

HashTable::HashTable() 
{
    m_offset = &(*(m_hash_array + 0));   // or simply m_offset = m_hash_array
    m_size = 0;
};

int HashTable::hash(std::string key)
{
    // define hashing algorithm
    int hashed_key = INITIAL_IDX;
    return hashed_key;
}

void HashTable::insert(std::string key, int value)
{
    int hashed_key = hash(key); // hashed key is an index
    
    int* p_hashed_key = new int(hashed_key);
    int* p_hashed_value = new int(value);
    
    m_hash_array[hashed_key] = p_hashed_value;
    
    m_size++;
}

void HashTable::print_debug()
{
    std::cout << m_hash_array[INITIAL_IDX] << std::endl;
    std::cout << *m_hash_array[INITIAL_IDX] << std::endl;
    std::cout << *m_offset << std::endl;
    std::cout << **m_offset << std::endl;
}

int HashTable::get(std::string key)
{
    int hashed_key = hash(key);
    return **(m_offset + hashed_key);
}

int main()
{
    HashTable hash_table = HashTable();
    hash_table.insert("test", 1);
    hash_table.print_debug();
    
    std::cout << hash_table.get("test") << std::endl;

    return 0;
}
