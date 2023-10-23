#include "BitcoinExchange.hpp"

Btc:: Btc(const std::string& file, const std::string& input)
{
	std:: ifstream database(file);
	if (!database.is_open()){
		std:: cout << "couldnt manage to read file" << std:: endl;
	}

	std:: string line;
	while (std::getline(database, line))
	{
		std:: istringstream strm(line);
		std:: string date;
		std:: string rate;
		if (std::getline(strm, date, ',') && strm >>  rate) {
            data[date] = atof(rate.c_str());
        }
	}
	//   for (std::map<std::string, float>::const_iterator it = data.begin(); it != data.end(); ++it) {
        // std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
    // }
	database.close();

	this->values = 0;
	read_input(input);
}


Btc:: Btc(Btc const &cpy)
{
	*this = cpy;

}


Btc &Btc:: operator=(Btc const &cpy)
{
	this->data = cpy.data;
	return (*this);

}


int Btc:: read_input(const std::string& input)
{
	std:: ifstream inputFile(input);
	if (!inputFile.is_open()){
		std:: cout << "couldnt manage to read file" << std:: endl;
	}

	std:: string inputLine;
	std:: string values;
	std:: string trimDate;
	std:: string datesInput;
	std:: string valueInput;
	double realValue;
	std::getline(inputFile, inputLine);
	int length;
	length = inputLine.length();
	while (std::getline(inputFile, inputLine))
	{
			trimDate = inputLine.substr(0,10);
			// std:: cout << trimDate << std:: endl;
			if (check_date(trimDate))
			{
				std::cout << "Error: bad input => " << trimDate << std::endl;
				continue ;
			}
			values = inputLine.substr(11, length);
			if(values == "")
				continue ;
			realValue = atof(values.c_str());
			{
				if (realValue < 0)
				{
					std::cout << "Error: not a positive number: " << realValue << std::endl;
					continue ;
				}
				if (realValue > 1000)
				{
					std::cout << "Error: too large number: " << realValue << std::endl;
					continue ;
				}
			}
			realValue = realValue * find_closest(trimDate);
			std::cout << trimDate << " => " << values << " = " << realValue << std::endl;
	}
	inputFile.close();
	return (0);
}

int Btc:: check_date(std:: string trimDate)
{
	int	y,m,d;
	if (trimDate.length() < 10)
		return (1);
	// std::istringstream iss(trimDate);
	y = std::stoi(trimDate.substr(0,4));
	m = std::stoi(trimDate.substr(5,2));
	d = std::stoi(trimDate.substr(8,2));
	if (y < 2008 || y > 9999 || m < 1 || m > 12 || d < 1 || d > 31)
	{
		// std:: cout << "Wrong date1 " << m <<std:: endl;
		return (1);
	}
	if (d == 31 && (m == 4 || m == 2 || m == 6 || m == 9 || m == 11))
	{
		// std:: cout << "Wrong date2" << std:: endl;
		return (1);
	}
	if (m == 2 && d == 30)
	{
		// std:: cout << "Wrong date3" << std:: endl;
		return (1);
	}
	if ((m == 2 && d == 29) && (y % 4 != 0))
	{
		// std:: cout << "Wrong date4" << std:: endl;
		return (1);
	}
	return (0);
}

double Btc:: find_closest(std:: string trimDate)
{
	std::map<std::string, float>::iterator itr = this->data.begin();
	std::string	closest = itr->first;
	while(itr != this->data.end())
	{
		if(trimDate > closest)
			itr++;
		if(trimDate == closest)
			return(this->data.find(closest)->second);
		if (trimDate < closest)
			return(this->data.find(closest)->second);
		closest = itr->first;
	}
	return(this->data.find(closest)->second);



}

Btc:: ~Btc()
{}
