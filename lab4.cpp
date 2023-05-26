#include <iostream>
#include "ImageProcessor.h"
#include "Parser.h"
#include "FileReader.h"
#include "Validator.h"

using namespace std;

//будуть завтра

bool is_number(const std::string& s);
bool is_file(const std::string& s);


int main(int argc, char* argv[])
{
    Validator validator;
    validator.CheckArguments(argc, argv);
    
    FileReader fr;
    Parser parser;
    parser.ProcessContent(fr.ReadFile(argv[1]));

    ImageProcessor ip(stoi(argv[3]), parser.GetData());
    ip.IncreaseSize();

    parser.ParseToWrite(ip.GetDaata());
    fr.Write(parser.GetDataToWrite(), string(argv[2]));

    cout << "Success";
}





