#四则运算表达式求值

##算法描述

输入一个中缀表达式，包括`+`，`-`，`*`，`/`，`(`，`)` 的四则运算，求其计算结果。

> 注意：如`3-5*2(6/2)`的表达式亦合法。

##算法思想

* 首先，将中缀表达式转换为后缀表达式。每一个表达式都对应一个符号表达式树（二叉树）（可参考严蔚敏版《数据结构》6.3节），中缀表达式是对树做中序遍历，而后缀表达式则是对树做后缀遍历，借助堆栈可以轻松实现此转换。
* 为了标识每个操作数在转换为后缀表达式后的结果，我们在每个操作数后面都加上了一个`#`，譬如`3+5`转换为后缀表达式即为`3#25#+`。
* 利用堆栈计算后缀表达式的值。该函数接受一个`string`类型的后缀表达式，循环读取其中每一个字符，如果是数字即放到字符串`strNum`之中，直到遇到`#`，然后将`strNum`中记录的完整数字的字符串转换成浮点数，然后入栈。遇到符号则取出栈顶两个元素，计算结果入栈。最后栈里的唯一数字即结果。

##C++实现

这里直接可借助 C++ STL 的模板库`stack`，没必要闭门造车。

```C++
#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>
#include <map>

/*  中缀表达式转换成后缀表达式
    输入中缀表达式字符串infix，转化后返回后缀表达式字符串postfix
    输出串中，每一个数字后面放置一个#作为标识。因为数字使用char表达，234即三个char，“#”标识数字结束,
    做好数字完结标识后，即写入输出字符串中。
    遇到符号，左括号直接入栈；右括号时，将栈顶符号逐个取出写入输出字符串中，直到遇见左括号；
    运算符需循环与栈顶符号优先级进行比较：如果小于或者等于，取出栈顶符号写入输出字符串中，
    如果是左括号，直接入栈，如果优先级高于栈顶符号，入栈。
*/
std::string InfixToPostfix(std::string infix)
{
    char current = 0;//读入的字符
    std::string postfix;//写入后缀表达式的字符串

    std::stack<char> mark;//符号入栈

    std::map<char,int> priority;//运算符号优先级表
    priority['+'] = 0;
    priority['-'] = 0;
    priority['*'] = 1;
    priority['/'] = 1;

    for(int i = 0;i < infix.size(); ++i)//逐个读取中缀表达式字符串中的字符
    {
        current =infix[i];
        switch(current)
        {
            case '0':case '1':case '2':case '3':case '4':case '5':
            case '6':case '7':case '8':case '9':case '.':
                postfix.push_back(current);//如果是数字的话直接写入输出字符串。
                break;
            case '+':case '-':case '*':case '/':
                //如果运算符的前一项不是右括号即说明前一个数字输入完毕，用#标识前面几个字符组成一个数字。
                if(infix[i-1] != ')')
                    postfix.push_back('#');
                //如果符号栈非空，即比较目前符号与栈顶符号优先级，低于等于出栈，并写入输出字符串。
                if(!mark.empty())
                {
                    char tempTop = mark.top();
                    while(tempTop != '(' && priority[current] <= priority[tempTop])
                    {
                        postfix.push_back(tempTop);
                        mark.pop();
                        if(mark.empty())
                            break;
                        tempTop = mark.top();
                    }
                }
                mark.push(current);//符号全部出栈或者遇到了'('或者大于栈顶符号的优先级，将新符号压入栈中
                break;
            case '(':
                if(infix[i-1] >= '0' && infix[i-1] <= '9')// for expression 2-5*2(6/2)
                {
                    postfix.push_back('#');
                    mark.push('*');
                }
                mark.push(current);
                break;
            case ')':
                postfix.push_back('#');//右括号说明前方数字输入完成，标识一下。
                while(mark.top() != '(')//直到栈顶元素是左括号才停止循环
                {
                    postfix.push_back(mark.top());//出栈并写入输出字符串中。
                    mark.pop();
                }
                mark.pop();//直接将左括号出栈。
                break;
            default:
                break;//忽略其他字符。
        }
    }
    if(infix[infix.size()-1] != ')')
        postfix.push_back('#');//中缀表达式最后一个是数字需要加上#。
    while(!mark.empty())//如果栈非空，全部出栈并写入输出字符串。
    {
        postfix.push_back(mark.top());
        mark.pop();
    }
    return postfix;//返回后缀表达式。
}

/*  计算后缀表达式结果
    输入为后缀表达式s，逐个读取字符，如果是数字即放入存放当前数字的字符串中，
    遇到“#”即将此字符串转换为float，
    使用atof()，参数接受const char*类型，字符串需使用.c_str()转化。
    完成数字识别转化后入栈，遇到符号即取出栈顶的两个数字计算，结果入栈。
    栈中最后的元素即为结果。
*/
float posfixCompute(std::string s)
{
    std::stack<float> tempResult;

    std::string strNum;
    float currNum = 0;

    float tempNum = 0;
    for(std::string::const_iterator i = s.begin(); i < s.end(); ++i)
    {
        switch(*i)
        {
            case '0':case '1':case '2':case '3':case '4':case '5':
            case '6':case '7':case '8':case '9':case '.':
                strNum.push_back(*i);
                break;
            case '+':
                tempNum = tempResult.top();
                tempResult.pop();
                tempNum += tempResult.top();
                tempResult.pop();
                tempResult.push(tempNum);
                break;
            case '-':
                tempNum = tempResult.top();
                tempResult.pop();
                tempNum = tempResult.top() - tempNum;
                tempResult.pop();
                tempResult.push(tempNum);
                break;
            case '*':
                tempNum = tempResult.top();
                tempResult.pop();
                tempNum *= tempResult.top();
                tempResult.pop();
                tempResult.push(tempNum);
                break;
            case '/':
                tempNum = tempResult.top();
                tempResult.pop();
                tempNum = tempResult.top() / tempNum;
                tempResult.pop();
                tempResult.push(tempNum);
                break;
            case '#':
                currNum = atof(strNum.c_str());//in c++11  currNum = std::stof(strNUm);
                strNum.clear();
                tempResult.push(currNum);
                break;
        }
    }
    return tempResult.top();
}

float expressionCalculate(std::string s)
{
    return posfixCompute(InfixToPostfix(s));
}

int main(void)
{
    std::string test1 = "(8+4)*5-7/2";
    std::string test2 = "3-5*2*(6/2)";
    std::string test3 = "3-5*2(6/2)";
    std::cout << "input expression is: "
         << test1 << " "
         << test2 << " "
         << test3 << " "
         << std::endl;

    std::cout << "result is: "
         << expressionCalculate(test1) << " "
         << expressionCalculate(test2) << " "
         << expressionCalculate(test3) << " "
         << std::endl;

    return 0;
}
```
输出为（gcc 4.8.2）：

```C++
input expression is: (8+4)*5-7/2 3-5*2*(6/2) 3-5*2(6/2)
result is: 56.5 -27 -27
```
## 参考资料

[四则混合运算C++代码](http://blog.csdn.net/windyitian/article/details/7307290)
