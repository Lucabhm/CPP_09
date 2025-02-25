/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:25:03 by lbohm             #+#    #+#             */
/*   Updated: 2025/02/24 19:50:59 by lucabohn         ###   ########.fr       */
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
						this->deque.push_back(nbr);
						this->vector.push_back(nbr);
					}
				}
				catch(const std::exception &e)
				{
					throw;
				}
			}
		}
		else
			throw std::runtime_error("input is wrong => " + *it);
	}
	this->compare = 0;
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
	for (ItDq it = this->deque.begin(); it != this->deque.end(); ++it)
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
	int		pairSize = 1;
	bool	odd = this->deque.size() > 1 && this->deque.size() % 2;
	ItDq	end = this->deque.end();

	if (odd)
		end = std::prev(end);
	this->sortDeque(end, pairSize);
	std::cout << "pairSize = " << pairSize << std::endl;
	this->printDeque();
	this->insertDeque(this->deque.end(), pairSize);
	bool sorted = std::is_sorted(this->deque.begin(), this->deque.end());
	std::cout << "sorted = " << sorted << std::endl;
	std::cout << "compare = " << this->compare << std::endl;
}


void	PmergeMe::sortDeque(ItDq end, int pairSize)
{
	if (pairSize == std::distance(this->deque.begin(), end))
		return ;
	while (std::distance(this->deque.begin(), end) % (pairSize * 2) != 0)
		end = std::prev(end);
	mergeDeque(end, pairSize);
	pairSize *= 2;
	this->sortDeque(end, pairSize);
	std::cout << "pairSize = " << pairSize << std::endl;
	this->printDeque();
	this->insertDeque(end, pairSize);
}


void	PmergeMe::mergeDeque(ItDq end, int pairSize)
{
	std::deque<std::pair<ItDq, ItDq> >	arr(2);

	for (ItDq start = this->deque.begin(); start != end; start = std::next(start, (pairSize * 2)))
	{
		arr[0] = std::pair<ItDq, ItDq>(start, start + pairSize);
		arr[1] = std::pair<ItDq, ItDq>(start + pairSize, start + (pairSize * 2));
		if (*std::prev(arr[0].second) > *std::prev(arr[1].second))
			std::rotate(arr[0].first, arr[1].first, arr[1].second);
		this->compare++;
	}
}

void	PmergeMe::insertDeque(ItDq end, int pairSize)
{
	ItDq	start = this->deque.begin();

	if (pairSize == std::distance(start, end) || std::distance(start, end) / pairSize == 2)
		return ;
	std::deque<std::pair<ItDq, ItDq> >				main;
	std::deque<std::pair<ItDq, ItDq> >				pend;
	std::deque<std::pair<ItDq, ItDq> >::iterator	startP;
	std::deque<std::pair<ItDq, ItDq> >::iterator	endP;
	size_t											currJ = 3;
	size_t											prevJ = 1;

	this->ceatePairs(main, pend, end, pairSize);
	std::cout << "main size = " << main.size() << " pend size = " << pend.size() << std::endl;
	endP = pend.end();
	while (true)
	{
		std::deque<std::pair<ItDq, ItDq> >::iterator	tmp;
		size_t											endJ;

		if (pend.size() >= currJ - 1)
		{
			startP = std::prev(pend.end(), currJ - 1);
			endJ = currJ + prevJ - 1;
		}
		else
		{
			startP = std::prev(pend.end(), pend.size());
			endJ = main.size() - 1;
		}
		std::cout << "endJ = " << endJ << std::endl;
		tmp = startP;
		while (startP != endP)
		{
			size_t iMain = this->binarySearch(main, *std::prev(startP->second), endJ);
			std::cout << "index = " << iMain << std::endl;
			ItDq	test;
			if (iMain < main.size())
			{
				if (main[iMain].first < startP->first)
					test = std::rotate(main[iMain].first, startP->first, startP->second);
				else
					test = std::rotate(startP->first, main[iMain].first, startP->second);
			}
			else
				test = std::rotate(main[iMain - 1].second, startP->first, startP->second);
			std::cout << "test = " << *test << std::endl;
			for (std::deque<std::pair<ItDq, ItDq> >::iterator it = pend.begin(); it != pend.end(); ++it)
			{
				if (test <= it->first && startP->first > it->first && it != startP)
				{
					it->first += pairSize;
					it->second += pairSize;
				}
			}
			for (std::deque<std::pair<ItDq, ItDq> >::iterator it = main.begin(); it != main.end(); ++it)
			{
				std::cout << "test = " << *test << " it->first = " << *it->first << " startP->first = " << *startP->first << std::endl;
				if (test < it->first && startP->first > it->first && it != startP)
				{
					it->first -= pairSize;
					it->second -= pairSize;
					std::cout << "change" << std::endl;
				}
			}
			size_t iPend = std::distance(main.begin()->first, startP->first) / pairSize;
			if (iPend > endJ)
				iPend = endJ;
			std::cout << "iPend = " << iPend << std::endl;
			if (iPend < main.size())
				main.insert(main.begin() + iPend, *startP);
			else
				main.push_back(*startP);
			std::cout << "main:" << std::endl;
			for (std::deque<std::pair<ItDq, ItDq> >::iterator it = main.begin(); it != main.end(); ++it)
				std::cout << "first = " << *it->first << " second = " << *it->second << std::endl;
			std::cout << std::endl;
			std::cout << "pend:" << std::endl;
			for (std::deque<std::pair<ItDq, ItDq> >::iterator it = pend.begin(); it != pend.end(); ++it)
				std::cout << "first = " << *it->first << " second = " << *it->second << std::endl;
			std::cout << std::endl;
			this->printDeque();
			startP++;
			// endJ--;
		}
		endP = tmp;
		nextJacobsthal(prevJ, currJ);
		if (endP == pend.begin())
			break ;
	}
	this->printDeque();
}

int	PmergeMe::binarySearch(std::deque<std::pair<ItDq, ItDq> > pairs, int target, int end)
{
	int low = 0, mid = 0, high = end;

	std::cout << "target = " << target << std::endl;
	while (low <= high)
	{
		mid = low + (high - low) / 2;
		std::cout << "low = " << low << " mid = " << mid << " high = " << high << std::endl;
		this->compare++;
		std::cout << "pos = " << *std::prev(pairs[mid].second) << " target = " << target << std::endl;
		if (*std::prev(pairs[mid].second) < target)
			low = mid + 1;
		else if (*std::prev(pairs[mid].second) > target)
			high = mid - 1;
		else
			return (mid);
	}
	return (low);
}

void	PmergeMe::ceatePairs(std::deque<std::pair<ItDq, ItDq> > &main, std::deque<std::pair<ItDq, ItDq> > &pend,
								std::deque<int>::iterator end, int pairSize)
{
	std::deque<int>::iterator	start = this->deque.begin();
	bool						odd = true;

	main.push_back(std::pair<ItDq, ItDq>(start, start + pairSize));
	main.push_back(std::pair<ItDq, ItDq>(start + pairSize, start + (pairSize * 2)));
	start += (pairSize * 2);
	for (; start != end; start += pairSize)
	{
		if (odd)
			pend.push_front(std::pair<ItDq, ItDq>(start, start + pairSize));
		else
			main.push_back(std::pair<ItDq, ItDq>(start, start + pairSize));
		odd = !odd;
	}
}

void	nextJacobsthal(size_t &prevJ, size_t &currJ)
{
	size_t	nextJ = currJ + 2 * prevJ;
	prevJ = currJ;
	currJ = nextJ;
}