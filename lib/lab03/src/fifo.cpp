#include "fifo.h"
#include <iostream>
namespace lab3{
    fifo::fifo() {
    //Reserve 100 spaces in fifo_storage
        fifo_storage = lab2::stringVector(100);
        front_index=back_index=-1;
    }

    fifo::fifo(std::string input_string) {
        fifo_storage = lab2::stringVector(100);
        front_index=back_index=-1;
        enqueue(input_string);
    }

    fifo::fifo(const fifo &original) {
       // std::cout<<"Copy Const:"<<original.fifo_storage.size()<<"  ";
        fifo_storage = original.fifo_storage;
        front_index = original.front_index;
        back_index=original.back_index;
    }

    fifo::~fifo() {

    }

    fifo &fifo::operator=(const fifo &right) {
        //return <#initializer#>;

        fifo_storage = right.fifo_storage;
        front_index = right.front_index;
        back_index = right.back_index;
        return *this;
    }

    bool fifo::is_empty(){
        if(size() ==0) return true;
        else return false;
    }

    int fifo::size(){
        //if(front_index > back_index) return back_index-front_index;
        if (back_index ==-1 && front_index == -1) return 0;
        else if (back_index == front_index) return 1;
        else return back_index-front_index+1;
    }

    std::string fifo::front(){
        if(!is_empty()){
            //std::cout<<"From Fifo.cpp Line 46:"<<front_index<<"|"<<fifo_storage[front_index]<<" \n";
            return fifo_storage[front_index];
        }

        else
            throw std::out_of_range("Queue is Empty");
    }
    std::string fifo::rear(){
        if(!is_empty())
            return fifo_storage[back_index];
        else
            throw std::out_of_range("Queue is Empty");
    }

    void fifo::enqueue(std::string input) {
        if(back_index == 99)  throw std::out_of_range("Queue is Full");
        else
        {
            if(front_index == -1) front_index =0;
            back_index++;
            fifo_storage.append(input);
        }

    }



    void fifo::dequeue() {
        if(is_empty()) throw std::out_of_range("Queue is Empty");
        else {
            if(front_index == back_index) front_index=back_index=-1;
            else front_index++;
        }

    }
}