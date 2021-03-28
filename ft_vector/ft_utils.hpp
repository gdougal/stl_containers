//
// Created by Gilberto Dougal on 3/15/21.
//

#ifndef FT_VECTOR_FT_UTILS_HPP
#define FT_VECTOR_FT_UTILS_HPP

namespace ft {

	template<class U>
	struct is_same {
	private:
		template<typename T1>
		static char	foo(T1*) {return 0;};
		template<typename T1>
		static int	foo(T1) {return 0;};
	public:
		const static bool value = sizeof(foo<U>(0)) == sizeof(char);
	};

	template<bool Cond, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> {
		typedef T type;
	};

	template<typename Any>
	void			f_swp(Any& val, Any& ref) {
		Any	buf;
		buf = val;
		val = ref;
		ref = buf;
	};

#define ENABLE_IF_TYPE(type_ref) \
	typename ft::enable_if<ft::is_same<type_ref>::value, type_ref>::type

}

#endif //FT_VECTOR_FT_UTILS_HPP
