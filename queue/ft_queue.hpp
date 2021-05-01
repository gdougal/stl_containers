//
// Created by Gilberto Dougal on 5/1/21.
//

#ifndef QUEUE_FT_QUEUE_HPP
#define QUEUE_FT_QUEUE_HPP


#include "../ft_list/ft_list.hpp"

namespace ft {

	template <class T, class Container = ft::list<T> >
	class queue {
	public:
		typedef Container																	container_type;
		typedef typename	container_type::value_type			value_type;
		typedef typename	container_type::reference				reference;
		typedef typename	container_type::const_reference	const_reference;
		typedef typename	container_type::size_type				size_type;

		explicit queue(const container_type& ctnr = container_type()): container_(ctnr) {};
		virtual ~queue() {};

		bool							empty()																								const	{ return container_.empty(); };
		size_type					size()																								const	{ return container_.size(); };
		reference					front()																												{ return container_.front(); };
		const_reference		front()																									const	{ return container_.front(); };
		void							push (const value_type& val)																{ container_.push_back(val); };
		void							pop()																												{ /*container_.erase(--container_.end());*/ container_.pop_front(); };

	private:
		container_type	container_;

		template <class T1, class Container1>
		friend bool operator== (const queue<T1,Container1>& lhs, const queue<T1,Container1>& rhs) {
			return lhs.container_ == rhs.container_;
		}
		template <class T1, class Container1>
		friend bool operator< (const queue<T1,Container1>& lhs, const queue<T1,Container1>& rhs) {
			return lhs.container_ == rhs.container_;
		}
	};

	template <class T, class Container>
	bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return !(lhs > rhs);
	}

	template <class T, class Container>
	bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return !(lhs < rhs);
	}

	template <class T, class Container>
	bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return !(lhs < rhs);
	}

}


#endif //QUEUE_FT_QUEUE_HPP
