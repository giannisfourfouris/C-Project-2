#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Color.h"
#include "Image.h"
#include "Filter.h"
#include "FilterLinear.h"
#include "FilterGamma.h"
#include "ppm\ppm.h"
#include <sstream>



using namespace std;
using namespace imaging;
int main(int argc, char *argv[]) {
	if (argc == 1) {
		//with the following i get the image and thw aerguments from the console.
		cout << "Please give the image and the filters with parameters: " << endl;
		string line;
		getline(cin, line);
	//	line = "filter -f linear 2 2 2 0 0 0 Image01.ppm";
			
		//me to parakatw spaw mia protash se memonomenes lekseis
		// Vector of string to save tokens 
		vector <string> tokens;
		// stringstream class check1 
		stringstream check1(line);
		string intermediate;
		// Tokenizing w.r.t. space ' ' 
		while (getline(check1, intermediate, ' '))
		{
			tokens.push_back(intermediate);
		}
		// Printing the token vector 
		//for (int i = 0; i < tokens.size(); i++) {
		//	cout << tokens[i] << '\n';
		//}
		Image image;
		string ppm="ppm";
		string gamma = "gamma";
		string linear = "linear";
		string f = "-f";
		//tokens einai o pinakas p exei oles ths lekseis sth seira
		if (tokens.size() < 5) {//an den exei 5 lekseis(filter -f gamma 2.0 Image01.ppm) tote telos
			cout << "Not enough arguments"<<endl; 
			system("pause");
			return 0;
		}
		bool load = image.load(tokens[tokens.size() - 1], ppm); //fortwnw thn eikona tokens[tokens.size() - 1](einai h teletaia leksh)
		//cout << tokens[tokens.size() - 1];
		if (load == false) {
			system("pause"); //an den mporei na th fortwsei tote vgazei lathos
			return 0;
		}
		for (int i = 2; i < tokens.size()-1; i++) { //ksekinaw apo th trith leksh gia na dv ti filtro exei
			if (tokens[i] == linear) { //an einai linear shmainei oti tha prepei na exei 6 noumera meta 
				//	cout << linear<<endl;
				// atof = string to double
				if ((int)(tokens[i + 1].c_str()) && (int)(tokens[i + 2].c_str()) && (int)(tokens[i + 3].c_str())
					&& (int)(tokens[i + 4].c_str()) && (int)(tokens[i + 5].c_str()) && (int)(tokens[i + 6].c_str())) {
					//cout << "You have give 6 numbers"<<endl;
					Vec3<float> a;                       //arxikopoiw ta a kai ta c me tous arithmous p m exoyn dvsei
					a.x = (atof(tokens[i + 1].c_str()));
					a.y = (atof(tokens[i + 2].c_str()));
					a.z = (atof(tokens[i + 3].c_str()));
					Vec3<float> c;
					c.x = (atof(tokens[i + 4].c_str()));
					c.y = (atof(tokens[i + 5].c_str()));
					c.z = (atof(tokens[i + 6].c_str()));
					FilterLinear  filterlinear(a, c); //arxikopoiw to filtro
					image = filterlinear<<(image);//efarmozv to filtro sthn eikona
				}
				else {
					cout << "You have not give 6 numbers" << endl;
					system("pause");
					return 0;
				}

			}
			else if (tokens[i] == gamma) { //an einai gamma
				//	cout << gamma<<endl;
				if ((atof)(tokens[i + 1].c_str())) { //to epomeno p dexomaste prepei an einai double arithmos
					//cout << "You have give 1 double number" << endl;

					if ((atof(tokens[i + 1].c_str()) >= 0, 5) && (atof(tokens[i + 1].c_str()) <= 2, 0)) { //elegxo ta oria
						cout << "Gamma number must be between 0.5 and 2.0" << endl;
						system("pause");
						return 0;
					}
					FilterGamma  filtergamma(atof(tokens[i + 1].c_str())); //arxikopoiw to filtro
					image = filtergamma<<(image);//efarmozw to filtro
				}
				else {
					cout << "You have not give 1 double number" << endl;
					system("pause");
					return 0;

				}

			}
			else {}

		}
		string filtered = "filtered_";
		string fName = filtered + tokens[tokens.size() - 1]; //ftianxw to onoma ths filtrarismenhs eikonas
		if (!image.save(fName, ppm)) { //th kanw save an ola pane kala tote eimaste entaksei alliw mhnyma lathous
			system("pause");
			return 0;
		}

		cout << "Everything works great!!\n";

		system("pause");
		return 0;
	}
	else {//if you have arguments
		Image image;
		string ppm = "ppm";
		string gamma = "gamma";
		string linear = "linear";
		string f = "-f";
		if (argc < 5) {
			cout << "Not enough arguments";
			system("pause");
			return 0;
		}

		bool load = image.load(argv[argc - 1], ppm);
		if (load == false) {
			system("pause");
			return 0;
		}


		// atof = string to double
		for (int i = 3; i < argc - 1; i++) {
			if (argv[i] == linear) {
				//	cout << linear<<endl;
				if ((int)(argv[i + 1]) && (int)(argv[i + 2]) && (int)(argv[i + 3])
					&& (int)(argv[i + 4]) && (int)(argv[i + 5]) && (int)(argv[i + 6])) {
					//cout << "You have give 6 numbers"<<endl;
					Vec3<float> a;
					a.x = (atof(argv[i + 1]));
					a.y = (atof(argv[i + 2]));
					a.z = (atof(argv[i + 3]));
					Vec3<float> c;
					c.x = (atof(argv[i + 4]));
					c.y = (atof(argv[i + 5]));
					c.z = (atof(argv[i + 6]));
					FilterLinear  filterlinear(a, c); // ç FilterLinear  filterlinear(a,c); image = filterlinear<<(image);
					image = filterlinear<<(image);
				}
				else {
					cout << "You have not give 6 numbers" << endl;
					system("pause");
					return 0;
				}

			}
			else if (argv[i] == gamma) {
				//	cout << gamma<<endl;
				if ((atof)(argv[i + 1])) {
					//cout << "You have give 1 double number" << endl;

					if ((atof(argv[i + 1]) >= 0, 5) && (atof(argv[i + 1]) <= 2, 0)) {
						cout << "Gamma number must be between 0.5 and 2.0" << endl;
						system("pause");
						return 0;
					}
					FilterGamma  filtergamma(atof(argv[i + 1]));
					image = filtergamma<<(image);
				}
				else {
					cout << "You have not give 1 double number" << endl;
					system("pause");
					return 0;

				}

			}
			else {}

		}


		string filtered = "filtered_";
		string fName = filtered + argv[argc - 1];
		if (!image.save(fName, ppm)) {
			system("pause");
			return 0;
		}

		cout << "Everything works great!!\n";

		system("pause");
		return 0;
	}
}

