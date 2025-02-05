/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:11:33 by lbohm             #+#    #+#             */
/*   Updated: 2025/02/05 11:08:23 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "RPN.hpp"

int	main(int argc, char **argv)
{
	int	result;

	if (argc == 2)
	{
		try
		{
			RPN	stack(argv[1]);

			result = stack.calcRPN();
			std::cout << result << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;;
		}
	}
	else
		std::cerr << "Error: Wrong nbr of Arguments" << std::endl;
	return (0);
}
