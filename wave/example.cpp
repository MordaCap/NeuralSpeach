#include <iostream>
#include "wav.hpp"

using namespace std;

int main(int argc,char* argv[])
{
	// Путь к файлу передали агрументом командной строки.
	if (argc < 2) return 0;

	char *src = argv[1];

	vector<float> data = wav::loadFloatFirstChannel(src);
	// Просто выведем полученный вектор на печать.
	for (auto i : data) 
		cout << i << endl;

	return 0;
}