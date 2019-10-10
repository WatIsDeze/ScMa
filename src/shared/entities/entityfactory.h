#pragma once

#include "cube.h"
#include "ents.h"
#include "coreentity.h"
#include "baseentity.h"

namespace entities {

    //
    // EntityFactory class used to manage entities. Entities are linked to it by the macro:
    // Example: ADD_ENTITY_TO_FACTORY(BaseDynamicEntity, base_dynamic_entity);
    //
    // Always place this at the bottom of your entityname.cpp file and it'll automatically
    // register itself as a possible entity to spawn in your maps.
    //
    class EntityFactory {
    private:
        // List of our factory functions.
        //static std::map<std::string, std::function<entities::classes::CoreEntity*()> > factoryList;
        typedef std::function<entities::classes::CoreEntity*()> EntityFactoryConstructor;
        // List of our factory functions.
        std::map<std::string, EntityFactoryConstructor> factoryList;

    public:
       /* entities::classes::CoreEntity * operator[] (const std::string &classname) {
            if (factoryList.at(classname)) {
                return factoryList[classname]();
            } else {
                return new entities::classes::BaseEntity();
            }
        }*/
        bool addClass(const std::string &classname, EntityFactoryConstructor constructor) {
            if (factoryList.find(classname) != factoryList.end()) {
                conoutf(CON_WARN, "Failed to add entity class '%s' to the entity factory", classname.c_str());
                return false;
            } else {
                factoryList[classname] = constructor;
                return true;
            }
        }

        // Constructs the entity by using the special macro generated EntityNameConstruct function.
        entities::classes::CoreEntity* constructEntity(const std::string &classname) {
            if (factoryList.find(classname) != factoryList.end()) {
                conoutf("Constructed class: %s", classname.c_str());
                return factoryList[classname]();
            } else {
                conoutf(CON_WARN, "Failed to construct entity class '%s'", classname.c_str());
                return nullptr;
            }
        }
    }; // EntityFactory.

    //
    // Extern variables for entity globals.
    //
    extern EntityFactory g_entFactory;

    //
    // Use ADD_ENTITY_TO_FACTORY at the bottom of your entityname.cpp file to hook it up to a
    // string name. For example: ADD_ENTITY_TO_FACTORY(GarageDoor, door_garage);
    //
    // LOCALNAME: The class name in the C++ code.
    // CLASSNAME: The string class name used by map editing.
    //
    // From here on it'll be spawnable by the NewEntity function.
    //
#define ADD_ENTITY_TO_FACTORY( LOCALNAME, CLASSNAME ) \
   static entities::classes::CoreEntity *LOCALNAME##Construct( void ) { \
        return static_cast<entities::classes::LOCALNAME*>( new entities::classes::LOCALNAME() ); \
   }; \
   class CLASSNAME { \
   public: \
       CLASSNAME ( void ) { \
            entities::g_entFactory.addClass(CLASSNAME, LOCALNAME##Construct); \
        } \
    };
};
            /*entities::g_entFactory[#CLASSNAME] = LOCALNAME##Construct; */
