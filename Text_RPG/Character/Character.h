#pragma once
#include <string>;

using namespace std;

class Character
{
public:
	Character();
	Character(const string& InName);
	virtual ~Character();

public:
	string GetName() const;
	void SetName(const string& InName);
protected:
	string Name;

};

