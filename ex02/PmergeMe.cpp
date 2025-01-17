/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:47:22 by kammi             #+#    #+#             */
/*   Updated: 2025/01/15 13:27:57 by kammi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(): _vectorTime(0), _listTime(0), _parsingTime(0), _deque(0), _dequeTime(0)
{
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	*this = other;
}

PmergeMe::~PmergeMe()
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_vector = other._vector;
		_list = other._list;
		_vectorTime = other._vectorTime;
		_listTime = other._listTime;
		_parsingTime = other._parsingTime;
		_deque = other._deque;
		_dequeTime = other._dequeTime;
	}
	return *this;
}

int	 ft_stoi(const std::string &str)
{
	int ret;
	std::stringstream ss(str);

	ss >> ret;
	if (ss.fail() || ss.bad())
		throw std::invalid_argument("Invalid argument");
	return ret;
}

//PARSING______________________________________________________

void	PmergeMe::parsing(char const **av)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);
	
	int i = 1;
	int value = 0;

	while (av[i])
	{
		value = ft_stoi(av[i]);
		if (value < 0)
		{
			throw InvalidArgument();
			return;
		}
			
		_vector.push_back(value);
		_list.push_back(value);
		_deque.push_back(value);
		i++;
	}
	gettimeofday(&end, NULL);
	_parsingTime = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
	
}

//DISPLAY______________________________________________________


void	PmergeMe::display()
{
	//std::cout << "Vector: ";
	for (std::vector<int>::iterator it = _vector.begin(); it != _vector.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;	

	// std::cout << "List: ";
	// for (std::list<int>::iterator it = _list.begin(); it != _list.end(); ++it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl;

	// std::cout << "Deque: ";
	// for (std::deque<int>::iterator it = _deque.begin(); it != _deque.end(); ++it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl;
}

void	PmergeMe::showTime()
{
	//std::cout << "Time to parse the arguments: " << _parsingTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector: " << _vectorTime << " µs" << std::endl;
	std::cout << "Time to process a range of " << _list.size() << " elements with std::list: " << _listTime << " µs" << std::endl;
	std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque: " << _dequeTime << " µs" << std::endl;
}

//CHECK IF SORTED______________________________________________________

bool	PmergeMe::isSorted()
{
	std::vector<int> tmp = _vector;
	std::list<int> tmp2 = _list;
	std::deque<int> tmp3 = _deque;
	
	for (size_t i = 0; i < tmp.size() - 1; i++)
	{
		if (tmp[i] > tmp[i + 1])
			return false;
	}
	for (std::list<int>::iterator it = tmp2.begin(); it != tmp2.end(); ++it)
	{
		
		if (*it > *_advance(it, 1) && _advance(it, 1) != tmp2.end())
			return false;
		
			
	}
	for (size_t i = 0; i < tmp3.size() - 1; i++)
	{
		if (tmp3[i] > tmp3[i + 1])
			return false;
	}
	
	return true;
	
}


/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
//SORTING ALGORITHM WITH VECTOR______________________________________________________

void	PmergeMe::mergeV(std::vector<int> &highs, int left, int mid, int right)
{
	int n1 = mid - left + 1; // taille du tableau de gauche
	int n2 = right - mid; // taille du tableau de droite
	std::vector<int> L(n1); // tableau de gauche
	std::vector<int> R(n2);// tableau de droite

	// remplir les tableaux
	for (int i = 0; i < n1; i++)
		L[i] = highs[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = highs[mid + 1 + j];

	
	//*************visual */

	//   std::cout << "Merging left: ";
	// for (int i = 0; i < n1; i++)
	//	 std::cout << L[i] << " ";
	// std::cout << "and right: ";
	// for (int j = 0; j < n2; j++)
	//	 std::cout << R[j] << " ";
    // std::cout << std::endl;


	int i = 0;
	int j = 0;
	int k = left;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			highs[k] = L[i];
			i++;
		}
		else
		{
			highs[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		highs[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		highs[k] = R[j];
		j++;
		k++;
	}

	//*********visual */
	
	//   std::cout << "Merging left: ";
	// for (int i = 0; i < n1; i++)
	//	 std::cout << L[i] << " ";
	// std::cout << "and right: ";
	// for (int j = 0; j < n2; j++)
	//	 std::cout << R[j] << " ";
	// std::cout << std::endl;
}

void	PmergeMe::mergeSortV(std::vector<int> &highs, int begin, int end)
{
	if (begin < end)
	{
		int mid = (begin + end) / 2;

		//*************visual */
		//  std::cout << "Sorting left part: ";
        // for (int i = begin; i <= mid; i++)
        //     std::cout << highs[i] << " ";
        // std::cout << std::endl;
		
		mergeSortV(highs, begin, mid);

		//*************visual */
		//  std::cout << "Sorting right part: ";
		// for (int i = mid + 1; i <= end; i++)
		// 	std::cout << highs[i] << " ";
		// std::cout << std::endl;		
		
		
		mergeSortV(highs, mid + 1, end);
		mergeV(highs, begin, mid, end);
	}
}

int	PmergeMe::binarySearchV(std::vector<int> &highs, int low)
{
	int begin = 0;
	int end = highs.size() - 1;
	int mid;

	while (begin <= end)
	{
		mid = (begin + end) / 2;
		if (highs[mid] == low)
			return mid;
		if (highs[mid] < low)
			begin = mid + 1;
		else
			end = mid - 1;
	}
	return begin;
}

/***********************visual */
// int	PmergeMe::binarySearchV(std::vector<int> &highs, int low)
// {
// 	int	begin = 0;
// 	int	end = highs.size() - 1;
// 	int	mid;

// 	std::cout << "Starting binary search for " << low << " in vector: ";
// 	for (size_t i = 0; i < highs.size(); ++i)
// 	{
// 		std::cout << highs[i] << " ";
// 	}
// 	std::cout << std::endl;

// 	while (begin <= end)
// 	{
// 		mid = (begin + end) / 2;
// 		std::cout << "begin: " << begin << ", end: " << end << ", mid: " << mid << ", highs[mid]: " << highs[mid] << std::endl;

// 		if (highs[mid] == low)
// 		{
// 			std::cout << "Found " << low << " at index " << mid << std::endl;
// 			return mid;
// 		}
// 		if (highs[mid] < low)
// 		{
// 			std::cout << low << " is greater than " << highs[mid] << ", moving begin to " << mid + 1 << std::endl;
// 			begin = mid + 1;
// 		}
// 		else
// 		{
// 			std::cout << low << " is less than " << highs[mid] << ", moving end to " << mid - 1 << std::endl;
// 			end = mid - 1;
// 		}
// 	}
// 	std::cout << "Did not find " << low << ", should be inserted at index " << begin << std::endl;
// 	return begin;
// }

void	PmergeMe::sortVector()
{
	//recuperer le temps actuel
	struct timeval start, end;
	gettimeofday(&start, NULL);
	
	std::vector<int>	highs;
	std::vector<int>	lows;
	
	int size = _vector.size();
	if (size % 2)
	{
		size--;
		highs.push_back(_vector[size]);
	}
	for (int i = 0; i < size; i += 2)
	{
		if (_vector[i] > _vector[i + 1])
		{
			highs.push_back(_vector[i]);
			lows.push_back(_vector[i + 1]);
		}
		else
		{
			highs.push_back(_vector[i + 1]);
			lows.push_back(_vector[i]);
		}
	}

	//************visual */
	// std::cout << "Highs: ";
	// for (size_t i = 0; i < highs.size(); i++)
	// 	std::cout << highs[i] << " ";
	// std::cout << std::endl;
	// std::cout << "Lows: ";
	// for (size_t i = 0; i < lows.size(); i++)
	// 	std::cout << lows[i] << " ";
	// std::cout << std::endl;

	// trier les hights avec un tri fusion
	mergeSortV(highs, 0, highs.size() - 1);

	// inserer les lows dans highs recherchant la bonne place avec une recherche binaire
	int indexInsert;
	for (size_t i = 0; i < lows.size(); i++)
	{
		indexInsert = binarySearchV(highs, lows[i]);
		highs.insert(highs.begin() + indexInsert, lows[i]);
	}
	
	_vector = highs;

	//recuperer le temps actuel
	gettimeofday(&end, NULL);
	_vectorTime = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
}


/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
//SORTING ALGORITHM WITH LIST______________________________________________________

void	PmergeMe::mergeL(std::list<int> &highs, int left, int mid, int right)
{
	int n1 = mid - left + 1; // taille du tableau de gauche
	int n2 = right - mid; // taille du tableau de droite
	
	std::list<int> L; // tableau de gauche
	std::list<int> R;// tableau de droite
	
	
	// remplir les tableaux
	std::list<int>::iterator it = _advance(highs.begin(), left); 
	for (int i = 0; i < n1; i++)
	{
		L.push_back(*it);
		++it;
	}
	
	it = _advance(highs.begin(), mid + 1);
	for (int i = 0; i < n2; i++)
	{
		R.push_back(*it);
		++it;
	}
	int i = 0;
	int j = 0;
	it = _advance(highs.begin(), left);
	
	
	std::list<int>::iterator itL = L.begin();
	std::list<int>::iterator itR = R.begin();


	while (i < n1 && j < n2)
	{
		if (*itL <= *itR)
		{
			*it = *itL;
			++itL;
			i++;
		}
		else
		{
			*it = *itR;
			++itR;
			j++;
		}
		++it;
	}
	
	while (i < n1)
	{
		*it = *itL;
		++itL;
		++it;
		i++;
	}
	
	while (j < n2)
	{
		*it = *itR;
		++itR;
		++it;
		j++;
	}

}

	
void	PmergeMe::mergeSortL(std::list<int> &highs, int begin, int end)
{
	if (begin < end)
	{
		int mid = begin + (end - begin) / 2;
		mergeSortL(highs, begin, mid);
		mergeSortL(highs, mid + 1, end);
		mergeL(highs, begin, mid, end);
	}
}

int	PmergeMe::binarySearchL(std::list<int> &highs, int low)
{
	int begin = 0;
	int end = highs.size() - 1;
	int mid;

	while (begin <= end)
	{
		mid = (begin + end) / 2;
		std::list<int>::iterator it = highs.begin();
		std::advance(it, mid);
		if (*it == low)
			return mid;
		if (*it < low)
			begin = mid + 1;
		else
			end = mid - 1;
	}
	return begin;
}


void	PmergeMe::sortList()
{
	//recuperer le temps actuel
	struct timeval start, end;
	gettimeofday(&start, NULL);
	
	std::list<int>	highs;
	std::list<int>	lows;
	
	int size = _list.size();
	if (size % 2)
	{
		size--;
		highs.push_back(*_list.rbegin());
	}
	
	std::list<int>::iterator it = _list.begin();
	
	for (int i = 0; i < size; i += 2)
	{
		if (*it > *_advance(it, 1))
		{
			highs.push_back(*it);
			lows.push_back(*_advance(it, 1));
		}
		else
		{
			highs.push_back(*_advance(it, 1));
			lows.push_back(*it);
		}
		it = _advance(it, 2);
	}

	
	// trier les hights avec un tri fusion
	mergeSortL(highs, 0, highs.size() - 1);
	
	
	// inserer les lows dans highs recherchant la bonne place avec une recherche binaire
	int indexInsert;
	for (std::list<int>::iterator it = lows.begin(); it != lows.end(); ++it)
	{
		indexInsert = binarySearchL(highs, *it);
		std::list<int>::iterator itH = highs.begin();
		std::advance(itH, indexInsert);
		highs.insert(itH, *it);
	}

	_list = highs;
	
	//recuperer le temps actuel
	gettimeofday(&end, NULL);
	_listTime = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
}

//ITERATOR ADVANCE

std::list<int>::iterator	PmergeMe::_advance(std::list<int>::iterator it, int n)
{
	std::advance(it, n);
	return it;
}

std::list<int>::const_iterator	PmergeMe::_advance(std::list<int>::const_iterator it, int n) const
{
	std::advance(it, n);
	return it;
}

// EXCEPTIONS______________________________________________________

const char* PmergeMe::InvalidArgument::what() const throw()
{
	return "Error";
}



/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
//SORTING ALGORITHM WITH DEQUE______________________________________________________


void PmergeMe::mergeD(std::deque<int> &highs, int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;
	std::deque<int> L(n1);
	std::deque<int> R(n2);

	for (int i = 0; i < n1; i++)
		L[i] = highs[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = highs[mid + 1 + j];

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			highs[k] = L[i];
			i++;
		}
		else
		{
			highs[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		highs[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		highs[k] = R[j];
		j++;
		k++;
	}
}

void PmergeMe::mergeSortD(std::deque<int> &highs, int begin, int end)
{
	if (begin < end)
	{
		int mid = (begin + end) / 2;
		mergeSortD(highs, begin, mid); // trier la partie gauche du tableau
		mergeSortD(highs, mid + 1, end); // trier la partie droite du tableau
		mergeD(highs, begin, mid, end); // fusionner les deux parties triées du tableau
	}
}

int PmergeMe::binarySearchD(std::deque<int> &highs, int low)
{
	int begin = 0;
	int end = highs.size() - 1;
	int mid;

	while (begin <= end)
	{
		mid = (begin + end) / 2;
		if (highs[mid] == low)
			return mid;
		if (highs[mid] < low)
			begin = mid + 1;
		else
			end = mid - 1;
	}
	return begin;
}

void PmergeMe::sortDeque()
{
	struct timeval start, end;
	gettimeofday(&start, NULL);

	std::deque<int> highs;
	std::deque<int> lows;

	int size = _deque.size();
	if (size % 2)
	{
		size--;
		highs.push_back(_deque[size]);
	}
	for (int i = 0; i < size; i += 2)
	{
		if (_deque[i] > _deque[i + 1])
		{
			highs.push_back(_deque[i]);
			lows.push_back(_deque[i + 1]);
		}
		else
		{
			highs.push_back(_deque[i + 1]);
			lows.push_back(_deque[i]);
		}
	}

	mergeSortD(highs, 0, highs.size() - 1);

	int indexInsert;
	for (size_t i = 0; i < lows.size(); i++)
	{
		indexInsert = binarySearchD(highs, lows[i]);
		highs.insert(highs.begin() + indexInsert, lows[i]);
	}

	_deque = highs;

	gettimeofday(&end, NULL);
	_dequeTime = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
}
