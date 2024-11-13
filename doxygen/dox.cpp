/**
 * @file dox.cpp
 * @brief doxygen sameple file
 * @details this file is to explain doxygen
 * 
 * @author mealsOrder
 * @date 2024-11-12
 * @version 0.0.1
 */

#include<iostream>
using namespace std;


/**
 * print string func
 * @author mealsOrder
 * @param str input string
 * @date 2024-11-12
 */
void print(char* str){
    cout << str << '\n';
}

/**
 * input from keyboard func
 * @author mealsOrder
 * @return input string
 * @date 2024-11-12
 */
char* input(){
    char* str;
    str = (char*)malloc(sizeof(char)*BUFSIZ);
    cin >> str;
    return str;
}
int main(){
    char* str = input();
    print(str);
    return 0;
}