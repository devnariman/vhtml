#include "vhtml.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>


using namespace std;
bool menu(vhtml& html);
void clearScreen();



int main() {

	string url;
	bool check;
	url = "https://www.tpointtech.com/features-of-java";
	//cout << "enter your url : "; cin >> url; cout << endl;
	//cin.ignore();
	vhtml html(url);


	while (true)
	{
		if (menu(html) == true) {
			cin.ignore();
			clearScreen();
		}
		else
		{
			clearScreen();
			break;
		};
	}
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
bool menu(vhtml& html) {
	int controler_number;
	cout << "menu : " << endl;
	cout << "1 - show vhtml" << endl;
	cout << "2 - vhtml size" << endl;
	cout << "3 - search vhtml" << endl;
	cout << "4 - vhtml map " << endl;
	cout << "5 - vhtml domain IP " << endl;
	cout << "Enter your controler number : "; cin >> controler_number; cout << endl;
	cin.ignore();
	string base;
	char temp;
	size_t char_count = 0;
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
	case 3:
		clearScreen();
		cout << "search in HTML , enter your str :  >>>>>>>> "; 
		while (true) {
			cin.get(temp);  // خواندن یک کاراکتر
			if (temp == '\n') {  // اگر به انتهای خط رسیدیم
				break;
			}
			char_count++;
			base.push_back(temp);  // اضافه کردن کاراکتر به وکتور
		}
		cout << html.get_element(base) << endl;
		break;
	case 4:
		clearScreen();
		cout << "HTML ClassName Map :  >>>>>>>> " << endl;
		html.show_all_className();
		break;
	case 5:
		clearScreen();
		cout << "vhtml IP :  >>>>>>>> ";
		cout << html.get_domain_ip() << endl;
		break;
	case 2256:
		return false;
	default:
		cout << "your controler number not declering !" << endl;
		break;
	}
	return true;
}

void clearScreen() { system("cls"); }
