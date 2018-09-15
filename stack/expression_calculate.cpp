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
    char current = 0;
    std::string postfix;//后缀表达式

    std::stack<char> mark;//符号栈

    std::map<char,int> priority;//符号优先级
    priority['+'] = 0;
    priority['-'] = 0;
    priority['*'] = 1;
    priority['/'] = 1;

    for(int i = 0; i < infix.size(); ++i)
    {
        current = infix[i];
        switch(current)
        {
            case '0':case '1':case '2':case '3':case '4':case '5':
            case '6':case '7':case '8':case '9':case '.':
                postfix.push_back(current);//数字直接写入
                break;
            case '+':case '-':case '*':case '/':
                //如果运算符的前一项不是右括号即说明前一个数字输入完毕，用#标识
                if(infix[i-1] != ')')
                    postfix.push_back('#');
                //如果符号栈非空，即比较目前符号与栈顶符号优先级，低于等于出栈(并写入输出字符串)，
                //直至符号全部出栈或者遇到了'('或者大于栈顶符号的优先级
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
                mark.push(current);//新符号入栈
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
                if(infix[i-1] >= '0' && infix[i-1] <= '9')
                    postfix.push_back('#');//右括号说明前方数字输入完成，标识一下
                while(mark.top() != '(')
                {
                    postfix.push_back(mark.top());
                    mark.pop();
                }
                mark.pop();//左括号出栈
                break;
            default:
                break;//忽略其他字符
        }
    }
    if(infix[infix.size()-1] != ')')
        postfix.push_back('#');//中缀表达式最后一个是数字需要加上#。
    while(!mark.empty())//如果栈非空，全部出栈并写入输出字符串
    {
        postfix.push_back(mark.top());
        mark.pop();
    }
    return postfix;
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
    for(std::string::const_iterator i = s.begin(); i != s.end(); ++i)
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
                currNum = atof(strNum.c_str());//in c++11, use currNum = std::stof(strNUm);
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
    std::string test4 = "2*(1*2+(1+1))";
    std::cout << "input expression is: "
         << test1 << " "
         << test2 << " "
         << test3 << " "
         << test4 << " "
         << std::endl;

    std::cout << "result is: "
         << expressionCalculate(test1) << " "
         << expressionCalculate(test2) << " "
         << expressionCalculate(test3) << " "
         << expressionCalculate(test4) << " "
         << std::endl;

    return 0;
}
