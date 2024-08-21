#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Task {
	string description;
	bool completed;
};

void displayMenu() {
	cout << "\nTo-Do List Manager\n";
	cout << "1. Add Task\n";
	cout << "2. View Tasks\n";
	cout << "3. Mark Task as Completed\n";
	cout << "4. Remove Task\n";
	cout << "5. Exit\n";
	cout << "Enter your choice: ";
}

void addTask(vector<Task>& tasks) {
	Task newTask;
	cout << "Enter task description: ";
	cin.ignore();
	getline(cin, newTask.description);
	newTask.completed = false;
	tasks.push_back(newTask);
	cout << "Task added.\n";
}

void viewTasks(const vector<Task>& tasks) {
	if (tasks.empty()) {
		cout << "No tasks in the list.\n";
	} else {
		for (size_t i = 0; i < tasks.size(); ++i) {
			cout << i + 1 << ". " << tasks[i].description << " ["
			     << (tasks[i].completed ? "Completed" : "Pending") << "]\n";
		}
	}
}

void markTaskCompleted(vector<Task>& tasks) {
	int taskNumber;
	cout << "Enter task number to mark as completed: ";
	cin >> taskNumber;
	if (taskNumber > 0 && taskNumber <= tasks.size()) {
		tasks[taskNumber - 1].completed = true;
		cout << "Task marked as completed.\n";
	} else {
		cout << "Invalid task number.\n";
	}
}

void removeTask(vector<Task>& tasks) {
	int taskNumber;
	cout << "Enter task number to remove: ";
	cin >> taskNumber;
	if (taskNumber > 0 && taskNumber <= tasks.size()) {
		tasks.erase(tasks.begin() + taskNumber - 1);
		cout << "Task removed.\n";
	} else {
		cout << "Invalid task number.\n";
	}
}

int main() {
	vector<Task> tasks;
	int choice;
	bool running = true;

	while (running) {
		displayMenu();
		cin >> choice;

		switch (choice) {
		case 1:
			addTask(tasks);
			break;
		case 2:
			viewTasks(tasks);
			break;
		case 3:
			markTaskCompleted(tasks);
			break;
		case 4:
			removeTask(tasks);
			break;
		case 5:
			running = false;
			cout << "Exiting the program.\n";
			break;
		default:
			cout << "Invalid choice. Please try again.\n";
		}
	}

	return 0;
}
