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

 
    // -------------------
    // test_mydeque_equality
	// -------------------

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

    // --------------------
	// test_mydeque_less_than
	// --------------------
    
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

	// ---------------------
	// test_iter_dereference
	// ---------------------
	
	void test_iter_dereference_1() {
		C d(11, 6);
		for(int i = 0; i < 6; i++)
		    d.push_back(1);
		typename C::iterator it1 = d.end() - 6;
		CPPUNIT_ASSERT(*it1 == 1);
		typename C::iterator it2 = d.begin() + 10;
		CPPUNIT_ASSERT(*it2 == 6);
		++it2;
		CPPUNIT_ASSERT(it1 == it2);
		CPPUNIT_ASSERT(*it1 == *it2);
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
			++it1;
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

	// --------------
	// test_iter_plus
	// --------------

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

	// -----------------
	// test_constructor
	// -----------------

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
		const unsigned x = 14;
		C d(x, 'a');

		CPPUNIT_ASSERT(d.size() == x);		
		CPPUNIT_ASSERT(d.end() == d.begin() + d.size());
		for (unsigned i = 0; i < x; ++i)
			CPPUNIT_ASSERT(d[i] == 'a');
	}

	void test_constructor_4() {
		C d(1000, 235);

		CPPUNIT_ASSERT(d.size() == 1000);
		CPPUNIT_ASSERT(d.end() == d.begin() + d.size());
		for (int i = 0; i < 1000; ++i)
			CPPUNIT_ASSERT(d[i] == 235);
	}
  
	void test_constructor_5() {
		const unsigned x = 423;
		C d(x, 97);
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
 
		CPPUNIT_ASSERT(e.size() == 4);
		for (int i = 0; i < 4; ++i)
			CPPUNIT_ASSERT(e[i] == d[i]);
	}

	void test_assign_2() {
		C d;
		C e(20, 'a');
		CPPUNIT_ASSERT(e.size() == 20);
		e = d;
		CPPUNIT_ASSERT(e.size() == 0);
	} 

	void test_assign_3() {
		C d(550, 2);
		C e(0, 1);
		e = d;	   
 
		CPPUNIT_ASSERT(e.size() == 550);
		for (int i = 0; i < 550; ++i)
			CPPUNIT_ASSERT(e[i] == d[i]);
	}

	void test_assign_4() {
		C e(3, 2);
		C d(e);
		e = d;	   
 
		CPPUNIT_ASSERT(e.size() == 3);
		for (int i = 0; i < 3; ++i)
			CPPUNIT_ASSERT(e[i] == d[i]);
	}

    // -------------
	// test_indexing
	// -------------
	
	void test_iter_indexing_1() {
		C d(0);
		d.push_back(1);
		CPPUNIT_ASSERT(d[0] == 1);
	}
	
	void test_iter_indexing_2() {
		C d(11, 6);
		d.push_back(1);
		d.push_front(-3);
		CPPUNIT_ASSERT(d[0] == -3);
		for(int i = 1; i < 12; i++)
		    CPPUNIT_ASSERT(d[i] == 6);
		CPPUNIT_ASSERT(d[12] == 1);
	}
	
	void test_iter_indexing_3() {
		C d;
		C e(2, 1);
		d.push_back(1);
		d.push_front(0);
		CPPUNIT_ASSERT(d[0] == 0);
		CPPUNIT_ASSERT(d[1] == 1);
		CPPUNIT_ASSERT(d[1] == e[1]);
		CPPUNIT_ASSERT(&d[1] != &e[1]);
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
	}

	void test_back_front_2() {
		C d(30, 6);
		CPPUNIT_ASSERT(d.size() == 30);
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
	}
	
	// ---------------------
	// test_resize and clear
	// ---------------------
	
	void test_clear() {
		C d(32, 7);
		d.clear();
		CPPUNIT_ASSERT(d.empty());
		CPPUNIT_ASSERT(d.begin() == d.end());
	}
	
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
		const int x = 16;
		C e(3, 2);
		e.resize(x, 5); 
 
		CPPUNIT_ASSERT(e.size() == (unsigned) x);
		for (int i = 0; i < 3; ++i)
			CPPUNIT_ASSERT(e[i] == 2);
		for (int i = 3; i < 16; ++i)
			CPPUNIT_ASSERT(e[i] == 5);
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
        d.insert(d.begin(), 3);
		d.insert(d.begin(), 2);
		d.insert(d.end(), 4);
		
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
		
	//-----------
	// test erase
	//-----------
	
	void test_erase_1() {
		C d(2, 4);
        d.push_front(3); 
		d.push_back(2);
		d.erase(d.begin() + 2);
		d.erase(d.end() - 3);
		
		int x[] = {4, 2};
		CPPUNIT_ASSERT(d.size() == 2);
		for(int i = 0; i < 2; i++)
		    CPPUNIT_ASSERT(d[i] == x[i]);
	}
	
	void test_erase_2() {
		C d;
        d.push_back(2);
		d.push_back(3);
		d.push_back(4);
		d.push_back(5);
		d.push_back(6);
		
		d.erase(d.begin());
		d.erase(d.end() - 1);
		d.erase(d.begin() + 1);
		
		int x[] = {3, 5};
		CPPUNIT_ASSERT(d.size() == 2);
		for(int i = 0; i < 2; i++)
		    CPPUNIT_ASSERT(d[i] == x[i]);
	}
	
	void test_erase_3() {
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
	
	void test_erase_4() {
		C d(1, 8);
		typename C::iterator it = d.erase(d.begin());
		d.insert(it, 2);
		
		CPPUNIT_ASSERT(d.size() == 1);
		CPPUNIT_ASSERT(d[0] == 2);
	}

	//const_it	
		
	// -----
	// suite
	// -----

	CPPUNIT_TEST_SUITE(TestDeque); 
	CPPUNIT_TEST(test_mydeque_equality_1);
	CPPUNIT_TEST(test_mydeque_equality_2);
	CPPUNIT_TEST(test_mydeque_equality_3);
	CPPUNIT_TEST(test_mydeque_less_than_1);
	CPPUNIT_TEST(test_mydeque_less_than_2);
	CPPUNIT_TEST(test_mydeque_less_than_3);
	CPPUNIT_TEST(test_iter_equality_1);
	CPPUNIT_TEST(test_iter_equality_2);
	CPPUNIT_TEST(test_iter_equality_3);
	CPPUNIT_TEST(test_iter_dereference_1);
	CPPUNIT_TEST(test_iter_dereference_2);
	CPPUNIT_TEST(test_iter_dereference_3); 
	CPPUNIT_TEST(test_iter_plus_1);
	CPPUNIT_TEST(test_iter_plus_2);
	CPPUNIT_TEST(test_iter_plus_3);
	CPPUNIT_TEST(test_iter_minus_1);
	CPPUNIT_TEST(test_iter_minus_2);
	CPPUNIT_TEST(test_iter_minus_3);
	CPPUNIT_TEST(test_constructor_1);
	CPPUNIT_TEST(test_constructor_2);
	CPPUNIT_TEST(test_constructor_3);
	CPPUNIT_TEST(test_constructor_4);
	CPPUNIT_TEST(test_constructor_5);
	CPPUNIT_TEST(test_assign_1);
	CPPUNIT_TEST(test_assign_2);
	CPPUNIT_TEST(test_assign_3);
	CPPUNIT_TEST(test_assign_4);
	CPPUNIT_TEST(test_iter_indexing_1);
	CPPUNIT_TEST(test_iter_indexing_2);
	CPPUNIT_TEST(test_iter_indexing_3);
	CPPUNIT_TEST(test_back_front_1);
	CPPUNIT_TEST(test_back_front_2);
	CPPUNIT_TEST(test_back_front_3);
	CPPUNIT_TEST(test_resize_1);
	CPPUNIT_TEST(test_resize_2);
	CPPUNIT_TEST(test_resize_3);
    CPPUNIT_TEST(test_clear);
	CPPUNIT_TEST(test_size_1);
	CPPUNIT_TEST(test_size_2);
	CPPUNIT_TEST(test_size_3);
	CPPUNIT_TEST(test_pop_1);
	CPPUNIT_TEST(test_pop_3);
	CPPUNIT_TEST(test_pop_2);
	CPPUNIT_TEST(test_push_1);
	CPPUNIT_TEST(test_push_2);
	CPPUNIT_TEST(test_push_3);
	CPPUNIT_TEST(test_swap_1);
	CPPUNIT_TEST(test_swap_2);
	CPPUNIT_TEST(test_swap_3);
	CPPUNIT_TEST(test_insert_1);
	CPPUNIT_TEST(test_insert_2);
	CPPUNIT_TEST(test_insert_3); 
	CPPUNIT_TEST(test_insert_4);
	CPPUNIT_TEST(test_erase_1);
	CPPUNIT_TEST(test_erase_2);
	CPPUNIT_TEST(test_erase_3);
	CPPUNIT_TEST(test_erase_4);
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
