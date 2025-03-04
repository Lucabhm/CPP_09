/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:10:06 by lbohm             #+#    #+#             */
/*   Updated: 2025/03/04 09:13:42 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// fill the mainIndex and pendIndex with the Index of deque
template <typename T>
void	createPairs(T &mainIndex, T &pendIndex, int pairSize, size_t containerSize)
{
	bool	odd = true;

	mainIndex.push_back(pairSize);
	mainIndex.push_back(pairSize * 2);
	for (size_t size = pairSize * 3; size <= containerSize; size += pairSize)
	{
		if (odd)
			pendIndex.push_back(size);
		else
			mainIndex.push_back(size);
		odd = !odd;
	}
}

template <typename T>
int	binarySearch(T &container, T mainIndex, int targetIndex, int endIndex)
{
	int	low = 0, mid, high = endIndex;
	int	value = container[targetIndex];

	while (low <= high)
	{
		mid = low + (high - low) / 2;
		if (static_cast<size_t>(mid) == mainIndex.size())
			return (mid) ;
		if (container[mainIndex[mid] - 1] < value)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return (low);
}

template <typename T>
void	insertPair(T &container, T &mainIndex, T &pendIndex, int indexMain, int indexPend, int pairSize)
{
	int	startI;
	int	startE = indexPend - pairSize;
	T	input;

	if (mainIndex.begin() + indexMain != mainIndex.end())
		startI = mainIndex[indexMain] - pairSize;
	else
		startI = mainIndex[indexMain - 1] + pairSize;
	if (startI != indexPend)
	{
		std::copy(container.begin() + startE, container.begin() + indexPend, std::back_inserter(input));
		container.insert(container.begin() + startI, input.begin(), input.end());
		typename T::iterator	erase;
		if (startI < startE)
			erase = container.erase(container.begin() + startE + pairSize, container.begin() + indexPend + pairSize);
		else
			erase = container.erase(container.begin() + startE, container.begin() + indexPend);
		int	tmp;
		if (startI < indexPend)
			tmp = mainIndex[indexMain];
		else
			tmp = std::distance(container.begin(), erase) + pairSize;
		for (typename T::iterator it = mainIndex.begin(); it != mainIndex.end(); ++it)
		{
			if (*it > startI && *it < indexPend)
				*it += pairSize;
		}
		for (typename T::iterator it = pendIndex.begin(); it != pendIndex.end(); ++it)
		{
			if (*it > startI && *it < indexPend)
				*it += pairSize;
		}
		typename T::iterator	pos = std::lower_bound(mainIndex.begin(), mainIndex.end(), tmp);
		int		find = std::distance(mainIndex.begin(), pos);
		mainIndex.insert(mainIndex.begin() + find, tmp);
	}
	else
		mainIndex.insert(mainIndex.begin() + indexMain, indexPend);
}
