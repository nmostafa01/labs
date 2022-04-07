#include <iostream>
#include "lib/lab01/inc/expressionstream.h"
int main() {
    std::cout << "Hello Thursday everyone!";
    lab1::expressionstream es = lab1::expressionstream("1+2+3");
    //std::cout<<es.get_next_token();
    return 0;
}