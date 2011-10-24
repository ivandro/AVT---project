// This file is part of CGLib.
//
// CGLib is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// CGLib is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CGLib; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
// Copyright 2007 Carlos Martinho

#ifndef TEST_H
#define TEST_H

#include <cassert>
#include <iostream>
#include <string>
#include <stdexcept>

#define TEST_EXCEPTION(e,x)\
	try{ x; assert(0); } catch(e&) {}

#define TEST(x)\
    x(); _testCount++;

#define CHECK(x)\
	cg::Test::check(x,#x,__LINE__);

namespace cg {

	/** cg::Test is an unit testing class.
	 *  To create a new unit test, create a new subclass of cg::Test, and implement
	 *  the cg::Test::test method, by calling each individual test using the macro
	 *  TEST. Within each test use the macro CHECK to assert if a condition is true
	 *  (as for the assert instruction), and the macro TEST_EXCEPTION to verify that 
	 *  an exception is thrown.
	 */
	class Test {

	protected:
		/**	The identification of the Test.
		 */
		std::string _name;
		
		/**	Counts the number of executed tests.
		 */
		int _testCount;

	public:
		/**	Creates a Test with a given name.
		 *	\param	name The name of the test.
		 */
		Test(std::string name) {
			_name = name;
		}
		
		/**	Destructor.
		 */
		virtual ~Test() {}

		/**	Executes a Test.
		 */
		void do_test() {
			std::cout << _name << std::endl;
			_testCount = 0;
			try {
				test();
			} catch(std::exception& e) {
				std::cout << e.what() << std::endl;
			}
			std::cout << "    " << _testCount << " tests.";
		}

		virtual void test() = 0;

		/**	Verifies if a given condition is accomplished. If not, prints 
		 *	to the standard output the condition followed by the line number 
		 *	where the failure occurred.
		 *	\param	condition	The condition to be verified.
		 *	\param	label		A string representing the condition to be verified.
		 *	\param	line		The line where the condition was not verified.
		 */
		static void check(bool condition, const std::string label, long line) {
			if( condition == false ) {
				std::cout << "    fail [line " << line << "]: " << label << std::endl;
			}
		}
	};

}

#endif // TEST_H
