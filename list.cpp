#define BOOST_TEST_MODULE my_list_test
#define BOOST_TEST_DYN_LINK
#define BOOST_MAIN
#include <boost/test/unit_test.hpp>

template <typename T>
struct my_list {
    struct node {
        my_list<T>::node* next;
        my_list<T>::node* previous;
        T value;

        node(const my_list<T>::node *next, my_list<T>::node const *previous, const T value) {
            this->next = next;
            this->previous = previous;
            this->value = value;
        }

        node(T value) {
            this->next = nullptr;
            this->previous = nullptr;
            this->value = value;
        }

        bool is_first() {
            return (this->previous == nullptr);
        }

        bool is_last() {
            return (this->next == nullptr);
        }
    };

    struct iterator {
        my_list<T>::node *ptr;

        iterator() {
            this->ptr = nullptr;
        }

        iterator(my_list<T>::node *node) {
            this->ptr = node;
        }

        T operator* () const {
            return ptr->value;
        }

        iterator& operator++ () {
            this->ptr = this->ptr->next;
            return (*this);
        }

        iterator operator++ (int) {
            this->ptr = this->ptr->next;
            return (*this);
        }

        iterator operator + (unsigned int offset) {
            my_list<T>::node *shift_ptr = this->ptr;
            while (offset > 0) {
                shift_ptr = shift_ptr->next;
                offset--;
            }
            return my_list<T>::iterator(shift_ptr);
        }

        bool operator != (iterator const& another) {
            return this->ptr != another.ptr;
        }

        bool operator == (iterator const& another) {
            return this->ptr == another.ptr;
        }
    };

    struct

    my_list<T>::node *top;
    my_list<T>::node *bottom;
    size_t length;

    my_list() {
        top = nullptr;
        bottom = nullptr;
        length = 0;
    }

    ~my_list() {
        my_list<T>::node *ptr;
        while (top != bottom) {
            ptr = top->next;
            delete top;
            top = ptr;
        }
    }

    my_list (const my_list<T> &another) {
        top = nullptr;
        bottom = nullptr;
        length = 0;

        for (auto other_ptr = another.begin(); other_ptr != another.end(); other_ptr++) {
            push_back(*other_ptr);
        }
    }

    my_list<T>::iterator begin() const {
        return my_list<T>::iterator(top);
    }

    my_list<T>::iterator end() const {
        return my_list<T>::iterator(nullptr);
    }

    void push_back(const T value) {
        my_list<T>::node *new_node = new my_list<T>::node(value);
        new_node->previous = bottom;
        if(length >= 1) {
            bottom->next = new_node;
        }
        else {
            top = new_node;
        }
        bottom = new_node;
        length++;
    }

    T pop_back() {
        T rv = bottom->value;
        bottom = bottom->previous;
        length--;
        if (length == 0) {
            top = nullptr;
        }
        return rv;
    }

    T back() const {
        return bottom->value;
    }

    size_t size() const {
        return length;
    }

    void push_front(const T value) {
        my_list<T>::node *new_node = new my_list<T>::node(value);
        new_node->next = top;
        if(length >= 1) {
            top->previous = new_node;
        }
        else {
            bottom = new_node;
        }
        top = new_node;
        length++;
    }

    T pop_front() {
        T rv = top->value;
        top = top->next;
        length--;
        if (length == 0) {
            bottom = nullptr;
        }
        return rv;
    }

    T front() const {
        return top->value;
    }

    void erase(my_list<T>::iterator first, const my_list<T>::iterator last) {
        while (first != last) {
            if (first == begin()) {
                top = top->next;
            }
            my_list<T>::node *removed = first.ptr;
            first++;
            length--;
            delete removed;
        };
    }

};

BOOST_AUTO_TEST_CASE(list_add_read_test)
{
    my_list<int> lst;
    lst.push_front(42);
    BOOST_CHECK_EQUAL(lst.front(), 42);
}

BOOST_AUTO_TEST_CASE(list_iterator_dereferencing_test)
{
    my_list<int> lst;
    lst.push_front(42);
    auto begin_iterator = lst.begin();
    BOOST_CHECK_EQUAL(*begin_iterator, 42);
}

BOOST_AUTO_TEST_CASE(list_push_erase_test)
{
    my_list<int> lst;
    lst.push_front(2);
    lst.push_front(1);
    auto fst = lst.begin();
    auto snd = fst + 1;

    lst.erase(fst, snd);
    BOOST_CHECK_EQUAL(lst.size(), 1);
    BOOST_CHECK_EQUAL(lst.front(), 2);
    BOOST_CHECK_EQUAL(lst.back(), 2);
}

BOOST_AUTO_TEST_CASE(list_pop_back_test)
{
    my_list<int> lst;
    lst.push_front(2);
    lst.push_front(1);
    BOOST_CHECK_EQUAL(lst.pop_back(), 2);
    BOOST_CHECK_EQUAL(lst.pop_back(), 1);
    BOOST_CHECK_EQUAL(lst.size(), 0);

    lst.push_back(4);
    lst.push_back(3);
    BOOST_CHECK_EQUAL(lst.pop_front(), 4);
    BOOST_CHECK_EQUAL(lst.pop_front(), 3);
    BOOST_CHECK_EQUAL(lst.size(), 0);
}

BOOST_AUTO_TEST_CASE(list_copying_test)
{
    my_list<int> lst1;
    lst1.push_front(1);
    lst1.push_front(0);
    my_list<int> lst2 = lst1;
    BOOST_CHECK_EQUAL(lst1.front(), lst2.front());
}
