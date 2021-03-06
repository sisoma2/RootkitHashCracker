// RootkitHashCracker.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

using namespace std;

// RSHash (Robert Sedgewick's string hashing algorithm)
unsigned int CalcRSHash(const char* str)
{
	unsigned int result = 0;
	unsigned int constant = 0xF8C9;

	while (*str)
	{
		if (*str < 'A' || *str > 'Z')
			result = *str + constant * result;
		else
			result = constant * result + *str + 0x20;
		constant *= 0x5C6B7;
		++str;
	}

	return result & 0x7FFFFFFF;
}

// Read file line by line and push line to vector of strings
bool readFileIntoVector(const char* filename, vector<string> &vector) {
	ifstream input(filename);
	
	if (input.fail()) {
		return false;
	}

	for (string line; getline(input, line); )
	{
		vector.push_back(line);
	}

	input.close();
	return true;
}

int main(int argc, const char* argv[])
{
	vector<string> vectorHashes;
	vector<string> vectorProcNames;
	unsigned int hashValue;
	unsigned int counter = 0;
	long long position = 0;
	bool cracked = false;

	// Say hello
	cout << "Rootkit Hash Cracker" << endl << endl;

	// Check arguments
	if (argc < 3) {
		cout << "[-] Too few arguments. File with hashes to crack and dictionary file with name of the processes needed." << endl;
		return -1;
	}

	// Read all the hashes to crack from the file and save it into vectorHashes as string
	if (!readFileIntoVector(argv[1], vectorHashes)) {
		cout << "[-] Error reading file: " << argv[1] << endl;
		return -2;
	}

	// Read all the process names from the dictionary file and save it into vectorProcNames
	if (!readFileIntoVector(argv[2], vectorProcNames)) {
		cout << "[-] Error reading file: " << argv[2] << endl;
		return -3;
	}
	
	// Iterate through all the hashes and calculate hashes for the processes
	for (vector<string>::iterator it = vectorHashes.begin(); it != vectorHashes.end(); ++it) {
		cracked = false;
		position = distance(vectorHashes.begin(), it);
		for (auto ProcName : vectorProcNames) {
			// convert string to int in hexa
			hashValue = stoi(*it, 0, 16);
			if ((CalcRSHash(ProcName.c_str()) == hashValue) && !cracked) {
				cout << "[+] Hash cracked: " << *it << " -> " << ProcName << " in position " << position << endl;
				cracked = true;
				counter++;
			}
		}
		if (!cracked) {
			cout << "[-] Hash not cracked: " << *it << " in position " << position << endl;
		}
	}

	// Number of total hashes cracked
	cout << endl << "Total number of hashes cracked: " << counter << "/" << vectorHashes.size() << endl;

    return 0;
}

