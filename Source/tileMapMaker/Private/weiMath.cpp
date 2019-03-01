#include "weiMath.h"

namespace weiMath {
	float round(float number, unsigned int bits) {
		stringstream ss;
		ss << fixed << setprecision(bits) << number;
		ss >> number;
		return number;
	}
	string floatToString(float number, unsigned int bits)
	{
		string res;
		stringstream ss;
		ss << fixed << setprecision(bits) << number;
		ss >> res;
		return res;
	}
}

