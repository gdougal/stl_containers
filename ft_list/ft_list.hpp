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

		node_pointer		node_;
		size_type				size_;
		allocator_type	alloc_;
		alloc_node			alloc_node_;

	public:
		typedef		listIterator<value_type, Node_>												iterator;
		typedef		constListIterator<value_type, Node_>									const_iterator;
		typedef		std::reverse_iterator<iterator>												reverse_iterator;
		typedef		const std::reverse_iterator<iterator>									const_reverse_iterator;


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
			createtNodes(val, n);
		};

		template <class InputIt>
		list (InputIt first, ENABLE_IF_TYPE(InputIt) last,
					const allocator_type& alloc = allocator_type()) {
			size_ = std::distance(first, last);
			firstNode();
			createtNodes(first, last);
		};

		list (const list& x) {
			*this = x;
			size_ = x.size();
		};

		~list() {
			if (!empty())
				clear();
			alloc_node_.deallocate(node_, 1);
		};

		list& operator=(const list& x) {
			if (this == &x)
				return *this;
			if (!empty())
				clear();
			createtNodes(x.begin(), x.end());
			size_ = x.size();
		};


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

		bool empty() const					{ return size_ == 0; };
		size_type size() const			{ return size_; };
		size_type max_size() const	{ return (UINT64_MAX)/(sizeof(Node_)); };
		reference front() { return node_->next->val; };
		const_reference front() const { return node_->next->val; };
		reference back() { return node_->prev->val; };
		const_reference back() const { return node_->prev->val; };

		template <class InputIt>
		void assign (InputIt first, ENABLE_IF_TYPE(InputIt) last) {
//			size_type	size = std::distance(first, last);
//			for (; size < size_;) {
//				pop_back();
//			}
//			for(iterator it = begin(); it != end(); ++it) {
//				alloc_.destroy(&(*it));
//			}
//			for (iterator it = begin(); first != last && it != end(); ++first, ++it) {
//				alloc_.construct(&(*it), *first);
//			}
//			for (;first != last; ++first) {
//				push_back(*first);
//			}
			clear();
			createtNodes(first, last);
			size_ = std::distance(first, last);
		};

		void assign (size_type n, const value_type& val) {
//			for (; n < size_;) {
//				pop_back();
//			}
//			for(iterator it = begin(); it != end(); ++it) {
//				alloc_.destroy(&(*it));
//			}
//			for (iterator it = begin(); it != end(); ++it) {
//				alloc_.construct(&(*it), val);
//			}
//			while (size_ < n) {
//				push_back(val);
//			}
			clear();
			createtNodes(val, n);
			size_ = n;
		};


		void push_back (const value_type& val) {
			createNode(val, node_);
			++size_;
		};

		void pop_back() {
			node_pointer cur = node_->prev;
			alloc_.destroy(&cur->val);
			pointingPop(cur->prev, node_);
			alloc_node_.deallocate(cur, 1);
			--size_;
		};

		void push_front (const value_type& val) {
			createNode(val, node_->next);
			++size_;
		};

		void pop_front() {
			node_pointer cur = node_->next;
			alloc_.destroy(&cur->val);
			pointingPop(node_, cur->next);
			alloc_node_.deallocate(cur, 1);
			--size_;
		};

		iterator insert (iterator position, const value_type& val) {
			createNode(val, position.getPointer());
			++size_;
			return --position;
		};

		void insert (iterator position, size_type n, const value_type& val) {
			if (!n)
				return ;
			createNode(val, position.getPointer());
			insert(position, --n, val);
		};

		template <class InputIt>
		void insert (iterator position, ENABLE_IF_TYPE(InputIt) first, InputIt last) {
			if (first == last)
				return ;
			insert(position, *(first));
			insert(position, ++first, last);
		};


		iterator erase (iterator position) {
			iterator ret((position.getPointer())->next);
			alloc_.destroy(position.operator->());
			pointingPop((position.getPointer())->prev, (position.getPointer())->next);
			alloc_node_.deallocate(position.getPointer(), 1);
			--size_;
			return ret;
		};

	private:
		void erase_util(iterator first, iterator& last) {
			if (first == last)
				return ;
			erase_util(erase(first), last);
		}
	public:

		iterator erase (iterator first, iterator last) {
			erase_util(first, last);
			return last;
//			for (;first != last ; ++first) {
//				alloc_.destroy(first.operator->());
//				pointingPop((first.getPointer())->prev, (first.getPointer())->next);
//				alloc_node_.deallocate(first.getPointer(), 1);
//				--size_;
//			}
//			return last;
		};

		void clear() {erase(begin(), end());};

		void resize (size_type n, value_type val = value_type()) {
			if (n == size_)
				return ;
			while (size_ > n)
				pop_back();
			while (size_ < n)
				push_back(val);
//			createtNodes(val, n - size_);
			size_ = n;
		};

		void swap (list& x) {
			ft::f_swp(size_, x.size_);
			ft::f_swp(node_, x.node_);
			ft::f_swp(alloc_, x.alloc_);
			ft::f_swp(alloc_node_, x.alloc_node_);
		};

		void splice (iterator position, list& x) {
			pointingPop((position.getPointer())->prev, (x.begin()).getPointer());
			pointingPop((x.end()).getPointer()->prev, position.getPointer());
			size_ += x.size();
			x.pointingPop(x.node_, x.node_);
			x.size_ = 0;
		};

		void splice (iterator position, list& x, iterator i) {
			node_pointer cur = i.getPointer();
			x.pointingPop(cur->prev, cur->next);
			pointingNew(cur, position.getPointer());
			++size_;
			x.size_ -= 1;
		};

		void splice (iterator position, list& x, iterator first, iterator last) {
			size_type			p_size = std::distance(first, last);
			node_pointer	firstPrev_p = (first.getPointer())->prev;
			node_pointer	lastPrev_p = (last.getPointer())->prev;
			node_pointer	last_p = last.getPointer();
			node_pointer	first_p = first.getPointer();

			pointingPop((position.getPointer())->prev, first_p);
			pointingPop(lastPrev_p, position.getPointer());
			x.pointingPop(firstPrev_p, last_p);
			size_ += p_size;
			x.size_ -= p_size;
		};

		void remove (const value_type& val) {
			iterator it = begin();
			while (it != end()) {
				if (*it == val) {
					it = erase(it);
				}
				else {
					++it;
				}
			}
		};

		template <class Predicate>
		void remove_if (Predicate pred) {
			iterator it = begin();
			while (it != end()) {
				if (pred(*it) == true) {
					it = erase(it);
				}
				else {
					++it;
				}
			}
		};

		void unique() {
			iterator it_prev(node_->next);
			iterator it_cur(node_->next->next);
			while (it_cur != end()) {
				if (*it_cur == *it_prev) {
					it_cur = erase(it_cur);
					it_prev = it_cur;
					--it_prev;
				}
				else {
					++it_cur;
					++it_prev;
				}
			}
		};

		template <class BinaryPredicate>
		void unique (BinaryPredicate binary_pred) {
			iterator it_prev(node_->next);
			iterator it_cur(node_->next->next);
			while (it_cur != end()) {
				if (binary_pred(*it_cur, *it_prev) == true) {
					it_cur = erase(it_cur);
					it_prev = it_cur;
					--it_prev;
				}
				else {
					++it_cur;
					++it_prev;
				}
			}
		};




		void merge (list& x) {
//			if (this == &x)
//				return ;
//			iterator it(begin());
//			while(!x.empty()) {
//				for (; *it < *(x.begin()) && it != end(); ++it);
//				splice(it, x, x.begin());
//			}
//			merge_util(x, it);
			merge(x, ft::compare<value_type>);
		};

		template <class Compare>
		void merge (list& x, Compare comp) {
			if (this == &x)
				return ;
			iterator it(begin());
			merge_util_comp(x, it, comp);
		};


		void sort_small() {
			list<value_type>	sorted;
			list<value_type>	part_b;
			while (begin() != end()) {
				part_b.splice(part_b.begin(), *this, begin());
				sorted.merge(part_b);
			}
			splice(begin(), sorted);
		};

		template <class Compare>
		void quickSort(node_pointer* array, int64_t low, int64_t high, Compare comp)
		{
			int64_t		i = low;
			int64_t		j = high;
			value_type pivot = (array[(i + j) / 2])->val;
			node_pointer temp;
			while (i <= j)
			{
				while (comp((array[i])->val, pivot) && i < high) {
					i++;
				}
				while (comp(pivot, (array[j])->val) && j > low)
					j--;
				if (i <= j)
				{
					temp = array[i];
					array[i] = array[j];
					array[j] = temp;
					i++;
					j--;
				}
			}
			if (j > low)
				quickSort(array, low, j, comp);
			if (i < high)
				quickSort(array, i, high, comp);
		}

		template <class Compare>
		void sort_large(Compare comp) {
			node_pointer* head = new node_pointer[size_];
			uint i = 0;
			for (iterator it = begin(); it != end() ; ++it, ++i) {
				head[i] = it.getPointer();
			}
			pointingNew((end()).getPointer(), (end()).getPointer());
			quickSort(head, 0, size_ - 1, comp);
			for (uint j = 0; j < i ; ++j) {
				pointingNew(head[j], (end()).getPointer());
			}
			delete[] head;
		}

		void sort() {
			if (size_ <= 2000)
				sort_small();
			else
				sort_large(ft::compare<value_type>);
		};

		template <class Compare>
		void sort (Compare comp) {
			sort_large(comp);
		};

//  Sorts the elements in the list, altering their position within the container.
//
//The sorting is performed by applying an algorithm that uses either operator< (in version (1)) or comp (in version (2)) to compare elements. This comparison shall produce a strict weak ordering of the elements (i.e., a consistent transitive comparison, without considering its reflexiveness).
//
//The resulting order of equivalent elements is stable: i.e., equivalent elements preserve the relative order they had before the call.
//
//The entire operation does not involve the construction, destruction or copy of any element object. Elements are moved within the container.
	private:
		inline void	firstNode() {
			node_ = alloc_node_.allocate(1);
			//
//			alloc_.construct(&node_->val, 0);
			//
			node_->prev = node_;
			node_->next = node_;
		};

		inline void	pointingNew(node_pointer newNode, node_pointer nextNode) {
			newNode->prev = nextNode->prev;
			newNode->next = nextNode;
			if (nextNode->next == nextNode) {
				nextNode->next = newNode;
			}
			else {
				nextNode->prev->next = newNode;
			}
			nextNode->prev = newNode;
		}

		inline void	pointingPop(node_pointer prevNode, node_pointer nextNode) {
			prevNode->next = nextNode;
			nextNode->prev = prevNode;
		}

		inline void	createNode(const value_type& val, node_pointer& nextNode) {
			node_pointer newNode;
			newNode = alloc_node_.allocate(1);
			alloc_.construct(&newNode->val, val);
			pointingNew(newNode, nextNode);
		};

		inline void	createtNodes(const value_type& val, size_type n) {
			for (size_type i = 0; i < n; ++i) {
				createNode(val, node_);
			}
		};

		template <class InputIt>
		inline void	createtNodes(InputIt& first, ENABLE_IF_TYPE(InputIt)& last) {
			for (; first != last; ++first) {
				createNode(*first, node_);
			}
		};

		///
//		void merge_util(list& x, iterator& it) {
//			if (x.empty())
//				return;
/////			while(!x.empty()) {
//			for (; *it < *(x.begin()) && it != end(); ++it);
//			splice(it, x, x.begin());
/////			}
////			iterator ret_it((it.getPointer())->next);
////			iterator ret_it(begin());
//			merge_util(x, it);
//		}
///
//		bool compare(value_type& first, value_type& second) {return (first < second);}

		template <class Compare>
		void merge_util_comp(list& x, iterator& it, Compare& comp) {
			if (x.empty())
				return;
			for (;it != end(); ++it) {
				if (comp(*(x.begin()), *it))
					break;
			}
//			iterator ret_it(begin());
			splice(it, x, x.begin());
			merge_util_comp(x, it, comp);
		}

	};
}

#endif //FT_LIST_FT_LIST_HPP
