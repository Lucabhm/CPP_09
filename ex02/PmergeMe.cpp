/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:25:03 by lbohm             #+#    #+#             */
/*   Updated: 2025/02/28 12:31:47 by lucabohn         ###   ########.fr       */
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

void	PmergeMe::sortData(void)
{
	int						pairSize = 1;
	bool					odd = this->deque.size() > 1 && this->deque.size() % 2;
	ItDq					endDq = this->deque.end();
	ItVec					endVec = this->vector.end();
	std::deque<int>			tmp;

	std::copy(this->deque.begin(), this->deque.end(), std::back_inserter(tmp));

	std::chrono::time_point	start = std::chrono::high_resolution_clock::now();
	if (odd)
		endDq = std::prev(endDq);
	this->sortDeque(endDq, pairSize);
	this->insertDeque(this->deque.end(), pairSize);
	std::chrono::time_point	end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double>	diffDq = end - start;

	start = std::chrono::high_resolution_clock::now();
	if (odd)
		endVec = std::prev(endVec);
	this->sortVec(endVec, pairSize);
	this->insertVec(this->vector.end(), pairSize);
	end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double >	diffVec = end - start;
	bool	sortDq = std::is_sorted(this->deque.begin(), this->deque.end());
	bool	sortVec = std::is_sorted(this->vector.begin(), this->vector.end());
	if (sortDq && sortVec)
		this->printResult(tmp, diffDq, diffVec);
	else
		std::cerr << "numbers are not sorted" << std::endl;
}


// Deque


void	PmergeMe::printDeque(void)
{
	for (ItDq it = this->deque.begin(); it != this->deque.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
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
	}
}

void	PmergeMe::insertDeque(ItDq end, int pairSize)
{
	ItDq	start = this->deque.begin();

	if (pairSize == std::distance(start, end) || std::distance(start, end) / pairSize == 2)
		return ;
	std::deque<int>	mainIndex;
	std::deque<int>	pendIndex;
	size_t			currJ = 3;
	size_t			prevJ = 1;
	int				endJ = -1;
	int				targetIndex;
	int				endIndex;

	createPairs(mainIndex, pendIndex, pairSize, this->deque.size());
	while (true)
	{
		int	tmp;

		if (pendIndex.size() > currJ - 2)
		{
			targetIndex = currJ - 2;
			endIndex = currJ + prevJ - 1;
		}
		else
		{
			targetIndex = pendIndex.size() - 1;
			endIndex = mainIndex.size() - 1;
		}
		tmp = targetIndex;
		while (targetIndex > endJ)
		{
			int	index = binarySearch(this->deque, mainIndex, pendIndex[targetIndex] - 1, endIndex);
			insertPair(this->deque, mainIndex, pendIndex, index, pendIndex[targetIndex], pairSize);
			--targetIndex;
		}
		endJ = tmp;
		if (static_cast<size_t>(endJ) == pendIndex.size() - 1)
			break ;
		nextJacobsthal(prevJ, currJ);
	}
}


// Vector


void	PmergeMe::printVec(void)
{
	for (std::vector<int>::iterator it = this->vector.begin(); it != this->vector.end(); ++it)
		std::cout << *it << std::endl;
}

void	PmergeMe::sortVec(ItVec end, int pairSize)
{
	if (pairSize == std::distance(this->vector.begin(), end))
		return ;
	while (std::distance(this->vector.begin(), end) % (pairSize * 2) != 0)
		end = std::prev(end);
	mergeVec(end, pairSize);
	pairSize *= 2;
	this->sortVec(end, pairSize);
	this->insertVec(end, pairSize);
}

void	PmergeMe::mergeVec(ItVec end, int pairSize)
{
	std::vector<std::pair<ItVec, ItVec> >	arr(2);

	for (ItVec start = this->vector.begin(); start != end; start = std::next(start, (pairSize * 2)))
	{
		arr[0] = std::pair<ItVec, ItVec>(start, start + pairSize);
		arr[1] = std::pair<ItVec, ItVec>(start + pairSize, start + (pairSize * 2));
		if (*std::prev(arr[0].second) > *std::prev(arr[1].second))
			std::rotate(arr[0].first, arr[1].first, arr[1].second);
	}
}

void	PmergeMe::insertVec(ItVec end, int pairSize)
{
	ItVec	start = this->vector.begin();

	if (pairSize == std::distance(start, end) || std::distance(start, end) / pairSize == 2)
		return ;
	std::vector<int>	mainIndex;
	std::vector<int>	pendIndex;
	size_t			currJ = 3;
	size_t			prevJ = 1;
	int				endJ = -1;
	int				targetIndex;
	int				endIndex;

	createPairs(mainIndex, pendIndex, pairSize, this->vector.size());
	while (true)
	{
		int	tmp;

		if (pendIndex.size() > currJ - 2)
		{
			targetIndex = currJ - 2;
			endIndex = currJ + prevJ - 1;
		}
		else
		{
			targetIndex = pendIndex.size() - 1;
			endIndex = mainIndex.size() - 1;
		}
		tmp = targetIndex;
		while (targetIndex > endJ)
		{
			int	index = binarySearch(this->vector, mainIndex, pendIndex[targetIndex] - 1, endIndex);
			insertPair(this->vector, mainIndex, pendIndex, index, pendIndex[targetIndex], pairSize);
			--targetIndex;
		}
		endJ = tmp;
		if (static_cast<size_t>(endJ) == pendIndex.size() - 1)
			break ;
		nextJacobsthal(prevJ, currJ);
	}
}

void	nextJacobsthal(size_t &prevJ, size_t &currJ)
{
	size_t	nextJ = currJ + 2 * prevJ;
	prevJ = currJ;
	currJ = nextJ;
}

void	PmergeMe::printResult(std::deque<int> befor, std::chrono::duration<double> diffDq, std::chrono::duration<double> diffVec)
{
	std::cout << "Befor: ";
	for (ItDq it = befor.begin(); it != befor.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "After: ";
	this->printDeque();
	
	std::cout << "Time to process a range of  " << this->deque.size() << " elements with std::deque : " << diffDq.count() << " us" << std::endl;
	std::cout << "Time to process a range of  " << this->vector.size() << " elements with std::vector : " << diffVec.count() << " us" << std::endl;
}