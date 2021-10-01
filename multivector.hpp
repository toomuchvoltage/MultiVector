#include <vector>
#include <string>
#include "vec3.hpp"

// (maximum G(3)) Geometric Algebra
class MultiVector
{
public:
	class Component
	{
	public:
		std::vector<char> basisBlades;
		float factor;

		Component(float inFact, std::vector<char> && inBasisBlades)
		{
			factor = inFact;
			basisBlades = inBasisBlades;
		}
		Component(float inFact, std::vector<char> & inBasisBlades)
		{
			factor = inFact;
			basisBlades = inBasisBlades;
		}
	};
	std::vector <Component> comps;

private:
	void cleanup()
	{
		for (Component & curComp : comps)
		{
			int movesToCoalesce1 = 0;
			int numBasisSameType1 = 0;

			int movesToCoalesce2 = 0;
			int numBasisSameType2 = 0;

			int numBasisSameType3 = 0;

			std::vector<char> restOfBasisBlades1;
			std::vector<char> restOfBasisBlades2;
			std::vector<char> collapsedBasisBlades;

			// Swap until 'x' blades are clumped together... and flip sign as appropriate
			for (int i = 0; i != curComp.basisBlades.size(); i++)
			{
				if (curComp.basisBlades[i] == 'x')
				{
					movesToCoalesce1 += (i - numBasisSameType1);
					numBasisSameType1++;
				}
				else
					restOfBasisBlades1.push_back(curComp.basisBlades[i]);
			}
			if (movesToCoalesce1 % 2 == 1)
				curComp.factor *= -1.0f;


			// Swap until 'y' blades are clumped together... and flip sign as appropriate
			for (int i = 0; i != restOfBasisBlades1.size(); i++)
			{
				if (restOfBasisBlades1[i] == 'y')
				{
					movesToCoalesce2 += max(i - numBasisSameType2, 0);
					numBasisSameType2++;
				}
				else
					restOfBasisBlades2.push_back(restOfBasisBlades1[i]);
			}
			if (movesToCoalesce2 % 2 == 1)
				curComp.factor *= -1.0f;


			numBasisSameType3 = (int)restOfBasisBlades2.size(); // Just 'z' left

			if (numBasisSameType1 % 2 == 1) collapsedBasisBlades.push_back('x');
			if (numBasisSameType2 % 2 == 1) collapsedBasisBlades.push_back('y');
			if (numBasisSameType3 % 2 == 1) collapsedBasisBlades.push_back('z');

			curComp.basisBlades = collapsedBasisBlades;
		}

		// Add factors with the same basis blades
		while (true)
		{
			bool foundSomething = false;
			for (int i = 0; i != comps.size(); i++)
			{
				for (int j = 0; j != comps.size(); j++)
				{
					if (i == j) continue;
					if (comps[i].basisBlades == comps[j].basisBlades)
					{
						comps[i].factor += comps[j].factor;
						comps.erase(comps.begin() + j);
						foundSomething = true;
						break;
					}
				}
				if (foundSomething) break;
			}
			if (!foundSomething) break;
		}

		// Erase components with a zero factor
		while (true)
		{
			bool foundSomething = false;
			for (int i = 0; i != comps.size(); i++)
			{
				if (comps[i].factor == 0.0f)
				{
					comps.erase(comps.begin() + i);
					foundSomething = true;
					break;
				}
			}
			if (!foundSomething) break;
		}
	}

public:

	MultiVector()
	{
	}

	// Vector as a multivector
	MultiVector(vec3 & inp1)
	{
		comps.emplace_back(Component(inp1.x, { 'x' }));
		comps.emplace_back(Component(inp1.y, { 'y' }));
		comps.emplace_back(Component(inp1.z, { 'z' }));

		cleanup();
	}

	// MultiVector resulting from geometric product of two vectors
	MultiVector(vec3 & inp1, vec3 & inp2)
	{
		vec3 i1i2 = inp1.cross(inp2);
		comps.emplace_back(Component(inp1.dot(inp2), {}));
		comps.emplace_back(Component(i1i2.x, { 'y', 'z' }));
		comps.emplace_back(Component(-i1i2.y, { 'x', 'z' }));
		comps.emplace_back(Component(i1i2.z, { 'x', 'y' }));

		cleanup();
	}

	// Geometric product of multivectors
	MultiVector operator*(const MultiVector & mv)
	{
		MultiVector retVal;
		for (Component & curComp1 : comps)
			for (unsigned int i = 0; i != mv.comps.size(); i++)
			{
				std::vector<char> combBasis = curComp1.basisBlades;
				combBasis.insert(combBasis.end(), mv.comps[i].basisBlades.begin(), mv.comps[i].basisBlades.end());
				retVal.comps.emplace_back(Component(curComp1.factor * mv.comps[i].factor, combBasis));
			}

		retVal.cleanup();

		return retVal;
	}

	// Syntactic sugar
	MultiVector & operator *=(const MultiVector & mv)
	{
		MultiVector retVal = *this * mv;
		*this = retVal;
		return *this;
	}

	// Extract the vector component
	vec3 extractVec3()
	{
		float compX = 0.0f, compY = 0.0f, compZ = 0.0f;
		for (Component & curComp : comps)
		{
			if (curComp.basisBlades == std::vector<char>({ 'x' }))
			{
				compX = curComp.factor;
			}
			else if (curComp.basisBlades == std::vector<char>({ 'y' }))
			{
				compY = curComp.factor;
			}
			else if (curComp.basisBlades == std::vector<char>({ 'z' }))
			{
				compZ = curComp.factor;
			}
		}
		return vec3(compX, compY, compZ);
	}

	std::string print()
	{
		std::string outP = "";
		for (unsigned int i = 0; i != comps.size(); i++)
		{
			outP += std::to_string(comps[i].factor) + std::string(comps[i].basisBlades.begin(), comps[i].basisBlades.end());
			if (i != (int)comps.size() - 1) outP += std::string(" + ");
		}
		return outP;
	}
};