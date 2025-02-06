/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:10:49 by lbohm             #+#    #+#             */
/*   Updated: 2025/02/06 09:24:59 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void) {}

RPN::RPN(std::string input)
{
	std::regex	pattern("^(?!.*\\d\\d)[+\\-*/\\s\\d]+$");
	int			count = 0;
	
	if (input.empty())
		throw std::runtime_error("Error: no input");
	if (!std::regex_match(input, pattern))
		throw std::runtime_error("Error: input is wrong => " + input);
	for (int i = 0; i < input.length(); ++i)
	{
		if (std::isdigit(input[i]))
			count++;
		else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
			count--;
	}
	if (count != 1)
		throw std::runtime_error("Error: input is worng => " + input);
	this->input = input;
}

RPN::RPN(const RPN &cpy)
{
	this->input = cpy.input;
	this->result = cpy.result;
}

RPN	&RPN::operator= (const RPN &cpy)
{
	if (this != &cpy)
	{
		this->input = cpy.input;
		this->result = cpy.result;
	}
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
			stack.push(nbrs.second - nbrs.first);
		}
		else if (this->input[i] == '*')
		{
			nbrs = getNbr(stack);
			stack.push(nbrs.second * nbrs.first);
		}
		else if (this->input[i] == '/')
		{
			nbrs = getNbr(stack);
			if (nbrs.first == 0 || nbrs.second == 0)
				throw std::runtime_error("Error: division by 0");
			stack.push(nbrs.second / nbrs.first);
		}
		else if (std::isdigit(this->input[i]))
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
