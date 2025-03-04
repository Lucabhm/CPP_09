/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:07:46 by lbohm             #+#    #+#             */
/*   Updated: 2025/03/04 09:10:59 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <deque>
# include <vector>
# include <regex>
# include <sstream>
# include <chrono>

class PmergeMe
{
	private:
		std::deque<int>		deque;
		std::vector<int>	vector;
	public:
		using	ItDq = std::deque<int>::iterator;
		using	ItVec = std::vector<int>::iterator;

		PmergeMe(void);
		PmergeMe(std::vector<std::string> input);
		PmergeMe(const PmergeMe &cpy);
		PmergeMe	&operator= (const PmergeMe &cpy);
		~PmergeMe(void);
		
		void	sortData(void);
		void	printResult(std::deque<int> befor, double diffDq, double diffVec);

		void	printDeque(void);
		void	sortDeque(ItDq end, int pairSize);
		void	mergeDeque(ItDq end, int pairSize);
		void	insertDeque(ItDq end, int pairSize);


		void	printVec(void);
		void	sortVec(ItVec end, int pairSize);
		void	mergeVec(ItVec end, int pairSize);
		void	insertVec(ItVec end, int pairSize);
};

void	nextJacobsthal(size_t &prevJ, size_t &currJ);

template <typename T>
void	createPairs(T &mainIndex, T &pendIndex, int pairSize, size_t containerSize);

template <typename T>
int		binarySearch(T &container, T mainIndex, int targetIndex, int endIndex);

template <typename T>
void	insertPair(T &container, T &mainIndex, T &pendIndex, int indexMain, int indexPend, int pairSize);

# include "PmergeMe.tpp"

#endif