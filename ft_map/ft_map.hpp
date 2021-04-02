//
// Created by Gilberto Dougal on 3/30/21.
//

#ifndef FT_MAP_FT_MAP_HPP
#define FT_MAP_FT_MAP_HPP

#include <memory>
#include "ft_map_utils.hpp"
#include "../ft_utils/ft_utils.hpp"
#include "map_iterator.hpp"

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
		typedef	typename allocator_type:: template rebind<Node_>::other	alloc_node;
		typedef	typename alloc_node::pointer														node_pointer;

		class value_compare : public std::binary_function<value_type, value_type, bool> {
//		protected:
		public:
			key_compare comp;
			value_compare(key_compare c) : comp(c) {}
			bool operator()(const value_type& x, const value_type& y) const
			{ return comp(x.first, y.first); }
		};

		node_pointer		root_;
		node_pointer		begin_;
		node_pointer		end_;
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
			begin_(nullptr),
			end_(nullptr) {
		};

		template< class InputIt >
		map(InputIt first, InputIt last, const key_compare& comp = key_compare(),
			const Alloc& alloc = Alloc()): comp_(comp) {

		};

		map(const map& other) {

		};

		virtual ~map() {}

		iterator				roooot_______()				{ return iterator(root_); };

		iterator				begin()				{ return iterator(begin_); };
		const_iterator	begin()	const	{ return const_iterator(begin_); };
		iterator				end()					{ return iterator(end_); };
		const_iterator	end()		const	{ return const_iterator(end_); };
		bool 						empty()	const	{ return size_ > 0; };
		size_type				size()	const { return size_; };


		bool	searchToInsert(node_pointer& cur, const value_type& value) {
			if (!cur) {
				return addNode(cur, nullptr, value);
			}
			else if (!comp_(value, cur->pair_) && !comp_(cur->pair_, value))
				return false;
//			else if (comp_(value, cur->pair_)) {
//				return  cur->left_ ? searchToInsert(cur->left_, value) : addNode((cur->left_), cur, value);
//			}
//			else if (!comp_(value, cur->pair_)) {
//				return  cur->right_ ? searchToInsert(cur->right_, value) : addNode((cur->right_), cur, value);
//			}
			return ( (cur->right_ && searchToInsert(cur->right_, value))
			|| (!comp_(value, cur->pair_) && addNode((cur->right_), cur, value)) )
			|| ( (cur->left_ && searchToInsert(cur->left_, value)) || addNode((cur->left_), cur, value) );
		}

		bool		addNode(node_pointer& new_place, const node_pointer& parent, const value_type& val) {
			new_place = alloc_node_.allocate(1);
			alloc_node_.construct(new_place, val);
			new_place->parent_ = parent;

			root_->parent_ = new_place; /// TODO : Приколдес нового уровня, не забывать подчищать
			return true;
		};

		ret_insert_	insert(const value_type& value) {
			bool serch_ret = searchToInsert(root_, value);
			iterator	it_ret(root_->parent_);
			ret_insert_ ret_val(it_ret, serch_ret);
			root_->parent_ = nullptr;
			return ret_val;
		};
	};
}

#endif //FT_MAP_FT_MAP_HPP
