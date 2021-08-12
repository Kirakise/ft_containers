#pragma once
#include "iterator.hpp"
#include "utils.hpp"
#include <cstddef>
#include <cstdio>
#include <algorithm>
#include <memory>
#include <iterator>
#include <cstring>
#include <exception>



namespace ft{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			template <class T1>
			class vec_iter : ft::iterator<ft::random_access_iterator_tag, T1>
			{
				typedef typename  ft::iterator <
					ft::random_access_iterator_tag,
					T1 > It;
				typedef  typename It::size_type size_type;
				typedef typename It::difference_type difference_type;
				typedef typename It::pointer pointer;
				typedef typename It::reference reference;
				typedef typename It::value_type value_type;
				typedef typename It::const_reference const_reference;
				T1 *ptr;
				public:
				vec_iter() : ptr(nullptr) {}
				vec_iter(pointer p) : ptr(p) {}
				vec_iter(vec_iter const &other) : ptr(other.ptr) {}
				~vec_iter(){}
				vec_iter &operator=(vec_iter const &other){ this->ptr = other.ptr; return *this; }
				virtual vec_iter &operator++() { this->ptr++; return *this; }
				virtual vec_iter operator++(int) { 
					vec_iter tmp(*this);
					this->ptr++;
					return tmp;
				}
				T1 *getptr() {return this->ptr; }
				virtual vec_iter &operator--() { this->ptr--; return *this; }
				virtual vec_iter operator--(int) {
					vec_iter tmp(*this);
					this->ptr--;
					return tmp;
				}
				pointer &operator->(){ return *this; }
				reference operator*(){ return *(this->ptr); }
				const_reference operator*() const { return *(this->ptr); }
				virtual vec_iter operator+(size_type t) { return this->ptr + t; }
				virtual vec_iter operator-(size_type t) { return this->ptr - t; }
				virtual difference_type  operator-(vec_iter const &other) const 
				{ return this->ptr - other.ptr; }
				reference operator[](size_type i) { return *(this->ptr[i]); }
				const_reference operator[](size_type i) const { return *(this->ptr[i]);}
				bool operator< (vec_iter const &other) const { return this->ptr < other.ptr; }
				bool operator> (vec_iter const &other) const { return this->ptr > other.ptr; }
				bool operator== (vec_iter const &other) const { return this->ptr == other.ptr; }
				bool operator!= (vec_iter const &other) const { return this->ptr != other.ptr; }
				bool operator<= (vec_iter const &other) const { return this->ptr <= other.ptr; }
				bool operator>= (vec_iter const &other) const { return this->ptr >= other.ptr; }
			};


			template <class T1>
			class rev_vec_iter : public vec_iter<T1>
			{
				typedef typename  ft::iterator <
					ft::random_access_iterator_tag,
					T1 > It;
				typedef  typename It::size_type size_type;
				typedef typename It::difference_type difference_type;
				typedef typename It::pointer pointer;
				typedef typename It::reference reference;
				typedef typename It::value_type value_type;
				typedef typename It::const_reference const_reference;
				rev_vec_iter &operator--() { this->ptr++; return *this; }
				rev_vec_iter operator--(int) { 
					rev_vec_iter tmp(*this);
					this->ptr++;
					return tmp;
				}
				rev_vec_iter &operator++() { this->ptr--; return *this; }
				rev_vec_iter operator++(int) {
					rev_vec_iter tmp(*this);
					this->ptr--;
					return tmp;
				}
				rev_vec_iter operator+(size_type t) { return this->ptr - t; }
				rev_vec_iter operator-(size_type t) { return this->ptr + t; }
				difference_type  operator-(rev_vec_iter const &other) const 
				{ return other.ptr - this->ptr; }

			};


			typedef T value_type;
			typedef Allocator allocator_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef vec_iter<T> iterator;
			typedef vec_iter<T> const_iterator;
			typedef rev_vec_iter<T> reverse_iterator;
			typedef rev_vec_iter<T> const_reverse_iterator;
			
			vector( const Allocator& alloc = allocator_type()) 
				: first(), last(), cap(), alloc(alloc) {
				this->container = this->alloc.allocate(0);
				this->first = this->container;
				this->last = this->first;
				this->cap = this->container;
				}
			vector( size_type count, const T &value = T(), 
				const Allocator &alloc = allocator_type())
				: first(), last(), cap(), alloc(alloc) {
					this->container = this->alloc.allocate(count);
					this->first = this->container;
					this->last = this->first + count;
					this->cap = this->last;
					for (size_type i = 0; i < count; i++)	
						this->alloc.construct(this->container + i, value);
				}
			template < class InputIt >
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(), 
			typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr )
			: first(), last(), alloc(alloc)
			{
				size_type t = last - first;
				this->container = this->alloc.allocate(t);
				this->first = this->container;
				this->last = this->first;
				this->cap = this->first + t;
				if (last - first)
					this->insert(this->end(), first, last);
			}

			vector( const vector& other ) : first(), last(), alloc(Allocator())
			{
				iterator st = other.begin();
				iterator bt = other.end();
				this->container = this->alloc.allocate(other.end() - other.begin());
				this->first = this->container;
				this->cap = this->first + (other.end() - other.begin());
				this->last = this->first;
				if (other.size())
					this->insert(this->begin(), st, bt);	
			}

			~vector(){
				alloc.deallocate(this->container, this->size());
			}
			vector &operator=(vector const &other) //same???
			{
				if (this == &other)
					return *this;
				if (this->capacity() < other.size() + 1)
					this->reserve(other.size());
				this->clear();
				iterator i2 = other.begin();
				while (i2 != other.end())
					*(this->last++) = *i2++;
				return *this;
			}
			void assign( size_type count, const T& value )
			{
				if (this->capacity() < count + 1)
					this->reserve(count);
				this->clear();
				while(count--)
					*(this->last++) = value;
			}
			template< class InputIt>
			void assign( InputIt first, InputIt last, 
			typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr )
			{
				size_type i = last - first;
				if (this->capacity() < i + 1)
					this->reserve(i);
				this->clear();
				while (first != last)
					*(this->last++) = *first++;
			}

			allocator_type get_allocator() const { return this->alloc; }
			
			reference at( size_type pos ) { return (*this)[pos]; }

			const_reference at( size_type pos ) const { return *(this)[pos]; }

			reference operator[]( size_type pos )
			{
				if (pos > this->size())
					throw OutOfRangeExp();
				return *(this->first + pos);
			}

			const_reference operator[]( size_type pos ) const
			{
				if (pos > this->size())
					throw OutOfRangeExp();
				return *(this->begin() + pos);
			}

			reference front() { return (*this)[0]; }
			const_reference front() const { return (*this)[0]; }
			reference back() { return *(this->end() - 1); }
			const_reference back() const { return *(this->end() - 1); }
			T* data() { return this->first.getptr(); }
			const T* data() const { return this->first.ptr; }
			iterator begin() { return this->first; }
			const_iterator begin() const { return this->first; }
			iterator end() { return this->last; }
			const_iterator end() const { return this->last; }
			reverse_iterator rbegin() { return this->last; }
			const_reverse_iterator rbegin() const { return this->last; }
			reverse_iterator rend() {return this->first; }
			const_reverse_iterator rend() const { return this->first; }

			bool empty() const { return this->first == this->last; }

			size_type size() const { return this->end() - this->begin(); }

			size_type max_size() const { return this->alloc.max_size(); }

			void reserve( size_type new_cap )
			{
				if (this->capacity() >= new_cap)
					return ;
				size_type tmp = this->size();
				vector <T> tmp2(tmp);
				tmp2 = *this;
				this->~vector();
				this->container = this->alloc.allocate(new_cap);
				this->first = this->container;
				this->last = this->first + tmp;
				this->cap = this->first + new_cap;
				this->operator=(tmp2);
			}

			size_type capacity() const { return this->cap - this->first; }

			void clear(){
				for (size_type i = 0; i < this->size(); i++)
					this->alloc.destroy(this->container + i);
				this->last = this->container;
			}
			
			iterator insert( iterator pos, const T& value )
			{
				size_type tmp = pos - first;
				if (this->capacity() < this->size() + 1)
					this->reserve(this->capacity()  ? this->capacity() * 2 : 1);
				iterator it = this->end();
				while (it != this->begin() + tmp)
				{
					*(it) = *(it - 1);
					it--;
				}
				*(this->begin() + tmp) = value;
				this->last++;
				return it;
			}

			void insert( iterator pos, size_type count, const T& value )
			{
				size_type tmp = pos - this->first;
				if (this->capacity() - this->size() < count + 1)
				{
					this->reserve(this->capacity() ? this->capacity() * 2 : count);
					this->insert(this->begin() + tmp, count, value);
					return ;
				}
				while (count--)
					this->insert(pos, value);
			}

			template< class InputIt>
			void insert( iterator pos, InputIt first, InputIt last,
				typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr)
			{
				size_type tmp = pos - this->begin();
				if (this->capacity() - this->size() < 
						(long unsigned int)(last - first + 1))
				{
					this->reserve(this->capacity() ? this->capacity() * 2 : last - first);
					this->insert(this->begin() + tmp, first, last);
					return ;
				}	
				while (first != last)
				{
					this->insert(pos++, *first);
					++first;
				}
			}
			
			iterator erase( iterator pos )
			{
				if (pos < this->begin() || pos > this->end())
					throw OutOfRangeExp();
				iterator it = pos;
				while (it < this->end())
				{
					*it = *(it + 1);
					it++;
				}
				this->last--;
				return pos;
			}

			iterator erase( iterator first, iterator last )
			{
				size_type tmp = last -first;
				if (this->begin() > first || this->end() < first)
					throw OutOfRangeExp();
				while (tmp--)
					this->erase(first);
				return first;
			}
			
			void push_back( const T& value )
			{
				this->insert(this->end(),value);
			}

			void pop_back()
			{
				this->erase(this->end() - 1);
			}
				
			void resize( size_type count, T value = T() )
			{
				if (count == this->size())
					return ;
				else if (count < this->size())
					this->erase(this->begin() + count, this->end());
				else
					while (this->size() < count)
						this->push_back(value);
			}

			void swap( vector& other )
			{
				if (this == &other)
					return ;
				if (this->capacity() < other.size() + 1)
					this->reserve(other.size());
				if (other.capacity() < this->size() + 1)
					other.reserve(this->size());
				iterator it1 = this->begin();
				iterator it2 = other.begin();
				value_type tmp;
				size_type s1 = this->size(), s2= other.size();
				while (it1 < this->end() || it2 < other.end())
				{
					tmp = *it1;
					*it1 = *it2;
					*it2 = tmp;
					it1++;
					it2++;
				}
				if (it1 < this->end())
					this->erase(it1, this->end());
				if (it2 < other.end())
					other.erase(it2, other.end());
				this->last = this->begin() + s2;
				other.last = other.begin() + s1;
			}

			struct OutOfRangeExp : public std::exception{
				using std::exception::what;
				const char * what() throw() { return "Vector out of range!"; }
			};	
		private:
			pointer container;
			iterator first;
			iterator last;
			iterator cap;
			allocator_type alloc;
	};

	template< class T, class Alloc >
	bool operator==( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false;
		typename ft::vector<T>::iterator it = rhs.begin();
		typename ft::vector<T>::iterator bt = lhs.begin();

		while (it != rhs.end())
		{
			if (*it++ != *bt++)
				return false;
		}
		return true;
	}

	template< class T, class Alloc >
	bool operator!=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class T, class Alloc >
	bool operator<( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class T, class Alloc >
	bool operator<=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
	{
		return (lhs == rhs) || (lhs < rhs) ;
	}

	template< class T, class Alloc >
	bool operator>( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )
	{
		return !(lhs <= rhs);
	}

	template< class T, class Alloc >
	bool operator>=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
	{
		return !(lhs < rhs);
	}



	template< class T, class Alloc >
	void swap( ft::vector<T,Alloc>& lhs,
           ft::vector<T,Alloc>& rhs )
	{
		lhs.swap(rhs);
	}
}
