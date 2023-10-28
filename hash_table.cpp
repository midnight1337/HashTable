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
//*m_hash_array[hashed_key] is same as **(m_offset + hashed_key)

*******************************************************************************/

#include <iostream>
#include <stdexcept>


#define CAPACITY 100 // Size of the HashTable.


class HashTable
{
    private:
        int** m_hash_array;
        int** m_offset;
        int m_size;
        void allocate_memory();
        
        
    public:
        HashTable();
        ~HashTable() = default;
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
    allocate_memory();
    m_offset = &(*(m_hash_array + 0));   // or simply m_offset = m_hash_array
    m_size = 0;
};

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

int main()
{
    char key_1[] = "abc";
    int value_1 = 1;
    
    char key_2[] = "test";
    int value_2 = 2;
    
    HashTable hash_table = HashTable();
    
    hash_table.insert(key_1, value_1);
    
    hash_table.insert(key_2, value_2);
    
    //hash_table.erase();
    hash_table.remove(key_1);
    
    hash_table.item_info(key_1);
    hash_table.item_info(key_2);
    
    
    std::cout << hash_table.get(key_1) << std::endl;
    std::cout << hash_table.get(key_2) << std::endl;

    return 0;
}
