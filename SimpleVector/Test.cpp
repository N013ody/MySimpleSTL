
#include <iostream>
#include "MyVector.h"
#include "MyAllocator.h"
#include <vector>
using namespace std;

int main()
{
    MyVector<int> vec(10);

    for (int i = 0; i < vec.size(); i++) {
        vec.push_back(i);
    }

    for (MyVector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
        std::cout<<*it<<" " << std::endl;
    }

  
    vector<int, MyAllocator<int>> v(0);

    for (size_t i = 0; i < 30; i++)
    {
     
        v.push_back(i);
        std::cout << "Mem :" << v.get_allocator().get_allocations() << std::endl;
    }
    system("pause");

}
