#include "a3_priority_queue.hpp"
#include <iostream> 
using namespace std;

// Nabeel Shahid 20460189 
// Jonathan Chan 20521786


PriorityQueue::PriorityQueue(unsigned int capacity){
    
    heap_ = new DataType[capacity_ + 1];
    size_ = 0;
    capacity_ = capacity;
    
}

PriorityQueue::~PriorityQueue(){
    
    delete[] heap_ ;
    
}

unsigned int PriorityQueue::size() const{
    
    return size_; 
}

bool PriorityQueue::empty() const{
    
    if (size_ == 0){
        return true; 
    }
    return false; 
}

bool PriorityQueue::full() const {
    
    if (size_ == capacity_){
        return true; 
    }
    
    return false; 
}

void PriorityQueue::print() const {
    
    // Prints all of the items in the queue level by level
    
    if (empty()){
        cout<< "The queue is empty\n";
    }
    
    for( int i = 1; i <=size_; i++){
        cout << heap_[i] <<endl ;
    }
    
}

PriorityQueue::DataType PriorityQueue::max() const {
    
    DataType temp;
    temp = heap_[1];
    return temp; 
    
}

bool PriorityQueue::enqueue(PriorityQueue::DataType value){
    
    if (full()){
        
        return false; 
    }
    
    heap_[size_+1] = value;
    size_ ++;
   
    // if the inserted node is bigger than parent then switch and keep going
    
    int placeholder_pos = size_;
    while (heap_[placeholder_pos]>heap_[placeholder_pos/2] && placeholder_pos>1){
        
        int temp = heap_[placeholder_pos/2];
        heap_[placeholder_pos/2] = heap_[placeholder_pos];
        heap_[placeholder_pos] = temp;
        
        placeholder_pos = placeholder_pos/2; 
        
    }
    return true; 

}

bool PriorityQueue::dequeue(){
    
    if (empty()){

        return false; 
    }
    
    if (size_== 1){
        
        heap_[1] = NULL ;
        size_-- ;

        return true; 
        
    }
    heap_[1] = NULL ;
    size_-- ;
    
    heap_[1] = heap_[size_];
    heap_[size_] = NULL;
  
    
    
    int placeholder = 1;
    while ((heap_[placeholder]<heap_[placeholder*2] || heap_[placeholder]<heap_[(placeholder*2)+1]) && placeholder <= capacity_/2){
        
        if (heap_[placeholder*2] > heap_[(placeholder*2)+1]) {
            
            int temp = heap_[placeholder*2];
            heap_[placeholder*2] = heap_[placeholder];
            heap_[placeholder] = temp;
            
            placeholder = placeholder*2; 
        }
        
        else {
            
            int temp = heap_[(placeholder*2)+1];
            heap_[(placeholder*2)+1] = heap_[placeholder];
            heap_[placeholder] = temp; 
            
            placeholder = (placeholder*2)+1;
            
        }
    
    }

    return true; 

}
