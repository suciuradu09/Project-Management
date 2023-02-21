#pragma once
#include "domain.h"
/// <summary>
/// Exceptie la validare
/// preia mesajul exceptiei 
/// </summary>
class ValidationException {
private:
	vector<string> msg;
public:

	ValidationException(vector<string> msg) : msg{ msg } {};
	string getErrorMessage() {
		string messages = "";
		for (const auto& e : msg) {
			messages += e + '\n';
		}
		return messages;
	}
};
/// <summary>
/// Clasa specifica validatorului 
/// valideaza obiecte de tip Task
/// </summary>
class validator {
public:
	void validate(const Task& t) {
		vector<string> errors;
		if (t.getID() < 0)
			errors.push_back("Id-ul trebuie sa fie pozitiv");
		if (t.getDescriere() == "")
			errors.push_back("Descrierea nu trebuie sa fie nula");
		if (t.getProgramatori().size() < 1 || t.getProgramatori().size() > 4)
			errors.push_back("Numarul de programatori este incorect");
		if (t.getStare() != "open" and t.getStare() != "closed" and t.getStare() != "inprogress")
			errors.push_back("Starea proiectului este incorecta");
		if (!errors.empty())
			throw ValidationException(errors);
	}
};