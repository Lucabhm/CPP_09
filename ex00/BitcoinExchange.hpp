/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 23:06:47 by lbohm             #+#    #+#             */
/*   Updated: 2025/02/04 12:41:59 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <string>
# include <map>
# include <regex>
# include <fstream>
# include <algorithm>

class BitcoinExchange
{
	private:
		std::multimap<std::string, std::string>	input;
		std::multimap<std::string, std::string>	db;
	public:
		BitcoinExchange(void);
		BitcoinExchange(std::string file, std::string database);
		BitcoinExchange(const BitcoinExchange &cpy);
		BitcoinExchange	&operator= (const BitcoinExchange &cpy);
		~BitcoinExchange(void);
		void	checkPrice(void) const;
};

std::multimap<std::string, std::string>	readFile(std::ifstream &input, char delimiter);
bool	checkDate(std::string date);
bool	isFloat(std::string input);
bool	isInt(std::string input);

#endif