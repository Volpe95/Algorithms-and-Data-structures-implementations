/*

   Author : Mahmoud Kassem

   Email : m_m_kassem@hotmail.com

   Date   : 3 / 5 / 2018 .

   Implementation of a template simple priority_queue with (O(n) enqueue )using the array Implementation + Dynamic resizing .


*/

#include<string>
#include<iostream>
#include<stdio.h>
#include <assert.h>     /* assert */

#define initial_size  2

using namespace std ;

template<class ValType> class priority_queue{
public:
    priority_queue() ; // default constructor of the queue .
    bool push(ValType val) ; // pushes a value to the queue and returns TRUE if successful  .
    ValType pop() ;     // pops the first value in the queue
    ValType top() ; // returns the first value in the queue without poping it .
    int size() ; // returns the size of the queue .
    bool empty() ; // returns TRUE if the queue is empty .
    void update(int x) ; // updates the whole queue with a certian value .
private:
    void resize(bool TypeOfResizing) ; // resize the array of the queue (increasing or decreasing) .
    void check(); // checks if the queue needs resizing
    void insert(int x , ValType value) ;  // inserts the value at position x and shifts the remainning right of the array .
    ValType * arr ; // pointer to the array to be resiszed and hold the queue values.
    int counter  , Current_Max_Size ; // the counter and the Current_max_size values .

};

template<class ValType>priority_queue<ValType> :: priority_queue(){
    Current_Max_Size = initial_size , counter = 0 ;
    arr = new ValType[Current_Max_Size] ;
}

template<class ValType>bool priority_queue<ValType> :: push(ValType value){

    if(size() == Current_Max_Size){ // if the max size reached , resize the array .
        resize(1) ;
    }

    for(int i = 0 ; i < size() ; i++){

        if(arr[i] >= value){ // if the current value is larger than the value sent , then insert .
            insert(i , value) ; // insert at pos i .
            return 1 ;
        }

    }

    insert(size() , value) ; // the value is larger than all the current values , so insert at the last element .
    return 1 ;
}

template<class ValType>void priority_queue<ValType> :: insert(int pos , ValType value){

    for(int i = size() ; i > pos ; i--){
        swap(arr[i] , arr[i - 1]) ;  // swaps the values , means shift all to right untill position
    }

    arr[pos] = value ;
    counter = counter + 1 ;
    return ;
}

template<class ValType> ValType priority_queue<ValType> :: pop(){
    assert(counter != 0); // terminates if the queue is empty  .

    ValType ret = arr[--counter] ; // saves the value of the last element .

    check() ; // check is the current size is less than half the current max_size  .

    return ret ; // returns the value .
}

template<class ValType> ValType priority_queue<ValType> :: top(){
    assert(counter != 0) ; // checks if the queue is not empty and terminates if so .

    return arr[counter - 1] ; // returns the value of the last element .
}

template<class ValType> int priority_queue<ValType> :: size(){ // returns the current size of the queue .
    return (counter) ;
}

template<class ValType> bool priority_queue<ValType> :: empty(){ // returns TRUE if the queue is empty
    return (counter == 0) ;
}

template<class ValType> void priority_queue<ValType> :: update(int x){
    for(int i = 0 ; i < size() ; i++){
        arr[i].first = arr[i].first + x ;
    }
    return ;
}
template<class ValType> void priority_queue<ValType> :: check(){

    if(size() * 4 == Current_Max_Size && Current_Max_Size != initial_size){
        resize(0) ; // Decrease the array size .
    }
    return ;
}

template<class ValType> void priority_queue<ValType> :: resize(bool type){

    if(type == 1){ // increase the size of the array .
        ValType * temp ;

        temp = new ValType[size()] ;

        for(int i = 0 ; i < size() ; i++){
            temp[i] = arr[i] ;
        }

        delete arr ;

        Current_Max_Size = Current_Max_Size * 2 ;

        arr = new ValType[Current_Max_Size] ;

        for(int i = 0 ; i < size() ; i++){
            arr[i] = temp[i] ;
        }

        delete temp ;
    }
    else {
        ValType * temp ;

        temp = new ValType[size()] ;

        for(int i = 0 ; i < size() ; i++){
            temp[i] = arr[i] ;
        }

        Current_Max_Size = Current_Max_Size / 2 ;

        delete arr ;

        arr = new ValType[Current_Max_Size] ;

        for(int i = 0 ; i < size() ; i++){
            arr[i] = temp[i] ;
        }

        delete temp ;
    }
    return ;
}
