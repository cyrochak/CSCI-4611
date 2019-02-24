#ifndef QUAKE_HPP
#define QUAKE_HPP

#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Date {
public:
    Date();
    Date(double seconds);
    Date(int m, int d, int y);
    Date(int m, int d, int y, int hr, int min, double sec);
    bool operator<(const Date& other);
    bool operator>(const Date& other);
    double asSeconds() const;
    double secondsUntil(const Date& other) const;
    int getYear();
    int getMonth();
    int getDay();
    int getHour();
    int getMinute();
    double getSecond();
protected:
    std::time_t ctime;
    int fouryears;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    double second;
};

class Earthquake {
public:
    Earthquake() {}
    // Create an earthquake from a datafile's line of text
    Earthquake(std::string s);
    Date getDate();
    double getLongitude();
    double getLatitude();
    double getMagnitude();
protected:
    std::string line;
    double parseFloat(std::string s);
    int parseInt(std::string s);
};

class EarthquakeDatabase {
public:
    // Creates an empty EarthquakeDatabase
    EarthquakeDatabase() {}
    // Creates an EarthquakeDatabase from file
    EarthquakeDatabase(std::string filename);
    // Returns Earthquake given index in file
    Earthquake getByIndex(int index);
    // Returns minimum index.  Note that this is not zero!
    int getMinIndex();
    // Returns maximum valid index.  Running
    // getByIndex(getMaxIndex()) WILL return the last earthquake in the file
    int getMaxIndex();
    // Returns the index of the most recent earthquake as of given date
    int getIndexByDate(Date d);
	// Flag which is set to true if the file was successfully loaded
	bool fileFound;
protected:
    std::vector<Earthquake> earthquakes;
};

// Date methods

static const int SECONDS_PER_4_YEARS=126230400;

inline Date::Date() {
    year = 0;
    month = 0;
    day = 0;
    hour = 0;
    minute = 0;
    second = 0;
    ctime = 0;
    fouryears = 0;
}
inline Date::Date(double seconds) {
    double tweakedSeconds = seconds;
    fouryears = 0;
    while (tweakedSeconds < 0) {
        tweakedSeconds += SECONDS_PER_4_YEARS;
        fouryears++;
    }
    ctime = int(tweakedSeconds);
    tm *t;
    t = localtime(&ctime);
    year = t->tm_year + 1900 - 4 * fouryears;
    month = t->tm_mon + 1;
    day = t->tm_mday;
    hour = t->tm_hour;
    minute = t->tm_min;
    second = t->tm_sec + (tweakedSeconds - ctime);
}

inline Date::Date(int m, int d, int y) {
    month = m;
    day = d;
    year = y;
    hour = 0;
    minute = 0;
    second = 0;
    fouryears = 0;
    tm t;
    while (year + fouryears*4 < 1970) {
        fouryears++;
    }
    t.tm_year = year - 1900 + fouryears * 4;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    ctime = mktime(&t);
}

inline Date::Date(int m, int d, int y, int hr, int min, double sec) {
    month = m;
    day = d;
    year = y;
    hour = hr;
    minute = min;
    second = sec;
    fouryears = 0;
    tm t;
    while (year + fouryears*4 < 1970) {
        fouryears++;
    }
    t.tm_year = year - 1900 + fouryears * 4;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = int(second);
    ctime = mktime(&t);
}

inline bool Date::operator<(const Date& other) {
    return asSeconds() < other.asSeconds();
}

inline bool Date::operator>(const Date& other) {
    return asSeconds() > other.asSeconds();
}

inline double Date::asSeconds() const {
    return ctime + second - int(second) - double(fouryears) * SECONDS_PER_4_YEARS;
}

inline double Date::secondsUntil(const Date& other) const {
    return asSeconds() - other.asSeconds();
}

inline int Date::getYear() {
    return year;
}

inline int Date::getMonth() {
    return month;
}

inline int Date::getDay() {
    return day;
}

inline int Date::getHour() {
    return hour;
}

inline int Date::getMinute() {
    return minute;
}

inline double Date::getSecond() {
    return second;
}

// Earthquake methods

inline Earthquake::Earthquake(std::string s) {
    line = s;
}

inline Date Earthquake::getDate() {
    int year = parseInt(line.substr(12,4));
    int month = parseInt(line.substr(17,2));
    int day = parseInt(line.substr(20,2));
    int hour = parseInt(line.substr(24,2));
    int minute = parseInt(line.substr(27,2));
    double second = parseFloat(line.substr(30,5));
    return Date(month, day, year, hour, minute, second);
}

inline double Earthquake::getLongitude() {
    return parseFloat(line.substr(44,8));
    //return parseFloat(line.substr(37,7));
}

inline double Earthquake::getLatitude() {
    //return parseFloat(line.substr(44,8));
    return parseFloat(line.substr(37,7));
}

inline double Earthquake::getMagnitude() {
    return parseFloat(line.substr(66,4));
}

inline double Earthquake::parseFloat(std::string s) {
    std::stringstream ss(s);
    double f;
    ss >> f;
    return f;
}

inline int Earthquake::parseInt(std::string s) {
    std::stringstream ss(s);
    int i;
    ss >> i;
    return i;
}

// Earthquake database methods

inline EarthquakeDatabase::EarthquakeDatabase(std::string filename) {
    std::ifstream in(filename.c_str());
	if (!in) {
		fileFound = false;
	}
	else {
		fileFound = true;
	}
    std::string line;
    while (getline(in, line)) {
        if (line.size() > 30) {
            earthquakes.push_back(Earthquake(line));
        }
    }
}

inline Earthquake EarthquakeDatabase::getByIndex(int index) {
    return earthquakes[index];
}

inline int EarthquakeDatabase::getMinIndex() {
    return 250;
}

inline int EarthquakeDatabase::getMaxIndex() {
    return earthquakes.size() - 1;
}

inline int EarthquakeDatabase::getIndexByDate(Date d) {
    double targetSeconds = d.asSeconds();
    int start = getMinIndex();
    int end = getMaxIndex();
    while (start < end-1) {
        int half = (start + end) / 2;
        if (earthquakes[half].getDate().asSeconds() > targetSeconds) {
            end = half - 1;
        } else {
            start = half;
        }
    }
    if (start == end)
        return start;
    else {
        if (earthquakes[end].getDate().asSeconds() > targetSeconds) {
            return start;
        } else {
            return end;
        }
    }
}

#endif
