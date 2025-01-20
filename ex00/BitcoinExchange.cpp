/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 23:07:37 by lucabohn          #+#    #+#             */
/*   Updated: 2025/01/20 23:30:06 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(std::string file)
{
	std::ifstream	input;
	std::string		line, date, nbr;
	size_t			mid = 0, end = 0;

	if (file.empty())
		throw std::runtime_error("file is empty");
	input.open(file, std::ios::in);
	if (!input.is_open())
		throw std::runtime_error("could not open file");
	while (std::getline(input, line))
	{
		mid = line.find('|');
		if (mid != std::string::npos)
		{
			end = line.length();
			date = line.substr(0, mid - 1);
			nbr = line.substr(mid + 1, end - mid - 1);
			this->data.insert(std::pair<std::string, std::string>(date, nbr));
		}
		else
			this->data.insert(std::pair<std::string, std::string>(line, "nan"));
	}
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &cpy)
{
	this->data = cpy.data;
}

BitcoinExchange	&BitcoinExchange::operator= (const BitcoinExchange &cpy)
{
	if (this != &cpy)
	{
		this->data = cpy.data;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void) {}

void	BitcoinExchange::showList(void) const
{
	for (std::multimap<std::string, std::string>::const_iterator it = this->data.begin(); it != this->data.end(); ++it)
		std::cout << it->first << " : " << it->second << std::endl;
}