#ifndef MYTINYSTL_ALGOBASE_H_
#define MYTINYSTL_ALGOBASE_H_

//这个头文件定义了stl的基本算法

#include <cstring>
#include "iterator.h"
#include "util.h"

namespace mystl
{
#ifdef max
#pragma message("#undefing marco max")
#undef max
#endif // max

#ifdef min
#pragma message("#undefing marco min")
#undef min
#endif // min


	// max 取二者中的较大值，语义相等时保证返回第一个参数
	template <class T>
	const T& max(const T& lhs, const T& rhs)
	{
		return lhs < rhs ? rhs : lhs;
	}

	//重载版本使用函数对象comp来做比较操作
	template <class T, class Compare>
	const T& max(const T& lhs, const T& rhs, Compare comp)
	{
		return comp(lhs, rhs) ? rhs : lhs;
	}

	//min 取二者中的较小值，语义相等时保证返回第一个参数
	template <class T>
	const T& min(const T& lhs, const T& rhs)
	{
		return rhs < lhs ? rhs : lhs;
	}

	// 重载版本使用函数对象 comp 代替比较操作
	template <class T, class Compare>
	const T& min(const T& lhs, const T& rhs, Compare comp)
	{
		return comp(rhs, lhs) ? rhs : lhs;
	}

	//iter_swap将两个迭代器所指的对象对调
	template<class FIter1, class FIter2>
	void iter_swap(FIter1 lhs, FIter2 rhs)
	{
		mystl::swap(*lhs, *lhs)
	}

	//copy把[first, last]区间的元素拷贝到[resoult, resoult + (last - first)]内
	//input_iterator_tag版本
	template <class InputIerator, class OutputIterator>
	OutputIterator uncheck_copy_cat(InputIerator first, InputIerator last,
		OutputIterator resoult, mystl::input_iterator_tag)
	{
		for (; first != last; ++first, ++resoult)
		{
			*resoult = *first;
		}
		return resoult;
	}

	//random_access_iterator_tag版本
	template <class RandomIter, class OutputIter>
	OutputIter uncheck_copy_cat(RandomIter first, RandomIter last,
		OutputIter result, mystl::random_access_iterator_tag)
	{
		for (auto n = last - first; n > 0; --n, first++, result++)
		{
			*result = *first;
		}
		return result;
	}

	template <class InputIter, class OutputIter>
	OutputIter uncheck_copy(InputIter first, InputIter last, OutputIter result)
	{
		return uncheck_copy_cat(first, last, result, iterator_category(first));
	}

	//为 trivially_copy_assignable 类型提供特化版本
	template <class Tp, class Up>
	typename std::enable_if<
		std::is_same<typename std::remove_const<Tp>::type, Up>::value&&
		std::is_trivially_copy_assignable<Up>::value,
		Up*>::type
		uncheck_copy(Tp* first, Tp* last, Up* result)
	{
		int n = static_cast<size_t> (last - first);
		if (n != 0)
			std::memmove(result, first, n * sizeof(Up));
		return result + n;	
	}


	template <class InputIter, class OutputIter>
	OutputIter copy(InputIter first, InputIter last, OutputIter result)
	{
		return uncheck_copy(first, last, result);
	}


	//把[first, second]拷贝到[result - (last - first), result]
	template <class BidirectionalIter1, class BidirectionalIter2>
	BidirectionalIter2 uncheck_copy_backward_cat(BidirectionalIter1 first,
		BidirectionalIter1 last, BidirectionalIter2 result, mystl::bidirectional_iterator_tag)
	{
		while (first != last)
		{
			*--result = *--last;
		}
		return result;
	}


	template <class RandomIter1, class BidrectionalIter2>
	BidrectionalIter2 uncheck_copy_backward_cat(RandomIter1 first,
		RandomIter1 last, BidrectionalIter2 result, mystl::random_access_iterator_tag)
	{
		for (int n = (last - first); n > 0; n--)
		{
			*--result = *--last;
		}
		return result;
	}

	template <class BidrectionalIter1, class BidrectionalIter2>
	BidrectionalIter2 uncheck_copy_backward(BidrectionalIter1 first,
		BidrectionalIter1 last, BidrectionalIter2 result)
	{
		return uncheck_copy_backward_cat(first, last, result, iterator_category(first));
	}


	template <class Tp, class Up>
	typename std::enable_if<
		std::is_same<typename std::remove_const<Tp>::type, Up>::value&&
		std::is_trivially_copy_assignable<Up>::value,
		Up*>::type
		unchecked_copy_backward(Tp* first, Tp* last, Up* result)
	{
		const auto n = static_cast<size_t>(last - first);
		if (0 != n)
		{
			result -= n;
			std::memmove(result, first, n * sizeof(Up));
		}
		return result;
	}

	template <class BidirectionalIter1, class BidirectionalIter2>
	BidirectionalIter2
		copy_backward(BidirectionalIter1 first, BidirectionalIter1 last,
			BidirectionalIter2 result)
	{
		return unchecked_copy_backward(first, last, result);
	}

	/*
	* copy_if 把（first， last）内的元素拷贝到result开始的位置
	*/
	template <class InputIter, class OutputIter, class UnaryPredicate>
	OutputIter
		copy_if(InputIter first, InputIter last, OutputIter result,
			UnaryPredicate unary_pred)
	{
		for (; first != last; ++first)
		{
			if (unary_pred(*first))
			{
				*result++ = *first;
			}
		}
		return result;
	}

	//copy_n把区间[first, first + n)的元素都拷贝到[result, result + n)上
	template <class InputIter, class Size, class OutputIter>
	mystl::pair<InputIter, OutputIter>
		unchecked_copy_n(InputIter first, Size n, OutputIter result, mystl::input_iterator_tag)
	{
		for (; n > 0; first++, result++)
		{
			*result = *first;
		}
		return mystl::pair<InputIter, OutputIter>(first, result);
	}

	template <class RandomIter, class OutputIter, class Size>
	mystl::pair<RandomIter, OutputIter>
		unchecked_copy_n(RandomIter first, Size n, OutputIter result,
			mystl::random_access_iterator_tag)
	{
		auto last = first + n;
		return pair<last, mystl::copy(first, last, result)>;
	}

	template <class InputIter, class Size, class OutputIter>
	mystl::pair<InputIter, OutputIter>
		copy_n(InputIter first, Size n, OutputIter result)
	{
		return unchecked_copy_n(first, n, result, iterator_category(first));
	}


	//move操作，把first~last 移动到 result ~ result + (last - first)
	template <class InputIter, class OutputIter>
	OutputIter unchecked_move_cat(InputIter first, InputIter last, OutputIter result,
		mystl::input_iterator_tag)
	{
		for (; first != last; result, first++)
		{
			*result = mystl::move(*first);
		}
		return result;
	}

}


#endif