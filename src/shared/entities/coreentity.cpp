#include "cube.h"
#include "game.h"
#include "ents.h"
#include "coreentity.h"

namespace entities {
namespace classes {

CoreEntity::CoreEntity() : o(0, 0, 0), attr1(0), attr2(0), attr3(0), attr4(0), attr5(0),
    et_type(ET_EMPTY), ent_type(ENT_INANIMATE), game_type(GAMEENTITY), reserved(0), model_idx(0), flags(EntityFlags::EF_NOFLAG),
    attached(nullptr) {

}

bool CoreEntity::spawned() const {
    return (flags&entities::EntityFlags::EF_SPAWNED) != 0;
}
void CoreEntity::setspawned(bool val) {
    if(val)
        flags |= entities::EntityFlags::EF_SPAWNED;
    else
        flags &= ~entities::EntityFlags::EF_SPAWNED;
}
void CoreEntity::setspawned() {
    flags |= entities::EntityFlags::EF_SPAWNED;
}
void CoreEntity::clearspawned() {
    flags &= ~entities::EntityFlags::EF_SPAWNED;
}

void CoreEntity::reset() {
    o = vec(0, 0, 0);
    attr1 = 0;
    attr2 = 0;
    attr3 = 0;
    attr4 = 0;
    attr5 = 0;
    et_type = ET_EMPTY;
    ent_type = ENT_INANIMATE;
    game_type = GAMEENTITY;
    reserved = 0;
    model_idx = 0;
    flags = EntityFlags::EF_NOFLAG;
    attached = nullptr;
}
} // classes
} // entities
