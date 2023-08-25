#ifndef MYTINYSTL_UTIL_H_
#define MYTINYSTL_UTIL_H_

// 这个文件包含一些通用工具，包括 move, forward, swap 等函数，以及 pair 等

#include <cstddef>
#include <iostream>
#include "type_traits.h"


namespace mystl
{
	//move
	template <class T>
	typename std::remove_reference<T>::type&& move(T&& arg)noexcept
	{
		return static_cast<typename std::remove_reference<T>::type&&>(arg);
	}

	//forward

	template <class T>
	T&& forward(typename std::remove_reference<T>::type& arg)noexcept
	{
		return static_cast<T&&> (arg);
	}

	template <class T>
	T&& forward(typename std::remove_reference<T>::type&& arg)noexcept
	{
		static_assert(!std::is_lvalue_reference<T>::value, "bad forward");
		return static_cast<T&&> (arg);
	}


	//swap
	template <class Tp>
	void swap(Tp& lhs, Tp& rhs)
	{
		auto tmp(mystl::move(lhs));
		lhs = mystl::move(rhs);
		rhs = mystl::move(tmp);
	}

	template <class ForwardIter1, class ForwardIter2>
	ForwardIter2 swap_range(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2)
	{
		for (; first1 != last1; first1++, (void)first2++)
			mystl::swap(*first1, *first2);
		return first2;
	}

	template <class Tp, size_t N>
	void swap(Tp(&a)[N], Tp(&b)[N])
	{
		mystl::swap_range(a, a + N, b);
	}


	// 结构体模板 : pair
	// 两个模板参数分别表示两个数据的类型
	// 用 first 和 second 来分别取出第一个数据和第二个数据

	template <class Ty1, class Ty2>
	struct pair
	{
		typedef Ty1    first_type;
		typedef Ty2    second_type;

		first_type first;   //保存第一个数据
		second_type second; //保存第二个数据

		//default constructiable
		template <class Other1 = Ty1, class Other2 = Ty2,
			typename = typename std::enable_if<    //检查是否可以默认构造Ty1和Ty2
			std::is_default_constructible<Other1>::value&&
			std::is_default_constructible<Other2>::value, void>::type>
		constexpr pair()
			:first(), second()
		{
		};

		// implicit constructiable for this type
		template <class U1 = Ty1, class U2 = Ty2,
			typename std::enable_if<
			std::is_copy_constructible<U1>::value&&
			std::is_copy_constructible<U2>::value&&
			std::is_convertible<const U1&, Ty1>::value&&
			std::is_convertible<const U2&, Ty2>::value, int>::type = 0>
		constexpr pair(const Ty1& a, const Ty2& b)
			: first(a), second(b)
		{
		}

		// explicit construcible for this type
		template <class U1 = Ty1, class U2 = Ty2,
			typename std::enable_if<
			std::is_copy_constructible<U1>::value&&
			std::is_copy_constructible<U2>::value &&
			(!std::is_convertible<const U1&, Ty1>::value ||
				!std::is_convertible<const U2&, Ty2>::value), int>::type = 0>
		explicit constexpr pair(const Ty1& a, const Ty2& b)
			:first(a), second(b)
		{
		}
	};
}


#endif