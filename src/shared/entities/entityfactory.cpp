#include "cube.h"
#include "game.h"
#include "ents.h"
#include "coreentity.h"
#include "baseentity.h"
#include "entityfactory.h"

namespace {
	const std::string fallbackEntityType = "core_entity";
}

std::map<std::string, entities::EntityFactory::EntityFactoryConstructor>& entities::EntityFactory::getFactories()
{
	static std::map<std::string, EntityFactoryConstructor> s_FactoryList;
	
	return s_FactoryList;
}

void entities::EntityFactory::addEntityFactory(const std::string &classname, EntityFactory::EntityFactoryConstructor constructor)
{
	auto& factoryList = getFactories();
	
	if (factoryList.find(classname) != factoryList.end())
	{
		printf("Entity Factory for class '%s' already exists!\n", classname.c_str());
		return;
	}

	printf("Entity Factory for class '%s' registered\n", classname.c_str());
	factoryList[classname] = constructor;
}

// Constructs the entity by using the special macro generated EntityNameConstruct function.
entities::classes::CoreEntity* entities::EntityFactory::constructEntity(const std::string &classname)
{
	auto& factoryList = getFactories();

	if (factoryList.find(classname) == factoryList.end())
	{
		conoutf(CON_WARN, "Entity Factory for class '%s' missing!", classname.c_str());
		return factoryList.at(fallbackEntityType)();
	}
	else
	{
		conoutf("Constructed class: %s", classname.c_str());
		return factoryList.at(classname)();
	}
}

