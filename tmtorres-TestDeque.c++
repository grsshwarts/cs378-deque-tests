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
#include <deque>     // deque
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TestSuite.h"               // TestSuite
#include "cppunit/TextTestRunner.h"          // TestRunner

#include "Deque.h"

// ---------
// TestDeque
// ---------

template <typename C>
struct TestDeque : CppUnit::TestFixture {
    // ----
    // constructors
    // ----
    
    void test_constructor_1_1 ()
    {
        C x;
        
        CPPUNIT_ASSERT(x.size() == 0);
    }
    
    void test_constructor_1_2 () 
    {
        C y;
        
        CPPUNIT_ASSERT(y.size() == 0);
    }
    
    void test_constructor_1_3 () 
    {
        C z;
        
        CPPUNIT_ASSERT(z.size() == 0);
    }
    
    void test_constructor_2_1 () 
    {
        C x (1);
        
        CPPUNIT_ASSERT(x.size() == 1);
        CPPUNIT_ASSERT(x.front() == 0);
        CPPUNIT_ASSERT(x.front() == x.back());
    }
    
    void test_constructor_2_2 () 
    {
        C y (2, 12);
        
        CPPUNIT_ASSERT(y.size() == 2);
        CPPUNIT_ASSERT(y.front() == 12);
        CPPUNIT_ASSERT(y.front() == y.back());
    }
    
    void test_constructor_2_3 () 
    {
        C z (3, 21);
        
        CPPUNIT_ASSERT(z.size() == 3);
        CPPUNIT_ASSERT(z.front() == 21);
        CPPUNIT_ASSERT(z.front() == z.back());
    }
    
    void test_constructor_3_1 () 
    {
        C x;
        
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        
        C y = x;
        
        CPPUNIT_ASSERT(x[0] == y[0]);
        CPPUNIT_ASSERT(x[1] == y[1]);
        CPPUNIT_ASSERT(x[2] == y[2]);
        CPPUNIT_ASSERT(x.size() == 3);
        CPPUNIT_ASSERT(x.size() == y.size());
    }
    
    void test_constructor_3_2 () 
    {
        C x;
        
        x.push_front(1);
        x.push_front(2);
        x.push_front(3);
        
        C y = x;
        
        CPPUNIT_ASSERT(x[0] == y[0]);
        CPPUNIT_ASSERT(x[1] == y[1]);
        CPPUNIT_ASSERT(x[2] == y[2]);
        CPPUNIT_ASSERT(x.size() == 3);
        CPPUNIT_ASSERT(x.size() == y.size());
    }
    
    void test_constructor_3_3 () 
    {
        C x (5, 9);
        C y (x);
        
        CPPUNIT_ASSERT(x[0] == y[0]);
        CPPUNIT_ASSERT(x[1] == y[1]);
        CPPUNIT_ASSERT(x[2] == y[2]);
        CPPUNIT_ASSERT(x.size() == 5);
        CPPUNIT_ASSERT(x.size() == y.size());
    }
    
    
    // ----
    // equality
    // ----
    void test_equality_1 () 
    {
        C x;
        
        x.push_front(1);
        x.push_front(2);
        x.push_front(3);
        
        C y = x;
        
        CPPUNIT_ASSERT(y == x);
        CPPUNIT_ASSERT(x == y);
    }
    
    void test_equality_2 () 
    {
        C x;
        C y = x;
        
        CPPUNIT_ASSERT(y == x);
        CPPUNIT_ASSERT(x == y);
    }
    
    void test_equality_3 () 
    {
        C x;
        
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        
        CPPUNIT_ASSERT(y != x);
        CPPUNIT_ASSERT(x != y);
        
        y = x;
        
        CPPUNIT_ASSERT(y == x);
        CPPUNIT_ASSERT(x == y);
    }
    
    
    // ----
    // lexicographical compare
    // ----
    void test_comparison_1 () 
    {
        C x;
        C y;
        
        x.push_back(7);
        x.push_back(8);
        x.push_back(9);
        
        y.push_back(10);
        y.push_back(11);
        y.push_back(12);
        
        CPPUNIT_ASSERT(x < y);
        CPPUNIT_ASSERT(!(y < x));
    }
    
    void test_comparison_2 () 
    {
        C x;
        C y;
        
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        
        y.push_back(4);
        y.push_back(5);
        y.push_back(6);
        
        CPPUNIT_ASSERT(x < y);
        CPPUNIT_ASSERT(!(y < x));
    }
    
    void test_comparison_3 () 
    {
        C x;
        C y;
        
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        
        y.push_back(1);
        y.push_back(2);
        y.push_back(3);
        
        CPPUNIT_ASSERT(!(x < y));
        CPPUNIT_ASSERT(!(y < x));
    }
    
    // ----
    // iterator constructor
    // ----
    void test_iterator_constructor_1 () 
    {
        C x;
        
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        
        typename C::iterator it1 = x.begin();
        typename C::iterator it2 = (x.end() - 1);
        
        CPPUNIT_ASSERT(*it1 == 1);
        CPPUNIT_ASSERT(*it2 == 3);
    }
    
    void test_iterator_constructor_2 () 
    {
        C x;
        
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        
        typename C::iterator it1 = x.begin();
        typename C::iterator it2 = x.end() - 1;
        
        CPPUNIT_ASSERT(*it1 == 1);
        CPPUNIT_ASSERT(*(it1 + 2) == 3);
        CPPUNIT_ASSERT(*(it2 - 1) == 5);
        CPPUNIT_ASSERT(*it2 != 5);
    }
    
    void test_iterator_constructor_3 () 
    {
        C x;
        
        x.push_back(1);
        
        typename C::iterator it1 = x.begin();
        typename C::iterator it2 = x.end();
        
        CPPUNIT_ASSERT(it1 == it2 - 1);
        CPPUNIT_ASSERT(it1 != it2);
    }
    
    
    // ----
    // iterator equality
    // ----
    void test_iterator_equality_1 () 
    {
        C x;
        
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        
        typename C::iterator it1 = x.begin() + 2;
        CPPUNIT_ASSERT(x.end() - 4 == it1);
    }
    
    void test_iterator_equality_2 () 
    {
        C x;
        
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        
        typename C::iterator it1 = x.begin() + 2;
        CPPUNIT_ASSERT(x.end() != it1);
        CPPUNIT_ASSERT(x.begin() + 2 == it1);
    }
    
    void test_iterator_equality_3 () 
    {
        C x;
        
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.push_back(3);
        x.push_back(4);
        x.push_back(5);
        
        typename C::iterator it1 = x.begin() + 2;
        typename C::iterator it2 = x.end() - 3;
        CPPUNIT_ASSERT(*it1 == 3);
        CPPUNIT_ASSERT(*it2 == 3);
        CPPUNIT_ASSERT(it2 != it1);
    }
    
    // ----
    // iterator increment
    // ----
    void test_iterator_increment_1 () 
    {
        C y;
        
        y.push_back(1);
        y.push_back(2);
        
        typename C::iterator it1 = y.begin();
        
        CPPUNIT_ASSERT(*it1 == 1);
        
        ++it1;
        
        CPPUNIT_ASSERT(*it1 == 2);
    }
    
    void test_iterator_increment_2 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        
        typename C::iterator it = y.begin();
        
        int sum = 0;
        
        while(it != y.end())
        {
            sum += *it;
            ++it;
        }
        
        CPPUNIT_ASSERT(sum == 6);
        CPPUNIT_ASSERT(it == y.end());
    }
    
    void test_iterator_increment_3 () 
    {
        C y;
        C x (5);
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(5);
        
        CPPUNIT_ASSERT(y != x);
        CPPUNIT_ASSERT(x != y);
        
        typename C::iterator it1 = y.begin();
        typename C::iterator it2 = x.begin();
        
        
        while(it1 != y.end())
        {
            *it2 = *it1;
            ++it1;
            ++it2;
        }
        
        CPPUNIT_ASSERT(x == y);
        CPPUNIT_ASSERT(y == x);
    }
    
    // ----
    // iterator decrement
    // ----
    void test_iterator_decrement_1 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(5);
        
        typename C::iterator it1 = y.end();
        
        CPPUNIT_ASSERT(*(--it1) == 1);
    }
    
    void test_iterator_decrement_2 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(5);
        
        typename C::iterator it1 = y.end();
        
        int i = 1;
        --it1;
        
        while(it1 != y.begin())
        {
            CPPUNIT_ASSERT(*it1 == i);
            --it1;
            ++i;
        }
        
    }
    
    void test_iterator_decrement_3 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        
        typename C::iterator it1 = y.end();
        
        CPPUNIT_ASSERT(*(--(--it1)) == 2);
        
    }
    
    // ----
    // iterator plus_equals
    // ----
    void test_iterator_plus_equals_1 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(5);
        y.push_front(6);
        y.push_front(7);
        y.push_front(8);
        y.push_front(9);
        y.push_front(10);
        
        typename C::iterator it1 = y.begin();
        typename C::iterator it2 = it1;
        
        it1 += 5;
        CPPUNIT_ASSERT(*it1 == 5);
        CPPUNIT_ASSERT(it1 != it2);
    }
    
    void test_iterator_plus_equals_2 () 
    {
        C y;
        
        y.push_back(1);
        y.push_back(2);
        y.push_back(3);
        y.push_back(4);
        y.push_back(5);
        y.push_back(6);
        y.push_back(7);
        y.push_back(8);
        y.push_back(9);
        y.push_back(10);
        
        typename C::iterator it1 = y.begin();
        typename C::iterator it2 = it1;
        
        it1 += 5;
        CPPUNIT_ASSERT(*it1 == 6);
        CPPUNIT_ASSERT(it1 != it2);
    }
    
    void test_iterator_plus_equals_3 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(5);
        y.push_front(6);
        y.push_front(7);
        y.push_front(8);
        y.push_front(9);
        y.push_front(10);
        
        typename C::iterator it1 = y.begin();
        typename C::iterator it2 = it1;
        
        it1 += 1;
        CPPUNIT_ASSERT(*it1 == 9);
        CPPUNIT_ASSERT(it1 != it2);
    }
    
    
    // ----
    // iterator minus equals
    // ----
    void test_iterator_minus_equals_1 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(5);
        y.push_front(6);
        y.push_front(7);
        y.push_front(8);
        y.push_front(9);
        y.push_front(10);
        
        typename C::iterator it1 = y.end();
        typename C::iterator it2 = it1;
        
        it1 -= 1;
        CPPUNIT_ASSERT(*it1 == 1);
        CPPUNIT_ASSERT(it1 != it2);
    }
    
    void test_iterator_minus_equals_2 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(5);
        y.push_front(6);
        y.push_front(7);
        y.push_front(8);
        y.push_front(9);
        y.push_front(10);
        
        typename C::iterator it1 = y.end();
        typename C::iterator it2 = it1;
        
        it1 -= 5;
        CPPUNIT_ASSERT(*it1 == 5);
        CPPUNIT_ASSERT(it1 != it2);
    }
    
    void test_iterator_minus_equals_3 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(5);
        y.push_front(6);
        y.push_front(7);
        y.push_front(8);
        y.push_front(9);
        y.push_front(10);
        
        typename C::iterator it1 = y.end();
        typename C::iterator it2 = it1;
        
        it1 -= 10;
        CPPUNIT_ASSERT(*it1 == 10);
        CPPUNIT_ASSERT(it1 != it2);
        CPPUNIT_ASSERT(it1 == y.begin());
    }
    
    // ----
    // equals
    // ----
    void test_equals_1 () 
    {
        C y;
        C x;
        C z;
    
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(5);
        
        x.push_front(1);
        x.push_front(2);
        x.push_front(3);
        x.push_front(4);
        x.push_front(5);
        
        CPPUNIT_ASSERT(x == y); 
        CPPUNIT_ASSERT(y == x);
        CPPUNIT_ASSERT(!(x != y));
        
        CPPUNIT_ASSERT(!(z == x));
        CPPUNIT_ASSERT(!(z == y));
        
        z = x;
        
        CPPUNIT_ASSERT(z == y); 
        CPPUNIT_ASSERT(z == x);
        
    }
    
    void test_equals_2 () 
    {
        C y;
        C x;
        C z;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(5);
        
        x.push_front(1);
        x.push_front(2);
        x.push_front(3);
        x.push_front(4);
        x.push_front(5);
        
        CPPUNIT_ASSERT(x == y); 
        CPPUNIT_ASSERT(y == x);
        CPPUNIT_ASSERT(z != x);
        CPPUNIT_ASSERT(z != y);
        
        z = x;
    
        CPPUNIT_ASSERT(z == x);
        CPPUNIT_ASSERT(z == y);
        
    }
    
    void test_equals_3 () 
    {
        C y;
        C x;
        
        CPPUNIT_ASSERT(x == y);
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(5);
        
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.push_back(4);
        x.push_back(5);
        
        CPPUNIT_ASSERT(x != y); 
        CPPUNIT_ASSERT(y != x);
        
        y = x;
        
        CPPUNIT_ASSERT(y == x);
        CPPUNIT_ASSERT(y == x);
    }
    
    // ----
    // dereference
    // ----
    void test_RA_1 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(5);
        y.push_front(6);
        y.push_front(7);
        y.push_front(8);
        y.push_front(9);
        
        CPPUNIT_ASSERT(y[0] == 9);
        CPPUNIT_ASSERT(y[8] == 1);
    }
    
    void test_RA_2 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(5);
        y.push_front(6);
        y.push_front(7);
        y.push_front(8);
        y.push_front(9);
        
        CPPUNIT_ASSERT(y[5] == 4);
        CPPUNIT_ASSERT(y[3] == 6);
    }
    
    void test_RA_3 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(5);
        y.push_front(6);
        y.push_front(7);
        y.push_front(8);
        y.push_front(9);
        
        y[0] = 3;
        
        CPPUNIT_ASSERT(y[0] != 9);
        CPPUNIT_ASSERT(y[0] == 3);
    }
    
    // ----
    // back
    // ----
    void test_back_1 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        
        CPPUNIT_ASSERT(y.back() == 1);
        CPPUNIT_ASSERT(y.back() - 1 == 0);
    }
    
    void test_back_2 () 
    {
        C y;
        y.push_front(1);
        
        CPPUNIT_ASSERT(y.back() == y.front());
    }
    
    void test_back_3 () 
    {
        C y(10, 6);
        
        CPPUNIT_ASSERT(y.back() == y.front());
        CPPUNIT_ASSERT(y.back() == 6);
    }
    
    // ----
    // begin
    // ----
    void test_begin_1 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        
        CPPUNIT_ASSERT(*y.begin() == 3);

    }
    
    void test_begin_2 () 
    {
        C y (10, 21);
        
        CPPUNIT_ASSERT(*y.begin() == 21);
    }
    
    void test_begin_3 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        
        C x = y;
        
        CPPUNIT_ASSERT(*x.begin() == 3);
    }
    
    
    // ----
    // clear
    // ----
    void test_clear_1 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        
        y.clear();
        
        CPPUNIT_ASSERT(y.size() == 0);
    }
    
    void test_clear_2 () 
    {
        C y;
        y.clear();
        
        CPPUNIT_ASSERT(y.size() == 0);
    }
    
    void test_clear_3 () 
    {
        C x;
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        
        x = y;
        x.clear();
        
        CPPUNIT_ASSERT(x.size() == 0);
        CPPUNIT_ASSERT(y.size() == 4);
        
    }
    
    // ----
    // empty
    // ----
    void test_empty_1 () 
    {
        C x;
        
        CPPUNIT_ASSERT(x.size() == 0);
        CPPUNIT_ASSERT(x.empty());
    }
    
    void test_empty_2 () 
    {
        C x;
        x.push_back(0);
        
        CPPUNIT_ASSERT(x.size() != 0);
        CPPUNIT_ASSERT(!x.empty());
    }
    
    void test_empty_3 () 
    {
        C x;
        x.push_back(0);
        x.pop_back();
        
        CPPUNIT_ASSERT(x.size() == 0);
        CPPUNIT_ASSERT(x.empty());
    }
    
    
    // ----
    // end
    // ----
    void test_end_1 () 
    {
        C y;
        
        y.push_front(21);
        
        CPPUNIT_ASSERT(*(y.end() - 1) == 21);
        
        y.push_front(31);
        y.push_front(41);
        
        CPPUNIT_ASSERT(*(y.end() - 1) == 21);
    }
    
    void test_end_2 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(5);
        y.push_front(6);
        y.push_front(7);
        y.push_front(8);
        y.push_front(9);
        y.push_front(10);
        y.push_front(11);
        
        CPPUNIT_ASSERT(*(y.end() - 1) == 1);
    }
    
    void test_end_3 () 
    {
        C y;
        
        y.push_back(1);
        y.push_back(2);
        y.push_back(3);
        y.push_back(4);
        y.push_back(5);
        y.push_back(6);
        y.push_back(7);
        y.push_back(8);
        y.push_back(9);
        y.push_back(10);
        y.push_back(11);
        
        CPPUNIT_ASSERT(*(y.end() - 1) == 11);
    }
    
    // ----
    // erase
    // ----
    void test_erase_1 () 
    {
        C y;
        
        y.push_back(1);
        y.push_back(2);
        y.push_back(3);
        y.push_back(4);
        y.push_back(5);
        y.push_back(6);
        y.push_back(7);
        y.push_back(8);
        y.push_back(9);
        y.push_back(10);
        y.push_back(11);
        
        CPPUNIT_ASSERT(*(y.erase(y.begin())) == 2);
    }
    
    void test_erase_2 () 
    {
        C y;
        
        y.push_back(1);
        y.push_back(2);
        y.push_back(3);
        y.push_back(4);
        y.push_back(5);
        y.push_back(6);
        y.push_back(7);
        y.push_back(8);
        y.push_back(9);
        y.push_back(10);
        y.push_back(11);
        
        y.erase(y.end());
        
        CPPUNIT_ASSERT(*(y.end() - 1) == 10);
        
        y.erase(y.end() - 1);
        
        CPPUNIT_ASSERT(*(y.end() - 1) == 9);
    }
    
    void test_erase_3 () 
    {
        C y;
        
        y.push_back(1);
        y.push_back(2);
        y.push_back(3);
        y.push_back(4);
        y.push_back(5);
        y.push_back(6);
        y.push_back(7);
        y.push_back(8);
        y.push_back(9);
        y.push_back(10);
        y.push_back(11);
        
        typename C::iterator it = y.erase(y.begin() + 5);
        
        CPPUNIT_ASSERT(*it == 7);
    }
    
    // ----
    // front
    // ----
    void test_front_1 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_back(4);
        
        CPPUNIT_ASSERT(y.front() == 3);
    }
    
    void test_front_2 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.pop_front();
        
        CPPUNIT_ASSERT(y.front() == 2);
    }
    
    void test_front_3 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        
        CPPUNIT_ASSERT(y.front() == 3);
    }
    
    
    // ----
    // insert
    // ----
    void test_insert_1 () 
    {
        C y;
        C x;
        
        y.push_back(5);
        y.push_back(6);
        y.push_back(7);
        y.push_back(8);
        y.push_back(9);
        
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);
        x.push_back(8);
        
        CPPUNIT_ASSERT(x.size() == 4);
        
        x.insert(x.end(), 9);
        
        CPPUNIT_ASSERT(y == x);
        CPPUNIT_ASSERT(x.size() == 5);
    }
    
    void test_insert_2 () 
    {
        C y;
        C x;
        
        y.push_back(4);
        y.push_back(5);
        y.push_back(6);
        y.push_back(7);
        y.push_back(8);
        
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);
        x.push_back(8);
        
        CPPUNIT_ASSERT(x.size() == 4);
        
        x.insert(x.begin(), 4);
        
        CPPUNIT_ASSERT(y == x);
        CPPUNIT_ASSERT(x.size() == 5);
    }
    
    void test_insert_3 () 
    {
        C y;
        C x;
        
        y.push_back(4);
        y.push_back(5);
        y.push_back(6);
        y.push_back(7);
        y.push_back(8);
        
        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(8);
        
        CPPUNIT_ASSERT(x.size() == 4);
        
        x.insert(x.begin() + 3, 7);
        
        CPPUNIT_ASSERT(y == x);
        CPPUNIT_ASSERT(x.size() == 5);
    }
    
    
    // ----
    // pop_back
    // ----
    void test_pop_back_1 () 
    {
        C y;
        C x;
        
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        
        y.push_back(1);
        y.push_back(2);
        y.push_back(3);
        y.push_back(4);
        y.push_back(5);
        y.push_back(6);
        y.push_back(7);
        y.push_back(8);
        y.push_back(9);
        
        CPPUNIT_ASSERT(y.size() == 9);
        
        y.pop_back();
        y.pop_back();
        y.pop_back();
        y.pop_back();
        y.pop_back();
        y.pop_back();
        
        CPPUNIT_ASSERT(y.size() == 3);
        CPPUNIT_ASSERT(y == x);        
    }
    
    void test_pop_back_2 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        
        y.pop_back();
        y.pop_back();
        y.pop_back();
        
        CPPUNIT_ASSERT(y.size() == 1);
        CPPUNIT_ASSERT(y.front() == y.back());
        CPPUNIT_ASSERT(y.front() == 4);
    }
    
    void test_pop_back_3 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(5);
        y.push_front(6);
        y.push_front(7);
        y.push_front(8);
        y.push_front(9);
        y.push_front(10);
        y.push_front(11);
        
        CPPUNIT_ASSERT(y.size() == 11);
        
        y.pop_back();
        y.pop_back();
        y.pop_back();
        y.pop_back();
        y.pop_back();
        y.pop_back();
        
        CPPUNIT_ASSERT(y.front() == 11);
        CPPUNIT_ASSERT(y.back() == 7);
        CPPUNIT_ASSERT(y.size() == 5);
    }
    
    
    // ----
    // pop_front
    // ----
    void test_pop_front_1 () 
    {
        C y;
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(5);
        y.push_front(6);
        y.push_front(7);
        y.push_front(8);
        y.push_front(9);
        y.push_front(10);
        y.push_front(11);
        
        y.pop_front();
        y.pop_front();
        y.pop_front();
        
        CPPUNIT_ASSERT(y.size() == 8);
        CPPUNIT_ASSERT(y.front() == 8);
        CPPUNIT_ASSERT(y.back() == 1);
    }
    
    void test_pop_front_2 () 
    {
        C y;
        
        y.push_back(1);
        y.push_back(2);
        y.push_back(3);
        y.push_back(4);
        y.push_back(5);
        y.push_back(6);
        y.push_back(7);
        y.push_back(8);
        y.push_back(9);
        y.push_back(10);
        y.push_back(11);
        
        y.pop_front();
        y.pop_front();
        y.pop_front();
        
        CPPUNIT_ASSERT(y.size() == 8);
        CPPUNIT_ASSERT(y.front() == 4);
        CPPUNIT_ASSERT(y.back() == 11);
    }
    
    void test_pop_front_3 () 
    {
        C y;
        
        y.push_back(1);
        y.push_back(2);
        y.push_back(3);
        y.push_back(4);
        y.push_back(5);
        y.push_back(6);
        y.push_back(7);
        y.push_back(8);
        y.push_back(9);
        y.push_back(10);
        y.push_back(11);
        
        y.pop_front();
        y.pop_front();
        y.pop_front();
        y.pop_front();
        y.pop_front();
        y.pop_front();
        y.pop_front();
        y.pop_front();
        y.pop_front();
        y.pop_front();
        y.pop_front();
        
        CPPUNIT_ASSERT(y.size() == 0);
        CPPUNIT_ASSERT(y.begin() == y.end());
    }
    
    
    // ----
    // push_back
    // ----
    void test_push_back_1 () 
    {
        C y;
        
        y.push_back(1);
        y.push_back(2);
        y.push_back(3);
        y.push_back(4);
        y.push_back(5);
        y.push_back(6);
        y.push_back(7);
        y.push_back(8);
        y.push_back(9);
        y.push_back(10);
        y.push_back(11);
        
        CPPUNIT_ASSERT(y.size() == 11);
        CPPUNIT_ASSERT(y.back() == 11);
    }
    
    void test_push_back_2 () 
    {
        C y (10, 3);
        
        y.push_back(3);
        y.push_back(3);
        y.push_back(3);
        
        CPPUNIT_ASSERT(y.size() == 13);
        CPPUNIT_ASSERT(y.back() == 3);
    }
    
    void test_push_back_3 () 
    {
        C y (18, 0);
        
        y.push_back(1);
        y.push_back(2);
        y.push_back(3);
        
        CPPUNIT_ASSERT(y.size() == 21);
        CPPUNIT_ASSERT(y.back() == 3);
        CPPUNIT_ASSERT(y.front() == 0);
    }
    
    
    // ----
    // push_front
    // ----
    void test_push_front_1 () 
    {
        C y;
        
        y.push_front(1);
        
        CPPUNIT_ASSERT(y.end() != y.begin());
        
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        
        CPPUNIT_ASSERT(y.size() == 12);
    }
    
    void test_push_front_2 () 
    {
        C y (10);
        
        y.push_front(1);
        
        CPPUNIT_ASSERT(y.front() == 1);
    }
    
    void test_push_front_3 () 
    {
        C y (10);
        
        y.push_back(11);
        y.push_front(1);
        
        CPPUNIT_ASSERT(y.front() == 1);
        CPPUNIT_ASSERT(y.size() == 12);
    }
    
    
    // ----
    // resize
    // ----
    void test_resize_1 () 
    {
        C y (21);
        CPPUNIT_ASSERT(y.size() == 21);
        
        y.resize(23);
        CPPUNIT_ASSERT(y.size() == 23);
    }
    
    void test_resize_2 () 
    {
        C y (21);
        CPPUNIT_ASSERT(y.size() == 21);
        
        y.resize(19);
        CPPUNIT_ASSERT(y.size() == 19);
    }
    
    void test_resize_3 () 
    {
        C y (21);
        CPPUNIT_ASSERT(y.size() == 21);
        
        y.resize(21);
        CPPUNIT_ASSERT(y.size() == 21);
        
        y.resize(0);
        CPPUNIT_ASSERT(y.size() == 0);
    }
    
    // ----
    // size
    // ----
    void test_size_1 () 
    {
        C y;
        
        CPPUNIT_ASSERT(y.size() == 0);
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        
        CPPUNIT_ASSERT(y.size() == 4);
        
        y.pop_back();
        
        CPPUNIT_ASSERT(y.size() == 3);
    }
    
    void test_size_2 () 
    {
        C y;
        
        CPPUNIT_ASSERT(y.size() == 0);
        
        y.push_back(0);
        y.push_back(0);
        y.push_back(0);
        
        y.pop_back();
        y.pop_back();
        y.pop_back();
        
        CPPUNIT_ASSERT(y.size() == 0);
    }
    
    void test_size_3 () 
    {
        C y (21);
        
        CPPUNIT_ASSERT(y.size() == 21);
        
        y.pop_back();
        y.pop_back();
        y.pop_back();
        
        CPPUNIT_ASSERT(y.size() == 18);
    }
    
    // ----
    // swap
    // ----
    void test_swap_1 () 
    {
        C y;
        C x;
        
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(5);
        
        CPPUNIT_ASSERT(x.size() == 3);
        CPPUNIT_ASSERT(x.front() == 1);
        CPPUNIT_ASSERT(x.back() == 3);
        
        CPPUNIT_ASSERT(y.size() == 5);
        CPPUNIT_ASSERT(y.front() == 5);
        CPPUNIT_ASSERT(y.back() == 1);
        
        x.swap(y);
        
        CPPUNIT_ASSERT(y.size() == 3);
        CPPUNIT_ASSERT(y.front() == 1);
        CPPUNIT_ASSERT(y.back() == 3);
        
        CPPUNIT_ASSERT(x.size() == 5);
        CPPUNIT_ASSERT(x.front() == 5);
        CPPUNIT_ASSERT(x.back() == 1);
    }
    
    void test_swap_2 () 
    {
        C y;
        C x;
        
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        
        y.push_front(1);
        y.push_front(2);
        y.push_front(3);
        y.push_front(4);
        y.push_front(5);
        
        CPPUNIT_ASSERT(x.size() == 3);
        CPPUNIT_ASSERT(x.front() == 1);
        CPPUNIT_ASSERT(x.back() == 3);
        
        CPPUNIT_ASSERT(y.size() == 5);
        CPPUNIT_ASSERT(y.front() == 5);
        CPPUNIT_ASSERT(y.back() == 1);
        
        y.swap(x);
        
        CPPUNIT_ASSERT(y.size() == 3);
        CPPUNIT_ASSERT(y.front() == 1);
        CPPUNIT_ASSERT(y.back() == 3);
        
        CPPUNIT_ASSERT(x.size() == 5);
        CPPUNIT_ASSERT(x.front() == 5);
        CPPUNIT_ASSERT(x.back() == 1);
    }
    
    void test_swap_3 () 
    {
        C y;
        C x;
        
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        
        y.swap(x);
        
        CPPUNIT_ASSERT(y.size() == 3);
        CPPUNIT_ASSERT(y.front() == 1);
        CPPUNIT_ASSERT(y.back() == 3);
        
        CPPUNIT_ASSERT(x.size() == 0);
        
    }
        
    
    
    // -----
    // suite
    // -----
    
    CPPUNIT_TEST_SUITE(TestDeque);
    CPPUNIT_TEST(test_constructor_1_1);
    CPPUNIT_TEST(test_constructor_1_2);
    CPPUNIT_TEST(test_constructor_1_3);
    
    CPPUNIT_TEST(test_constructor_2_1);
    CPPUNIT_TEST(test_constructor_2_2);
    CPPUNIT_TEST(test_constructor_2_3);
    
    CPPUNIT_TEST(test_constructor_3_1);
    CPPUNIT_TEST(test_constructor_3_2);
    CPPUNIT_TEST(test_constructor_3_3);
    
    CPPUNIT_TEST(test_equality_1);
    CPPUNIT_TEST(test_equality_2);
    CPPUNIT_TEST(test_equality_3);
    
    CPPUNIT_TEST(test_comparison_1);
    CPPUNIT_TEST(test_comparison_2);
    CPPUNIT_TEST(test_comparison_3);
    
    CPPUNIT_TEST(test_iterator_constructor_1);
    CPPUNIT_TEST(test_iterator_constructor_2);
    CPPUNIT_TEST(test_iterator_constructor_3);
    
    CPPUNIT_TEST(test_iterator_equality_1);
    CPPUNIT_TEST(test_iterator_equality_2);
    CPPUNIT_TEST(test_iterator_equality_3);
    
    CPPUNIT_TEST(test_iterator_increment_1);
    CPPUNIT_TEST(test_iterator_increment_2);
    CPPUNIT_TEST(test_iterator_increment_3);
    
    CPPUNIT_TEST(test_iterator_decrement_1);
    CPPUNIT_TEST(test_iterator_decrement_2);
    CPPUNIT_TEST(test_iterator_decrement_3);
    
    CPPUNIT_TEST(test_iterator_plus_equals_1);
    CPPUNIT_TEST(test_iterator_plus_equals_2);
    CPPUNIT_TEST(test_iterator_plus_equals_3);
    
    CPPUNIT_TEST(test_iterator_minus_equals_1);
    CPPUNIT_TEST(test_iterator_minus_equals_2);
    CPPUNIT_TEST(test_iterator_minus_equals_3);
    
    CPPUNIT_TEST(test_equals_1);
    CPPUNIT_TEST(test_equals_2);
    CPPUNIT_TEST(test_equals_3);
    
    CPPUNIT_TEST(test_RA_1);
    CPPUNIT_TEST(test_RA_2);
    CPPUNIT_TEST(test_RA_3);
    
    CPPUNIT_TEST(test_back_1);
    CPPUNIT_TEST(test_back_2);
    CPPUNIT_TEST(test_back_3);
    
    CPPUNIT_TEST(test_begin_1);
    CPPUNIT_TEST(test_begin_2);
    CPPUNIT_TEST(test_begin_3);
    
    CPPUNIT_TEST(test_clear_1);
    CPPUNIT_TEST(test_clear_2);
    CPPUNIT_TEST(test_clear_3);
    
    CPPUNIT_TEST(test_empty_1);
    CPPUNIT_TEST(test_empty_2);
    CPPUNIT_TEST(test_empty_3);
    
    CPPUNIT_TEST(test_end_1);
    CPPUNIT_TEST(test_end_2);
    CPPUNIT_TEST(test_end_3);
    
    CPPUNIT_TEST(test_erase_1);
    CPPUNIT_TEST(test_erase_2);
    CPPUNIT_TEST(test_erase_3);
    
    CPPUNIT_TEST(test_front_1);
    CPPUNIT_TEST(test_front_2);
    CPPUNIT_TEST(test_front_3);
    
    CPPUNIT_TEST(test_insert_1);
    CPPUNIT_TEST(test_insert_2);
    CPPUNIT_TEST(test_insert_3);
    
    CPPUNIT_TEST(test_pop_back_1);
    CPPUNIT_TEST(test_pop_back_2);
    CPPUNIT_TEST(test_pop_back_3);
    
    CPPUNIT_TEST(test_pop_front_1);
    CPPUNIT_TEST(test_pop_front_2);
    CPPUNIT_TEST(test_pop_front_3);
    
    CPPUNIT_TEST(test_push_back_1);
    CPPUNIT_TEST(test_push_back_2);
    CPPUNIT_TEST(test_push_back_3);
    
    CPPUNIT_TEST(test_push_front_1);
    CPPUNIT_TEST(test_push_front_2);
    CPPUNIT_TEST(test_push_front_3);
    
    CPPUNIT_TEST(test_resize_1);
    CPPUNIT_TEST(test_resize_2);
    CPPUNIT_TEST(test_resize_3);
    
    CPPUNIT_TEST(test_size_1);
    CPPUNIT_TEST(test_size_2);
    CPPUNIT_TEST(test_size_3);
    
    CPPUNIT_TEST(test_front_1);
    CPPUNIT_TEST(test_front_2);
    CPPUNIT_TEST(test_front_3);
    
    CPPUNIT_TEST(test_swap_1);
    CPPUNIT_TEST(test_swap_2);
    CPPUNIT_TEST(test_swap_3);
    
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);        // turn off synchronization with C I/O
    cout << "TestDeque.c++" << endl << endl;
    
    CppUnit::TextTestRunner tr;
    tr.addTest(TestDeque< MyDeque<int> >::suite());
    tr.addTest(TestDeque<   deque<int> >::suite());
    tr.run();
    
    cout << "Done." << endl;
    return 0;}