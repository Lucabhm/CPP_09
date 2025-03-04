/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:10:41 by lbohm             #+#    #+#             */
/*   Updated: 2025/03/04 09:13:55 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>
# include <regex>
# include <cctype>
# include <limits>

class RPN
{
	private:
		std::string		input;
		int				result;
	public:
		RPN(void);
		RPN(std::string input);
		RPN(const RPN &cpy);
		RPN	&operator= (const RPN &cpy);
		~RPN(void);
		int	calcRPN(void);
};

std::pair<int, int>	getNbr(std::stack<int> &stack);
int					checkNbr(std::stack<int> &stack, char op);

#endif