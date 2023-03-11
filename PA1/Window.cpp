#include "Window.h"

Window::Window() {
    this->activeTab = 0;
    tabs.append(Tab());
}

Tab Window::getActiveTab() {
    // TODO
    Node<Tab> *curr = tabs.getFirstNode();
    if( tabs.isEmpty()){
        return Tab();
    }
    for(int i=0; i<activeTab; i++){
        curr = curr->next;
    }
    return curr->data;
}

bool Window::isEmpty() const {
    // TODO
    if( tabs.isEmpty()){
        return true;
    }
    return false;
}

void Window::newTab(const Tab &tab) {
    // TODO
    if(tabs.getSize() == 0){
        tabs.append(tab);
        activeTab = 0;
    }
    else{
        tabs.insertAfterNode(tab, tabs.getNodeAtIndex(activeTab));
        activeTab++;
    }
}

void Window::closeTab() {
    if(activeTab != -1) {
        // TODO
        tabs.removeNodeAtIndex(activeTab);
        if(isEmpty()){
            activeTab = -1;
        }
        else if(activeTab == tabs.getSize()) activeTab--; 
        
        
    }
}

void Window::moveActiveTabTo(int index) {
    // TODO
    tabs.moveToIndex(activeTab, index);
    if(index>=0){
        if(index > tabs.getSize()-1) index = tabs.getSize()-1;
        activeTab = index;
    }
}

void Window::changeActiveTabTo(int index) {
    // TODO
    if(index >= 0 && index<tabs.getSize()){
        activeTab = index;
    }
}

void Window::addTab(Node<Tab> &tab) {
    // TODO
    if(isEmpty()){
        activeTab = 0;
    }
    tabs.append(tab.data);
}

void Window::print() {
    if(tabs.isEmpty()) std::cout << "Window is empty" << std::endl;
    else std::cout << "The active tab is tab " << activeTab << std::endl;
    tabs.print();
}
