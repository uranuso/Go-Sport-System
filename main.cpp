#include"head.h"
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<stdexcept>
#include<windows.h>

using namespace std;

struct deleter {
	template<class T>
	void operator() (T* p) {
		delete p;
	}
};

vector<RunningAccount*>runningaccounts;
vector<RidingAccount*>ridingaccounts;

int main() {
	Date date(2022, 3, 1);

	SetColorAndBackground(14, 0);
	cout << "(a)Add account (r)Run (d)Ride (u)Runner's show (i)Rider's show (c)Change day (n)Next month (q)Quit " << endl;
	SetColorAndBackground(15, 0);
	char cmd;
	int index;
	RunningAccount* runningaccount;
	RidingAccount* ridingaccount;
	do {
		SetColorAndBackground(11, 0);
		cout << date;
		cout << "\tTotal Mileage: " << RunningAccount::getAllMileage() + RidingAccount::getAllMileage() << " Total Time: ";
		Time allTime = RunningAccount::getAllTime() + RidingAccount::getAllTime();
		cout << allTime;
		cout << "\tcommand>>>";
		SetColorAndBackground(15, 0);

		bool flag0 = false;
		while (!flag0) {
			cin >> cmd;
			switch (cmd) {
			case 'a': {
				SetColorAndBackground(14, 0);
				cout << "(r)Running (d)Riding >>>";
				SetColorAndBackground(15, 0);
				char accounttype;
				cin >> accounttype;
				if (accounttype == 'r') {
					SetColorAndBackground(14, 0);
					cout << "Please input your ID >>>";
					SetColorAndBackground(15, 0);
					std::string id;
					cin >> id;
					runningaccount = new RunningAccount(date, id);
					runningaccounts.push_back(runningaccount);
				}
				else if (accounttype == 'd') {
					SetColorAndBackground(14, 0);
					cout << "Please input your ID >>>";
					SetColorAndBackground(15, 0);
					std::string id;
					cin >> id;
					ridingaccount = new RidingAccount(date, id);
					ridingaccounts.push_back(ridingaccount);
				}
				else {
					SetColorAndBackground(12, 0);
					throw runtime_error("Invalid Instruction");
					SetColorAndBackground(15, 0);
				}
				flag0 = true;
				break;
			}
			case 'r': {
				double mileage = 0;
				int minute = 0, second = 0;
				cin >> index;
				if (index >= runningaccounts.size()) {
					SetColorAndBackground(12, 0);
					cout << "Invalid index!" << endl;
					SetColorAndBackground(15, 0);
					flag0 = true;
					continue;
				}
				SetColorAndBackground(14, 0);
				cout << "Please input mileage,minute,second in order >>>";
				SetColorAndBackground(15, 0);
				cin >> mileage;
				cin >> minute >> second;
				Time runTime(minute, second);
				runningaccounts[index]->running(date, mileage, runTime);
				flag0 = true;
				break;
			}
			case 'd': {
				double mileage = 0;
				int minute = 0, second = 0;
				cin >> index;
				if (index >= ridingaccounts.size()) {
					SetColorAndBackground(12, 0);
					cout << "Invalid index!" << endl;
					SetColorAndBackground(15, 0);
					flag0 = true;
					continue;
				}
				SetColorAndBackground(14, 0);
				cout << "Please input mileage,minute,second in order >>>";
				SetColorAndBackground(15, 0);
				cin >> mileage;
				cin >> minute >> second;
				Time runTime(minute, second);
				ridingaccounts[index]->riding(date, mileage, runTime);
				flag0 = true;
				break;
			}
			case 'u': {
				cin >> index;
				if (index >= runningaccounts.size()) {
					SetColorAndBackground(12, 0);
					cout << "Invalid index!" << endl;
					SetColorAndBackground(15, 0);
					flag0 = true;
					continue;
				}
				SetColorAndBackground(14, 0);
				cout << "(1)Phased show (2)Show (e)Exit >>>";
				SetColorAndBackground(15, 0);
				char cmd1;
				bool flag1 = false;
				while (!flag1) {
					cin >> cmd1;
					if (cmd1 == '1') {
						SetColorAndBackground(14, 0);
						cout << "(y)Year (m)Month of the year (e)Exit >>>";
						SetColorAndBackground(15, 0);
						char type;
						bool flag2 = false;
						while (!flag2) {
							cin >> type;
							if (type == 'y') {
								int year;
								cin >> year;
								Date d(year, 1, 1);
								runningaccounts[index]->singleShow("y", d);
								flag2 = true;
							}
							else if (type == 'm') {
								int year, month;
								cin >> year >> month;
								Date d(year, month, 1);
								runningaccounts[index]->singleShow("m", d);
								flag2 = true;
							}
							else if (type == 'e') {
								break;
							}
							else {
								SetColorAndBackground(12, 0);
								cout << "Invalid instruction:\"" << type << "\"! ";
								cout << "Please enter again." << endl;
								SetColorAndBackground(15, 0);
								//exit(1);
							}
						}
						flag1 = true;
					}
					else if (cmd1 == '2') {
						runningaccounts[index]->totShow();
						flag1 = true;
					}
					else if (cmd1 == 'e') {
						break;
					}
					else {
						SetColorAndBackground(12, 0);
						cout << "Invalid instruction:\"" << cmd1 << "\"! ";
						cout << "Please enter again." << endl;
						SetColorAndBackground(15, 0);
					}
				}
				flag0 = true;
				break;
			}
			case 'i': {
				cin >> index;
				if (index >= ridingaccounts.size()) {
					SetColorAndBackground(12, 0);
					cout << "Invalid index!" << endl;
					SetColorAndBackground(15, 0);
					flag0 = true;
					continue;
				}
				SetColorAndBackground(14, 0);
				cout << "(1)Phased show (2)Show (e)Exit >>>";
				SetColorAndBackground(15, 0);
				char cmd1;
				bool flag1 = false;
				while (!flag1) {
					cin >> cmd1;
					if (cmd1 == '1') {
						SetColorAndBackground(14, 0);
						cout << "(y)Year (m)Month of the year (e)Exit >>>";
						SetColorAndBackground(15, 0);
						char type;
						bool flag2 = false;
						while (!flag2) {
							cin >> type;
							if (type == 'y') {
								int year;
								cin >> year;
								Date d(year, 1, 1);
								ridingaccounts[index]->singleShow("y", d);
								flag2 = true;
							}
							else if (type == 'm') {
								int year, month;
								cin >> year >> month;
								Date d(year, month, 1);
								ridingaccounts[index]->singleShow("m", d);
								flag2 = true;
							}
							else if (type == 'e') {
								break;
							}
							else {
								SetColorAndBackground(12, 0);
								cout << "Invalid instruction:\"" << type << "\"! ";
								cout << "Please enter again." << endl;
								SetColorAndBackground(15, 0);
								//exit(1);
							}
						}
						flag1 = true;
					}
					else if (cmd1 == '2') {
						ridingaccounts[index]->totShow();
						flag1 = true;
					}
					else if (cmd1 == 'e') {
						break;
					}
					else {
						SetColorAndBackground(12, 0);
						cout << "Invalid instruction:\"" << cmd1 << "\"! ";
						cout << "Please enter again." << endl;
						SetColorAndBackground(15, 0);
					}
				}
				flag0 = true;
				break;
			}
			case 'c': {
				int day;
				cin >> day;
				if (day < date.getDay()) {
					SetColorAndBackground(12, 0);
					cout << "You can't specify a previous day." << endl;
					SetColorAndBackground(15, 0);
				}
				else if (day > date.getMaxDay()) {
					SetColorAndBackground(12, 0);
					cout << "Invalid date:\"day " << day << " \"! " << endl;
					SetColorAndBackground(15, 0);
				}
				else
					date = Date(date.getYear(), date.getMonth(), day);
				flag0 = true;
				break;
			}
			case 'n': {
				if (date.getMonth() == 12)
					date = Date(date.getYear() + 1, 1, 1);
				else
					date = Date(date.getYear(), date.getMonth() + 1, 1);
				Time umin(10000, 0);
				std::string fid = " ";
				for (int i = 0; i < runningaccounts.size(); i++) {
					if (umin > runningaccounts[i]->getPace()) {
						umin = runningaccounts[i]->getPace();
						fid = runningaccounts[i]->getId();
					}
				}
				if (fid != " ") {
					SetColorAndBackground(10, 0);
					cout << "#" << fid << " runs the fastest!" << endl;
					SetColorAndBackground(15, 0);
				}
				Time imin(10000, 0);
				fid = " ";
				for (int i = 0; i < ridingaccounts.size(); i++) {
					if (imin > ridingaccounts[i]->getPace()) {
						imin = ridingaccounts[i]->getPace();
						fid = ridingaccounts[i]->getId();
					}
				}
				if (fid != " ") {
					SetColorAndBackground(10, 0);
					cout << "#" << fid << " rides the fastest!" << endl;
					SetColorAndBackground(15, 0);
				}
				flag0 = true;
				break;
			}
			case 'q': {
				SetColorAndBackground(14, 0);
				cout << "Successfully quit the system." << endl;
				SetColorAndBackground(15, 0);
				flag0 = true;
				break;
			}
			default: {
				SetColorAndBackground(12, 0);
				cout << "Invalid instruction:\"" << cmd << "\"! ";
				cout << "Please enter again." << endl;
				SetColorAndBackground(14, 0);
				cout << "(a)Add account (r)Run (d)Ride (u)Runner's show (i)Rider's show (c)Change day (n)Next month (q)Quit " << endl;
				SetColorAndBackground(11, 0);
				cout << "command>>>";
				SetColorAndBackground(15, 0);
				break;
			}
			}
		}
	} while (cmd != 'q');

	for_each(runningaccounts.begin(), runningaccounts.end(), deleter());
	for_each(ridingaccounts.begin(), ridingaccounts.end(), deleter());

	return 0;
}