#include "RPN.hpp"
#include <string>
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2 || argv[1][0] == '\0')
	{
		std::cerr << "Error: Wrong number of arguments" << std::endl;
	}
	else{
		RPN Rpn;
		Rpn.calculate(argv[1]);
	}

	return (0);


}
