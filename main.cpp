#include <iostream>

#include "bst.h"

int main(int, char**) {
    
    int array[] = { 10,8, 45, 34, 12, 1, 7, 55, 9, 3 };
    int size = sizeof(array) / sizeof(int);
    BST<int> bst;


    for (int i = 0; i < size; i++) {
        bst.insert(array[i]);
    }

    std::cout << "Imprimindo a arvore:" << std::endl;
    bst.print();

    std::cout << " Removendo o 8..." << std::endl;
    bst.remove(8);

    std::cout << "Imprimindo a arvore:" << std::endl;
    bst.print();


    return 0;

}
