
#include <iostream>
#include "MyVector.h"
int main()
{
    MyVector<int> vec(10);

    for (int i = 0; i < vec.size(); i++) {
        vec.push_back(i);
    }

    for (MyVector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
        std::cout<<*it<<" " << std::endl;
    }
    system("pause");

}
