/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasenin <amasenin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 00:38:33 by amasenin          #+#    #+#             */
/*   Updated: 2025/01/20 13:46:53 by amasenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iomanip>

class BitcoinExchange
{
    private :
        std::map<std::string, float> _data;

        bool isValidDate(std::string const &date) const;
        bool isValidValue(std::string const &valuestr, float &value) const;
        std::string trim(std::string const &str);

    public :
        BitcoinExchange();
        BitcoinExchange(BitcoinExchange const &toCopy);
        ~BitcoinExchange();
        BitcoinExchange& operator=(BitcoinExchange const &copy);

        void    loadData(std::string const &filename);
        void    processInput(std::string const &inputFile);
        float   getRate(std::string const &date) const;
};

#endif