#include "util.h"

using namespace std;
using namespace util;

int main(int argc, const char * const * argv)
{
	if (argc < 4)
	{
		cerr << "ccmonad: usage error" << endl;
		exit(1);
	}
	string compiler = argv[1];
	string inputFile;
	vector<string> options;
	string outputFile;
	bool isNextOutput = false;
	for (int32_t i = 2; i < argc; i++)
	{
		if (strlen(argv[i]) > 0)
		{
			if (argv[i][0] == '-')
			{
				if (strlen(argv[i]) > 1 && argv[i][1] == 'o')
					isNextOutput = true;
				else if (strcmp(argv[i], "-c") != 0)
					options.push_back(argv[i]);
			}
			else
			{
				if (isNextOutput)
					outputFile = argv[i];
				else
				{
					if (inputFile == "")
						inputFile = argv[i];
					else
					{
						cerr << "ccmonad: error: ccmonad can only take one input file" << endl;
						exit(1);
					}
				}
			}
		}
	}
	if (outputFile == "")
	{
		cerr << "ccmonad: usage error" << endl;
		exit(1);
	}
#if 0
	cout << "Compiler: " << compiler << endl;
	cout << "Input: " << inputFile << endl;
	cout << "Output: " << outputFile << endl;
#endif

	if (!exists(inputFile))
	{
		cerr << "ccmonad: error: file not found: " << inputFile << endl;
		exit(1);
	}

	vector<string> args1 = options;
	args1.push_back("-c");
	args1.push_back(inputFile);
	args1.push_back("-o");
	args1.push_back(outputFile);
	int8_t result1 = exec(compiler, args1);
	if (result1 != 0)
	{
		vector<size_t> splits;
		splits.push_back(0); // for compiling something always (should be empty)

		ifstream input(inputFile.c_str());
		for (size_t line_i = 1; input.good(); line_i++)
		{
			string line;
			getline(input, line);
			vector<string> tokens = tokenize(line, " \t");
			if (tokens.size() >= 2 && tokens[0] == "#if" && tokens[1] == "MONAD_SPLIT")
				splits.push_back(line_i);
		}

		vector<string> intermediate_outputs; // = options;
		//intermediate_outputs.push_back("-shared");
		intermediate_outputs.push_back("-r");
		for (size_t split_i = 0; split_i < splits.size(); split_i++)
		{
			vector<string> args = options;
			args.push_back("-c");
			args.push_back(inputFile);
			args.push_back("-DMONAD_SPLIT_LINE_NUMBER=" + lexical_cast<string>(splits[split_i]));
			args.push_back("-o");
			args.push_back(outputFile + "." + split_i);
		
#if 0
			cout << "\tmonacc: " << compiler;
			for (size_t i = 0; i < args.size(); i++)
				cout << ' ' << args[i];
			cout << endl;
#endif

			int8_t result2 = exec(compiler, args);
			if (result2 == 0)
				intermediate_outputs.push_back(outputFile + "." + split_i);
		}
		intermediate_outputs.push_back("-o");
		intermediate_outputs.push_back(outputFile);

		return exec("ld", intermediate_outputs);
		//return exec("mv", intermediate_outputs[2], outputFile);
	}
	else
		return 0;
}
