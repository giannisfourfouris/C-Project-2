#ifndef _FILTER
#define _FILTER
#include "Image.h"
#include "Vec3.h"
#include "Array.h"
#include <vector>
#include <math.h>       /* pow */
using namespace math;
using namespace std; 
using namespace imaging;

class Filter {
public:

	Filter() {}//default 
	
	Filter(const Filter & f) {}//copy 

	virtual Image operator << (const Image & image) = 0; //operator <<. Epeidh h methodos einai pure virtual gia ayto to (methodos=0) 

};
#endif