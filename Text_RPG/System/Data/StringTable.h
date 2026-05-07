#pragma once
#include "DataTable.h"

class StringTable : public IDataTable
{
private:
	StringTable() {};
	StringTable(const StringTable& rhs) = delete;
	StringTable operator=(const StringTable& rhs) = delete;
public:
	virtual ~StringTable() {};

	static StringTable& GetInstance();
	virtual bool Load(const string& filePath) override;

	void PrintString(const string& key) const;
	void PrintFormatString(const string& key, initializer_list<pair<string, string>> replacements) const;
	string GetString(const string& key) const;
	string GetFormatString(const string& key, initializer_list<pair<string, string>> replacements) const;

protected:
	virtual void ParseString(const string& inString) override;

private:
	map<string, string> mStrings;
};

inline void PrintString(const string& key)
{
	return StringTable::GetInstance().PrintString(key);
}

inline void PrintFormatString(const string& key, initializer_list<pair<string, string>> replacements)
{
	return StringTable::GetInstance().PrintFormatString(key, replacements);
}

inline string GetString(const string& key)
{
	return StringTable::GetInstance().GetString(key);
}
inline string GetFormatString(const string& key, initializer_list<pair<string, string>> replacements)
{
	return StringTable::GetInstance().GetFormatString(key, replacements);
}