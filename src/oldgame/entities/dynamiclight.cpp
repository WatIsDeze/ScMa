#include "../game.h"
// #include "baseentity.h"
#include "dynamiclight.h"

namespace entities {
namespace classes {

DynamicLight::DynamicLight() : BaseEntity() {

}

DynamicLight::~DynamicLight() {

}

void DynamicLight::preload() {
    conoutf("%s", "Preloading dynamiclight entity");

}

void DynamicLight::think() {

}

} // classes
} // entities
