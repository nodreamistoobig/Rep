#ifndef _TEXTFILE_H
#define _TEXTFILE_H

using namespace std;

class TextFile {
public:
	string path;
	int state;
	TextFile();
	TextFile(string p, int s);
	friend istream& operator >> (istream& in, TextFile& file);
	friend ostream& operator << (ostream& out, const TextFile& file);
	void CopyFile(TextFile fileout);
	void AddToFile(TextFile addfile);
	void MakeUniq(TextFile file1, TextFile file2);
	void SortAscend(int col);
	void SortDescend(int col);
};

#endif 