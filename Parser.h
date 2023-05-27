#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Structs.h"

using namespace std;


class Parser
{
	vector<uint8_t> content_in;
	int index;

	BMPHEAD head;
	vector<vector<PIXELDATA>> pixels;

	int32_t Read(int size){
		int32_t result = 0;
		int coef = 1;
		for (int i = 0; i < size; i++) {
			result += content_in[index++] * coef;
			coef *= 256;
		}
		return result;
	}

	void ProcessBMPHEAD() {
		head.id[0] = Read(sizeof(head.id[0]));
		head.id[1] = Read(sizeof(head.id[0]));
		head.filesize = Read(sizeof(head.filesize));
		head.reserved[0] = Read(sizeof(head.reserved[0]));
		head.reserved[1] = Read(sizeof(head.reserved[1]));
		head.headersize= Read(sizeof(head.headersize));
		head.infoSize= Read(sizeof(head.infoSize));
		head.width= Read(sizeof(head.width));
		head.depth = Read(sizeof(head.depth));
		head.biPlanes = Read(sizeof(head.biPlanes));
		head.bits = Read(sizeof(head.bits));
		head.biCompression = Read(sizeof(head.biCompression));
		head.biSizeImage = Read(sizeof(head.biSizeImage));
		head.biXPelsPerMeter = Read(sizeof(head.biXPelsPerMeter));
		head.biYPelsPerMeter = Read(sizeof(head.biYPelsPerMeter));
		head.biClrUsed = Read(sizeof(head.biClrUsed));
		head.biClrImportant = Read(sizeof(head.biClrImportant));
	}

	PIXELDATA ProcessPixel() {
		PIXELDATA to_add;
		to_add.redComponent = Read(sizeof(to_add.redComponent));
		to_add.greenComponent = Read(sizeof(to_add.greenComponent));
		to_add.blueComponent = Read(sizeof(to_add.blueComponent));
		return to_add;
	}

	void ParseToRead() {
		index = 0;

		ProcessBMPHEAD();
		int skip = (4 - (head.width * sizeof(PIXELDATA)) % 4) % 4;

		for (int i = 0; i < head.depth; i++) {
			vector<PIXELDATA> row;
			for (int j = 0; j < head.width; j++) {
				row.push_back(ProcessPixel());
			}
			for (int j = 0; j < skip; j++) {
				index++;
			}
			pixels.push_back(row);
		}
	}

	vector<uint8_t> ParseToWrite(vector<vector<PIXELDATA>> pixels, int width) {

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
	
	pair<BMPHEAD, vector<vector<PIXELDATA>>> GetDataToProcess(vector<uint8_t> _content) {
		content_in = _content;
		ParseToRead();
		content_in.clear();
		return make_pair(head, pixels);
	}

	pair<BMPHEAD, vector<uint8_t>> GetDataToWrite(pair<BMPHEAD, vector<vector<PIXELDATA>>> data) {
		return make_pair(data.first, ParseToWrite(data.second, data.first.width));
	}
};

