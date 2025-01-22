/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasenin <amasenin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:35:24 by amasenin          #+#    #+#             */
/*   Updated: 2025/01/21 20:38:39 by amasenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac < 2)
        return (std::cerr << "Error: need more arguments" << std::endl, 1);
    
    PmergeMe sequence;
    sequence.sort(av);

    return (0);
}