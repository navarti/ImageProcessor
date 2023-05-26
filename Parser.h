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
		head.reserved[1] = Read(sizeof(head.reserved[0]));
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

public:
	void ProcessContent(vector<uint8_t> _content) {
		content_in = _content;
		index = 0;
		
		ProcessBMPHEAD();
		int skip = (4 - (head.width * sizeof(PIXELDATA)) % 4)%4;

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
		
		int skip = (4 - (data.first.width * sizeof(PIXELDATA)) % 4)%4;

		for (const vector<PIXELDATA>& row : data.second) {
			for (const PIXELDATA& pixel : row) {
				content_out.push_back(pixel.redComponent);
				content_out.push_back(pixel.greenComponent);
				content_out.push_back(pixel.blueComponent);
			}
			for (int i = 0; i < skip; i++) {
				content_out.push_back(0);
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

