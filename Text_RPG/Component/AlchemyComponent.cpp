#include "AlchemyComponent.h"
#include "../Item/Item.h"

AlchemyComponent::AlchemyComponent(Character* owner, string name)
	:Component(owner, name)
{
}

AlchemyComponent::~AlchemyComponent()
{
}

void AlchemyComponent::Initialize()
{
	Recipe hpPotionRecipe;
	hpPotionRecipe.result = "HP포션";
	hpPotionRecipe.ingredients.push_back(make_pair("허브", 1));
	hpPotionRecipe.ingredients.push_back(make_pair("맑은물", 1));

	mRecipes.emplace_back(hpPotionRecipe);

	Recipe mpPotionRecipe;
	mpPotionRecipe.result = "MP포션";
	mpPotionRecipe.ingredients.push_back(make_pair("베리", 1));
	mpPotionRecipe.ingredients.push_back(make_pair("맑은물", 1));

	mRecipes.emplace_back(mpPotionRecipe);

	Recipe steminaPotionRecipe;
	steminaPotionRecipe.result = "스태미나포션";
	steminaPotionRecipe.ingredients.push_back(make_pair("허브", 1));
	steminaPotionRecipe.ingredients.push_back(make_pair("베리", 1));

	mRecipes.emplace_back(steminaPotionRecipe);
}

void AlchemyComponent::FindRecipesByIngredient(string itemName)
{
	bool bFound = false;
	for (Recipe recipe : mRecipes)
	{
		for (const auto& pair : recipe.ingredients)
		{
			string ingredientName = pair.first;
			if (ingredientName == itemName)
			{
				bFound = true;
				recipe.Print();
				break;
			}
		}
	}

	if (!bFound)
	{
		PrintString("not_found");
	}
}

void AlchemyComponent::FindRecipesByResult(string itemName)
{
	for (Recipe recipe : mRecipes)
	{
		if(itemName == recipe.result)
		{
			recipe.Print();
			return;
		}
	}

	PrintString("not_found");
}

void AlchemyComponent::PrintAllRecipes()
{
	for (Recipe recipe : mRecipes)
	{
		recipe.Print();
	}
}
