/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 23:06:47 by lbohm             #+#    #+#             */
/*   Updated: 2025/01/20 23:27:55 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <string>
# include <map>
# include <regex>
# include <fstream>

class BitcoinExchange
{
	private:
		std::multimap<std::string, std::string>	data;
	public:
		BitcoinExchange(void);
		BitcoinExchange(std::string file);
		BitcoinExchange(const BitcoinExchange &cpy);
		BitcoinExchange	&operator= (const BitcoinExchange &cpy);
		~BitcoinExchange(void);
		void	showList(void) const;
};

#endif