//
// Created by Gilberto Dougal on 3/30/21.
//

#ifndef FT_MAP_FT_MAP_HPP
#define FT_MAP_FT_MAP_HPP

#include <memory>
#include "ft_utils/ft_map_utils.hpp"
#include "ft_utils/ft_utils.hpp"
#define		DRAW 1

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
		typedef	map_util::map_node<value_type>																Node_;
		typedef	typename allocator_type::template rebind<Node_>::other	alloc_node;
		typedef	typename alloc_node::pointer														node_pointer;

		class value_compare : public std::binary_function<value_type, value_type, bool> {
		public:
			key_compare comp;
			explicit value_compare(key_compare c) : comp(c) {}
			bool operator()(const value_type& x, const value_type& y) const
			{ return comp(x.first, y.first); }
		};

	private:

		node_pointer		root_;
		node_pointer		end_node_;
		node_pointer		begin_node_;
		size_type				size_;
		allocator_type	alloc_;
		alloc_node			alloc_node_;
		value_compare		comp_;

	public:
		typedef		map_util::mapIterator<value_type, Node_>							iterator;
		typedef		map_util::constMapIterator<value_type, Node_>					const_iterator;
		typedef		gu::reverse_it<iterator>															reverse_iterator;
		typedef		gu::const_reverse_it<iterator>												const_reverse_iterator;

	private:
		typedef		std::pair<iterator, bool>															ret_insert_;

	public:


		explicit map(const key_compare& comp = key_compare(), const Alloc& alloc = Alloc())
			: comp_(comp),
			size_(0),
			root_(nullptr),
			alloc_(alloc),
			alloc_node_(alloc_) {
			allocate_end_begin();
		};

		template< class InputIt >
		map(InputIt first, InputIt last, const key_compare& comp = key_compare(),
			const Alloc& alloc = Alloc(), ENABLE_IF_TYPE(InputIt))
			: comp_(comp),
			size_(0),
			root_(nullptr),
			alloc_(alloc),
			alloc_node_(alloc_) {
			allocate_end_begin();
			insert(first, last);
		};

		map(const map& other)
		: comp_(comp_.comp),
		size_(0),
		root_(nullptr),
		alloc_(other.alloc_),
		alloc_node_(alloc_)
		{
			allocate_end_begin();
			*this = other;
		};

		map& operator=(const map& x) {
			if (this != &x) {
				clear();
				insert(x.begin(), x.end());
			}
			return *this;
		};


		virtual ~map() {
			clear();
			deallocate_end_begin();
		}


		value_type&			operator[] (const key_type& k) {return (*((insert(value_type(k, mapped_type()))).first)).second;};
		reverse_iterator				rbegin()				{ return  reverse_iterator(end()); };
		const_reverse_iterator	rbegin()	const	{ return const_reverse_iterator(end()); };
		reverse_iterator				rend()					{ return reverse_iterator(begin()); };
		const_reverse_iterator	rend()		const	{ return const_reverse_iterator(begin()); };
		iterator								begin()					{ return iterator(begin_node_->parent_); };
		const_iterator					begin()		const	{ return const_iterator(begin_node_->parent_); };
		iterator								end()						{ return iterator(end_node_); };
		const_iterator					end()			const	{ return const_iterator(end_node_); };
		bool 										empty()		const	{ return size_ == 0; };
		size_type								size()		const { return size_; };


		ret_insert_	insert(const value_type& value) {
			if (root_)
				disconnect_begin_end();
			node_pointer	place = wrap_find(value, true);
			if (!place) {
				add_node(root_, root_, value);
				return ret_insert_(iterator(root_), true);
			}
			else if (!comp_(value, place->pair_) && !comp_(place->pair_, value)) {
				set_begin_end_ptr();
				return ret_insert_(iterator(place), false);
			}
			add_node(getKeyWay(value,place), place, value);
			return ret_insert_(iterator(place), true);
		};

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last, ENABLE_IF_TYPE(InputIterator)) {
			if (first == last)
				return ;
			insert((*first));
			insert(++first, last);
		};

		std::pair<const_iterator,const_iterator>	equal_range (const key_type& k) const {
			const_iterator ret = find(k);
			return std::pair<const_iterator,const_iterator>(ret, ret);
		};

		std::pair<iterator,iterator>							equal_range (const key_type& k) {
			iterator ret = find(k);
			return std::pair<iterator,iterator>(ret, ret);
		};

		void clear() {
			erase(begin(), end());
		};

		void	erase (iterator position) {
			if (position == end())
				return ;
			if (root_)
				disconnect_begin_end();
			node_pointer position_ptr = position.getPointer();
			erase_util(position_ptr, position_ptr->parent_);
			if (root_)
				set_begin_end_ptr();
		};

		size_type erase (const key_type& k) {
			node_pointer place = wrap_find(value_type(k, T()));
			if (!place)
				return 0;
			erase(iterator(place));
			return 1;
		};

		void erase (iterator first, iterator last) {
			if (first.getPointer() != end_node_)
				return ;
			erase(first++);
			erase(first, last);
		};


		iterator				find(const key_type& k) {
			node_pointer place = wrap_find(value_type(k, T()));
			if (!place || !equal(place, value_type(k, T())))
				return end();
			return iterator(place);
		};

		const_iterator	find(const key_type& k) const {
			node_pointer place = wrap_find(value_type(k, T()));
			if (!place || !equal(place, value_type(k, T())))
				return end();
			return const_iterator(place);
		};

		size_type count(const key_type& k) const {
			return (find(k) != end());
		};

		iterator lower_bound (const key_type& k) {
			node_pointer place = wrap_find(value_type(k, T()));
			if (!place || place == begin_node_)
				return end();
			return iterator(place);
		};

		const_iterator lower_bound (const key_type& k) const {
			node_pointer place = wrap_find(value_type(k, T()));
			if (!place || place == begin())
				return end();
			return const_iterator(place);
		};

		iterator upper_bound (const key_type& k) {
			iterator ret(lower_bound(k));
			if (ret != end())
				return ++ret;
			return ret;
		};

		const_iterator upper_bound (const key_type& k) const {
			const_iterator ret(lower_bound(k));
			if (ret != end())
				return ++ret;
			return ret;
		};

		void swap (map& x) {
			f_swp(root_, x.root_);
			f_swp(alloc_node_, x.alloc_node_);
			f_swp(alloc_, x.alloc_);
			f_swp(begin_node_, x.begin_node_);
			f_swp(end_node_, x.end_node_);
			f_swp(comp_, x.comp_);
			f_swp(size_, x.size_);
		};

#if DRAW
		int16_t				height_ret() const {
			return root_->height_;
		}
		const node_pointer	root_ret() const {
			return root_;
		}
#endif

	private:

		void			allocate_end_begin() {
			end_node_ = alloc_node_.allocate(1);
			alloc_node_.construct(end_node_);
			begin_node_ = alloc_node_.allocate(1);
			alloc_node_.construct(begin_node_);
		};

		void			deallocate_end_begin() {
			alloc_node_.deallocate(begin_node_, 1);
			alloc_.destroy(&begin_node_->pair_);
			alloc_node_.deallocate(end_node_, 1);
			alloc_.destroy(&end_node_->pair_);
		};

		void				disconnect_begin_end() {
			if (size_) {
				begin_node_->parent_->left_ = nullptr;
				end_node_->parent_->right_ = nullptr;
			}
				begin_node_->parent_ = nullptr;
				end_node_->parent_ = nullptr;
		}

		void				set_begin_end_ptr() {
			(go_to_left(root_))->setLeftChild(begin_node_, true);
			(go_to_right(root_))->setRightChild(end_node_, true);
		}

		void	dlete_elem(node_pointer& position) {
			alloc_.destroy(&position->pair_);
			position->left_ = nullptr;
			position->right_ = nullptr;
			position->parent_ = nullptr;
			alloc_node_.deallocate(position, 1);
			--size_;
		};

		node_pointer&	go_to_right(node_pointer& start) const {
			if (!start || !start->right_)
				return start;
			return go_to_right(start->right_);
		}

		node_pointer&	go_to_left(node_pointer& start) const {
			if (!start || !start->left_)
				return start;
			return go_to_left(start->left_);
		}

		void erase_util(node_pointer& position_ptr, node_pointer& parent_ptr) {
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
				balance = target->parent_ != position_ptr ? target->parent_ : position_ptr->left_;
				pointing_child_and_delete(position_ptr, target);
			}
			else {
				target = go_to_right(position_ptr->left_);
				balance = target->parent_ != position_ptr ? target->parent_ : position_ptr->right_;
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


		node_pointer&	getKeyWay(const value_type& fo_comp, const node_pointer& cur) const {
			return comp_(fo_comp, cur->pair_) ? cur->left_ : cur->right_;
		}


		bool	stop_find(const node_pointer& cur, const value_type& val, const bool& to_insert, node_pointer*& buf) const {
			if (equal(cur, val)) {
				*buf = cur;
				return true;
			}
			if (!to_insert) {
				if (comp_(val, cur->pair_)) {
					if (*buf && !getKeyWay(val, cur)) {
						*buf = cur;
						return true;
					}
					*buf = cur;
				}
			}
			return false;
		}

		bool stop_find_insert(const node_pointer& cur, const value_type& val, const bool& to_insert) const {
			return (to_insert && (!cur || !getKeyWay(val, cur)));
		}

		bool equal(const node_pointer& cur, const value_type& val) const {
			return (!comp_(val, cur->pair_) && !comp_(cur->pair_, val));
		}

		void	find_util(const node_pointer& cur, const value_type& val, node_pointer* res, const bool to_insert = false) const {
			if (!cur || stop_find_insert(cur, val, to_insert) || stop_find(cur, val, to_insert, res)) {
				if (!(*res))
					*res = cur;
				return ;
			}
			find_util(getKeyWay(val, cur), val, res, to_insert);
		}

		node_pointer wrap_find(const value_type& to_compare, const bool to_end = false) const {
			node_pointer	result_find = nullptr;
			find_util(root_, to_compare, &result_find, to_end);
			if (!to_end && !equal(result_find, to_compare))
				return nullptr;
			else
				return result_find;
		};

		void		add_node(node_pointer& new_place, node_pointer& parent, const value_type& val) {
			new_place = alloc_node_.allocate(1);
			alloc_node_.construct(new_place, val);
			if (new_place != root_) {
				new_place->parent_ = parent;
			}
			++size_;
			go_to_root_and_balance(new_place);
			set_begin_end_ptr();
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
				if(cur->getBalanceFactor(cur->left_) > 0)
					rotate_left(cur->left_);
				rotate_right(cur);
			}
		}

		void	rotate_right(node_pointer cur) // правый поворот вокруг p
		{
			node_pointer neo_head = cur->left_;
			node_pointer tmp = neo_head->right_;
			cur->setLeftChild(tmp);
			if (cur == root_)
				root_ = neo_head;
			neo_head->setParent(neo_head, cur->parent_, cur);
			neo_head->setRightChild(cur);
		}

		void	rotate_left(node_pointer cur) // левый поворот вокруг p
		{
			node_pointer neo_head = cur->right_;
			node_pointer tmp = neo_head->left_;
			cur->setRightChild(tmp);
			if (cur == root_)
				root_ = neo_head;
			neo_head->setParent(neo_head, cur->parent_, cur);
			neo_head->setLeftChild(cur);
		}

		void	go_to_root_and_balance(node_pointer cur) {
			if (!cur)
				return;
			node_pointer tmp = cur->parent_;
			balance(cur);
			go_to_root_and_balance(tmp);
		}
	};
}

#endif //FT_MAP_FT_MAP_HPP
