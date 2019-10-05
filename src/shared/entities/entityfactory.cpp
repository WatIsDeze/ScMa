#include "entityfactory.h"
#include "coreentity.h"

namespace entities {

	std::map<std::string, EntityFactory::EntityConstructorCallbackT>& EntityFactory::GetRegisteredFactories()
	{
		static std::map<std::string, EntityFactory::EntityConstructorCallbackT> s_RegisteredFactories {};
		
		return s_RegisteredFactories;
	}
	
	void EntityFactory::RegisterEntityFactory(const std::string& name, EntityFactory::EntityConstructorCallbackT constructor)
	{
		GetRegisteredFactories()[name] = constructor;
	}

	classes::CoreEntity* EntityFactory::ConstructEntity(const std::string& name)
	{
		auto registeredFactories = GetRegisteredFactories();

		if (registeredFactories.find(name) != registeredFactories.end())
		{
			return registeredFactories.at(name)();
		}
		
		return nullptr;
	}
}
