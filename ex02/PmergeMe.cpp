/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasenin <amasenin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:38:42 by amasenin          #+#    #+#             */
/*   Updated: 2025/01/22 03:39:47 by amasenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(PmergeMe const &toCopy)
{
    _vector.clear();
    _vector.insert(_vector.end(), toCopy._vector.begin(), toCopy._vector.end());
    _deque.clear();
    _deque.insert(_deque.end(), toCopy._deque.begin(), toCopy._deque.end());
}

PmergeMe::~PmergeMe() {}

PmergeMe&   PmergeMe::operator=(PmergeMe const &copy)
{
    if (this != &copy)
    {
        _vector.clear();
        _vector.insert(_vector.end(), copy._vector.begin(), copy._vector.end());
        _deque.clear();
        _deque.insert(_deque.end(), copy._deque.begin(), copy._deque.end());
    }
    return (*this);
}

void    PmergeMe::parseSequence(char **av)
{
    for (int i = 1; av[i]; i++)
    {
        for (int j = 0; av[i][j]; j++)
        {
            if (!isdigit(av[i][j]) && av[i][j] != ' ' && av[i][j] != '+')
                throw (std::invalid_argument("Error: invalid character in sequence."));
        }
        int tmp = myStoi(av[i]);
        if (tmp < 0)
            throw (std::out_of_range("Error: number out of range."));
        _vector.push_back(tmp);
        _deque.push_back(tmp);
    }
}

template <typename T>
void    PmergeMe::swapPair(T &vec, int i, int j)
{
    if (vec[i] > vec[j])
    {
        int tmp = vec[j];
        vec[j] = vec[i];
        vec[i] = tmp;
    }
}

template <typename T>
void    PmergeMe::merge(T &vec, int start, int mid, int end)
{
    int one = mid - start +1;
    int two = end - mid;

    std::vector<typename T::value_type> left(one);
    std::vector<typename T::value_type> right(two);

    for (int i = 0; i < one; i++)
    {
        left[i] = vec[start + i];
    }
    for (int i = 0; i < two; i++)
    {
        right[i] = vec[mid + 1 + i];
    }

    int index_one = 0;
    int index_two = 0;
    int index_merged = start;

    while (index_one < one && index_two < two)
    {
        if (left[index_one] <= right[index_two])
        {
            vec[index_merged] = left[index_one];
            index_one++;
        }
        else
        {
            vec[index_merged] = right[index_two];
            index_two++;
        }
        index_merged++;
    }
    while (index_one < one)
    {
        vec[index_merged] = left[index_one];
        index_one++;
        index_merged++;
    }
    while (index_two < two)
    {
        vec[index_merged] = right[index_two];
        index_two++;
        index_merged++;
    }
}

template <typename T>
void    PmergeMe::fordJohnson(T &vec, int start, int end)
{
    if (start < end)
    {
        std::vector<std::pair<int,int> > pairs;
        int n = end - start + 1;
        
        for (int i = start; i <= end - 1; i += 2)
        {
            if (vec[i] > vec[i + 1])
                swapPair(vec, i, i + 1);
            pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
        }

        if (n % 2 != 0)
            pairs.push_back(std::make_pair(vec[end], -1));

        int mid = (start + end) / 2;
        fordJohnson(vec, start, mid);
        fordJohnson(vec, mid + 1, end);
        merge(vec, start, mid, end);
    }
}

void    PmergeMe::sort(char **av)
{
    try
    {
        parseSequence(av);
        std::cout << "Before: ";
        for (size_t i = 0; i < _vector.size(); i++)
            std::cout << _vector[i] << " ";
        std::cout << std::endl;
        
        std::clock_t start = std::clock();
        fordJohnson(_vector, 0, _vector.size() - 1);
        std::clock_t end = std::clock();
        double timeVector = ((double)end - double(start)) / CLOCKS_PER_SEC * 1000;

        std::cout << "After: ";
        for (size_t i = 0; i < _vector.size(); i++)
            std::cout << _vector[i] << " ";
        std::cout << std::endl;
        std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector: " << timeVector << " us" << std::endl;

        start = std::clock();
        fordJohnson(_deque, 0, _deque.size() - 1);
        end = std::clock();
        double timeDeque = ((double)end - double(start)) / CLOCKS_PER_SEC * 1000;
        std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque: " << timeDeque << " us" << std::endl;
        
        // for (size_t i = 0; i < _vector.size() - 1; i++)
        // {
        //     if (_vector[i] > _vector[i + 1])
        //         throw (std::invalid_argument("Error: sequence not sorted."));
        // }
        
    }
    catch (const std::exception &e)
    {std::cerr << e.what() << std::endl;}
}