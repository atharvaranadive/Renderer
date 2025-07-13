#include <vector>
#include <iostream>

int main(void){
    std::cout << "Hello world" << std::endl;

    std::vector<int> test;
    test.push_back(10);
    test.push_back(15);
    for(auto i : test){
        std::cout << i << std::endl;
    }

}