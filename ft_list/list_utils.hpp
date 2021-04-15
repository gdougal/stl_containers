//
// Created by Gilberto Dougal on 3/19/21.
//

#ifndef FT_LIST_LIST_UTILS_HPP
#define FT_LIST_LIST_UTILS_HPP

namespace ft {

	template <typename value_type>
	struct	list_node {
	public:
		value_type									val;
		ft::list_node<value_type>*	prev;
		ft::list_node<value_type>*	next;
	};

	template <typename value_type>
	inline bool compare(const value_type& first, const value_type& second) {return (first < second);}

	template <typename value_type>
	inline bool								defaultPred(value_type& a, value_type& b) {
		return a == b;
	}
	template <typename value_type>
	inline bool								defaultRemovePred(value_type& val, value_type& ref) {
		return val == ref;
	}

}

#endif //FT_LIST_LIST_UTILS_HPP
