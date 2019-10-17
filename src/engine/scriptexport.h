#pragma once
#include <functional>

#ifdef SCRIPTBIND_RUN
#define VISIBLE_SYMBOL
#else
#define VISIBLE_SYMBOL __attribute__((__visibility__("default")))
#endif

#define SCRIPTEXPORT __attribute__((annotate("scriptexport"))) VISIBLE_SYMBOL
#define SCRIPTEXPORT_AS(NAME) __attribute__((annotate("scriptexport" #NAME))) VISIBLE_SYMBOL

class ScriptBindStaticInitializer
{
public:
	static ScriptBindStaticInitializer& Get();
    void Register(std::function<void()> initializer);
    void Execute();
};
