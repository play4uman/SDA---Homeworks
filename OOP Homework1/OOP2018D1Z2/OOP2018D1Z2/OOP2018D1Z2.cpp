// OOP2018D1Z2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstring>
#include <iostream>

using namespace std;

struct HistoryEntry {
	int date;
	char* URL;
	HistoryEntry();
	HistoryEntry(int, const char*, int);
	HistoryEntry& operator=(HistoryEntry const &);
	~HistoryEntry();
};

HistoryEntry::HistoryEntry() {
	date = 0;
	URL = NULL;
}

HistoryEntry::HistoryEntry(int m, const char* _url, int len) {
	URL = new char[len + 1];
	strcpy(URL, _url);
	date = m;
}

HistoryEntry::~HistoryEntry() {
	delete[] URL;
}

HistoryEntry& HistoryEntry::operator=(HistoryEntry const & other) {
	if (this != &other) {
		this->date = other.date;
		URL = new char[strlen(other.URL) + 1];
		strcpy(URL, other.URL);
	}
	return *this;
}

class BrowserHistory {
	HistoryEntry* hisArr;
	int maxCount;
	int currEntry;

public:
	BrowserHistory(int);
	BrowserHistory();
	BrowserHistory(BrowserHistory const &);
	BrowserHistory& operator=(BrowserHistory const &);
	~BrowserHistory();
	int getCurrEntry() const;
	HistoryEntry* getArray() const;
	void addSite();
	void addSite(HistoryEntry const &);
	void printAll() const;
	int visitedInMonth(int) const;
	int mostVisitedMonth() const;
	void removeMostRecent();
	void cat(BrowserHistory const &) const;
};

BrowserHistory::BrowserHistory(int n) {
	maxCount = n;
	hisArr = new HistoryEntry[maxCount];
	currEntry = 0;
}

BrowserHistory::BrowserHistory() {
	maxCount = 0;
	hisArr = NULL;
	currEntry = 0;
}

BrowserHistory::BrowserHistory(BrowserHistory const & other) {
	maxCount = other.maxCount;
	currEntry = other.currEntry;
	hisArr = new HistoryEntry[maxCount];
	for (int i = 0; i < other.maxCount; i++) {
		hisArr[i] = other.hisArr[i];
	}
}

BrowserHistory& BrowserHistory::operator=(BrowserHistory const & other) {
	if (this != &other) {
		maxCount = other.maxCount;
		currEntry = other.currEntry;
		hisArr = new HistoryEntry[maxCount];
		for (int i = 0; i < other.maxCount; i++) {
			hisArr[i] = other.hisArr[i];
		}
	}
	return *this;
}

BrowserHistory::~BrowserHistory() {
	delete[] hisArr;
}

int BrowserHistory::getCurrEntry() const {
	return currEntry;
}

HistoryEntry* BrowserHistory::getArray()const {
	return hisArr;
}

void BrowserHistory::addSite() {
	if (currEntry < maxCount) {
		int month;
		char* inURL = new char[1000];
		cout << "Enter site URL: " << endl;
		cin >> inURL;
		cout << "Enter site month: " << endl;
		cin >> month;
		hisArr[currEntry] = HistoryEntry(month, inURL, strlen(inURL));
		currEntry++;
	}
	else {
		cout << "Error! Limit of sites reached. ";
	}
}

void BrowserHistory::addSite(HistoryEntry const & other) {
	if (currEntry < maxCount) {
		hisArr[currEntry] = other;
		currEntry++;
	}
	else {
		cout << "Error! Limit of sites reached. ";
	} 
}

void BrowserHistory::printAll() const {
	for (int i = 0; i < currEntry; i++) {
		cout << hisArr[i].date << "\t" << hisArr[i].URL << endl;
	}
}

int BrowserHistory::visitedInMonth(int n) const {
	int counter = 0;
	for (int i = 0; i < currEntry; i++) {
		if (hisArr[i].date == n)
			counter++;
	}
	return counter;
}

int BrowserHistory::mostVisitedMonth() const {
	int cntArr[13];
	int max = 0;
	for (int i = 0; i < 13; i++){
		cntArr[i] = 0;
	}
	for (int i = 0; i < currEntry; i++) {
		cntArr[hisArr[i].date]++;
	}
	for (int i = 0; i < 13; i++) {
		if (cntArr[i] > max) {
			max = cntArr[i];
		}
	}
	for (int i = 0; i < 13; i++) {
		if (cntArr[i] == max)
			return i;
	}
	return 42;
}


void BrowserHistory::removeMostRecent() {
	currEntry--;
}

void BrowserHistory::cat(BrowserHistory const & other) const {
	BrowserHistory result(currEntry + other.getCurrEntry());
	HistoryEntry* rightStart = other.getArray();
	int rightLen = other.getCurrEntry();
	HistoryEntry* resultArr = result.getArray();

	for (int i = 0; i < currEntry; i++) {
		result.addSite(hisArr[i]);
	}

	for (int  i = 0; i < other.getCurrEntry(); i++){
		result.addSite(other.getArray()[i]);
	}

	result.printAll();
}

int main()
{
	BrowserHistory br(6);
	BrowserHistory mr(6);
	br.addSite(HistoryEntry(11, "Abv.bg", 7));
	br.addSite(HistoryEntry(11, "Abv.bg", 7));
	br.addSite(HistoryEntry(7, "Abv.bg", 7));
	br.addSite(HistoryEntry(7, "Abv.bg", 7));
	br.addSite(HistoryEntry(7, "Abv.bg", 7));
//	br.printAll();
	mr.addSite(HistoryEntry(10, "Pesho.bg", 8));
	mr.addSite(HistoryEntry(10, "Pesho.bg", 8));
	mr.addSite(HistoryEntry(10, "Pesho.bg", 8));
	mr.addSite(HistoryEntry(10, "Pesho.bg", 8));
	mr.addSite(HistoryEntry(10, "Pesho.bg", 8));
	br.cat(mr);
    return 0;
}

