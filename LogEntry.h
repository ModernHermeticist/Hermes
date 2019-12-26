#ifndef LOGENTRY_H
#define LOGENTRY_H

class LogEntry
{
public:
	LogEntry(std::string s, TCODColor c);
	~LogEntry();

	std::string getEntry();
	TCODColor getEntryColor();

private:
	std::string entry;
	TCODColor entryColor;

};



#endif