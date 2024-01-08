#include <iostream>
#include <string>
#include <vector>
using namespace std;


class student {
public:
	string Name;
	vector <int> grades;
	vector <string> subjects;
	student() {
		Name = "NoName";
	}

	student(string S) {
		Name = S;
	}
	void GetName() {
		cout << Name << endl;
	}
	void TakeGrade(int grade, string SubjectName) {
		if (grade > 0 and grade < 6) {
			grades.push_back(grade);
			subjects.push_back(SubjectName);
		}
		else {
			cout << "Оценка введена неверно" << endl;
		}
	}
	void GetGrade() {
		int k = 0;
		if (!grades.empty()) {
			while (k < grades.size()) {
				cout << subjects[k] << " " << grades[k] << endl;
				k++;
			}
		}
		else {
			cout << "У студента нет оценок" << endl;
		}
	}

	bool IsExelent() {
		int k=0;
		double sum = 0;
		if (!grades.empty()) {
			while (k < grades.size()) {
				sum += grades[k];
				k++;
			}
		}
		else {
			return false;
		}
		sum = sum / k;
		if (sum >= 4.5) {
			return true;
		}
		else {
			return false;
		}
		
	}
};

class teacher {
public:
	string Name;
	int TypeOfTeacher = rand() % 3; // 0 - зависит от настроения, 1 - всегда ставит 5, 2 - всегда ставит 2
	bool Mood = true;// true - хорошее, false - плохое
	int NumberOfGrades = 0;
	int TypeOfMoodChange = rand() % 3; // 0 - настроения меняется после 5 оценки, 1 - настроения меняется после 3 оценки, 2 - настроения меняется после 7 оценки

	teacher() {
		Name = "NoName";
	}

	teacher(string name, bool mood) {
		Name = name;
		Mood = mood;
	}

	void GetInfo() {
		cout << Name << " " << Mood << " " << TypeOfMoodChange << " " << NumberOfGrades << endl;
	}

	void GiveGrade(student* student,string subName) {
		int n;
		int r = rand() % 2;
		if (TypeOfTeacher == 1) {
			n = 5;
		}
		else if (TypeOfTeacher == 2) {
			n = 2;
		}
		else {
			if (Mood and student->IsExelent()) {
				n = 5;
			}
			else if (!Mood and student->IsExelent()) {
				if (r == 1) {
					n = 5;
				}
				else {
					n = 4;
				}
			}
			else if (Mood and ((student->IsExelent()) == false)) {
				n = 4;
			}
			else {
				if (r == 1) {
					n = 3;
				}
				else {
					n = 2;
				}
			}
		}
		
		student->TakeGrade(n, subName);
		NumberOfGrades++;
		int ChanceOfReverse = rand() % 2;// 0 - противоположное, 1 - не изменяется
		if ((TypeOfMoodChange == 0 and NumberOfGrades == 5) or (TypeOfMoodChange == 1 and NumberOfGrades == 3) or (TypeOfMoodChange == 2 and NumberOfGrades == 7)) {
			if (ChanceOfReverse == 0) {
				Mood = !Mood;
			}
			NumberOfGrades = 0;
		}
	}
};

class GroupOfStudents {
public:
	vector <student*> group;
	void AddStudent(student* stud) {
		group.push_back(stud);
	}
};

class lesson {
public:
	string Name;
	teacher* Teacher;
	vector <student*> Group;
	lesson() {
		Name = "NoLesson";
	}
	lesson(teacher* teacher1, vector <student*> group, string name) {
		Teacher = teacher1;
		Group = group;
		Name = name;
	}

	void GiveMarks() {
		int i = 0;

		if (!Group.empty()) {
			while (i < Group.size()) {
				int r = rand() % 2;
				while (r != 0) {
					r = rand() % 2;
					Teacher->GiveGrade(Group[i], Name);
				}
				i++;
			}
		}
		else {
			cout << "На занятии отсутствуют студенты" << endl;
		}
	}
};

class parent {
public:
	string Name;
	int Mood; //0 - плохое настроение, 1 - хорошее
	vector <student*> children;
	parent() {
		Name = "NoName";
		Mood = rand() % 2;
	}
	parent(string name) {
		Name = name;
		Mood = rand() % 2;
	}

	void AddChild(student* child) {
		children.push_back(child);
	}

	bool IsOwnChild(student* child) {
		int i = 0;
		if (!children.empty()) {
			while (i < children.size()) {
				if (children[i] == child) {
					return true;
				}
				i++;
			}
		}
		return false;
	}

	void TellAboutAll() {
		int i = 0;
		if (!children.empty()) {
			while (i < children.size()) {
				if (children[i]->IsExelent() and Mood == 1) {
					cout << children[i]->Name << " гениальный ребёнок" << endl;
				}
				else if (children[i]->IsExelent() and Mood == 0) {
					cout << children[i]->Name << " учится хорошо" << endl;
				}
				else if (!children[i]->IsExelent() and Mood == 1) {
					cout << children[i]->Name << " старается изо всех сил" << endl;
				}
				else {
					cout << children[i]->Name << " учится плохо" << endl;
				}
				i++;
			}
		}
		else {
			cout << "У меня нет детей" << endl;
		}
	}

	void TellRandom() {
		if (!children.empty()) {
			int i = rand() % (children.size());
			if (children[i]->IsExelent() and Mood == 1) {
				cout << children[i]->Name << " гениальный ребёнок" << endl;
			}
			else if (children[i]->IsExelent() and Mood == 0) {
				cout << children[i]->Name << " учится хорошо" << endl;
			}
			else if (!children[i]->IsExelent() and Mood == 1) {
				cout << children[i]->Name << " старается изо всех сил" << endl;
			}
			else {
				cout << children[i]->Name << " учится плохо" << endl;
			}
		}
		else {
			cout << "У меня нет детей" << endl;
		}
	}

	void TellSum() {
		int i = 0;
		if (!children.empty()) {
			double sum = 0;
			while (i < children.size()) {
				if (children[i]->IsExelent()) { 
					sum++; 
				}
				i++;
			}
			sum = sum / children.size();
			if (sum>=0.5 and Mood == 1) {
				cout << "Мои дети гении" << endl;
			}
			else if (sum >= 0.5 and Mood == 0) {
				cout << children[i]->Name << "Мои дети учатся хорошо" << endl;
			}
			else if (sum < 0.5 and Mood == 1) {
				cout << children[i]->Name << "Мои дети стараются изо всех сил" << endl;
			}
			else {
				cout << children[i]->Name << "Мои дети учатся плохо" << endl;
			}
		}
		else {
			cout << "У меня нет детей" << endl;
		}
	}

	void TellAboutOne(string name) {
		int i = 0;
		if (!children.empty()) {
			while (i < children.size()) {
				if (children[i]->Name == name) {
					if (children[i]->IsExelent() and Mood == 1) {
						cout << children[i]->Name << " гениальный ребёнок" << endl;
					}
					else if (children[i]->IsExelent() and Mood == 0) {
						cout << children[i]->Name << " учится хорошо" << endl;
					}
					else if (!children[i]->IsExelent() and Mood == 1) {
						cout << children[i]->Name << " старается изо всех сил" << endl;
					}
					else {
						cout << children[i]->Name << " учится плохо" << endl;
					}
					return;
				}
				i++;
			}
		}
		else {
			cout << "У меня нет детей" << endl;
		}
		cout << "У меня нет ребёнка с таким именем" << endl;
	}
};
