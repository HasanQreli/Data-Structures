#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod { preorder, inorder, postorder };

template<class T>
class ScapegoatTree {
public: // DO NOT CHANGE THIS PART.
    ScapegoatTree();

    ScapegoatTree(const ScapegoatTree<T>& obj);

    ~ScapegoatTree();

    bool isEmpty() const;

    int getHeight() const;

    int getSize() const;

    bool insert(const T& element);

    bool remove(const T& element);

    void removeAllNodes();

    const T& get(const T& element) const;

    void print(TraversalMethod tp = inorder) const;

    void printPretty() const;

    ScapegoatTree<T>& operator=(const ScapegoatTree<T>& rhs);

    void balance();

    const T& getCeiling(const T& element) const;

    const T& getFloor(const T& element) const;

    const T& getMin() const;

    const T& getMax() const;

    const T& getNext(const T& element) const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(Node<T>* node, TraversalMethod tp) const;
    void printPretty(Node<T>* node, int indentLevel, bool isLeftChild) const;
    int getHeight(Node<T>* r) const;
    int getSize(Node<T>* r) const;

    void buildArray(Node<T>*& r, T*& arr, int& i);

    void buildTree(T*& arr, int low, int high, Node<T>*& r);

    Node<T>*& findScapegoat(Node<T>*& r, Node<T>*& c);

    Node<T>*& parent(Node<T>*& r, Node<T>*& c);

    void insert(Node<T>*& r, const T& element);

    bool inTree(Node<T>* r, const T& element) const;

    Node<T>*& getNode(Node<T>*& r, const T& element) const;

    void remove(Node<T>*& r, const T& element);

    void removeAllNodes(Node<T>*& r);

    void copy(Node<T>*& r, Node<T>* c);

    const T& get(Node<T>* r, const T& element) const;
    
    void getCeiling(Node<T>* r, Node<T>*& c, const T& element) const;
    
    void getFloor(Node<T>* r, Node<T>*& c, const T& element) const;

    void getNext(Node<T>* r, Node<T>*& c, const T& element) const;

    Node<T>* getMax(Node<T>* r) const;
    
    Node<T>* getMin(Node<T>* r) const;
    

private: // DO NOT CHANGE THIS PART.
    Node<T>* root;

    int upperBound;
};

#endif //TREE_H

template<class T>
ScapegoatTree<T>::ScapegoatTree() {
    /* TODO */
    root = NULL;
    upperBound = 0;
}

template<class T>
ScapegoatTree<T>::ScapegoatTree(const ScapegoatTree<T>& obj) {
    /* TODO */
    copy(root, obj.root);
    upperBound = obj.upperBound;
}

template<class T>
ScapegoatTree<T>::~ScapegoatTree() {
    /* TODO */
    removeAllNodes();
}

template<class T>
bool ScapegoatTree<T>::isEmpty() const {
    /* TODO */
    return root == NULL;
}

template<class T>
int ScapegoatTree<T>::getHeight() const {
    /* TODO */
    return getHeight(root);
}

template<class T>
int ScapegoatTree<T>::getHeight(Node<T>* r) const {
    /* TODO */
    if (r == NULL) return -1;
    else {
        return 1 + ((getHeight(r->left) > getHeight(r->right)) ? getHeight(r->left) : getHeight(r->right));
    }
}

template<class T>
int ScapegoatTree<T>::getSize() const {
    /* TODO */
    return getSize(root);
}

template<class T>
int ScapegoatTree<T>::getSize(Node<T>* r) const {
    /* TODO */
    if (r == NULL) return 0;
    else {
        return 1 + getSize(r->left) + getSize(r->right);
    }
}

template<class T>
bool ScapegoatTree<T>::insert(const T& element) {
    /* TODO */
    if (inTree(root, element)) return false;
    else {
        insert(root, element);
        upperBound++;
        if (getHeight() * log(1.5) > log(upperBound) ) {
            Node<T>* Scapegoat = findScapegoat(root, getNode(root, element));
            Node<T>* insertHere = parent(root, Scapegoat);
            int cond = 2;
            if(insertHere == Scapegoat){ insertHere == root; cond = 0;}
            else if(insertHere->right == Scapegoat) cond = 1;
            else;
            
            int size = getSize(Scapegoat);
            int i = 0;
            T* arr = new T[size];
            buildArray(Scapegoat, arr, i);
            removeAllNodes(Scapegoat);
            buildTree(arr, 0, size-1, Scapegoat);
            delete[] arr;
            if(cond == 0) insertHere = Scapegoat;
            else if(cond == 1) insertHere->right = Scapegoat;
            else insertHere->left = Scapegoat;
        }
        return true;
    }

}

template<class T>
void ScapegoatTree<T>::buildArray(Node<T>*& r, T*& arr, int& i) {
    if (r == NULL) return;
    else {
        buildArray(r->left, arr, i);
        arr[i] = r->element;
        i++;
        buildArray(r->right, arr, i);
    }
}

template<class T>
void ScapegoatTree<T>::buildTree(T*& arr, int low, int high, Node<T>*& r) {
    if (low > high) return;
    else {
        r = new Node<T>(arr[(high + low) / 2], NULL, NULL);

        buildTree(arr, low, ((high + low) / 2) - 1, r->left);
        buildTree(arr, ((high + low) / 2) + 1, high, r->right);
    }
}

template<class T>
Node<T>*& ScapegoatTree<T>::findScapegoat(Node<T>*& r, Node<T>*& c) {
    if ((getSize(c) * 3)  > (2 * getSize(parent(r,c)))) return parent(r, c);
    else return findScapegoat(r, parent(r, c));
}

template<class T>
Node<T>*& ScapegoatTree<T>::parent(Node<T>*& r, Node<T>*& c) {
    if (r == c) return r; // burda sikinti cikabilir ama Null olursa da sikinti
    else if (r->left == c || r->right == c) return r;
    else if (r->element > c->element) return parent(r->left, c);
    else return parent(r->right, c);
}

template<class T>
void ScapegoatTree<T>::insert(Node<T>*& r, const T& element) {
    /* TODO */
    if (r == NULL) {
        r = new Node<T>(element, NULL, NULL);
    }
    else if (r->element > element) {
        insert(r->left, element);
    }
    else {
        insert(r->right, element);
    }
}

template<class T>
bool ScapegoatTree<T>::inTree(Node<T>* r, const T& element) const {
    if (r == NULL) return false;
    else {
        if (r->element == element) return true;
        else if (r->element > element) return inTree(r->left, element);
        else return inTree(r->right, element);
    }
}

template<class T>
Node<T>*& ScapegoatTree<T>::getNode(Node<T>*& r, const T& element) const {
    if (r->element == element) return r;
    else if (r->element > element) return getNode(r->left, element);
    else return getNode(r->right, element);
}

template<class T>
bool ScapegoatTree<T>::remove(const T& element) {
    /* TODO */
    if (!inTree(root, element)) return false;
    else {
        remove(root, element);
        if(root != NULL && (upperBound > 2*getSize() || getSize() > upperBound)){
            balance();
            upperBound = getSize();
        }
        return true;
    }

}

template<class T>
void ScapegoatTree<T>::remove(Node<T>*& r, const T& element) {

    if (r == NULL)
        return;

    if (element < r->element)
        remove(r->left, element);
    else if (element > r->element)
        remove(r->right, element);
    else {
        if (r->left == NULL && r->right == NULL)
        {
            delete r;
            r = NULL;
        }
        else if (r->left == NULL) {
            Node<T>* temp = r;
            r = r->right;
            delete temp;
            temp = NULL;
        }
        else if (r->right == NULL) {
            Node<T>* temp = r;
            r = r->left;
            delete temp;
            temp = NULL;
        }
        else{
            Node<T>* temp = getMax(r->left);
            // Copy the inorder successor's content to this node
            r->element = temp->element;
    
            // Delete the inorder successor
            remove(r->left, temp->element);
        }
    }
}


template<class T>
void ScapegoatTree<T>::removeAllNodes() {
    /* TODO */
    upperBound = 0;
    removeAllNodes(root);
}

template<class T>
void ScapegoatTree<T>::removeAllNodes(Node<T>*& r) {
    /* TODO */
    if (r == NULL) return;
    else {
        removeAllNodes(r->left);
        removeAllNodes(r->right);
        delete r;
        r = NULL;
    }
}

template<class T>
const T& ScapegoatTree<T>::get(const T& element) const {
    /* TODO */
    
    return get(root, element);
}

template<class T>
const T& ScapegoatTree<T>::get(Node<T>* r, const T& element) const {
    /* TODO */
    if (r == NULL) throw NoSuchItemException();
    else if (r->element == element) return r->element;
    else if (r->element > element) return get(r->left, element);
    else return get(r->right, element);
}

template<class T>
void ScapegoatTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) {
        /* TODO */
        if (isEmpty()) {
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        std::cout << "BST_preorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;

    }
    else if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    }
    else if (tp == postorder) {
        /* TODO */
        if (isEmpty()) {
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        std::cout << "BST_postorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;

    }
}

template<class T>
void ScapegoatTree<T>::print(Node<T>* node, TraversalMethod tp) const {

    if (tp == preorder) {
        /* TODO */
        if (node == NULL)
            return;
        std::cout << "\t" << node->element;

        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);

        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);

    }
    else if (tp == inorder) {
        // check if the node is NULL?
        if (node == NULL)
            return;

        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    }
    else if (tp == postorder) {
        /* TODO */
        if (node == NULL)
            return;


        print(node->left, postorder);

        if (node->left) {
            std::cout << "," << std::endl;
        }


        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }

        std::cout << "\t" << node->element;
    }
}

template<class T>
void ScapegoatTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void ScapegoatTree<T>::printPretty(Node<T>* node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}

template<class T>
ScapegoatTree<T>& ScapegoatTree<T>::operator=(const ScapegoatTree<T>& rhs) {
    /* TODO */
    if (this != &rhs) {
        removeAllNodes();
        copy(root, rhs.root);
        upperBound = rhs.upperBound;
    }
    return *this;
}

template<class T>
void ScapegoatTree<T>::copy(Node<T>*& r, Node<T>* c) {
    if (c == NULL){ r = NULL;return;}
    r = new Node<T>(c->element, NULL, NULL);
    copy(r->left, c->left);
    copy(r->right, c->right);
}

template<class T>
void ScapegoatTree<T>::balance() {
    /* TODO */
    int size = getSize();
    int i = 0;
    T* arr = new T[size];
    buildArray(root, arr, i);
    removeAllNodes(root);
    buildTree(arr, 0, size - 1, root);
    delete[] arr;
}

template<class T>
const T& ScapegoatTree<T>::getCeiling(const T& element) const {
    /* TODO */
    Node<T>* ceiling = NULL;
    
    getCeiling(root, ceiling, element);
    if(!ceiling) throw NoSuchItemException();
    return ceiling->element;
}

template<class T>
void ScapegoatTree<T>::getCeiling(Node<T>* r, Node<T>*& c, const T& element) const {
    /* TODO */
    
    if(r==NULL) return;
    else if(element == r->element) c = r;
    else if(element < r->element){
        c = r;
        getCeiling(r->left, c, element);
    }
    else if(element > r->element){
        getCeiling(r->right, c, element);
    }
    
}

template<class T>
const T& ScapegoatTree<T>::getFloor(const T& element) const {
    /* TODO */
    Node<T>* floor = NULL;
    
    getFloor(root, floor, element);
    if(!floor) throw NoSuchItemException();
    return floor->element;
}

template<class T>
void ScapegoatTree<T>::getFloor(Node<T>* r, Node<T>*& c, const T& element) const {
    /* TODO */
    
    if(r==NULL) return;
    else if(element == r->element) c = r;
    else if(element > r->element){
        c = r;
        getFloor(r->right, c, element);
    }
    else if(element < r->element){
        getFloor(r->left, c, element);
    }
    
}

template<class T>
const T& ScapegoatTree<T>::getMin() const {
    /* TODO */
    if(isEmpty()) throw NoSuchItemException();
    return getMin(root)->element;
}

template<class T>
Node<T>* ScapegoatTree<T>::getMin(Node<T>* r) const {
    if (r->left == NULL) return r;
    else return getMin(r->left);
}

template<class T>
const T& ScapegoatTree<T>::getMax() const {
    /* TODO */
    if(isEmpty()) throw NoSuchItemException();
    return getMax(root)->element;
}

template<class T>
Node<T>* ScapegoatTree<T>::getMax(Node<T>* r) const {
    if (r->right == NULL) return r;
    else return getMax(r->right);
}


template<class T>
const T& ScapegoatTree<T>::getNext(const T& element) const {
    /* TODO */
    Node<T>* ceiling = NULL;
    
    getNext(root, ceiling, element);
    if(!ceiling) throw NoSuchItemException();
    return ceiling->element;
}

template<class T>
void ScapegoatTree<T>::getNext(Node<T>* r, Node<T>*& c, const T& element) const {
    /* TODO */
    
    if(r==NULL) return;
    else if(element < r->element){
        c = r;
        getNext(r->left, c, element);
    }
    else if(element >= r->element){
        getNext(r->right, c, element);
    }
    
}
