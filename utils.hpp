#ifndef UTILS_HPP
#define UTILS_HPP


	/*-----------------
		ITERATOR_TRAITS	
	------------------*/

template< class Iter >
struct iterator_traits
{
	difference_type	Iter::difference_type;
	value_type	Iter::value_type;
	pointer	Iter::pointer;
	reference	Iter::reference;
	iterator_category	Iter::iterator_category;

}
template< class T >
struct iterator_traits<T*>
{
	difference_type	std::ptrdiff_t
	value_type	T
	pointer	T*
	reference	T&
	iterator_category	std::random_access_iterator_tag
}

template< class T >
struct iterator_traits<const T*>
{
	difference_type	std::ptrdiff_t;
	value_type	T;
	pointer	const T*;
	reference	const T&;
	iterator_category	std::random_access_iterator_tag;
}

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
template<typename> struct is_integral_base: std::false_type {};
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
#endif