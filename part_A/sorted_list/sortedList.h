
typedef int T;

template <class T>
struct Node {
    T item;
    struct Node* next;
};


template <class T>
class SortedList {
private:
    <T>Node* first_node;
    int size;

public:
    SortedList();
    ~SortedList();
    SortedList(const SortedList&);
    SortedList& operator=(const SortedList&); 
    void insert(const T& element);
    void remove // continue
    int length();

    class Iterator;
    const_iterator begin() const;
    const_iterator end() const;

}

class SortedList::Iterator {
private:
    const SortedList* sorted_list;
    int index;
    Iterator(const SortedList* sorted_list, int index);
    friend class SortedList;

public:
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;
    ~Iterator() = default;
    Iterator& operator++();
    bool operator==(const Iterator&) const;
    const T& operator*();

}
