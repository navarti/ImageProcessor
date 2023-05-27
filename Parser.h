#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Structs.h"
#include "Validator.h"

using namespace std;


class Parser
{
	Validator* validator;

public:
	Parser(Validator* _validator) : validator(_validator) {}

	pair<BMPHEAD, vector<vector<PIXELDATA>>> GetDataToProcess(pair<BMPHEAD, vector<uint8_t>>* content) {
		vector<vector<PIXELDATA>> pixels;

		int index = 0;
		int skip = (4 - (content->first.width * sizeof(PIXELDATA)) % 4) % 4;

		for (int i = 0; i < content->first.depth; i++) {
			vector<PIXELDATA> row;
			for (int j = 0; j < content->first.width; j++) {
				PIXELDATA to_add;
				try {
					to_add.redComponent = content->second[index++];
					to_add.greenComponent = content->second[index++];
					to_add.blueComponent = content->second[index++];
					row.push_back(to_add);
				}
				catch (...) {
					validator->AddError("The file is damaged");
					return make_pair(content->first, pixels);
				}
			}
			for (int j = 0; j < skip; j++) {
				index++;
			}
			pixels.push_back(row);
		}
		return make_pair(content->first, pixels);
	}

	pair<BMPHEAD, vector<uint8_t>> GetDataToWrite(pair<BMPHEAD, vector<vector<PIXELDATA>>> data) {
		vector<uint8_t> pixels_in_bytes;
		int skip = (4 - (data.first.width* sizeof(PIXELDATA)) % 4) % 4;

		for (const vector<PIXELDATA>& row : data.second) {
			for (const PIXELDATA& pixel : row) {
				pixels_in_bytes.push_back(pixel.redComponent);
				pixels_in_bytes.push_back(pixel.greenComponent);
				pixels_in_bytes.push_back(pixel.blueComponent);
			}
			for (int i = 0; i < skip; i++) {
				pixels_in_bytes.push_back(0);
			}
		}
		
		return make_pair(data.first, pixels_in_bytes);
	}
};



