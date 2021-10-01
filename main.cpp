#include "multivector.hpp"
#include <iostream>

int main()
{
	float rotAngle = 0.2f * (float)M_PI;
	vec3 _u = vec3(sinf(0.0f), 0.0f, cosf(0.0f));
	vec3 _v = vec3(sinf(rotAngle), 0.0f, cosf(rotAngle));
	vec3 rotateThis = vec3(1.0f, 0.5f, 1.0f);
	std::cout << "The original vector is: " << rotateThis.print() << "\n";
	MultiVector _uv(_u, _v);
	MultiVector _vu(_v, _u);
	MultiVector _w(rotateThis);
	MultiVector vuwuv = _vu * _w * _uv;
	std::cout << "The new multi-vector is: " << vuwuv.print() << "\n";
	vec3 twiceRotated = vuwuv.extractVec3();
	vec3 twiceRotatedVerify = Spin(_u.cross(_v), rotateThis, rotAngle * 2.0f);
	std::cout << "Extracted vector: " << twiceRotated.print() << "\n";
	std::cout << "Twice rotated (by other means): " << twiceRotatedVerify.print() << "\n";
	return 0;
}