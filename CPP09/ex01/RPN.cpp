#include "RPN.hpp"


RPN:: RPN()
{}

int RPN:: is_oper(char c)
{
	if (c == '+' || c == '-' || c == '/' || c == '*')
		return (1);
	return (0);
}

int RPN:: calculate(std::string arg){

	std::stack<double> myStack;
	double one;
	double two;

	for(int i = 0; arg[i]; ++i)
	{
		if (std::isdigit(arg[i]))
		{
			if (std::isdigit(arg[i + 1]))
			{
				std:: cout << "Error" << std:: endl;
				return (1);
			}
			myStack.push(arg[i] - '0');
		}
		else if (is_oper(arg[i]))
		{
			if (myStack.size() < 2)
			{
				std:: cout << "Error in size or order of elements" << std::endl;
				return (1);
			}
			two = myStack.top();
			myStack.pop();
			one = myStack.top();
			myStack.pop();
			if (arg[i] == '+')
				myStack.push(one + two);
			if (arg[i] == '-')
				myStack.push(one - two);
			if (arg[i] == '*')
				myStack.push(one * two);
			if (arg[i] == '/')
				myStack.push(one / two);
		}
		else if (arg[i] != ' ')
		{
			std::cout << "Unknown element: " << arg[i] << std::endl;
			return (1);
		}
	}
	if (myStack.size() > 1)
	{
		std::cout << "Error " << std::endl;
		return (1);
	}
	std::cout << myStack.top();
	std::cout << std::endl;
	return (0);
}

RPN:: ~RPN(){}

