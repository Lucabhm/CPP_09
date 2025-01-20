/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 23:07:58 by lbohm             #+#    #+#             */
/*   Updated: 2025/01/20 23:30:21 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		try
		{
			BitcoinExchange	input(argv[1]);

			input.showList();
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	else
		std::cerr << "Error: Wrong nbr of Arguments" << std::endl;
	return (0);
}
