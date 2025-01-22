/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasenin <amasenin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 00:38:30 by amasenin          #+#    #+#             */
/*   Updated: 2025/01/20 13:57:13 by amasenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &toCopy) : _data(toCopy._data) {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange const &copy)
{
    if (this != &copy)
        _data = copy._data;
    return (*this);
}

void    BitcoinExchange::loadData(std::string const &filename)
{
    std::ifstream   file(filename.c_str());
    try 
    {
        if (!file.is_open())
           throw (std::runtime_error("Error: could not open data file."));
    }
    catch(const std::exception& e)
    {std::cerr << e.what() << std::endl;}
    
    
    std::string     line;
    std::getline(file, line); //skip header
    while (std::getline(file, line))
    {
        try
        {
            std::istringstream  iss(line);
            std::string         date;
            std::string         ratestr;

            if (std::getline(iss, date, ',') && std::getline(iss, ratestr))
            {
                float rate = std::atof(ratestr.c_str());
                _data[date] = rate;
            }
            else
                throw (std::invalid_argument("Error: invalid input: " + line));
        }
        catch (std::exception const &e)
        {std::cerr << e.what() << std::endl;}
    }
    file.close();
}

bool BitcoinExchange::isValidDate(std::string const &date) const
{
    if (date.length() != 10)
        return false;
    
    int year;
    int month;
    int day;
    int daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    std::istringstream iss(date);

    iss >> year;
    iss.ignore();
    iss >> month;
    iss.ignore();
    iss >> day;
    if (iss.fail())
        return false;
    else if (year < 2009 || year > 2024)
        return false;
    else if (month < 1 || month > 12)
        return false;
    else
    {
        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
            daysPerMonth[1] = 29;
    }
    return (day > 0 && day <= daysPerMonth[month - 1]);
}

bool    BitcoinExchange::isValidValue(std::string const &valuestr, float &value) const
{
    std::string str = valuestr;
    if (!str.empty() && str[str.size() - 1] == 'f')
        str = str.substr(0, str.size() - 1);
    std::istringstream  iss(str);
    iss >> value;
    if (iss.fail())
        return false;
    char leftover;
    if (iss >> leftover)
        return false;
    return (value >= 0 && value <= 1000);
}

void    BitcoinExchange::processInput(std::string const &filename)
{
    std::ifstream inputFile(filename.c_str());
    try
    {
        if (!inputFile.is_open())
            throw (std::runtime_error("Error: could not open file."));
    }
    catch (std::exception const &e)
    {std::cerr << e.what() << std::endl;}

    std::string line;
    while (std::getline(inputFile, line))
    {
        try
        {
            std::istringstream iss(line);
            std::string date;
            std::string valuestr;

            if (!std::getline(iss, date, '|') || !std::getline(iss, valuestr))
                throw (std::runtime_error("Error: invalid input: " + line));

            date = trim(date);
            valuestr = trim(valuestr);
            
            if (!isValidDate(date))
                throw (std::invalid_argument("Error: invalid date: " + date));
            
            float value;
            if (!isValidValue(valuestr, value))
                throw (std::invalid_argument("Error: invalid value: " + valuestr));

            float rate = getRate(date);
            std::cout   << date
                        << " => "
                        << value
                        << " = "
                        << std::fixed
                        << std::setprecision(1)
                        << (value * rate)
                        << std::endl;
        }
        catch (std::exception const &e)
        {std::cerr << e.what() << std::endl;}
    }
    inputFile.close();
}

float   BitcoinExchange::getRate(std::string const &date) const
{
    std::map<std::string, float>::const_iterator it = _data.lower_bound(date);
    if (it == _data.end() || it->first != date)
    {
        if (it != _data.begin())
            --it;
    }
    return it->second;
}

std::string BitcoinExchange::trim(std::string const &str)
{
    std::size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos)
        return ("");
    
    std::size_t last = str.find_last_not_of(" \t");
    return (str.substr(first, (last - first + 1)));
}