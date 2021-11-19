#ifndef STACK_HPP
# define STACK_HPP
#include "Vector_template.hpp"

namespace ft {
	template < class T, class Container = ft::vector<T> >
	class stack {
		public:
		typedef T 			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;
		
		explicit stack( const Container& cont = Container() ) : c(cont)	{}

		~stack(){};
		stack& operator=( const stack& other ) { this->c = other.c; }
		bool empty(void) const { return c.empty(); }
		size_type size(void) const { return c.size(); }
		value_type& top(void) { return c.back(); }
		const value_type& top(void) const { return c.back(); }
		void push (const value_type& val) { c.push_back(val); }
		void pop(void) { c.pop_back(); }


		friend bool operator== (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c == rhs.c; }
		friend bool operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c != rhs.c; }
		friend bool operator<  (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c < rhs.c; }
		friend bool operator<= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c <= rhs.c; }
		friend bool operator>  (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c > rhs.c; }
		friend bool operator>= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c >= rhs.c; }
		
		protected:
			container_type c;
	};
}//end ft
#endif