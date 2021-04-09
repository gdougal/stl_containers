//
// Created by Gilberto Dougal on 3/30/21.
//

#ifndef FT_MAP_FT_MAP_HPP
#define FT_MAP_FT_MAP_HPP

#include <memory>
#include "ft_map_utils.hpp"
#include "../ft_utils/ft_utils.hpp"
#include "map_iterator.hpp"
#include <cmath>

namespace ft {

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
	class map {
	public:

		typedef	Key																											key_type;
		typedef	T																												mapped_type;
		typedef	std::pair<const Key, T>																	value_type;
		typedef	size_t																									size_type;
		typedef	std::ptrdiff_t																					difference_type;
		typedef Compare																									key_compare;
		typedef	Alloc																										allocator_type;
		typedef	typename allocator_type::pointer												pointer;
		typedef	typename allocator_type::reference											reference;
		typedef	typename allocator_type::const_pointer									const_pointer;
		typedef	typename allocator_type::const_reference								const_reference;

	private:
		typedef	ft::map_node<value_type>																Node_;
		typedef	typename allocator_type::template rebind<Node_>::other	alloc_node;
		typedef	typename alloc_node::pointer														node_pointer;

		class value_compare : public std::binary_function<value_type, value_type, bool> {
//		protected:
		public:
			key_compare comp;
			value_compare(key_compare c) : comp(c) {}
			bool operator()(const value_type& x, const value_type& y) const
			{ return comp(x.first, y.first); }
		};

	public:

		node_pointer		root_;
		node_pointer		begin_ptr_;
		node_pointer		end_ptr_;

		Node_						end_node_;
		Node_						begin_node_;

		size_type				size_;
		allocator_type	alloc_;
		alloc_node			alloc_node_;
		value_compare		comp_;

	public:
		typedef		mapIterator<value_type, Node_>												iterator;
		typedef		constMapIterator<value_type, Node_>										const_iterator;
		typedef		std::reverse_iterator<iterator>												reverse_iterator;
		typedef		const std::reverse_iterator<iterator>									const_reverse_iterator;
	private:
		typedef		std::pair<iterator, bool>															ret_insert_;

	public:


		explicit map(const key_compare& comp = key_compare(), const Alloc& alloc = Alloc())
			: comp_(comp),
			size_(0),
			root_(nullptr),
			begin_ptr_(nullptr),
			end_ptr_(nullptr),
			alloc_(alloc),
			alloc_node_(alloc_) {};

		template< class InputIt >
		map(InputIt first, InputIt last, const key_compare& comp = key_compare(),
			const Alloc& alloc = Alloc()): comp_(comp) {

		};

		map(const map& other) {

		};

		virtual ~map() {}

		iterator				begin()				{ return iterator(begin_ptr_); };
		const_iterator	begin()	const	{ return const_iterator(begin_ptr_); };
		iterator				end()					{ return iterator(end_ptr_->right_); };
		const_iterator	end()		const	{ return const_iterator(end_ptr_); };
		bool 						empty()	const	{ return size_ > 0; };
		size_type				size()	const { return size_; };


		ret_insert_	insert(const value_type& value) {
			disconnect_begin_end();
			return find_place_to_insert(root_, value);
		};


		void	erase (iterator position) {
			if (position == end())
				return ;
			disconnect_begin_end();
			node_pointer position_ptr = position.getPointer();
			node_pointer parent_ptr = position_ptr->parent_;
			erase_util(position_ptr, parent_ptr);
			connect_begin_end();
		};
//		size_type erase (const key_type& k) {};
//		void erase (iterator first, iterator last) {};


	private:

		void				disconnect_begin_end() {
			if (begin_ptr_)
				begin_ptr_->left_ = nullptr;
			if (end_ptr_)
				end_ptr_->right_ = nullptr;
		}

		void				connect_begin_end() {
			end_node_.parent_ = end_ptr_;
			begin_node_.parent_ = begin_ptr_;
			end_ptr_->right_ = &end_node_;
			begin_ptr_->left_ = &begin_node_;
		}

		void				set_begin_end_ptr(node_pointer& position_ptr = 0) {
			if (position_ptr == begin_ptr_) {
				node_pointer cur = root_;
				while (cur->left_)
					cur = cur->left_;
				begin_ptr_ = cur;
			}
			else if (position_ptr == end_ptr_) {
				node_pointer cur = root_;
				while (cur->right_)
					cur = cur->right_;
				end_ptr_ = cur;
			}
		}

		void	dlete_elem(node_pointer& position) {
			alloc_.destroy(&position->pair_);
			position->left_ = nullptr;
			position->right_ = nullptr;
			position->parent_ = nullptr;
			alloc_node_.deallocate(position, 1);
			--size_;
		};

		node_pointer&	go_left_to_right(node_pointer& start_l) {
			node_pointer	cur = start_l->left_;
			while(cur->right_) {
				cur = cur->right_;
			}
			return cur;
		}

		node_pointer&	go_right_to_left(node_pointer& start_r) {
			node_pointer	cur = start_r->right_;
			while(cur->left_) {
				cur = cur->left_;
			}
			return (cur);
		}

		void erase_util(node_pointer position_ptr, node_pointer parent_ptr) {
			if (!position_ptr->left_ || !position_ptr->right_) {
				node_pointer child_ptr = position_ptr->getOneChild();
				position_ptr->setParent(child_ptr, parent_ptr, position_ptr);
				dlete_elem(position_ptr);
				if (position_ptr == root_) {
					root_ = child_ptr;
					if (!root_) {
						return;
					}
				}
			}
			else {
				if (position_ptr != root_ && parent_ptr->right_ == position_ptr) {
					parent_ptr = pointing_child_and_delete(position_ptr,
																								 go_right_to_left(position_ptr));
				}
				else {
					parent_ptr = pointing_child_and_delete(position_ptr,
																								 go_left_to_right(position_ptr));
				}
			}

			go_to_root_and_balance(parent_ptr);
			set_begin_end_ptr(position_ptr);
		}

		node_pointer	pointing_child_and_delete(node_pointer& ref, node_pointer target) {
			node_pointer	ret_val = target->parent_;
			target->setParent(target->getOneChild(), target->parent_, target);
			target->setRightChild(ref->right_);
			target->setLeftChild(ref->left_);
			target->setParent(target, ref->parent_, ref);
			if (ref == root_)
				root_ = target;
			dlete_elem(ref);
			return ret_val;
		}

		ret_insert_	find_place_to_insert(node_pointer& cur, const value_type& value) {
			if (!cur) {
				return add_node(cur, root_, value);
			}
			else if (!comp_(value, cur->pair_) && !comp_(cur->pair_, value))
				return ret_insert_(iterator(root_), false);
			else if (comp_(value, cur->pair_)) {
				return cur->left_ ? find_place_to_insert(cur->left_, value)
															: add_node((cur->left_), cur, value);
			}
			else if (!comp_(value, cur->pair_)) {
				return cur->right_ ? find_place_to_insert(cur->right_, value)
															: add_node((cur->right_), cur, value);
			}
		}

		ret_insert_		add_node(node_pointer& new_place, node_pointer& parent, const value_type& val) {
			new_place = alloc_node_.allocate(1);
			alloc_node_.construct(new_place, val);
			if (!begin_ptr_ || comp_(val, begin_ptr_->pair_)) {
				begin_ptr_ = new_place;
			}
			if (!end_ptr_ || !comp_(val, end_ptr_->pair_)) {
				end_ptr_ = new_place;
			}
			if (new_place != root_) {
				new_place->parent_ = parent;
				new_place->fix_height();
				go_to_root_and_balance(parent);
			}
			connect_begin_end();
			++size_;
			return ret_insert_(iterator(new_place), true) ;
		};


		void	balance(node_pointer cur) {
			if(cur->getBalanceFactor(cur) == 2)
			{
				if(cur->getBalanceFactor(cur->right_) < 0)
					rotate_right(cur->right_);
				rotate_left(cur);
			}
			if(cur->getBalanceFactor(cur) == -2)
			{
				if( cur->getBalanceFactor(cur->left_) > 0)
					rotate_left(cur->left_);
				rotate_right(cur);
			}
		}

		void	rotate_right(node_pointer& cur) // правый поворот вокруг p
		{
			node_pointer neo_head = cur->right_;
			if (cur == root_)
				root_ = neo_head;
			node_pointer tmp = neo_head->left_;
			neo_head->setParent(neo_head, cur->parent_, cur);
			neo_head->setLeftChild(cur);
			cur->setRightChild(tmp);
		}

		void	rotate_left(node_pointer& cur) // левый поворот вокруг p
		{
			node_pointer neo_head = cur->left_;
			if (cur == root_)
				root_ = neo_head;
			node_pointer tmp = neo_head->right_;
			neo_head->setParent(neo_head, cur->parent_, cur);
			neo_head->setRightChild(cur);
			cur->setLeftChild(tmp);
		}

		bool	go_to_root_and_balance(node_pointer& cur) {
			// Может останавливаться если height_ перестает меняться?
//			int8_t	prev = cur->height_;
			cur->fix_height();
			balance(cur);
//			&& cur->height_ != prev
			return (cur && cur->parent_ != nullptr) && go_to_root_and_balance(cur->parent_);
		}
	};
}

#endif //FT_MAP_FT_MAP_HPP
