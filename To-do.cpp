#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int ID;  // To track the ID of tasks

// Custom type for tasks with ID and task description
struct Todo {
    int id;
    string task;
};

// Add New Task Method
void addTodo() {
    system("cls");
    cout << "\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t                                                                        " << endl;
    cout << "\t\t\t                       WELCOME TO Your TODO List                       " << endl;
    cout << "\t\t\t                                                                        " << endl;
    cout << "\t\t\t***********************************************************************" << endl << endl << endl;
    
    Todo todo;
    cout << "\n\tEnter new task: ";
    cin.get();
    getline(cin, todo.task);
    ID++; 

    // Write this task to the todo.txt file
    ofstream write("todo.txt", ios::app);
    write << "\n" << ID;
    write << "\n" << todo.task;
    write.close();

    // Update the ID file
    ofstream idFile("id.txt");
    idFile << ID;
    idFile.close();

    char ch;
    cout << "\n\tDo you want to add more tasks? (y or n): ";
    cin >> ch;

    if (ch == 'y') {
        addTodo();
    } else {
        cout << "\n\tTask has been added successfully.";
    }
}

// Display Added Tasks Method
void print(const Todo& s) {
    cout << "\tID: " << s.id;
    cout << "\tTask: " << s.task << endl;
}

// Read Added Tasks from todo.txt Method
void readData() {
    system("cls");
    cout << "\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t                                                                        " << endl;
    cout << "\t\t\t                       WELCOME TO Your TODO List                       " << endl;
    cout << "\t\t\t                                                                        " << endl;
    cout << "\t\t\t***********************************************************************" << endl << endl << endl;
    
    Todo todo;
    ifstream read("todo.txt");
    cout << "\n\t\t\t------------------Your current tasks in the list--------------------" << endl;
    
    while (read >> todo.id) {
        read.ignore();
        getline(read, todo.task);
        print(todo);
    }
    read.close();
}

// Search for a specific task from the todo.txt file Method
int searchData() {
    system("cls");
    cout << "\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t                                                                        " << endl;
    cout << "\t\t\t                       WELCOME TO Your TODO List                       " << endl;
    cout << "\t\t\t                                                                        " << endl;
    cout << "\t\t\t***********************************************************************" << endl << endl << endl;

    int id;
    cout << "\n\tEnter task ID: ";
    cin >> id;
    Todo todo;
    ifstream read("todo.txt");
    
    while (read >> todo.id) {
        read.ignore();
        getline(read, todo.task);
        if (todo.id == id) {
            print(todo);
            return id;
        }
    }
    read.close();
    return -1; // Return -1 if not found
}

// Delete Task Method
void deleteData() {
    system("cls");
    cout << "\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t                                                                        " << endl;
    cout << "\t\t\t                       WELCOME TO Your TODO List                       " << endl;
    cout << "\t\t\t                                                                        " << endl;
    cout << "\t\t\t***********************************************************************" << endl << endl << endl;

    int id = searchData();
    if (id == -1) {
        cout << "\n\tTask ID not found.";
        return;
    }

    cout << "\n\tDo you want to delete this task? (y or n): ";
    char choice;
    cin >> choice;
    if (choice == 'y') {
        Todo todo;
        ofstream tempFile("temp.txt");
        ifstream read("todo.txt");

        while (read >> todo.id) {
            read.ignore();
            getline(read, todo.task);
            if (todo.id != id) {
                tempFile << "\n" << todo.id;
                tempFile << "\n" << todo.task;
            }
        }
        read.close();
        tempFile.close();
        remove("todo.txt");
        rename("temp.txt", "todo.txt");
        cout << "\n\tTask deleted successfully.";
    } else {
        cout << "\n\tRecord not deleted.";
    }
}

// Main Function
int main() {
    system("cls");
    system("Color 2F"); // Set background color to light yellow and text color to black
    system("title TODO List Application");
    cout << "\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t*                                                                     *" << endl;
    cout << "\t\t\t*                      WELCOME TO Your TODO List                      *" << endl;
    cout << "\t\t\t*                                                                     *" << endl;
    cout << "\t\t\t***********************************************************************" << endl << endl << endl << endl;

    // Read the last used ID from file
    ifstream read("id.txt");
    if (!read.fail()) {
        read >> ID;
    } else {
        ID = 0;
    }
    read.close();

    while (true) {
        cout << endl << endl;
        cout << "\n\t1. Add new task";
        cout << "\n\t2. View all tasks";
        cout << "\n\t3. Search for a task";
        cout << "\n\t4. Delete a task";
        cout << "\n\t5. Exit";

        int choice;
        cout << "\n\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTodo();
                break;
            case 2:
                readData();
                break;
            case 3:
                searchData();
                break;
            case 4:
                deleteData();
                break;
            case 5:
                cout << "\n\tExiting the program. Goodbye!" << endl;
                return 0; // Exit the program
            default:
                cout << "\n\tInvalid choice. Please enter a number between 1 and 5." << endl;
        }
    }
}
