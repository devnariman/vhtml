#include "vhtml.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <memory>


using namespace std;
bool menu(vhtml& html);
void clearScreen();



int main() {

	string url;
	bool check;
	url = "https://vgdl.ir/";
	//cout << "enter your url : "; cin >> url; cout << endl;
	//cin.ignore();
	vhtml html(url);
    
   

	
	while (true)
	{
		
        if(html.availability_status() == false) 
        {
            break;
        }
        else
        {
            if (menu(html) == true)
            {
                cin.ignore();
                clearScreen();
            }
            else
            {
                clearScreen();
                break;
            };
        }
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
    cout << "6 - vhtml All Start Element from className " << endl;
    cout << "7 - search in vhtml by class name " << endl;
    cout << "Enter your controler number : "; cin >> controler_number; cout << endl;
    cin.ignore();

    /*
    if (controler_number != 1,
        controler_number != 2,
        controler_number != 3,
        controler_number != 4,
        controler_number != 5,
        controler_number != 6 ,
        controler_number != 7)
    {
        cout << "your number not defined ! " << endl;
        return true;
    }
    */

    auto base = std::make_unique<std::string>(); // استفاده از unique_ptr به جای new
    auto temp = std::make_unique<char>();       // استفاده از unique_ptr به جای new
    size_t char_count = 0;

    switch (controler_number) {
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
        cout << "search in HTML , enter your str :  >>>>>>>> "; // 7 va 3
        while (true) {
            cin.get(*temp);  // خواندن یک کاراکتر
            if (*temp == '\n') {  // اگر به انتهای خط رسیدیم
                break;
            }
            char_count++;
            base->push_back(*temp);  // اضافه کردن کاراکتر به string
        }
        cout << html.get_element(*base) << endl;
        break;
    case 4:
        clearScreen();
        cout << "HTML ClassName Map :  >>>>>>>> " << endl;
        html.show_all_className();
        break;
    case 5:
        clearScreen();
        cout << "vhtml IP :  >>>>>>>> " << endl;
        cout << html.get_domain_ip() << endl;
        break;
    case 6:
        cout << "vhtml All Start Element from className :  >>>>>>>> " << endl;
        html.show_all_className_tagElement();
        break;
    case 7:
        clearScreen();
        cout << "search in HTML by class name, enter your classname target :  >>>>>>>> "; // 3 va 7
        while (true) {
            cin.get(*temp);  // خواندن یک کاراکتر
            if (*temp == '\n') {  // اگر به انتهای خط رسیدیم
                break;
            }
            char_count++;
            base->push_back(*temp);  // اضافه کردن کاراکتر به string
        }
        cout << html.GetElement_by_className(*base) << endl;
        break;
    case 2256:
        return false;
    default:
        break;
    }
    return true;
}

void clearScreen() { system("cls"); }
