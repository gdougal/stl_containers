//
// Created by Gilberto Dougal on 3/15/21.
//

#ifndef FT_VECTOR_FT_UTILS_HPP
#define FT_VECTOR_FT_UTILS_HPP

namespace ft {

	struct false_type {
		char v[1];
		const static bool value = false;
	};

	struct true_type {
		false_type v[2];
		const static bool value = true;
	};

	template<class T, class U>
	struct is_ptr : false_type {
	};

	template<class T>
	struct is_ptr<T, T> : true_type {
	};

	template<class U, typename ptr>
	struct is_same {
	private:
		template<class T1>
		static uint64_t	foo(ptr* T1::* = 0) {return 0;};
		template<typename T1>
		static int			foo(T1 a = 0) {return 0;};
	public:
		const static bool value = (sizeof(foo<U>(0)) != sizeof(int)) || is_ptr<U, ptr>::value;
	};

	template<bool Cond, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> {
		typedef T type;
	};

#define ENABLE_IF_TYPE(type_ref, val_t) \
	typename ft::enable_if<ft::is_same<type_ref, val_t>::value, type_ref>::type

	template<typename Any>
	void			f_swp(Any& val, Any& ref) {
		Any	buf;
		buf = val;
		val = ref;
		ref = buf;
	};

}

#endif //FT_VECTOR_FT_UTILS_HPP
