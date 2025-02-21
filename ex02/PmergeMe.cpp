/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:25:03 by lbohm             #+#    #+#             */
/*   Updated: 2025/02/21 13:47:21 by lbohm            ###   ########.fr       */
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
	int			pairSize = 1;
	bool		odd = this->deque.size() > 1 && this->deque.size() % 2;
	ItDq	end = this->deque.end();

	if (odd)
		end = std::prev(end);
	this->sortDeque(end, pairSize);
	this->insertDeque(this->deque.end(), pairSize);
	bool sorted = std::is_sorted(this->deque.begin(), this->deque.end());
	std::cout << "sorted = " << sorted << std::endl;
	if (!sorted)
		this->printDeque();
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
	std::deque<std::pair<ItDq, ItDq> >	main;
	std::deque<std::pair<ItDq, ItDq> >	pend;
	bool											odd = true;

	main.push_back(std::pair<ItDq, ItDq>(start, start + pairSize));
	main.push_back(std::pair<ItDq, ItDq>(start + pairSize, start + (pairSize * 2)));
	start += (pairSize * 2);
	for (; start != end; start += pairSize)
	{
		if (odd)
			pend.push_back(std::pair<ItDq, ItDq>(start, start + pairSize));
		else
			main.push_back(std::pair<ItDq, ItDq>(start, start + pairSize));
		odd = !odd;
	}
	for (std::deque<std::pair<ItDq, ItDq> >::iterator it = pend.begin(); it != pend.end(); ++it)
	{
		size_t index = this->binarySearch(main, *std::prev(it->second));
		if (index < main.size())
		{
			if (main[index].first < it->first)
				std::rotate(main[index].first, it->first, it->second);
			else
				std::rotate(it->first, main[index].first, it->second);
		}
		else
			std::rotate(main[index - 1].second, it->first, it->second);
		size_t testsize = std::distance(main.begin()->first, it->first) / pairSize;
		if (testsize < main.size())
			main.insert(main.begin() + testsize, *it);
		else
			main.push_back(*it);
	}
}

int	PmergeMe::binarySearch(std::deque<std::pair<ItDq, ItDq> > pairs, int target)
{
	int low = 0, mid = 0, high = pairs.size() - 1;

	while (low <= high)
	{
		mid = low + (high - low) / 2;
		if (*std::prev(pairs[mid].second) < target)
			low = mid + 1;
		else if (*std::prev(pairs[mid].second) > target)
			high = mid - 1;
		else
			return (mid);
	}
	return (low);
}
