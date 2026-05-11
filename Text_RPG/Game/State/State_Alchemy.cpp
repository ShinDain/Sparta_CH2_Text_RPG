#include "State_Alchemy.h"
#include "../Conditions/TriggerCondition.h"

#include "../Game.h"
#include "../../Data/Table/StringTable.h"
#include "../../Component/AlchemyComponent.h"
#include "../../Character/Player.h"
#include "../../Manager/ObjectManager.h"
#include "../../Component/InventoryComponent.h"

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
	PrintString("alchemy_select_6");
	PrintString("double_line");
	PrintString("input_number");

	int input = 0;
	cin >> input;

	Player* player = ObjectManager::GetInstance().mPlayer;
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
		ProcessAid();
		break;
	case 5:
		mTransitions[StateID::MainMenu]->Notify();
		break;
	default:
		PrintString("invalid_input");
		break;
	}
}

void State_Alchemy::ProcessAid()
{
	bool bAction = true;

	Player* player = ObjectManager::GetInstance().mPlayer;
	InventoryComponent* inventory = player->FindComponent<InventoryComponent>("Inventory");

	while (bAction)
	{
		int cnt = 1;

		// 테스트 코드
		int stock[2] = { 0, 0 };

		for (auto& pair : Game::GetInstance().mPotionStock)
		{
			string itemName = pair.first;
			int amount = pair.second;

			stock[cnt - 1] = amount;

			cout << cnt << ". ";
			PrintFormatString("alchemy_stock_print", { {"{Name}", itemName}, {"{Amount}", to_string(amount)} });
			cnt++;
		}

		cout << "3. 돌아가기\n";
		PrintString("input_number");

		string input = {};
		cin >> input;

		int select = stoi(input);

		Player* player = ObjectManager::GetInstance().mPlayer;

		string bottleName = "공병";
		switch (select)
		{
		case 1:
		{
			string hpPotionName = "HP포션";
			int num = stock[0];

			if (num > 0)
			{
				if (inventory->UseItem(bottleName))
				{
					inventory->AddItem(hpPotionName, 1);
					Game::GetInstance().mPotionStock[hpPotionName] -= 1;
					PrintFormatString("alchemy_stock_acquire", { {"{Name}", hpPotionName}, {"{Amount}", to_string(num - 1)} });
				}
				else
				{
					PrintFormatString("alchemy_stock_acquire_fail", { {"{Name}", hpPotionName} });
					PrintString("alchemy_stock_fail_need_bottle");
				}
			}
			else
			{
				PrintFormatString("alchemy_stock_acquire_fail", { {"{Name}", hpPotionName} });
				PrintString("alchemy_stock_fail_out_of_stock");
			}
		}
		break;
		case 2:
		{
			string mpPotionName = "MP포션";
			int num = stock[1];

			if (num > 0)
			{
				if (inventory->UseItem(bottleName))
				{
					inventory->AddItem(mpPotionName, 1);
					Game::GetInstance().mPotionStock[mpPotionName] -= 1;
					PrintFormatString("alchemy_stock_acquire", { {"{Name}", mpPotionName}, {"{Amount}", to_string(num - 1)} });
				}
				else
				{
					PrintFormatString("alchemy_stock_acquire_fail", { {"{Name}", mpPotionName} });
					PrintString("alchemy_stock_fail_need_bottle");
				}
			}
			else
			{
				PrintFormatString("alchemy_stock_acquire_fail", { {"{Name}", mpPotionName} });
				PrintString("alchemy_stock_fail_out_of_stock");
			}
		}
		break;
		case 3:
			bAction = false;
			break;
		default:
			PrintString("invalid_input");
			bAction = true;
			break;
		}
	}
}
