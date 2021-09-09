#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>
#include <limits>
#include <stdio.h>
using namespace std;
string subject[8] = {"Probability and Statistics", "Discrete Mathematics", "Economics", "Object Oriented Programming", "Data Structures and Algorithms", "Principle of Digital Communication", "Data Structures and Algorithms Lab", "Object Oriented Programming Lab"};
class Student
{
protected:
	char name[30];
	int credits[8] = {3, 3, 3, 3, 4, 4, 1, 1};
	float sgpa, cgpa, marks[8];
	int rollno, grade[8];

public:
	void getInfo()
	{	system("clear");
		cout << "Enter name: ";
		fgets(name, 30, stdin);
		cout << endl
			 << "Enter Roll No. : ";
		cin >> rollno;
	j1:
		cout << "Enter Previous CGPA : ";
		cin >> cgpa;
		if (cgpa > 10 || cgpa < 0 || isnan(cgpa))
		{
			cout << "CPGA entered outside accepted range!" << endl;
			goto j1;
		}
	}
	void initMarks()
	{
		cout << "Enter Marks as defined: \n"
			 << endl;
		for (int i = 0; i < 6; i++)
		{
			cout << subject[i] << ": "
				 << "\n"
				 << endl;
			marks[i] = getMarks();
			cout << "\n";
		}
		for (int i = 6; i < 8; i++)
		{
			cout << subject[i] << ": "
				 << "\n"
				 << endl;
			marks[i] = getLab();
			cout << "\n";
		}
	}
	float getLab()
	{
		float midterm, labfile, viva, endterm;
	jump1:
		cout << "Enter Midsem + Daily Evaluation Marks: ";
		cin >> midterm;
		if (midterm > 50 || midterm < 0)
		{
			cout << "Marks entered outside accepted range!" << endl;
			goto jump1;
		}
	jump2:
		cout << "Enter Lab File Marks: ";
		cin >> labfile;
		if (labfile > 10 || labfile < 0)
		{
			cout << "Marks entered outside accepted range!" << endl;
			goto jump2;
		}
	jump3:
		cout << "Enter Viva Marks: ";
		cin >> viva;
		if (viva > 10 || viva < 0)
		{
			cout << "Marks entered outside accepted range!" << endl;
			goto jump3;
		}
	jump4:
		cout << "Enter Lab Exam Marks: ";
		cin >> endterm;
		if (endterm > 30 || endterm < 0)
		{
			cout << "Marks entered outside accepted range!" << endl;
			goto jump4;
		}
		return midterm + labfile + endterm + viva;
	}
	float getMarks()
	{
		float midsem, internal, endsem, tot;
	jump1:
		cout << "Enter Midsem Marks: ";
		cin >> midsem;
		if (midsem > 20 || midsem < 0)
		{
			cout << "Marks entered outside accepted range!" << endl;
			goto jump1;
		}
	jump2:
		cout << "Enter Internal Marks: ";
		cin >> internal;
		if (internal > 30 || internal < 0)
		{
			cout << "Marks entered outside accepted range!" << endl;
			goto jump2;
		}
	jump3:
		cout << "Enter EndSem Marks: ";
		cin >> endsem;
		if (endsem > 50 || endsem < 0)
		{
			cout << "Marks entered outside accepted range!" << endl;
			goto jump3;
		}
		tot = midsem + internal + endsem;
		return tot;
	}
	void calcSgpa()
	{
		float obcr = 0;
		int totcr = 0;
		for (int i = 0; i < 8; i++)
			totcr += credits[i];
		for (int i = 0; i < 8; i++)
		{
			if (marks[i] == 100)
				grade[i] = 10;
			else
				grade[i] = (marks[i] / 10) + 1;
			obcr += grade[i] * credits[i];
		}
		sgpa = obcr / totcr;
	}
	virtual void calcCgpa()
	{
		cout << "You are not supposed to be here" << endl;
	}
	virtual void show()
	{
		cout << setfill('+') << setw(70) << ""
			 << "\n";
		cout << right << setfill(' ') << setw(57) << "KALINGA INSTITUTE OF INDUSTRIAL TECHNOLOGY"
			 << "\n";
		cout << setfill('-') << setw(70) << ""
			 << "\n";
		cout << left << setfill(' ') << setw(9) << "Name ";
		cout << ":";
		cout << left << setfill(' ') << setw(70) << name << endl;
		cout << left << setfill(' ') << setw(10) << "Roll No. :";
		cout << left << setfill(' ') << setw(70) << rollno << endl;
		cout << setfill('-') << setw(70) << ""
			 << "\n";
		cout << right << setfill(' ') << setw(46) << "Semester Grade Report"
			 << "\n";
		cout << left << setfill(' ') << setw(50) << "  Subject Name:";
		cout << left << setfill(' ') << setw(10) << "Marks:";
		cout << left << setfill(' ') << setw(10) << "Grade :"
			 << "\n"
			 << endl;
		for (int i = 0; i < 8; i++)
		{
			cout << "  ";
			cout << left << setfill(' ') << setw(50) << subject[i];
			cout << left << setfill(' ') << setw(10) << marks[i];
			cout << left << setfill(' ') << setw(10) << grade[i] << endl;
		}
		cout << setfill('-') << setw(70) << ""
			 << "\n";
		cout << right << setfill(' ') << setw(38) << "SGPA = " << fixed << setprecision(2) << sgpa << endl;
		cout << right << setfill(' ') << setw(38) << "CGPA = " << fixed << setprecision(2) << cgpa << endl;
		cout << setfill('+') << setw(70) << ""
			 << "\n";
	}
	friend void addToFile(const Student &);
	friend void readFromFile();
};
class cgpa : public Student
{
public:
	void calcCgpa()
	{
		Student::cgpa = (Student::cgpa * 2 + Student::sgpa) / 3;
	}
};
void addToFile(const cgpa &s)
{
	ofstream outFile("Student.txt", ios::app | ios::binary);
	outFile.write((char *)&s, sizeof(s));
	outFile.close();
}
void readFromFile()
{
	cgpa s;
	ifstream inFile("Student.txt", ios::in | ios::binary);
	while (inFile.read((char *)&s, sizeof(s)))
	{
		s.show();
		cout << setfill(' ') << setw(70) << ""
			 << "\n";
	}
	inFile.close();
}
float calcReq(float aim, float ob)
{
	float req;
	req = (aim * 3) - (2 * ob);
	return req;
}
int main()
{
	int choice;
	cout << setfill('~') << setw(70) << ""
		 << "\n";
	cout << setfill(' ') << setw(53) << "Welcome to Examination Grading System"
		 << "\n";
	cout << setfill('~') << setw(70) << ""
		 << "\n";
	do
	{
		cout << right << setfill(' ') << setw(42) << "Select Your Option:"
			 << "\n";
		cout << left << setfill(' ') << setw(30) << "1. Calculate SGPA";
		cout << endl;
		cout << left << setfill(' ') << setw(30) << "2. Estimate SGPA";
		cout << endl;
		cout << left << setfill(' ') << setw(30) << "3. Read Records From File";
		cout << endl;
		cout << left << setfill(' ') << setw(30) << "4. Exit";
		cout << endl;
		cout << setfill('~') << setw(70) << ""
			 << "\n\n";
		cout << left << setfill(' ') << setw(15) << "Your Choice:";
		cin >> choice;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (!choice)
		{
			cout << "Please Don't Enter a Character" << endl;
			choice = 0;
			continue;
		}
		system("clear");
		switch (choice)
		{
		case 1:
		{
			cout << setfill('_') << setw(70) << ""
				 << "\n\n";
			char ch1 = 'Y', ch2;
			while (ch1 == 'Y' || ch1 == 'y')
			{
				cgpa c;
				Student *s = &c;
				s->getInfo();
				s->initMarks();
				s->calcSgpa();
				s->calcCgpa();
				system("clear");
				s->show();
				cout << "Write to File? (Y/N)" << endl;
				cin >> ch2;
				if (ch2 == 'Y' || ch2 == 'y')
				{
					cout << "Writing to file!" << endl;
					addToFile(c);
				}
				cout << setfill('-') << setw(70) << ""
					 << "\n";
				cout << "Want to enter more data?(Y/N)" << endl;
				cin >> ch1;
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin.clear();
			}
			cout << setfill('_') << setw(70) << ""
				 << "\n\n";
			break;
		}
		case 2:
		{
			float cgpa, aim, req;
			cout << setfill('_') << setw(70) << ""
				 << "\n\n";
		j1:
			cout << "Enter Previous CGPA : ";
			cin >> cgpa;
			if (cgpa > 10 || cgpa < 0)
			{
				cout << "CPGA entered outside accepted range!" << endl;
				goto j1;
			}
		j2:
			cout << "Enter Expected CGPA : ";
			cin >> aim;
			if (aim > 10 || aim < 0)
			{
				cout << "CPGA entered outside accepted range!" << endl;
				goto j2;
			}
			req = calcReq(aim, cgpa);
			cout << endl;
			if (req > 10)
			{
				cout << right << setfill(' ') << setw(45) << "Required SGPA beyond 10" << endl;
			}
			else
				cout << right << setfill(' ') << setw(38) << "Required SGPA = " << fixed << setprecision(2) << req << endl;
			cout << setfill('_') << setw(70) << ""
				 << "\n\n";
			break;
		}
		case 3:
		{
			cout << "\n\n";
			system("clear");
			cout << right << setfill(' ') << setw(46) << "Printing Records From File"
				 << "\n";
			cout << "\n\n";
			readFromFile();
			cout << right << setfill(' ') << setw(43) << "End Of Records"
				 << "\n\n";
			cout << setfill('_') << setw(70) << ""
				 << "\n\n";
			break;
		}
		default:
			break;
		}
	} while (choice != 4);
}
