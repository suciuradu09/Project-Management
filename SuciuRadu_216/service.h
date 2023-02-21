#pragma once
#include "domain.h"
#include "repository.h"
#include "observer.h"
#include <string>
#include <functional>
#include <algorithm>
#include <iterator>

using std::sort;

class Service : public Observable{
private:
	RepoFile& repo;
	validator& val;
public:
	Service(RepoFile repo, validator val) : repo{ repo }, val{ val }{};
	Service(Service& ot) = delete;

	void store(int id, string desc, vector<string> prog, string stare);
	/// <summary>
	/// Functionalitatea verifica daca un anumit programator exista in lista
	/// </summary>
	/// <param name="p"> programatorul cautat</param>
	/// <returns>true daca e gasit false in caz contrar</returns>
	bool exists(const string p);

	/// <summary>
	/// Filtrare vector de taskuri in functie de un nume de programator
	/// </summary>
	/// <param name="programator"> programatorul dupa care se face filtrarea </param>
	/// <returns>vectorul filtrat de taskuri </returns>
	vector<Task> filterProgramer(const string& programator);

	/// <summary>
	/// Sorteaza taskurile in functie de starea lor
	/// </summary>
	/// <returns> vectorul de taskuri ordonat dupa stare </returns>
	vector<Task> sortStare();

	/// <summary>
	/// returneaza toate taskurile existente in fisier
	/// </summary>
	/// <returns></returns>
	vector<Task> getAllTasksService() {
		return this->repo.getAllTasks();
	}
};


