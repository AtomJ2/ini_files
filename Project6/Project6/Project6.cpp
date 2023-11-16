#include "Header1.h"
#include <sstream>
#include <gtest/gtest.h>

using namespace Ini;

// Тест для оператора [] const версии Section
TEST(SectionTest, ConstOperatorSquareBrackets) {
    Section section;
    section["key1"] = "value1";
    section["key2"] = "value2";

    const Section& constSection = section;
    EXPECT_EQ(constSection["key1"], "value1");
    EXPECT_EQ(constSection["key2"], "value2");
}

// Тест для оператора [] неконстантной версии Section
TEST(SectionTest, OperatorSquareBrackets) {
    Section section;
    section["key1"] = "value1";
    section["key2"] = "value2";

    EXPECT_EQ(section["key1"], "value1");
    EXPECT_EQ(section["key2"], "value2");
}

// Тест для функции GetValues
TEST(SectionTest, GetValues) {
    Section section;
    section["key1"] = "value1";
    section["key2"] = "value2";

    const std::unordered_map<std::string, std::string>& values = section.GetValues();

    EXPECT_EQ(values.at("key1"), "value1");
    EXPECT_EQ(values.at("key2"), "value2");
}

// Тест для функции AddSection
TEST(DocumentTest, AddSection) {
    Document doc;
    Section& section = doc.AddSection("section1");

    EXPECT_EQ(doc.SectionCount(), 1);
    EXPECT_EQ(&section, &doc.GetSection("section1"));
}

// Тест для функции GetSection
TEST(DocumentTest, GetSection) {
    Document doc;
    Section& section = doc.AddSection("section1");

    const Section& constSection = doc.GetSection("section1");

    EXPECT_EQ(&section, &constSection);
}

// Тест для функции SectionCount
TEST(DocumentTest, SectionCount) {
    Document doc;
    doc.AddSection("section1");
    doc.AddSection("section2");

    EXPECT_EQ(doc.SectionCount(), 2);
}

// Тест для функции Load
TEST(LoadTest, Load) {
    std::stringstream input;
    input << "[section1]\n";
    input << "key1=value1\n";
    input << "\n";
    input << "[section2]\n";
    input << "key2=value2\n";

    Document doc = Load(input);

    EXPECT_EQ(doc.SectionCount(), 2);
    EXPECT_EQ(doc.GetSection("section1")["key1"], "value1");
    EXPECT_EQ(doc.GetSection("section2")["key2"], "value2");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}