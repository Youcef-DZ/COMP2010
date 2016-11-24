#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<map>
#include<vector>

using namespace std;
vector<string> split(const string &s, char delim);
void read_write(map<string, vector<int> >& wordsCount);
void find_word(map<string, vector<int> >& wordsCount, string& word);

int main() {
	map<string, vector<int>> wordsCount;

	read_write(wordsCount);

	string word;
	do {
		cout << "\nEnter a words to search: ";
		cin >> word;
		find_word(wordsCount, word);
	} while (word != "exit");

	system("pause");
	return 0;
}

void read_write(map<string, vector<int> >& wordsCount) {
	int numLines = 0;
	int numChars = 0;
	int numWords = 0;
	map<char, int> charCount;

	ifstream fin;
	ofstream words_out, chars_out;

	string file_name = "War_And_Peace.txt";
	string words_out_file = "word_count.txt";
	string chars_out_file = "character_count.txt";
	string line;

	fin.open(file_name);
	words_out.open(words_out_file);
	chars_out.open(chars_out_file);

	if (fin.fail()) {
		cout << "Failed to open " << file_name << endl;
		exit(1);
	}

	while (getline(fin, line)) {
		unsigned int size = line.size();
		for (unsigned int i = 0; i < size; i++) {
			charCount[line[i]]++;
			numChars++;

			// replace punctuations with a space
			if (ispunct(line[i])) { line[i] = ' '; }
		}

		// get words from string, separated by space
		vector<string> words = split(line, ' ');

		// count words
		for (unsigned int i = 0; i < words.size(); i++) {
			string word = words[i];
			// transform string to lower case
			transform(word.begin(), word.end(), word.begin(), ::tolower);
			// push word number into the vector in a map with the word as primary key
			wordsCount[word].push_back(numLines);
			numWords++;
		}

		numLines++; // count number of lines
	}

	for (map<char, int>::iterator it = charCount.begin(); it != charCount.end(); ++it) {
		chars_out << it->first << ": " << it->second << endl;
	}

	for (map<string, vector<int>>::iterator it = wordsCount.begin(); it != wordsCount.end(); ++it) {
		words_out << it->first << ": " << it->second.size() << endl;
	}

	cout << "number of lines		= " << numLines << endl;
	cout << "number of words		= " << numWords << endl;
	cout << "number of chars		= " << numChars << endl;
	cout << "number of unique words	= " << wordsCount.size() << endl;
	cout << "number of unique chars	= " << charCount.size() << endl;

	fin.close();
	words_out.close();
	chars_out.close();
}

void find_word(map<string, vector<int> >& wordsCount, string& word) {
	transform(word.begin(), word.end(), word.begin(), ::tolower);

	vector<int> result;
	for (map<string, vector<int>>::iterator it = wordsCount.begin(); it != wordsCount.end(); ++it) {
		if (word == it->first) {
			result = it->second;
		}
	}

	cout << "\"" << word << "\"" << " is found: " << result.size() << " times." << endl;
	cout << "In the following lines: " << endl;
	for (unsigned int i = 0; i < result.size(); i++) {
		if (i % 6 == 0) {
			cout << endl;
		}

		cout << result[i];

		if (i != (result.size() - 1)) {
			cout << ", ";
		}
		else { cout << "."; }
	}
}

vector<string> split(const string &s, char delim) {
	vector<string> elems;
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}