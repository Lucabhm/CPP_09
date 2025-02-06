/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:10:41 by lbohm             #+#    #+#             */
/*   Updated: 2025/02/06 09:13:25 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>
# include <regex>
# include <cctype>

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

#endif