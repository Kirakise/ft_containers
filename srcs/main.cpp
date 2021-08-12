#include "pair.hpp"
#include <ctime>
#include "vector.hpp"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>
#include "map.hpp"
#include "stack.hpp"
template <class T>
void prinvec(ft::vector <T> &tmp)
{
	std::cout << "vector size: " << tmp.size() << std::endl;
	std::cout << "vector cap: " << tmp.capacity() << std::endl;
	for (long unsigned int i = 0; i < tmp.size(); i++)
	{
		std::cout << tmp[i] << " ";
	}
	std::cout << std::endl << std::endl;
}

template <class K, class T>
void printmap(ft::map<K, T> &tmp)
{
	std::cout << "map size: " << tmp.size() << std::endl;
	std::cout << "map contains: " << std::endl;
	typename ft::map<K, T>::iterator it = tmp.begin();
	while (it != tmp.end())
	{
		std::cout << (*it).first << ":" << (*it).second << "\t";
		it++;
	}
	std::cout << std::endl << std::endl;
}

void vector_test()
{
	ft::vector <int> d;
	ft::vector <int> d1(10, 2);
	ft::vector <int> d2(d1);
	d2[0] = 1;
	d2[3] = 4;
	ft::vector <int> d3(d2.begin(), d2.end());
	d3[1] = 7;
	d3[6] = 8;	
	std::cout << "--------------Operator =--------------" << std::endl;
	std::cout << "\t Original vector " << std::endl;
	prinvec(d3);
	std::cout << "\t New vector " << std::endl;
	ft::vector <int> d4 = d3;
	prinvec(d4);
	std::cout << "--------------Assign:--------------" << std::endl;
	d.assign(12, 24);
	prinvec(d);
	d.assign(d1.begin(), d1.end());
	prinvec(d);
	std::cout << "At" << std::endl;
	std::cout << d3.at(1) << std::endl;
	std::cout << "Operator []" << std::endl;
	prinvec(d3);
	std::cout << "--------------Front--------------" << std::endl;
	std::cout << d3.front() << std::endl;
	std::cout << "--------------Back--------------" << std::endl;
	std::cout << d3.back() << std::endl;
	std::cout << "--------------Push_back--------------" << std::endl;
	std::cout << "\t" << "Before:" << std::endl;
	prinvec(d3);
	d3.push_back(12);
	std::cout << "\tAfter:" << std::endl;
	prinvec(d3);
	std::cout << "--------------Empty--------------" << std::endl;
	std::cout << "\twith non-empty vector:" << std::endl;
	std::cout << d3.empty() << std::endl;
	d3.clear();
	std::cout << "\tWith empty vector" << std::endl;
	std::cout << d3.empty() << std::endl;
	std::cout << "Max Size" << std::endl;
	std::cout << d3.max_size() << std::endl;
	std::cout << "--------------Reserve--------------" << std::endl;
	std::cout << "\tCurrent cap: " << d3.capacity() << std::endl;
	std::cout << "\tReserve less than cap: ";
	d3.reserve(d3.capacity() - 1);
	std::cout << d3.capacity() << std::endl;
	std::cout << "\tNow 1 more than cap: ";
	d3.reserve(d3.capacity() + 1);
	std::cout << d3.capacity() << std::endl;
	std::cout << "Clear!" << std::endl << "\tBefore:" << std::endl;
	prinvec(d2);
	std::cout << "\tAfter:" << std::endl;
	d2.clear();
	prinvec(d2);
	std::cout << "--------------insert--------------" << std::endl;
	std::cout << "\tOriginal vector" << std::endl;
	prinvec(d2);
	std::cout << "\tAdd one element to the middle" << std::endl;
	d2.insert(d2.begin() + d2.size() / 2, 99);
	prinvec(d2);
	std::cout << "\tAdd 3 elements to the beginning of the vector" << std::endl;
	d2.insert(d2.begin(), 3, 76);
	prinvec(d2);
	std::cout << "\tAdd 3 last elements from the other vector to the end of this one" << std::endl;
	std::cout << "\tVector to import from:" << std::endl;
	prinvec(d1);
	std::cout << "\tResult:" << std::endl;
	d2.insert(d2.end(), d1.end() - 4, d1.end() - 1);
	prinvec(d2);
	std::cout << "--------------Erase--------------" << std::endl;
	std::cout << "\tOriginal vector" << std::endl;
	prinvec(d2);
	std::cout << "\tdelete one element from the beginning" << std::endl;
	d2.erase(d2.begin());
	prinvec(d2);
	std::cout << "\tdelete three elements in the middle" << std::endl;
	d2.erase(d2.begin() + d2.size()/2 - 1, d2.begin() + d2.size()/2 + 1);
	prinvec(d2);
	std::cout << "--------------push_back--------------" << std::endl;
	std::cout << "\tOriginal vector" << std::endl;
	prinvec(d2);
	std::cout << "\tpush_back(12)" << std::endl;
	d2.push_back(12);
	prinvec(d2);
	std::cout << "--------------pop_back--------------" << std::endl;
	std::cout << "\tOriginal vector" << std::endl;
	prinvec(d2);
	std::cout << "\tpop_back()" << std::endl;
	d2.pop_back();
	prinvec(d2);
	std::cout << "--------------resize--------------" << std::endl;
	std::cout << "\tOriginal vector" << std::endl;
	prinvec(d2);
	std::cout << "Resize > this->size()" << std::endl;
	d2.resize(d2.size() + 4, 36);
	prinvec(d2);
	std::cout << "Resize < this->size()" << std::endl;
	d2.resize(d2.size() - 4);
	prinvec(d2);
	std::cout << "--------------swap--------------" << std::endl;
	std::cout << "\tvector 1" << std::endl;
	prinvec(d2);
	std::cout << "\tvector 2" << std::endl;
	prinvec(d);
	d2.swap(d);
	std::cout << "\t new vector 1" << std::endl;
	prinvec(d2);
	std::cout << "\t new vector 2" << std::endl;
	prinvec(d);
	std::cout << "--------------Compare operators--------------" << std::endl;
	std::cout << "\tvector 1" << std::endl;
	prinvec(d2);
	std::cout << "\tvector 2" << std::endl;
	prinvec(d);
	std::cout << "\tvec1 == vec2" << std::endl;
	std::cout << (d2 == d) << std::endl;
	std::cout << "\tvec1 != vec2" << std::endl;
	std::cout << (d2 != d) << std::endl;
	std::cout << "\tvec1 < vec2" << std::endl;
	std::cout << (d2 < d) << std::endl;
	std::cout << "\tvec1 <= vec2" << std::endl;
	std::cout << (d2 <= d) << std::endl;
	std::cout << "\tvec1 > vec2" << std::endl;
	std::cout << (d2 > d) << std::endl;
	std::cout << "\tvec1 >= vec2" << std::endl;
	std::cout << (d2 >= d) << std::endl;
	std::cout << "--------------Non-member swap--------------" << std::endl;
	std::cout << "\tvector 1" << std::endl;
	prinvec(d2);
	std::cout << "\tvector 2" << std::endl;
	prinvec(d);
	ft::swap(d, d2);
	std::cout << "\t new vector 1" << std::endl;
	prinvec(d2);
	std::cout << "\t new vector 2" << std::endl;
	prinvec(d);
	ft::vector <int> d5;
	d5.resize(10000);
	for (int i = 0; i < 10000; i++)
		d5.push_back(i);
}


void map_test(){

	std::cout << "--------------Map--------------" << std::endl;
	std::cout << "--------------Constructors--------------" << std::endl;
	ft::map<int, int> m1;
	m1[32] = 7;
	m1.insert(ft::make_pair(24, 2));
	m1[42] = 9;
	m1[42] = 4;
	ft::map<int, int> m2(m1.begin(), m1.end());
	ft::map<int, int> m3(m2);
	printmap(m1);
	printmap(m2);
	printmap(m3);
	std::cout << "--------------Operator=--------------" << std::endl;
	std::cout << "\tOriginal FROM" << std::endl;
	m2[3] = 9;
	m2[45] = 6;
	printmap(m2);
	std::cout << "\tOriginal TO" << std::endl;
	printmap(m3);
	m3 = m2;
	std::cout << "\tFROM hasn't been changed" << std::endl;
	printmap(m2);
	std::cout << "\tNew TO" << std::endl;
	printmap(m3);
	std::cout << "--------------At--------------" << std::endl;
	std::cout << "\tMap" << std::endl;
	printmap(m2);
	std::cout << "\tat(42)" << std::endl;
	std::cout << m2.at(42) << std::endl;
	std::cout << "\tat(34)" << std::endl;
	try{
		std::cout << m2.at(34) << std::endl;
	}
	catch (std::exception &e)
	{	
		std::cout << e.what() << std::endl;
	}
	std::cout << "--------------Operator[]--------------" << std::endl;
	std::cout << "\tMap" << std::endl;
	printmap(m2);
	std::cout << "\tmap[42]" << std::endl;
	std::cout << m2[42] << std::endl;
	std::cout << "\tmap[34]" << std::endl;
	std::cout << m2[34] << std::endl;
	std::cout << "\tNow map looks like this:" << std::endl;
	printmap(m2);
	std::cout << "--------------Empty--------------" << std::endl;
	std::cout << "\tWith empty map" << std::endl;
	ft::map<int, char> m4;
	std::cout << m4.empty() << std::endl;
	std::cout << "\tWith not empty map" << std::endl;
	std::cout << m3.empty() << std::endl;
	std::cout << "--------------Size--------------" << std::endl;
	std::cout << "\tEmpty map" << std::endl;
	std::cout << m4.size() << std::endl;
	std::cout << "\tNot empty map" << std::endl;
	std::cout << m3.size() << std::endl;
	std::cout << "--------------Max Size--------------" << std::endl;
	std::cout << m3.max_size() << std::endl;
	std::cout << "--------------Clear--------------" << std::endl;
	std::cout << "\tMap before" << std::endl;
	printmap(m2);
	m2.clear();
	std::cout << "\tMap after" << std::endl;
	printmap(m2);
	std::cout << "--------------Insert--------------" << std::endl;
	std::cout << "\tOriginal map" << std::endl;
	printmap(m2);
	std::cout << "\tInsert {35,27}" << std::endl;
	m2.insert(ft::make_pair(35, 27));
	printmap(m2);
	std::cout << "\tInsert {35,23}" << std::endl;
	m2.insert(ft::make_pair(35, 23));
	printmap(m2);
	std::cout << "\tInserting by iterators from map" << std::endl;
	printmap(m3);
	std::cout << "\tNew map" << std::endl;
	m2.insert(m3.begin(), m3.end());
	printmap(m2);
	std::cout << "--------------Erase--------------" << std::endl;
	std::cout << "\tOriginal map" << std::endl;
	printmap(m2);
	std::cout << "\tErase one element in the begining" << std::endl;
	m2.erase(m2.begin());
	printmap(m2);
	std::cout << "\tErase first half of the map" << std::endl;
	m2.erase(m2.begin(), m2.find(35));
	printmap(m2);
	std::cout << "\tErase by key 45" << std::endl;
	m2.erase(45);
	printmap(m2);
	std::cout << "\tErase by key 21" << std::endl;
	m2.erase(21);
	printmap(m2);
	std::cout << "--------------Swap--------------" << std::endl;
	std::cout << "\tOriginal map1" << std::endl;
	printmap(m2);
	std::cout << "\tOriginal map2" << std::endl;
       	printmap(m3);
	m2.swap(m3);
	std::cout << "\tNew map1" << std::endl;
	printmap(m2);
	std::cout << "\tNew map2" << std::endl;
	printmap(m3);
	std::cout << "--------------Count--------------" << std::endl;
	std::cout << "\tElement in map and element not in map" << std::endl;
	std::cout << m3.count(42) << " " << m3.count(41) << std::endl;
	std::cout << "--------------Find--------------" << std::endl;
	std::cout << "\tMap" << std::endl;
	printmap(m2);
	std::cout << "\tFind 42" << std::endl;
	std::cout << (*(m2.find(42))).first << ":" << (*(m2.find(42))).second << std::endl;
	std::cout << "--------------Lower-upper-equal--------------" << std::endl;
	std::cout << "\tOriginal map" << std::endl;
	printmap(m2);
	std::cout << "\tLower_bound 42" << std::endl;
	std::cout << (*(m2.lower_bound(42))).first << std::endl;
	std::cout << "\tUpper_bound 42" << std::endl;
	std::cout << (*(m2.upper_bound(42))).first << std::endl;
	std::cout << "--------------Compare operators--------------" << std::endl;
	std::cout << "\tMap1" << std::endl;
	printmap(m2);
	std::cout << "\tMap2" << std::endl;
	printmap(m3);
	std::cout << "\tm1 == m2" << std::endl;
	std::cout << (m2 == m3) << std::endl;
	std::cout << "\tm1 != m2" << std::endl;
	std::cout << (m2 != m3) << std::endl;
	std::cout << "\tm1 > m2" << std::endl;
	std::cout << (m2 == m3) << std::endl;
	std::cout << "\tm1 >= m2" << std::endl;
	std::cout << (m2 >= m3) << std::endl;
	std::cout << "\tm1 < m2" << std::endl;
	std::cout << (m2 < m3) << std::endl;
	std::cout << "\tm1 <= m2" << std::endl;
	std::cout << (m2 <= m3) << std::endl;
	for (int i = 0; i < 1000000; i++)
		m2[i] = i;
}

void stack_test()
{
	std::cout << "--------------Stack--------------" << std::endl;
	std::cout << "--------------Constructor--------------" << std::endl;
	ft::stack<int> d1;
	d1.push(231);
	ft::stack<int> d2(d1);
	ft::stack<int> d3;
	std::cout << "Constructors did their job" << std::endl;
	std::cout << "--------------Operator=--------------" << std::endl;
	d1.push(131);
	std::cout << "\t deck before" << std::endl;
	std::cout << d1.top() << std::endl;
	std::cout << "\t deck after" << std::endl;
	d1 = d2;
	std::cout << d1.top() << std::endl;
	std::cout << "--------------Top--------------" << std::endl;
	std::cout << "\tThe same deck as previous" << std::endl;
	std::cout << d1.top() << std::endl;
	std::cout << "--------------Empty--------------" << std::endl;
	std::cout << "With empty stack" << std::endl;
	std::cout << d3.empty() << std::endl;
	std::cout << "With non-empty stack" << std::endl;
	std::cout << d2.empty() << std::endl;
	std::cout << "--------------Size--------------" << std::endl;
	std::cout << d2.size() << std::endl;
	std::cout << "--------------Push--------------" << std::endl;
	std::cout << "\tTop element before" << std::endl;
	std::cout << d2.top() << std::endl;
	d2.push(11);
	std::cout << "\tTop element after" << std::endl;
	std::cout << d2.top() << std::endl;
	std::cout << "--------------Pop--------------" << std::endl;
	std::cout << "\tTop element before" << std::endl;
	std::cout << d2.top() << std::endl;
	d2.pop();
	std::cout << "\tTop element after" << std::endl;
	std::cout << d2.top() << std::endl;
	for (int i = 0; i < 10000000; i++)
		d2.push(i);
}

int main()
{
	std::cout << std::fixed;
	size_t t, t1, t2;
	size_t e, e1, e2;
	t = std::clock();
	vector_test();
	e = std::clock();
	t1 = std::clock();
	map_test();
	e1 = std::clock();
	t2 = std::clock();
	stack_test();
	e2 = std::clock();
	std::cout << "Working time for vector" << std::endl << (e - (double)t) / CLOCKS_PER_SEC << std::endl;
	std::cout << "Working time for map" << std::endl << (e1 - (double)t1) / CLOCKS_PER_SEC << std::endl;
	std::cout << "Working time for stack" << std::endl << (e2 - (double)t2) / CLOCKS_PER_SEC << std::endl;
}
