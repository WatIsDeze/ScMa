#include "engine.h"
#include "help.h"

#include <map>

namespace {
    std::string formatData(const std::vector<std::string>& data)
    {
        std::string output;

        for (auto element : data)
        {
            if (!output.empty())
            {
                output += " ";
            }
            output += element;
        }

        return output;
    }

    struct HelpStorage
    {
        static std::map<std::string, std::string> g_StringToSection;
        static std::map<HelpSection, std::string> g_SectionToString;
        static std::map<HelpSection, std::vector<std::string> > g_SectionLines;
    };

    std::string sectionToString(HelpSection section)
    {
        if (HelpStorage::g_SectionToString.find(section) != HelpStorage::g_SectionToString.end())
            return HelpStorage::g_SectionToString.at(section);

        return "Other";
    }

    std::map<std::string, std::string> HelpStorage::g_StringToSection;
    std::map<HelpSection, std::string> HelpStorage::g_SectionToString;
    std::map<HelpSection, std::vector<std::string> > HelpStorage::g_SectionLines;
}

std::map<std::string, std::string> g_test {};

void Test()
{
    auto commandSection = std::make_pair<std::string, std::string>("commands", "commands");

    std::map<std::string, std::string> test;
    test.insert(commandSection);

    g_test.insert(commandSection); // <== Crash
}

void InitHelp()
{
    //Test();
    
    auto commandSection = std::make_pair<std::string, std::string>("commands", "commands");

    HelpStorage::g_StringToSection.insert(commandSection);
    HelpStorage::g_StringToSection["commands"] = "commands";

    HelpStorage::g_SectionToString[HelpSection::Commands] = "commands";

    HelpStorage::g_SectionLines[HelpSection::Commands] = {};
}

void RegisterHelp(HelpSection section, const std::vector<std::string>& data)
{
    if (HelpStorage::g_SectionLines.find(section) == HelpStorage::g_SectionLines.end())
    {
        InitHelp();
    }

    auto& sectionLineData = HelpStorage::g_SectionLines[section];
    sectionLineData.push_back(formatData(data));
}

void PrintHelp(const char* arg)
{
    std::string sArg = arg;

    if (sArg.empty())
    {
        for (auto section : HelpStorage::g_SectionLines)
        {
            conoutf("==== %s ====", sectionToString(section.first).c_str());

            for (auto line : section.second)
            {
                conoutf("    %s", line.c_str());
            }
        }
    }
}

ICOMMAND(help, "s", (const char* arg),{ PrintHelp(arg); }); 
