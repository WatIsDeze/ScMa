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

}

Help::HelpSection Help::StringToSection(const std::string& sectionName)
{
    static std::map<std::string, Help::HelpSection> g_StringToSection = std::map<std::string, Help::HelpSection> {
        {"Commands", HelpSection::Commands}
    };

    if (g_StringToSection.find(sectionName) != g_StringToSection.end())
    {
        return g_StringToSection.at(sectionName);
    }

    return HelpSection::Other;
}

std::string Help::SectionToString(HelpSection section)
{
    static std::map<HelpSection, std::string> g_SectionToString = std::map<Help::HelpSection, std::string> {
        {HelpSection::Commands, "Commands"},
        {HelpSection::Other, "Other"}
    };

    if (g_SectionToString.find(section) != g_SectionToString.end())
    {
        return g_SectionToString.at(section);
    }

    return g_SectionToString.at(HelpSection::Other);
}

std::map<Help::HelpSection, std::vector<std::string> >& Help::SectionLines()
{
    static std::map<Help::HelpSection, std::vector<std::string> > g_SectionLines = std::map<Help::HelpSection, std::vector<std::string> > {
        {HelpSection::Commands, {} },
        {HelpSection::Other, {} }
    };

    return g_SectionLines;
}

void Help::Register(Help::HelpSection section, const std::vector<std::string>& data)
{
    auto& sectionLineData = SectionLines()[section];
    sectionLineData.push_back(formatData(data));
}

void Help::Print(const char* arg)
{
    std::string sArg = arg;

    if (sArg.empty())
    {
        for (auto section : SectionLines())
        {
            conoutf("==== %s ====", SectionToString(section.first).c_str());

            for (auto line : section.second)
            {
                conoutf("    %s", line.c_str());
            }
        }
    }
}

ICOMMAND(help, "s", (const char* arg),{ Help::Print(arg); }); 
