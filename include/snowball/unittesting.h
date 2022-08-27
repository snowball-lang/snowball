

#include <string>
#include <vector>

#include "logger.h"

#ifndef __SNOWBALL_UNIT_TESTING_H_
#define __SNOWBALL_UNIT_TESTING_H_

namespace snowball {
    class TestingContext {

        public:
            TestingContext() {};

            int addTest(std::string p_desc) { _tests.push_back(p_desc); return _tests.size(); }
            int getTestLength() { return _tests.size(); }
            std::string getTestAt(int i) { return _tests.at(i); }

            std::string get_name(int number) {
                return Logger::format("_SNTSsc?%i..Prv$V", number);
            }

            ~TestingContext() {};
        private:
            std::vector<std::string> _tests;
    };
}

#endif // __SNOWBALL_UNIT_TESTING_H_
