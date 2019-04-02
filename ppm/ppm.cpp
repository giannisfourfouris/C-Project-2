#include <iostream>
#include <fstream>
#include "ppm.h"
#include <string>




using namespace std;

/*! Reads a PPM image file and returns a pointer to a newly allocated float array containing the image data.
*
* Values in the returned array are in the range [0,1] and for each pixel, three values are stored.
*
*  \param filename is the null-terminated string of the name of the file to open.
*  \param w is the address of an integer parameter to return the width of the image into.
*  \param h is the address of an integer parameter to return the height of the image into.
*
*  \return a pointer to a new float array of 3 X w X h floats, that contains the image data.
*  If the reading operation failed the function returns nullptr.
*/
float * imaging::ReadPPM(const char * filename, int * w, int * h) {

	

	ifstream iFile(filename, ios::in | ios::binary);  //anoigw arxei se binary morfh
	if (!iFile.is_open()) { //elegxw an mporei na anoiksei
		cout << "Could not open file" << endl;
		return 0;
	}
	string fileHeaderFormat;
	int  fileLenght;

	iFile >> fileHeaderFormat >> *w >> *h >> fileLenght;//diavazw to  P6,width,height,length
	cout << "Image dimensions are: " << *w << " * " << *h << endl; //emfaanizoyme diastaseis
	if (fileHeaderFormat.compare("P6") != 0) { //elegxei an h epikefalia einai P6
		cout << "The header format is not P6!" << endl;
		iFile.close();
		return false;
	}
	if (*w == 0) {//elegxei an uparxei to width
		cout << "The width does not exist!" << endl;
		iFile.close();
		return false;
	}

	if (*h == 0) {//elegxei an uparxei to height
		cout << "The height does not exist!" << endl;
		iFile.close();
		return false;
	}

	if (fileLenght == 0 || fileLenght > 255) {//elegxei an to length einai mesa sta oria
		cout << "The lenght does not exist or is bigger than 255!" << endl;
		iFile.close();
		return false;
	}
	
	float *buffer = new float[3 * (*h)*(*w)];// dhmiourgia float*buffer.ekei grafw ta dedomena pou diavazw
	char ch;
	iFile.get(ch);										// reads the new line character
    int i = 0;
	while (iFile.get(ch)) {
		float f = 0.0;
		f = (float)((unsigned char)ch) / 255.0f;            // divide by 255 to have floats from 0.0 to 1.0
        buffer[i] = f;								//store to the buffer the float values
		i++;
	}//end of while
	// Now go back to start of file and close the file
	iFile.clear();
	iFile.seekg(0, ios_base::beg);
	iFile.close();
	return buffer;
}

/*! Writes an image buffer as a PPM file.
*
*  \param data contains the image buffer. The data are RGB float tripplets with values in the range [0,1].
*  \param w is the width of the image in pixels.
*  \param h is the height of the image in pixels.
*  \param filename is the null-terminated string of the name of the file to create.
*
*  \return true if the image save operation was successful, false otherwise. If the data parameter is nulltr, the
*  function returns immediately with a false return value.
*/
bool imaging::WritePPM(const float * data, int w, int h, const char * filename) {

	cout << "Opening " << filename << " for writing... \n";
	ofstream oFile(filename, ios::out | ios::binary); //anoigw to file poy dexomai gia na  grapsw
	if (!oFile.is_open()) {//checks if fille is open or not
		cout << "Could not open filtered_Image!" << endl;
		return false;
	}


	//ftiaxnw thn epikefalida kai th grafw sto arxeio
	string headerformat = "P6";
	string lenght = "255";
	string text = headerformat + "\n" + std::to_string(w) + "\n" + std::to_string(h) + "\n255\n"; // afto mporei na thelei mono ena xarakthra allagh grammhs kai na mhn thelei keno "\n255\n"
	oFile << text;


    char * buff = new char[3 * w*h];        //a buffer of characters
	for (int i = 0; i < 3 * w*h; i++)
	{
		buff[i] = data[i] * 255;							//float * 255 
	}
	//file write (buffer,size)
	oFile.write((char*)buff, 3 * w*h);
    // Make sure everything passed into the file
	oFile.flush();
	// Now go back to start of file and close the file
	oFile.clear();
	oFile.seekp(0, ios_base::beg);
	oFile.close();

	cout << "The filtered_Image has been written correctly!! " << endl;
	return true;

}
