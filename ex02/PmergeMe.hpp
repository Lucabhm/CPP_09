/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:07:46 by lbohm             #+#    #+#             */
/*   Updated: 2025/02/20 11:28:48 by lbohm            ###   ########.fr       */
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
	public:
		using iteratorDq = std::deque<int>::iterator;

		PmergeMe(void);
		PmergeMe(std::vector<std::string> input);
		PmergeMe(const PmergeMe &cpy);
		PmergeMe	&operator= (const PmergeMe &cpy);
		~PmergeMe(void);
		void	printDeque(void);
		void	printVec(void);
		void	sortData(void);
		void	sortDeque(iteratorDq end, int pairSize);
		void	mergeDeque(iteratorDq end, int pairSize);
		void	insertDeque(iteratorDq end, int pairSize);
		int		binarySearch(std::deque<std::pair<iteratorDq, iteratorDq> > pairs, int target);
		// void	sortDeque(int end, int pairSize);
		// void	mergeDeque(int end, int pairSize);
		// bool	insertDeque(int end, int pairSize);
		// int		binarySearch(std::deque<std::pair<int, int> > pairs, int target);
};

#endif