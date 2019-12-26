#include <iostream>
#include <fstream>
#include <string>
#include "avl.hpp"
#ifndef WORK_FILE_H
#define WORK_FILE_H
using namespace std;

class work_file:public AVL
{
	string word;
   public:
	void open_file();
};


void work_file::open_file()
{
	string line, buffer;
        cout<<"Enter file name : ";
	cin>>word; 
        ifstream file(word); 
        if (file.is_open())
        {
            while (file>>word)
            {
                 getline(file, line);
                 if(word[0]>='A' && word[0]<='Z')
				word[0]+=32;
                 Tree *avl = avl_newNode(line, word);
			     insert (avl);
            }  file.close();  cout << "File reading!"<<endl;
        } 
	else cout << "Error in file openning"<<endl;
}
#endif
