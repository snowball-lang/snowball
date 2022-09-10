
#include "api.h"

#ifndef __SNOWBALL_ATTRIBUTES_H_
#define __SNOWBALL_ATTRIBUTES_H_

namespace snowball {

    class Attribute {
        public:
            virtual std::string get_name() {};
            virtual bool start(SNAPI::Context p_ctx) { /* throw errror about attribute not defined */ };
            virtual void end(llvm::Value* p_value, SNAPI* p_api) {  };

            virtual void after_compile(SNAPI* p_api) {  };

            virtual ~Attribute() { }
    };
}

#endif // __SNOWBALL_ATTRIBUTES_H_
