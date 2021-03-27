//
// Created by Gilberto Dougal on 3/19/21.
//

#ifndef FT_LIST_LIST_UTILS_HPP
#define FT_LIST_LIST_UTILS_HPP

namespace ft {

	template <typename value_type>
	struct	Node {
	public:
		value_type						val;
		ft::Node<value_type>*	prev;
		ft::Node<value_type>*	next;
	};

	template <typename value_type>
	bool compare(const value_type first,const value_type second) {return (first < second);}
}

#endif //FT_LIST_LIST_UTILS_HPP
