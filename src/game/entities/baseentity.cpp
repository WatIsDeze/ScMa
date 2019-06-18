#include "../game.h"
#include "baseentity.h"

namespace entities {
namespace classes {

BaseEntity::BaseEntity() : gameentity(), attached(NULL) {

}

BaseEntity::~BaseEntity() {

}

void BaseEntity::preload() {
    conoutf("%s", "Preloading playerstart entity");
}

void BaseEntity::think() {

}

} // classes
} // entities
