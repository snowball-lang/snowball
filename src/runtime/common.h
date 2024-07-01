
#ifndef __SNOWBALL_RUNTIME_COMMON_H_
#define __SNOWBALL_RUNTIME_COMMON_H_

#ifndef SNOWBALL_HIDDEN_RUNTIME
#define SNOWBALL_RT_VISIBILITY __attribute__((visibility("default")))
#else
#define SNOWBALL_RT_VISIBILITY __attribute__((visibility("hidden")))
#endif

#ifndef SNOWBALL_TEST_EXPORT
#define SNOWBALL_TEST_EXPORT "sn.test.run"
#endif

#ifndef SNOWBALL_TEST_PRE_RUN
#define SNOWBALL_TEST_PRE_RUN "sn.test.start"
#endif

#ifndef SNOWBALL_TEST_POST_RUN
#define SNOWBALL_TEST_POST_RUN "sn.test.end"
#endif

#endif // __SNOWBALL_RUNTIME_COMMON_H_
