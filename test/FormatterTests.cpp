#include "gtest/gtest.h"

#include "HDMapTests.hpp"
#include "Formatter.hpp"

namespace opendrive {
    namespace tests {

        /**
         * Base setup for the tests of the Road class.
         */
        class ConverterTests : public HDMapTests {
        public:
            /**
             * @destrcutor
             */
            ~ConverterTests() override = default;

        protected:

        };

        /**
         * Tests formatting the objects to CSV.
         */
        TEST_F(ConverterTests, testToCSV) {
            std::string csv = opendrive::ObjectsToCSV(*highwayExitSouth);

            std::stringstream expected;
            std::ifstream expectedDataFile("../misc/objects.csv");
            std::string line;
            if (expectedDataFile.is_open()) {
                while (getline(expectedDataFile, line)) {
                    expected << line << '\n';
                }
                expectedDataFile.close();
            }

            ASSERT_STREQ(expected.str().c_str(), csv.c_str());
        }

        /**
         * Tests formatting the objects to YAML.
         */
        TEST_F(ConverterTests, testToYAML) {
            const std::string &formattedYaml = opendrive::ObjectsToYAML(*highwayExitSouth);
            YAML::Node actual = YAML::Load(formattedYaml);
            YAML::Node expected = YAML::LoadFile("../misc/objects.yaml");

            ASSERT_STREQ(expected["geoReference"].as<std::string>().c_str(),
                         actual["geoReference"].as<std::string>().c_str());
            ASSERT_EQ(expected["objects"].IsSequence(), true);
            ASSERT_EQ(expected["objects"].IsSequence(), expected["objects"].IsSequence());

            for (const auto &object : actual["objects"]) {
                ASSERT_EQ(object["id"].IsDefined(), true);
                ASSERT_EQ(object["type"].IsDefined(), true);
                ASSERT_EQ(object["name"].IsDefined(), true);

                ASSERT_EQ(object["validLength"].IsScalar(), true);
                ASSERT_EQ(object["hdg"].IsScalar(), true);
                ASSERT_EQ(object["pitch"].IsScalar(), true);
                ASSERT_EQ(object["roll"].IsScalar(), true);
                ASSERT_EQ(object["height"].IsScalar(), true);
                ASSERT_EQ(object["length"].IsScalar(), true);
                ASSERT_EQ(object["width"].IsScalar(), true);
                ASSERT_EQ(object["radius"].IsScalar(), true);

                ASSERT_EQ(object["position"].IsSequence(), true);
                int i = 0;
                for (const auto &element : object["position"]) {
                    ASSERT_EQ(element.IsScalar(), true);
                    i++;
                }
                ASSERT_EQ(i, 3);

                ASSERT_EQ(object["googleMaps"].IsDefined(), true);
            }
        }

    }// namespace tests
}// namespace opendrive