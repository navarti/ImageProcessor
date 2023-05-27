#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdint>
#include "Validator.h"
#include "Structs.h"

using namespace std;


class FileReader
{
	Validator* validator;

public:
	
	FileReader(Validator* _validator) : validator(_validator) {}

	vector<uint8_t> ReadFile(string filename) {
		vector<uint8_t> content;
		ifstream file(filename, ios::binary | ios::in);
		if (!file.is_open()) {
			validator->AddError("Error while openning file\n");
			return content;
		}
		while (!file.eof())
		{
			content.push_back(file.get());
		}
		file.close();
		return content;
	}

	void Write(pair<BMPHEAD, vector<uint8_t>> content, string filename) {
		ofstream file(filename, ios::binary | ios::out);
		if (!file.is_open()) {
			validator->AddError("Error while openning file\n");
			return;
		}
		cout << sizeof(BMPHEAD);

		//file.write((char*)&content.first, sizeof(BMPHEAD));
		
		file.write(reinterpret_cast<const char*>(&content.first.id[0]), sizeof(content.first.id[0]));
		file.write(reinterpret_cast<const char*>(&content.first.id[1]), sizeof(content.first.id[0]));
		file.write(reinterpret_cast<const char*>(&content.first.filesize), sizeof(content.first.filesize));
		file.write(reinterpret_cast<const char*>(&content.first.reserved[0]), sizeof(content.first.reserved[0]));
		file.write(reinterpret_cast<const char*>(&content.first.reserved[1]), sizeof(content.first.reserved[0]));
		file.write(reinterpret_cast<const char*>(&content.first.headersize), sizeof(content.first.headersize));
		file.write(reinterpret_cast<const char*>(&content.first.infoSize), sizeof(content.first.infoSize));
		file.write(reinterpret_cast<const char*>(&content.first.width), sizeof(content.first.width));
		file.write(reinterpret_cast<const char*>(&content.first.depth), sizeof(content.first.depth));
		file.write(reinterpret_cast<const char*>(&content.first.biPlanes), sizeof(content.first.biPlanes));
		file.write(reinterpret_cast<const char*>(&content.first.bits), sizeof(content.first.bits));
		file.write(reinterpret_cast<const char*>(&content.first.biCompression), sizeof(content.first.biCompression));
		file.write(reinterpret_cast<const char*>(&content.first.biSizeImage), sizeof(content.first.biSizeImage));
		file.write(reinterpret_cast<const char*>(&content.first.biXPelsPerMeter), sizeof(content.first.biXPelsPerMeter));
		file.write(reinterpret_cast<const char*>(&content.first.biYPelsPerMeter), sizeof(content.first.biYPelsPerMeter));
		file.write(reinterpret_cast<const char*>(&content.first.biClrUsed), sizeof(content.first.biClrUsed));
		file.write(reinterpret_cast<const char*>(&content.first.biClrImportant), sizeof(content.first.biClrImportant));
		
		
		for (int i = 0; i < content.second.size(); i++) {
			file.write(reinterpret_cast<const char*>(&content.second[i]), sizeof(content.second[i]));
		}
		file.close();
	}
};

