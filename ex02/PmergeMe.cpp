/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:25:03 by lbohm             #+#    #+#             */
/*   Updated: 2025/02/14 17:44:12 by lbohm            ###   ########.fr       */
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
	for (iteratorDq it = this->deque.begin(); it != this->deque.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void	PmergeMe::printVec(void)
{
	std::cout << "Vec:" << std::endl;
	for (std::vector<int>::iterator it = this->vector.begin(); it != this->vector.end(); ++it)
		std::cout << *it << std::endl;
}

void	PmergeMe::sortData(void)
{
	int			pairSize = 1;
	bool		odd = this->deque.size() % 2;
	iteratorDq	start = this->deque.begin();
	iteratorDq	end = this->deque.end();

	if (odd)
		end = std::prev(end);
	this->sortDeque(start, end, pairSize);
}

void	PmergeMe::sortDeque(iteratorDq start, iteratorDq end, int pairSize)
{
	if (pairSize >= std::distance(start, end))
		return ;
	while (std::distance(start, end) % (pairSize * 2) != 0)
		end = std::prev(end);
	mergeDeque(start, end, pairSize);
	this->printDeque();
	pairSize *= 2;
	this->sortDeque(start, end, pairSize);
	if (!this->insertDeque(start, end, pairSize))
		return ;
	std::cout << "pairSize = " << pairSize << " distance = " << std::distance(start, end) << std::endl;
}

void	PmergeMe::mergeDeque(iteratorDq start, iteratorDq end, int pairSize)
{
	std::pair<iteratorDq, iteratorDq>	firstPair;
	std::pair<iteratorDq, iteratorDq>	secondPair;
	

	while (start < end)
	{
		iteratorDq	firstEnd = std::next(start, pairSize);
		iteratorDq	secondEnd = std::next(firstEnd, pairSize);
		iteratorDq	secondLast = std::prev(secondEnd);

		firstPair.first = start;
		firstPair.second = std::prev(firstEnd);
		secondPair.first = std::prev(secondLast, pairSize - 1);
		secondPair.second = secondLast;
		if (*firstPair.second > *secondPair.second)
		{
			while (firstPair.first <= firstPair.second)
			{
				std::swap(*firstPair.first, *secondPair.first);
				firstPair.first++;
				secondPair.first++;
			}
		}
		start = std::next(start, pairSize * 2);
	}
}

bool	PmergeMe::insertDeque(iteratorDq start, iteratorDq end, int pairSize)
{
	if (pairSize >= std::distance(start, end) || std::distance(start, end) / pairSize == 2)
		return (false);
	start = std::next(start, pairSize * 2);
	std::deque<int>						pend;
	std::pair<iteratorDq, iteratorDq>	pair;

	while (start != end)
	{
		pair.first = start;
		pair.second = std::next(start, pairSize);
		pend.insert(pend.end(), pair.first, pair.second);
		this->deque.erase(pair.first, pair.second);
		if (pair.second == end)
			start = std::next(start, pairSize * 2);
		else
			break ;
		std::cout << "here" << std::endl;
	}
	std::cout << "pend:" << std::endl;
	for (iteratorDq it = pend.begin(); it != pend.end(); ++it)
		std::cout << *it << std::endl;
	return (true);
}