#include <cmath>

#define M_PI 3.1415926535
#define max(x,y) (x > y ? x : y)

class vec3
{
	public:
		float x,y,z;
	
		vec3 ()
		{
		}
		
		vec3 (float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		
		float dot (const vec3 & rhs)
		{
			return x * rhs.x + y * rhs.y + z * rhs.z;
		}
		
		vec3 cross (const vec3 & rhs)
		{
			return vec3(y*rhs.z - z*rhs.y,
						z*rhs.x - x*rhs.z,
						x*rhs.y - y*rhs.x);
		}
		
		vec3 normalized ()
		{
			float len = sqrtf ((x*x) + (y*y) + (z*z));
			return vec3 (x/len, y/len, z/len);
		}
		
		vec3 operator+(const vec3 & rhs)
		{
			return vec3 (x + rhs.x, y + rhs.y, z + rhs.z);
		}

		vec3& operator+=(const vec3 & rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		vec3 operator-(const vec3 & rhs)
		{
			return vec3 (x - rhs.x, y - rhs.y, z - rhs.z);
		}

		vec3& operator-=(const vec3 & rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		vec3& operator*=(const float rhs)
		{
			x *= rhs;
			y *= rhs;
			z *= rhs;
			return *this;
		}

		vec3& operator/=(const float rhs)
		{
			x /= rhs;
			y /= rhs;
			z /= rhs;
			return *this;
		}

		std::string print()
		{
			return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
		}
};

vec3 operator*(const float lhs, const vec3 & rhs)
{
	return vec3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

vec3 operator*(const vec3 & lhs, const float rhs)
{
	return vec3(rhs * lhs.x, rhs * lhs.y, rhs * lhs.z);
}

vec3 operator/(const float lhs, const vec3 & rhs)
{
	return vec3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
}

vec3 operator/(const vec3 & lhs, const float rhs)
{
	return vec3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

vec3 Spin(vec3 axis, vec3 vec, float angle)
{
	vec3 axis_n = axis.normalized();
	float shadow = axis_n.dot(vec);
	vec3 bring_down = shadow * axis_n;
	vec3 plane_pt = vec - bring_down;

	vec3 X = plane_pt.normalized();
	vec3 Y = axis_n.cross(X);

	float pt_x = plane_pt.dot(X);
	float new_pt_x = cosf(angle)*pt_x;
	float new_pt_y = sinf(angle)*pt_x;

	return ((new_pt_x)*X) + ((new_pt_y)*Y) + bring_down;
}