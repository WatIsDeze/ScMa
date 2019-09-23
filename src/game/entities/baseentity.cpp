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


void BaseEntity::onAttributeSet(const std::string &key, const std::string &value) {}

bool BaseEntity::onTrigger(entities::classes::BaseEntity *otherEnt, const vec &dir) {}
bool BaseEntity::onTouch(entities::classes::BaseEntity *otherEnt, const vec &dir) {}

void BaseEntity::respawn()
{
    dynent::reset();
    // TODO: Reset other variables here.
}

} // classes
} // entities
