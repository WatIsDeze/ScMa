#pragma once 
#include <functional>
#include <string>
#include <map>

#define ENTITY_FACTORY(NAME) struct NAME##Initializer { NAME##Initializer(){ entities::EntityFactory::RegisterEntityFactory(#NAME, entities::classes::NAME::factory); } } Init##NAME##Initializer;

namespace entities {
    namespace classes {
        class CoreEntity;
    }

    class EntityFactory
    {

    public:
        typedef std::function<classes::CoreEntity*()> EntityConstructorCallbackT;

        static void RegisterEntityFactory(const std::string& name, EntityConstructorCallbackT constructor);
        static classes::CoreEntity* ConstructEntity(const std::string& name);
		static std::map<std::string, EntityFactory::EntityConstructorCallbackT>& GetRegisteredFactories();
    };
}
