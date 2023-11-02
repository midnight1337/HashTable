#include <iostream>

class Node
{
    public:
        Node() = default;
        int data;
        Node* link;

        Node& memory();
};
