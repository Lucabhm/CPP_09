/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:25:03 by lbohm             #+#    #+#             */
/*   Updated: 2025/02/27 17:32:28 by lbohm            ###   ########.fr       */
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

	// std::cout << "deque befor" << std::endl;
	// this->printDeque();
	if (odd)
		end = std::prev(end);
	this->sortDeque(end, pairSize);
	std::cout << "pairSize = " << pairSize << std::endl;
	this->insertDeque(this->deque.end(), pairSize);

	bool sorted = std::is_sorted(this->deque.begin(), this->deque.end());
	// if (!sorted)
		// this->printDeque();
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
	this->insertDeque(end, pairSize);
	if (pairSize == 2)
		exit(0);
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

	// if i have only one group or two i can return because they already sorted
	if (pairSize == std::distance(start, end) || std::distance(start, end) / pairSize == 2)
		return ;
	// stores the last index of the groups
	std::deque<int>	mainIndex;
	std::deque<int>	pendIndex;
	// the current and previous Jacobsthal numbers and the end of the loop
	size_t			currJ = 3;
	size_t			prevJ = 1;
	int				endJ = -1;
	// the index that gets inserted
	int				targetIndex;
	// the index of max comparisons for the targetIndex
	int				endIndex;

	this->createPairs(mainIndex, pendIndex, pairSize);
	this->printDeque();
	std::cout << "mainIndex" << std::endl;
	for (ItDq it = mainIndex.begin(); it != mainIndex.end(); ++it)
		std::cout << *it << std::endl;
	std::cout << "pendIndex" << std::endl;
	for (ItDq it = pendIndex.begin(); it != pendIndex.end(); ++it)
		std::cout << *it << std::endl;
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
			int	index = this->binarySearch(mainIndex, pendIndex[targetIndex] - 1, endIndex);
			std::cout << "index = " << index << std::endl;
			this->insertPair(mainIndex, pendIndex, index, pendIndex[targetIndex], pairSize);
			--targetIndex;
		}
		endJ = tmp;
		if (static_cast<size_t>(endJ) == pendIndex.size() - 1)
			break ;
		nextJacobsthal(prevJ, currJ);
	}
	std::cout << "after insert " << std::endl;
	this->printDeque();
}

// fill the mainIndex and pendIndex with the Index of deque
void	PmergeMe::createPairs(std::deque<int> &mainIndex, std::deque<int> &pendIndex, int pairSize)
{
	bool	odd = true;

	mainIndex.push_back(pairSize);
	mainIndex.push_back(pairSize * 2);
	for (size_t size = pairSize * 3; size <= this->deque.size(); size += pairSize)
	{
		if (odd)
			pendIndex.push_back(size);
		else
			mainIndex.push_back(size);
		odd = !odd;
	}
}

int	PmergeMe::binarySearch(std::deque<int> mainIndex, int targetIndex, int endIndex)
{
	int	low = 0, mid, high = endIndex;
	int	value = this->deque[targetIndex];

	std::cout << "target = " << value << std::endl;
	while (low <= high)
	{
		mid = low + (high - low) / 2;
		if (static_cast<size_t>(mid) == mainIndex.size())
			return (mid) ;
		this->compare++;
		if (this->deque[mainIndex[mid] - 1] < value)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return (low);
}

void	PmergeMe::insertPair(std::deque<int> &mainIndex, std::deque<int> &pendIndex, int indexMain, int indexPend, int pairSize)
{
	int	startI;
	int	startE = indexPend - pairSize;
	std::deque<int>	input;

	if (mainIndex.begin() + indexMain != mainIndex.end())
		startI = mainIndex[indexMain] - pairSize;
	else
		startI = mainIndex[indexMain - 1] + pairSize;
	if (startI != indexPend)
	{
		std::copy(this->deque.begin() + startE, this->deque.begin() + indexPend, std::back_inserter(input));
		this->deque.insert(this->deque.begin() + startI, input.begin(), input.end());
		ItDq	test;
		if (startI < startE)
			test = this->deque.erase(this->deque.begin() + startE + pairSize, this->deque.begin() + indexPend + pairSize);
		else
			test = this->deque.erase(this->deque.begin() + startE, this->deque.begin() + indexPend);
		std::cout << "test = " << *test << std::endl;
		std::cout << "test distanz = " << std::distance(this->deque.begin(), test) + pairSize << std::endl;
		std::cout << std::endl;
		int	tmp;
		if (startI < indexPend)
			tmp = mainIndex[indexMain];
		else
			tmp = startI;
		std::cout << "correct pos = " << indexPend - pairSize << std::endl;
		std::cout << "tmp = " << tmp << std::endl;
		std::cout << "startI = " << startI << " indexPend = " << indexPend << " startE = " << startE << std::endl;
		std::cout << "mainIndex before" << std::endl;
		for (ItDq it = mainIndex.begin(); it != mainIndex.end(); ++it)
			std::cout << *it << std::endl;
		std::cout << "pendIndex before" << std::endl;
		for (ItDq it = pendIndex.begin(); it != pendIndex.end(); ++it)
			std::cout << *it << std::endl;
		for (ItDq it = mainIndex.begin(); it != mainIndex.end(); ++it)
		{
			if (startI > indexPend)
			{
				if (*it > startI && *it < indexPend)
					*it += pairSize;
			}
			else
			{
				if (*it <= startI && *it > indexPend)
					*it -= pairSize;
			}
		}
		for (ItDq it = pendIndex.begin(); it != pendIndex.end(); ++it)
		{
			if (*it > startI && *it < indexPend)
				*it += pairSize;
		}
		std::cout << "mainIndex after" << std::endl;
		for (ItDq it = mainIndex.begin(); it != mainIndex.end(); ++it)
			std::cout << *it << std::endl;
		std::cout << "pendIndex after" << std::endl;
		for (ItDq it = pendIndex.begin(); it != pendIndex.end(); ++it)
			std::cout << *it << std::endl;
		mainIndex.insert(mainIndex.begin() + indexMain, tmp);
	}
	else
		mainIndex.insert(mainIndex.begin() + indexMain, indexPend);
	this->printDeque();
	std::cout << "mainIndex in insertPair" << std::endl;
	for (ItDq it = mainIndex.begin(); it != mainIndex.end(); ++it)
		std::cout << *it << std::endl;
	std::cout << "pendIndex in insertPair" << std::endl;
	for (ItDq it = pendIndex.begin(); it != pendIndex.end(); ++it)
		std::cout << *it << std::endl;
}

// void	PmergeMe::insertDeque(ItDq end, int pairSize)
// {
// 	ItDq	start = this->deque.begin();

// 	if (pairSize == std::distance(start, end) || std::distance(start, end) / pairSize == 2)
// 		return ;
// 	std::deque<std::pair<ItDq, ItDq> >				main;
// 	std::deque<std::pair<ItDq, ItDq> >				pend;
// 	std::deque<std::pair<ItDq, ItDq> >::iterator	startP;
// 	std::deque<std::pair<ItDq, ItDq> >::iterator	endP;
// 	size_t											currJ = 3;
// 	size_t											prevJ = 1;

// 	this->ceatePairs(main, pend, end, pairSize);
// 	endP = pend.end();
// 	while (true)
// 	{
// 		std::deque<std::pair<ItDq, ItDq> >::iterator	tmp;
// 		size_t											endJ;

// 		if (pend.size() >= currJ - 1)
// 		{
// 			startP = std::prev(pend.end(), currJ - 1);
// 			endJ = currJ + prevJ - 1;
// 		}
// 		else
// 		{
// 			startP = std::prev(pend.end(), pend.size());
// 			endJ = main.size() - 1;
// 		}
// 		tmp = startP;
// 		while (startP != endP)
// 		{
// 			size_t iMain = this->binarySearch(main, *std::prev(startP->second), endJ);
// 			this->insertPair(main, pend, startP, pairSize, iMain);
// 			if (iMain < main.size())
// 				main.insert(main.begin() + iMain, *startP);
// 			else
// 				main.push_back(*startP);
// 			startP++;
// 		}
// 		endP = tmp;
// 		nextJacobsthal(prevJ, currJ);
// 		if (endP == pend.begin())
// 			break ;
// 	}
// }

int	PmergeMe::binarySearch(std::deque<std::pair<ItDq, ItDq> > pairs, int target, int end)
{
	int low = 0, mid = 0, high = end;

	while (low <= high && static_cast<size_t>(low) < pairs.size())
	{
		mid = low + (high - low) / 2;
		this->compare++;
		if (*std::prev(pairs[mid].second) < target)
			low = mid + 1;
		else if (*std::prev(pairs[mid].second) > target)
			high = mid - 1;
		else
			return (mid);
	}
	return (low);
}

// void	PmergeMe::ceatePairs(std::deque<std::pair<ItDq, ItDq> > &main, std::deque<std::pair<ItDq, ItDq> > &pend,
// 								std::deque<int>::iterator end, int pairSize)
// {
// 	std::deque<int>::iterator	start = this->deque.begin();
// 	bool						odd = true;

// 	main.push_back(std::pair<ItDq, ItDq>(start, start + pairSize));
// 	main.push_back(std::pair<ItDq, ItDq>(start + pairSize, start + (pairSize * 2)));
// 	start += (pairSize * 2);
// 	for (; start != end; start += pairSize)
// 	{
// 		if (odd)
// 			pend.push_front(std::pair<ItDq, ItDq>(start, start + pairSize));
// 		else
// 			main.push_back(std::pair<ItDq, ItDq>(start, start + pairSize));
// 		odd = !odd;
// 	}
// }

void	nextJacobsthal(size_t &prevJ, size_t &currJ)
{
	size_t	nextJ = currJ + 2 * prevJ;
	prevJ = currJ;
	currJ = nextJ;
}

void	PmergeMe::insertPair(std::deque<std::pair<ItDq, ItDq> > &main, std::deque<std::pair<ItDq, ItDq> > &pend,
								std::deque<std::pair<ItDq, ItDq> >::iterator b, int pairSize, int index)
{
	ItDq			end;
	std::deque<int>	tmp;
	std::deque<int>	offsetM;
	std::deque<int>	offsetP;
	int				offsetE;
	int				offsetI;

	if (b->second == this->deque.end())
		offsetE = this->deque.size();
	else
		offsetE = std::distance(this->deque.begin(), b->second);
	if (main.size() == static_cast<size_t>(index))
		offsetI = index;
	else
		offsetI = std::distance(this->deque.begin(), main[index].first);
	if (offsetI == offsetE)
		return ;
	for (ItDq it = b->first; it != b->second; ++it)
		tmp.push_back(*it);
	for (std::deque<std::pair<ItDq, ItDq> >::iterator it = main.begin(); it != main.end(); ++it)
		offsetM.push_back(std::distance(this->deque.begin(), it->first));
	for (std::deque<std::pair<ItDq, ItDq> >::iterator it = pend.begin(); it != pend.end(); ++it)
		offsetP.push_back(std::distance(this->deque.begin(), it->first));


	this->deque.insert(this->deque.begin() + offsetI, tmp.begin(), tmp.end());

	if (this->deque.begin() + offsetE == this->deque.end())
		this->deque.erase(this->deque.begin() + offsetE);
	else
		this->deque.erase(this->deque.begin() + offsetE, this->deque.begin() + offsetE + pairSize);


	int	i = 0;
	for (std::deque<std::pair<ItDq, ItDq> >::iterator it = main.begin(); it != main.end(); ++it)
	{
		if (offsetM[i] >= offsetI && offsetM[i] < offsetE)
		{
			it->first = this->deque.begin() + offsetM[i] + pairSize;
			it->second = std::next(it->first, pairSize);
		}
		else
		{
			it->first = this->deque.begin() + offsetM[i];
			it->second = std::next(it->first, pairSize);
		}
		i++;
	}
	i = 0;
	for (std::deque<std::pair<ItDq, ItDq> >::iterator it = pend.begin(); it != pend.end(); ++it)
	{
		if (it != b)
		{
			if (offsetP[i] >= offsetI && offsetP[i] < offsetE)
			{
				it->first = this->deque.begin() + offsetP[i] + pairSize;
				it->second = std::next(it->first, pairSize);
			}
			else
			{
				it->first = this->deque.begin() + offsetP[i];
				it->second = std::next(it->first, pairSize);
			}
		}
		else
		{
			it->first = this->deque.begin() + offsetI;
			it->second = std::next(it->first, pairSize);
		}
		i++;
	}
}
