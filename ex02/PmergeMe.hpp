/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:47:16 by kammi             #+#    #+#             */
/*   Updated: 2024/12/23 16:42:46 by kammi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <exception>
#include <sys/time.h>
#include <iterator>
#include <deque>


class   PmergeMe
{
    private:
        std::vector<int>    _vector;
        std::list<int>     	_list;
        long                _vectorTime;
        long                _listTime;
		long				_parsingTime;
		std::deque<int>		_deque;
		long				_dequeTime;
		
		//parsing
		void    	_parsing(const char **av);

		//vector
		void		mergeSortV(std::vector<int> &highs, int begin, int end);
		void		mergeV(std::vector<int> &highs, int left, int mid, int right);
		int			binarySearchV(std::vector<int> &highs, int low);

		//list
		void		mergeSortL(std::list<int> &highs, int begin, int end);
		void		mergeL(std::list<int> &highs, int left, int mid, int right);
		int			binarySearchL(std::list<int> &highs, int low);

		//deque
        void        mergeSortD(std::deque<int> &highs, int begin, int end);
        void        mergeD(std::deque<int> &highs, int left, int mid, int right);
        int         binarySearchD(std::deque<int> &highs, int low);

		//utils 
		std::list<int>::iterator	_advance(std::list<int>::iterator it, int n);
		std::list<int>::const_iterator	_advance(std::list<int>::const_iterator it, int n) const;

		
        
    public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		~PmergeMe();
        
		PmergeMe &operator=(const PmergeMe &other);

		void	parsing(char const **av);
		
		void	display();
		
		void	sortVector();
		void	sortList();
		void    sortDeque();
		
		void	showTime();

		bool	isSorted();

		class	InvalidArgument : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		
		

		

};

#endif

