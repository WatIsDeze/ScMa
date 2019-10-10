#pragma once

#include "cube.h"
#include "ents.h"
#include "coreentity.h"
#include "baseentity.h"

namespace entities {

    //
    // EntityFactory class used to manage entities. Entities are linked to it by the macro:
    // Example: ADD_ENTITY_TO_FACTORY(BaseDynamicEntity, "base_dynamic_entity");
    //
    // Always place this at the bottom of your entityname.cpp file and it'll automatically
    // register itself as a possible entity to spawn in your maps.
    //
    class EntityFactory
    {
    private:
        // List of our factory functions.
        //static std::map<std::string, std::function<entities::classes::CoreEntity*()> > factoryList;
        typedef std::function<entities::classes::CoreEntity*()> EntityFactoryConstructor;
        
        // Factory functions storage
        static std::map<std::string, EntityFactoryConstructor>& getFactories();

    public:
        static void addEntityFactory(const std::string &classname, EntityFactoryConstructor constructor);
        static entities::classes::CoreEntity* constructEntity(const std::string &classname);
    };
}


    //
    // Use ADD_ENTITY_TO_FACTORY at the bottom of your entityname.cpp file to hook it up to a
    // string name. For example: ADD_ENTITY_TO_FACTORY(GarageDoor, "door_garage");
    //
    // LOCALNAME: The class name in the C++ code.
    // CLASSNAME: The string class name used by map editing.
    //
    // From here on it'll be spawnable by the NewEntity function.
    //
#define ADD_ENTITY_TO_FACTORY(LOCALNAME, CLASSNAME) \
	entities::classes::CoreEntity *LOCALNAME##Construct()\
	{\
		return static_cast<entities::classes::CoreEntity*>(new entities::classes::LOCALNAME()); \
	}\
	struct LOCALNAME##Intializer\
	{\
		LOCALNAME##Intializer()\
		{\
            entities::EntityFactory::addEntityFactory(CLASSNAME, LOCALNAME##Construct);\
		}\
    } LOCALNAME##IntializerInstance;
