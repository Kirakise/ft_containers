#pragma once


namespace ft{
	template< class T1, class T2> 
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;
		pair() {}
		pair( const T1& x, const T2& y ) : first(x), second(y) {}
		template< class U1, class U2 >
		pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {}
		pair& operator=( const pair& other )
		{
			this->first = other.first;
			this->second = other.second;
			return *this;
		}
		T1 first;
		T2 second;
	};

	template< class T1, class T2 >
	ft::pair<T1,T2> make_pair( T1 t, T2 u )
	{
		ft::pair<T1, T2> a(t, u);
		return a;
	}

	template< class T1, class T2 >
	bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		if (lhs.first == rhs.first && rhs.second == lhs.second)
			return true;
		return false;
	}

	template< class T1, class T2 >
	bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class T1, class T2 >
	bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		if (lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second))
			return true;
		return false;
	}

	template< class T1, class T2 >
	bool operator<=( const ft::pair<T1,T2>& lhs,
                          const ft::pair<T1,T2>& rhs )
	{
		return (lhs == rhs || lhs < rhs);
	}
	template< class T1, class T2 >
	bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return !(lhs <= rhs);
	}

	template< class T1, class T2 >
	bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return !(lhs < rhs);
	}
}
