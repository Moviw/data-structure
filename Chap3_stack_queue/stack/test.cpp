#include <iostream>
using namespace std;

#include "stack.h"
int main()
{
    Stack<int> a = Stack<int>();
    // a.push(20);
    a.Show();
    int test;
    a.topValue(test);
    cout<<test<<endl;
}