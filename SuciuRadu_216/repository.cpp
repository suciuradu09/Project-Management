#include "repository.h"
#include <sstream>
#include <fstream>
#include <iostream>
using std::stringstream;
using namespace std;
using std::stoi;

void RepoFile::loadFromFile()
{
	ifstream fin(this->filename);

	if (!fin.is_open())
		throw RepoException("Fisierul nu poate fi deschis");

	string line;
	while (getline(fin, line)) {
		int id = 0;
		string descriere;
		vector<string> programatori;
		string stare;

		int line_no = 0;
		string curent_item;
		stringstream fin_line(line);
		while (getline(fin_line, curent_item, ';'))
		{
			if (line_no == 0) id = stoi(curent_item);
			if (line_no == 1) descriere = curent_item;
			if (line_no == 2)
			{
				string programator;
				stringstream fin_pr(curent_item);
				while (getline(fin_pr, programator, ','))
				{
					programatori.push_back(programator);
				}
			}
			if (line_no == 3) stare = curent_item;
			line_no++;
		}
		Task t(id, descriere, programatori, stare);
		this->store(t);
	}
	fin.close();
}

void RepoFile::saveToFile()
{
	ofstream fout(this->filename);

	if (!fout.is_open())
		throw RepoException("Nu se poate deschide fisierul");

	for (const Task& t : this->allTasks)
	{
		fout << t.getID() << ';' << t.getDescriere() << ';';
		fout << t.getProgramatori()[0];
		for (int i = 1; i < t.getProgramatori().size(); i++)
		{
			fout << ',' << t.getProgramatori()[i];
		}
		fout << ';' << t.getStare() << '\n';
	}
	fout.close();
}

void RepoFile::store(const Task& t)
{
	if (exists(t)) {
		throw RepoException("Taskul exista deja");
	}
	this->allTasks.push_back(t);
}

bool RepoFile::exists(const Task& t)
{
	for (const Task& task : this->allTasks) {
		if (task.getID() == t.getID())
			return true;
	}
	return false;
}

vector<Task>& RepoFile::getAllTasks()
{
	return this->allTasks;
}
