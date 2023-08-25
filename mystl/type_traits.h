#ifndef MYTINYSTL_TYPE_TRAITS_H_
#define MYTINYSTL_TYPE_TRAITS_H_

//���ͷ�ļ�������ȡ������Ϣ

#include <type_traits>


namespace mystl
{
	//help struct
	template<class T, T v>
	struct m_integral_constant
	{
		static constexpr T value = v;
	};

	template<bool b>
	using m_bool_constant = m_integral_constant<bool, b>;

	typedef m_bool_constant<true> m_true_type;
	typedef m_bool_constant<false> m_false_type;

	/*****************************************************************************************/
	// type traits

	// is_pair

	// --- forward declaration begin
	template <class T1, class T2>
	struct pair;
	// --- forward declaration end

	template <class T>
	struct is_pair : mystl::m_false_type {};

	template <class T1, class T2>
	struct is_pair<mystl::pair<T1, T2>> : mystl::m_true_type {};
}  //namespace mystl


#endif // !MYTINYSTL_TYPE_TRAITS_H_


/*��δ����Ƕ����������ռ�mystl�еġ������ȶ�����һ�������ṹm_integral_constant���ýṹ��һ��ģ�壬
����һ������T��һ�������͵�ֵv������һ����̬������Աvalue��������Ϊconst T*��ֵΪv��

���ţ���������һ������ģ��m_bool_constant����ģ�����һ��bool���͵Ĳ�����
����ת��Ϊ��Ӧ��m_integral_constantʵ����

Ȼ�����������������ͱ�����m_true_type��m_false_type��
���Ƿֱ��Ӧ��m_bool_constant<true>��m_bool_constant<false>�����͡�

��������һ���ִ����ǹ������������ģ�type traits�������ȣ���������һ����ǰ������forward declaration����
������һ����Ϊpair�Ľṹ���������Ϊ�˺������ػ�������׼����

Ȼ����������һ����Ϊis_pair�Ľṹ���ýṹ��һ��ģ�壬����һ������T��Ĭ������£�
�����������Ͳ���pair���ͣ���ô�ýṹ���̳���m_false_type����������������pair���ͣ�
��ô�ýṹ���ػ�Ϊm_true_type��

�����δ���ر��������ռ�mystl��������

���������Ҫ�����ڱ���ʱ�������ͼ���������ȡ��ʹ�ô�����Ӱ�ȫ����Ч����
���磬ͨ�����һ�������Ƿ���pair���ͣ�
�����ڱ���ʱ�����Ƿ���ԶԸ�����ִ��ĳ���ض��Ĳ�����*/