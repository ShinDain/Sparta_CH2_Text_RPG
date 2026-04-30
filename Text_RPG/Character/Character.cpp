#include "Character.h"

Character::Character()
{
}

Character::Character(const string& InName)
    : Name(InName)
{
}

Character::~Character()
{
}

string Character::GetName() const
{
    return Name;
}

void Character::SetName(const string& InName)
{
    Name = InName;
}
