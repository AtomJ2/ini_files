#include "ini.h"
#include <sstream>
#include <fstream>

namespace Ini {

    const std::string& Section::operator[](const std::string& key) const {
        return values.at(key);
        // Если ключ отсутствует, генерируется исключение std::out_of_range.
    }

    std::string& Section::operator[](const std::string& key) {
        return values[key];
        // Если ключ отсутствует, он добавляется в секцию
        // с пустым значением и возвращается ссылка на это значение.
    }

    const std::unordered_map<std::string, std::string>& Section::GetValues() const {
        return values;
    }

    Section& Document::AddSection(const std::string& name) {
        if (sections.count(name) > 0) {
            std::cerr << "Section is already exists!" << std::endl;
        }
        return sections[name];
    }

    const Section& Document::GetSection(const std::string& name) const {
        return sections.at(name);
    }

    size_t Document::SectionCount() const {
        return sections.size();
    }

    Document Load(std::istream& input) {
        Document doc;
        Section* cur_section = nullptr;
        std::string line;
        std::string merged_line;
        while (std::getline(input, line)) {
            if (line.empty() || line[0] == ';' || line[0] == '#') {
                continue;
            }
            if (!merged_line.empty() && merged_line.back() == '\\') {
                merged_line.pop_back();
                merged_line += line;
                continue;
            }
            merged_line = line;
            if (merged_line[0] == '[') {
                std::string sectionName = merged_line.substr(1, merged_line.size() - 2);
                cur_section = &doc.AddSection(sectionName);
            }
            else {
                std::stringstream ss(merged_line);
                std::string key, value;
                std::getline(ss, key, '=');
                std::getline(ss, value);
                if (!value.empty() && (value.front() == '\'' || value.front() == '\"') && value.front() == value.back())
                    value = value.substr(1, value.size() - 2);
                (*cur_section)[key] = value;
            }
        }
        return doc;
    }
}