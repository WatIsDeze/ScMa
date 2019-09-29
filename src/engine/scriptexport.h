#pragma once

#define SCRIPTEXPORT __attribute__((annotate("scriptexport")))
#define SCRIPTEXPORT_AS(NAME) __attribute__((annotate("scriptexport" #NAME)))
