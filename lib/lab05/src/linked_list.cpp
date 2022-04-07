#include <linked_list.h>
#include <stdexcept>
namespace lab5 {
    linked_list::linked_list() {
        head = tail = nullptr;
    }

    linked_list::linked_list(std::string &data) {
        lab5::node n = lab5::node(data);
        head = tail = &n;

    }

    linked_list::linked_list(const linked_list &original) {
        head = original.head;
        tail = original.tail;

    }

    linked_list::~linked_list() {

    }

    linked_list &lab5::linked_list::operator=(const linked_list &RHS) {
        //return <#initializer#>;
    }


    bool linked_list::isEmpty() const {
        if(head == nullptr && tail == nullptr) return true;
        else return false;
    }

    unsigned linked_list::listSize() const {
        if(isEmpty()) return 0;
        else{
            int size = 0;
            node *temp_ptr = head;
            while (temp_ptr != nullptr) {
                temp_ptr = temp_ptr->next;
                size++;
            }
            return size;
        }
    }

    void linked_list::insert(const std::string input, unsigned int location) {
        lab5::node newNode = lab5::node(input);
        if(location<1){
           throw std::out_of_range("Invalid position");
        }
        else if (location == 1){
            newNode.next = head;
            head = &newNode;
        }
        else{
            node* temp = head;
            for(int i = 1; i < location-1; i++) {
                if(temp != nullptr) {
                    temp = temp->next;
                }
            }

            if(temp != NULL) {
                newNode.next = temp->next;
                temp->next = &newNode;
            } else {
                throw std::bad_exception();
            }

        }

    }

    void linked_list::append(const std::string input) {
        lab5::node newNode = lab5::node(input);
        if(listSize()>0){
            tail->next = &newNode;
            tail = &newNode;
        }
        else{
            head = tail = &newNode;
        }

    }

    void linked_list::remove(unsigned location) {
        if (head == nullptr) return;
        lab5::node *temp = head;
        if(location == 0){
            head = temp->next;
            free(temp);
            return;
        }
        for (int i = 0; temp != nullptr && i < location - 1; i++)
            temp = temp->next;
        if (temp == nullptr || temp->next == nullptr)
            return;
        node* next = temp->next->next;
        free(temp->next);
        temp->next = next;
    }

    std::ostream& operator<<(std::ostream &stream, linked_list &RHS) {
        return stream;
    }

    std::istream& operator>>(std::istream &stream, linked_list &RHS) {
        return stream;
    }

    void linked_list::sort() {

    }

    std::string linked_list::get_value_at(unsigned location) {
        if(location>listSize()) {
            throw std::out_of_range("Invalid Location. Location is greater than size of the list.");
        }
        else{
            node* current = head;
            int count = 0;
            while (current != nullptr) {
                if (count == location)
                    return (current->data);
                count++;
                current = current->next;
            }
        }
    }
}