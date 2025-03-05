#include "vhtml.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;
void menu(vhtml& html);
void clearScreen();



int main() {

	string url;
	cout << "enter your url : "; cin >> url; cout << endl;

	vhtml html(url, "nariman");


	//menu(html);
	cin.get();
	cin.ignore();
	return 0;
}
//.
//.
//.
//.
//.
//.
//.
//.
//.
void menu(vhtml& html) {
	int controler_number;
	cout << "menu : " << endl;
	cout << "1 - show vhtml" << endl;
	cout << "2 - vhtml size" << endl << endl;
	cout << "Enter your controler number : "; cin >> controler_number; cout << endl;

	switch (controler_number)
	{
	case 1:
		clearScreen();
		cout << "show HTML >>>>>>>>" << endl << endl;
		cout << html;
		break;
	case 2:
		clearScreen();
		cout << "HTML size >>>>>>>> "; html.html_size(); cout << " Byte" << endl;
		break;
	default:
		cout << "your controler number not declering !" << endl;
		break;
	}
}

void clearScreen() { system("cls"); }
