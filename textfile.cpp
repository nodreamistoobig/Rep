#include <iostream>
#include <fstream>
#include "textfile.h"
#include "list.h"

using namespace std;

TextFile::TextFile() {
	path = "";
	state = 0;
}

TextFile::TextFile(string p, int s) {
	path = p;
	state = 0;
}

istream& operator >> (istream& in, TextFile& file) {
	in >> file.path >> file.state;
	return in;
}

ostream& operator << (ostream& out, TextFile& file) {
	out <<  file.path << file.state;
	return out;
}

void TextFile::CopyFile(TextFile fileout) {
	ifstream in(this->path);
	ofstream out(fileout.path);
	if (!in.is_open())
	{
		cout << "Error: file isn't found" << endl;
		return;
	}
	char str[200];
	while (!in.eof()) {
		in.getline(str, 200);
		out << str;
	}
}

void TextFile::AddToFile(TextFile addfile) {
	TextFile buf("buf.txt", 0);
	ofstream out(buf.path);
	ifstream in(this->path);
	if (!in.is_open())
	{
		cout << "Error: file isn't found" << endl;
		return;
	}
	char str[200];
	while (!in.eof()) {
		in.getline(str, 200);
		out << str;
	}
	ifstream fin(addfile.path);
	if (!fin.is_open())
	{
		cout << "Error: file isn't found" << endl;
		return;
	}
	while (!fin.eof()) {
		fin.getline(str, 200);
		out << str;
	}
	buf.CopyFile(*this);
}

void TextFile::MakeUniq(TextFile file1, TextFile file2) {
	
}

void TextFile::SortAscend(int col) {
	ifstream in(this->path);
	if (!in.is_open())
	{
		cout << "Error: file isn't found" << endl;
		return;
	}
	char str[200];
	in.getline(str, 200);
	int count = 0;
	for (int i = 0; i < 200; i++)
	{
		if (!(str[i] == ' '))
		{
			count++;
			while (!(str[i] == ' '))
			{
				i++;
			}
			i--;
			
		}
	}
	cout << count << endl;
	if (count < col)
	{
		cout << "There are less columns in the file" << endl;
		return;
	}
	Data dataOfFile(count);
	LineList <Data> fileContent;
	LineListElem<Data>* ptr = fileContent.getStart();
	while (!in.eof()) {
		in >> dataOfFile;
		if (!fileContent.getStart())
			fileContent.insertFirst(dataOfFile);
		else {
			for (LineListElem<Data>* it = fileContent.getStart(); it; it = it->getNext()) {
				//cout << it->data.d[col] << " " << dataOfFile.d[col] << endl;
				if (it->data.d[col] <= dataOfFile.d[col] && (!it->getNext() || it->getNext()->data.d[col] >= dataOfFile.d[col]))
				{
					fileContent.insertAfter(ptr, dataOfFile);
					break;
				}
				else if (it->data.d[col] > dataOfFile.d[col])
				{
					fileContent.insertFirst(dataOfFile);
					break;
				}
				ptr = ptr->getNext();
			}
		}
	}
	ofstream out(this->path);
	out << fileContent;


}

void TextFile::SortDescend(int col) {

}