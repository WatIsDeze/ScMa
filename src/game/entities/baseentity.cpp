#include "../game.h"
//#include "baseentity.h"

namespace entities {
namespace classes {

BaseEntity::BaseEntity() : dynent(), flags(EF_RENDER), attached(NULL) {
    // Setup defaults.
    et_type = ET_EMPTY;
    ent_type = ENT_INANIMATE;
    game_type = GAMEENTITY;
}

BaseEntity::~BaseEntity() {

}

void BaseEntity::preload() {}
void BaseEntity::think() {}
void BaseEntity::render() {}

bool BaseEntity::onTrigger(entities::classes::BaseEntity *otherEnt, const vec &dir) {}
bool BaseEntity::onTouch(entities::classes::BaseEntity *otherEnt, const vec &dir) {}

} // classes
} // entities
