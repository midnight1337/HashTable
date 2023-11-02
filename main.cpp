#include <iostream>
#include "hash_table.cpp"


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
