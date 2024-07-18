//逆波兰

#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

//转化为逆波兰表达式
string trans(string& s)
{
	string operand;
	stack<char> Operator;
	int flag = 0;//记录括号优先级
	for (const auto& e : s)//一个一个遍历
	{
		if (e == '(')
		{
			Operator.push(e);
			flag = 1;
			continue;
		}
		if (e == ')')
		{
			flag = 0;
			while (Operator.top() != '(')
			{
				operand.push_back(Operator.top());
				Operator.pop();
			}
			Operator.pop();
			continue;
		}
		//操作符
		if (e == '+' || e == '-' || e == '*' || e == '/')
		{
			if (flag == 1)//如果在括号里面
			{
				if (Operator.top() == '(')
				{
					Operator.push(e);
				}
				else if ((e == '*' || e == '/') && (Operator.top() == '+' || Operator.top() == '-'))
				{
					Operator.push(e);
				}
				else//操作符的优先级低于或等于栈顶操作符则出栈，直至遇到'('
				{
					while (Operator.top() != '(')
					{
						operand.push_back(Operator.top());
						Operator.pop();
					}
					Operator.push(e);
				}
			}
			else if (Operator.empty())//栈空就入栈
			{
				Operator.push(e);
			}
			//操作符的优先级高于栈顶操作符，入栈
			else if ((e == '*' || e == '/') && (Operator.top() == '+' || Operator.top() == '-'))
			{
				Operator.push(e);
			}
			else//操作符的优先级低于或等于栈顶操作符则出栈，直至栈空或者优先级高于栈顶操作符
			{
				while (!Operator.empty())
				{
					operand.push_back(Operator.top());
					Operator.pop();
				}
				Operator.push(e);
			}
		}
		//操作数
		else
		{
			operand.push_back(e);
		}
	}
	while (!Operator.empty())//最后将剩余在栈里面的全部出栈
	{
		operand.push_back(Operator.top());
		Operator.pop();
	}
	return operand;
}

int evalRPN(const string& s)
{
	stack<char> operand;
	int left = 0, right = 0;
	for (const auto& e : s)
	{
		if (e == '+' || e == '-' || e == '*' || e == '/')
		{
			switch (e)
			{
			case '+':
				right = operand.top();
				operand.pop();
				left = operand.top();
				operand.pop();
				operand.push(left + right);
				break;
			case '-':
				right = operand.top();
				operand.pop();
				left = operand.top();
				operand.pop();
				operand.push(left - right);
				break;
			case '*':
				right = operand.top();
				operand.pop();
				left = operand.top();
				operand.pop();
				operand.push(left * right);
				break;
			case '/':
				right = operand.top();
				operand.pop();
				left = operand.top();
				operand.pop();
				operand.push(left / right);
				break;
			}
		}
		else//操作数
		{
			operand.push(e - '0');
		}
	}
	return operand.top();
}

int RPN(const string& str)
{
	//1.中缀表达式转化为后缀表达式
	string s(str);
	s = trans(s);
	//2.后缀表达式计算答案
	return evalRPN(s);
}

int main()
{
	string s("5*(3+5)/5-4/2");
	int ret = RPN(s);
	cout << "ret:" << ret << endl;
	return 0;
}
