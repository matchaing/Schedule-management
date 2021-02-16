//Calendar Management Program
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

struct Day {
	int year, month, day;
	string name;
};
struct Fday {
	int year, month, day, tmonth, tday;
	string name;
};

class Schedule {
protected:
	int count, fcount;
	Day *da;
	Fday *fa;
public:
	Schedule();
	void showschedule(int, int);
	void set_Schedule(); 
	void out_todo(int, int);
	void out_user(int, int);
};

Schedule::Schedule() {
	ifstream fin("user.txt");
	fin >> count; 
	da = new Day[count + 5];
	for (int i = 0; i < count; i++) {
		fin >> da[i].year >> da[i].month >> da[i].day >> da[i].name; 
	}
	fin.close();
}


void Schedule::showschedule(int y, int m) {
	int i;
	for (i = 0; i < count; i++) {
		if ((da[i].year == y) && (da[i].month == m)) {
			cout << da[i].month << "/" << da[i].day << "/"<< da[i].year << " " << da[i].name << endl;
		}
	}
}

void Schedule::set_Schedule() {
	int iyear, imonth, iday, num;
	string iname;
	do {
		system("cls");
		cout << endl << "\t [ 1. Register schedule ] " << endl;
		cout << "   Enter date(month day year):";
		cin >> imonth >> iday >> iyear;
		if ((imonth < 0) || (imonth > 13)) set_Schedule();
		da[count].year = iyear; da[count].month = imonth; da[count].day=iday;
		cout << "   Calendar name(Please enter in ENG): ";
		cin >> iname;

		da[count].name = iname;

		
		ofstream fout("user.txt",ios::app); //파일이어쓰기
		fout << endl << da[count].month << " "<< da[count].day <<" " << da[count].year << " "<< da[count].name;
		count++;
		fout.close();
		
		cout << endl << "       < Successfully registered! > " << endl;
		cout << "   1. Register another schedule " << endl << "   2. Return to Main menu " << endl << "   --> ";
		cin >> num;
		if (num != 1 && num != 2) {
			cout << endl << "   You've entered something wrong. Please re-enter: ";
			cin >> num;
		}
		if (num == 2) {
			system("cls"); break; }
	} while (num == 1);
}

void Schedule::out_todo(int iny, int inm) {
	int i;
	string fname;
	ifstream che("academic_calendar.txt");
	che >> fcount; 
	fa = new Fday[fcount + 5];
	for (i = 0; i < fcount; i++) {
		che >> fa[i].month >> fa[i].day >> fa[i].tmonth >> fa[i].tday >> fa[i].year;
		che >> fname;
		fa[i].name = fname;
	}
	che.close();
	for (i = 0; i < fcount; i++) {
		if ((fa[i].year == iny) && (fa[i].month == inm)) {
			cout << fa[i].month << "/" << fa[i].day << " - " <<
				fa[i].tmonth << "/" << fa[i].tday << "/" << fa[i].year << " " << fa[i].name << endl;
		}
	}
}
void Schedule::out_user(int iny, int inm) {
	int i,j;
	ifstream use("user.txt");
	use >> j;
	da = new Day[count + 1];
	for (i = 0; i < count; i++) 
		use >> da[i].month >> da[i].day >> da[i].year >> da[i].name;
	use.close();
	for (i = 0; i < count; i++) {
		if ((da[i].year == iny) && (da[i].month == inm))
			cout << da[i].month << "/" << da[i].day << "/" << da[i].year << " " << da[i].name << endl;
	}
}

class ToDo : protected Schedule {
	int max_day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
public:
	ToDo() {};
	void print_calendar(int, int);
	void findschedule();
	int yoonyear(int year) {
		if ((year % 4 == 0) && !(year % 100 == 0) || (year % 400 == 0))
			return 1;
		else return 0;
	}
};

void ToDo::print_calendar(int year, int month) {
	int i, sum, k;
	char week[7][4] = { {"SUN"}, {"MON"}, {"TUE"}, {"WED"}, {"THU"}, {"FRI"}, {"SAT"} };
	if (yoonyear(year)) 
		max_day[1] = 29;
	else max_day[1] = 28;


	sum = 365;
	for (i = 1; i < year; i++) {
		if (yoonyear(i)) sum += 366;
		else sum += 365;
	}
	for (i = 0; i < month - 1; i++) {
		sum += max_day[i];
	}
	k = sum % 7;

	cout << endl << endl << "\t      " << month << " / " << year;
	cout << "\n---------------------------------------\n";
	if (month >= 1 && month <= 12) {
		for (int i = 0; i < 7; i++)
			cout << week[i] << "   ";
	}
	cout << "\n---------------------------------------\n"; 
	for (int j = 0; j < k; j++) {
		cout << "      ";
	}
	for (int i = 1; i <= max_day[month - 1]; i++) {
		cout << fixed << right << setw(3) << i << "   ";
		if (k == 6) {
			k = -1;
			cout << endl;
		}
		k++;
	}
	cout << "\n---------------------------------------\n" << endl;
}


void ToDo::findschedule() {
	int num, ytodo, mtodo;
	do {
		system("cls");
		cout << endl << "\t [ 2. Search schedule ] " << endl;
		cout << "    Month Year: ";
		cin >> mtodo >> ytodo;
		if ((mtodo <= 0) || (mtodo > 13)) {
			cout << "    You've entered something wrong. Please re-enter: ";
			findschedule();
		}
		print_calendar(ytodo, mtodo); //캘린더
		cout << " [ Academic Calendar ] " << endl;
		out_todo(ytodo, mtodo); //학사일정
		cout << endl << " [ Personal Schedule ]" << endl;
		out_user(ytodo, mtodo); //사용자일정

		cout << endl << "       < Your search is complete! > " << endl;
		cout << "   1. Search again " << endl << "   2. Return to Main menu " << endl << "   --> ";
		cin >> num;
		if (num != 1 && num != 2) {
			cout << endl << "   You've entered something wrong. Please re-enter: ";
			cin >> num;
		}
		if (num == 2) {
			system("cls"); break; }
	} while (num == 1);
}


int main() {  
	int select;
	Schedule sch;
	ToDo to;
	cout << "   < Launches a calendar management program >" << endl << endl << "      ...Loading... ";
	while (1) {
		system("cls");
		cout << endl << endl << "   [ Calendar Management Program ]" << endl << endl;
		cout << "   1. Register schedule" << endl << "   2. Search schedule" << endl << "   3. Exit" << endl;
		cout << endl << "   --> Please enter the number of the Main menu you want: ";
		cin >> select;
		cout << endl << endl;
		switch (select) {
		case 1:
			sch.set_Schedule();
			break;
		case 2:
			to.findschedule();
			break;
		case 3:
			cout << endl << "  Exit the program." << endl;
			return 0;
		default:
			cout << endl << "   You've entered something wrong. Please re-enter." << endl;
			system("cls");
			break;
		}
	}
	return 0;
}