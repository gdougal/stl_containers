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
//		node_pointer		begin_ptr_;
//		node_pointer		end_ptr_;

//		Node_						end_node_;
//		Node_						begin_node_;

		node_pointer		end_node_;
		node_pointer		begin_node_;

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


		void			create_end_begin() {
			end_node_ = alloc_node_.allocate(1);
			alloc_node_.construct(end_node_);
			begin_node_ = alloc_node_.allocate(1);
			alloc_node_.construct(begin_node_);
		};

		explicit map(const key_compare& comp = key_compare(), const Alloc& alloc = Alloc())
			: comp_(comp),
			size_(0),
			root_(nullptr),
			alloc_(alloc),
			alloc_node_(alloc_) {
			create_end_begin();
		};

		template< class InputIt >
		map(InputIt first, InputIt last, const key_compare& comp = key_compare(),
			const Alloc& alloc = Alloc()): comp_(comp) {

		};

		map(const map& other) {

		};

		virtual ~map() {
			if (size_)
				clear();
		}

		iterator				begin()				{ return iterator(begin_node_->parent_); };
		const_iterator	begin()	const	{ return const_iterator(begin_node_->parent_); };
		iterator				end()					{ return iterator(end_node_); };
		const_iterator	end()		const	{ return const_iterator(end_node_); };
		bool 						empty()	const	{ return size_ > 0; };
		size_type				size()	const { return size_; };


		ret_insert_	insert(const value_type& value) {
			disconnect_begin_end();
			return find_place_to_insert(root_, value);
		};

		void clear() { erase(begin(), end()); };

		void	erase (iterator position) {
			if (position == end())
				return ;
			disconnect_begin_end();
			node_pointer position_ptr = position.getPointer();
			erase_util(position_ptr, position_ptr->parent_);
			if (root_)
				set_begin_end_ptr(position_ptr);
		};

		size_type erase (const key_type& k) { erase(find(k)); };

		void erase (iterator first, iterator last) {
			if (first == last)
				return ;
			erase(first++);
			erase(first, last);
		};

		iterator				find(const key_type& k) {
			node_pointer result_find;
			find_util(root_, k, &result_find);
			return iterator(result_find);
		};

		const_iterator	find(const key_type& k) const {
			node_pointer result_find;
			find_util(root_, k, &result_find);
			return const_iterator(result_find);
		};

	private:

		void				disconnect_begin_end() {
			if (begin_node_->parent_)
				begin_node_->parent_->left_ = nullptr;
			if (end_node_->parent_)
				end_node_->parent_->right_ = nullptr;
		}

		void				set_begin_end_ptr(node_pointer& position_ptr) {
			(go_to_left(root_))->setLeftChild(begin_node_);
			(go_to_right(root_))->setRightChild(end_node_);
		}

		void	dlete_elem(node_pointer& position) {
			alloc_.destroy(&position->pair_);
			position->left_ = nullptr;
			position->right_ = nullptr;
			position->parent_ = nullptr;
			alloc_node_.deallocate(position, 1);
			--size_;
		};

		node_pointer&	go_to_right(node_pointer& start) {
			if (!start || !start->right_)
				return start;
			return go_to_right(start->right_);
		}

		node_pointer&	go_to_left(node_pointer& start) {
			if (!start || !start->left_)
				return start;
			return go_to_left(start->left_);
		}

		void erase_util(node_pointer position_ptr, node_pointer parent_ptr) {
			node_pointer balance;
			node_pointer target;

			if (!position_ptr->left_ || !position_ptr->right_) {
				if (position_ptr == root_) {
					root_ = position_ptr->getOneChild();
					dlete_elem(position_ptr);
					return;
				}
				balance = position_ptr->getOneChild();
				position_ptr->setParent(balance, parent_ptr, position_ptr);
				dlete_elem(position_ptr);
				if (!balance)
					balance = parent_ptr;
			}
			else if (position_ptr != root_ && parent_ptr->right_ == position_ptr) {
				target = go_to_left(position_ptr->right_);
				balance = target->parent_;
				pointing_child_and_delete(position_ptr, target);
			}
			else {
				target = go_to_right(position_ptr->left_);
				balance = target->parent_;
				pointing_child_and_delete(position_ptr, target);
			}
			go_to_root_and_balance(balance);
		}

		void	pointing_child_and_delete(node_pointer& ref, node_pointer target) {
			target->setParent(target->getOneChild(), target->parent_, target);
			target->setRightChild(ref->right_);
			target->setLeftChild(ref->left_);
			target->setParent(target, ref->parent_, ref);
			if (ref == root_)
				root_ = target;
			dlete_elem(ref);
		}

		void	find_util(node_pointer& cur, const key_type& value, node_pointer* res) {
			if (cur && cur->pair_.first == value) {
				*res = cur != begin_node_ ? cur : end_node_;
			}
			else if (cur && value < cur->pair_.first) {
				find_util(cur->left_, value, res);
			}
			else if (cur && value > cur->pair_.first) {
				find_util(cur->right_, value, res);
			}
			else {
				*res = end_node_;
			}
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
			if (new_place != root_) {
				new_place->parent_ = parent;
				new_place->fix_height();
				go_to_root_and_balance(parent);
			}
			++size_;
			set_begin_end_ptr(parent);
			return ret_insert_(iterator(new_place), true);
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

		void	go_to_root_and_balance(node_pointer& cur) {
			// Может останавливаться если height_ перестает меняться?
			cur->fix_height();
			balance(cur);
			if (cur)
				go_to_root_and_balance(cur->parent_);
		}
	};
}

#endif //FT_MAP_FT_MAP_HPP
