#pragma once
#include <type_traits>
namespace ft{
	template<typename> struct is_integral_base: public std::false_type {};
	template<> struct is_integral_base<bool>: public std::true_type {};
	template<> struct is_integral_base<char>: public std::true_type {};
	template<> struct is_integral_base<char16_t>: public std::true_type {};
	template<> struct is_integral_base<char32_t>: public std::true_type {};
	template<> struct is_integral_base<wchar_t>: public std::true_type {};
	template<> struct is_integral_base<signed char>: public std::true_type {};
	template<> struct is_integral_base<short int>: public std::true_type {};
	template<> struct is_integral_base<int>: public std::true_type {};
	template<> struct is_integral_base<long int>: public std::true_type {};
	template<> struct is_integral_base<unsigned char>: public std::true_type {};
	template<> struct is_integral_base<unsigned short int>: public std::true_type {};
	template<> struct is_integral_base<unsigned int>: public std::true_type {};
	template<> struct is_integral_base<unsigned long int>: public std::true_type {};
	template<typename T> struct is_integral: public is_integral_base<T> {};

	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template< class InputIt1, class InputIt2 >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
             InputIt2 first2, InputIt2 last2 )
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}
}
