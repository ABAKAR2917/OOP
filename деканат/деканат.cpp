#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Group {
    string name;
    vector<string> Students;
};

struct Subject {
    string name;
    string teacher;
};

class SortedTreeNode {
public:
    string studentName;
    SortedTreeNode* left;
    SortedTreeNode* right;

    SortedTreeNode(string name) : studentName(name), left(nullptr), right(nullptr) {}
};

class SortedTree {
private:
    SortedTreeNode* root;

    void insert(SortedTreeNode*& node, const string& name) {
        if (!node) {
            node = new SortedTreeNode(name);
        }
        else if (name < node->studentName) {
            insert(node->left, name);
        }
        else {
            insert(node->right, name);
        }
    }

    void inOrderTraversal(SortedTreeNode* node, ostream& os) {
        if (node) {
            inOrderTraversal(node->left, os);
            os << node->studentName << endl;
            inOrderTraversal(node->right, os);
        }
    }

public:
    SortedTree() : root(nullptr) {}

    void insert(const string& name) {
        insert(root, name);
    }

    void printInOrder(ostream& os) {
        inOrderTraversal(root, os);
    }
};

int main() {
    int nGroups, nSubjects;

    ifstream in("groups.txt");
    if (!in) {
        cerr << "Ошибка открытия файла groups.txt" << endl;
        return 1;
    }

    in >> nGroups;
    vector<Group> groups(nGroups);
    in.ignore();

    for (int i = 0; i < nGroups; i++) {
        getline(in, groups[i].name);
        string studentName;

        while (getline(in, studentName)) { // Читаем до пустой строки
            groups[i].Students.push_back(studentName);
        }

        cout << "Группа " << groups[i].name << " успешно сохранена!" << endl << endl;
    }

    ifstream in2("predmets.txt");
    if (!in2) {
        cerr << "Ошибка открытия файла predmets.txt" << endl;
        return 1;
    }

    in2 >> nSubjects;
    vector<Subject> subjects(nSubjects);
    in2.ignore();

    for (int i = 0; i < nSubjects; i++) {
        in2 >> subjects[i].name >> subjects[i].teacher;
        cout << "Предмет " << subjects[i].name << " успешно сохранён!" << endl << endl;
    }

    while (true) {
        int tmp;
        cout << "\n\nВыберите тип ведомости (0 - зачёт, 1 - экзамен): ";
        cin >> tmp;

        while (tmp != 0 && tmp != 1) {
            cout << "Ошибка: введите 0 для зачёта или 1 для экзамена." << endl;
            cout << "Попробуйте снова: ";
            cin >> tmp;
        }

        string typeVed = (tmp == 1) ? "экзамен" : "зачёт";

        for (int i = 0; i < nGroups; i++) {
            cout << i << ": " << groups[i].name << endl;
        }

        int group;
        do {
            cout << "Выберите группу, сдающую " << typeVed << ": ";
            cin >> group;

            if (group < 0 || group >= nGroups) {
                cout << "Ошибка: выберите корректный номер группы." << endl;
            }
        } while (group < 0 || group >= nGroups);

        for (int i = 0; i < nSubjects; i++) {
            cout << i << ": " << subjects[i].name << endl;
        }

        int subject;
        do {
            cout << "Выберите предмет, который сдаёт группа " << groups[group].name << ": ";
            cin >> subject;

            if (subject < 0 || subject >= nSubjects) {
                cout << "Ошибка: выберите корректный номер предмета." << endl;
            }
        } while (subject < 0 || subject >= nSubjects);

        // Генерация ведомости
        cout << (typeVed == "экзамен" ? "Экзаменационная ведомость" : "Зачётная ведомость") << endl;
        cout << "Преподаватель: " << subjects[subject].teacher << endl;
        cout << "Группа: " << groups[group].name << endl;
        cout << "Предмет: " << subjects[subject].name << endl;

        SortedTree studentTree;

        for (const auto& fio : groups[group].Students) {
            studentTree.insert(fio);
        }

        cout << "Список студентов:" << endl;
        studentTree.printInOrder(cout);

        system("pause");
    }

    return 0;
}
