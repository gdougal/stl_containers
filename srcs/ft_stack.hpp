//
// Created by Gilberto Dougal on 5/1/21.
//

#ifndef FT_STACK_STACK_HPP
#define FT_STACK_STACK_HPP
#include "ft_list.hpp"
//#include <stack>

namespace ft {

	template <class T, class Container = ft::list<T> >
	class stack {
	public:
		typedef Container																	container_type;
		typedef typename	container_type::value_type			value_type;
		typedef typename	container_type::reference				reference;
		typedef typename	container_type::const_reference	const_reference;
		typedef typename	container_type::size_type				size_type;

		explicit stack(const container_type& ctnr = container_type()): container_(ctnr) {};
		virtual ~stack() {};

		bool							empty()																								const	{ return container_.empty(); };
		size_type					size()																								const	{ return container_.size(); };
		reference					top()																												{ return container_.back(); };
		const_reference		top()																									const	{ return container_.back(); };
		void							push (const value_type& val)																{ container_.push_back(val); };
		void							pop()																												{ /*container_.erase(--container_.end());*/ container_.pop_back(); };

	private:
		container_type	container_;

//		template <class T1, class Container1>
		friend bool operator== (const stack<T, container_type>& lhs, const stack<T, container_type>& rhs) {
			return lhs.container_ == rhs.container_;
		}
//		template <class T1, class Container1>
		friend bool operator< (const stack<T, container_type>& lhs, const stack<T, container_type>& rhs) {
			return lhs.container_ < rhs.container_;
		}
	};

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return !(lhs > rhs);
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return !(lhs < rhs);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return !(lhs < rhs);
	}

}
#endif //FT_STACK_STACK_HPP
