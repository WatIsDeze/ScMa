#include "cube.h"
#include "game.h"
#include "ents.h"
#include "coreentity.h"
#include "baseentity.h"
#include "entityfactory.h"

namespace entities {
    namespace factory {
        std::map<std::string, std::function<entities::classes::CoreEntity*()> > factoryList;
    } // factory.
} // entities.
