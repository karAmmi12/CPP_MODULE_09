/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:46:53 by kammi             #+#    #+#             */
/*   Updated: 2024/12/23 16:11:28 by kammi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <string>
# include <cmath>
# include <sstream>

class   RPN
{
    private:
        std::stack<double>  _stack;
        std::string         _input;
        bool                _isOperator(char c); 
           
    public:
        RPN();
        RPN(const RPN &other);
        ~RPN();

        RPN &operator=(const RPN &other);

        void    calculate(const std::string &input);

        //Exceptions
        class   InvalidExpressionException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };

        class   DivisionByZeroException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };
};

#endif