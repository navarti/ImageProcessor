#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Structs.h"

using namespace std;


class Parser
{
	vector<uint8_t> content_in;
	vector<uint32_t> content_out;
	BMPHEAD head;
	vector<vector<PIXELDATA>> pixels;

	int index;

	int32_t Read(int size){
		int32_t result = 0;

		int to_read = size / 8;
		int coef = 1;

		for (int i = 0; i < to_read; i++) {
			result += content_in[index++] * coef;
			coef *= 256;
		}
		
		return result;
	}

	void ProcessBMPHEAD() {
		head.id[0] = Read(8);
		head.id[1] = Read(8);
		head.filesize = Read(32);
		head.reserved[0] = Read(16);
		head.reserved[1] = Read(16);
		head.headersize= Read(32);
		head.infoSize= Read(32);
		head.width= Read(32);
		head.depth = Read(32);
		head.biPlanes = Read(16);
		head.bits = Read(16);
		head.biCompression = Read(32);
		head.biSizeImage = Read(32);
		head.biXPelsPerMeter = Read(32);
		head.biYPelsPerMeter = Read(32);
		head.biClrUsed = Read(32);
		head.biClrImportant = Read(32);
	}

	PIXELDATA ProcessPixel() {
		PIXELDATA to_add;
		to_add.redComponent = Read(8);
		to_add.greenComponent = Read(8);
		to_add.blueComponent = Read(8);
		return to_add;
	}

public:
	void ProcessContent(vector<uint8_t> _content) {
		content_in = _content;
		index = 0;
		
		ProcessBMPHEAD();

		for (int i = 0; i < head.depth; i++) {
			vector<PIXELDATA> row;
			for (int j = 0; j < head.width; j++) {
				row.push_back(ProcessPixel());
			}
			pixels.push_back(row);
		}
	}

	void ParseToWrite(pair<BMPHEAD, vector<vector<PIXELDATA>>> data) {
		content_out.clear();

		content_out.push_back(data.first.id[0]);
		content_out.push_back(data.first.id[1]);
		content_out.push_back(data.first.filesize);
		content_out.push_back(data.first.reserved[0]);
		content_out.push_back(data.first.reserved[1]);
		content_out.push_back(data.first.headersize);
		content_out.push_back(data.first.infoSize);
		content_out.push_back(data.first.width);
		content_out.push_back(data.first.depth);
		content_out.push_back(data.first.biPlanes);
		content_out.push_back(data.first.bits);
		content_out.push_back(data.first.biCompression);
		content_out.push_back(data.first.biSizeImage);
		content_out.push_back(data.first.biXPelsPerMeter);
		content_out.push_back(data.first.biYPelsPerMeter);
		content_out.push_back(data.first.biClrUsed);
		content_out.push_back(data.first.biClrImportant);
		
		for (const vector<PIXELDATA>& row : data.second) {
			for (const PIXELDATA& pixel : row) {
				content_out.push_back(pixel.redComponent);
				content_out.push_back(pixel.greenComponent);
				content_out.push_back(pixel.blueComponent);
			}
		}
	}

	pair<BMPHEAD, vector<vector<PIXELDATA>>> GetData() {
		return make_pair(head, pixels);
	}

	vector<uint32_t> GetDataToWrite() {
		return content_out;
	}
};

