#include <iostream>
#include <time.h>
#include <string>
#include "Set.cpp"

int main()
{
    //Test int
    AvlTree<int> at;
    at.insert(123);
    at.insert(100);
    at.insert(300);
    at.insert(13235);
    at.insert(400);
    at.treeprint();
    auto it = at.rbegin();
    while(it!=at.rend()){
        std::cout << *it << std::endl;
    ++it;
    }


    // Test string

   /* AvlTree<std::string> at;
    at.insert("Privet");
    at.insert("PrivetPrivet");
    at.insert("Hi");
    at.treeprint();*/

    // Test time

   /* setlocale(LC_ALL, "");
    AvlTree<int> at;
    clock_t start, end;
    for (int i = 0; i < 100000; ++i) {
        start = clock();
        for (int j = 0; j < 10000000; ++j) {
            at.insert(i + j + 3);
        }
        end = clock();
        double temp = ((double)end - start) / ((double)CLOCKS_PER_SEC);
        std::cout << "Итерация - " << i << " - Вставлено 10000000 элементов" << std::endl;
        std::cout << "Времени потребовалось: " << temp << std::endl;
    }*/
}
