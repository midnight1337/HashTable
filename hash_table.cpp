#include "hash_table.h"


HashTable::HashTable() 
{
    allocate_memory();
    m_offset = &(*(m_hash_array + 0));   // or simply m_offset = m_hash_array
    m_size = 0;
}

void HashTable::allocate_memory()
{
    // dynamicallu allocate CAPACITY size for m_hash_array
    m_hash_array = new int * [CAPACITY];
    
    // Fill it with nullptr which indicates empty space
    for (int i = 0; i < CAPACITY; i++)
    {
        m_hash_array[i] = nullptr;
    }
}

int HashTable::hash(char* key)
{
    // hashing algorithm: char to ascii number
    unsigned long hash = 0;

    for (int j = 0; key[j]; j++)
    {
        hash += key[j];
    }
    
    return hash % CAPACITY;
}

//template
void HashTable::insert(char* key, int value)
{
    int hashed_key = hash(key); // hashed key is an index for value in m_hash_array
    
    int* p_hashed_value = new int(value);   // create on heap variable value and hold a pointer to that memory
    
    m_hash_array[hashed_key] = p_hashed_value;  // Store pointer to the memory of particular value, in array with index as hashed key
    
    m_size++;
}

void HashTable::remove(char* key)
{
    int hashed_key = hash(key);
    
    m_hash_array[hashed_key] = nullptr;
    //*(m_offset + hashed_key) = nullptr;
    
    m_size--;
}

void HashTable::erase()
{
    //FIX ME, I don't work as I should :D
    for (int i = 0; i < CAPACITY; i++)
    {
        delete m_hash_array[i];
    }
    
    delete[] m_hash_array;
    
    // for (auto& item : *m_hash_array)
    // {
    //     item = 0;
    // }
}

void HashTable::item_info(char* key)
{
    int hashed_key = hash(key);
    
    try
    {
        if (m_hash_array[hashed_key] == nullptr)
        {
            throw std::invalid_argument("Key not found in Hash Table, can't provide item info.\n");
        }
        
        std::cout << "Hashed key index: " << hashed_key << std::endl;
        std::cout << "Value address: " << *(m_offset + hashed_key) << std::endl;
        std::cout << "Value: " << **(m_offset + hashed_key) << std::endl;
        std::cout << "m_hash_array[hashed_key]: " << m_hash_array[hashed_key] << std::endl;
        std::cout << "*m_hash_array[hashed_key]: " << *m_hash_array[hashed_key] << std::endl;
        std::cout << "Hash Table size: " << m_size << std::endl;
        std::cout << "---" << std::endl;
    }
    
    catch (std::invalid_argument& e)
    {
        // char error, controls stream buffer, cerr is able to write output to log file
        std::cerr << e.what();
    }
}

int HashTable::get(char* key)
{
    int hashed_key = hash(key);
    
    try
    {
        if (m_hash_array[hashed_key] == nullptr)
        {
            throw std::invalid_argument("Key not found in Hash Table, return -1.\n");
        }
        return *m_hash_array[hashed_key];
        //return **(m_offset + hashed_key);
    }
    
    catch (std::invalid_argument& e)
    {
        std::cerr << e.what();
        return -1;
    }
}
