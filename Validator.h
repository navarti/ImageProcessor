#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Validator
{
	vector<string> errors;

    bool is_number(const std::string& s)
    {
        return !s.empty() && std::find_if(s.begin(),
            s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    }

    bool is_file(const std::string& s) {
        return s.rfind(".bmp") != string::npos;
    }
public:
    bool IsValid() {
        return errors.size() == 0;
    }

	void PrintErrors() {
		for (const string& err : errors) {
			cout << err;
		}
	}

    void AddError(string err) {
        errors.push_back(err);
    }

	void CheckArguments(int argc, char* argv[]) {
        if (argc != 4)
        {
            errors.push_back("Pass 3 arguments to launch the program (input file, output file, number to increase)\n");
            return;
        }

        string input_filename = argv[1];
        string output_filename = argv[2];
        string number_to_increase = argv[3];

        if (!is_file(input_filename) || !is_file(output_filename) || !is_number(number_to_increase)) {
            errors.push_back("Arguments are incorrect\n");
            return;
        }
	}



};

