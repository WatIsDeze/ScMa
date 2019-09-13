#include "../game.h"
//#include "baseentity.h"

namespace entities {
namespace classes {

BaseEntity::BaseEntity() : dynent(), flags(0), attached(NULL) {
    // Setup defaults.
    game_type = GAMEENTITY;
}

BaseEntity::~BaseEntity() {

}

void BaseEntity::preload() {
    //conoutf("%s", "Preloading BaseEntity entity");
}

void BaseEntity::think() {

}

void BaseEntity::render() {

}

} // classes
} // entities
