
#ifndef __SNOWBALL_API_UTILS_H_
#define __SNOWBALL_API_UTILS_H_

#define CLASS __c
#define METHOD(name, ret, ...) API->create_class_method(CLASS, name, ret, std::vector<std::pair<snowball::Type*, llvm::Type*>> __VA_ARGS__);
#define METHOD_ARGUMENT(name, ty) std::make_pair(name, ty)

#endif // __SNOWBALL_API_UTILS_H_