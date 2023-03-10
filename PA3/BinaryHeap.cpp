#include "BinaryHeap.h"

BinaryHeap::BinaryHeap()
{
    // TODO: or not
    elements.resize(1);
    size = 0;
}

bool BinaryHeap::contains(int uniqueId){
    
    
    for (int i = 1; i<size+1; i++){
        if (elements[i].uniqueId == uniqueId) return true;
    }

    return false;
}

bool BinaryHeap::Add(int uniqueId, double weight)
{
    // TODO:
    if(contains(uniqueId)) return false;
    else{
        elements[0].weight = weight;
        elements.resize(elements.size() + 1);
        int hole = ++size;
        for( ; weight < elements[hole/2].weight; hole /= 2 )
            elements[hole] = elements[hole/2];
        elements[hole].weight = weight;
        elements[hole].uniqueId = uniqueId;
        
        return true;
    }
}

bool BinaryHeap::PopHeap(int& outUniqueId, double& outWeight)
{
    // TODO:
    if(size!=0){
        outUniqueId = elements[1].uniqueId;
        outWeight = elements[1].weight;
        elements[1] = elements[size];
        size--;
        percolateDown(1);
        return true;
    }
    return false;

}

void BinaryHeap::percolateDown(int hole){
    int child;
    HeapElement tmp = elements[hole];

    for( ; hole*2 <= size; hole = child) {
        child = hole * 2;
        if(child != size && elements[child + 1].weight < elements[child].weight)
            child++;
        if(elements[child].weight < tmp.weight)
            elements[hole] = elements[child];
        else
            break;
    }
    elements[hole] = tmp;
}

void BinaryHeap::BuildHeap(){
    for(int i=size/2 ; i>0; i--){
        percolateDown(i);
    }
}

bool BinaryHeap::ChangePriority(int uniqueId, double newWeight)
{
    // TODO:
    if(contains(uniqueId)){
        int valInd;
        for (int i = 1; i <= size; i++) {
            if (elements[i].uniqueId == uniqueId) {
                valInd = i;
                break;
            }
        }
        elements[valInd].weight = newWeight;
    
        BuildHeap();
        return true;
    }
    return false;
}

int BinaryHeap::HeapSize() const
{
    // TODO:
    return size;
}

