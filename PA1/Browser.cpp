#include "Browser.h"

/* your browser implementation here */

Browser::Browser() {
    windows.append(Window());
}

void Browser::newWindow() {
    // TODO

    windows.prepend(Window());
}

void Browser::closeWindow() {
    // TODO
    windows.removeNodeAtIndex(0);
}

void Browser::switchToWindow(int index) {
    // TODO
    windows.moveToIndex(index, 0);  
}

Window &Browser::getWindow(int index) {
    return windows.getNodeAtIndex(index) -> data;
}


void Browser::moveTab(Window &from, Window &to) {
    // TODO
    Tab win;
    win = from.getActiveTab();
    from.closeTab();
    to.newTab(win);
    
}

void Browser::mergeWindows(Window &window1, Window &window2) {
    // TODO
    
    while (!window2.isEmpty())
    {
        window2.changeActiveTabTo(0);
        window1.newTab(window2.getActiveTab());
        window2.closeTab();
    }
    
}

void Browser::mergeAllWindows() {
    // TODO
    for(int i=0; i < windows.getSize()-1; i++){
        mergeWindows(windows.getFirstNode()->data, windows.getNodeAtIndex(i+1)->data);

    }
}

void Browser::closeAllWindows() {
    // TODO
    windows.removeAllNodes();
}

void Browser::closeEmptyWindows() {
    // TODO
    Node<Window> *curr = windows.getFirstNode();
    int loop = windows.getSize();
    for(int i=0; i<loop; i++){
        if(curr->data.isEmpty()){
            Node<Window> *tmp = curr->next;
            windows.removeNode(curr);
            curr = tmp;
        }
        else curr = curr->next;
    }
}

void Browser::print() {
    Node<Window> *head = windows.getFirstNode();
    if(head == NULL) {
        std::cout << "The browser is empty" << std::endl;
    } else {
        (head -> data).print();
        head = head -> next;
        while(head != windows.getFirstNode()) {
            (head -> data).print();
            head = head -> next;
        }
    }
}
