#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdint>


using namespace std;


class FileReader
{
	//string input_filename;
	//string output_filename;

public:
	//FileReader(string _input_filename, string _output_filename) : 
	//			input_filename(_input_filename), output_filename(_output_filename) {}


	vector<uint8_t> ReadFile(string filename) {
		vector<uint8_t> content;
		ifstream file(filename, ios::binary | ios::in);
		if (!file.is_open()) {
			//validator->AddError("Error while openning file\n");
			return content;
		}
		while (!file.eof())
		{
			content.push_back(file.get());
		}
		return content;
	}

	void Write(vector<uint32_t> content, string filename) {
		const int sequence[] = {1,1,4,2,2,4,4,4,4,2,2,4,4,4,4,4,4};

		ofstream file(filename, ios::binary | ios::out);
		for (int i = 0; i < content.size(); i++) {
			file.write(reinterpret_cast<const char*>(&content[i]), (i<17 ? sequence[i] : 1));
		}
	}
};

