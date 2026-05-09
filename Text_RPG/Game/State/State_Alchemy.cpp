#include "State_Alchemy.h"
#include "../Conditions/TriggerCondition.h"

#include "../../Data/Table/StringTable.h"
#include "../../Component/AlchemyComponent.h"
#include "../../Character/Player.h"
#include "../../Manager/ObjectManager.h"

State_Alchemy::State_Alchemy()
{
	mName = "Alchemy";
	AddTransition<TriggerCondition>(StateID::MainMenu);
}

void State_Alchemy::Enter()
{
	PrintString("menu_move_alchemy");
}

void State_Alchemy::Process()
{
	PrintString("alchemy_select_1");
	PrintString("alchemy_select_2");
	PrintString("alchemy_select_3");
	PrintString("alchemy_select_4");
	PrintString("alchemy_select_5");
	PrintString("double_line");
	PrintString("input_number");

	int input = 0;
	cin >> input;

	Player* player = dynamic_cast<Player*>(ObjectManager::GetInstance().mPlayer);
	AlchemyComponent* alchemyComp = player->FindComponent<AlchemyComponent>("Alchemy");
	if (!alchemyComp)
	{
		mTransitions[StateID::MainMenu]->Notify();
		return;
	}

	switch (input)
	{
	case 1:
		alchemyComp->PrintAllRecipes();
		break;
	case 2:
	{
		PrintString("alchemy_find_by_potion");
		string inputStr;
		cin >> inputStr;

		alchemyComp->FindRecipesByResult(inputStr);

		break;
	}
	case 3:
	{
		PrintString("alchemy_find_by_ingredient");
		string inputStr;
		cin >> inputStr;

		alchemyComp->FindRecipesByIngredient(inputStr);

	}
	break;
	case 4:
		mTransitions[StateID::MainMenu]->Notify();
		break;
	default:
		PrintString("invalid_input");
		break;
	}
}