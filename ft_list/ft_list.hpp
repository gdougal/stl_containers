//
// Created by Gilberto Dougal on 3/19/21.
//

#ifndef FT_LIST_FT_LIST_HPP
#define FT_LIST_FT_LIST_HPP
#include <memory>
#include "list_utils.hpp"
#include "ft_utils.hpp"
#include "listIterator.hpp"

namespace ft {

#define ENABLE_IF_TYPE(type_ref) \
	typename ft::enable_if<ft::is_same<type_ref>::value, type_ref>::type

	template < class T, class Alloc = std::allocator<T> >
	class list {
	public:
		typedef	T																											value_type;
		typedef	Alloc																									allocator_type;
		typedef	size_t																								size_type;
		typedef	std::ptrdiff_t																				difference_type;
		typedef	typename allocator_type::pointer											pointer;
		typedef	typename allocator_type::reference										reference;
		typedef	typename allocator_type::const_pointer								const_pointer;
		typedef	typename allocator_type::const_reference							const_reference;

	private:
		typedef	ft::Node<value_type>																		Node_;
		typedef	typename allocator_type:: template rebind<Node_>::other	alloc_node;
		typedef	typename alloc_node::pointer														node_pointer;
	public:

		typedef		listIterator<value_type, Node_>												iterator;
		typedef		constListIterator<value_type, Node_>									const_iterator;
		typedef		std::reverse_iterator<iterator>												reverse_iterator;
		typedef		const std::reverse_iterator<iterator>									const_reverse_iterator;

		node_pointer		node_;
		size_type				size_;
		allocator_type	alloc_;
		alloc_node			alloc_node_;


	public:
		void	firstNode() {
			node_ = alloc_node_.allocate(1);
			node_->val = alloc_.allocate(1);
			node_->prev = node_;
			node_->next = node_;
		};

		void	createtNode(const value_type& val) {
			node_pointer newNode;
			newNode = alloc_node_.allocate(1);
			newNode->val = alloc_.allocate(1);
			alloc_.construct(newNode->val, val);
			newNode->prev = node_->prev;
			newNode->next = node_;
			if (node_->next == node_)
				node_->next = newNode;
			else
				node_->prev->next = newNode;
			node_->prev = newNode;
		};

		template<class InputIt>
		void	createPoolsNodes()

		explicit list(const allocator_type& alloc = allocator_type()) :
		size_(0),
		node_(0),
		alloc_(alloc) {
			firstNode();
		}

		explicit list (size_type n, const value_type& val = value_type(),
									 const allocator_type& alloc = allocator_type()) :
		size_(n),
		alloc_(alloc) {
			firstNode();
			for (size_type i = 0; i < n; ++i)
				createtNode(val);
		};
		template <class InputIt>
		list (InputIt first, ENABLE_IF_TYPE(InputIt) last,
					const allocator_type& alloc = allocator_type()) {
			size_ = std::distance(first, last);

		};
//		copy (4)
//		list (const list& x);


		iterator begin() {
			iterator start(node_->next);
			return start;
		};

		const_iterator begin() const {
			const_iterator	start(begin());
			return start;
		};

		iterator end() {
			iterator last(node_);
			return last;
		};

		const_iterator end() const {
			const_iterator	last(end());
			return last;
		};

		bool empty() const					{ return size_ > 0; };
		size_type size() const			{ return size_; };
		size_type max_size() const	{ return (UINT64_MAX)/(sizeof(value_type) == 1 ? 2 : sizeof(value_type)); };
		reference front() { return *(node_->next->value); };
		const_reference front() const { return *(node_->next->value); };
		reference back() { return *(node_->prev->value); };
		const_reference back() const { return *(node_->prev->value); };

	};
}

#endif //FT_LIST_FT_LIST_HPP
