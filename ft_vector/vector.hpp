//
// Created by Gilberto Dougal on 2/26/21.
//

#ifndef FT_VECTOR_VECTOR_HPP
#define FT_VECTOR_VECTOR_HPP
#include <memory>
#include <iterator>

//	Vectors are sequence containers representing arrays that can change in size.
//	Just like arrays, vectors use contiguous storage locations for their elements,
//which means that their elements can also be accessed using offsets on regular
//pointers to its elements, and just as efficiently as in arrays. But unlike arrays,
//their size can change dynamically, with their storage being handled automatically
//by the container.
//	Internally, vectors use a dynamically allocated array to store their elements.
//This array may need to be reallocated in order to grow in size when new elements
//are inserted, which implies allocating a new array and moving all elements to it.
//This is a relatively expensive task in terms of processing time, and thus, vectors
//do not reallocate each time an element is added to the container.
//	Instead, vector containers may allocate some extra storage to accommodate for
//possible growth, and thus the container may have an actual capacity greater than
//the storage strictly needed to contain its elements (i.e., its size). Libraries
//can implement different strategies for growth to balance between memory usage and
//reallocations, but in any case, reallocations should only happen at logarithmically
//growing intervals of size so that the insertion of individual elements at the end
//of the vector can be provided with amortized constant time complexity (see push_back).
//	Therefore, compared to arrays, vectors consume more memory in exchange for the
//ability to manage storage and grow dynamically in an efficient way.
//	Compared to the other dynamic sequence containers (deques, lists and forward_lists),
//vectors are very efficient accessing its elements (just like arrays) and relatively
//efficient adding or removing elements from its end. For operations that involve inserting
//or removing elements at positions other than the end, they perform worse than the others,
//and have less consistent iterators and references than lists and forward_lists.

//Sequence
//		Elements in sequence containers are ordered in a strict linear sequence.
//Individual elements are accessed by their position in this sequence.
//Dynamic array
//		Allows direct access to any element in the sequence, even through pointer
//arithmetics, and provides relatively fast addition/removal of elements at the
//end of the sequence.
//Allocator-aware
//		The container uses an allocator object to dynamically handle its storage needs.



//	reallocate memory	: new_el + size/10 * ln(size) + size
//	allocate memory		: new_el + new_el/10 * ln(new_el)


namespace ft {
	template <class T, class Allocator = std::allocator<T> >
	class vector {
	private:
		class vectorIterator;
		typedef		T																		value_type;
		typedef		Allocator														allocator_type;
		typedef		typename Allocator::reference				reference;
		typedef		typename Allocator::const_reference	const_reference;
		typedef		typename Allocator::pointer					pointer;
		typedef		typename Allocator::const_pointer		const_pointer;
		typedef		size_t															size_type;
		typedef		std::ptrdiff_t											difference_type;
		typedef		vectorIterator											iterator;

		value_type	*vector_;
		size_type		size_;
		pointer			end_elem_;
		
		
		class vectorIterator {
		public:
			typedef		T																		iterator_type;
			typedef		std::random_access_iterator_tag			iterator_category;
			typedef		iterator_type												value_type;
			typedef		iterator_type&											reference;
			typedef		iterator_type*											pointer;
			typedef		std::ptrdiff_t											difference_type;
			//Is default-constructible, copy-constructible, copy-assignable and destructible			X a;
			//																																										X b(a);
			//																																										b = a;

			//Can be compared for equivalence using the equality/inequality operators 						a == b
			//(meaningful when both iterator values iterate over the same underlying sequence).		a != b
			//

			//Can be dereferenced as an rvalue (if in a dereferenceable state).										*a
			//																																										a->m

			//For mutable iterators (non-constant iterators):
			//Can be dereferenced as an lvalue (if in a dereferenceable state).										*a = t

			//Can be incremented (if in a dereferenceable state).																		++a
			//The result is either also dereferenceable or a past-the-end iterator.									a++
			//Two iterators that compare equal, keep comparing equal after being both increased.		*a++
			//
			//
			//
			//	Can be decremented (if a dereferenceable iterator value precedes it).
			//																																											--a
			//																																											a--
			//																																											*a--
			//	Supports the arithmetic operators + and - between an iterator and an integer value, or subtracting an iterator from another.	a + n
			//																																																																n + a
			//																																																																a - n
			//																																																																a - b

			//	Can be compared with inequality relational operators (<, >, <= and >=).																												a < b
			//																																																																a > b
			//																																																																a <= b
			//																																																																a >= b

			//	Supports compound assignment operations += and -=																																							a += n
			//																																																																a -= n
			//	Supports the offset dereference operator ([])	a[n]
		};
//const_iterator	LegacyRandomAccessIterator to const value_type
//reverse_iterator	std::reverse_iterator<iterator>
//const_reverse_iterator	std::reverse_iterator<const_iterator>
	};
}

#endif //FT_VECTOR_VECTOR_HPP