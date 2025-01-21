/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:10:49 by lbohm             #+#    #+#             */
/*   Updated: 2025/01/21 23:13:20 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

RPN::RPN(void) {}

RPN::RPN(std::string input)
{
	std::regex	pattern("^(?!.*\\d\\d)[+\\-*/\\s\\d]+$");
	
	if (input.empty())
		throw std::runtime_error("no input");
	if (!std::regex_match(input, pattern))
		throw std::runtime_error("input is wrong");
	this->input = input;
}

RPN::RPN(const RPN &cpy) {}

RPN	&RPN::operator= (const RPN &cpy)
{
	return (*this);
}

RPN::~RPN(void) {}

int	RPN::calcRPN(void)
{
	std::stack<int>	stack;
	int				nbr = 0, nbr2 = 0;

	for (int i = 0; i < this->input.length(); i++)
	{
		if (this->input[i] == '+')
		{
			nbr = stack.top();
			stack.pop();
			nbr2 = stack.top();
			stack.pop();
			stack.push(nbr + nbr2);
			std::cout << "+ " << stack.top() << std::endl;
		}
		else if (this->input[i] == '-')
		{
			nbr = stack.top();
			stack.pop();
			nbr2 = stack.top();
			stack.pop();
			stack.push(nbr - nbr2);
			std::cout << "- " << stack.top() << std::endl;
		}
		else if (this->input[i] == '*')
		{
			nbr = stack.top();
			stack.pop();
			nbr2 = stack.top();
			stack.pop();
			stack.push(nbr * nbr2);
			std::cout << "* " << stack.top() << std::endl;
		}
		else if (this->input[i] == '/')
		{
			nbr = stack.top();
			stack.pop();
			nbr2 = stack.top();
			stack.pop();
			if (nbr == 0 || nbr2 == 0)
				throw std::runtime_error("division by 0");
			stack.push(nbr / nbr2);
			std::cout << "/ " << stack.top() << std::endl;
		}
		else if (this->input[i] != ' ')
			stack.push(this->input[i] - 48);
	}
	return (stack.top());
}
