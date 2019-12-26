#include "main.h"


LogEntry::LogEntry(std::string s, TCODColor c)
{
	entry = s;
	entryColor = c;
}

LogEntry::~LogEntry()
{

}

std::string LogEntry::getEntry() { return entry; }

TCODColor LogEntry::getEntryColor() { return entryColor; }