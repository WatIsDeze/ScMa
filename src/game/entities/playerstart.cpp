#include "../game.h"
//#include "baseentity.h"
#include "playerstart.h"

namespace entities {
namespace classes {

PlayerStart::PlayerStart() : BaseEntity() {

}

PlayerStart::~PlayerStart() {

}

void PlayerStart::preload() {
    conoutf("%s", "Preloading playerstart entity");
}

void PlayerStart::think() {

}

} // classes
} // entities
