#pragma once
#include <type_traits>
namespace ft{
	template<typename> struct is_integral_base: std::false_type {};
	template<> struct is_integral_base<bool>: std::true_type {};
	template<> struct is_integral_base<char>: std::true_type {};
	template<> struct is_integral_base<char16_t>: std::true_type {};
	template<> struct is_integral_base<char32_t>: std::true_type {};
	template<> struct is_integral_base<wchar_t>: std::true_type {};
	template<> struct is_integral_base<signed char>: std::true_type {};
	template<> struct is_integral_base<short int>: std::true_type {};
	template<> struct is_integral_base<int>: std::true_type {};
	template<> struct is_integral_base<long int>: std::true_type {};
	template<> struct is_integral_base<long long int>: std::true_type {};
	template<> struct is_integral_base<unsigned char>: std::true_type {};
	template<> struct is_integral_base<unsigned short int>: std::true_type {};
	template<> struct is_integral_base<unsigned int>: std::true_type {};
	template<> struct is_integral_base<unsigned long int>: std::true_type {};
	template<> struct is_integral_base<unsigned long long int>: std::true_type {};
	template<typename T> struct is_integral: is_integral_base<std::remove_cv_t<T>> {};

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
