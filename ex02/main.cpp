/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:07:22 by lbohm             #+#    #+#             */
/*   Updated: 2025/02/13 16:36:16 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	if (argc >= 2)
	{
		std::vector<std::string>	values(argv + 1, argv + argc);

		try
		{
			PmergeMe	input(values);

			input.sortData();
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	else
		std::cerr << "Error: wrong nbr of args" << std::endl;
	return (0);
}
