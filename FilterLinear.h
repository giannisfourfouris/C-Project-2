#include "Vec3.h"
#include "Array.h"
#include "Filter.h"
#include <vector>
#include <math.h>       /* pow */
using namespace math;
using namespace std; 
using namespace imaging;
class FilterLinear : public Filter {

private:
	Vec3<float> a, c;


public:

	FilterLinear() { //default
		a = 0;
		c = 0;
	}


	FilterLinear(const FilterLinear & f) :Filter(f) {}; //copy constructor

	FilterLinear(Vec3<float> a, Vec3<float> c) {
		this->a = a;
		this->c = c;
	}
	//setters and getters
	void seta(Vec3<float> a) {
		this->a = a;
	}

	Vec3<float> geta()
	{
		return a;
	}

	void setc(Vec3<float> c) {
		this->c = c;
	}

	Vec3<float> getc()
	{
		return c;
	}

	virtual Image operator << (const Image & image)
	{
		Image item(image);//φτιαχνει ενα αντικειμενο τυπου image
		for (int i = 0; i < image.getWidth(); i++)
			for (int j = 0; j < image.getHeight(); j++)
			{
				Vec3<float> items = image.getRate(i, j);
				items=a*items + c;
				items = items.clampToUpperBound(1.0f);//χρησιμοποιει τις clampToUpperBound και clampToLowerBound για να ειναι στο διαστημα(0.0,1.0
				items = items.clampToLowerBound(0.0f);
				item.setRate(i, j, items);

			}
		return item;
	}
};