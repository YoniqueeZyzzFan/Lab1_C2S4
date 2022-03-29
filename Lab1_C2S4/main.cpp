#include <iostream>
#include <chrono>
#include "Set.cpp"

int main()
{
    AvlTree<int> at;
    at.insert(15);
    at.insert(-65);
    at.insert(15);
    at.insert(65);
    at.insert(-5);
    at.insert(31);
    at.insert(104);
    at.insert(-15);
    at.insert(-150);
    at.insert(16);
    at.treeprint();
    std::cout << "___________________________" << std::endl;
    for (auto it = at.begin(); it != at.end(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout << "___________________________" << std::endl;
    for (auto it = at.rbegin(); it != at.rend(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout << "___________________________" << std::endl;
    at.erase(15);
    at.treeprint();

    // Test time

   /* setlocale(LC_ALL, "");
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100000; ++j) {
            at.insert(i * 100000 + j);
        }
        auto start = std::chrono::steady_clock::now();
        at.insert(i * (-1));
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::nano > elapsed_seconds = end - start;
        std::cout << "Итерация - " << i << " - Вставлено 1000000 элементов" << std::endl;
        std::cout << "Времени потребовалось: " << elapsed_seconds.count() << std::endl;
    }*/
}
