#include <iostream>
#include "Linked_List.h"
using namespace std;

int main()
{
    Linked_List<int> a;
    a.Append(7);
    a.Append(2);
    a.Append(4);
    a.Append(93);
    a.Insert(3, 3880);
    a.Show();
    a.Remove(4);
    a.Show();
}