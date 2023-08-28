#ifndef MYTINYSTL_ALGOBASE_H_
#define MYTINYSTL_ALGOBASE_H_

//���ͷ�ļ�������stl�Ļ����㷨

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


	// max ȡ�����еĽϴ�ֵ���������ʱ��֤���ص�һ������
	template <class T>
	const T& max(const T& lhs, const T& rhs)
	{
		return lhs < rhs ? rhs : lhs;
	}

	//���ذ汾ʹ�ú�������comp�����Ƚϲ���
	template <class T, class Compare>
	const T& max(const T& lhs, const T& rhs, Compare comp)
	{
		return comp(lhs, rhs) ? rhs : lhs;
	}

	//min ȡ�����еĽ�Сֵ���������ʱ��֤���ص�һ������
	template <class T>
	const T& min(const T& lhs, const T& rhs)
	{
		return rhs < lhs ? rhs : lhs;
	}

	// ���ذ汾ʹ�ú������� comp ����Ƚϲ���
	template <class T, class Compare>
	const T& min(const T& lhs, const T& rhs, Compare comp)
	{
		return comp(rhs, lhs) ? rhs : lhs;
	}

	//iter_swap��������������ָ�Ķ���Ե�
	template<class FIter1, class FIter2>
	void iter_swap(FIter1 lhs, FIter2 rhs)
	{
		mystl::swap(*lhs, *lhs)
	}

	//copy��[first, last]�����Ԫ�ؿ�����[resoult, resoult + (last - first)]��
	//input_iterator_tag�汾
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