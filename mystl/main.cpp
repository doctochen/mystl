#include "util.h"
#include <iostream>


int main()
{
    // 调用隐式构造函数  
    mystl::pair<int, int> p1(1, 2);
    // 调用显式构造函数  
    mystl::pair<int, double> p2(10, 20.5);
	//std::cout << x.first << ' ' << x.second << std::endl;
	return 0;
}