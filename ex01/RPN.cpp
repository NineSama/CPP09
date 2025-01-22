/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasenin <amasenin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:31:23 by amasenin          #+#    #+#             */
/*   Updated: 2025/01/20 20:12:59 by amasenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(RPN const &toCopy)
{
    while (!_data.empty())
        _data.pop();
    
    std::stack<int> tmp = toCopy._data;

    while (!tmp.empty())
    {
        _data.push(tmp.top());
        tmp.pop();
    }
}

RPN::~RPN() {}

RPN&    RPN::operator=(RPN const &copy)
{
    if (this != &copy)
    {
        while (!_data.empty())
            _data.pop();
        
        std::stack<int> tmp = copy._data;

        while (!tmp.empty())
        {
            _data.push(tmp.top());
            tmp.pop();
        }
    }
    return (*this);
}

bool    RPN::isInputValid(std::string const &input) const
{
    for (size_t i = 0; i < input.size(); i++)
    {
        char c = input[i];

        if (c >= '0' && c <= '9')
            continue ;
        else if (isOperator(c) || c == ' ' || c == '\t')
            continue ;
        else
            return false;
    }
    return true;
}

bool    RPN::isOperator(char const c) const
{return (c == '+' || c == '-' || c == '*' || c == '/');}

void    RPN::doTheMaths(char const c)
{
    if (_data.size() < 2)
        throw (std::invalid_argument("Error: insufficient data for operation."));
    
    int b = _data.top();
    _data.pop();
    int a = _data.top();
    _data.pop();
    int result;

    switch (c)
    {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/':
            if (b == 0)
                throw (std::invalid_argument("Error: cannot divide by 0."));
            result = a / b; break;
    }
    _data.push(result);
}

void    RPN::processInput(std::string const &input)
{
    std::string str = input;
    try
    {
        if (!isInputValid(str))
            throw (std::invalid_argument("Error: bad input: " + str));
        
        for (size_t i = 0; i < str.size(); i++)
        {
            char c = str[i];

            if (c == ' ' || c =='\t')
                continue ;
            if (c >= '0' && c <= '9')
                _data.push(str[i] - 48);
            else if (isOperator(c))
                doTheMaths(c);
            else
                throw (std::invalid_argument("Error: invalid character encountered: "));
        }
        if (_data.size() != 1)
            throw (std::invalid_argument("Error: invalid RPN expression."));
        std::cout << _data.top() << std::endl;
    }
    catch (std::exception const &e)
    {std::cerr << e.what() << std::endl;}   
}