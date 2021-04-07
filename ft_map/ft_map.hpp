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

		iterator				roooot_______()				{ return iterator(root_); };

		iterator				begin()				{ return iterator(begin_ptr_); };
		const_iterator	begin()	const	{ return const_iterator(begin_ptr_); };
		iterator				end()					{ return iterator(end_ptr_->right_); };
		const_iterator	end()		const	{ return const_iterator(end_ptr_); };
		bool 						empty()	const	{ return size_ > 0; };
		size_type				size()	const { return size_; };


		ret_insert_	searchToInsert(node_pointer& cur, const value_type& value) {
			if (!cur) {
				return addNode(cur, root_, value);
			}
			else if (!comp_(value, cur->pair_) && !comp_(cur->pair_, value))
				return ret_insert_(iterator(root_), false);
			else if (comp_(value, cur->pair_)) {
				return  cur->left_ ? searchToInsert(cur->left_, value) : addNode((cur->left_), cur, value);
			}
			else if (!comp_(value, cur->pair_)) {
				return  cur->right_ ? searchToInsert(cur->right_, value) : addNode((cur->right_), cur, value);
			}
		}

		ret_insert_		addNode(node_pointer& new_place, node_pointer& parent, const value_type& val) {
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
				searchToRoot(parent);
			}
			end_node_.parent_ = end_ptr_;
			end_ptr_->right_ = &end_node_;
			++size_;
			return ret_insert_(iterator(new_place), true) ;
		};

		void balance(node_pointer cur) {
			if(cur->getBalanceFactor(cur) == 2)
			{
				if(cur->getBalanceFactor(cur->right_) < 0)
					rotate_right(cur->right_);
				rotate_left(cur);
			}
			if(cur->getBalanceFactor(cur) == -2)
			{
				if( cur->getBalanceFactor(cur->left_) > 0  )
					rotate_left(cur->left_);
				rotate_right(cur);
			}
		}

		void rotate_right(node_pointer cur) // правый поворот вокруг p
		{
			node_pointer neo_head = cur->right_;
			if (cur == root_)
				root_ = neo_head;
			else
				cur->parent_->right_ = neo_head;
			node_pointer tmp = neo_head->left_;
			neo_head->parent_ = cur->parent_;

			cur->parent_ = neo_head;
			neo_head->left_ = cur;
			cur->right_ = tmp;
			if (tmp)
				tmp->parent_ = neo_head->left_;

//			neo_head->fix_height();
			cur->right_->fix_height();
			cur->fix_height();
		}

		void rotate_left(node_pointer cur) // левый поворот вокруг p
		{
			node_pointer neo_head = cur->left_;
			if (cur == root_)
				root_ = neo_head;
			else
				cur->parent_->left_ = neo_head;
			node_pointer tmp = neo_head->right_;
			neo_head->parent_ = cur->parent_;

			cur->parent_ = neo_head;
			neo_head->right_ = cur;
			cur->left_ = tmp;
			if (tmp)
				tmp->parent_ = neo_head->right_;

//			neo_head->fix_height();
			cur->left_->fix_height();
			cur->fix_height();
		}

			bool	searchToRoot(node_pointer& cur) {
				// Может останавливаться если height_ перестает меняться?
				int8_t	prev = cur->height_;
				cur->fix_height();
				balance(cur);
				return (cur && cur->parent_ != nullptr && cur->height_ != prev) && searchToRoot(cur->parent_);
		}

		ret_insert_	insert(const value_type& value) {
			if (end_ptr_)
				end_ptr_->right_ = nullptr;
			return searchToInsert(root_, value);
		};

		void	dlete_elem(node_pointer& position) {
			alloc_.destroy(&position->pair_);
			if (position == end_ptr_ && position->parent_)
				end_ptr_ = position->parent_;
			position->left_ = nullptr;
			position->right_ = nullptr;
			position->parent_ = nullptr;
			alloc_node_.deallocate(position, 1);
			--size_;
		};

		void	go_left_to_right(node_pointer pointer) {
				pointer = pointer->left_;
				while(pointer->right_) {
					pointer = pointer->right_;
				}
		}

		void	go_right_to_left(node_pointer pointer) {
			pointer = pointer->left_;
			while(pointer->right_) {
				pointer = pointer->right_;
			}
		}

		void	swp(ft::map_node<value_type>* ref, ft::map_node<value_type>* target) {
			target->parent_ = ref->parent_;
			target->right_ = ref->right_;
			target->left_ = ref->left_;
			target->fix_height();
		}

		void	erase (iterator position) {
			if (position == end())
				return ;
			if (end_ptr_)
				end_ptr_->right_ = nullptr;
			node_pointer pointer = position.getPointer();
			node_pointer parent = pointer->parent_;
			if (!pointer->left_ && !pointer->right_) {
				dlete_elem(pointer);
			}
			else if (((bool)pointer->left_ + (bool)pointer->right_) < 2) {
				if (pointer == parent->left_) {
					parent->left_ = pointer->left_ ? pointer->left_ : pointer->right_;
					parent->left_->parent_ = parent;
				}
				else {
					parent->right_ = pointer->left_ ? pointer->left_ : pointer->right_;
					parent->right_->parent_ = parent;
				}
				dlete_elem(pointer);
			}
			else {

			}
			searchToRoot(parent);
			end_ptr_->right_ = &end_node_;
		};
//		size_type erase (const key_type& k) {};
//		void erase (iterator first, iterator last) {};

//		Для балансировки будем хранить для каждой вершины разницу между высотой её левого и правого
	};
}

#endif //FT_MAP_FT_MAP_HPP
