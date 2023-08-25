#ifndef MYTINYSTL_TYPE_TRAITS_H_
#define MYTINYSTL_TYPE_TRAITS_H_

//这个头文件用于提取类型信息

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


/*这段代码是定义在命名空间mystl中的。它首先定义了一个帮助结构m_integral_constant，该结构是一个模板，
接受一个类型T和一个该类型的值v，并有一个静态常量成员value，其类型为const T*，值为v。

接着，它定义了一个别名模板m_bool_constant，该模板接受一个bool类型的参数，
将其转化为对应的m_integral_constant实例。

然后，它定义了两个类型别名：m_true_type和m_false_type。
它们分别对应于m_bool_constant<true>和m_bool_constant<false>的类型。

接下来的一部分代码是关于类型特征的（type traits）。首先，它进行了一个向前声明（forward declaration），
声明了一个名为pair的结构，这可能是为了后续的特化定义做准备。

然后，它定义了一个名为is_pair的结构，该结构是一个模板，接受一个类型T。默认情况下，
如果传入的类型不是pair类型，那么该结构将继承自m_false_type；如果传入的类型是pair类型，
那么该结构将特化为m_true_type。

最后，这段代码关闭了命名空间mystl的声明。

这种设计主要用于在编译时进行类型检查和特征提取，使得代码更加安全、高效和灵活。
例如，通过检查一个类型是否是pair类型，
可以在编译时决定是否可以对该类型执行某种特定的操作。*/