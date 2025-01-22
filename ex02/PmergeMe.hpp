/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasenin <amasenin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:05:01 by amasenin          #+#    #+#             */
/*   Updated: 2025/01/22 03:32:10 by amasenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <exception>
#include <climits>
#include <ctime>

class PmergeMe
{
    private:
        std::vector<int> _vector;
        std::deque<int> _deque;
        
        void    parseSequence(char **av);
        int     myStoi(char const *str);

        template <typename T> void  swapPair(T &vec, int i, int j);
        template <typename T> void  fordJohnson(T &vec, int start, int end);
        template <typename T> void  merge(T &vec, int start, int mid, int end);
        
    public:
        PmergeMe();
        PmergeMe(PmergeMe const &toCopy);
        ~PmergeMe();
        PmergeMe& operator=(PmergeMe const &copy);

        void    sort(char **av);
};

#endif