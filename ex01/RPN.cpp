/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:46:57 by kammi             #+#    #+#             */
/*   Updated: 2025/01/14 15:30:18 by kammi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN &other)
{
	*this = other;
}

RPN::~RPN()
{
}

RPN	&RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		_stack = other._stack;
		_input = other._input;
	}
	return *this;
}

void	RPN::calculate(const std::string &input)
{
	bool	isNumber = false;

	_input = input;
		
	for (size_t i = 0; i < _input.size(); i++)
	{
		if (isdigit(_input[i]) || ((_input[i] == '-' || _input[i] == '+') && isdigit(_input[i + 1])))
		{
			if (isNumber)
			{
				std::cout << input[i] << std::endl;
				throw InvalidExpressionException();
			}
				
			
			int sign = 1;
			if (_input[i] == '-' || _input[i] == '+')
			{
				if (_input[i] == '-')
					sign = -1;	
				i++;
			}
			int nbr = _input[i] - '0';
			_stack.push(nbr * sign);
			isNumber = true;
		}
		else 
		{
			isNumber = false;
			if (_isOperator(_input[i]))
			{
				if (_stack.size() < 2)
					throw InvalidExpressionException();
				double a = _stack.top();
				_stack.pop();
				double b = _stack.top();
				_stack.pop();
				if (_input[i] == '+')
					_stack.push(b + a);
				else if (_input[i] == '-')
					_stack.push(b - a);
				else if (_input[i] == '*')
					_stack.push(b * a);
				else if (_input[i] == '/')
				{
					if (a == 0)
						throw DivisionByZeroException();
					_stack.push(b / a);
				}
				else if (_input[i] == '^')
					_stack.push(pow(b, a));
			}
			else if (iswspace(_input[i]))
				continue;
			else
				throw InvalidExpressionException();
		}
	
			
	}
	std::cout << _stack.top() << std::endl;
}

bool	RPN::_isOperator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}


//Exceptions

const char*	RPN::InvalidExpressionException::what() const throw()
{
	return "Invalid expression";
}


const char* RPN::DivisionByZeroException::what() const throw()
{
	return "Division by zero";
}

// Explanation:

// void	RPN::calculate(const std::string &input)
// {
// 	bool	isNumber = false;

// 	_input = input;
		
// 	for (size_t i = 0; i < _input.size(); i++)
// 	{
// 		if (isdigit(_input[i]) || ((_input[i] == '-' || _input[i] == '+') && isdigit(_input[i + 1])))
// 		{
// 			if (isNumber)
// 			{
// 				std::cout << input[i] << std::endl;
// 				throw InvalidExpressionException();
// 			}
				
			
// 			int sign = 1;
// 			if (_input[i] == '-' || _input[i] == '+')
// 			{
// 				if (_input[i] == '-')
// 					sign = -1;	
// 				i++;
// 			}
// 			int nbr = _input[i] - '0';
// 			_stack.push(nbr * sign);
// 			isNumber = true;
// 			std::cout << "Pushed number: " << nbr * sign << " | Current stack state: ";
// 			std::stack<double> temp = _stack;
// 			while (!temp.empty()) 
// 			{
// 				std::cout << temp.top() << " ";
// 				temp.pop();
// 			}
// 			std::cout << std::endl;
// 		}
// 		else 
// 		{
// 			isNumber = false;
// 			if (_isOperator(_input[i]))
// 			{
// 				if (_stack.size() < 2)
// 					throw InvalidExpressionException();
// 				double a = _stack.top();
// 				_stack.pop();
// 				double b = _stack.top();
// 				_stack.pop();
// 				double result = 0;
// 				if (_input[i] == '+')
// 					result = b + a;
// 				else if (_input[i] == '-')
// 					result = b - a;
// 				else if (_input[i] == '*')
// 					result = b * a;
// 				else if (_input[i] == '/')
// 				{
// 					if (a == 0)
// 						throw DivisionByZeroException();
// 					result = b / a;
// 				}
// 				else if (_input[i] == '^')
// 					result = pow(b, a);
// 				_stack.push(result);
// 				std::cout << "Applied operator: " << _input[i] << " | Result: " << result << " | Current stack state: ";
// 				std::stack<double> temp = _stack;
// 				while (!temp.empty()) 
// 				{
// 					std::cout << temp.top() << " ";
// 					temp.pop();
// 				}
// 				std::cout << std::endl;
// 			}
// 			else if (iswspace(_input[i]))
// 				continue;
// 			else
// 				throw InvalidExpressionException();
// 		}
// 	}
// 	std::cout << "Final result: " << _stack.top() << std::endl;
// }