#ifndef SORTED_LIST_H
#define SORTED_LIST_H
#include "sortedList.h"
#include <iostream>
#include <stdexcept>
#include <algorithm> 

namespace mtm {
    template <class T>
    class SortedList {
    private:
        struct Node {
            T item;
            struct Node* next;
        };
        Node* first_node;
        int len;
        SortedList& concatinate_list(const SortedList& list2);
        void clear();

    public:
        SortedList();
        ~SortedList();
        SortedList(const SortedList&);
        SortedList& operator=(const SortedList&);

        template <class Predicate>
        SortedList filter(Predicate function);
        template <class function>
        SortedList apply(function func);

        class const_iterator;
        const_iterator begin() const;
        const_iterator end() const;

        void insert(const T& element);
        void remove(const_iterator it);
        int length() const;
    };


    template <class T>
    class SortedList<T>::const_iterator {
    private:
        const SortedList<T>* sorted_list;
        int index;
        const_iterator(const SortedList<T>* sorted_list, int index);
        Node* getNodePtr();
        friend class SortedList;

    public:
        const_iterator(const const_iterator&) = default;
        const_iterator& operator=(const const_iterator&) = default;
        ~const_iterator() = default;
        const_iterator& operator++();
        bool operator==(const const_iterator&) const;
        const T& operator*();
    };

    ////////////////////// filter and apply ///////////////////

    template <class T>
    template <class Predicate>
    SortedList<T> SortedList<T>::filter(Predicate function){
        SortedList sorted_list_filter= SortedList();
        for(const_iterator i=this->begin(); !(i==this->end()); ++i){
            if(function(*i)){
                sorted_list_filter.insert(*i);
            }
        }
        return sorted_list_filter;
    }


    template <class T>
    template <class function>
    SortedList<T> SortedList<T>::apply(function func) {
        SortedList sorted_list_apply= SortedList();
        for(const_iterator i = this->begin(); (!(i==this->end())); ++i){
            T returned_value=func(*i);
            sorted_list_apply.insert(returned_value);
        }
        return sorted_list_apply;
    }


    ///////////////////// const_iterator ///////////////////
    template <class T>
    SortedList<T>::const_iterator::const_iterator(const SortedList* sorted_list, int index) :
        sorted_list(sorted_list), index(index) {}


    template <class T>
    typename SortedList<T>::Node* SortedList<T>::const_iterator::getNodePtr() {
        Node* current_node = this->sorted_list->first_node;
        for (int j=0; j<this->index; j++) {
            current_node = current_node->next; 
        }
        return current_node;
    }

    template <class T>
    typename SortedList<T>::const_iterator& SortedList<T>::const_iterator::operator++() {
        if (this->index > this->sorted_list->len) { 
            throw std::out_of_range("bla");
        }
        this->index++; 
        return *this;
    }

    template <class T>
    bool SortedList<T>::const_iterator::operator==(const SortedList::const_iterator& it) const {
        return this->index == it.index;
    }

    template <class T>
    const T& SortedList<T>::const_iterator::operator*() {
        return this->getNodePtr()->item;
    }

    ///////////////////////////////////////////////////////////////////
    template <class T>
    SortedList<T>& SortedList<T>::concatinate_list(const SortedList<T>& list2) {
        const_iterator i = list2.begin();
        while(!(i==list2.end())){ 
            this->insert(*i);
            ++i;
        }
        return *this;
    }


    template <class T>
    void SortedList<T>::clear() {
        while (this->len>0) {
            this->remove(const_iterator(this, ((this->len)-1)));
        }
    }

    template <class T>
    SortedList<T>::SortedList() :first_node(NULL),len(0){}

    template <class T>
    SortedList<T>::~SortedList() {
        this->clear();
    }

    template <class T>
    SortedList<T>::SortedList(const SortedList& sorted_list_original) :
        first_node(NULL), len(0) {
        this->concatinate_list(sorted_list_original);
    }


    template <class T>
    SortedList<T>& SortedList<T>::operator=(const SortedList<T>& sorted_list_original) {
        if (this == &sorted_list_original){
            return *this;
        }
        this->clear(); 
        this->concatinate_list(sorted_list_original);
        this->len=sorted_list_original.len;
        return *this;
    }

    template <class T>
    typename SortedList<T>::const_iterator SortedList<T>::begin() const {
        return const_iterator(this, 0);
    }

    template <class T>
    typename SortedList<T>::const_iterator SortedList<T>::end() const {
        return const_iterator(this, (this->len));
    }


    template <class T>
    void SortedList<T>::remove(const_iterator it) {
        this->len--;
        Node* node =  it.getNodePtr();
        if (node == this->first_node) {
            this->first_node = node->next; 
        }   
          else { 
            const_iterator(this, it.index-1).getNodePtr()->next = node->next;
          }
          delete node;
    }

    /////////////////////////////////////// insert and length //////////////////////////////////////

    template <class T>
    int SortedList<T>::length() const {
        return this->len;
    }

    template <class T>
    void SortedList<T>::insert(const T& element) {
        Node* new_node = new Node;
        new_node->item = element;
        if (this->len == 0) {
            new_node->next = NULL;
            this->first_node = new_node;
            this->len++;
            return;
        }

        const_iterator i = this->begin();
        for(int counter=0; counter<len; counter++) {

            if (element < *i) {
                this->len++;
                if (i==this->begin()) {
                    new_node->next = i.getNodePtr();
                    this->first_node = new_node;
                    return;
                }
                new_node->next = i.getNodePtr();
                const_iterator(this, i.index-1).getNodePtr()->next = new_node;
                return;
            }
            if (!(counter==len-1)) { 
                ++i;
            }
        }
        new_node->next = NULL;
        i.getNodePtr()->next = new_node;
        this->len++;
    }
}
#endif // SORTED_LIST_H
