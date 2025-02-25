/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:07:46 by lbohm             #+#    #+#             */
/*   Updated: 2025/02/25 14:57:17 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <deque>
# include <vector>
# include <regex>
# include <sstream>

class PmergeMe
{
	private:
		std::deque<int>		deque;
		std::vector<int>	vector;
		int					compare;
	public:
		using ItDq = std::deque<int>::iterator;

		PmergeMe(void);
		PmergeMe(std::vector<std::string> input);
		PmergeMe(const PmergeMe &cpy);
		PmergeMe	&operator= (const PmergeMe &cpy);
		~PmergeMe(void);
		void	printDeque(void);
		void	printVec(void);
		void	sortData(void);
		void	sortDeque(ItDq end, int pairSize);
		void	mergeDeque(ItDq end, int pairSize);
		void	insertDeque(ItDq end, int pairSize);
		int		binarySearch(std::deque<std::pair<ItDq, ItDq> > pairs, int target, int end);
		void	ceatePairs(std::deque<std::pair<ItDq, ItDq> > &main, std::deque<std::pair<ItDq, ItDq> > &pend,
							std::deque<int>::iterator end, int pairSize);
		void	insertPair(std::deque<std::pair<ItDq, ItDq> > &main, std::deque<std::pair<ItDq, ItDq> >::iterator &pend, int pairSize, int index);
};

void	nextJacobsthal(size_t &prevJ, size_t &currJ);

#endif