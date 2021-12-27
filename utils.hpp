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
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type  value_type;
		typedef typename Iter::pointer  pointer;
		typedef typename Iter::reference reference;
		typedef typename Iter::iterator_category iterator_category;

	};
	template< class T >
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template< class T >
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag	iterator_category;
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
	template < class T1, class T2 >
	struct pair {
	/* member functions */
	
		typedef T1	first_type;
		typedef T2	second_type;

	/* member variables */
	
		first_type	first;
		second_type second;

	/* member functions */
	
	/* constructor / destructor / operator= */
		
		/**
		 * @brief constructor: default
		 * @note constructs a pair object with its elements value-initialized
		 */
		pair(void) :
			first(),
			second() {}
		
		/**
		 * @brief constructor: copy
		 * @note the object is iniialized with the contents of the pr pair object.
		 * the corresponding member of pr is passed to the constructor of each of its members.
		 * 
		 * @param pr: another pair object.
		 */
		template< class U, class V >
		pair(const pair<U, V> & pr) :
			first(pr.first),
			second(pr.second) {}
		
		/**
		 * @brief constructor: initialization
		 * @note member first is constructed with a and member second with b.
		 * 
		 * @param a: an object of the type of first, of some other type implicitly convertible to it.
		 * @param b: an object of the type of second, of some other type implicitly convertible to it.
		 */
		pair(const first_type & a, const second_type & b) :
			first(a),
			second(b) {}

		/**
		 * @brief assign contents
		 * @note assigns pr as the new content for the pair object.
		 * 
		 * @param pr: another par object.
		 * @return *this
		 */
		// implicitly declared:
		pair& operator= (const pair & pr) {
			if (this == &pr) return *this;

			first = pr.first;
			second = pr.second;
			return *this;
		}
	};
	
	/* non-member function: pair */

	/**
	 * @brief relational operators for pair
	 * @note performs the appropriate comparison operation between the pair objects lhs and rhs.
	 * 
	 * @param lhs, rhs: pair object, having both the same template parameters (T1 and T2).
	 */
	template < class T1, class T2 >
	bool operator== (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template < class T1, class T2 >
	bool operator!= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(lhs == rhs);
	}

	template < class T1, class T2 >
	bool operator<  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template < class T1, class T2 >
	bool operator<= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(rhs < lhs);
	}

	template < class T1, class T2 >
	bool operator>  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return rhs < lhs;
	}

	template < class T1, class T2 >
	bool operator>= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(lhs < rhs);
	}


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