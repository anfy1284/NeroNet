
#include <iostream>
#include "headers\queue.h"

int main()
{
    std::cout << "Hello World" << std::endl;

    Queue<int> myQueue;
    
    myQueue.addAtFirst(1);
    myQueue.addAtFirst(2);
    myQueue.addAtFirst(3);

    Queue<int>::Selection *selection = myQueue.select();

    while (selection->next())
    {
        int n = selection->get();
        // printf("%n", n);
    }
 
}