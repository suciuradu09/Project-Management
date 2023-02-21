#include "service.h"

void Service::store(int id, string desc, vector<string> prog, string stare)
{
	Task t{ id, desc, prog, stare };
	val.validate(t);
	repo.store(t);
}

vector<Task> Service::filterProgramer(const string& programator)
{
    vector<Task> sortat{ repo.getAllTasks() };
    vector<Task> new_list;
    std::copy_if(sortat.begin(), sortat.end(), back_inserter(new_list), [programator](const Task& t) {
        for (const auto& prog : t.getProgramatori())
        {
            if (prog == programator)
                return true;
        }
        return false;
        });
    return new_list;
}

bool Service::exists(const string p)
{
    for (const auto& task : repo.getAllTasks()) {
        for (const auto& prog : task.getProgramatori())
            if (prog == p)
                return true;
    }
    throw RepoException("Programatorul nu exista");
}

vector<Task> Service::sortStare()
{
    vector<Task> sortat{ repo.getAllTasks() };
    sort(sortat.begin(), sortat.end(), [&](Task& t1, Task& t2) {
        return t1.getStare() > t2.getStare();
        });
    return sortat;
}
