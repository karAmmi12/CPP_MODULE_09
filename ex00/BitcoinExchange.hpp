/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:07:29 by kammi             #+#    #+#             */
/*   Updated: 2025/01/17 15:37:25 by kammi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <map>
# include <sstream>
# include <string>
# include <algorithm>

class BitcoinExchange
{
	private:
		std::map<std::string, double>	_data;

		void	isValidDate(const std::string &date);
		double	_isValidValue(const std::string &str);

	public:

		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		~BitcoinExchange();

		BitcoinExchange	&operator=(const BitcoinExchange &other);

		void	exchange(const char *file);
		void	printData(void) const;
		

		// library functions
		int		ft_stoi(const std::string &str);
		double	ft_stod(const std::string &str);


		//Exceptions
		class NoDataException : public std::exception
		{
			public:
				virtual const char* what() const throw();

		};

		class	InvalidDataException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class	EmptyFileException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class	NoPreviousDataException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class	AmountOutOfRangeException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		
		class	NegativeValueException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};	

};

# endif
