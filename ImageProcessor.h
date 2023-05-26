#pragma once
#include "Structs.h"
#include <string>
#include <vector>


using namespace std;

class ImageProcessor
{
	int n;
	
	BMPHEAD head;
	BMPHEAD new_head;
	vector<vector<PIXELDATA>> pixels;
	vector<vector<PIXELDATA>> new_pixels;

	void IncreaseHead() {
		int headsize = head.filesize - head.width * head.depth * sizeof(PIXELDATA);
		
		new_head.depth *= n;
		new_head.width *= n;
		new_head.filesize = headsize + new_head.depth * new_head.width * sizeof(PIXELDATA);
		return;
	}

	void IncreasePixels() {	

		for (int i = 0; i < new_head.depth; i++) {
			vector<PIXELDATA> row;
			for (int j = 0; j < new_head.width; j++) {
				row.push_back(PIXELDATA());
			}
			new_pixels.push_back(row);
		}

		
		int index_row = 0;
		int index_col = 0;
		for (int i = 0; i < pixels.size(); i++) {
			
			for (int j = 0; j < pixels[0].size(); j++) {	
				PIXELDATA to_add = pixels[i][j];

				for (int k = index_row; k < index_row + n; k++) {
					for (int h = index_col; h < index_col + n; h++) {						
						new_pixels[k][h] = to_add;
					}
				}
				index_col += n;
			}
			index_row += n;
			index_col = 0;
		}
		return;
	}

public:
	ImageProcessor(int _n, pair<BMPHEAD, vector<vector<PIXELDATA>>> data) :
		n(_n), head(data.first), pixels(data.second), new_head(data.first) {}

	
	void IncreaseSize() {
		IncreaseHead();
		IncreasePixels();
	}

	pair<BMPHEAD, vector<vector<PIXELDATA>>> GetData() {
		return make_pair(new_head, new_pixels);
	}
};

