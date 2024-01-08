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
			cout << "У студента нет оценок" << endl;
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
	bool Mood = true;// true - хорошее, false - плохое
	teacher() {
		Name = "NoName";
	}
	teacher(string name, bool mood) {
		Name = name;
		Mood = mood;
	}

	void GiveGrade(student* student,string subName) {
		int n;
		int r = rand() % 2;
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
		student->TakeGrade(n, subName);
	}
};
