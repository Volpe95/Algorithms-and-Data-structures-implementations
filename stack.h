/*

   Author : Mahmoud Kassem

   Date   : 21 / 4 / 2018 .

   Implementation of a template stack using the array Implementation + Dynamic resizing .


*/

#include<string> // Value Type of the stack may be a string .
#include <assert.h>     /* assert */
using namespace std;

template<class ValType> class stack{

public:

    stack() ; // class constructor
    ValType pop(); // takes out the last value and returns it .
    ValType top(); // returns the value on top
    bool push(ValType Value) ; // inserts a new value on the stack
    int size() ; // returns the number of elements currently in the stack .
    bool empty() ; // checks if the stack is empty .
    void clear();  // clears all values of the stack
    void print() ; // print all elements in the stack .

private:

    void resize(bool TypeOfResizing) ; // resize the array of the stack (increasing or decreasing) .
    ValType * arr ; // pointer to the array to be resiszed and hold the stack values.
    void check(); // checks if the stack needs resizing
    int counter  , Current_Max_Size ;

};

template<class ValType>stack<ValType> :: stack() { // Constructor
    counter = 0 ; Current_Max_Size = 256 ;
    arr = new ValType[256] ; // initialize the array with 256
}

template<class ValType> ValType stack<ValType> :: pop(){ // takes out the first value and returns it
    assert(!empty()) ;

    ValType ret = arr[--counter] ;

    check() ; // checks if the array needs resizing .

    return ret ;
}


template<class ValType> ValType stack<ValType> :: top(){
    assert(!empty()) ;
    return arr[counter - 1] ;
}

template<class ValType> bool stack<ValType> :: push(ValType Value){
    if(size() == Current_Max_Size){
        resize(1) ;  // increase the size of the array .
    }
    arr[counter++] = Value ;
    return 1 ;
}


template<class ValType> bool stack<ValType> :: empty(){
    return (counter == 0) ;
}


template<class ValType> int stack<ValType> :: size(){
    return counter ;
}


template<class ValType> void stack<ValType> :: clear(){
    delete arr ;   counter = 0  ;

    Current_Max_Size = 256 ;

    arr = new ValType[256] ;

    return ;
}

template<class ValType> void stack<ValType> :: print(){
    for(int i = size() - 1 ; i >= 0 ; i--){
        cout << arr[i] << endl ;
    }
    return ;
}

template<class ValType> void stack<ValType> :: check(){

    if(size() * 4 == Current_Max_Size && Current_Max_Size != 256){
        resize(0) ; // Decrease the array size .
    }
    return ;
}

template<class ValType> void stack<ValType> :: resize(bool type){

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


/*** TODO ***\

 Public : Print

 */
