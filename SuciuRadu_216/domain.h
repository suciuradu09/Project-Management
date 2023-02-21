#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

/// <summary>
/// Clasa specifica obiectului de tip Task
/// </summary>
class Task {
private:
	int id;
	string descriere;
	vector<string> programatori;
	string stare;
public:
	/// <summary>
	/// Constructorul obiectului
	/// </summary>
	/// <param name="id"> id-ul obiectului</param>
	/// <param name="descriere"> descrierea obiectului </param>
	/// <param name="prog">programatorii obiectului</param>
	/// <param name="stare">starea obiectului </param>
	Task(int id, string descriere, vector<string> prog, string stare) : id{ id }, descriere{ descriere }, programatori{ prog }, stare{ stare } {};
	// copy constructor
	Task(const Task& ot) : id{ ot.id }, descriere{ ot.descriere }, programatori{ ot.programatori }, stare{ ot.stare }{};

	/// <summary>
	/// Gettere si settere specifice clasei
	/// </summary>
	/// <returns></returns>
	int getID() const {
		return this->id;
	}
	/// <summary>
	/// getter descriere
	/// </summary>
	/// <returns></returns>
	string getDescriere() const {
		return this->descriere;
	}
	/// <summary>
	/// getter programator
	/// </summary>
	/// <returns></returns>
	vector<string> getProgramatori() const {
		return this->programatori;
	}
	/// <summary>
	/// stare task
	/// </summary>
	/// <returns></returns>
	string getStare() const {
		return this->stare;
	}
	/// <summary>
	/// comparare obiecte de tip Task
	/// </summary>
	/// <param name="t1"></param>
	/// <param name="t2"></param>
	/// <returns></returns>
	bool cmpStare(const Task& t1, const Task& t2) {
		return t1.getStare() > t2.getStare();
	}

};