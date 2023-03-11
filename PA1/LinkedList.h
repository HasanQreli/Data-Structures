#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    int size;
};

template<class T>
LinkedList<T>::LinkedList()
{
    /* TODO */
    size=0;
    head=NULL;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj)
{
    /* TODO */
    if(&obj == this){
        return;
    }
    size=0;
    head=NULL;

    Node<T> *curr1 = obj.head;
    for(int i=0; i<obj.size; i++){
        append(curr1->data);
        curr1 = curr1->next;
    }
    
}

template<class T>
LinkedList<T>::~LinkedList()
{
    /* TODO */
    removeAllNodes();
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    /* TODO */
    if(this == &rhs){
        return *this;
    }
    removeAllNodes();
    Node<T> *curr1 = rhs.head;
    for(int i=0; i<rhs.size; i++){
        append(curr1->data);
        curr1 = curr1->next;
    }
    return *this;
}

template<class T>
int LinkedList<T>::getSize() const
{
    /* TODO */
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    /* TODO */
    if(size==0) return true;
    return false;
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    /* TODO */
    Node<T> *curr1 = head;
    for(int i=0; i<size; i++){
        if(curr1==node){
            return true;
        }
        curr1 = curr1->next;
    }
    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    /* TODO */
    if(isEmpty()) return NULL;
    return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    /* TODO */
    if(isEmpty()) return NULL;
    return head->prev;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    /* TODO */
    Node<T> *curr1 = head;
    for(int i=0; i<size; i++){
        if(curr1->data == data){
            return curr1;
        }
        curr1 = curr1->next;
    }
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    /* TODO */
    Node<T> *curr1 = head;
    if(index > size-1 || index < 0){
        return NULL;
    }
    for(int i=0; i<index; i++){
        
        curr1 = curr1->next;
    }
    return curr1;
}

template<class T>
void LinkedList<T>::append(const T &data)
{
    /* TODO */
    Node<T> *node = new Node<T>(data);
    if(size==0){
        head = node;
        node->next = head;
        node->prev = head;
    }
    else{
        node->next = head;
        node->prev = head->prev;
        head->prev->next = node;
        head->prev = node;
    }
    size++;
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    /* TODO */
    Node<T> *node = new Node<T>(data, NULL, NULL);
    if(size==0){
        head = node;
        node->next = head;
        node->prev = head;
    }
    else{
        Node<T> *last = head->prev;
        head->prev = node;
        node->next = head;
        node->prev = last;
        last->next = node;
        head=node;
    }
    size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    /* TODO */
    if(getIndex(node) == -1){
        return;
    }
    insertAtIndex(data, getIndex(node)+1);
}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    /* TODO */
    
    if(index > size || index < 0){
        return;
    }
    if(index==0){
        prepend(data);
        
    }
    else{
        
        Node<T> *curr = head;
        
        Node<T> *node = new Node<T>(data);
        for(int i=0; i<index; i++){
            curr = curr->next;
            
        }
        curr->prev->next = node;
        node->prev = curr->prev;
        node->next = curr;
        curr->prev = node;
    
        size++;
    }
    
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    /* TODO */
    Node<T> *curr1 = head;
    for(int i=0; i<size; i++){
        if(curr1==node){
            return i;
        }
        curr1 = curr1->next;
    }
    return -1;
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    /* TODO */
    Node<T> *node = getNodeAtIndex(currentIndex);
    if(newIndex >= size){
	    newIndex = size-1;
	}
    if(currentIndex >= size || currentIndex == newIndex || size == 0 || size == 1 || newIndex < 0 || node == NULL)
        return;

	node->prev->next = node->next;
	node->next->prev = node->prev;
	size--;
	if(currentIndex == 0){
	    head = node->next;
	}

	
	if(newIndex==0){
	    node->next = head;
	    node->prev = head->prev;
	    head->prev->next = node;
	    head->prev = node;
	    
	    head = node;
	    size++;
	}
	else{
	    
	    Node<T> *curr = head;
	    
	    for(int i=0; i<newIndex; i++){
			curr = curr->next;
		
	    }
	    curr->prev->next = node;
	    node->prev = curr->prev;
	    node->next = curr;
	    curr->prev = node;

	    size++;
	}
    
    
}  

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    /* TODO */
    
    if(node!=NULL && containsNode(node)){
        Node<T> *curr = head;
        if(size == 1){
            delete node;
            head = NULL;
        }
        else if(getIndex(node) == 0){
            Node<T> *tmp = head->next;
            head->prev->next = head->next;
            head->next->prev = head->prev;
            delete head;
            head = tmp;
            
        }
        else{
            for(int i=0; i<getIndex(node); i++){
                curr = curr->next;
            }
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            delete curr;
        }
        size--;
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{
    /* TODO */
    while(containsNode(getNode(data)))
        removeNode(getNode(data));
    
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    /* TODO */
    removeNode(getNodeAtIndex(index));
    
    
}

template<class T>
void LinkedList<T>::removeAllNodes()
{
    if(!isEmpty()){
        while (head->next != head)
    	{
    		Node<T>* p = head->next;
    		p->next->prev = head;
    		head->next = p->next;
    		delete p;
    	}
    	delete head;
    }
    size = 0;
    
}

template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    do {
        std::cout << *node << std::endl;
        node = node->next;
    }
    while (node != this->getFirstNode());
}

#endif //LINKEDLIST_H

