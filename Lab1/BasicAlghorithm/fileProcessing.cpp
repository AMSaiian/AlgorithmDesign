#include "fileProcessing.h"

void createFirstFiles(string source)
{
	ifstream input(source);
	vector<ofstream> auxiliary;
	string auxName = "";
	for (int i = 1; i <= 4; i++)
	{
		auxName = "B" + to_string(i) + ".txt";
		auxiliary.push_back(ofstream(auxName));
	}
	while (!input.eof())
	{
		for (int i = 0; i < 4; i++)
		{
			if (!input.eof())
			{
				writeSeries(auxiliary[i], input);
			}
		}
	}
	input.close();
	for (int i = 0; i < 4; i++)
	{
		auxiliary[i].close();
	}
}

void writeSeries(ofstream& receiver, ifstream& source)
{
	long int previous;
	long int current;
	auto parse = [&source](long& number) {string input = ""; source >> input; number = stol(input); };
	bool flag = true;
	parse(previous);
	receiver << " " << previous;
	int digits = 0;
	while (flag && !source.eof())
	{
		parse(current);
		if (previous <= current)
		{
			receiver << " " << current;
		}
		else
		{
			flag = false;
			if (current == 0)
				digits = 1;
			else if (current < 0)
				digits = (int)log10(abs(current)) + 2;
			else
				digits = (int)log10(current) + 1;
			source.seekg(-digits, ios::cur);
		}
		previous = current;
	}
}

void sort()
{
	bool direction = false;
	vector<ofstream> receiver;
	vector<ifstream> source;
	string recName = "";
	string srcName = "";
	while (moreThanOneNotEmpty())
	{
		recName = direction ? "B" : "C";
		srcName = !direction ? "B" : "C";
		for (int i = 1; i <= 4; i++)
		{
			receiver.push_back(ofstream(recName + to_string(i) + ".txt", ios::trunc));
			source.push_back(ifstream(srcName + to_string(i) + ".txt"));
		}
		mergingFiles(receiver, source, direction);
		direction = !direction;
		receiver.clear();
		source.clear();
	}
}

bool moreThanOneNotEmpty()
{
	int counter = 0;
	auto isEmpty = [](ifstream& stream) -> bool
	{
		return !stream.tellg();
	};
	for (int i = 1; i <= 4; i++)
	{
		ifstream B("B" + to_string(i) + ".txt", ios::ate);
		ifstream C("C" + to_string(i) + ".txt", ios::ate);
		if (!isEmpty(B))
			counter++;
		else if (!isEmpty(C))
			counter++;
		B.close();
		C.close();
		if (counter >= 2)
			return true;
	}
	return false;
}

void mergingFiles(vector<ofstream>& receiver, vector<ifstream>& source, bool direction)
{
	string recName = direction ? "B" : "C";
	string srcName = !direction ? "B" : "C";
	vector<long> elements(4, numeric_limits<long>::min());
	auto checkEnd = [&elements]() 
	{
		for (auto elem : elements)
		{
			if (elem != numeric_limits<long>::max())
			{
				return false;
			}
		}
		return true;
	};
	auto getNum = [&source, &elements](int index)
	{
		long temp = numeric_limits<long>::max();
		int digits = 0;
		if (elements[index] == numeric_limits<long>::max())
			return;
		if (!source[index].eof())
		{
			source[index] >> temp;
			if (elements[index] > temp)
			{
				if (temp == 0)
					digits = 1;
				else if (temp < 0)
					digits = (int)log10(abs(temp)) + 2;
				else
					digits = (int)log10(temp) + 1;
				source[index].seekg(-digits, ios::cur);
				temp = numeric_limits<long>::max();
			}
		}
		else
			temp = numeric_limits<long>::max();
		elements[index] = temp;
	};
	for (int i = 0; i < 4; i++)
	{
		getNum(i);
	}
	int recieverNum = -1;
	while (!checkEnd())
	{
		recieverNum++;
		recieverNum %= 4;
		do
		{
			long smaller = numeric_limits<long>::max();
			int indexSmaller = -1;
			for (int i = 0; i < 4; i++)
			{
				if (elements[i] == numeric_limits<long>::max())
					continue;
				if (elements[i] < smaller)
				{
					smaller = elements[i];
					indexSmaller = i;
				}
			}
			receiver[recieverNum] << " " << smaller;
			getNum(indexSmaller);
		} while (!checkEnd());
		elements = vector<long>(4, numeric_limits<long>::min());
		for (int i = 0; i < 4; i++)
		{
			getNum(i);
		}
	}
	for (int i = 1; i <= 4; i++)
	{
		receiver[i - 1].close();
		source[i - 1].close();
		ofstream temp(srcName + to_string(i) + ".txt", ios::trunc);
		temp.close();
	}
}

bool checkOrder()
{
	ifstream in("B1.txt", ios::binary);
	in.seekg(0, ios::beg);
	long previous;
	long current;
	in >> previous;
	bool flag = true;
	while (!in.eof())
	{
		in >> current;
		if (current < previous)
		{
			flag = false;
			break;
		}
		previous = current;
	}
	return flag;
}
