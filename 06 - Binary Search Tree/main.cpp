#include <iostream>

#include "bin_tree.h"

void printer(int value)
{
    std::cout << value << " ";
}

int main()
{
    // Vlastiti testovi

    BinarySTree<int> B;
        
    std::cout<< B.insert(6) <<std::endl;
    std::cout<< B.insert(7) <<std::endl;
    std::cout<< B.insert(6) <<std::endl;
    std::cout<< B.insert(2) <<std::endl;

    B.insert(10);
    B.insert(8);

    std::cout << B.empty() << std::endl;

    std::cout << B.isInTree(11) << std::endl;

    B.insert(1);

    std::cout << B.size() << std::endl;

    B.insert(4);
    B.insert(3);
    
    B.preOrder(printer);
    std::cout << std::endl << std::endl;
    B.postOrder(printer);
    std::cout << std::endl << std::endl;

    std::cout << B.remove(9) << std::endl;
    std::cout << B.remove(2) << std::endl;
    B.remove(2);
    B.remove(7);

    B.preOrder(printer);
    std::cout << std::endl << std::endl;

    B.remove(8);
    B.clear();                // clear se poziva u destruktoru, a moze se pozivati i iz glavnog programa
    std::cout << B.empty() << std::endl;

    return 0;
}