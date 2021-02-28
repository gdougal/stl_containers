//
// Created by Gilberto Dougal on 2/24/21.
//

#ifndef FT_LIST_FT_LIST_HPP
#define FT_LIST_FT_LIST_HPP
#include <memory>



//default (1)	:		explicit list (const allocator_type& alloc = allocator_type());
//fill (2)		:		explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
//range (3)		:		template <class InputIterator> list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
//copy (4)		:		list (const list& x);

//(1)	empty container constructor (default constructor)		Constructs an empty container, with no elements.
//(2)	fill constructor																		Constructs a container with n elements. Each element is a copy of val.
//(3) range constructor																		Constructs a container with as many elements as the range [first,last),
//																												with each element constructed from its corresponding element in that range, in the same order.
//(4) copy constructor																		Constructs a container with a copy of each of the elements in x, in the same order.
//
//The container keeps an internal copy of alloc, which is used to allocate storage throughout its lifetime.
//The copy constructor (4) creates a container that keeps and uses a copy of x's allocator.
//The storage for the elements is allocated using this internal allocator.

//alloc
//				Allocator object.
//The container keeps and uses an internal copy of this allocator.
//Member type allocator_type is the internal allocator type used by the container, defined in list as an alias of its second template parameter (Alloc).
//If allocator_type is an instantiation of the default allocator (which has no state), this is not relevant.
//n
//				Initial container size (i.e., the number of elements in the container at construction).
//Member type size_type is an unsigned integral type.
//val
//				Value to fill the container with. Each of the n elements in the container is initialized to a copy of this value.
//Member type value_type is the type of the elements in the container, defined in list as an alias of its first template parameter (T).
//first, last
//				Input iterators to the initial and final positions in a range. The range used is [first,last), which includes all the elements between first and last, including the element pointed by first but not the element pointed by last.
//The function template argument InputIterator shall be an input iterator type that points to elements of a type from which value_type objects can be constructed.
//x
//				Another list object of the same type (with the same class template arguments), whose contents are either copied or acquired.
//il
//				An initializer_list object.
//These objects are automatically constructed from initializer list declarators.
//Member type value_type is the type of the elements in the container, defined in list as an alias of its first template parameter (T)



namespace ft {
		template < class T, class Alloc = std::allocator<T> >
	class list {
	public:
		T																				value_;
		std::allocator<T>												allocator_;
		
//						Members type:
//						value_type			The first template parameter (T)
//						allocator_type	The second template parameter (Alloc)	defaults to: allocator<value_type>
//		reference	allocator_type::reference	for the default allocator: value_type&
//		const_reference	allocator_type::const_reference	for the default allocator: const value_type&
//		pointer	allocator_type::pointer	for the default allocator: value_type*
//		const_pointer	allocator_type::const_pointer	for the default allocator: const value_type*
//		iterator	a bidirectional iterator to value_type	convertible to const_iterator
//const_iterator	a bidirectional iterator to const value_type
//reverse_iterator	reverse_iterator<iterator>
//const_reverse_iterator	reverse_iterator<const_iterator>
//difference_type	a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
//size_type	an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t
	};
}

#endif //FT_LIST_FT_LIST_HPP
