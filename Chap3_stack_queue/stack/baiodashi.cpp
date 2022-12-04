#include <iostream>
#include <cstring>
#include "stack.h"
using namespace std;

bool is_digit(char a)
{
    return (a == '-' || a == '+' || a == '*' || a == '/' || a == '(' || a == ')') ? 0 : 1;
}

int get_operator_priority(char a) //获得各运算符的优先级
{
    if (a == '+' || a == '-')
        return 0;
    else if (a == '(')
        return -1;
    else if (a == '*' || a == '/' || a == ')')
        return 1;
}
string get_suffix(string &s) //返回中缀表达式的后缀表达形式
{
    string ret;
    Stack<char> *a = new Stack<char>(s.size());
    int i = 0;
    while (i < s.size())
    {

        if (is_digit(s[i])) //如果是数字直接放到结果中
        {
            ret.append(1, s[i++]);
        }
        else //如果是符号
        {
            if (s[i] == ')')
            {
                char item;
                a->topValue(item);
                while (!a->isEmpty() && item != '(')
                {
                    a->pop(item);
                    ret.append(1, item);
                    a->topValue(item);
                }
                a->pop(item); //去除左括号
                i++;
            }
            else if (s[i] == '(' || a->isEmpty())
            {
                a->push(s[i++]);
                continue;
            }
            else
            {
                char temp; //用于获得栈顶元素 比较时需要
                a->topValue(temp);
                if (get_operator_priority(s[i]) > get_operator_priority(temp))
                {
                    a->push(s[i++]);
                    continue;
                }
                else
                {
                    char mul;
                    a->pop(mul);
                    ret.append(1, mul);
                    a->push(s[i++]);
                    continue;
                }
            }
        }
    }
    while (!a->isEmpty())
    {
        char item;
        a->pop(item);
        ret.append(1, item);
    }
    return ret;
}

void calculate(string &str) //计算一个中缀表达式的值
{
    string s = get_suffix(str);
    Stack<int> a(str.size());
    int i = 0;
    while (i < s.size())
    {
        if (is_digit(s[i]))
        {
            a.push(s[i] - 0x30);
        }
        else
        {
            int x, y;
            switch (s[i])
            {
            case '+':
                a.pop(x);
                a.pop(y);
                a.push(y + x);
                break;
            case '-':
                a.pop(x);
                a.pop(y);
                a.push(y - x);
                break;
            case '*':
                a.pop(x);
                a.pop(y);
                a.push(y * x);
                break;
            case '/':
                a.pop(x);
                a.pop(y);
                a.push(y / x);
                break;
            }
        }
        i++;
    }
    int ret;
    a.pop(ret);
    cout << endl
         << ret;
}

int main()
{
    string s = "1*(3*2-5)+4";
    // cin >> s;
    cout << get_suffix(s) << endl;
    calculate(s);
}