#pragma once
#include <stdexcept>
#include <functional>
#include <memory>
#include <stdexcept>
#include "iterator.hpp"
#include "pair.hpp"
#include "utils.hpp"
#include "vector.hpp"

namespace ft{
	template< class T >
	struct equal_to
	{
		bool operator()( const T& lhs, const T& rhs ) const
		{
			return lhs == rhs;
		}
	};



	template <class T>
	class map_iter : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		private:
		T **ptr;
		public:
		typedef typename ft::iterator <ft::bidirectional_iterator_tag,
			T> It;
		typedef typename It::size_type size_type;
		typedef typename It::difference_type difference_type;
		typedef typename It::pointer pointer;
		typedef T& reference;
		typedef typename It::value_type value_type;
		typedef reference const_reference;
		map_iter() : ptr(nullptr) {}
	       	map_iter(pointer p) : ptr(p) {}
		map_iter(T **ptr) : ptr(ptr) {}
		map_iter(map_iter const &other) : ptr(other.ptr) {}
		map_iter (typename ft::vector<T *>::iterator it) : ptr(it.getptr()) {}
		map_iter &operator=(map_iter const &other) { this->ptr = other.ptr; return *this; }
		map_iter &operator++() { this->ptr++; return *this; }
		map_iter operator++(int) {
			map_iter tmp(*this);
			this->ptr++;
			return tmp;
		}
		pointer getptr() {return *(this->ptr); }
		map_iter &operator--() { this->ptr--;  return *this; }
		map_iter operator--(int) { 
			map_iter tmp(*this);
			this->ptr--;
			return tmp;
		}
		pointer &operator->() {return *this; }
		reference operator*() { return **(this->ptr); }
		map_iter operator+(size_type t) { return this->ptr + t; }
		map_iter operator-(size_type t) { return this->ptr - t; }
		difference_type operator-(map_iter const &other) const
		{ return this->ptr - other.ptr; }
		bool operator< (map_iter const &other) const { return this->ptr < other.ptr; }
		bool operator> (map_iter const &other) const { return this->ptr > other.ptr; }
		bool operator==(map_iter const &other) const { return this->ptr == other.ptr; }
		bool operator!=(map_iter const &other) const { return this->ptr != other.ptr; }
		bool operator>= (map_iter const &other) const { return this->ptr >= other.ptr; }
		bool operator<= (map_iter const &other) const { return this->ptr <= other.ptr; }
	};
//unordered map in fact...
	template <class Key, class T,
    	class Compare = ft::equal_to<Key>,
	class Allocator = std::allocator< ft::pair<Key, T> >,
       	class Hash = std::hash<Key> >
    	class map{
		public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<Key, T> value_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef typename ft::map_iter<value_type> iterator;
		typedef typename ft::map_iter<value_type> const_iterator;
		typedef typename ft::map_iter<value_type>
			reverse_iterator;
		typedef typename ft::map_iter<value_type>
			const_reverse_iterator;
		
		class value_compare
		{
			public:
			value_compare( Compare c = ft::equal_to<Key>()) : c(c) {};	
			Compare c;
			bool operator()( const value_type& lhs,
			const value_type& rhs ) const
			{
				return c(lhs.first, rhs.first);
			}
		};

		
		map() : ct(1000), cmp(ct[0]) {}

		map( const Compare& comp,
              const Allocator& alloc = Allocator() ) : ct(1000, value_type(Key(), T()), alloc), cmp(ct[0]) {}

		template< class InputIt >
		map( InputIt first, InputIt last,
     		const Compare& comp = Compare(),
     		const Allocator& alloc = Allocator() ) : t(comp), ct(1000, value_type(Key(), T()), alloc), cmp(ct[0]) {
			while (first != last)
			{
				this->insert(*first);
				first++;
			}
		}

		map( const map& other ) : t(other.t), ct(1000), cmp(ct[0]){
			iterator it = other.begin();

			while (it != other.end())
			{
				this->insert(*it);
				it++;
			}	
		}

		~map() {}

		map &operator=(map const &other) {
			this->ct.clear();
			this->kt.clear();
			this->ct.resize(this->ct.capacity());
			this->cmp = this->ct[0];
			iterator it = other.begin();
			while (it != other.end())
				this->insert(*it++);
			return *this;
		}

		T &at(const Key &key) {
			if (this->ct[this->getpos(key)] != cmp)
				return this->ct[this->getpos(key)].second;
			else
				throw std::out_of_range("out_of_range");
		}
		const T& at( const Key& key ) const {
			if (this->ct[this->getpos(key)] != cmp)
				return this->ct[this->getpos(key)].second;
			else
				throw std::out_of_range("out_of_range");
		}
		T& operator[]( const Key& key ) {
			if (this->ct[this->getpos(key)] == cmp)
				this->insert(ft::make_pair(key, T()));
			return this->ct[this->getpos(key)].second;
		}
		iterator begin() {
			iterator a(this->kt.begin());
		       	return a;
		}
		const_iterator begin() const { return this->kt.begin(); }
		iterator end() {
			iterator a(this->kt.end());
			return a;
		}
		const_iterator end() const { return this->kt.end(); }
	       	reverse_iterator rbegin() { return this->kt.end(); }
		const_reverse_iterator rbegin() const { return this->kt.end(); }
		reverse_iterator rend() { return this->kt.begin(); }
		const_reverse_iterator rend() const { return this->kt.begin(); }
		bool empty() const { return this->kt.empty(); }
		size_type size() const { return this->kt.size(); }
		size_type max_size() const { return this->ct.max_size(); }
		void clear() { 
			this->kt.clear(); 
			this->ct.clear(); 
			this->ct.resize(this->ct.capacity());
			this->cmp = this->ct[0];
		}
		ft::pair<iterator, bool> insert( const value_type& value )
		{
			if (this->ct[getpos(value.first)] == cmp)
			{
				this->ct[getpos(value.first)] = value;
				this->kt.push_back(&this->ct[getpos(value.first)]);
				return ft::make_pair(this->end() - 1, true);
			}
			else if (this->ct[getpos(value.first)].first != value.first)
			{
				this->rehash();
				return this->insert(value);
			}
			else
			{
				for (size_type i = 0; i < kt.size(); i++)
				{
					if (kt[i]->first == value.first)
						return ft::make_pair(this->begin() + i, false);
				}
				return ft::make_pair(this->end(), false);
			}
		}


		template< class InputIt >
		void insert( InputIt first, InputIt last )
		{
			while (first != last)
			{
				this->insert(*first);
				first++;
			}
		}	

		void erase( iterator pos )
		{
			*pos = cmp;
			this->kt.erase(this->kt.begin() + (pos - this->begin()) );
		}

		void erase( iterator first, iterator last )
		{
			size_type tmp = last - first;
			size_type tmp2 = first - this->begin();
			while(tmp--)
				this->erase(this->begin() + tmp2);
		}
		size_type erase( const key_type& key )
		{
			if (this->ct[getpos(key)] == cmp)
				return (0);
			else
			{
				iterator it = this->begin();
				while (it < this->end())
				{
					if ((*it).first == key)
					{
						this->erase(it);
						return (1);
					}
					it++;
				}
			}
			return (0);
		}

		void swap( map& other )
		{
			ft::vector<value_type *> tmp;
			tmp = kt;
			kt.clear();
			for (size_type i = 0; i < other.size(); i++)
				kt.push_back(&ct[getpos(other.kt[i]->first)]);
			other.kt.clear();
			for (size_type i = 0; i < tmp.size(); i++)
				other.kt.push_back(&other.ct[other.getpos(tmp[i]->first)]);
			this->ct.swap(other.ct);
		}

		size_type count( const Key& key ) const
		{
			if (this->ct[getpos(key)].first == key)
				return 1;
			else
				return 0;
		}

		iterator find( const Key& key )
		{
			for (size_type i = 0; i < this->kt.size(); i++)
				if (this->kt[i]->first == key)
					return this->begin() + i;
			return this->end();
		}
		const_iterator find( const Key& key ) const
		{
			for (int i = 0; i < this->kt.size(); i++)
				if (this->kt[i]->first == key)
					return this->begin() + i;
			return this->end();
		}
		std::pair<iterator,iterator> equal_range( const Key& key )
		{
			iterator first = this->end();
			iterator second = this->end();
			iterator it = this->begin();
			while (it < this->end())
			{
				if (first != this->end() && (*it).first < key)
					first = it;
				else if (second != this->end() && (*it).first > key)
					second = it;
			}
			return ft::make_pair(first, second);
		}
		std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
		{
			const iterator first = this->end();
			const iterator second = this->end();
			const iterator it = this->begin();
			while (it < this->end())
			{
				if (first != this->end() && (*it).first < key)
					first = it;
				else if (second != this->end() && (*it).first > key)
					second = it;
			}
			return ft::make_pair(first, second);
		}

		iterator lower_bound( const Key& key )
		{
			iterator it = this->begin();
			while (it != this->end())
			{
				if ((*it).first >= key)
					return it;
				it++;
			}
			return it;
		}
		const_iterator lower_bound( const Key& key ) const
		{
			const iterator it = this->begin();
			while (it != this->end())
			{
				if ((*it).first >= key)
					return it;
				it++;
			}
			return it;
		}

		iterator upper_bound( const Key& key )
		{
			iterator it = this->begin();
			while (it != this->end())
			{
				if ((*it).first <= key)
					return it;
				it++;
			}
			return it;
		}
		const_iterator upper_bound( const Key& key ) const
		{
			const iterator it = this->begin();
			while (it != this->end())
			{
				if ((*it).first <= key)
					return it;
				it++;
			}
			return it;
		}

		key_compare key_comp() const{
			return this->Compare;
		}

		value_compare value_comp() const
		{
			return this->t;
		}
		private:
		bool isinkt(const Key &key) const {
			for (int i = 0; i < kt.size(); i++)
				if (kt[i]->first == key)
					return true;
			return false;
		}
		std::size_t getpos(const Key &key) const{
			return Hash{}(key) % this->ct.size();
		}

		void rehash()
		{
			map tmp;
			iterator it = this->begin();
			while (it != this->end())
				tmp.insert(*it);
			this->clear();
			this->ct.resize(this->ct.size() * 2);
			it = tmp.begin();
			while (it != tmp.end())
				this->insert(*it);
		}
		
		
		value_compare t;
		ft::vector<value_type> ct;
		ft::vector<value_type *> kt;
		value_type cmp;
	};

	template< class Key, class T, class Compare, class Alloc, class Hash >
	bool operator==( const ft::map<Key,T,Compare,Alloc, Hash>& lhs,
                 const ft::map<Key,T,Compare,Alloc, Hash>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false;
		typename ft::map<Key, T>::iterator it = lhs.begin();
		typename ft::map<Key, T>::iterator bt = rhs.begin();
		typename ft::map<Key, T>::value_compare t;

		while (it != lhs.end())
		{
			if (!t(*it, *bt))
				return false;
			it++;
			bt++;
		}
		return true;
	}

	template< class Key, class T, class Compare, class Alloc, class Hash >
	bool operator!=( const ft::map<Key,T,Compare,Alloc, Hash>& lhs,
                 const ft::map<Key,T,Compare,Alloc, Hash>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class Key, class T, class Compare, class Alloc, class Hash >
	bool operator<( const ft::map<Key,T,Compare,Alloc, Hash>& lhs,
                 const ft::map<Key,T,Compare,Alloc, Hash>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
				rhs.end());
	}

	template< class Key, class T, class Compare, class Alloc, class Hash >
	bool operator<=( const ft::map<Key,T,Compare,Alloc, Hash>& lhs,
                 const ft::map<Key,T,Compare,Alloc, Hash>& rhs )
	{
		return (lhs == rhs) || (lhs < rhs);
	}

	template< class Key, class T, class Compare, class Alloc, class Hash >
	bool operator>( const ft::map<Key,T,Compare,Alloc, Hash>& lhs,
                 const ft::map<Key,T,Compare,Alloc, Hash>& rhs )
	{
		return !(lhs <= rhs);
	}

	template< class Key, class T, class Compare, class Alloc, class Hash >
	bool operator>=( const ft::map<Key,T,Compare,Alloc, Hash>& lhs,
                 const ft::map<Key,T,Compare,Alloc, Hash>& rhs )
	{
		return !(lhs < rhs);
	}
	template< class Key, class T, class Compare, class Alloc, class Hash >
	void swap( const ft::map<Key,T,Compare,Alloc, Hash>& lhs,
                 const ft::map<Key,T,Compare,Alloc, Hash>& rhs )
	{
		lhs.swap(rhs);
	}


};
