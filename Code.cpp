#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


class student {
public:
	string Name;
	vector <int> grades;
	vector <string> subjects;
	string ParentName = " ";
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
	string className;

	teacher() {
		Name = "NoName";
		className = "Unknown";
	}

	teacher(string name, bool mood, string classname) {
		Name = name;
		Mood = mood;
		className = classname;
	}

	void GetInfo() {
		cout << Name << " " << Mood << " " << TypeOfMoodChange << " " << NumberOfGrades << endl;
	}

	void GiveGrade(student* student) {
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
		
		student->TakeGrade(n, className);
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
					Teacher->GiveGrade(Group[i]);
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
		child->ParentName = Name;
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

	void TellWithSubject(string sbj) {
		int i = 0;
		if (!children.empty()) {
			while (i < children.size()) {
				if (!children[i]->subjects.empty()) {
					int k = 0;
					while (k < children[i]->subjects.size()) {
						if (children[i]->subjects[k] == Name) {
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
							break;
						}
						k++;
					}
				}
				i++;
			}
		}
		else {
			cout << "У меня нет детей" << endl;
		}
	}
};

class GrandMother {
public:
	string Name;
	int Mood; //0 - плохое настроение, 1 - хорошее
	vector <student*> children;
	GrandMother() {
		Name = "NoName";
		Mood = rand() % 2;
	}
	GrandMother(string name) {
		Name = name;
		Mood = rand() % 2;
	}

	void AddChild(student* child) {
		children.push_back(child);
		child->ParentName = Name;
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
				cout << children[i]->Name << " гениальный ребёнок" << endl;
			}
		}
		else {
			cout << "У меня нет детей/внуков" << endl;
		}
	}

	void TellRandom() {
		if (!children.empty()) {
			int i = rand() % (children.size());
			cout << children[i]->Name << " гениальный ребёнок" << endl;
		}
		else {
			cout << "У меня нет детей/внуков" << endl;
		}
	}

	void TellSum() {
		int i = 0;
		if (!children.empty()) {

			cout << "Мои дети гении" << endl;
		}
		else {
			cout << "У меня нет детей/внуков" << endl;
		}
	}

	void TellAboutOne(string name) {
		int i = 0;
		if (!children.empty()) {
			while (i < children.size()) {
				if (children[i]->Name == name) {
					cout << children[i]->Name << " гениальный ребёнок" << endl;
					return;
				}
				i++;
			}
		}
		else {
			cout << "У меня нет детей/внуков" << endl;
		}
		cout << "У меня нет ребёнка/внука с таким именем" << endl;
	}

	void TellWithSubject(string sbj) {
		int i = 0;
		if (!children.empty()) {
			while (i < children.size()) {
				if (!children[i]->subjects.empty()) {
					int k = 0;
					while (k < children[i]->subjects.size()) {
						if (children[i]->subjects[k] == Name) {
							cout << children[i]->Name << " гениальный ребёнок" << endl;
							break;
						}
						k++;
					}
				}
				i++;
			}
		}
		else {
			cout << "У меня нет детей/внуков" << endl;
		}
	}

	void TellAboutAnyChild(student* child) {
		if (IsOwnChild(child)) {
			cout << child->Name << " гениальный ребёнок" << endl;
		}
		else {
			if (child->IsExelent() and Mood == 1) {
				cout << child->Name << " гениальный ребёнок" << endl;
			}
			else if (child->IsExelent() and Mood == 0) {
				cout << child->Name << " учится хорошо" << endl;
			}
			else if (!child->IsExelent() and Mood == 1) {
				cout << child->Name << " старается изо всех сил" << endl;
			}
			else {
				cout << child->Name << " учится плохо" << endl;
			}
		}
	}
};

class meeting {
public:
	
	vector <GrandMother*> grandmothers;
	vector <parent*> parents;
	vector <teacher*> TeachersNow;
	vector <student*> students;
	vector <lesson*> lessons;
	vector <string> ParentNames;

	void addLesson(lesson* lesson) {
		
		lessons.push_back(lesson);
		if (!lesson->Group.empty()) {
			int i = 0;
			while (i < lesson->Group.size()) {
				students.push_back(lesson->Group[i]);
				i++;
			}
		}
	}
	void addParent(parent* parent) {
		parents.push_back(parent);
		ParentNames.push_back(parent->Name);
	}
	void addTeacher(teacher* teacher) {
		TeachersNow.push_back(teacher);
	}
	void addGrandMother(GrandMother* parent) {
		grandmothers.push_back(parent);
		ParentNames.push_back(parent->Name);
	}


	void MakeList() {
		cout << "Список отсутствующих родителей: ";
		bool flag = false;
		for (int i = 0; i < students.size(); i++) {
			if (ParentNames.end() == find(ParentNames.begin(), ParentNames.end(), students[i]->ParentName)) {
				flag = true;
				cout << students[i]->ParentName << "  ";
			}
		}
		if (flag == false) {
			cout << "Все присутствуют";
		}
		cout << endl;
		cout << endl;
	}

	void ParentTell() {
		for (int i = 0; i < lessons.size(); i++) {
			if (TeachersNow.end() == find(TeachersNow.begin(), TeachersNow.end(), lessons[i]->Teacher)) {
				cout << lessons[i]->Teacher->Name << " отсутствует" << endl;
			}
			else {
				cout << "Урок " << lessons[i]->Name << endl;
				for (int j = 0; j < parents.size(); j++) {
					cout << parents[j]->Name << " говорит:" << endl;
					for (int k = 0; k < parents[j]->children.size(); k++) {
						if (students.end() != find(students.begin(), students.end(), parents[j]->children[k])) {
							parents[j]->TellAboutOne(parents[j]->children[k]->Name);
						}
					}
					cout << endl;
				}
				cout << endl;
			}
		}
	}
	void GrandMotherTell() {
		for (int i = 0; i < lessons.size(); i++) {
			if (TeachersNow.end() == find(TeachersNow.begin(), TeachersNow.end(), lessons[i]->Teacher)) {
				cout << lessons[i]->Teacher->Name << " отсутствует" << endl;
			}
			else {
				cout << "Урок " << lessons[i]->Name << endl;
				for (int j = 0; j < grandmothers.size(); j++) {
					cout << grandmothers[j]->Name << " говорит:" << endl;
					for (int k = 0; k < grandmothers[j]->children.size(); k++) {
						if (students.end() != find(students.begin(), students.end(), grandmothers[j]->children[k])) {
							grandmothers[j]->TellAboutOne(grandmothers[j]->children[k]->Name);
						}
					}
					cout << endl;
				}
				cout << endl;
			}
		}
	}

};

//Этап 9
//В предметной области появляется Бабушка, которая являясь родителем / опекуном ребёнка может выступать на собраниях и обладает теми же функциями, что и Родитель.Единственное, что у Бабушка всегда о своих детях говорит хорошо, а о чужих по - настроению.
//


int main()
{
	srand((unsigned)time(NULL));
	setlocale(LC_ALL, "Russian");
	student* first = new student("Alex");
	student* second = new student("Stella");
	// 1 этап
	first->TakeGrade(4, "math");
	first->TakeGrade(5, "russian language");
	first->TakeGrade(4, "russian language");
	second->TakeGrade(5, "math");
	second->TakeGrade(4, "math");
	second->TakeGrade(5, "russian language");
	first->GetGrade();
	if (first->IsExelent()) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}
	if (second->IsExelent()) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}
	// 2+3 этапы
	teacher* teacher1 = new teacher("Anabel", true, "Chemistry");
	teacher1->GiveGrade(first);
	first->GetGrade();
	// 4 этап
	GroupOfStudents group1;
	group1.AddStudent(first);
	group1.AddStudent(second);
	lesson* lesson1 = new lesson(teacher1, group1.group, "IT");
	lesson1->GiveMarks();
	first->GetGrade();
	cout << endl;
	second->GetGrade();
	cout << endl;
	// 5 этап
	teacher* teacher2 = new teacher("1", true, "Math");
	teacher* teacher3 = new teacher("2", false, "Language");
	teacher* teacher4 = new teacher("3", true, "IT");
	student* student1 = new student("Somebody");
	teacher2->GiveGrade(student1);
	teacher2->GiveGrade(student1);
	student1->GetGrade();
	teacher3->GiveGrade(student1);
	teacher3->GiveGrade(student1);
	student1->GetGrade();
	teacher4->GiveGrade(student1);
	teacher4->GiveGrade(student1);
	student1->GetGrade();
	// 6 этап
	teacher* teacher5 = new teacher("Joseph", true, "Math");
	student* student2 = new student("Peter");
	teacher5->GetInfo();
	teacher5->GiveGrade(student2);
	teacher5->GetInfo();
	teacher5->GiveGrade(student2);
	teacher5->GetInfo();
	teacher5->GiveGrade(student2);
	teacher5->GetInfo();
	teacher5->GiveGrade(student2);
	teacher5->GetInfo();
	teacher5->GiveGrade(student2);
	teacher5->GetInfo();
	teacher5->GiveGrade(student2);
	teacher5->GetInfo();
	teacher5->GiveGrade(student2);
	teacher5->GetInfo();
	// 7 этап
	parent* parent1 = new parent("Olga");
	parent1->AddChild(first);
	parent1->AddChild(second);
	parent1->AddChild(student1);
	parent1->AddChild(student2);
	parent1->TellAboutAll();
	parent1->TellAboutOne("Alex");
	parent1->TellRandom();
	// 8 этап
	GroupOfStudents group2;
	GroupOfStudents group3;
	student* student3 = new student("B");
	student* student4 = new student("C");
	student* student5 = new student("D");
	student* student6 = new student("E");
	student* student7 = new student("F");
	student* student8 = new student("G");
	student* student9 = new student("H");
	student* student10 = new student("I");
	student* student11 = new student("J");
	student* student12 = new student("K");
	student* student13 = new student("L");
	student* student14 = new student("M");
	student* student15 = new student("S");

	group2.AddStudent(student3);
	group2.AddStudent(student4);
	group2.AddStudent(student5);
	group2.AddStudent(student6);
	group2.AddStudent(student7);
	group2.AddStudent(student10);
	group2.AddStudent(student15);
	group3.AddStudent(student8);
	group3.AddStudent(student9);
	group3.AddStudent(student10);
	group3.AddStudent(student11);
	group3.AddStudent(student4);
	group3.AddStudent(student7);

	parent* parent2 = new parent("Q");
	parent* parent3 = new parent("QQ");
	parent* parent4 = new parent("QQQ");
	parent* parent5 = new parent("QQQQ");
	parent* parent6 = new parent("QQQQQ");
	parent2->AddChild(student3);
	parent2->AddChild(student4);
	parent2->AddChild(student5);
	parent3->AddChild(student6);
	parent3->AddChild(student7);
	parent4->AddChild(student8);
	parent4->AddChild(student9);
	parent4->AddChild(student10);
	parent5->AddChild(student11);
	parent5->AddChild(student12);
	parent6->AddChild(student13);
	parent6->AddChild(student14);


	teacher* teacher6 = new teacher("Georgi", false, "Language");
	teacher* teacher7 = new teacher("Anna", true, "Math");
	lesson* lesson2 = new lesson(teacher6, group2.group, teacher6->className);
	lesson* lesson3 = new lesson(teacher7, group3.group, teacher7->className);

	lesson2->GiveMarks();
	lesson3->GiveMarks();

	meeting* meeting1 = new meeting();
	meeting1->addLesson(lesson2);
	meeting1->addLesson(lesson3);
	meeting1->addTeacher(teacher6);
	meeting1->addParent(parent2);
	meeting1->addParent(parent3);
	meeting1->addParent(parent4);
	meeting1->addParent(parent6);
	meeting1->ParentTell();
	meeting1->MakeList();
	// этап 9
	GrandMother* grandmom1 = new GrandMother("Bella");
	grandmom1->AddChild(student15);
	group2.AddStudent(student15);
	lesson2->Group = group2.group;
	lesson2->GiveMarks();
	meeting* meeting2 = new meeting();
	meeting2->addLesson(lesson2);
	meeting2->addLesson(lesson3);
	meeting2->addTeacher(teacher6);
	meeting2->addParent(parent2);
	meeting2->addParent(parent3);
	meeting2->addParent(parent4);
	meeting2->addParent(parent6);
	meeting2->addGrandMother(grandmom1);
	meeting2->GrandMotherTell();
	meeting2->MakeList();


}
