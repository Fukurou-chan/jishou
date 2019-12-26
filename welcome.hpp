#include "workfile.hpp"
#ifndef WELCOME_H
#define WELCOME_H
using namespace std;

class Welcome: public work_file
{
   public:
	void showMenu();
	bool choose(char ch);
    void dictionary();
};

void Welcome::dictionary()
{
	char chi;
 	for (;;) 
	{
			do {
				showMenu();
				cin >> chi;
			} 
		while (choose(chi));
		if (chi == 'q') break;
		cout << endl;
              
    }
}

void Welcome::showMenu()
{
	cout<<endl<<"***** MAIN MENU *****"<<endl;
	cout<<"1.Read file Data"<<endl;
	cout<<"2.Add new word"<<endl;
	cout<<"3.Remove a word"<<endl;
	cout<<"4.Search for a word"<<endl;
	cout<<"5.Get hight tree"<<endl;
	cout<<"q if you want exit"<<endl;
	cout<<"==================="<<endl;
}

bool Welcome::choose(char ch)
{
	if ((ch < '1' || ch > '5') || (ch == 'q'))
			return false;
    else
	{
		switch(ch)
		{
			case 1 : {open_file ();
						break;}
			/*case 2 : {insert (Tree *tree);
						break;}
			case 3 : {remove(Tree *tree);
						break;}
			case 4 : {search(Tree *tree);
						break;}
			case 5 :{ getHeightDif(Tree *tree);
						break;}*/
		};
	}
}
#endif
