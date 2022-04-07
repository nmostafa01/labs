#include "lifo.h"
#include <stdexcept>
#include <iostream>
namespace lab3{
    lifo::lifo() {
    //Reserve 100 spaces in lifo_storage
        lifo_storage = lab2::stringVector(100);
        index = 0;
    }

    lifo::lifo(std::string input_string) {
        lifo_storage = lab2::stringVector(100);
        lifo_storage.append(input_string);
        index++;
    }

    lifo &lifo::operator=(const lifo &original) {
        lifo_storage = original.lifo_storage;
        index = original.index;
        return *this;
    }

    lifo::~lifo() {
        
    }


    bool lifo::is_empty(){
        return index == 0;
    }

    int lifo::size(){
        return index;
    }

    std::string lifo::top(){
        //std::cout<<"lifo.cpp Line 44:"<<lifo_storage[lifo_storage.size()-1]<<std::endl;
        //if
        return lifo_storage[index-1];

    }

    void lifo::push(std::string input) {
        if(index > 100) throw std::out_of_range("Stack is Full");
        if(index ==0) {
            lifo_storage.insert(0,input) ;
            index++;
        }
        else{
            lifo_storage.insert(index,input);
            index++;
        }


    }

    void lifo::pop() {
        if(!is_empty()){
            --index;
        }
        else{
            throw std::out_of_range("Stack is Empty");
        }

    }
}