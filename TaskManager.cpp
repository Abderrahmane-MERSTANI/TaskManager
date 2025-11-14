#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <optional>
#include <algorithm>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

// ======================= STRUCT =======================
struct Task {
    int id;
    string title;
    bool done;
    string created_at;
};

// ======================= UTILS ========================
string now() {
    time_t t = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&t));
    return string(buf);
}

int nextId(const vector<Task>& tasks) {
    if (tasks.empty()) return 1;
    return max_element(tasks.begin(), tasks.end(),
        [](const Task& a, const Task& b) { return a.id < b.id; }
    )->id + 1;
}

// ======================= JSON IO =======================
vector<Task> loadTasks(const string& filename) {
    vector<Task> tasks;
    ifstream file(filename);

    if (!file.is_open()) return tasks;

    try {
        json j;
        file >> j;

        for (auto& item : j) {
            tasks.push_back({
                item.value("id", 0),
                item.value("title", "Sans titre"),
                item.value("done", false),
                item.value("created_at", "unknown")
            });
        }
    } catch (...) {
        cerr << "Erreur: fichier JSON corrompu.\n";
    }

    return tasks;
}

void saveTasks(const vector<Task>& tasks, const string& filename) {
    json j = json::array();
    for (const auto& t : tasks) {
        j.push_back({
            {"id", t.id},
            {"title", t.title},
            {"done", t.done},
            {"created_at", t.created_at}
        });
    }

    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Erreur: impossible d'écrire dans " << filename << "\n";
        return;
    }
    file << setw(2) << j;
}

// ======================= OPERATIONS =======================
void listTasks(const vector<Task>& tasks) {
    cout << "\n===== LISTE DES TÂCHES =====\n";
    if (tasks.empty()) {
        cout << "Aucune tâche disponible.\n";
        return;
    }

    for (const auto& t : tasks) {
        cout << "#" << t.id 
             << " [" << (t.done ? "✔" : " ") << "] "
             << t.title 
             << " (créée le " << t.created_at << ")\n";
    }
}

void addTask(vector<Task>& tasks) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Titre de la tâche : ";
    string title;
    getline(cin, title);

    if (title.empty()) {
        cout << "Erreur: titre vide.\n";
        return;
    }

    tasks.push_back({
        nextId(tasks),
        title,
        false,
        now()
    });

    cout << "Tâche ajoutée avec succès !\n";
}

optional<Task*> findTask(vector<Task>& tasks, int id) {
    for (auto& t : tasks) {
        if (t.id == id) {
            return &t;
        }
    }
    return nullopt;
}

void markDone(vector<Task>& tasks) {
    cout << "ID de la tâche : ";
    int id; cin >> id;

    auto t = findTask(tasks, id);
    if (!t) {
        cout << "Tâche non trouvée.\n";
        return;
    }

    (*t.value())->done = true;
    cout << "Tâche marquée terminée.\n";
}

void deleteTask(vector<Task>& tasks) {
    cout << "ID de la tâche : ";
    int id; cin >> id;

    auto it = remove_if(tasks.begin(), tasks.end(),
                        [id](const Task& t) { return t.id == id; });

    if (it == tasks.end()) {
        cout << "Tâche introuvable.\n";
        return;
    }

    tasks.erase(it, tasks.end());
    cout << "Tâche supprimée.\n";
}

// ======================= MAIN =======================
int main() {
    const string filename = "tasks.json";
    vector<Task> tasks = loadTasks(filename);

    int choice;
    do {
        cout << "\n=== GESTIONNAIRE DE TÂCHES ===\n"
             << "1. Lister les tâches\n"
             << "2. Ajouter une tâche\n"
             << "3. Marquer une tâche comme terminée\n"
             << "4. Supprimer une tâche\n"
             << "0. Quitter\n"
             << "Votre choix : ";
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

    return 0;
}
