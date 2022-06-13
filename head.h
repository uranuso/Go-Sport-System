#ifndef __HEAD_H__
#define __HEAD_H__

#include<string>
#include<iostream>

void SetColorAndBackground(int ForgC, int BackC);

class Date {
private:
	int year;
	int month;
	int day;
	//int totDays;
public:
	Date(int year, int month, int day);
	void changeYear(int newYear) {
		year = newYear;
	}
	void changeMonth(int newMonth) {
		month = newMonth;
	}
	void changeDay(int newDay) {
		day = newDay;
	}
	int getYear() const {
		return year;
	}
	int getMonth() const {
		return month;
	}
	int getDay() const {
		return day;
	}
	int getMaxDay() const;
	bool isLeapYear() const {
		return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	}
	void show() const;
	~Date() {};
};
std::ostream& operator<<(std::ostream& out, const Date& date);


class Time {
private:
	int minute;
	int second;
public:
	Time(int minute, int second);
	int getMinute() const {
		return minute;
	}
	int getSecond() const {
		return second;
	}
	void show();
	Time operator+(const Time& t2)const;
	Time operator/(const double& m)const;
	bool operator>(const Time& t1)const;
	~Time() {};
};
std::ostream& operator<<(std::ostream& out, const Time& time);


class Account {
private:
	std::string id;
	Date date;//  Date类 
protected:
	Account(const Date& date, const std::string& id);
	void error(const std::string& msg) const;

	Time totTime;//  Time类 (重载运算符) check
	Time pace;
	double totMileage = 0;
public:
	const std::string& getId() const {
		return id;
	}
	double getTotMileage() const {
		return totMileage;
	}
	Time getTotTime() const {
		return totTime;
	}
	Time getPace() const {
		return totTime / totMileage;
	}
	void totShow();
	virtual void singleShow();
};

class RunningAccount : public Account {
	friend class Time;//友元类 
	friend class Date;
private:
	Time yearTime[1500];
	Time monthTime[1500][13];
	Time pace;
	double yearMileage[1500] = { 0 };
	double monthMileage[1500][13] = { {0} };
	static double allMileage;
	static Time allTime;
public:
	RunningAccount(const Date& date, const std::string& id);
	static double getAllMileage() {
		return allMileage;
	}
	static Time getAllTime() {
		return allTime;
	}
	void running(Date& date, double mileage, Time time);//km,min'secend"
	void singleShow(std::string op, Date& data);
	~RunningAccount() {};
};

class RidingAccount : public Account {
	friend class Time;//友元类 
	friend class Date;
private:
	Time yearTime[1500];
	Time monthTime[1500][13];
	Time pace;
	double yearMileage[1500] = { 0 };
	double monthMileage[1500][13] = { {0} };
	static double allMileage;
	static Time allTime;
public:
	RidingAccount(const Date& date, const std::string& id);
	static double getAllMileage() {
		return allMileage;
	}
	static Time getAllTime() {
		return allTime;
	}
	void riding(Date& date, double mileage, Time time);//km,min'secend"
	void singleShow(std::string op, Date& data);
	~RidingAccount() {};
};

#endif