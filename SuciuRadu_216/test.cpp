#include "domain.h"
#include "validator.h"
#include "service.h"
#include "test.h"
#include <cassert>

void test() {
	RepoFile repoTest{ "testFile.txt " };
	
	vector<Task> v1 = repoTest.getAllTasks();
	
	assert(v1[0].getID() == 1);
	
	assert(v1[0].getProgramatori().size() == 3);
	
	assert(v1[0].getStare() == "open");
	
	assert(v1[1].getID() == 2);
	
	assert(v1[2].getID() == 3);
	
	assert(v1[3].getID() == 4);
	
	v1 = repoTest.getAllTasks();
	
	assert(v1.size() == 4);
	
	validator val;
	Service ser{ repoTest, val };
	vector<Task> v4 = ser.getAllTasksService();

	Task t1{ -1, "Ceva", {"Alin"}, "open" };
	
	try {
		val.validate(t1);
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(true);
	}

	Task t2{ 10, "", {"Alin"}, "open" };
	
	try {
		val.validate(t2);
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(true);
	}

	Task t3{ 10, "Ceva", {}, "open" };
	
	try {
		val.validate(t3);
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(true);
	}

	Task t4{ 10, "Ceva", {"Alin"}, "altceva" };
	
	try {
		val.validate(t4);
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(true);
	}

	Task t5{ 10, "Ceva", {"Alin", "Marian", "Daniel", "Cojocaru", "Paul"}, "inprogress"};

	try {
		val.validate(t5);
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(true);
	}

}