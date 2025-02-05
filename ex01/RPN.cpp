/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:10:49 by lbohm             #+#    #+#             */
/*   Updated: 2025/02/05 11:36:34 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

RPN::RPN(void) {}

RPN::RPN(std::string input)
{
	std::regex	pattern("^(?!.*\\d\\d)[+\\-*/\\s\\d]+$");
	
	if (input.empty())
		throw std::runtime_error("Error: no input");
	if (!std::regex_match(input, pattern))
		throw std::runtime_error("Error: input is wrong => " + input);
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
	std::stack<int>		stack;
	std::pair<int, int>	nbrs;

	for (int i = 0; i < this->input.length(); i++)
	{
		if (this->input[i] == '+')
		{
			nbrs = getNbr(stack);
			stack.push(nbrs.second + nbrs.first);
		}
		else if (this->input[i] == '-')
		{
			nbrs = getNbr(stack);
			stack.push(nbrs.second + nbrs.first);
		}
		else if (this->input[i] == '*')
		{
			nbrs = getNbr(stack);
			stack.push(nbrs.second + nbrs.first);
		}
		else if (this->input[i] == '/')
		{
			nbrs = getNbr(stack);
			if (nbrs.first == 0 || nbrs.second == 0)
				throw std::runtime_error("Error: division by 0");
			stack.push(nbrs.second + nbrs.first);
		}
		else if (this->input[i] != ' ')
			stack.push(this->input[i] - 48);
	}
	return (stack.top());
}

std::pair<int, int>	getNbr(std::stack<int> &stack)
{
	int					nbr, nbr2;

	if (stack.size() > 1)
	{
		nbr = stack.top();
		stack.pop();
		nbr2 = stack.top();
		stack.pop();
	}
	else
		throw std::runtime_error("Error: wrong input");
	return (std::pair<int, int>(nbr, nbr2));
}
