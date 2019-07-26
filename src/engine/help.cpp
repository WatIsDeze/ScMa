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

    std::string sectionToString(Help::HelpSection section)
    {
        if (Help::g_SectionToString.find(section) != Help::g_SectionToString.end())
            return Help::g_SectionToString.at(section);

        return "Other";
    }
}

std::map<std::string, Help::HelpSection> Help::g_StringToSection;
std::map<Help::HelpSection, std::string> Help::g_SectionToString;
std::map<Help::HelpSection, std::vector<std::string> > Help::g_SectionLines;
bool Help::initialized = false;

void Help::Initialize()
{
    if (!initialized)
    {
        g_StringToSection = std::map<std::string, Help::HelpSection> {
            {"commands", HelpSection::Commands}
        };
        g_SectionToString = std::map<Help::HelpSection, std::string> {
            {HelpSection::Commands, "commands"}
        };
        g_SectionLines = std::map<Help::HelpSection, std::vector<std::string> > {
            {HelpSection::Commands, {} }
        };

        initialized = true;
    }
}

void Help::Register(HelpSection section, const std::vector<std::string>& data)
{
    if (g_SectionLines.find(section) == g_SectionLines.end())
    {
        Initialize();
    }

    auto& sectionLineData = g_SectionLines[section];
    sectionLineData.push_back(formatData(data));
}

void Help::Print(const char* arg)
{
    std::string sArg = arg;

    if (sArg.empty())
    {
        for (auto section : g_SectionLines)
        {
            conoutf("==== %s ====", sectionToString(section.first).c_str());

            for (auto line : section.second)
            {
                conoutf("    %s", line.c_str());
            }
        }
    }
}

ICOMMAND(help, "s", (const char* arg),{ Help::Print(arg); }); 