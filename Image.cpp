#include <string>
#include <iostream>
#include <fstream>
#include "ppm/ppm.h"
#include "Image.h"
#include "Array.h"
#include "Vec3.h"
#include <vector>

/*! The imaging namespace contains every class or function associated with the image storage, compression and manipulation.
*/
using namespace math;
using namespace imaging;
using namespace std;


	
		/*! Default constructor.
		*
		* By default, the dimensions of the image should be zero and the buffer must be set to nullptr.
		*/
		Image::Image():Array<Vec3<float>>() {}

		/*! Constructor with width and height specification.
		*
		* \param width is the desired width of the new image.
		* \param height is the desired height of the new image.
		*/
		Image::Image(unsigned int width, unsigned int height):Array<Vec3<float>>(width,height) {}

		/*! Constructor with data initialization.
		*
		* \param width is the desired width of the new image.
		* \param height is the desired height of the new image.
		* \param data_ptr is the source of the data to copy to the internal image buffer.
		*
		* \see setData
		*/
		Image::Image(unsigned int width, unsigned int height, const vector<Vec3<float>>  data_ptr): Array<Vec3<float>>(width, height,data_ptr) {}

		/*! Copy constructor.
		*
		* \param src is the source image to replicate in this object.
		*/
		Image::Image(const Image &src):Array<Vec3<float>>(src){
		}

		/*! The Image destructor.
		*/
		Image::~Image() {
			
		}


		/*!
		* Loads the image data from the specified file, if the extension of the filename matches the format string.
		*
		* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the
		* Image object is initialized, its contents are wiped out before initializing it to the width, height and data
		* read from the file.
		*
		* \param filename is the string of the file to read the image data from.
		* \param format specifies the file format according to which the image data should be decoded from the file.
		* Only the "ppm" format is a valid format string for now.
		*
		* \return true if the loading completes successfully, false otherwise.
		*/
		bool Image::load(const std::string & filename, const std::string & format) {
		
			const char * charFilename = filename.c_str(); //pairnoume to onoma toy arxeioy poy anoigoyme gia na diavasoume
			if(format.compare("ppm")!=0){ //elegxoume an to arxeio exei katalhksh ppm
				cout << "This is a not ppm format!" << endl;
				return false;
			}
			

		    int fileWidth = 0; // arxikopoioume to width pou exoyme me 0
			int fileHeight = 0;// arxikopoioume to height pou exoyme me 0
			
		  float * result=ReadPPM(charFilename, &fileWidth, &fileHeight);  //ftiaxnei ena float * gia afta pou tha diavasei
		   width = fileWidth; //ksanapairnw ta file Width
		   height = fileHeight;//ksanapairnw ta file Height
		   buffer.resize(width*height); //kanw resize to buffer mas me afta p mas hrthan
		  
		   int j = 0;
		   for (int i = 0; i < 3 * width*height; i = i + 3) {          //antigrafoume ta dedomena apo to float * sto color Buffer
			   buffer[j].r = result[i];
			   buffer[j].g = result[i + 1];
			   buffer[j].b = result[i + 2];
			   j++;
		   }
			Image * img = new Image(fileWidth, fileHeight, buffer);       //dhmiourgoume to Image antikeimeno me vash fileWidth, fileHeight,c olor buffer
            return true;

		}

		/*!
		* Stores the image data to the specified file, if the extension of the filename matches the format string.
		*
		* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the
		* Image object is not initialized, the method should return immediately with a false return value.
		*
		* \param filename is the string of the file to write the image data to.
		* \param format specifies the file format according to which the image data should be encoded to the file.
		* Only the "ppm" format is a valid format string for now.
		*
		* \return true if the save operation completes successfully, false otherwise.
		*/
		bool Image:: save(const std::string & filename, const std::string & format) {

			if (format.compare("ppm") != 0) { //elegxoume an to arxeio exei katalhksh ppm
				cout << "This is a not ppm format!" << endl;
				return false;
			}

			const char * charFilename = filename.c_str(); //pairnoyme to onoma to arxeioy poy anoigoyme gia na grapsoume
			float *  result=new float[3* getWidth()*getHeight()]; //arxikopoume to pinaka float* result pou exoyme na grapsoume
			int count = 0;
			for (int i = 0; i < getWidth()*getHeight(); i = i+1) {  //pairnw to buffer pou exw kai gia kathe r,g,b afairw to 255 pou einai
				result[count] = buffer[i].r;                 //h megisth timh gia na ftiaksw to arnhtiko kai ta bazw sto pinaka result
				result[count + 1] = buffer[i].g;
				result[count + 2] = buffer[i].b;
				count = count + 3;
			}
			
			if (!WritePPM(result, getWidth(), getHeight(), charFilename)) {   // edw fwnazw th WritePPM gia na m grapsei to pinaka float* result sto arxeio
				return false;

			}
			delete[] result;// diagrafw to float * result
			return true;			
		}

	   





