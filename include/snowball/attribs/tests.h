
#include "../api.h"
#include "../attributes.h"

#ifndef __SNOWBALL_ATTRIBUTES_TESTS_H_
#define __SNOWBALL_ATTRIBUTES_TESTS_H_

extern "C" int __sn_testing_try(void (*f)()) {
    try {
        f();
        return 0;
    } catch(...) {
        return 1;
    }
}

namespace snowball {

    class TestsAttribute : public Attribute {
        public:
            std::string get_name() { return "test"; };
            bool start(SNAPI::Context p_ctx) override {
                return p_ctx.is_test;
            }

            void end(llvm::Value* p_value, SNAPI* p_api) override {

                if (!p_value->getType()->isFunctionTy()) {
                    // TODO: error
                }

                // TODO: check if arg count is 0 and return type is void

                std::string mangled_name = mangle("_SN&.Core&.Testing.&start&");
                auto mod = p_api->compiler->get_module();

                auto fn = mod->getFunction(mangled_name);
                auto builder = p_api->compiler->builder;

                if (!fn) {
                    auto prototype = llvm::FunctionType::get(builder->getVoidTy(), {});

                    fn = llvm::Function::Create(
                        prototype,
                        llvm::Function::ExternalLinkage,
                        mangled_name,
                        mod);

                    llvm::BasicBlock *body = llvm::BasicBlock::Create(builder->getContext(), "body", fn);
                    builder->SetInsertPoint(body);

                    builder->CreateRetVoid();
                }

                llvm::BasicBlock& block = fn->getEntryBlock();
                block.back().eraseFromParent();

                builder->SetInsertPoint(&block);

                llvm::Constant* string_value = builder->CreateGlobalStringPtr(unmangle(p_value->getName().str(), "::").name, ".test::alloca");

                auto test_fn = get_test_fn(mod, builder);
                auto call = builder->CreateCall(test_fn, { p_value });


                builder->CreateRetVoid();
            }

            llvm::Function* get_test_fn(llvm::Module* p_module, std::shared_ptr<llvm::IRBuilder<>> p_builder) {
                llvm::FunctionType* function_type = llvm::FunctionType::get(p_builder->getInt1Ty(), { llvm::FunctionType::get(p_builder->getVoidTy(), {})->getPointerTo() }, false);
                return (llvm::Function*)p_module->getOrInsertFunction("__sn_testing_try", function_type).getCallee();
            }

            void after_compile(SNAPI* p_api) {
                if (start(p_api->context)) {

                }
            };
    };
}

#endif // __SNOWBALL_ATTRIBUTES_TESTS_H_
