/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator_bst.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:35:19 by jcueille          #+#    #+#             */
/*   Updated: 2021/12/22 14:40:37 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_BST_HPP
# define ITERATOR_BST_HPP

namespace ft {

template <typename T, typename node_type>
class bstIte {
	protected:
		node_type						*_node;
		bstIte(node_type *src);

	public:
		typedef T						value_type;
		typedef ptrdiff_t				difference_type;
		typedef value_type&				reference;
		typedef value_type*				pointer;

		bstIte(void);
		bstIte(const bstIte &src);
		virtual ~bstIte(void);
		bstIte	&operator=(bstIte const &rhs);

		template <class U> bool	operator==(const bstIte<U, node_type> &rhs) const;
		template <class U> bool	operator!=(const bstIte<U, node_type> &rhs) const;

		bstIte		&operator++(void);
		bstIte		operator++(int);
		bstIte		&operator--(void);
		bstIte		operator--(int);

		reference	operator*(void) const;
		pointer		operator->(void) const;

		operator bstIte<const T, node_type>(void) const {
			return bstIte<const T, node_type>(this->_node);
		}

		template <class, class, class, class>
		friend class map;

		template <class, class>
		friend class bstIte;

}; // ****************************************************** class bstIte end //

template <typename T, typename node_type>
bstIte<T, node_type>::bstIte(void) : _node(NULL) { return ; }

template <typename T, typename node_type>
bstIte<T, node_type>::bstIte(node_type *src) { this->_node = src; }

template <typename T, typename node_type>
bstIte<T, node_type>::bstIte(const bstIte &src) { *this = src; }

template <typename T, typename node_type>
bstIte<T, node_type>::~bstIte(void) { return ; }

template <typename T, typename node_type>
bstIte<T, node_type> &bstIte<T, node_type>::operator=(const bstIte &rhs) {
	if (this == &rhs)
		return (*this);
	this->_node = rhs._node;
	return (*this);
}

template <typename T, typename node_type> template <class U>
bool	bstIte<T, node_type>::operator==(const bstIte<U, node_type> &rhs) const {
	return (this->_node == rhs._node);
}

template <typename T, typename node_type> template <class U>
bool	bstIte<T, node_type>::operator!=(const bstIte<U, node_type> &rhs) const {
	return (this->_node != rhs._node);
}

template <typename T, typename node_type>
bstIte<T, node_type> &bstIte<T, node_type>::operator++(void) {
	if (this->_node->right != NULL)
		this->_node = farLeft(this->_node->right);
	else
	{
		node_type	*child = this->_node;

		this->_node = this->_node->parent;
		while (this->_node && child == this->_node->right)
		{
			child = this->_node;
			this->_node = this->_node->parent;
		}
	}
	return (*this);
}

template <typename T, typename node_type>
bstIte<T, node_type> bstIte<T, node_type>::operator++(int) {
	bstIte	tmp(*this);
	++(*this);
	return (tmp);
}

template <typename T, typename node_type>
bstIte<T, node_type>& bstIte<T, node_type>::operator--(void) {
	if (this->_node->left != NULL)
		this->_node = farRight(this->_node->left);
	else
	{
		node_type	*child = this->_node;

		this->_node = this->_node->parent;
		while (this->_node && child == this->_node->left)
		{
			child = this->_node;
			this->_node = this->_node->parent;
		}
	}
	return (*this);
}

template <typename T, typename node_type>
bstIte<T, node_type> bstIte<T, node_type>::operator--(int) {
	bstIte	tmp(*this);
	--(*this);
	return (tmp);
}

template <typename T, typename node_type>
typename bstIte<T, node_type>::reference bstIte<T, node_type>::operator*(void) const {
	return (this->_node->data);
}

template <typename T, typename node_type>
typename bstIte<T, node_type>::pointer bstIte<T, node_type>::operator->(void) const {
	return &this->operator*();
}

} // ******************************************************* ft namespace end //

#endif // ********************************************* ITERATOR_BST_HPP end //