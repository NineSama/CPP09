/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myStoi.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasenin <amasenin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 22:50:00 by amasenin          #+#    #+#             */
/*   Updated: 2025/01/21 23:23:45 by amasenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <climits>

int PmergeMe::myStoi(const char *str)
{
    int result = 0;
    int negative = false;
    int i = 0;

    for (i = 0; str[i] == '-' || str[i] == '+' || str[i] == ' ' || str[i] == '\t'; i++)
    {
        if (str[i] == '-')
            negative++;
    }

    if (negative % 2 == 1)
        throw (std::out_of_range("Error: negative number."));
    
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            throw (std::invalid_argument("Error: invalid character in sequence."));
        
        int digit = str[i] - 48;

        if (result > (INT_MAX / 10) || (result == INT_MAX / 10 && digit > INT_MAX % 10))
            throw (std::out_of_range("Error: number out of range."));
        
        result = result * 10 + digit;
        i++;
    }
    return (result);
}