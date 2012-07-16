// ----------------------------
// projects/deque/TestDeque.c++
// Copyright (C) 2012
// Glenn P. Downing
// ----------------------------

/*
To test the program:
	% ls /usr/include/cppunit/
	...
	HelperMacros.h
	...
	% locate libcppunit.a
	/usr/lib/libcppunit.a
	% g++ -ansi -pedantic -lcppunit -ldl -Wall TestDeque.c++ -o TestDeque.c++.app
	% valgrind TestDeque.c++.app >& TestDeque.out
*/

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <deque>	 // deque
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>	// ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"			 // TestFixture
#include "cppunit/TestSuite.h"			   // TestSuite
#include "cppunit/TextTestRunner.h"		  // TestRunner

#include "Deque.h"

// ---------
// TestDeque
// ---------

using namespace std;

template <typename C>
struct TestDeque : CppUnit::TestFixture {
 
    // ---------------------
    // test_mydeque_equality
	// ---------------------

    void test_mydeque_equality_1() {
	    C d;
		C e;
		CPPUNIT_ASSERT(d == e);
	}
	
	void test_mydeque_equality_2() {
	    C d;
		C e(3, 7);
		CPPUNIT_ASSERT(d != e);
		d = e;
		CPPUNIT_ASSERT(d == e);
	}
	
	void test_mydeque_equality_3() {
	    C d(11, 7);
		C e(11, 7);
		CPPUNIT_ASSERT(d == e);
		d.push_back(7);
		CPPUNIT_ASSERT(d != e);
		d.pop_front();
		CPPUNIT_ASSERT(d == e);
		d.push_front(5);
		CPPUNIT_ASSERT(d != e);
		d.pop_back();
		CPPUNIT_ASSERT(d != e);
	}

	void test_mydeque_equality_4() {
	    C d(600, 7);
		C e(600, 7);
		CPPUNIT_ASSERT(d == e);
		d.push_back(7);
		CPPUNIT_ASSERT(d != e);
		d.pop_front();
		CPPUNIT_ASSERT(d == e);
		d.push_front(5);
		CPPUNIT_ASSERT(d != e);
		d.pop_back();
		CPPUNIT_ASSERT(d != e);
	}

    // ----------------------
	// test_mydeque_less_than
	// ----------------------
    
	void test_mydeque_less_than_1() {
	    C d;
		C e;
		CPPUNIT_ASSERT(!(d < e));
		e.push_back(7);
		CPPUNIT_ASSERT(d < e);
		d.push_front(8);
		CPPUNIT_ASSERT(e < d);
	}
	
	void test_mydeque_less_than_2() {
	    C d;
		C e(13, 7);
		CPPUNIT_ASSERT(d < e);
		d.push_back(7);
		CPPUNIT_ASSERT(d < e);
		d.push_back(8);
		CPPUNIT_ASSERT(e < d);
	}
	
	void test_mydeque_less_than_3() {
	    C d(10, 7);
		C e(10, 7);
		CPPUNIT_ASSERT(!(d < e));
		d.pop_front();
		CPPUNIT_ASSERT(d < e);
		e.push_front(2);
		CPPUNIT_ASSERT(e < d);
		e.pop_back();
		e.pop_back();
		CPPUNIT_ASSERT(e < d);
		d = e;
		CPPUNIT_ASSERT(!(e < d));
	}
	
	void test_mydeque_less_than_4() {
	    C d(700, 500);
		C e(700, 500);
		CPPUNIT_ASSERT(!(d < e));
		d.pop_front();
		CPPUNIT_ASSERT(d < e);
		e.push_front(2);
		CPPUNIT_ASSERT(e < d);
		e.pop_back();
		e.pop_back();
		CPPUNIT_ASSERT(e < d);
		d = e;
		CPPUNIT_ASSERT(!(e < d));
	}

	// ITERATOR TESTS

	// ------------------
	// test_iter_equality
	// ------------------
	
	void test_iter_equality_1() {
		C d(9, 5);
		typename C::iterator it1 = d.begin();
		typename C::iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
		it1 = d.begin() + 9;
	    CPPUNIT_ASSERT(it1 != it2);
		it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}
	
	void test_iter_equality_2() {
		C d(13, 200);
		C e(13, 200);
		typename C::iterator it1 = d.begin();
		typename C::iterator it2 = e.begin();
		CPPUNIT_ASSERT(it1 != it2);
		it1 = d.end();
		it2 = e.end();
		CPPUNIT_ASSERT(it1 != it2);
	}

	void test_iter_equality_3() {
		C d(10, 3);
		typename C::iterator it1 = d.begin() + 3;
		typename C::iterator it2 = d.begin() + 7;
		CPPUNIT_ASSERT(it1 != it2);
		it1 = it2;
		CPPUNIT_ASSERT(it1 == it2);
		--it1;
		CPPUNIT_ASSERT(it1 != it2);
		++it1;
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_iter_equality_4() {
		C d(808, 300);
		typename C::iterator it1 = d.begin() + 3;
		typename C::iterator it2 = d.begin() + 7;
		CPPUNIT_ASSERT(it1 != it2);
		it1 = it2;
		CPPUNIT_ASSERT(it1 == it2);
		it1 = it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
		--it1;
		CPPUNIT_ASSERT(it1 != it2);
		++it1;
		CPPUNIT_ASSERT(it1 == it2);
	}

	// --------------
	// test_iter_plus
	// --------------

	void test_iter_plus_1() {
		C d(9, 5);
		typename C::iterator it1 = d.begin();
		it1 = it1 + 9;
		typename C::iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}
	
	void test_iter_plus_2() {
		const int x = 3;
		const int y = 200;
		C d(x, y);
		typename C::iterator it1 = d.begin();

		for (int i = 0; i < x; ++i) {
			CPPUNIT_ASSERT(*it1 == y);
			it1 = it1 + 1;
		}
		CPPUNIT_ASSERT(it1 == d.end());
	}

	void test_iter_plus_3() {
		C d(1, 100);
		d.push_front(99);
		d.push_back(101);
		typename C::iterator it1 = d.begin();
        CPPUNIT_ASSERT(*it1 == 99);
		it1 += 1;
		CPPUNIT_ASSERT(*it1 == 100);
		++it1;
		CPPUNIT_ASSERT(*it1 == 101);
	}

	void test_iter_plus_4() {
		C d(512, 5);
		typename C::iterator it1 = d.begin();
		it1 = it1 + 512;
		typename C::iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}
	
	// ---------------
	// test_iter_minus
	// ---------------

	void test_iter_minus_1() {
		C d(9, 5);
		typename C::iterator it1 = d.end();
		it1 = it1 - 9;
		typename C::iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}
	
	void test_iter_minus_2() {
		const int x = 3;
		const int y = 200;
		C d(x, y);
		typename C::iterator it1 = d.end();

		for (int i = x; i > 0; --i) {
            --it1;
			CPPUNIT_ASSERT(*it1 == y);
		}
		CPPUNIT_ASSERT(it1 == d.begin());
	}

	void test_iter_minus_3() {
		C d(1, 100);
		d.push_front(99);
		d.push_back(101);
		typename C::iterator it1 = d.end() - 1;
        CPPUNIT_ASSERT(*it1 == 101);
		it1 -= 1;
		CPPUNIT_ASSERT(*it1 == 100);
		--it1;
		CPPUNIT_ASSERT(*it1 == 99);
	}

	void test_iter_minus_4() {
		C d(512, 5);
		typename C::iterator it1 = d.end();
		it1 = it1 - 512;
		typename C::iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}
	
	// ---------------------
	// test_iter_dereference
	// ---------------------
	
	void test_iter_dereference_1() {
		C d(11, 6);
		for(int i = 0; i < 6; ++i)
		    d.push_back(i);
		typename C::iterator it1 = d.end() - 6;
		CPPUNIT_ASSERT(*it1 == 0);
		typename C::iterator it2 = d.begin() + 10;
		CPPUNIT_ASSERT(*it2 == 6);
		++it2;

		// it1 and it2 both point to 0, after the 11 6's
		for(int i = 0; i < 6; ++i) {
			CPPUNIT_ASSERT(*it2 == i);
			CPPUNIT_ASSERT(*it1 == *it2);
			CPPUNIT_ASSERT(it1 == it2);
			++it1;
			++it2;
		}

		typename C::iterator it3 = d.begin();
		for (int i = 0; i < 17; ++i) {
			*it3 = i + 10;
			++it3;
		}
		it3 = d.begin();
		for (int i = 0; i < 17; ++i) {
			CPPUNIT_ASSERT(*it3 == i + 10);
			++it3;
		}
	}
	
	void test_iter_dereference_2() {
		C d;
		d.push_back(5); 
		d.push_front(0);
		d.push_back(11);
		typename C::iterator it1 = d.begin();
		CPPUNIT_ASSERT(*it1 == 0);
		CPPUNIT_ASSERT(*(d.end() - 1) == 11);
		++it1;
		CPPUNIT_ASSERT(*it1 == 5);
		*it1 = 2000;
		CPPUNIT_ASSERT(*it1 == 2000);
	}
	
	void test_iter_dereference_3() {
		C d(9, 0);
		d.push_back(-1); 
		d.push_front(-1);
		CPPUNIT_ASSERT(*(d.begin()) == -1);
		CPPUNIT_ASSERT(*(d.end() - 1) == -1);
		typename C::iterator it1 = d.end();
		it1 -= 5;
		CPPUNIT_ASSERT(*it1 == 0);
		*it1 = 777;
		CPPUNIT_ASSERT(*it1 == 777);
	}
	
	void test_iter_dereference_4() {
		C d(900, 6);
		for(int i = 0; i < 6; ++i)
		    d.push_back(i);
		typename C::iterator it1 = d.end() - 6;
		CPPUNIT_ASSERT(*it1 == 0);
		typename C::iterator it2 = d.begin() + 899;
		CPPUNIT_ASSERT(*it2 == 6);
		++it2;

		for(int i = 0; i < 6; ++i) {
			CPPUNIT_ASSERT(*it2 == i);
			CPPUNIT_ASSERT(*it1 == *it2);
			CPPUNIT_ASSERT(it1 == it2);
			++it1;
			++it2;
		}
	}

	// --------------
	// iter_increment
	// --------------
	
	void test_iter_increment_1() {
		C d;
		for (int i = 0; i < 600; ++i)
			d.push_back(i);

		typename C::iterator it = d.begin();
		for (int i = 0; i < 600; ++i) {
			CPPUNIT_ASSERT(*it == i);
			++it;
		}

		typename C::iterator it2 = d.end();
		CPPUNIT_ASSERT(it == it2);
	}
	
	void test_iter_increment_2() {
		C d(1, 5);
		typename C::iterator it1 = d.begin();
		CPPUNIT_ASSERT(*it1 == 5);
		++it1;
		typename C::iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_iter_increment_3() {
		C d;
		d.push_back(10);
		d.push_back(11);

		typename C::iterator it1 = d.begin();
		typename C::iterator it2 = it1++;
		CPPUNIT_ASSERT(*it1 == 11);
		CPPUNIT_ASSERT(*it2 == 10);
		it1++;
		CPPUNIT_ASSERT(it1 == d.end());
	}

	// --------------
	// iter_decrement
	// --------------
	
	void test_iter_decrement_1() {
		C d;
		for (int i = 0; i < 600; ++i)
			d.push_back(i);

		typename C::iterator it = d.end();
		for (int i = 599; i >= 0; --i) {
			--it;
			CPPUNIT_ASSERT(*it == i);
		}

		typename C::iterator it2 = d.begin();
		CPPUNIT_ASSERT(it == it2);
	}
	
	void test_iter_decrement_2() {
		C d(1, 5);
		typename C::iterator it1 = d.end();
		--it1;
		CPPUNIT_ASSERT(*it1 == 5);
		typename C::iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_iter_decrement_3() {
		C d;
		d.push_back(10);
		d.push_back(11);

		typename C::iterator it1 = d.end();
		typename C::iterator it2 = it1--;
		CPPUNIT_ASSERT(it2 == d.end());
		CPPUNIT_ASSERT(*it1 == 11);
		it1--;
		CPPUNIT_ASSERT(*it1 == 10);
		CPPUNIT_ASSERT(it1 == d.begin());
	}

	// ---------------------
	// test_iter_plus_equals
	// ---------------------

	void test_iter_plus_equals_1() {
		C d(9, 5);
		typename C::iterator it1 = d.begin();
		it1 += 9;
		typename C::iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}
	
	void test_iter_plus_equals_2() {
		const int x = 3;
		const int y = 200;
		C d(x, y);
		typename C::iterator it1 = d.begin();

		for (int i = 0; i < x; ++i) {
			CPPUNIT_ASSERT(*it1 == y);
			it1 += 1;
		}
		CPPUNIT_ASSERT(it1 == d.end());
	}

	void test_iter_plus_equals_3() {
		C d(512, 5);
		typename C::iterator it1 = d.begin();
		it1 += 512;
		typename C::iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}
	
	// ----------------------
	// test_iter_minus_equals
	// ----------------------

	void test_iter_minus_equals_1() {
		C d(9, 5);
		typename C::iterator it1 = d.end();
		it1 -= 9;
		typename C::iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}
	
	void test_iter_minus_equals_2() {
		const int x = 3;
		const int y = 200;
		C d(x, y);
		typename C::iterator it1 = d.end();

		for (int i = x; i > 0; --i) {
            it1 -= 1;
			CPPUNIT_ASSERT(*it1 == y);
		}
		CPPUNIT_ASSERT(it1 == d.begin());
	}

	void test_iter_minus_equals_3() {
		C d(1, 100);
		d.push_front(99);
		d.push_back(101);
		typename C::iterator it1 = d.end();
		it1 -= 1;
        CPPUNIT_ASSERT(*it1 == 101);
		it1 -= 1;
		CPPUNIT_ASSERT(*it1 == 100);
		it1 -= 1;
		CPPUNIT_ASSERT(*it1 == 99);
	}

	void test_iter_minus_equals_4() {
		C d(512, 5);
		typename C::iterator it1 = d.end();
		it1 -= 512;
		typename C::iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}
	
	// CONST_ITERATOR TESTS

	// ------------------------
	// test_const_iter_equality
	// ------------------------
	
	void test_const_iter_equality_1() {
		const C d(9, 5);
		typename C::const_iterator it1 = d.begin();
		typename C::const_iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
		it1 = d.begin() + 9;
	    CPPUNIT_ASSERT(it1 != it2);
		it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}
	
	void test_const_iter_equality_2() {
		const C d(13, 200);
		const C e(13, 200);
		typename C::const_iterator it1 = d.begin();
		typename C::const_iterator it2 = e.begin();
		CPPUNIT_ASSERT(it1 != it2);
		it1 = d.end();
		it2 = e.end();
		CPPUNIT_ASSERT(it1 != it2);
	}

	void test_const_iter_equality_3() {
		const C d(10, 3);
		typename C::const_iterator it1 = d.begin() + 3;
		typename C::const_iterator it2 = d.begin() + 7;
		CPPUNIT_ASSERT(it1 != it2);
		it1 = it2;
		CPPUNIT_ASSERT(it1 == it2);
		--it1;
		CPPUNIT_ASSERT(it1 != it2);
		++it1;
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_const_iter_equality_4() {
		const C d(808, 300);
		typename C::const_iterator it1 = d.begin() + 3;
		typename C::const_iterator it2 = d.begin() + 7;
		CPPUNIT_ASSERT(it1 != it2);
		it1 = it2;
		CPPUNIT_ASSERT(it1 == it2);
		it1 = it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
		--it1;
		CPPUNIT_ASSERT(it1 != it2);
		++it1;
		CPPUNIT_ASSERT(it1 == it2);
	}

	// --------------------
	// test_const_iter_plus
	// --------------------

	void test_const_iter_plus_1() {
		const C d(9, 5);
		typename C::const_iterator it1 = d.begin();
		it1 = it1 + 9;
		typename C::const_iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}
	
	void test_const_iter_plus_2() {
		const int x = 3;
		const int y = 200;
		const C d(x, y);
		typename C::const_iterator it1 = d.begin();

		for (int i = 0; i < x; ++i) {
			CPPUNIT_ASSERT(*it1 == y);
			it1 = it1 + 1;
		}
		CPPUNIT_ASSERT(it1 == d.end());
	}

	void test_const_iter_plus_3() {
		C d(1, 100);
		d.push_front(99);
		d.push_back(101);
		const C e(d);

		typename C::const_iterator it1 = e.begin();
        CPPUNIT_ASSERT(*it1 == 99);
		it1 += 1;
		CPPUNIT_ASSERT(*it1 == 100);
		++it1;
		CPPUNIT_ASSERT(*it1 == 101);
	}

	void test_const_iter_plus_4() {
		const C d(512, 5);
		typename C::const_iterator it1 = d.begin();
		it1 = it1 + 512;
		typename C::const_iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}
	
	// ---------------------
	// test_const_iter_minus
	// ---------------------

	void test_const_iter_minus_1() {
		const C d(9, 5);
		typename C::const_iterator it1 = d.end();
		it1 = it1 - 9;
		typename C::const_iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}
	
	void test_const_iter_minus_2() {
		const int x = 3;
		const int y = 200;
		const C d(x, y);
		typename C::const_iterator it1 = d.end();

		for (int i = x; i > 0; --i) {
            --it1;
			CPPUNIT_ASSERT(*it1 == y);
		}
		CPPUNIT_ASSERT(it1 == d.begin());
	}

	void test_const_iter_minus_3() {
		C e(1, 100);
		e.push_front(99);
		e.push_back(101);
		const C d(e);

		typename C::const_iterator it1 = d.end() - 1;
        CPPUNIT_ASSERT(*it1 == 101);
		it1 -= 1;
		CPPUNIT_ASSERT(*it1 == 100);
		--it1;
		CPPUNIT_ASSERT(*it1 == 99);
	}

	void test_const_iter_minus_4() {
		const C d(512, 5);
		typename C::const_iterator it1 = d.end();
		it1 = it1 - 512;
		typename C::const_iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}
	
	// ---------------------------
	// test_const_iter_dereference
	// ---------------------------
	
	void test_const_iter_dereference_1() {
		C e(11, 6);
		for(int i = 0; i < 6; ++i)
		    e.push_back(i);
		const C d(e);
		typename C::const_iterator it1 = d.end() - 6;
		CPPUNIT_ASSERT(*it1 == 0);
		typename C::const_iterator it2 = d.begin() + 10;
		CPPUNIT_ASSERT(*it2 == 6);
		++it2;

		// it1 and it2 both point to 0, after the 11 6's
		for(int i = 0; i < 6; ++i) {
			CPPUNIT_ASSERT(*it2 == i);
			CPPUNIT_ASSERT(*it1 == *it2);
			CPPUNIT_ASSERT(it1 == it2);
			++it1;
			++it2;
		}
	}
	
	void test_const_iter_dereference_2() {
		C e;
		e.push_back(5); 
		e.push_front(0);
		e.push_back(11);
		const C d(e);

		typename C::const_iterator it1 = d.begin();
		CPPUNIT_ASSERT(*it1 == 0);
		CPPUNIT_ASSERT(*(d.end() - 1) == 11);
		++it1;
		CPPUNIT_ASSERT(*it1 == 5);
	}
	
	void test_const_iter_dereference_3() {
		C e(9, 0);
		e.push_back(-1); 
		e.push_front(-1);
		const C d(e);

		CPPUNIT_ASSERT(*(d.begin()) == -1);
		CPPUNIT_ASSERT(*(d.end() - 1) == -1);
		typename C::const_iterator it1 = d.end();
		it1 -= 5;
		CPPUNIT_ASSERT(*it1 == 0);
	}
	
	void test_const_iter_dereference_4() {
		C e(900, 6);
		for(int i = 0; i < 6; ++i)
		    e.push_back(i);
		const C d(e);

		typename C::const_iterator it1 = d.end() - 6;
		CPPUNIT_ASSERT(*it1 == 0);
		typename C::const_iterator it2 = d.begin() + 899;
		CPPUNIT_ASSERT(*it2 == 6);
		++it2;

		for(int i = 0; i < 6; ++i) {
			CPPUNIT_ASSERT(*it2 == i);
			CPPUNIT_ASSERT(*it1 == *it2);
			CPPUNIT_ASSERT(it1 == it2);
			++it1;
			++it2;
		}
	}

	// --------------------
	// const_iter_increment
	// --------------------
	
	void test_const_iter_increment_1() {
		C e;
		for (int i = 0; i < 600; ++i)
			e.push_back(i);
		const C d(e);

		typename C::const_iterator it = d.begin();
		for (int i = 0; i < 600; ++i) {
			CPPUNIT_ASSERT(*it == i);
			++it;
		}

		typename C::const_iterator it2 = d.end();
		CPPUNIT_ASSERT(it == it2);
	}
	
	void test_const_iter_increment_2() {
		const C d(1, 5);
		typename C::const_iterator it1 = d.begin();
		CPPUNIT_ASSERT(*it1 == 5);
		++it1;
		typename C::const_iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_const_iter_increment_3() {
		C e;
		e.push_back(10);
		e.push_back(11);
		const C d(e);

		typename C::const_iterator it1 = d.begin();
		typename C::const_iterator it2 = it1++;
		CPPUNIT_ASSERT(*it1 == 11);
		CPPUNIT_ASSERT(*it2 == 10);
		it1++;
		CPPUNIT_ASSERT(it1 == d.end());
	}

	// --------------------
	// const_iter_decrement
	// --------------------
	
	void test_const_iter_decrement_1() {
		C e;
		for (int i = 0; i < 600; ++i)
			e.push_back(i);
		const C d(e);

		typename C::const_iterator it = d.end();
		for (int i = 599; i >= 0; --i) {
			--it;
			CPPUNIT_ASSERT(*it == i);
		}

		typename C::const_iterator it2 = d.begin();
		CPPUNIT_ASSERT(it == it2);
	}
	
	void test_const_iter_decrement_2() {
		const C d(1, 5);
		typename C::const_iterator it1 = d.end();
		--it1;
		CPPUNIT_ASSERT(*it1 == 5);
		typename C::const_iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}

	void test_const_iter_decrement_3() {
		C e;
		e.push_back(10);
		e.push_back(11);
		const C d(e);

		typename C::const_iterator it1 = d.end();
		typename C::const_iterator it2 = it1--;
		CPPUNIT_ASSERT(it2 == d.end());
		CPPUNIT_ASSERT(*it1 == 11);
		it1--;
		CPPUNIT_ASSERT(*it1 == 10);
		CPPUNIT_ASSERT(it1 == d.begin());
	}

	// ---------------------------
	// test_const_iter_plus_equals
	// ---------------------------

	void test_const_iter_plus_equals_1() {
		const C d(9, 5);
		typename C::const_iterator it1 = d.begin();
		it1 += 9;
		typename C::const_iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}
	
	void test_const_iter_plus_equals_2() {
		const int x = 3;
		const int y = 200;
		const C d(x, y);
		typename C::const_iterator it1 = d.begin();

		for (int i = 0; i < x; ++i) {
			CPPUNIT_ASSERT(*it1 == y);
			it1 += 1;
		}
		CPPUNIT_ASSERT(it1 == d.end());
	}

	void test_const_iter_plus_equals_3() {
		const C d(512, 5);
		typename C::const_iterator it1 = d.begin();
		it1 += 512;
		typename C::const_iterator it2 = d.end();
		CPPUNIT_ASSERT(it1 == it2);
	}
	
	// ----------------------------
	// test_const_iter_minus_equals
	// ----------------------------

	void test_const_iter_minus_equals_1() {
		const C d(9, 5);
		typename C::const_iterator it1 = d.end();
		it1 -= 9;
		typename C::const_iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}
	
	void test_const_iter_minus_equals_2() {
		const int x = 3;
		const int y = 200;
		const C d(x, y);
		typename C::const_iterator it1 = d.end();

		for (int i = x; i > 0; --i) {
            it1 -= 1;
			CPPUNIT_ASSERT(*it1 == y);
		}
		CPPUNIT_ASSERT(it1 == d.begin());
	}

	void test_const_iter_minus_equals_3() {
		C e(1, 100);
		e.push_front(99);
		e.push_back(101);
		const C d(e);

		typename C::const_iterator it1 = d.end();
		it1 -= 1;
        CPPUNIT_ASSERT(*it1 == 101);
		it1 -= 1;
		CPPUNIT_ASSERT(*it1 == 100);
		it1 -= 1;
		CPPUNIT_ASSERT(*it1 == 99);
	}

	void test_const_iter_minus_equals_4() {
		const C d(512, 5);
		typename C::const_iterator it1 = d.end();
		it1 -= 512;
		typename C::const_iterator it2 = d.begin();
		CPPUNIT_ASSERT(it1 == it2);
	}
	
	// ----------------
	// test_constructor
	// ----------------

	void test_constructor_1() {
		C d;
		CPPUNIT_ASSERT(d.size() == 0);
		CPPUNIT_ASSERT(d.begin() == d.end());
	}

	void test_constructor_2() {
		C d(15, 8);

		CPPUNIT_ASSERT(d.size() == 15);
		CPPUNIT_ASSERT(d.end() == d.begin() + d.size());
		for (int i = 0; i < 15; ++i)
			CPPUNIT_ASSERT(d[i] == 8);
	}

	void test_constructor_3() {
		const unsigned x = 512;
		C d(x, 303);

		CPPUNIT_ASSERT(d.size() == x);		
		CPPUNIT_ASSERT(d.end() == d.begin() + d.size());
		for (unsigned i = 0; i < x; ++i)
			CPPUNIT_ASSERT(d[i] == 303);
	}

	void test_constructor_4() {
		const unsigned x = 513;
		C d(x, 235);

		CPPUNIT_ASSERT(d.size() == x);
		CPPUNIT_ASSERT(d.end() == d.begin() + d.size());
		for (unsigned i = 0; i < x; ++i)
			CPPUNIT_ASSERT(d[i] == 235);
	}
  
	void test_constructor_5() {
		const unsigned x = 51320;
		C d(x, 235);

		CPPUNIT_ASSERT(d.size() == x);
		CPPUNIT_ASSERT(d.end() == d.begin() + d.size());
		for (unsigned i = 0; i < x; ++i)
			CPPUNIT_ASSERT(d[i] == 235);
	}
  
	void test_constructor_6() {
		const unsigned x = 566;
		C d(x, 97);
		C e(d);

		CPPUNIT_ASSERT(e.size() == x);
		CPPUNIT_ASSERT(d.end() == d.begin() + d.size());
		for (unsigned i = 0; i < x; ++i) {
			CPPUNIT_ASSERT(e[i] == d[i]);
		}
	}

	void test_constructor_7() {
		const unsigned x = 100001;
		C d(x, 60001);
		C e(d);

		CPPUNIT_ASSERT(e.size() == x);
		CPPUNIT_ASSERT(d.end() == d.begin() + d.size());
		for (unsigned i = 0; i < x; ++i) {
			CPPUNIT_ASSERT(e[i] == d[i]);
		}
	}

	//--------------------
	// assignment operator
	//--------------------
 
	void test_assign_1() {
		C d(4, 1);
		C e(4, 2);
		e = d;	   
 
		CPPUNIT_ASSERT(d.size() == 4);
		CPPUNIT_ASSERT(e.size() == 4);
		for (int i = 0; i < 4; ++i)
			CPPUNIT_ASSERT(e[i] == d[i]);
	}

	void test_assign_2() {
		C d;
		C e;
		CPPUNIT_ASSERT(e.size() == 0);
		e = d;
		CPPUNIT_ASSERT(e.size() == 0);
		e = e;
		CPPUNIT_ASSERT(e.size() == 0);
	} 

	void test_assign_3() {
		C d(550, 2);
		C e;
		e = d;	   
 
		CPPUNIT_ASSERT(e.size() == 550);
		for (int i = 0; i < 550; ++i)
			CPPUNIT_ASSERT(e[i] == d[i]);

		e.clear();
		d = e;
		CPPUNIT_ASSERT(d.size() == 0);
	}

	void test_assign_4() {
		C d(550, 2);
		C e(0, 7);

		CPPUNIT_ASSERT(e.size() == 0);
		e = d;
		CPPUNIT_ASSERT(e.size() == 550);
		for (int i = 0; i < 550; ++i)
			CPPUNIT_ASSERT(e[i] == d[i]);

		e.clear();
		CPPUNIT_ASSERT(e.size() == 0);
		d = e;
		CPPUNIT_ASSERT(d.size() == 0);
	}

	void test_assign_5() {
		C e(3000, 27);
		C d(3000, 6);
		e = d;	   
 
		CPPUNIT_ASSERT(e.size() == 3000);
		for (int i = 0; i < 3000; ++i)
			CPPUNIT_ASSERT(e[i] == d[i]);
	}

	void test_assign_6() {
		C e(1025, 27);
		C d(2000, 6);
		d = e;	   
 
		CPPUNIT_ASSERT(d.size() == 1025);
		for (int i = 0; i < 1025; ++i)
			CPPUNIT_ASSERT(e[i] == d[i]);
	}

	void test_assign_7() {
		C e(125, 550);
		C d(201, 777);
		d = e;	   
 
		CPPUNIT_ASSERT(d.size() == 125);
		for (int i = 0; i < 125; ++i)
			CPPUNIT_ASSERT(e[i] == d[i]);
	}

    // -------------
	// test_indexing
	// -------------
	
	void test_indexing_1() {
		C d(0);
		d.push_back(1);
		CPPUNIT_ASSERT(d[0] == 1);
	}
	
	void test_indexing_2() {
		C d(11, 6);
		d.push_back(1);
		d.push_front(-3);
		CPPUNIT_ASSERT(d[0] == -3);
		for(int i = 1; i < 12; i++)
		    CPPUNIT_ASSERT(d[i] == 6);
		CPPUNIT_ASSERT(d[12] == 1);
	}
	
	void test_indexing_3() {
		C d;
		C e(2, 1);
		d.push_back(1);
		d.push_front(0);
		CPPUNIT_ASSERT(d[0] == 0);
		CPPUNIT_ASSERT(d[1] == 1);
		CPPUNIT_ASSERT(d[1] == e[1]);
		CPPUNIT_ASSERT(&d[1] != &e[1]);
	}
	
    // -------
	// test_at
	// -------
	
	void test_at_1() {
		C d(0);
		d.push_back(1);
		CPPUNIT_ASSERT(d.at(0) == 1);
	}
	
	void test_at_2() {
		C e(11, 6);
		e.push_back(1);
		e.push_front(-3);

		const C d(e);
		CPPUNIT_ASSERT(d.at(0) == -3);
		for(int i = 1; i < 12; ++i)
		    CPPUNIT_ASSERT(d.at(i) == 6);
		CPPUNIT_ASSERT(d.at(12) == 1);
	}
	
	void test_at_3() {
		C d;
		C e(2, 1);
		d.push_back(1);
		d.push_front(0);
		CPPUNIT_ASSERT(d.at(0) == 0);
		CPPUNIT_ASSERT(d.at(1) == 1);
		CPPUNIT_ASSERT(d.at(1) == e.at(1));
		CPPUNIT_ASSERT(&d.at(1) != &e.at(1));
	}
	
	// ---------------
	// test_back_front
	// ---------------

	void test_back_front_1() {
		C d(8, 2);
		CPPUNIT_ASSERT(d.back() == 2);
		d.push_back(3);
		CPPUNIT_ASSERT(d.size() == 9);
		CPPUNIT_ASSERT(d.back() == 3);
		CPPUNIT_ASSERT(d.front() == 2);
		d.push_front(100);
		CPPUNIT_ASSERT(d.front() == 100);
	}

	void test_back_front_2() {
		C d(30, 6);
		CPPUNIT_ASSERT(d.size() == 30);
		CPPUNIT_ASSERT(d.front() == 6);
		d.push_front(4);
		CPPUNIT_ASSERT(d.size() == 31);
		CPPUNIT_ASSERT(d.front() == 4);
	}

	void test_back_front_3() {
		C d;
		d.push_back(3);
		d.push_front(2);
		d.push_front(1);
		CPPUNIT_ASSERT(d.size() == 3);
		CPPUNIT_ASSERT(d.front() == 1);
		CPPUNIT_ASSERT(&(d.front()) == &*(d.begin()));
		CPPUNIT_ASSERT(d.back() == 3); 
		CPPUNIT_ASSERT(&(d.back()) == &*(d.end() - 1));
		d.pop_front();
		CPPUNIT_ASSERT(d.front() == 2);
		d.pop_back();
		CPPUNIT_ASSERT(d.back() == 2);
	}
	
	void test_back_front_4() {
		C d(800, 2001);
		CPPUNIT_ASSERT(d.front() == 2001);
		CPPUNIT_ASSERT(d.back() == 2001);
		d.push_back(3);
		CPPUNIT_ASSERT(d.size() == 801);
		CPPUNIT_ASSERT(d.back() == 3);
		CPPUNIT_ASSERT(d.front() == 2001);
	}

	void test_back_front_5() {
		C d(512, 6);
		CPPUNIT_ASSERT(d.size() == 512);
		CPPUNIT_ASSERT(d.front() == 6);

		d.push_front(4);
		CPPUNIT_ASSERT(d.size() == 513);
		CPPUNIT_ASSERT(d.front() == 4);
	}

	void test_back_front_6() {
		C d(513, 60);
		CPPUNIT_ASSERT(d.size() == 513);
		CPPUNIT_ASSERT(d.front() == 60);
		CPPUNIT_ASSERT(d.back() == 60);

		d.push_front(4);
		CPPUNIT_ASSERT(d.size() == 514);
		CPPUNIT_ASSERT(d.front() == 4);
		CPPUNIT_ASSERT(d.back() == 60);
	}

	// ----------
	// test_begin
	// ----------

	void test_begin_1() {
		C d;
		CPPUNIT_ASSERT(d.size() == 0);
		CPPUNIT_ASSERT(d.begin() == d.end());
	}

	void test_begin_2() {
		C d(15, 8);

		CPPUNIT_ASSERT(d.size() == 15);
		CPPUNIT_ASSERT(*(d.begin()) == 8);
	}

	void test_begin_3() {
		const unsigned x = 51;
		const C d(x, 303);

		CPPUNIT_ASSERT(d.size() == x);		
		CPPUNIT_ASSERT(*(d.begin()) == 303);		
	}

	// ----------
	// test_clear
	// ----------
	
	void test_clear_1() {
		C d;
		d.clear();
		CPPUNIT_ASSERT(d.empty());
		CPPUNIT_ASSERT(d.begin() == d.end());
	}

	void test_clear_2() {
		C d(0, 7);
		d.clear();
		CPPUNIT_ASSERT(d.empty());
		CPPUNIT_ASSERT(d.begin() == d.end());
	}

	void test_clear_3() {
		C d(32, 7);
		d.clear();
		CPPUNIT_ASSERT(d.empty());
		CPPUNIT_ASSERT(d.begin() == d.end());
	}

	void test_clear_4() {
		C d(3200, 7);
		d.clear();
		CPPUNIT_ASSERT(d.empty());
		CPPUNIT_ASSERT(d.begin() == d.end());
	}

	// ----------
	// test_empty
	// ----------
	
	void test_empty_1() {
		C d;
		CPPUNIT_ASSERT(d.empty());
	}

	void test_empty_2() {
		C d(0, 7);
		CPPUNIT_ASSERT(d.empty());
	}

	void test_empty_3() {
		C d(32, 7);
		CPPUNIT_ASSERT(!d.empty());
	}

	void test_empty_4() {
		C d(589, 7);
		CPPUNIT_ASSERT(!d.empty());
		d.clear();
		CPPUNIT_ASSERT(d.empty());
	}

	// --------
	// test_end
	// --------

	void test_end_1() {
		C d;
		CPPUNIT_ASSERT(d.size() == 0);
		CPPUNIT_ASSERT(d.begin() == d.end());
	}

	void test_end_2() {
		C d(15, 8);

		CPPUNIT_ASSERT(d.size() == 15);
		CPPUNIT_ASSERT(*(d.end() - 1) == 8);
	}

	void test_end_3() {
		const unsigned x = 512;
		const C d(x, 303);

		CPPUNIT_ASSERT(d.size() == x);		
		CPPUNIT_ASSERT(*(d.end() - 1) == 303);		
	}

	//-----------
	// test erase
	//-----------
	
	void test_erase_1() {
		C d(1, 1);
		CPPUNIT_ASSERT(d.size() == 1);
		d.erase(d.begin());
		CPPUNIT_ASSERT(d.size() == 0);
	}
	
	void test_erase_2() {
		C d(2, 4);
        d.push_front(3); 
		d.push_back(2);
		typename C::iterator it = d.erase(d.begin() + 2);
		CPPUNIT_ASSERT(*it == 2);
		CPPUNIT_ASSERT(d[0] == 3);
		CPPUNIT_ASSERT(d[1] == 4);
		CPPUNIT_ASSERT(d[2] == 2);
		d.erase(d.end() - 3);
		
		int x[] = {4, 2};
		CPPUNIT_ASSERT(d.size() == 2);
		for(int i = 0; i < 2; i++)
		    CPPUNIT_ASSERT(d[i] == x[i]);

		it = d.erase(d.begin() + 1);
		CPPUNIT_ASSERT(d[0] == 4);
		CPPUNIT_ASSERT(it == d.end());
	}
	
	void test_erase_3() {
		C d;
        d.push_back(2);
		d.push_back(3);
		d.push_back(4);
		d.push_back(5);
		d.push_back(6);
		
		d.erase(d.begin());
		d.erase(d.end() - 1);

		typename C::iterator it = d.erase(d.begin() + 1);
		CPPUNIT_ASSERT(*it == 5);
		
		int x[] = {3, 5};
		CPPUNIT_ASSERT(d.size() == 2);
		for(int i = 0; i < 2; i++)
		    CPPUNIT_ASSERT(d[i] == x[i]);
	}
	
	void test_erase_4() {
	    C d(11, 0);
		d.erase(d.begin() + 6);
		d.erase(d.begin());
		d.insert(d.begin() + 3, 3);
		d.erase(d.end() - 1);
		
		int x[] = {0, 0, 0, 3, 0, 0, 0, 0, 0};
		CPPUNIT_ASSERT(d.size() == 9);
		for(int i = 0; i < 9; i++)
		    CPPUNIT_ASSERT(d[i] == x[i]);
	}
	
	void test_erase_5() {
		C d(1, 8);
		typename C::iterator it = d.erase(d.begin());
		d.insert(it, 2);
		
		CPPUNIT_ASSERT(d.size() == 1);
		CPPUNIT_ASSERT(d[0] == 2);
	}

	void test_erase_6() {
		C d;
		for (int i = 0; i < 8888; ++i)
			d.push_front(i);

		CPPUNIT_ASSERT(d.size() == 8888);
		typename C::iterator it = d.begin();
		for (int i = 8887; i >= 0; --i) {
			CPPUNIT_ASSERT(*it == i);
			it = d.erase(it);
		}
		CPPUNIT_ASSERT(it == d.end());
		CPPUNIT_ASSERT(d.empty());
	}

	void test_erase_7() {
		C d;
		for (int i = 0; i < 5; ++i)
			d.push_back(i);
		CPPUNIT_ASSERT(d.size() == 5);
		CPPUNIT_ASSERT(d.back() == 4);

		typename C::iterator it = d.erase(d.end());
		CPPUNIT_ASSERT(d.size() == 4);
		CPPUNIT_ASSERT(d.back() == 3);
		CPPUNIT_ASSERT(*(d.end() - 1) == 3);
		CPPUNIT_ASSERT(it == d.end() + 1);
	}

	// front() tests included in back() tests above

	//------------
	// test insert
	//------------
	
	void test_insert_1() {
		C d(2, 4);
        d.insert(d.begin() + 1 , 3);
		
		int x[] = {4, 3, 4};
		CPPUNIT_ASSERT(d.size() == 3);
		for(int i = 0; i < 3; i++)
		    CPPUNIT_ASSERT(d[i] == x[i]);
	}
	
	void test_insert_2() {
		C d;
        typename C::iterator it = d.insert(d.begin(), 3);
		CPPUNIT_ASSERT(*it == 3);
		it = d.insert(d.begin(), 2);
		CPPUNIT_ASSERT(*it == 2);
		it = d.insert(d.end(), 4);
		CPPUNIT_ASSERT(*it == 4);
		
		int x[] = {2, 3, 4};
		CPPUNIT_ASSERT(d.size() == 3);
		for(int i = 0; i < 3; i++)
		    CPPUNIT_ASSERT(d[i] == x[i]);
	}
	
	void test_insert_3() {
		C d(9, 5);
        d.insert(d.begin() + 5, 3);
		d.insert(d.end() - 5, 2);
		d.pop_back();
		d.insert(d.end(), 4);
		d.pop_front();
		d.insert(d.begin(), 4);
		
		int x[] = {4, 5, 5, 5, 5, 2, 3, 5, 5, 5, 4};
		CPPUNIT_ASSERT(d.size() == 11);
		for(int i = 0; i < 11; i++)
		    CPPUNIT_ASSERT(d[i] == x[i]);
	}

	void test_insert_4() {
		C d;
        d.insert(d.begin(), 3);
		
		CPPUNIT_ASSERT(d.size() == 1);
		CPPUNIT_ASSERT(d[0] == 3);
	}
		
	void test_insert_5() {
		C d;
		typename C::iterator it = d.begin();
		for (int i = 0; i < 7777; ++i) {
			it = d.insert(d.begin(), i);
			CPPUNIT_ASSERT(*it == i);
		}
		CPPUNIT_ASSERT(d.size() == 7777);
		CPPUNIT_ASSERT(it == d.begin());

		for (int i = 7776, j = 0; i >= 0; --i, ++j)
			CPPUNIT_ASSERT(d[j] == i);
	}
		
	// --------
	// test_pop
	// --------	
	
	void test_pop_1() {
		C d(10, 7);
		CPPUNIT_ASSERT(d.size() == 10);
		d.pop_back();
		CPPUNIT_ASSERT(d.size() == 9);
		d.pop_front();
		CPPUNIT_ASSERT(d.size() == 8);}
		
	void test_pop_2() {
		C d;
		d.push_back(1);
		d.push_back(2);
		d.push_back(3);
		CPPUNIT_ASSERT(d.size() == 3);
		CPPUNIT_ASSERT(d[0] == 1);
		CPPUNIT_ASSERT(d[2] == 3);
		d.pop_back();
		CPPUNIT_ASSERT(d[1] == 2);
		CPPUNIT_ASSERT(d.size() == 2);
		d.pop_front();
		CPPUNIT_ASSERT(d[0] == 2);
		CPPUNIT_ASSERT(d.size() == 1);}

    void test_pop_3() {
		C d(1, 1);
		d.push_back(3);
		d.push_back(5);
		d.push_back(7);
		CPPUNIT_ASSERT(d[0] == 1);
		d.pop_front();
		CPPUNIT_ASSERT(d[0] == 3);
		d.pop_front();
		CPPUNIT_ASSERT(d[0] == 5);
		d.pop_back();
		CPPUNIT_ASSERT(d[0] == 5);
		d.pop_back();
		CPPUNIT_ASSERT(d.empty());}	

    void test_pop_4() {
		C d;
		for (int i = 0; i < 5000; ++i)
			d.push_back(i);

		CPPUNIT_ASSERT(d.size() == 5000);

		for (int i = 1; i <= 2500; ++i) {
			d.pop_back();
			d.pop_front();
			CPPUNIT_ASSERT(d.size() == (unsigned) (5000 - 2*i));
		}
	}

    void test_pop_5() {
		C d;
		for (int i = 0; i < 600; ++i)
			d.push_back(i);

		CPPUNIT_ASSERT(d.size() == 600);

		for (int i = 0; i < 600; ++i) {
			CPPUNIT_ASSERT(d[0] == i);
			d.pop_front();
		}
		CPPUNIT_ASSERT(d.size() == 0);
	}

    void test_pop_6() {
		C d;
		for (int i = 0; i < 600; ++i)
			d.push_front(i);

		CPPUNIT_ASSERT(d.size() == 600);

		for (int i = 599; i >= 0; --i) {
			CPPUNIT_ASSERT(d[0] == i);
			d.pop_front();
		}
		CPPUNIT_ASSERT(d.size() == 0);
	}

    // ---------
	// test_push
	// ---------	
	
	void test_push_1() {
		C d(10, 7);
		CPPUNIT_ASSERT(d.size() == 10);
		d.push_back(7);
		CPPUNIT_ASSERT(d.size() == 11);
		d.push_front(7);
		CPPUNIT_ASSERT(d.size() == 12);}
		
	void test_push_2() {
		C d(7, 1);
		d.push_back(7);
		d.push_back(5);
		d.pop_front();
		d.push_front(2);
		d.push_front(1);
		d.push_back(6);
	
		int x[] = {1, 2, 1, 1, 1, 1, 1, 1, 7, 5, 6};
		CPPUNIT_ASSERT(d.size() == 11);
		for(int i = 0; i < 11; ++i){
			CPPUNIT_ASSERT(d[i] == x[i]);
		}
	}		
		
	void test_push_3() {
		C d;
		d.push_back(1);
		d.push_back(2);
		d.push_back(3);
		CPPUNIT_ASSERT(d.size() == 3);
		CPPUNIT_ASSERT(d[0] == 1);
		CPPUNIT_ASSERT(d[2] == 3);
		d.push_back(4);
		CPPUNIT_ASSERT(d[0] == 1);
		CPPUNIT_ASSERT(d[3] == 4);
		d.push_front(0);
		CPPUNIT_ASSERT(d[0] == 0);
		CPPUNIT_ASSERT(d[4] == 4);
		CPPUNIT_ASSERT(d.size() == 5);}

	void test_push_4() {
		C d;
		for (int i = 0; i < 5500; ++i)
			d.push_front(i);

		for (int i = 5499, j = 0; i >= 0; --i, ++j)
			CPPUNIT_ASSERT(d[j] == i);
	}
		
	void test_push_5() {
		C d;
		for (int i = 0; i < 5500; ++i)
			d.push_back(i);

		for (int i = 0; i < 5500; ++i)
			CPPUNIT_ASSERT(d[i] == i);
	}
		
	void test_push_6() {
		C d;
		for (int i = 0; i < 5500; ++i) {
			d.push_front(i);
			d.push_back(i);
		}

		for (int i = 0, j = 5499; j >= 0; ++i, --j)
			CPPUNIT_ASSERT(d[i] == j);

		for (int i = 5500, j = 0; i < 11000; ++i, ++j)
			CPPUNIT_ASSERT(d[i] == j);
	}
		
	// -----------
	// test_resize
	// -----------
	
	void test_resize_1() {
		C d(5, 6);
		CPPUNIT_ASSERT(d.size() == 5);
		d.resize(5);

		CPPUNIT_ASSERT(d.size() == 5);
		for (int i = 0; i < 5; ++i)
			CPPUNIT_ASSERT(d[i] == 6);
	} 

	void test_resize_2() {
		C d(550, 2);
		d.resize(20);
 
		CPPUNIT_ASSERT(d.size() == 20);
		for (int i = 0; i < 20; ++i)
			CPPUNIT_ASSERT(d[i] == 2);
	}

	void test_resize_3() {
		C e(3, 2);
		const int x = 16;
		e.resize(x, 5); 
 
		CPPUNIT_ASSERT(e.size() == (unsigned) x);
		for (int i = 0; i < 3; ++i)
			CPPUNIT_ASSERT(e[i] == 2);
		for (int i = 3; i < 16; ++i)
			CPPUNIT_ASSERT(e[i] == 5);
	}

	void test_resize_4() {
		C d(550, 2);
		d.resize(0);
		CPPUNIT_ASSERT(d.empty());
	}

	void test_resize_5() {
		C d;
		d.resize(0);
		CPPUNIT_ASSERT(d.empty());
	}

	void test_resize_6() {
		C d(40, 1);
		CPPUNIT_ASSERT(d.size() == 40);
		d.resize(4000, 2);
		CPPUNIT_ASSERT(d.size() == 4000);
		for (int i = 0; i < 40; ++i)
			CPPUNIT_ASSERT(d[i] == 1);
		for (int i = 40; i < 4000; ++i)
			CPPUNIT_ASSERT(d[i] == 2);
	}

	void test_resize_7() {
		C d;
		d.resize(700, 50);
		CPPUNIT_ASSERT(d.size() == 700);
		for (int i = 0; i < 700; ++i)
			CPPUNIT_ASSERT(d[i] == 50);
	}

	void test_resize_8() {
		C d(70, 4);
		d.resize(30, 50);
		CPPUNIT_ASSERT(d.size() == 30);
		for (int i = 0; i < 30; ++i)
			CPPUNIT_ASSERT(d[i] == 4);
	}

	void test_resize_9() {
		C d(7000, 4);
		d.resize(8000, 50);
		CPPUNIT_ASSERT(d.size() == 8000);
		for (int i = 0; i < 7000; ++i)
			CPPUNIT_ASSERT(d[i] == 4);
		for (int i = 7000; i < 8000; ++i)
			CPPUNIT_ASSERT(d[i] == 50);
	}

	void test_resize_10() {
		C d;
		for (int i = 0; i < 1001; ++i)
			d.push_back(i);
		d.resize(2000, 50);
		CPPUNIT_ASSERT(d.size() == 2000);
		for (int i = 0; i < 1001; ++i)
			CPPUNIT_ASSERT(d[i] == i);
		for (int i = 1001; i < 2000; ++i)
			CPPUNIT_ASSERT(d[i] == 50);
	}

	void test_resize_11() {
		C d;
		for (int i = 0; i < 1001; ++i)
			d.push_back(i);
		d.resize(300);
		CPPUNIT_ASSERT(d.size() == 300);
		for (int i = 0; i < 300; ++i)
			CPPUNIT_ASSERT(d[i] == i);
	}

	// ---------
	// test_size
	// ---------

	void test_size_1() {
		C d;
		CPPUNIT_ASSERT(d.size() == 0);
		d.push_front(2);
		CPPUNIT_ASSERT(d.size() == 1);
		}
   
        void test_size_2() {
		C d(5, 6);
		CPPUNIT_ASSERT(d.size() == 5);
		d.pop_front();
		d.pop_back();
		CPPUNIT_ASSERT(d.size() == 3);}
		
	void test_size_3() {
		C d(10, 7);
		CPPUNIT_ASSERT(d.size() == 10);
		d.push_back(7);
		CPPUNIT_ASSERT(d.size() == 11);}	
		
	//-----------	
	// test swap
    //-----------	
		
	void test_swap_1() {
		C d;
		C e;
		d.push_front(3);
		e.push_back(5);
		CPPUNIT_ASSERT(d.size() == 1);
		CPPUNIT_ASSERT(e.size() == 1);
		CPPUNIT_ASSERT(d[0] == 3);
		CPPUNIT_ASSERT(e[0] == 5);
		
		d.swap(e);

		CPPUNIT_ASSERT(d.size() == 1);
		CPPUNIT_ASSERT(e.size() == 1);
		CPPUNIT_ASSERT(d[0] == 5);
		CPPUNIT_ASSERT(e[0] == 3);
	}

	void test_swap_2() {
		C d(15, 8);
		C e(200, 4);

		CPPUNIT_ASSERT(d.size() == 15);
		CPPUNIT_ASSERT(e.size() == 200);
		CPPUNIT_ASSERT(d[0] == 8);
		CPPUNIT_ASSERT(e[0] == 4);
		
		d.swap(e);

		CPPUNIT_ASSERT(d.size() == 200);
		CPPUNIT_ASSERT(e.size() == 15);
		for (int i = 0; i < 200; ++i)
			CPPUNIT_ASSERT(d[i] == 4);
		for (int i = 0; i < 15; ++i)
			CPPUNIT_ASSERT(e[i] == 8);
	}

	void test_swap_3() {
		C d;
		C e(1, 6);

		CPPUNIT_ASSERT(d.size() == 0);
		CPPUNIT_ASSERT(e.size() == 1);
		CPPUNIT_ASSERT(e[0] == 6);
		
		d.swap(e);

		CPPUNIT_ASSERT(d.size() == 1);
		CPPUNIT_ASSERT(e.size() == 0);
		CPPUNIT_ASSERT(d[0] == 6);
	}
	
	// -----
	// suite
	// -----

	CPPUNIT_TEST_SUITE(TestDeque); 
	CPPUNIT_TEST(test_mydeque_equality_1);
	CPPUNIT_TEST(test_mydeque_equality_2);
	CPPUNIT_TEST(test_mydeque_equality_3);
	CPPUNIT_TEST(test_mydeque_equality_4);
	CPPUNIT_TEST(test_mydeque_less_than_1);
	CPPUNIT_TEST(test_mydeque_less_than_2);
	CPPUNIT_TEST(test_mydeque_less_than_3);
	CPPUNIT_TEST(test_mydeque_less_than_4);

	CPPUNIT_TEST(test_iter_equality_1);
	CPPUNIT_TEST(test_iter_equality_2);
	CPPUNIT_TEST(test_iter_equality_3);
	CPPUNIT_TEST(test_iter_equality_4);
	CPPUNIT_TEST(test_iter_plus_1);
	CPPUNIT_TEST(test_iter_plus_2);
	CPPUNIT_TEST(test_iter_plus_3);
	CPPUNIT_TEST(test_iter_plus_4);
	CPPUNIT_TEST(test_iter_minus_1);
	CPPUNIT_TEST(test_iter_minus_2);
	CPPUNIT_TEST(test_iter_minus_3);
	CPPUNIT_TEST(test_iter_minus_4);
	CPPUNIT_TEST(test_iter_dereference_1);
	CPPUNIT_TEST(test_iter_dereference_2);
	CPPUNIT_TEST(test_iter_dereference_3); 
	CPPUNIT_TEST(test_iter_dereference_4); 
	CPPUNIT_TEST(test_iter_increment_1);
	CPPUNIT_TEST(test_iter_increment_2);
	CPPUNIT_TEST(test_iter_increment_3);
	CPPUNIT_TEST(test_iter_decrement_1);
	CPPUNIT_TEST(test_iter_decrement_2);
	CPPUNIT_TEST(test_iter_decrement_3);
	CPPUNIT_TEST(test_iter_plus_equals_1);
	CPPUNIT_TEST(test_iter_plus_equals_2);
	CPPUNIT_TEST(test_iter_plus_equals_3);
	CPPUNIT_TEST(test_iter_minus_equals_1);
	CPPUNIT_TEST(test_iter_minus_equals_2);
	CPPUNIT_TEST(test_iter_minus_equals_3);
	CPPUNIT_TEST(test_iter_minus_equals_4);

	CPPUNIT_TEST(test_const_iter_equality_1);
	CPPUNIT_TEST(test_const_iter_equality_2);
	CPPUNIT_TEST(test_const_iter_equality_3);
	CPPUNIT_TEST(test_const_iter_equality_4);
	CPPUNIT_TEST(test_const_iter_plus_1);
	CPPUNIT_TEST(test_const_iter_plus_2);
	CPPUNIT_TEST(test_const_iter_plus_3);
	CPPUNIT_TEST(test_const_iter_plus_4);
	CPPUNIT_TEST(test_const_iter_minus_1);
	CPPUNIT_TEST(test_const_iter_minus_2);
	CPPUNIT_TEST(test_const_iter_minus_3);
	CPPUNIT_TEST(test_const_iter_minus_4);
	CPPUNIT_TEST(test_const_iter_dereference_1);
	CPPUNIT_TEST(test_const_iter_dereference_2);
	CPPUNIT_TEST(test_const_iter_dereference_3); 
	CPPUNIT_TEST(test_const_iter_dereference_4); 
	CPPUNIT_TEST(test_const_iter_increment_1);
	CPPUNIT_TEST(test_const_iter_increment_2);
	CPPUNIT_TEST(test_const_iter_increment_3);
	CPPUNIT_TEST(test_const_iter_decrement_1);
	CPPUNIT_TEST(test_const_iter_decrement_2);
	CPPUNIT_TEST(test_const_iter_decrement_3);
	CPPUNIT_TEST(test_const_iter_plus_equals_1);
	CPPUNIT_TEST(test_const_iter_plus_equals_2);
	CPPUNIT_TEST(test_const_iter_plus_equals_3);
	CPPUNIT_TEST(test_const_iter_minus_equals_1);
	CPPUNIT_TEST(test_const_iter_minus_equals_2);
	CPPUNIT_TEST(test_const_iter_minus_equals_3);
	CPPUNIT_TEST(test_const_iter_minus_equals_4);

	CPPUNIT_TEST(test_constructor_1);
	CPPUNIT_TEST(test_constructor_2);
	CPPUNIT_TEST(test_constructor_3);
	CPPUNIT_TEST(test_constructor_4);
	CPPUNIT_TEST(test_constructor_5);
	CPPUNIT_TEST(test_constructor_6);
	CPPUNIT_TEST(test_constructor_7);
	CPPUNIT_TEST(test_assign_1);
	CPPUNIT_TEST(test_assign_2);
	CPPUNIT_TEST(test_assign_3);
	CPPUNIT_TEST(test_assign_4);
	CPPUNIT_TEST(test_assign_5);
	CPPUNIT_TEST(test_assign_6);
	CPPUNIT_TEST(test_assign_7);
	CPPUNIT_TEST(test_indexing_1);
	CPPUNIT_TEST(test_indexing_2);
	CPPUNIT_TEST(test_indexing_3);
	CPPUNIT_TEST(test_at_1);
	CPPUNIT_TEST(test_at_2);
	CPPUNIT_TEST(test_at_3);
	CPPUNIT_TEST(test_back_front_1);
	CPPUNIT_TEST(test_back_front_2);
	CPPUNIT_TEST(test_back_front_3);
	CPPUNIT_TEST(test_back_front_4);
	CPPUNIT_TEST(test_back_front_5);
	CPPUNIT_TEST(test_back_front_6);
	CPPUNIT_TEST(test_begin_1);
	CPPUNIT_TEST(test_begin_2);
	CPPUNIT_TEST(test_begin_3);
    CPPUNIT_TEST(test_clear_1);
    CPPUNIT_TEST(test_clear_2);
    CPPUNIT_TEST(test_clear_3);
    CPPUNIT_TEST(test_clear_4);
    CPPUNIT_TEST(test_empty_1);
    CPPUNIT_TEST(test_empty_2);
    CPPUNIT_TEST(test_empty_3);
    CPPUNIT_TEST(test_empty_4);
    CPPUNIT_TEST(test_end_1);
    CPPUNIT_TEST(test_end_2);
    CPPUNIT_TEST(test_end_3);
	CPPUNIT_TEST(test_erase_1);
	CPPUNIT_TEST(test_erase_2);
	CPPUNIT_TEST(test_erase_3);
	CPPUNIT_TEST(test_erase_4);
	CPPUNIT_TEST(test_erase_5);
	CPPUNIT_TEST(test_erase_6);
	CPPUNIT_TEST(test_erase_7);
	CPPUNIT_TEST(test_insert_1);
	CPPUNIT_TEST(test_insert_2);
	CPPUNIT_TEST(test_insert_3); 
	CPPUNIT_TEST(test_insert_4);
	CPPUNIT_TEST(test_insert_5);
	CPPUNIT_TEST(test_pop_1);
	CPPUNIT_TEST(test_pop_2);
	CPPUNIT_TEST(test_pop_3);
	CPPUNIT_TEST(test_pop_4);
	CPPUNIT_TEST(test_pop_5);
	CPPUNIT_TEST(test_pop_6);
	CPPUNIT_TEST(test_push_1);
	CPPUNIT_TEST(test_push_2);
	CPPUNIT_TEST(test_push_3);
	CPPUNIT_TEST(test_push_4);
	CPPUNIT_TEST(test_push_5);
	CPPUNIT_TEST(test_push_6);
	CPPUNIT_TEST(test_resize_1);
	CPPUNIT_TEST(test_resize_2);
	CPPUNIT_TEST(test_resize_3);
	CPPUNIT_TEST(test_resize_4);
	CPPUNIT_TEST(test_resize_5);
	CPPUNIT_TEST(test_resize_6);
	CPPUNIT_TEST(test_resize_7);
	CPPUNIT_TEST(test_resize_8);
	CPPUNIT_TEST(test_resize_9);
	CPPUNIT_TEST(test_resize_10);
	CPPUNIT_TEST(test_resize_11);
	CPPUNIT_TEST(test_size_1);
	CPPUNIT_TEST(test_size_2);
	CPPUNIT_TEST(test_size_3);
	CPPUNIT_TEST(test_swap_1);
	CPPUNIT_TEST(test_swap_2);
	CPPUNIT_TEST(test_swap_3);
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () {
	using namespace std;
	ios_base::sync_with_stdio(false);		// turn off synchronization with C I/O
	cout << "TestDeque.c++" << endl << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestDeque< MyDeque<int> >::suite());
	tr.addTest(TestDeque<   deque<int> >::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;}
