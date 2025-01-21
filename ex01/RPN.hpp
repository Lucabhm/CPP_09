/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:10:41 by lbohm             #+#    #+#             */
/*   Updated: 2025/01/21 23:06:47 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <stack>
# include <regex>

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

#endif