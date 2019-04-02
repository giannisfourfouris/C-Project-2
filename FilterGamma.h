#include "Vec3.h"
#include "Array.h"
#include "Filter.h"
#include <vector>
#include <math.h>       /* pow */
using namespace math;
using namespace std; 
using namespace imaging;
class FilterGamma : public Filter {

private:
	double y ;
public:
    
	FilterGamma() { y = 0; }//default constructor

	FilterGamma(double y) {
		this->y = y;
	}
	
	FilterGamma(const FilterGamma & f):Filter(f) {}; //copy constructor

	void setG(double y) {//setter
		this->y = y;
	}

	double gety()//getter
	{
		return y;
	}

	virtual Image operator << (const Image & image)
	{
		Image item(image);
		for (int i = 0; i < image.getWidth(); i++)//για καθε καναλι χρωματος κανει την πραξη p(x,y)^y  και στο τελος επιστρεφει τον item	
			for (int j = 0; j < image.getHeight(); j++)
			{
				Vec3<float> items = image.getRate(i, j);
				items.x = pow(items.x, y);  //to pow einai to ^
				items.y = pow(items.y, y);    //p'(x,y)=p(x,y)^y
				items.z = pow(items.z, y);
				items = items.clampToUpperBound(1.f);  // Clamps all coordinates so that they are at most val
				items = items.clampToLowerBound(0.f); // Clamps all coordinates so that they are at least val
				item.setRate(i, j, items);
			}
		return item;
			
	}
};

