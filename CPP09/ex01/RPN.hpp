#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <map>
#include <utility>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <string>
#include <stack>

class RPN
{
	private:
			RPN(const RPN  &cpy);
			RPN &operator=(const RPN  &cpy);


	public:
			RPN();
			int calculate(std:: string arg);
			int is_oper(char c);
			~RPN();

};


#endif
