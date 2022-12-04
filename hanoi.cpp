#include <iostream>
using namespace std;
void hanio(int n, char A, char B, char C)
{
    /*
    1.把n-1个圆环从A借助C移到B
    2.把第n个圆环直接从A移到C
    3.把n-1个圆环从B借助A移到C
    */
    if (n == 1)
    {
        cout << "put " << n << " from " << A << " to " << C << endl;
    }
    else
    {
        hanio(n - 1, A, C, B);
        cout << "put " << n << " from " << A << " to " << C << endl;
        hanio(n - 1, B, A, C);
    }
}
int main()
{
    hanio(6, 'A', 'B', 'C');
}