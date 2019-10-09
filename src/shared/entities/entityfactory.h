#pragma once

#include "cube.h"
#include "ents.h"
#include "coreentity.h"
#include "baseentity.h"

namespace entities {

    // Factory pattern for registering entities.
    namespace factory {
        extern std::map<std::string, std::function<entities::classes::CoreEntity*()> > factoryList;

        static entities::classes::CoreEntity* constructEntity(const std::string &classname) {
            if (factoryList.find(classname) != factoryList.end()) {
                conoutf("Constructed class: %s", classname.c_str());
                return factoryList[classname]();
            } else {
                return new entities::classes::BaseEntity();
            }
        }
    }; // factory.

    /*
    // Entity Factory Macro linking function.
    */
    namespace factory {
        #define LINK_ENTITY_TO_CLASS( LOCALNAME, CLASSNAME ) \
            static entities::classes::CoreEntity *LOCALNAME##Construct( void ) { \
                return static_cast<entities::classes::CoreEntity*>( new entities::classes::LOCALNAME() ); \
            }; \
            class CLASSNAME { \
            public: \
                CLASSNAME ( void ) { \
                    entities::factory::factoryList[#CLASSNAME] = &LOCALNAME##Construct; \
                } \
            };
    };
}; // entities
