#include"head.h"
#include<iostream>
#include<string>
#include<cstdlib>
#include<stdexcept>
#include<windows.h>

using namespace std;

void SetColorAndBackground(int ForgC, int BackC) {
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}

Date::Date(int year, int month, int day)
	:year(year), month(month), day(day) {
	if (year <= 1000 || year >= 2500 || month <= 0 || month > 12 || day <= 0 || day > getMaxDay()) {
		SetColorAndBackground(12, 0);
		throw runtime_error("Invalid date!");
		//cout<<"Invalid date: ";show();cout<<"!"<<endl;
		//exit(1);/////////////////////////
		SetColorAndBackground(15, 0);
	}
}
int Date::getMaxDay() const {
	if (isLeapYear() && month == 2) {
		return 29;
	}
	else {
		int maxday = 0;
		switch (month) {
		case 1:maxday = 31; break;
		case 2:maxday = 28; break;
		case 3:maxday = 31; break;
		case 4:maxday = 30; break;
		case 5:maxday = 31; break;
		case 6:maxday = 30; break;
		case 7:maxday = 31; break;
		case 8:maxday = 31; break;
		case 9:maxday = 30; break;
		case 10:maxday = 31; break;
		case 11:maxday = 30; break;
		case 12:maxday = 31; break;
		}
		return maxday;
	}
}
void Date::show() const {
	cout << getYear() << "-" << getMonth() << "-" << getDay();
}
ostream& operator<<(ostream& out, const Date& date) {
	out << date.getYear() << "-" << date.getMonth() << "-" << date.getDay();
	return out;
}

Time::Time(int minute = 0, int second = 0)
	:minute(minute), second(second) {};
void Time::show() {
	cout << minute << "'" << second << "\"";
}
Time Time::operator+(const Time& t2)const {
	int x = (second + t2.second) / 60;
	return Time(minute + t2.minute + x, (second + t2.second) % 60);
	return Time(minute + t2.minute, second + t2.second);
}
Time Time::operator/(const double& m)const {
	int totSecond = minute * 60 + second;
	return Time((int)(totSecond / m) / 60, (int)(totSecond / m) % 60);
}
bool Time::operator>(const Time& t1)const {
	int second = 0;
	second = minute * 60 + second;
	int t1second = t1.minute * 60 + t1.second;
	return second > t1second;
}
ostream& operator<<(ostream& out, const Time& time) {
	out << time.getMinute() << "'" << time.getSecond() << "\"";
	return out;
}

Account::Account(const Date& date, const std::string& id)
	:id(id), date(date) {
	SetColorAndBackground(11, 0);
	cout << date;
	cout << "\t#" << id << " is created" << endl;
	SetColorAndBackground(15, 0);
}
void Account::error(const std::string& msg) const {
	SetColorAndBackground(12, 0);
	cout << "Error:(#" << id << "):" << msg << endl;
	SetColorAndBackground(15, 0);
}
void Account::totShow() {
	if (totMileage == 0) {
		SetColorAndBackground(12, 0);
		error("divided by zero!");
		SetColorAndBackground(15, 0);
		pace = (0, 0);
		//exit(1);/////////////////////////
	}
	else {
		pace = totTime / totMileage;// 重载运算符 
	}
	SetColorAndBackground(11, 0);
	cout << "#" << id << endl << "     \ttotal mileage: " << totMileage << " km" << endl;
	cout << "     " << "\ttotal time: " << totTime << " minutes" << endl;
	cout << "     " << "\taverage pace: " << pace << " minutes/km" << endl;
	SetColorAndBackground(15, 0);
}
void Account::singleShow() {};

RunningAccount::RunningAccount(const Date& date, const std::string& id)
	:Account(date, id) {}
double RunningAccount::allMileage = 0;
Time RunningAccount::allTime = Time(0, 0);
void RunningAccount::running(Date &date,double mileage,Time time){
	allMileage += mileage;
	totMileage += mileage;//同时用数组计算每年每月的跑量  check
	yearMileage[date.getYear() - 1000] += mileage;
	monthMileage[date.getYear() - 1000][date.getMonth()] += mileage;
	
	allTime = allTime + time;
	totTime = totTime + time;
	yearTime[date.getYear() - 1000] = yearTime[date.getYear() - 1000] + time;
	monthTime[date.getYear() - 1000][date.getMonth()] = monthTime[date.getYear() - 1000][date.getMonth()] + time;
	
	SetColorAndBackground(11, 0);
	cout << date;
	cout << "\t#" << getId() << " spent ";
	cout << time;
	cout<<" to run "<<mileage<<" km"<<endl;
	SetColorAndBackground(15, 0);
}
void RunningAccount::singleShow(std::string op,Date &data){
	bool flag=false;
	int y,m;
	while(!flag){
		if(op=="y"){
			if(data.getYear()<=1000||data.getYear()>=2500){
				SetColorAndBackground(12, 0);
				cout<<"Invalid date:\"year "<<data.getYear()<<"\"! ";
				cout<<"Please enter again."<<endl;
				SetColorAndBackground(15, 0);
				cin>>y;
				data.changeYear(y);
				continue;
				//exit(1);
			}
			else{
				SetColorAndBackground(11, 0);
				cout<<"In year "<<data.getYear()<<" you have spent ";
				cout << yearTime[data.getYear() - 1000];
				cout<<" to run "<<yearMileage[data.getYear() - 1000]<<" km."<<endl;
				SetColorAndBackground(15, 0);
				flag=true;
			} 
		}
		else if(op=="m"){
			if(data.getYear()<=1000||data.getYear()>=2500){
				SetColorAndBackground(12, 0);
				cout<<"Invalid date:\"year "<<data.getYear()<<"\"! ";
				cout<<"Please enter again."<<endl;
				SetColorAndBackground(15, 0);
				cin>>y;
				data.changeYear(y);
				continue;
				//exit(1);
			}
			else if(data.getMonth()<=0||data.getMonth()>12){
				SetColorAndBackground(12, 0);
				cout<<"Invalid date:\"month "<<data.getMonth()<<" \"! ";
				cout<<"Please enter again."<<endl;
				SetColorAndBackground(15, 0);
				cin>>m;
				data.changeMonth(m);
				continue;
				//exit(1);
			}
			else{ 
				SetColorAndBackground(11, 0);
				std::string monthName[]={"January","February","March","April","May","June","July",
				"August","September","October","November","December"};
				cout<<"In "<<monthName[data.getMonth()-1]<<" "<<data.getYear()<<" you have spent ";
				cout << monthTime[data.getYear() - 1000][data.getMonth()];
				cout<<" to run "<<monthMileage[data.getYear() - 1000][data.getMonth()]<<" km."<<endl;
				SetColorAndBackground(15, 0);
				flag=true;
			} 
		}
	}
}

RidingAccount::RidingAccount(const Date& date, const std::string& id)
	:Account(date, id) {}
double RidingAccount::allMileage = 0;
Time RidingAccount::allTime = Time(0, 0);
void RidingAccount::riding(Date& date, double mileage, Time time) {
	allMileage += mileage;
	totMileage += mileage;//同时用数组计算每年每月的跑量  check
	yearMileage[date.getYear() - 1000] += mileage;
	monthMileage[date.getYear() - 1000][date.getMonth()] += mileage;

	allTime = allTime + time;
	totTime = totTime + time;
	yearTime[date.getYear() - 1000] = yearTime[date.getYear() - 1000] + time;
	monthTime[date.getYear() - 1000][date.getMonth()] = monthTime[date.getYear() - 1000][date.getMonth()] + time;

	SetColorAndBackground(11, 0);
	cout << date;
	cout << "\t#" << getId() << " spent ";
	cout << time;
	cout << " to ride " << mileage << " km" << endl;
	SetColorAndBackground(15, 0);
}
void RidingAccount::singleShow(std::string op, Date& data) {
	bool flag = false;
	int y, m;
	while (!flag) {
		if (op == "y") {
			if (data.getYear() <= 1000 || data.getYear() >= 2500) {
				SetColorAndBackground(12, 0);
				cout << "Invalid date:\"year " << data.getYear() << "\"! ";
				cout << "Please enter again." << endl;
				SetColorAndBackground(15, 0);
				cin >> y;
				data.changeYear(y);
				continue;
				//exit(1);
			}
			else {
				SetColorAndBackground(11, 0);
				cout << "In year " << data.getYear() << " you have spent ";
				cout << yearTime[data.getYear() - 1000];
				cout << " to ride " << yearMileage[data.getYear() - 1000] << " km." << endl;
				SetColorAndBackground(15, 0);
				flag = true;
			}
		}
		else if (op == "m") {
			if (data.getYear() <= 1000 || data.getYear() >= 2500) {
				SetColorAndBackground(12, 0);
				cout << "Invalid date:\"year " << data.getYear() << "\"! ";
				cout << "Please enter again." << endl;
				SetColorAndBackground(15, 0);
				cin >> y;
				data.changeYear(y);
				continue;
				//exit(1);
			}
			else if (data.getMonth() <= 0 || data.getMonth() > 12) {
				SetColorAndBackground(12, 0);
				cout << "Invalid date:\"month " << data.getMonth() << " \"! ";
				cout << "Please enter again." << endl;
				SetColorAndBackground(15, 0);
				cin >> m;
				data.changeMonth(m);
				continue;
				//exit(1);
			}
			else {
				SetColorAndBackground(11, 0);
				std::string monthName[] = { "January","February","March","April","May","June","July",
				"August","September","October","November","December" };
				cout << "In " << monthName[data.getMonth() - 1] << " " << data.getYear() << " you have spent ";
				cout << monthTime[data.getYear() - 1000][data.getMonth()];
				cout << " to ride " << monthMileage[data.getYear() - 1000][data.getMonth()] << " km." << endl;
				SetColorAndBackground(15, 0);
				flag = true;
			}
		}
	}
}