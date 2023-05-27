#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Structs.h"

using namespace std;


class Parser
{

	vector<vector<PIXELDATA>> ParsePixelsToRead(BMPHEAD head, vector<uint8_t> bytes) {
		int index = 0;
		vector<vector<PIXELDATA>> pixels;
		int skip = (4 - (head.width * sizeof(PIXELDATA)) % 4) % 4;

		for (int i = 0; i < head.depth; i++) {
			vector<PIXELDATA> row;
			for (int j = 0; j < head.width; j++) {
				PIXELDATA to_add;
				to_add.redComponent = bytes[index++];
				to_add.greenComponent = bytes[index++];
				to_add.blueComponent = bytes[index++];
				row.push_back(to_add);
			}
			for (int j = 0; j < skip; j++) {
				index++;
			}
			pixels.push_back(row);
		}
		return pixels;
	}

	vector<uint8_t> ParsePixelsToWrite(vector<vector<PIXELDATA>> pixels, int width) {
		vector<uint8_t> res;
		int skip = (4 - ( width * sizeof(PIXELDATA)) % 4) % 4;

		for (const vector<PIXELDATA>& row : pixels) {
			for (const PIXELDATA& pixel : row) {
				res.push_back(pixel.redComponent);
				res.push_back(pixel.greenComponent);
				res.push_back(pixel.blueComponent);
			}
			for (int i = 0; i < skip; i++) {
				res.push_back(0);
			}
		}
		return res;
	}
public:
	
	pair<BMPHEAD, vector<vector<PIXELDATA>>> GetDataToProcess(pair<BMPHEAD, vector<uint8_t>> content){	
		return make_pair(content.first, ParsePixelsToRead(content.first, content.second));
	}

	pair<BMPHEAD, vector<uint8_t>> GetDataToWrite(pair<BMPHEAD, vector<vector<PIXELDATA>>> data) {
		return make_pair(data.first, ParsePixelsToWrite(data.second, data.first.width));
	}
};

