#pragma once
#include "Component.h"

struct Recipe;
class Character;

class AlchemyComponent : public Component
{
public:
	AlchemyComponent() = delete;
	AlchemyComponent(Character* owner, string name);
	virtual ~AlchemyComponent();

	virtual void Initialize() override;

	void FindRecipesByIngredient(string itemName);
	void FindRecipesByResult(string itemName);

	void PrintAllRecipes();
private:
	vector<Recipe> mRecipes;
};

