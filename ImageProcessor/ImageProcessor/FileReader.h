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

	pair<BMPHEAD, vector<uint8_t>> ReadFile(string filename) {
		BMPHEAD head;
		vector<uint8_t> content;
		ifstream file(filename, ios::binary | ios::in);
		if (!file.is_open()) {
			validator->AddError("Error while openning file\n");
			return make_pair(head, content);
		}

		file.read((char*)&head, sizeof(BMPHEAD));

		while (!file.eof())
		{
			content.push_back(file.get());
		}
		file.close();
		return make_pair(head, content);
	}

	void Write(pair<BMPHEAD, vector<uint8_t>> content, string filename) {
		ofstream file(filename, ios::binary | ios::out);
		if (!file.is_open()) {
			validator->AddError("Error while openning file\n");
			return;
		}

		file.write((char*)&content.first, sizeof(BMPHEAD));
				
		for (int i = 0; i < content.second.size(); i++) {
			file.write(reinterpret_cast<const char*>(&content.second[i]), sizeof(content.second[i]));
		}
		file.close();
	}
};

