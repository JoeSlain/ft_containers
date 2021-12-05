#ifndef UTILS_HPP
#define UTILS_HPP

#include <type_traits>
	/*-----------------
		ITERATOR_TRAITS	
	------------------*/
namespace ft{
	template< class Iter >
	struct iterator_traits
	{
		difference_type	Iter::difference_type;
		value_type	Iter::value_type;
		pointer	Iter::pointer;
		reference	Iter::reference;
		iterator_category	Iter::iterator_category;

	};
	template< class T >
	struct iterator_traits<T*>
	{
		difference_type	std::ptrdiff_t
		value_type	T
		pointer	T*
		reference	T&
		iterator_category	std::random_access_iterator_tag
	};

	template< class T >
	struct iterator_traits<const T*>
	{
		difference_type	std::ptrdiff_t;
		value_type	T;
		pointer	const T*;
		reference	const T&;
		iterator_category	std::random_access_iterator_tag;
	};

		/*---------------
			ENABLE_IF
		----------------*/

	template < bool Cond, class T = void >
	struct enable_if {};

	template < class T >
	struct enable_if<true, T> { typedef T type; };

		/*---------------
			IS_INTEGRAL
		----------------*/
	template<typename> struct is_integral: std::false_type {};
	template <>			 struct is_integral<bool> : public std::true_type {};
	template <>			 struct is_integral<char> : public std::true_type {};
	template <>			 struct is_integral<char16_t> : public std::true_type {};
	template <>			 struct is_integral<char32_t> : public std::true_type {};
	template <>			 struct is_integral<wchar_t> : public std::true_type {};
	template <>			 struct is_integral<signed char> : public std::true_type {};
	template <>			 struct is_integral<short int> : public std::true_type {};
	template <>			 struct is_integral<int> : public std::true_type {};
	template <>			 struct is_integral<long int> : public std::true_type {};
	template <>			 struct is_integral<long long int> : public std::true_type {};
	template <>			 struct is_integral<unsigned char> : public std::true_type {};
	template <>			 struct is_integral<unsigned short int> : public std::true_type {};
	template <>			 struct is_integral<unsigned int> : public std::true_type {};
	template <>			 struct is_integral<unsigned long int> : public std::true_type {};
	template <>			 struct is_integral<unsigned long long int> : public std::true_type {};

		/*---------------
			EQUAL COMPARE
		----------------*/
	template< class InputIt1, class InputIt2 >
	bool equal( InputIt1 first1, InputIt1 last1,
				InputIt2 first2 )
	{
		for (; first1 != last1; ++first1, ++first2) {
			if (!(*first1 == *first2)) {
				return false;
			}
		}
		return true;
	}

	template< class InputIt1, class InputIt2, class BinaryPredicate >
	bool equal( InputIt1 first1, InputIt1 last1,
				InputIt2 first2, BinaryPredicate p )
	{
		for (; first1 != last1; ++first1, ++first2) {
			if (!p(*first1, *first2)) {
				return false;
			}
		}
		return true;
	}

		/*---------------
			LEXICO COMPARE
		----------------*/
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

	template< class InputIt1, class InputIt2, class Compare >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2,
								Compare comp )
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (comp(*first1, *first2)) return true;
			if (comp(*first2, *first1)) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

		/*-----------
			PAIR
		------------*/
	template< class T1, class T2 >
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair(void) : first(), second() {}
		pair( const T1& x, const T2& y ) : first(x), second(y) {}
		template< class U1, class U2 >
		pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {};

		pair& operator=( const pair& other )
		{
			this->first = other.first;
			this->second = other.second;
			return *this;
		}

		template< class T1, class T2 >
		bool operator==( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
		{
			return (lhs.first == rhs.firsst && lhs.second == rhs.second);
		}
		template< class T1, class T2 >
		bool operator!=( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
		{
			return (lhs.first != rhs.first || lhs.second != rhs.second);
		}
		template< class T1, class T2 >
		bool operator<( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
		{
			if (lhs.first<rhs.first)
				return true;
			if (rhs.first<lhs.first)
				return false; 
			if (lhs.second<rhs.second)
				return true; 
			return false;
		}

		template< class T1, class T2 >
		bool operator<=( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
		{
			return (!(rhs < lhs));
		}

		template< class T1, class T2 >
		bool operator>( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
		{
			return (rhs < lhs);
		}
		template< class T1, class T2 >
		bool operator>=( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
		{
			return (!(lhs < rhs));
		}
	};

	template< class T1, class T2 >
	pair<T1,T2> make_pair( T1 t, T2 u )
	{
		return (pair<T1, T2>(t, u));
	}

	struct nullptr_t
	{
		template <typename T>
		operator T*() { return static_cast<T*>(0); }
	};
}//end namespace
#endif