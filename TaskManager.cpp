#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <nlohmann/json.hpp> // JSON for Modern C++ (https://github.com/nlohmann/json)

using json = nlohmann::json;
using namespace std;

struct Task {
    int id;
    string title;
    bool done;
    string created_at;
};

string now() {
    time_t t = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&t));
    return string(buf);
}

vector<Task> loadTasks(const string &filename) {
    vector<Task> tasks;
    ifstream file(filename);
    if (!file.is_open()) return tasks;

    json j;
    file >> j;
    for (auto &item : j) {
        tasks.push_back({
            item["id"],
            item["title"],
            item["done"],
            item["created_at"]
        });
    }
    return tasks;
}

void saveTasks(const vector<Task> &tasks, const string &filename) {
    json j = json::array();
    for (const auto &t : tasks) {
        j.push_back({
            {"id", t.id},
            {"title", t.title},
            {"done", t.done},
            {"created_at", t.created_at}
        });
    }
    ofstream file(filename);
    file << setw(2) << j;
}

void listTasks(const vector<Task> &tasks) {
    cout << "\n===== LISTE DES TÂCHES =====\n";
    if (tasks.empty()) {
        cout << "Aucune tâche trouvée.\n";
        return;
    }
    for (const auto &t : tasks) {
        cout << "#" << t.id << " [" << (t.done ? "✔" : " ") << "] "
             << t.title << " (créée le " << t.created_at << ")\n";
    }
}

void addTask(vector<Task> &tasks) {
    cin.ignore();
    cout << "Titre de la tâche : ";
    string title;
    getline(cin, title);

    int id = tasks.empty() ? 1 : tasks.back().id + 1;
    tasks.push_back({id, title, false, now()});
    cout << "Tâche ajoutée !\n";
}

void markDone(vector<Task> &tasks) {
    int id;
    cout << "ID de la tâche à marquer terminée : ";
    cin >> id;
    for (auto &t : tasks) {
        if (t.id == id) {
            t.done = true;
            cout << "Tâche #" << id << " marquée comme terminée.\n";
            return;
        }
    }
    cout << "Tâche non trouvée.\n";
}

void deleteTask(vector<Task> &tasks) {
    int id;
    cout << "ID de la tâche à supprimer : ";
    cin >> id;
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            tasks.erase(it);
            cout << "Tâche supprimée.\n";
            return;
        }
    }
    cout << "Tâche non trouvée.\n";
}

int main() {
    const string filename = "tasks.json";
    vector<Task> tasks = loadTasks(filename);

    int choice;
    do {
        cout << "\n=== GESTIONNAIRE DE TÂCHES ===\n";
        cout << "1. Lister les tâches\n";
        cout << "2. Ajouter une tâche\n";
        cout << "3. Marquer une tâche comme terminée\n";
        cout << "4. Supprimer une tâche\n";
        cout << "0. Quitter\n";
        cout << "Choix : ";
        cin >> choice;

        switch (choice) {
            case 1: listTasks(tasks); break;
            case 2: addTask(tasks); saveTasks(tasks, filename); break;
            case 3: markDone(tasks); saveTasks(tasks, filename); break;
            case 4: deleteTask(tasks); saveTasks(tasks, filename); break;
            case 0: cout << "Au revoir 👋\n"; break;
            default: cout << "Choix invalide.\n"; break;
        }
    } while (choice != 0);

    saveTasks(tasks, filename);
    return 0;
}
