/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 23:07:37 by lucabohn          #+#    #+#             */
/*   Updated: 2025/02/06 17:52:30 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(std::string file, std::string database)
{
	std::ifstream	input, db;

	if (file.empty())
		throw std::runtime_error("inputfile is empty");
	if (database.empty())
		throw std::runtime_error("database is empty");
	input.open(file, std::ios::in);
	if (!input.is_open())
		throw std::runtime_error("could not open file");
	db.open(database, std::ios::in);
	if (!db.is_open())
		throw std::runtime_error("could not open database");
	this->input = readFile(input, '|');
	this->db = readFile(db, ',');
	for (std::multimap<std::string, std::string>::iterator it = this->db.begin(); it != this->db.end(); ++it)
	{
		if (!checkDate(it->first))
			throw std::runtime_error("database has wrong date");
		float nbr = std::stof(it->second);
		std::cout << nbr << std::endl;
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &cpy)
{
	this->input = cpy.input;
	this->db = cpy.db;
}

BitcoinExchange	&BitcoinExchange::operator= (const BitcoinExchange &cpy)
{
	if (this != &cpy)
	{
		this->input = cpy.input;
		this->db = cpy.db;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void) {}

void	BitcoinExchange::checkPrice(void) const
{
	std::multimap<std::string, std::string>::const_iterator	found;

	for (std::multimap<std::string, std::string>::const_iterator it = this->input.begin(); it != this->input.end(); ++it)
	{
		if (checkDate(it->first))
		{
			found = this->db.lower_bound(it->first);
			if (found == this->db.end() || found->first != it->first)
				--found;
			if (checkNbr(it->second))
				std::cout << it->first << " => " << it->second << " = " << std::stof(it->second) * std::stof(found->second) << std::endl;
		}
		else
			std::cerr << "Error: bad input => " + it->first << std::endl;
	}
}

std::multimap<std::string, std::string>	readFile(std::ifstream &input, char delimiter)
{
	std::multimap<std::string, std::string>	map;
	std::string								line, date, nbr;
	int										mid = 0, end = 0;

	std::getline(input, line);
	while (std::getline(input, line))
	{
		mid = line.find(delimiter);
		if (mid != std::string::npos)
		{
			end = line.length();
			date = line.substr(0, mid);
			date.erase(std::remove_if(date.begin(), date.end(), ::isspace), date.end());
			nbr = line.substr(mid + 1, end - mid);
			nbr.erase(std::remove_if(nbr.begin(), nbr.end(), ::isspace), nbr.end());
			map.insert(std::pair<std::string, std::string>(date, nbr));
		}
		else
			map.insert(std::pair<std::string, std::string>(line, ""));
	}
	return (map);
}

bool	checkDate(std::string date)
{
	std::regex	datePattern("^\\s*\\d{4}-\\d{2}-\\d{2}\\s*$");
	int	dayOfMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int	year, month, day;

	if (std::regex_match(date, datePattern))
	{
		year = std::stoi(date.substr(0, 4));
		month = std::stoi(date.substr(5, 2));
		day = std::stoi(date.substr(8, 2));
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			dayOfMonth[1] = 29;
		if (month < 1 || month > 12)
			return (false);
		if (day < 1 || day > dayOfMonth[month - 1])
			return (false);
		return (true);
	}
	return (false);
}

bool	checkNbr(std::string nbr)
{
	std::regex	intPattern("^[+]?\\d{1,4}$"), floatPatern("^[+]?\\d{1,4}\\.\\d+$");
	float		value;

	if (std::regex_match(nbr, intPattern) || std::regex_match(nbr, floatPatern))
	{
		value = std::stof(nbr);

		if (value > 1000)
		{
			std::cerr << "Error: nbr is to big => " + nbr << std::endl;
			return (false);
		}
		return (true);
	}
	else if (nbr.length() > 4)
		std::cerr << "Error: nbr is to big => " + nbr << std::endl;
	else if (nbr[0] == '-')
		std::cerr << "Error: nbr is negative => " + nbr << std::endl;
	return (false);
}
