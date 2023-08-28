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


}


#endif