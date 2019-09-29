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

    static HelpSection StringToSection(const std::string& sectionName);
    static std::string SectionToString(HelpSection section);
    static std::map<HelpSection, std::vector<std::string> >& SectionLines();

    static void Register(HelpSection section, const std::vector<std::string>& data, const std::string& doc = "");
    static void Print(const char* arg);
};

