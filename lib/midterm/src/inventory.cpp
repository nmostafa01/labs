#include "../inc/inventory.h"

int inventory::reserve_upc() {
    srand(42);
    auto random_upc_location = int(rand()%upc_generator.size());
    auto a = upc_generator.begin();
    for(auto a = upc_generator.begin(); --random_upc_location != 0; a++);
    while(!a->second && a != upc_generator.end()) a++;
    a->second = false;
    return a->first;
}

void inventory::release_upc(int input_upc) {
    auto val =  upc_generator.find(input_upc);
    if(val->first == input_upc && val->second == false){
        val->second = true;
        return;
    }
    else throw "UPC not valid";
}

bool inventory::valid_upc(int input_upc) {
    if(input_upc == 0) return false;
    auto val = inventory::upc_generator.find(input_upc);
    return val->first == input_upc;
}

void inventory::initialize_upc() {
    srand(17); // Initial seed
    for(int i = 1; i< 1000; i++) {
        int unique_upc = 1000000 + rand() % 9000000;
        inventory::upc_generator.insert(std::pair<int, bool>(unique_upc, true));
    }
}

inventory::inventory() {
    head = nullptr;
    tail = nullptr;
    initialize_upc();
}

inventory::~inventory() {

}

void inventory::add_sku(std::string new_name, int initial_price, int initial_inventory, int initial_date) {


}

void inventory::remove_sku(int input_upc) {

}

std::vector<int> inventory::get_upc(std::string input_name) {


}

int inventory::get_price(int input_upc) {

}

int inventory::get_inventory(int input_upc) {


}

std::string inventory::get_name(int input_upc) {

}

void inventory::adjust_price(int input_upc, int new_price, int new_date) {

}

void inventory::adjust_inventory(int input_upc, int new_inventory) {

}

inventory_node *inventory::get_head() {
    return head;
}

bool inventory::isEmpty() const {
    if((head && !tail) || (!head && tail))throw std::logic_error ("Error head and tail are not both null"); // this should never happen internal error
    return !head;
}