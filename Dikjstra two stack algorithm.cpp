/*
    Author : Mahmoud Kassem
    Email : m_m_kassem@hotmail.com
    Dijkstra two stack algorithm C++ implementaion
*/

#include <iostream>
#include "stack.h"
#include<string>
#include<stdio.h>
#include <cstdlib>


#define Invalid "Invalid Expression"

using namespace std;
stack<double>numbers ; stack<char>operators ;

bool is_digit(char x){ // returns true if the result is digit .
    return (x >= '0' && x <= '9') ;
}

bool is_operation(char x){ // checks if the char is a valid operation character .
    return (x == '+' || x == '-' || x == '/' || x == 'x') ;
}
double evaluate_expression(double op1 , double op2 , char operator_ch){ // returns the result of the expression

    if(operator_ch == '/' && op2 == 0){
        cout << Invalid << endl ;
        exit(0) ;
    }
    if(operator_ch == '+')
        return op1 + op2 ;

    if(operator_ch == '-')
        return op1 - op2 ;

    if(operator_ch == 'x')
        return op1 * op2 ;

    if(operator_ch == '/'){ // make sure op2 is not zero before going in the function
        return op1 / op2 ;
    }
}
double operation(){ // makes an operation

    double op2 = numbers.top() ; numbers.pop() ;
    double op1 = numbers.top() ; numbers.pop() ;
    char operator_ch = operators.top() ; operators.pop() ;

    return evaluate_expression(op1 , op2 , operator_ch);
}
int main(int argc , char * argv[])
{
    // The input of the program is given using the cmd .
    if(argc == 1){
        double ans = 0 ;
        printf("%.2f\n" , ans) ;
        return 0 ;
    }

    if(argc != 2){
        cout << Invalid << endl ;
        return 0 ;
    }

    string exp = argv[1] ; bool sign = 0 ;

    for(int i = 0 ; i < exp.size() ; i++){ // loop on the whole expression

        if(is_digit(exp[i])){ // if the char is digit then store it in the digits stack
            int val = 0 ;
            while(i != exp.size() && is_digit(exp[i]))
                val = val * 10 + (exp[i] - '0')  , i++ ;
            i-- ;
            numbers.push(val - 2 * (sign) * val) ; // if sign = 1 , make the digit to be -ve
            sign = 0 ;
        }
        else if(exp[i] == '('){
            operators.push(exp[i]) ;
        }
        else if(exp[i] == ')'){  // clear till the open bracket .
            while(!operators.empty() && numbers.size() >= 2){

                if(operators.top() == '('){
                   ///open_fnd = 1 ;
                   break ;
                }
                numbers.push(operation()) ;
            }

            if(operators.empty() || operators.top() != '('){ // if a opening bracked is not found then the expression must be invalid
                cout << Invalid << endl ;
                return 0 ;
            }
            operators.pop() ;
        }
        else if(exp[i] == '-' || exp[i] == '+'){

            if(exp[i] == '-' && (i == 0 || !is_digit(exp[i - 1]) && exp[i - 1] != ')')){
                if(sign){ // double signs are not allowed for example --2 is considered to invalid .
                    cout << Invalid << endl ;
                    return 0 ;
                }
                sign ^= 1 ;
                continue;
            }

            while(!operators.empty()){ // make all previous operations wit higher or equal preceduance .
                if(is_operation(operators.top())){
                    if(numbers.size() < 2){
                        cout << Invalid << endl ;
                        return 0 ;
                    }
                    numbers.push(operation()) ;
                }
                else
                    break;
            }
            operators.push(exp[i]) ;
        }
        else if(exp[i] == 'x' || exp[i] == '/'){
            if(i == 0 || (exp[i - 1] == '(')){
                cout << Invalid << endl ;
                return 0 ;
            }
            while(!operators.empty()){

                if(operators.top() == 'x' || operators.top() == '/'){ // make all previous operations with higher or equal preceduace .
                    if(numbers.size() >= 2){
                        numbers.push(operation()) ;
                    }
                    else
                        return cout << Invalid << endl , 0 ;
                }

                else {
                    break ;
                }
            }
            operators.push(exp[i]) ;
        }
        else {
            cout << Invalid << endl ;
            return 0 ;
        }
    }

    // clear till the last element

    while(!operators.empty()){
        if(numbers.size() < 2){
            cout << Invalid << endl ;
            return 0 ;
        }
        numbers.push(operation()) ;
    }

    if(numbers.size() != 1 || !operators.empty()){
        cout << Invalid << endl ;
        return 0 ;
    }

    printf("%.2f\n" , numbers.top()) ; // print the result with 2 decimal values .

    return 0 ;
}
