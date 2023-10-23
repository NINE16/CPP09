#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Please add a file as argument" << std:: endl;
		return (1);
	}
	else
	{
		Btc Btc("data.csv", argv[1]);
		// std::cout << "reading file.. " << std::endl;
		// btc.read_input(argv[1]);
	}

}

// Your program should display on the standard output the result of the value multiplied by the exchange rate according
// to the date indicated in your database
