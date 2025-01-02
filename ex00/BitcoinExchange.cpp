/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:07:25 by kammi             #+#    #+#             */
/*   Updated: 2024/12/18 11:33:28 by kammi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	std::string line;
	std::ifstream file("data.csv");

	if (!file.is_open())
		throw NoDataException();

	// Verifier si le fichier est vide
	if (file.peek() == std::ifstream::traits_type::eof())
		throw EmptyFileException();

	// Verifier si le header du fichier est valide
	std::getline(file, line);
	if (line != "date,exchange_rate")
		throw InvalidDataException();

	while (std::getline(file, line))
	{
		std::string	date;
		double		rate;
		std::stringstream ss(line);

		std::getline(ss, date, ',');
		ss >> rate;
		if (ss.fail() || ss.bad())
			throw InvalidDataException();

		try {
			isValidDate(date);
		}
		catch (std::exception &e) {
			throw InvalidDataException();
		}
		_data[date] = rate;
	}
	file.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	*this = other;
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		_data = other._data;
	}
	return *this;
}


//functions

void	BitcoinExchange::isValidDate(const std::string &date)
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		throw std::invalid_argument("Invalid date");

	int year = ft_stoi(date.substr(0, 4));
	int month = ft_stoi(date.substr(5, 2));
	int day = ft_stoi(date.substr(8, 2));

	if (month < 1 || month > 12 || day < 1 || day > 31)
		throw std::invalid_argument("Invalid date");
	if (month == 2)
	{
		if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
		{
			if (day > 29)
				throw std::invalid_argument("Invalid date");
		}
		else
		{
			if (day > 28)
				throw std::invalid_argument("Invalid date");
		}
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
			throw std::invalid_argument("Invalid date");
	}
	//a raccourcir
	time_t now = time(0);
	tm *ltm = localtime(&now);
	if (year > 1900 + ltm->tm_year)
		throw std::invalid_argument("Invalid date");
	if (year == 1900 + ltm->tm_year && month > 1 + ltm->tm_mon)
		throw std::invalid_argument("Invalid date");
	if (year == 1900 + ltm->tm_year && month == 1 + ltm->tm_mon && day > ltm->tm_mday)
		throw std::invalid_argument("Invalid date");

}





double	BitcoinExchange::_isValidValue(const std::string &str)
{
	if (str.empty() || std::count(str.begin(), str.end(), '.') > 1)
		throw std::invalid_argument("Invalid value");
	
	double ret = ft_stod(str);

	if (ret < 0)
		throw NegativeValueException();
	if (ret > 1000)
		throw AmountOutOfRangeException();
	return ret;
}

//LIBRARY

int		BitcoinExchange::ft_stoi(const std::string &str)
{
	int		ret;
	std::stringstream ss(str);

	ss >> ret;
	if (ss.fail() || ss.bad())
		throw std::invalid_argument("Invalid argument");
	return ret;
}

double	BitcoinExchange::ft_stod(const std::string &str)
{
	double	ret;
	std::stringstream ss(str);

	ss >> ret;
	if (ss.fail() || ss.bad())
		throw std::invalid_argument("Invalid argument");
	return ret;
}

void	BitcoinExchange::printData(void) const
{
	for (std::map<std::string, double>::const_iterator it = _data.begin(); it != _data.end(); ++it)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}
}

void	BitcoinExchange::exchange(const char *file)
{
	std::string line;
	std::ifstream file2(file);

	if (!file2.is_open())
	{
		throw NoDataException();
	}

	// Verifier si le fichier est vide
	if (file2.peek() == std::ifstream::traits_type::eof())
		throw EmptyFileException();

	// Verifier si le header du fichier est valide
	std::getline(file2, line);
	if (line != "date | value")
	{
		throw InvalidDataException();
	}


	while (std::getline(file2, line))
	{
		std::string			date;
		std::string			amount;
		std::stringstream 	ss(line);

		std::getline(ss, date, '|');
		date.erase(std::remove(date.begin(), date.end(), ' '), date.end());

		std::getline(ss, amount);
		amount.erase(std::remove(amount.begin(), amount.end(), ' '), amount.end());

		
		try {
			if (line.empty())
				throw std::invalid_argument("empty field");
			isValidDate(date);
		}
		catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}

		try {
			double value = _isValidValue(amount);
			if (this->_data.count(date))
			{
				std::cout << date << " => " << value << " = " << value * this->_data[date] << std::endl;
			}
			else
			{
				std::map<std::string, double>::const_iterator it = this->_data.upper_bound(date);
				if (it == this->_data.begin())
					throw NoPreviousDataException();
				else
				{
					--it;
					std::cout << date << " => " << value << " = " << value * it->second << std::endl;
				}
			}
			}
		catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	file2.close();
}



//Exceptions

const char* BitcoinExchange::NoDataException::what() const throw()
{
	return "No data found";
}

const char* BitcoinExchange::InvalidDataException::what() const throw()
{
	return "Invalid data found";
}

const char* BitcoinExchange::EmptyFileException::what() const throw()
{
	return "Empty file";
}

const char* BitcoinExchange::NoPreviousDataException::what() const throw()
{
	return "No previous data found";
}

const char* BitcoinExchange::AmountOutOfRangeException::what() const throw()
{
	return "Amount out of range";
}

const char* BitcoinExchange::NegativeValueException::what() const throw()
{
	return "Negative value";
}
