#include <iostream>
#include <set>
#include "queue.h"
using namespace std;
int main()
{
    Queue<int> *a = new Queue<int>(20);
    int b;
    a->EnQueue(2);
    a->Show();

    a->GetFront(b);
    cout << b << endl;
    a->Show();

    a->DeQueue(b);
    cout << b << endl;
    a->Show();
}