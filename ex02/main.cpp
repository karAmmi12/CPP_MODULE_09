/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:33:50 by kammi             #+#    #+#             */
/*   Updated: 2025/01/14 11:31:24 by kammi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, const char** argv)
{
 if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <number1> <number2> ... <numberN>" << std::endl;
        return 1;
    }

	PmergeMe merge;

	try
	{
		merge.parsing(argv);
		
		if (merge.isSorted())
			{
				std::cout << "the list is already sorted" << std::endl;
				return 0;
			}
		std::cout << "Before:\t";
		merge.display();
        merge.sortVector();
		merge.sortList();
		merge.sortDeque();
        std::cout << "After:\t";
		// std::cout << "is sorted :" << (merge.isSorted()? "true" : "false") << std::endl;
        merge.display();
        merge.showTime();

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	} 
	
	return 0;
}