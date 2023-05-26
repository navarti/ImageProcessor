#include <iostream>
#include "ImageProcessor.h"
#include "Parser.h"
#include "FileReader.h"

using namespace std;

//будуть завтра

bool is_number(const std::string& s);
bool is_file(const std::string& s);


int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "Pass 3 arguments to launch the program (input file, output file, number to increase)\n";
        return 3;
    }

    string input_filename = argv[1];
    string output_filename = argv[2];
    string number_to_increase = argv[3];

    if (!is_file(input_filename) || !is_file(output_filename) || !is_number(number_to_increase)) {
        cout << "Arguments are incorrect\n";
        return 3;
    }

    FileReader fr;
    Parser parser;
    parser.ProcessContent(fr.ReadFile(input_filename));

    ImageProcessor ip(stoi(number_to_increase), parser.GetData());
    ip.IncreaseSize();
    parser.ParseToWrite(ip.GetDaata());
    
    fr.Write(parser.GetDataToWrite(), output_filename);

    cout << "Success";
}


bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

bool is_file(const std::string& s) {
    return s.rfind(".bmp") != string::npos;
}




