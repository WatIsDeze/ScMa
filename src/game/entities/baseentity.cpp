#include "../game.h"
#include "baseentity.h"

namespace entities {
namespace classes {

BaseEntity::BaseEntity() : entity(), flags(0), attached(NULL) {
    // Setup defaults, at least, ensure the strings are empty.
    copycubestr(classname, "", 256);
    copycubestr(str_attr1, "", 256);
    copycubestr(str_attr2, "", 256);
    copycubestr(str_attr3, "", 256);
    copycubestr(str_attr4, "", 256);
    copycubestr(str_attr5, "", 256);
    copycubestr(str_attr6, "", 256);
    copycubestr(str_attr7, "", 256);
    copycubestr(str_attr8, "", 256);

}

BaseEntity::~BaseEntity() {

}

void BaseEntity::preload() {
    conoutf("%s", "Preloading BaseEntity entity");
}

void BaseEntity::think() {

}

} // classes
} // entities
