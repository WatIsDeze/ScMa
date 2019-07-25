//Help in the Console

#pragma once
#include <vector>
#include <string>


enum class HelpSection
{
    Commands,

    Other
};

void RegisterHelp(HelpSection section, const std::vector<std::string>& data);