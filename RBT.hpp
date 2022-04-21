/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcueille <jcueille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:58:57 by jcueille          #+#    #+#             */
/*   Updated: 2022/04/20 17:22:15 by jcueille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
# define RB_TREE_HPP
# include <sstream>
# include <iostream>
# include <string>
# include <algorithm>
# include "RandIterator.hpp"
# include "Reverse_iterator.hpp"
# include "utils.hpp"

namespace ft {

	typedef enum e_color {
		RED = false,
		BLACK = true
	} t_color;

	/*-----------
		NODE
	-----------*/
	template <typename T>
	struct rb_node {

		bool color;
		rb_node *parent;
		rb_node *left;
		rb_node *right;
		T data;

		rb_node(T data, t_color color = RED, rb_node *parent = NULL,
		rb_node *left = NULL, rb_node *right = NULL)
		: color(color), parent(parent), left(left), right(right), data(data) {
		}

		rb_node(rb_node const &node)
		: color(node.color), parent(node.parent), left(node.left), right(node.right), data(node.data) {
		}

		~rb_node(void) {
		}

		rb_node	&operator=(rb_node const &rhs) {
			if (this != &rhs) {
				this->data = rhs.data;
				this->color = rhs.color;
				this->parent = rhs.parent;
				this->left = rhs.left;
				this->right = rhs.right;
			}
			return (*this);
		}
	};

	/*-------------
		ITERATOR
	-------------*/

	template <typename T, typename Node>
	class rb_tree_iterator {

		public:
			typedef T value_type;
			typedef T * pointer;
			typedef T const * const_pointer;
			typedef T & reference;
			typedef T const & const_reference;
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef std::ptrdiff_t difference_type;
			typedef Node * node_ptr;

			node_ptr current;

		private:
			node_ptr _root;
			node_ptr _nil;

		public:
			rb_tree_iterator(void)
			: current(NULL), _root(NULL), _nil(NULL) {
			}

			rb_tree_iterator(node_ptr node, node_ptr root, node_ptr nil)
			: current(node), _root(root), _nil(nil) {
			}

			rb_tree_iterator(rb_tree_iterator const &rbtit)
			: current(rbtit.current), _root(rbtit._root), _nil(rbtit._nil) {
			}

			~rb_tree_iterator(void) {
			}

			rb_tree_iterator	&operator=(rb_tree_iterator const &rhs) {
				if (this != &rhs) {
					this->current = rhs.current;
					this->_root = rhs._root;
					this->_nil = rhs._nil;
				}
				return (*this);
			}

			operator	rb_tree_iterator<value_type const, Node>(void) const {
				return (rb_tree_iterator<value_type const, Node>(this->current, this->_root, this->_nil));
			}

			rb_tree_iterator	&operator++(void) {
				this->current = this->_next(this->current);
				return (*this);
			}

			rb_tree_iterator	operator++(int) {
				rb_tree_iterator tmp(this->current, this->_root, this->_nil);
				this->current = this->_next(this->current);
				return (tmp);
			}

			pointer	operator->(void) {
				return (&this->operator*());
			}

			const_pointer	operator->(void) const {
				return (&this->operator*());
			}

			reference	operator*(void) {
				return (this->current->data);
			}

			const_reference	operator*(void) const {
				return (this->current->data);
			}

			bool	operator==(rb_tree_iterator const &rhs) const {
				return (this->current == rhs.current);
			}

			bool	operator!=(rb_tree_iterator const &rhs) const {
				return (this->current != rhs.current);
			}

	/*-------------------
		BIDIRECTIONNAL
	-------------------*/

			rb_tree_iterator	&operator--(void) {
				if (this->current == this->_nil)
					this->current = this->_max(this->_root);
				else
					this->current = this->_prev(this->current);
				return (*this);
			}

			rb_tree_iterator	operator--(int) {
				rb_tree_iterator tmp(this->current, this->_root, this->_nil);
				if (this->current == this->_nil)
					this->current = this->_max(this->_root);
				else
					this->current = this->_prev(this->current);
				return (tmp);
			}

	/*-----------
		UTILS
	-----------*/

		private:
			node_ptr	_max(node_ptr node) {
				if (node != this->_nil)
					while (node->right != this->_nil)
						node = node->right;
				return (node);
			}

			node_ptr	_min(node_ptr node) {
				if (node != this->_nil)
					while (node->left != this->_nil)
						node = node->left;
				return (node);
			}

			/* Si node right alors on return min du node de droite
				else on remonte les parents de l'arbre */
			node_ptr	_next(node_ptr node) {
				if (node->right != this->_nil)
					return (this->_min(node->right));
				node_ptr parent = node->parent;
				while (parent != this->_nil && node == parent->right) {
					node = parent;
					parent = parent->parent;
				}
				return (parent);
			}

			node_ptr	_prev(node_ptr node) {
				if (node->left != this->_nil)
					return (this->_max(node->left));
				node_ptr parent = node->parent;
				while (parent != this->_nil && node == parent->left) {
					node = parent;
					parent = parent->parent;
				}
				return (parent);
			}
	};

	/*----------
		RBT
	----------*/

	template <typename T, typename Allocator, typename Compare = std::less<T> >
	class rb_tree {

		public:
			typedef rb_node<T> node;
			typedef rb_node<T> *node_ptr;
			typedef T value_type;
			typedef typename Allocator::template rebind<rb_node<value_type> >::other allocator_type;
			typedef Compare compare_type;
			typedef rb_tree_iterator<T, rb_node<T> > iterator;
			typedef rb_tree_iterator<T const, rb_node<T> > const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef std::size_t size_type;

		private:
			node_ptr _root;
			node_ptr _nil;
			allocator_type _alloc;
			compare_type _compare;
			size_type _size;

		public:
			rb_tree(allocator_type const &alloc = allocator_type(), compare_type const &compare = compare_type())
			: _alloc(alloc), _compare(compare), _size(size_type(0)) {
				this->_nil = this->_alloc.allocate(1);
				this->_alloc.construct(this->_nil, node(
					value_type(), BLACK, this->_nil, this->_nil, this->_nil));
				this->_root = this->_nil;
			}

			rb_tree(rb_tree const &rhs)
			: _alloc(rhs._alloc), _compare(rhs._compare), _size(size_type(0)) {
				this->_nil = this->_alloc.allocate(1);
				this->_alloc.construct(this->_nil, node(
					value_type(), BLACK, this->_nil, this->_nil, this->_nil));
				this->_root = this->_nil;
				*this = rhs;
			}

			~rb_tree(void) {
				this->clear();
				this->_delete_node(this->_nil);
			}

			rb_tree	&operator=(rb_tree const &rhs) {
				if (this != &rhs) {
					this->clear();
					for (const_iterator it = rhs.begin(), ite = rhs.end(); it != ite; ++it)
						this->insert(this->end(), *it);
				}
				return (*this);
			}

	/*--------------
		ITERATORS
	--------------*/

			iterator	begin(void) {
				return (iterator(this->min(), this->_root, this->_nil));
			}

			const_iterator	begin(void) const {
				return (const_iterator(this->min(), this->_root, this->_nil));
			}

			iterator	end(void) {
				return (iterator(this->_nil, this->_root, this->_nil));
			}

			const_iterator	end(void) const {
				return (const_iterator(this->_nil, this->_root, this->_nil));
			}

			reverse_iterator	rbegin(void) {
				return (reverse_iterator(this->end()));
			}

			const_reverse_iterator	rbegin(void) const {
				return (const_reverse_iterator(this->end()));
			}

			reverse_iterator	rend(void) {
				return (reverse_iterator(this->begin()));
			}

			const_reverse_iterator	rend(void) const {
				return (const_reverse_iterator(this->begin()));
			}

	/*--------------
		CAPACITY
	--------------*/
			size_type	size(void) const {
				return (this->_size);
			}

			size_type	max_size(void) const {
				return (this->_alloc.max_size());
			}

	/*-------------
		MODIFIERS
	-------------*/

			node_ptr	max(void) const {
				return (this->_max(this->_root));
			}

			node_ptr	_max(node_ptr current) const {
				while (current->right != this->_nil)
					current = current->right;
				return (current);
			}

			node_ptr	min(void) const {
				return (this->_min(this->_root));
			}

			node_ptr	_min(node_ptr current) const {
				while (current->left != this->_nil)
					current = current->left;
				return (current);
			}

			ft::pair<iterator, bool>	insert(const_iterator hint, value_type val) {
				node_ptr prev = this->_nil;
				node_ptr  current;
				if (hint.current == this->_nil
					|| !(this->_compare(val, hint.current->right->data) == true
						&& this->_compare(hint.current->parent->data, val) == true)
					|| !(this->_compare(hint.current->left->data, val) == true
						&& this->_compare(val, hint.current->parent->data) == true))
					current = this->_root;
				else
					current = hint.current;
				while (current != this->_nil) {
					prev = current;
					if (this->_compare(val, current->data))
						current = current->left;
					else if (this->_compare(current->data, val))
						current = current->right;
					else
						return (ft::make_pair(iterator(current, this->_root, this->_nil), false));
				}
				node_ptr new_node = this->_new_node(val);
				new_node->parent = prev;
				if (prev == this->_nil)
					this->_root = new_node;
				else if (this->_compare(new_node->data, prev->data))
					prev->left = new_node;
				else
					prev->right = new_node;
				this->_fix_insert(new_node);
				// if (current == this->_nil)
					// return (ft::make_pair(this->end(), false));
				++this->_size;
				return (ft::make_pair(iterator(new_node, this->_root, this->_nil), true));
			}

			void	erase(iterator position) {
				erase(position.current);
			}

			void	erase(value_type val) {
				node_ptr node;
				node = this->_search(val);
				if (node != this->_nil)
					this->erase(node);
			}

			void	erase(node_ptr node) {
				node_ptr tmp = node;
				node_ptr x;
				bool tmp_color = tmp->color;
				if (node->left == this->_nil) {
					x = node->right;
					this->_transplant(node, node->right);
				} else if (node->right == this->_nil) {
					x = node->left;
					this->_transplant(node, node->left);
				} else {
					tmp = _min(node->right);
					tmp_color = tmp->color;
					x = tmp->right;
					if (tmp->parent == node)
						x->parent = tmp;
					else {
						this->_transplant(tmp, tmp->right);
						tmp->right = node->right;
						tmp->right->parent = tmp;
					}
					this->_transplant(node, tmp);
					tmp->left = node->left;
					tmp->left->parent = tmp;
					tmp->color = node->color;
				}
				--this->_size;
				this->_delete_node(node);
				if (tmp_color == BLACK)
					this->_fix_erase(x);
			}

			void	swap(rb_tree &tree) {
				std::swap(this->_root, tree._root);
				std::swap(this->_nil, tree._nil);
				std::swap(this->_size, tree._size);
			}

			void	clear(void) {
				this->_clear(this->_root);
				this->_root = this->_nil;
				this->_size = 0;
			}

	/*--------------
		OPERATIONS
	--------------*/

			iterator	find(value_type const &key) {
				node_ptr node = this->_search(key);
				return (iterator(node, this->_root, this->_nil));
			}

			const_iterator	find(value_type const &key) const {
				node_ptr node = this->_search(key);
				return (const_iterator(node, this->_root, this->_nil));
			}

			iterator	lower_bound(value_type const key) {
				iterator it = this->begin();
				iterator ite = this->end();
				for (; it != ite; ++it)
					if (this->_compare(*it, key) == false)
						break ;
				return (it);
			}

			const_iterator	lower_bound(value_type const key) const {
				const_iterator it = this->begin();
				const_iterator ite = this->end();
				for (; it != ite; ++it)
					if (this->_compare(*it, key) == false)
						break ;
				return (it);
			}


			iterator	upper_bound(value_type const key) {
				iterator it = this->begin();
				iterator ite = this->end();
				for (; it != ite; ++it)
					if (this->_compare(key, *it) == true)
						break ;
				return (it);
			}

			const_iterator	upper_bound(value_type const key) const {
				const_iterator it = this->begin();
				const_iterator ite = this->end();
				for (; it != ite; ++it)
					if (this->_compare(key, *it) == true)
						break ;
				return (it);
			}

		private:

	/*-----------
		ROTATE
	-----------*/

			void	_right_rotate(node_ptr node) {
				node_ptr tmp = node->left;
				node->left = tmp->right;
				if (tmp->right != this->_nil)
					tmp->right->parent = node;
				tmp->parent = node->parent;
				if (node->parent == this->_nil)
					this->_root = tmp;
				else if (node == node->parent->right)
					node->parent->right = tmp;
				else
					node->parent->left = tmp;
				tmp->right = node;
				node->parent = tmp;
			}


			void	_left_rotate(node_ptr node) {
				node_ptr tmp = node->right;
				node->right = tmp->left;
				if (tmp->left != this->_nil)
					tmp->left->parent = node;
				tmp->parent = node->parent;
				if (node->parent == this->_nil)
					this->_root = tmp;
				else if (node == node->parent->left)
					node->parent->left = tmp;
				else
					node->parent->right = tmp;
				tmp->left = node;
				node->parent = tmp;
			}

	/*-----------
		INSERT
	-----------*/

			void	_fix_insert(node_ptr node) {
				node_ptr uncle;
				while (node->parent->color == RED) {
					if (node->parent == node->parent->parent->left) {
						uncle = node->parent->parent->right;
						if (uncle->color == RED) {
							node->parent->color = BLACK;
							uncle->color = BLACK;
							node->parent->parent->color = RED;
							node = node->parent->parent;
						} else {
							if (node == node->parent->right) {
								node = node->parent;
								this->_left_rotate(node);
							}
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							this->_right_rotate(node->parent->parent);
						}
					} else {
						uncle = node->parent->parent->left;
						if (uncle->color == RED) {
							node->parent->color = BLACK;
							uncle->color = BLACK;
							node->parent->parent->color = RED;
							node = node->parent->parent;
						} else {
							if (node == node->parent->left) {
								node = node->parent;
								this->_right_rotate(node);
							}
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							this->_left_rotate(node->parent->parent);
						}
					}
				}
				this->_root->color = BLACK;
			}

	/*-----------
		ERASE
	-----------*/

			void	_fix_erase(node_ptr x) {
				node_ptr w;
				while (x != this->_root && x->color == BLACK) {
					if (x == x->parent->left) {
						w = x->parent->right;
						if (w->color == RED) {
							w->color = BLACK;
							x->parent->color = RED;
							this->_left_rotate(x->parent);
							w = x->parent->right;
						}
						if (w->left->color == BLACK && w->right->color == BLACK) {
							w->color = RED;
							x = x->parent;
						} else {
							if (w->right->color == BLACK) {
								w->left->color = BLACK;
								w->color = RED;
								this->_right_rotate(w);
								w = x->parent->right;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->right->color = BLACK;
							this->_left_rotate(x->parent);
							x = this->_root;
						}
					} else {
						w = x->parent->left;
						if (w->color == RED) {
							w->color = BLACK;
							x->parent->color = RED;
							this->_right_rotate(x->parent);
							w = x->parent->left;
						}
						if (w->right->color == BLACK && w->left->color == BLACK) {
							w->color = RED;
							x = x->parent;
						} else {
							if (w->left->color == BLACK) {
								w->right->color = BLACK;
								w->color = RED;
								this->_left_rotate(w);
								w = x->parent->left;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->left->color = BLACK;
							this->_right_rotate(x->parent);
							x = this->_root;
						}
					}
				}
				x->color = BLACK;
			}

			/* Connects node to to_cut's parent */
			void	_transplant(node_ptr to_cut, node_ptr to_connect) {
				if (to_cut->parent == this->_nil)
					this->_root = to_connect;
				else if (to_cut == to_cut->parent->left)
					to_cut->parent->left = to_connect;
				else
					to_cut->parent->right = to_connect;
				to_connect->parent = to_cut->parent;
			}

			void	_clear(node_ptr node) {
				if (node == this->_nil)
					return ;
				this->_clear(node->left);
				this->_clear(node->right);
				this->_delete_node(node);
			}

	/*-----------
		SEARCH
	-----------*/

			node_ptr	_search(value_type value) const {
				node_ptr current = this->_root;
				while (current != this->_nil) {
					if (this->_compare(value, current->data))
						current = current->left;
					else if (this->_compare(current->data, value))
						current = current->right;
					else
						break ;
				}
				return (current);
			}

	/*----------------------
		CREATE/DELETE NODE
	----------------------*/

			node_ptr	_new_node(value_type val = value_type()) {
				node_ptr new_node = this->_alloc.allocate(1);
				this->_alloc.construct(new_node, node(
					val, RED, this->_nil, this->_nil, this->_nil));
				return (new_node);
			}

			void	_delete_node(node_ptr node) {
					this->_alloc.destroy(node);
					this->_alloc.deallocate(node, 1);
			}

	/*-----------
		PRINT
	-----------*/

			void	print(void) {
				std::stringstream buffer;
				this->_print(this->_root, buffer, true, "");
				std::cout << buffer.str();
			}

			void	_print(rb_node<T> *node, std::stringstream &buffer, bool is_tail, std::string prefix) {
				if (node->right != this->_nil)
					this->_print(node->right, buffer, false,
						std::string(prefix).append(is_tail != 0 ? "│   " : "    "));
				buffer << prefix << (is_tail != 0 ? "└── " : "┌── ");
				if (node->color == RED)
					buffer << "\033[31m";
				buffer << node->data << "\033[0m" << std::endl;
				if (node->left != this->_nil)
					this->_print(node->left, buffer, true,
							std::string(prefix).append(is_tail != 0 ? "    " : "│   "));
			}
	};
}

#endif