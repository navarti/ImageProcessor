#pragma once
#include <cstdint>

typedef struct {
    uint8_t id[2];            // ������ �� ����� 'B' � 'M'
    uint32_t filesize;        // ����� ����� � ������   +++        
    uint16_t reserved[2];     // 0, 0
    uint32_t headersize;      // 54L ��� 24-����� ���������
    uint32_t infoSize;        // 40L ��� 24-����� ���������
    uint32_t width;           // ������ ���������� � �������  +++
    uint32_t depth;           // ������ ���������� � ������� +++
    uint16_t biPlanes;        // 1 (��� 24-����� ���������)
    uint16_t bits;            // 24 (��� 24-����� ���������)
    uint32_t biCompression;   // 0L
    uint32_t biSizeImage;     // ����� ��������� � 0L ��� ��������� ��� �������� (��� ������)
    uint32_t biXPelsPerMeter; // ������������� ������� ������ �� ����, ����� 0L
    uint32_t biYPelsPerMeter; // �� ����, �� �����
    uint32_t biClrUsed;       // ��� ������������ ���������, ����� ��������� 0L
    uint32_t biClrImportant;  // �� ����
} BMPHEAD;



typedef struct {
    uint8_t redComponent;     
    uint8_t greenComponent;
    uint8_t blueComponent;
} PIXELDATA;