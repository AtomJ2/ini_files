#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

namespace Ini {

    class Section {
    public:
        const std::string& operator[](const std::string& key) const;
        std::string& operator[](const std::string& key);

        const std::unordered_map<std::string, std::string>& GetValues() const;

    private:
        std::unordered_map<std::string, std::string> values;
    };

    class Document {
    public:
        Section& AddSection(const std::string& name);
        const Section& GetSection(const std::string& name) const;
        size_t SectionCount() const;

    private:
        std::unordered_map<std::string, Section> sections;
    };

    Document Load(std::istream& input);

}