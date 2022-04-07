#ifndef CMPE126EXAM1_TUESDAY_NODE_H
#define CMPE126EXAM1_TUESDAY_NODE_H

#include <string>
#include "stack.h"

class inventory_node{
public:
    inventory_node* next;

    int upc;
    std::string name;
    int inventory_count;
    stack price;

    inventory_node(int upc, std::string name, int count, int price, int date);
    ~inventory_node();
};

#endif