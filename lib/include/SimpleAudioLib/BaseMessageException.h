/**
 * Simple Audio Library - Base Message Exception.
 *
 * LICENSE:
 *	
 *	The MIT License (MIT)
 *
 *	Copyright (c) 2013-2016 by Andy Liebke. All rights reserved.
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 * 	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in
 *	all copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *	THE SOFTWARE.
 *
 * @author		Andy Liebke<coding@andysmiles4games.com>
 * @file		Header/SimpleAudioLib/BaseMessageException.h
 * @version 	1.0.1 01-Jan-16
 * @copyright	Copyright (c) 2013-2016 by Andy Liebke. All rights reserved. (http://andysmiles4games.com)
 */
#ifndef __BASE_MESSAGE_EXCEPTION_H__
#define __BASE_MESSAGE_EXCEPTION_H__

#include <exception>
#include <string>

/**
 * Simple Audio Library Namespace.
 */
namespace SimpleAudioLib
{
	/**
	 * Base Message Exception Class.
	 */
	class BaseMessageException : public std::exception
	{
		public:
			
			/**
			 * Creates new instance of this class.
			 *
			 * @param message - string including exception message
			 */
			BaseMessageException(const std::string message);
			
			/**
			 * Creates new instance by copying another instance of this class.
			 *
			 * @param src - reference to the other instance of this class
			 */
			BaseMessageException(const BaseMessageException &src);
			
			/**
			 * Releases this instance of this class.
			 */
			virtual ~BaseMessageException(void) throw();
			
			/**
			 * Assigns data by another instance of this class.
			 *
			 * @param src - reference to the other instance of this class
			 * @return reference to this instance of this class
			 */
			BaseMessageException& operator = (const BaseMessageException &src);
			
			/**
			 * Returns exception message.
			 *
			 * @return string including exception message
			 */
			virtual const char* what(void) const throw();
			
		private:
		
			/**
			 * Stores exception message.
			 */
			std::string _message;
	};
}

#endif
