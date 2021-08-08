#pragma once
#include "vector.hpp"

namespace ft{

	template<class T, class Container = ft::vector<T> > 
	class stack
	{
		public:
		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference cont_reference;

		explicit stack( const Container& cont = Container() ) : ct(cont) {}
		stack( const stack& other ) : ct(other.ct) {}

		~stack() {}

		stack& operator=( const stack& other )
		{
			this->ct = other.ct;
			return *this;
		}

		reference top()
		{
			return *(this->ct.end() - 1);
		}

		bool empty() const { return this->ct.empty(); }

		size_type size() const { return this->ct.size(); }

		void push( const value_type& value ) { this->ct.push_back(value); }

		void pop() { this->ct.pop_back(); }

		private:
		container_type ct;
	};
}
