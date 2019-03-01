#pragma once

//个人的数学库

#include <iostream>
#include <sstream>
#include <iomanip>

namespace weiMath {
	using namespace std;

	//对输入参数number进行bit位的小数的四舍五入保留
	float round(float number, unsigned int bits);
	
}


