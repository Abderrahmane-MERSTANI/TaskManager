# 📝 TaskManager (C++)

Un petit gestionnaire de tâches en ligne de commande écrit en **C++17**.  
Les tâches sont stockées dans un fichier JSON (`tasks.json`).

## ⚙️ Fonctionnalités
- Ajouter une tâche
- Afficher toutes les tâches
- Marquer une tâche comme terminée
- Supprimer une tâche
- Sauvegarde automatique dans un fichier JSON

## 🚀 Installation
1. Cloner le dépôt :
   ```bash
   git clone https://github.com/<ton-nom-utilisateur>/TaskManager.git
   cd TaskManager
Télécharger la dépendance JSON :

json.hpp

la placer dans le dossier du projet.

Compiler :

bash
Copier le code
g++ -std=c++17 main.cpp -o taskmanager
Lancer :

bash
Copier le code
./taskmanager
🧠 Exemple d’utilisation
markdown
Copier le code
=== GESTIONNAIRE DE TÂCHES ===
1. Lister les tâches
2. Ajouter une tâche
3. Marquer une tâche comme terminée
4. Supprimer une tâche
0. Quitter
Choix : 2
Titre de la tâche : Faire les devoirs
Tâche ajoutée !
💡 Améliorations possibles
Ajout de dates d’échéance et priorités

Interface graphique avec Qt

Sauvegarde automatique chiffrée

Synchronisation Cloud (API REST)

🪪 Licence
MIT — libre d’utilisation, modification et distribution.

yaml
Copier le code

---

## 🧾 `.gitignore`
*.exe
*.out
*.json
*.o

yaml
Copier le code

---

Souhaites-tu que je t’ajoute aussi un **`CMakeLists.txt`** (pour un projet CMake complet prêt à ouvrir dans Visual Studio Code / CLion) ?  
👉 Je peux le générer automatiquement pour toi.
