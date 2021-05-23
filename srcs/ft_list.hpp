//
// Created by Gilberto Dougal on 3/19/21.
//

#ifndef FT_LIST_FT_LIST_HPP
#define FT_LIST_FT_LIST_HPP
#include <memory>
#include "ft_utils/ft_utils.hpp"

namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class list {
	public:
		typedef	T																													value_type;
		typedef	Alloc																											allocator_type;
		typedef	size_t																										size_type;
		typedef	std::ptrdiff_t																						difference_type;
		typedef	typename allocator_type::pointer													pointer;
		typedef	typename allocator_type::reference												reference;
		typedef	typename allocator_type::const_pointer										const_pointer;
		typedef	typename allocator_type::const_reference									const_reference;

	private:
		typedef	list_util::list_node<value_type>													Node_;
		typedef	typename allocator_type:: template rebind<Node_>::other		alloc_node;
		typedef	typename alloc_node::pointer															node_pointer;

		node_pointer		node_;
		size_type				size_;
		allocator_type	alloc_;
		alloc_node			alloc_node_;

	public:
		typedef		list_util::listIterator<value_type, Node_>							iterator;
		typedef		list_util::constListIterator<value_type, Node_>					const_iterator;
		typedef		gu::reverse_it<iterator>																reverse_iterator;
		typedef		gu::const_reverse_it<iterator>													const_reverse_iterator;


		explicit				list(const allocator_type& alloc = allocator_type()) :
		node_(nullptr),
		size_(0),
		alloc_(alloc) {
			firstNode();
		}

		explicit				list(size_type n, const value_type& val = value_type(),
									 const allocator_type& alloc = allocator_type()) :
		size_(0),
		alloc_(alloc) {
			firstNode(val);
			createtNodes(val, n);
		};

		template <class InputIt>
		list(InputIt first, InputIt last, const allocator_type& alloc = allocator_type(),
			 ENABLE_IF_TYPE(InputIt)):
			size_(0),
			alloc_(alloc)
			{
			firstNode();
			createtNodes(first, last);
		};

										list(const list& x):
			size_(0) {
			firstNode();
			*this = x;
//			size_ = x.size();
		};

										~list() {
			clear();
			alloc_node_.deallocate(node_, 1);
		};

		list& 					operator=(const list& x) {
			if (this == &x)
				return *this;
			clear();
			createtNodes(x.begin(), x.end());
//			size_ = x.size();
			return *this;
		};

		reverse_iterator				rbegin()					{ return  reverse_iterator(end()); };
		const_reverse_iterator	rbegin()		const	{ return const_reverse_iterator(end()); };
		reverse_iterator				rend()						{ return reverse_iterator(begin()); };
		const_reverse_iterator	rend()			const	{ return const_reverse_iterator(begin()); };
		iterator								begin()						{ return iterator(node_->next); };
		const_iterator					begin()			const	{ return const_iterator(iterator(node_->next)); };
		iterator								end()							{ return iterator(node_); };
		const_iterator					end()				const	{ return const_iterator(node_); };
		bool										empty()			const	{ return size_ == 0; };
		size_type								size()			const	{ return size_; };
		size_type								max_size()	const	{ return (UINT64_MAX)/(sizeof(Node_)); };
		reference								front() 					{ return node_->next->val; };
		const_reference					front()			const	{ return node_->next->val; };
		reference								back()						{ return node_->prev->val; };
		const_reference					back()			const	{ return node_->prev->val; };

		template <class InputIt>
		void						assign(InputIt first, InputIt last, ENABLE_IF_TYPE(InputIt)) {
			clear();
			createtNodes(first, last);
		};

		void						assign(size_type n, const value_type& val) {
			clear();
			createtNodes(val, n);
		};

		void						push_back(const value_type& val) {
			createNode(val, node_);
		};

		void						pop_back() {
			node_pointer cur = node_->prev;
			pointingPop(cur->prev, node_);
			alloc_.destroy(&cur->val);
			alloc_node_.deallocate(cur, 1);
			--size_;
		};

		void						push_front(const value_type& val) {
			createNode(val, node_->next);
		};

		void						pop_front() {
			node_pointer cur = node_->next;
			pointingPop(node_, cur->next);
			alloc_.destroy(&cur->val);
			alloc_node_.deallocate(cur, 1);
			--size_;
		};

		iterator				insert(iterator position, const value_type& val) {
			createNode(val, position.getPointer());
			return --position;
		};

		void						insert(iterator position, size_type n, const value_type& val) {
			if (!n)
				return ;
			insert(position, val);
			insert(position, --n, val);
		};

		template <class InputIt>
		void						insert(iterator position, InputIt first, InputIt last, ENABLE_IF_TYPE(InputIt)) {
			if (first == last)
				return ;
			insert(position, *(first));
			insert(position, ++first, last);
		};

		iterator				erase(iterator position) {
			if (empty() || position == end())
				return end();
			iterator ret((position.getPointer())->next);
			alloc_.destroy(position.operator->());
			pointingPop((position.getPointer())->prev, (position.getPointer())->next);
			alloc_node_.deallocate(position.getPointer(), 1);
			--size_;
			return ret;
		};

		iterator				erase(iterator first, iterator last) {
			while ((first = erase(first)) != last);
			return last;
		};

		void						clear() { erase(begin(), end()); };

		void						resize(size_type n, value_type val = value_type()) {
			if (n == size_)
				return ;
			if (n < size_) {
				iterator it = begin();
				for (size_type i = 0; i < n; ++i, ++it);
				erase(it, end());
			}
			else {
				while (size_ < n)
					push_back(val);
			}
		};

		void						swap(list& x) {
			gu::f_swp(size_, x.size_);
			gu::f_swp(node_, x.node_);
			gu::f_swp(alloc_, x.alloc_);
			gu::f_swp(alloc_node_, x.alloc_node_);
		};

		void						splice(iterator position, list& x) {
			pointingPop((position.getPointer())->prev, (x.begin()).getPointer());
			pointingPop((x.end()).getPointer()->prev, position.getPointer());
			size_ += x.size();
			x.pointingPop(x.node_, x.node_);
			x.size_ = 0;
		};

		void						splice(iterator position, list& x, iterator i) {
			node_pointer cur = i.getPointer();
			x.pointingPop(cur->prev, cur->next);
			pointingNew(cur, position.getPointer());
			++size_;
			x.size_ -= 1;
		};

		void						splice(iterator position, list& x, iterator first, iterator last) {
			if (x.empty())
				return;
			size_type	p_size = static_cast<size_type>(std::distance(first, last));
			if (p_size <= 0)
				return;
			node_pointer		firstPrev_p = (first.getPointer())->prev;
			node_pointer		lastPrev_p = (last.getPointer())->prev;
			node_pointer		last_p = last.getPointer();
			node_pointer		first_p = first.getPointer();
			x.pointingPop(firstPrev_p, last_p);
			pointingPop((position.getPointer())->prev, first_p);
			pointingPop(lastPrev_p, position.getPointer());
			size_ += p_size;
			x.size_ -= p_size;
		};

		void						remove(const value_type& val) {
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
		void							remove_if(Predicate pred) {
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

		void								unique()			{ unique(list_util::defaultPred<value_type>); };

		template <class BinaryPredicate>
		void								unique(BinaryPredicate binary_pred) {
			iterator it_cur(node_->next->next);
			iterator it_prev(node_->next);
			while (it_cur != end()) {
				if (binary_pred(*it_prev, *it_cur)) {
					it_cur = erase(it_cur);
					continue;
				}
				++it_cur;
				++it_prev;
			}
		};

		void								merge (list& x)	{ merge(x, list_util::compare<value_type>); };

		template <class Compare>
		void 								merge (list& x, Compare comp) {
			if (this == &x)
				return ;
			iterator it(begin());
			merge_util_comp(x, it, comp);
		};

		void								sort() {
			if (!empty()) {
				sort_large(list_util::compare<value_type>);
			}
		};

		template <class Compare>
		void								sort (Compare comp) {sort_large(comp);};

		void reverse()	{
			for (iterator it = begin(); it != end(); --it) {
				gu::f_swp((it.getPointer())->prev, (it.getPointer())->next);
			}
			gu::f_swp((end().getPointer())->prev, (end().getPointer())->next);
		};

	private:
		void			firstNode(value_type ref = value_type()) {
			node_ = alloc_node_.allocate(1);
			alloc_.construct(&node_->val, ref);
			node_->prev = node_;
			node_->next = node_;
		};

		void			pointingNew(node_pointer newNode, node_pointer nextNode) {
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

		void				pointingPop(node_pointer prevNode, node_pointer nextNode) {
			prevNode->next = nextNode;
			nextNode->prev = prevNode;
		}

		void				createNode(const value_type& val, const node_pointer& nextNode) {
			node_pointer newNode;
			newNode = alloc_node_.allocate(1);
			alloc_.construct(&newNode->val, val);
			pointingNew(newNode, nextNode);
			++size_;
		};

		void				createtNodes(const value_type& val, size_type n) {
			for (size_type i = 0; i < n; ++i) {
				createNode(val, node_);
			}
		};

		template <class InputIt>
		inline void	createtNodes(InputIt& first, InputIt& last, ENABLE_IF_TYPE(InputIt)) {
			for (; first != last; ++first) {
				createNode(*first, node_);
			}
		};

		inline void	createtNodes(const_iterator first, const_iterator last) {
			if(first == last)
				return;
			createNode(*first, node_);
			createtNodes(++first, last);
		};

		template <class Compare>
		void				merge_util_comp(list& x, iterator& it, Compare& comp) {
			if (x.empty())
				return;
			for (;it != end(); ++it) {
				if (comp(*(x.begin()), *it))
					break;
			}
			splice(it, x, x.begin());
			merge_util_comp(x, it, comp);
		}

		template <class Compare>
		void				quickSort(node_pointer* array, int64_t low, int64_t high, Compare comp)
		{
			int64_t		i = low;
			int64_t		j = high;
			value_type pivot = (array[(i + j) / 2])->val;
			node_pointer temp;
			while (i <= j)
			{
				while (comp((array[i])->val, pivot)) {
					if (!((array[i])->val > pivot) && !((array[i])->val < pivot))
						break;
					i++;
				}
				while (comp(pivot, (array[j])->val) && j > low) {
					if (!((array[j])->val > pivot) && !((array[j])->val < pivot))
						break;
					j--;
				}
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
		void			sort_large(Compare comp) {
			node_pointer* head = new node_pointer[size_];
			size_type i = 0;
			for (iterator it = begin(); it != end() ; ++it, ++i) {
				head[i] = it.getPointer();
			}
			pointingNew((end()).getPointer(), (end()).getPointer());
			quickSort(head, 0, static_cast<int64_t>(size_ - 1), comp);
			for (size_type j = 0; j < i ; ++j) {
				pointingNew(head[j], (end()).getPointer());
			}
			delete[] head;
		}

	};

	template <class T, class Alloc>
	bool				operator==(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		if (lhs.size() == rhs.size()) {
			return std::equal(lhs.begin(), lhs.end(), rhs.begin());
		}
		return false;
	}

	template <class T, class Alloc>
	bool				operator!=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (!(ft::operator==(lhs, rhs)));
	}

	template <class T, class Alloc>
	bool				operator<(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool				operator>(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return std::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template <class T, class Alloc>
	bool				operator<=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (!(ft::operator>(lhs, rhs)));
	}

	template <class T, class Alloc>
	bool				operator>=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (!(ft::operator<(lhs, rhs)));
	}

	template <class T, class Alloc>
	void				swap (list<T,Alloc>& x, list<T,Alloc>& y) {
		x.swap(y);
	}
}

#endif //FT_LIST_FT_LIST_HPP
