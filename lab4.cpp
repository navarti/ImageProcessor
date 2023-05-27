#include <iostream>
#include "ImageProcessor.h"
#include "Parser.h"
#include "Structs.h"
#include "FileReader.h"
#include "Validator.h"

using namespace std;

bool CheckValidator(Validator* validator) {
    if (!validator->IsValid()) {
        validator->PrintErrors();
        exit(3);
    }
}

int main(int argc, char* argv[])
{
    Validator validator;
    validator.CheckArguments(argc, argv);
    CheckValidator(&validator);
    
    FileReader fr(&validator);
    Parser parser(&validator);
    pair<BMPHEAD, vector<uint8_t>> data = fr.ReadFile(argv[1]);
    CheckValidator(&validator);

    pair<BMPHEAD, vector<vector<PIXELDATA>>> parsed_data = parser.GetDataToProcess(&data);
    CheckValidator(&validator);

    ImageProcessor ip(stoi(argv[3]), &parsed_data);
    ip.IncreaseSize();
    fr.Write(parser.GetDataToWrite(ip.GetData()), argv[2]);
    CheckValidator(&validator);

    cout << "Success";
}

