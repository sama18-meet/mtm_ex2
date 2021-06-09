#include "sortedList.h"

SortedList::SortedList() :
    first_node(NULL), size(0) {
}

SortedList::Iterator::Iterator(const SortedList* sorted_list, int index) :
    sorted_list(sorted_list), index(index) {
}

SortedList::Iterator& SortedList::Iterator::operator++() {
    if (this->index >= this->sorted_list->size - 1) {
        throw std::out_of_range;
    }
    this->index++; 
    return *this;
}


bool SortedList::Iterator::operator==(const SortedList::Iterator& it) const {
    assert(this->sorted_list == it.sorted_list);
    return this->index == it.index;
}


const T& SortedList::Iterator::operator*() {
    <class T>Node* curr_node = this->sorted_list->first_node;
    for (int j=1; j<=this->idx; j++) {
        curr_node = current_node->next; 
    }
    return current_node->item;
}



/*
void SortedList::insert(const T& element) {
    Node* new_node = new Node;
    new_node->item = element;
    Node previous_node = this->first_node;
    for (Node current_node = this->first_node, current_node==NULL, current_node=*(current_node->next)
        if (element < current_node.item) {
            if (current_node == this->first_node) {
                this->first_node = 
            new_node->next = current_node;
            previous_node->next = new_node;
            return;
        }
    }
}
*/
