/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:25:03 by lbohm             #+#    #+#             */
/*   Updated: 2025/02/19 17:11:30 by lbohm            ###   ########.fr       */
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

// void	PmergeMe::sortData(void)
// {
// 	int			pairSize = 1;
// 	bool		odd = this->deque.size() % 2;
// 	iteratorDq	start = this->deque.begin();
// 	iteratorDq	end = this->deque.end();

// 	if (odd)
// 		end = std::prev(end);
// 	this->sortDeque(start, end, pairSize);
// }

void	PmergeMe::sortData(void)
{
	int		pairSize = 1;
	bool	odd = this->deque.size() % 2;
	int		end = this->deque.size();

	if (odd)
		--end;
	this->sortDeque(end, pairSize);
	this->printDeque();
}

// void	PmergeMe::sortDeque(iteratorDq start, iteratorDq end, int pairSize)
// {
// 	if (pairSize == std::distance(start, end))
// 		return ;
// 	while (std::distance(start, end) % (pairSize * 2) != 0)
// 		end = std::prev(end);
// 	mergeDeque(start, end, pairSize);
// 	pairSize *= 2;
// 	this->sortDeque(start, end, pairSize);
// 	if (!this->insertDeque(start, end, pairSize))
// 		return ;
// }

void	PmergeMe::sortDeque(int end, int pairSize)
{
	if (pairSize == end)
		return ;
	while (end % (pairSize * 2) != 0)
		--end;
	this->mergeDeque(end, pairSize);
	pairSize *= 2;
	this->sortDeque(end, pairSize);
	if (!this->insertDeque(end, pairSize))
		return ;
	this->printDeque();
	exit(0);
}

// void	PmergeMe::mergeDeque(iteratorDq start, iteratorDq end, int pairSize)
// {
// 	std::pair<iteratorDq, iteratorDq>	firstPair;
// 	std::pair<iteratorDq, iteratorDq>	secondPair;
	

// 	while (start != end)
// 	{
// 		iteratorDq	firstEnd = std::next(start, pairSize);
// 		iteratorDq	secondEnd = std::next(firstEnd, pairSize);
// 		iteratorDq	secondLast = std::prev(secondEnd);

// 		firstPair.first = start;
// 		firstPair.second = std::prev(firstEnd);
// 		secondPair.first = std::prev(secondLast, pairSize - 1);
// 		secondPair.second = secondLast;
// 		if (*firstPair.second > *secondPair.second)
// 		{
// 			while (firstPair.first <= firstPair.second)
// 			{
// 				std::swap(*firstPair.first, *secondPair.first);
// 				firstPair.first++;
// 				secondPair.first++;
// 			}
// 		}
// 		start = std::next(start, pairSize * 2);
// 	}
// }

void	PmergeMe::mergeDeque(int end, int pairSize)
{
	std::deque<int>	arr(4);
	int				start = 0;

	while (start != end)
	{
		arr[0] = start;
		arr[1] = start + pairSize - 1;
		arr[2] = arr[1] + 1;
		arr[3] = arr[2] + pairSize - 1;
		if (this->deque.size() > static_cast<unsigned long>(arr[3]))
		{
			if (this->deque[arr[1]] > this->deque[arr[3]])
				std::rotate(this->deque.begin() + arr[0], this->deque.begin() + arr[2], this->deque.begin() + arr[3] + 1);
		}
		start += (pairSize * 2);
	}
}

// bool	PmergeMe::insertDeque(iteratorDq start, iteratorDq end, int pairSize)
// {
// 	if (pairSize == std::distance(start, end) || std::distance(start, end) / pairSize == 2)
// 		return (false);
// 	std::deque<std::pair<iteratorDq, iteratorDq> >	pairs;
// 	std::deque<std::pair<iteratorDq, iteratorDq> >	pend;

// 	for (iteratorDq it = start; it != end; it = std::next(it, pairSize))
// 	{
// 		pairs.push_back(std::pair<iteratorDq, iteratorDq>(it, std::next(it, pairSize)));
// 	}
// 	std::deque<std::pair<iteratorDq, iteratorDq> >::iterator pairStart = pairs.begin();
// 	pairStart = std::next(pairStart, 2);
// 	for (std::deque<std::pair<iteratorDq, iteratorDq> >::iterator it = pairStart; it != pairs.end(); ++it)
// 	{
// 		pend.push_back(*it);
// 		it = pairs.erase(it);
// 		if (it == pairs.end())
// 			break ;
// 	}
// 	std::cout << "pair size = " << pairs.size() << std::endl;
// 	std::cout << "pend size = " << pend.size() << std::endl;
// 	std::cout << "befor deque:" << std::endl;
// 	for (iteratorDq it = start; it != end; ++it)
// 		std::cout << *it << " ";
// 	std::cout << std::endl;
// 	for (std::deque<std::pair<iteratorDq, iteratorDq> >::iterator it = pend.begin(); it != pend.end(); ++it)
// 	{
// 		int	index = this->binarySearch(pairs, *std::prev(it->second));
// 		pairs.insert(std::next(pairs.begin(), index), *it);
// 	}
// 	int	i = 0;
// 	for (iteratorDq it = start; it != end; it = std::next(it, pairSize))
// 	{
// 		std::cout << "it = " << *it << " pair = " << *pairs[i].first << std::endl;
// 		if (*it == *pairs[i].first)
// 			i++;
// 		else
// 		{
// 			std::cout << "here" << std::endl;
// 			if (it < pairs[i].first)
// 				std::rotate(it, pairs[i].first, pairs[i].second);
// 			else
// 				std::rotate(pairs[i].first, it, std::next(it, pairSize));
// 			std::cout << "after" << std::endl;
// 			it = std::next(it, pairSize);
// 			i++;
// 		}
// 		std::cout << "it = " << *it << " end = " << *end << std::endl;
// 		// std::cout << "mid deque:" << std::endl;
// 		// for (iteratorDq it = start; it != end; ++it)
// 		// 	std::cout << *it << " ";
// 		// std::cout << std::endl;
// 	}
// 	for (iteratorDq it = start; it != end; ++it)
// 		std::cout << *it << " ";
// 	std::cout << std::endl;
// 	for (std::deque<std::pair<iteratorDq, iteratorDq> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
// 		std::cout << "first = " << *it->first << " second = " << *it->second << std::endl;
// 	return (true);
// }

bool	PmergeMe::insertDeque(int end, int pairSize)
{
	if (pairSize == end || (end / pairSize) == 2)
		return (false);
	std::deque<std::pair<int, int> >	mainChain;
	std::deque<std::pair<int, int> >	pend;
	int				start = 0;
	bool			test = true;

	mainChain.push_back(std::pair<int, int>(start, pairSize - 1));
	mainChain.push_back(std::pair<int, int>(pairSize, (pairSize * 2) - 1));
	start = (pairSize * 2);
	while (start < end)
	{
		if (test)
		{
			pend.push_back(std::pair<int, int>(start, start + pairSize - 1));
			test = false;
		}
		else
		{
			mainChain.push_back(std::pair<int, int>(start, start + pairSize - 1));
			test = true;
		}
		start += pairSize;
	}
	for (std::deque<std::pair<int, int> >::iterator it = pend.begin(); it != pend.end(); ++it)
	{
		int index = this->binarySearch(mainChain, it->second);
		std::cout << "index = " << index << std::endl;
		std::rotate(this->deque.begin() + mainChain[index].second + 1, this->deque.begin() + it->first, this->deque.begin() + it->second + 1);
	}
	return (true);
}

// int	PmergeMe::binarySearch(std::deque<std::pair<iteratorDq, iteratorDq> > pairs, int target)
// {
// 	int low = 0, mid = 0, high = pairs.size();

// 	while (low <= high)
// 	{
// 		mid = low + (high - low) / 2;
// 		if (*std::prev(pairs[mid].second) < target)
// 			low = mid + 1;
// 		else if (*std::prev(pairs[mid].second) > target)
// 			high = mid - 1;
// 	}
// 	return (mid);
// }

int	PmergeMe::binarySearch(std::deque<std::pair<int, int> > mainChain, int target)
{
	int low = 0, mid = 0, high = mainChain.size();

	while (low <= high)
	{
		mid = low + (high - low) / 2;
		std::cout << "main  = " << this->deque[mainChain[mid].second] << " target = " << this->deque[target] << std::endl;
		if (this->deque[mainChain[mid].second] < this->deque[target])
			low = mid + 1;
		else if (this->deque[mainChain[mid].second] > this->deque[target])
			high = mid - 1;
	}
	return (mid - 1);
}
