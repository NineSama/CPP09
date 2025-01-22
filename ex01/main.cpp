/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasenin <amasenin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:31:26 by amasenin          #+#    #+#             */
/*   Updated: 2025/01/20 20:13:48 by amasenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
        return (std::cerr << "Error: bad input. Tuto: ./RPN \".....\"" << std::endl, 1);
    
    RPN rpn;
    rpn.processInput(av[1]);
    return (0);
}