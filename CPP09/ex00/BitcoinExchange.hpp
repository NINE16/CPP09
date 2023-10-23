#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <utility>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <string>
#include <algorithm>

class Btc {

	private:
			std:: map<std:: string, float> data;
			double values;
			Btc();

	public:
			Btc(const std::string& data, const std::string& input);
			Btc(Btc const &cpy);
			Btc &operator=(Btc const &cpy);
			int check_date(std:: string datesInput);
			int read_input(const std::string& input);
			double find_closest(std:: string trimDate);

			~Btc();


};



#endif
