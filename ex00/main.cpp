/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasenin <amasenin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 00:38:21 by amasenin          #+#    #+#             */
/*   Updated: 2025/01/20 12:35:34 by amasenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>

int main(int ac, char **av)
{
    if (ac != 2)
        return (std::cerr << "Error: need one file." << std::endl, 1);

    std::ifstream inputFile(av[1]);
    if (!inputFile.is_open())
        return (std::cerr << "Error: could not open file." << std::endl, 2);
    BitcoinExchange Exchange;
    Exchange.loadData("data.csv");
    Exchange.processInput(av[1]);
    return (0);
}