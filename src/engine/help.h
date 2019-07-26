//Help in the Console

#pragma once
#include <vector>
#include <string>




struct Help
{
    enum class HelpSection
    {
        Commands,

        Other
    };

    static std::map<std::string, HelpSection> g_StringToSection;
    static std::map<HelpSection, std::string> g_SectionToString;
    static std::map<HelpSection, std::vector<std::string> > g_SectionLines;
    static bool initialized;

    static void Register(HelpSection section, const std::vector<std::string>& data);
    static void Initialize();
    static void Print(const char* arg);
};

