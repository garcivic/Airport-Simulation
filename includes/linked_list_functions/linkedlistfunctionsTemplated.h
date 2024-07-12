#ifndef LINKED_LIST_FUNCTIONSTEMPLATED_H
#define LINKED_LIST_FUNCTIONSTEMPLATED_H
#include <iostream>

using namespace std;
#include "../node/node.h"

//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head);

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head);

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head,
                            T key);


template <typename T>
node<T>* _insert_head(node<T> *&head,
                            T insert_this);

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head,
                                node<T> *after_this,
                                T insert_this);

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head,
                                node<T>* before_this,
                                T insert_this);

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this);

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this);

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head);

//duplicate the list, return pointer to last node in dest... 
//     use this function in your queue big three 
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src);



//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head);

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos);

template <typename T> void _print_list(node<T>* head)
{
    cout << "HEAD->";
    for (node<T>* walker = head; walker != nullptr; walker = walker->_next)
        cout << *walker; 
    cout << "||\n";
}
//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head)
{
    node<T>* walker = head;

    cout << "||";
    
    while ( walker->_next != nullptr )
        walker = walker->_next;
    
    while (walker != head)
    {
        cout << *walker;
        walker = walker->_prev;
    }
        
    cout << *walker << "<-HEAD\n";
}
//return ptr to key or NULL
template <typename T> node<T>* _search_list(node<T>* head, T key)
{
    node<T>* walker = head;
    for (node<T>* walker = head; walker != nullptr; walker = walker->_next)
    {
        if (walker->_item == key)
            return walker;
    }
    return nullptr;
}
template <typename T> node<T>* _insert_head(node<T> *&head, T insert_this)
{
    node<T>* newNode = new node<T>(insert_this);
    if (head != nullptr)
    {
        newNode->_prev = nullptr;
        newNode->_next = head;
        head->_prev = newNode;
    }
    head = newNode;
    
    return head;
}
//insert after ptr: insert head if marker null
template <typename T> node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this)
{
    // assert(after_this != nullptr && "OOPS, tried to insert after a null pointer.\n");
    
    if (head == nullptr)
        return _insert_head(head, insert_this);
    
    node<T>* inserted = new node<T>(insert_this, after_this->_next, after_this);

    // Checks if after_this is @ end of the linked list
    if (after_this->_next != nullptr)
        after_this->_next->_prev = inserted;
    
    after_this->_next = inserted;

    
    return inserted;
}
//insert before ptr: insert head if marker null
template <typename T> node<T>* _insert_before(node<T>*& head,node<T>* before_this, 
T insert_this)
{
    if (head == nullptr)
        return _insert_head<T>(head, insert_this);

    node<T>* inserted = new node<T>(insert_this, before_this, before_this->_next);

    if (before_this->_prev)
        before_this->_prev->_next = inserted;
    
    inserted->_prev = before_this->_prev;

    return inserted;
}
//ptr to previous node
template <typename T> node<T>* _previous_node(node<T>* prev_to_this)
{
    assert(prev_to_this && "TRYING TO ACCES A PREVIOUS NODE TO A NULLPTR!\n");

    return prev_to_this->_prev;
}
//delete, return item
template <typename T> T _delete_node(node<T>*& head, node<T>* delete_this)
{
    assert(
    delete_this != nullptr && "ASSERT CALLED: delete_this node is NULL"
    );

    T deleted_value = delete_this->_item;
    node<T>* found_ptr = _search_list(head, delete_this->_item);

    if(found_ptr == nullptr)
        return -1;
    
    if (delete_this != head)
    {
        node<T>* previous_to_deleted = _previous_node(delete_this);
        node<T>* next_to_deleted = delete_this->_next;

        if (previous_to_deleted)
            previous_to_deleted->_next = next_to_deleted;
        if (next_to_deleted)
            next_to_deleted->_prev = previous_to_deleted;
        
    }
    else
    {   
        delete_this = delete_this->_next;
        if (delete_this)
            delete_this->_prev = nullptr;  
        head = delete_this;
    }
    
    return deleted_value;
    
}
//duplicate the list...
template <typename T> node<T>* _copy_list(node<T>* head) //I THINK ITS DONE!
{
    if (head == nullptr)
        return nullptr;
    
    node<T>* new_list = new node<T>(head->_item), *walker = head,
        *new_list_walker = new_list;
    
    walker = walker->_next;
    for (;walker != nullptr; walker = walker->_next)
    {
        new_list_walker->_next = new node<T>(walker->_item);
        new_list_walker->_prev = new_list_walker;
        new_list_walker = new_list_walker->_next;
    }

    return new_list;
}
//duplicate the list, return pointer to last node in dest... 
//     use this function in your queue big three 
template <typename T> node<T> *_copy_list(node<T> *&dest, node<T> *src) //DONT KNOW IF IT WORKS YET
{
    if (src == nullptr)
        return nullptr;
    
    //create temp variable 
    node<T>* walker = src;
    
    //allocates head of new list(Dest)
    dest = new node<T>(walker->_item);
    //move walker
    walker = walker->_next;

    //iterate through new list
    node<T>* current = dest;

    while (walker != nullptr)
    {
        current->_next = new node<T>(walker->_item);
        
        node<T>* previous = new node<T>(current->_item, current->_next, current->_prev);
        current->_prev = previous->_prev;
        current->_next->_prev = previous;

        current = current->_next;
        walker = walker->_next;
    }
    
    return current;
}
//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head)
{
    node<T>* walker = head;
    T deleted;

    node<T>* temp;

    while (head != nullptr)
    {
        temp = head;
        deleted = _delete_node(head, head);
        temp = temp->_next;
    }
}

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos)
{
    node<T>* walker = head;
    int it = 0;
    while (it != pos)
    {
        walker = walker->_next;
        assert( walker !=  nullptr && "pos given was greater than length of linked list\n");
        it++;
    }
    return walker->_item;
}
#endif //LINKED_LIST_FUNCTIONSTEMPLATED_H