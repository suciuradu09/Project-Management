#pragma once
#include "domain.h"
#include "validator.h"
#include <iostream>

/// <summary>
/// clasa repo exception pentru tratarea erorilor in repository
/// </summary>
class RepoException {
private:
	string msg;
public:
	RepoException(string msg) : msg{ msg } {};
	string getErrorMessage() {
		return this->msg;
	}
};

class RepoFile {
private:
	vector<Task> allTasks;
	string filename;

	void loadFromFile();
	void saveToFile();
public:
	/// <summary>
	/// Constructorul repository-ului
	/// </summary>
	/// <param name="filename"> numele fisierului in care este stocat initial </param>
	RepoFile(string filename) : filename{ filename } {
			loadFromFile();
	};

	void store(const Task& t);

	bool exists(const Task& t);

	vector<Task>& getAllTasks();
};

