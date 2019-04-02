#ifndef _ARRAY
#define _ARRAY

#include "Vec3.h"
#include <string>
#include <vector>




/*! The imaging namespace contains every class or function associated with the image storage, compression and manipulation.
 */
using namespace std;
using namespace imaging;


//------------------------------------ class Array ------------------------------------------------

	/*! It is the class that represents a generic data container for an image.
	 *
	 * It holds the actual buffer of the pixel values and provides methods for accessing them,
	 * either as individual pixels or as a memory block. The Image class alone does not provide
	 * any functionality for loading and storing an image, as it is the result or input to such a procedure.
	 *
	 * The internal buffer of an image object stores the actual bytes (data) of the color image as
	 * a contiguous sequence of Color structures. Hence, the size of the buffer variable holding these data is
	 * width X height X sizeof(Color) bytes.
	 *
	 * All values stored in the Color data type components are assumed to be floating point values and for typical (normalized)
	 * intensity ranges, each color component is within the range [0.0, 1.0].
	 */
namespace math {
	template<class T>
	class Array
	{
	public:

	protected:
		vector<T>  buffer;                              //! Holds the image data.

		unsigned int width, 						 //! The width of the image (in pixels)
			height;		                 //! The height of the image (in pixels)

	public:
		// metric accessors

		/*! Returns the width of the image
		 */
		const unsigned int getWidth() const { return width; }

		/*! Returns the height of the image
		 */
		const unsigned int getHeight() const { return height; }

		// data accessors

		/*! Obtains a pointer to the internal data.
		 *
		 *  This is NOT a copy of the internal image data, but rather a pointer
		 *  to the internally allocated space, so DO NOT attempt to delete the pointer.
		 */
		vector<T>  getRawDataPtr();

		/*! Obtains the color of the image at location (x,y).
		 *
		 *  The method should do any necessary bounds checking.
		 *
		 *  \param x is the (zero-based) horizontal index of the pixel to get.
		 *  \param y is the (zero-based) vertical index of the pixel to get.
		 *
		 *  \return The color of the (x,y) pixel as a Color object. Returns a black (0,0,0) color in case of an out-of-bounds x,y pair.
		 */
		T getRate(unsigned int x, unsigned int y) const;

		// data mutators

		/*! Sets the RGB values for an (x,y) pixel.
		 *
		 *  The method should perform any necessary bounds checking.
		 *
		 *  \param x is the (zero-based) horizontal index of the pixel to set.
		 *  \param y is the (zero-based) vertical index of the pixel to set.
		 *  \param value is the new color for the (x,y) pixel.
		 */
		void setRate(unsigned int x, unsigned int y, T & value);

		/*! Copies the image data from an external raw buffer to the internal image buffer.
		 *
		 *  The member function ASSUMES that the input buffer is of a size compatible with the internal storage of the
		 *  Image object and that the data buffer has been already allocated. If the image buffer is not allocated or the
		 *  width or height of the image are 0, the method should exit immediately.
		 *
		 *  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Image object.
		 */
		void setData(const vector<T>  & data_ptr);

		// constructors and destructor

		/*! Default constructor.
		 *
		 * By default, the dimensions of the image should be zero and the buffer must be set to nullptr.
		 */
		Array();

		/*! Constructor with width and height specification.
		 *
		 * \param width is the desired width of the new image.
		 * \param height is the desired height of the new image.
		 */
		Array(unsigned int width, unsigned int height);

		/*! Constructor with data initialization.
		 *
		 * \param width is the desired width of the new image.
		 * \param height is the desired height of the new image.
		 * \param data_ptr is the source of the data to copy to the internal image buffer.
		 *
		 * \see setData
		 */
		Array(unsigned int width, unsigned int height, const vector<T> data_ptr);

		/*! Copy constructor.
		 *
		 * \param src is the source image to replicate in this object.
		 */
		Array(const Array &src);

		/*! The Image destructor.
		 */
		~Array();

		/*! Copy assignment operator.
		 *
		 * \param right is the source image.
		 */
		Array<T> & operator = (const Array & right);

		/*! operator() returns  áíáöïñÜ óôï óôïé÷åßï ôýðïõ Ô óôç ãñáììÞ j êáé óôÞëç i.
		 *
		 * \param x is the x column and param y is thw row column.
		 */
		T & operator () (const int & x, const int & y);



	};

	template<class T>
	vector<T> Array<T>::getRawDataPtr() {
		return buffer;
	}

	/*! Obtains the color of the image at location (x,y).
	*
	*  The method should do any necessary bounds checking.
	*
	*  \param x is the (zero-based) horizontal index of the pixel to get.
	*  \param y is the (zero-based) vertical index of the pixel to get.
	*
	*  \return The color of the (x,y) pixel as a Color object. Returns a black (0,0,0) color in case of an out-of-bounds x,y pair.
	*/template<class T>
	T Array<T>::getRate(unsigned int x, unsigned int y) const {
		
		T color;
		if (x<0 || x>getWidth() || y<0 || y>getHeight()) {
			color.r =0 ;
			color.g =0;
			color.b =0;
		}
		else {
			int position = x + width * y;
			color.r = buffer[position].r;
			color.g = buffer[position].g;
			color.b = buffer[position].b;
			
		}
		return color;
	}

	// data mutators

	/*! Sets the RGB values for an (x,y) pixel.
	*
	*  The method should perform any necessary bounds checking.
	*
	*  \param x is the (zero-based) horizontal index of the pixel to set.
	*  \param y is the (zero-based) vertical index of the pixel to set.
	*  \param value is the new color for the (x,y) pixel.
	*/template<class T>
	void Array<T>::setRate(unsigned int x, unsigned int y, T & value) {

		T color;
		if (x<0 || x>getWidth() || y<0 || y>getHeight()) {
			cout << "x, y Out of bounds!" << endl;
		}
		else {
		    color.r = value.r;
			color.g = value.g;
			color.b = value.b;
			buffer[x + width * y]=color;
		}
		

	}

	/*! Copies the image data from an external raw buffer to the internal image buffer.
	*
	*  The member function ASSUMES that the input buffer is of a size compatible with the internal storage of the
	*  Image object and that the data buffer has been already allocated. If the image buffer is not allocated or the
	*  width or height of the image are 0, the method should exit immediately.
	*
	*  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Image object.
	*/
	template<class T>
	void Array<T>::setData(const vector<T> & data_ptr) {
		buffer.resize(width*  height);
		if (getWidth() != 0 && getWidth() != 0) {
			for (int i = 0; i < getWidth()*getHeight(); i++) {
				buffer.push_back(data_ptr[i]); //gemizei o buffer etsi giati allios prokalei thorivo
				
			}
		}

	}

	// constructors and destructor

	/*! Default constructor.
	*
	* By default, the dimensions of the image should be zero and the buffer must be set to nullptr.
	*/template<class T>
	Array<T>::Array() :width(0), height(0) {}

	/*! Constructor with width and height specification.
	*
	* \param width is the desired width of the new image.
	* \param height is the desired height of the new image.
	*/template<class T>
	Array<T>::Array(unsigned int width, unsigned int height) :width(width), height(height) {}

	/*! Constructor with data initialization.
	*
	* \param width is the desired width of the new image.
	* \param height is the desired height of the new image.
	* \param data_ptr is the source of the data to copy to the internal image buffer.
	*
	* \see setData
	*/
	template<class T>
	Array<T>::Array(unsigned int width, unsigned int height, const vector<T> data_ptr) :width(width), height(height) {
		setData(data_ptr);
	}

	/*! Copy constructor.
	*
	* \param src is the source image to replicate in this object.
	*/template<class T>
	Array<T>::Array(const Array &src) :width(src.getWidth()), height(src.getHeight()) {
		const vector<T> srcbuffer = src.buffer;
		setData(srcbuffer);
	}

	/*! The Image destructor.
	*/template<class T>
	Array<T>::~Array() {
		buffer.erase(buffer.begin(), buffer.end());

	}

	/*! Copy assignment operator.
	*
	* \param right is the source image.
	*/template<class T>
	Array<T> & Array<T>::operator = (const Array<T> & right) {
		if (!buffer.empty()) {
			buffer.erase(buffer.begin(), buffer.end()); //an den einai adeia th gemizw
		}
		width = right.getWidth();
		height = right.getHeight();
		for (int i = 0; i < width*height; i++)
			buffer.push_back(right.buffer[i]); //vector exw pushback
		return *this;
	}
	/*να επιστρέφει αναφορά στο στοιχείο τύπου Τ στη γραμμή j και στήλη i.*/
	template<class T>
	T & Array<T>::operator ()(const int & x, const int & y) {
		if (x < getWidth() && y < getHeight())
			return buffer[x + width * y];
		else
			return -1;
	}

}

#endif