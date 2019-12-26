#include <iostream>
#include "textfile.h"

using namespace std;

int main()
{
	TextFile file1("file1.txt", 0);
	TextFile copy("copy.txt", 0);
	file1.CopyFile(copy);
	file1.SortAscend(1);
	file1.AddToFile(copy);
}
