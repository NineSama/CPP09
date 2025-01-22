/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasenin <amasenin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:31:16 by amasenin          #+#    #+#             */
/*   Updated: 2025/01/20 19:45:43 by amasenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <exception>

class RPN
{
    private:
        std::stack<int> _data;
        
        bool    isInputValid(std::string const &input) const;
        bool    isOperator(char const c) const;
        void    doTheMaths(char const c);
        
    public:
        RPN();
        RPN(RPN const &toCopy);
        ~RPN();
        RPN&    operator=(RPN const &copy);

        void    processInput(std::string const &input);
};

#endif