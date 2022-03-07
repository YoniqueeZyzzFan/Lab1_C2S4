#include <iostream>
#include "Set.cpp"

int main()
{
    AvlTree at;
    at.insert(30);
    at.insert(15);
    at.insert(14);
    at.insert(52);
    at.insert(-30);
    at.insert(-42);
    AvlTree bt(at);
    at.erase(30);
    bt.treeprint();
    AvlTree ct = bt;
    //at.treeprint();
    AvlTree::MyIterator it = at.begin();
    std::cout << "_____________";
    std::cout << *(it);
    std::cout << "_____________";
    std::cout << *(++it);
    std::cout << "_____________";
    std::cout << *(++it);
    std::cout << "_____________";
    std::cout << *(++it);
}
