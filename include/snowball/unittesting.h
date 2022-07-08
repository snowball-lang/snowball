
#ifndef __SNOWBALL_UNIT_TESTING_H_
#define __SNOWBALL_UNIT_TESTING_H_

namespace snowball {
    class TestingContext {

        public:
            TestingContext() {};

            int addTest() { return ++_length; }
            int getTest() { return _length; }

            ~TestingContext() {};
        private:
            int _length = 0;
    };
}

#endif // __SNOWBALL_UNIT_TESTING_H_
