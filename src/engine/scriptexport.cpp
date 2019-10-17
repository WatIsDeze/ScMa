#include "scriptexport.h"
#include <vector>

namespace {
    std::vector<std::function<void()> >& GetInitializers()
    {
        static std::vector<std::function<void()> > s_Initializers;
        return s_Initializers;
    }
}

ScriptBindStaticInitializer& ScriptBindStaticInitializer::Get()
{
	static ScriptBindStaticInitializer s_Initializer;
	
	return s_Initializer;
}

void ScriptBindStaticInitializer::Register(std::function<void()> initalizerFunc)
{
    GetInitializers().push_back(initalizerFunc);
}

void ScriptBindStaticInitializer::Execute()
{
    for (auto& initializer : GetInitializers())
    {
        initializer();
    }
}
