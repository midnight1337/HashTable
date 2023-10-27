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

Dereference value
//*m_hash_array[hashed_key] is same as **(m_offset + hashed_key)

*******************************************************************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>


#define CAPACITY 100 // Size of the HashTable.


class HashTable
{
    private:
        int* m_hash_array[CAPACITY];
        int** m_offset;   // memory address of an pointers array
        int m_size;
        
        
    public:
        HashTable();
        int hash(char* key);
        int get(char* key);
        int size();
        void insert(char* key, int value); // put key and value in array, overload for any type of value
        void remove(char* key);
        void erase();
        void item_info(char* key);
};

HashTable::HashTable() 
{
    m_offset = &(*(m_hash_array + 0));   // or simply m_offset = m_hash_array
    m_size = 0;
};

int HashTable::hash(char* key)
{
    // defined hashing algorithm, char to ascii number
    unsigned long hash = 0;

    for (int j = 0; key[j]; j++)
    {
        hash += key[j];
    }
    
    return hash % CAPACITY;
}

void HashTable::insert(char* key, int value)
{
    int hashed_key = hash(key); // hashed key is an index, 94
    
    int* p_hashed_key = new int(hashed_key);    // use malloc()??
    int* p_hashed_value = new int(value);
    
    m_hash_array[hashed_key] = p_hashed_value;
    
    m_size++;
}

void HashTable::remove(char* key)
{
    int hashed_key = hash(key);

    //free(m_hash_array[hashed_key]);   // use free if malloc was called
    delete m_hash_array[hashed_key];

    **(m_offset + hashed_key) = 0;
    
    m_size--;
}

void HashTable::erase()
{
    // for (auto& item : *m_hash_array)
    // {
    //     item = 0;
    // }
}

void HashTable::item_info(char* key)
{
    int hashed_key = hash(key);

    if (*m_hash_array[hashed_key] == 0) {return;}

    std::cout << "Hashed key index: " << hashed_key << std::endl;
    std::cout << "Key: " << "UNHASH ASCII" << std::endl;
    std::cout << "Value address: " << *(m_offset + hashed_key) << std::endl;
    std::cout << "Value: " << **(m_offset + hashed_key) << std::endl;
    std::cout << "Hash Table size: " << m_size << std::endl;
    std::cout << "---" << std::endl;
}

int HashTable::get(char* key)
{
    int hashed_key = hash(key);
    
    return **(m_offset + hashed_key);
}

int main()
{
    char key_1[] = "abc";
    int value_1 = 1;
    
    char key_2[] = "test";
    int value_2 = 2;
    
    HashTable hash_table = HashTable();
    
    hash_table.insert(key_1, value_1);
    
    hash_table.erase();
    
    hash_table.insert(key_2, value_2);
    
    //hash_table.erase();
    hash_table.remove(key_1);
    
    hash_table.item_info(key_1);
    hash_table.item_info(key_2);
    
    std::cout << hash_table.get(key_1) << std::endl;
    std::cout << hash_table.get(key_2) << std::endl;
    
    return 0;
}
