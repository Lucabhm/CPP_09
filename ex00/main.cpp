/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 23:07:58 by lbohm             #+#    #+#             */
/*   Updated: 2025/02/04 11:02:14 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		try
		{
			BitcoinExchange	input(argv[1], argv[2]);

			input.checkPrice();
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	else
	{
		std::cerr << "Error: Wrong nbr of Arguments" << std::endl;
		std::cerr << "input shout look like ./btc inputfile database" << std::endl;
	}
	return (0);
}
