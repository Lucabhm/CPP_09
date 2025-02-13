/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:25:03 by lbohm             #+#    #+#             */
/*   Updated: 2025/02/13 17:03:09 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) {}

PmergeMe::PmergeMe(std::vector<std::string> input)
{
	std::regex				pattern("^[\\d\\s]+$");
	std::string				line;
	int						nbr;
	std::string::iterator	newEnd;

	for (std::vector<std::string>::iterator it = input.begin(); it != input.end(); ++it)
	{
		if (std::regex_match(*it, pattern))
		{
			std::stringstream	ss(*it);
			while (std::getline(ss, line, ' '))
			{
				try
				{
					newEnd = std::remove_if(line.begin(), line.end(), ::isspace);
					line.erase(newEnd, line.end());
					if (!line.empty())
					{
						nbr = std::stoi(line);
						if (std::find(this->deque.begin(), this->deque.end(), nbr) == this->deque.end())
						{
							this->deque.push_back(nbr);
							this->vector.push_back(nbr);
						}
						else
							throw std::runtime_error("duplicat found");
					}
				}
				catch(const std::exception &e)
				{
					throw;
				}
			}
		}
		else
			throw std::runtime_error("input is wrong");
	}
}

PmergeMe::PmergeMe(const PmergeMe &cpy)
{
	this->deque = cpy.deque;
	this->vector = cpy.vector;
}

PmergeMe	&PmergeMe::operator= (const PmergeMe &cpy)
{
	if (this != &cpy)
	{
		this->deque = cpy.deque;
		this->vector = cpy.vector;
	}
	return (*this);
}

PmergeMe::~PmergeMe(void) {}

void	PmergeMe::printDeque(void)
{
	std::cout << "Deque:" << std::endl;
	for (std::deque<int>::iterator it = this->deque.begin(); it != this->deque.end(); ++it)
		std::cout << *it << std::endl;
}

void	PmergeMe::printVec(void)
{
	std::cout << "Vec:" << std::endl;
	for (std::vector<int>::iterator it = this->vector.begin(); it != this->vector.end(); ++it)
		std::cout << *it << std::endl;
}

void	PmergeMe::sortData(void)
{
	this->sortDeque();
}

void	PmergeMe::sortDeque(void)
{
	std::deque<std::pair<int, int> >	pairs;
	bool								odd = this->deque.size() % 2;
	int									oddNbr;

	if (odd)
		oddNbr = this->deque.back();
	for (auto it = this->deque.begin(); it != this->deque.end(); ++it)
	{
		std::deque<int>::iterator	nextIt = std::next(it);
		if (nextIt != this->deque.end())
		{
			pairs.push_back(std::pair<int, int>(*it, *nextIt));
			++it;
		}
		else
			break ;
	}
	for (std::deque<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
		std::cout << "first = " << it->first << " second = " << it->second << std::endl;
	if (odd)
		std::cout << "Last nbr = " << oddNbr << std::endl;
	// this->merge(pairs);
}

// void	PmergeMe::merge(std::deque<std::pair<int, int> > pairs)
// {
	
// }