
#include "../api.h"
#include "../attributes.h"

#include <string>
#include <vector>

#ifndef __SNOWBALL_ATTRIBUTES_TESTS_H_
#define __SNOWBALL_ATTRIBUTES_TESTS_H_
#define __SNOWBALL_CORE_TEST_START() mangle("_SN&.Core&.Testing.&start&")

extern "C" int __sn_testing_try(const char* p_name, void (*p_function)()) {
    printf("  Testing %s ... ", p_name);
    try {
        p_function();

        printf("%sok!%s\n", snowball::BGRN, snowball::RESET);
        return 0;
    } catch(...) {
        // TODO: show exepcion when the "Exception" class is created.

        printf("%serror!%s\n", snowball::BRED, snowball::RESET);
        return 1;
    }
}
namespace snowball {

    class TestsAttribute : public Attribute {
        std::vector<std::string> tests;

        public:
            std::string get_name() override { return "test"; }
            bool start(SNAPI::Context p_ctx) override {
                return p_ctx.is_test && p_ctx.is_crate;
            }

            void end(ResponseValue p_value, SNAPI* p_api) override {

                if (!(p_value.type == ResponseValue::ResponseType::LLVM_FUNCTION)) {
                    // TODO: error
                }

                // TODO: check if arg count is 0 and return type is void
                p_value.function.llvm_value = p_api->compiler->get_generator()->paste_function(p_value.function.store);

                std::string mangled_name = __SNOWBALL_CORE_TEST_START();
                auto mod = p_api->compiler->get_module();

                auto fn = mod->getFunction(mangled_name);
                auto builder = p_api->compiler->builder;

                if (!fn) {
                    auto prototype = llvm::FunctionType::get(builder->getInt32Ty(), {});

                    fn = llvm::Function::Create(
                        prototype,
                        llvm::Function::ExternalLinkage,
                        mangled_name,
                        mod);

                    llvm::BasicBlock *body = llvm::BasicBlock::Create(builder->getContext(), "body", fn);
                    builder->SetInsertPoint(body);

                    builder->CreateRet(llvm::ConstantInt::get(builder->getInt32Ty(), 0));
                }

                llvm::BasicBlock& block = fn->getEntryBlock();
                block.back().eraseFromParent();

                builder->SetInsertPoint(&block);

                run_function(p_value.function.llvm_value, Logger::format(mangle("_SN&.Core&.Testing.&run&..$%s$..@Vd").c_str(), p_value.function.llvm_value->getName().str().c_str()), p_api);

                // 0 means that all tests has been successfuly executed
                builder->CreateRet(llvm::ConstantInt::get(builder->getInt32Ty(), 0));
            }

            void run_function(llvm::Value* p_value, std::string p_function_name, SNAPI* p_api) {
                auto builder = p_api->compiler->builder;
                auto backup = builder->GetInsertBlock();
                auto mod = p_api->compiler->get_module();

                auto prototype = llvm::FunctionType::get(builder->getInt32Ty(), {});

                auto fn = llvm::Function::Create(
                    prototype,
                    llvm::Function::ExternalLinkage,
                    p_function_name,
                    mod);

                llvm::BasicBlock *body = llvm::BasicBlock::Create(builder->getContext(), "body", fn);
                builder->SetInsertPoint(body);

                builder->CreateRetVoid();

                llvm::BasicBlock& block = fn->getEntryBlock();
                block.back().eraseFromParent();

                builder->SetInsertPoint(&block);

                tests.push_back(p_value->getName().str());

                // TODO: unmangled base name
                llvm::Constant* string_value = builder->CreateGlobalStringPtr(unmangle(p_value->getName().str(), "::", true).name, ".test::alloca");

                auto test_fn = get_test_fn(mod, builder);

                auto call = builder->CreateCall(test_fn, { string_value, p_value });


                builder->CreateRet(call);

                builder->SetInsertPoint(backup);
                auto test_call = builder->CreateCall(fn);

                llvm::BasicBlock* IfBB = llvm::BasicBlock::Create(builder->getContext(), "bb", backup->getParent());
                llvm::BasicBlock* ContinueBB = llvm::BasicBlock::Create(builder->getContext(), "bb", backup->getParent());

                builder->CreateCondBr(builder->CreateICmpEQ(test_call, builder->getInt32(1)), IfBB, ContinueBB);

                // Generate if statement
                builder->SetInsertPoint(IfBB);
                builder->CreateRet(llvm::ConstantInt::get(builder->getInt32Ty(), 1));

                // Continue with rest of body
                builder->SetInsertPoint(ContinueBB);
            }

            llvm::Function* get_test_fn(llvm::Module* p_module, std::shared_ptr<llvm::IRBuilder<>> p_builder) {
                llvm::FunctionType* function_type = llvm::FunctionType::get(p_builder->getInt32Ty(), { p_builder->getInt8PtrTy(), llvm::FunctionType::get(p_builder->getVoidTy(), {})->getPointerTo() }, false);
                return (llvm::Function*)p_module->getOrInsertFunction("__sn_testing_try", function_type).getCallee();
            }

            void after_compile(SNAPI* p_api) override {
                if (start(p_api->context)) {
                    auto builder = p_api->compiler->builder;
                    auto backup = builder->GetInsertBlock();
                    auto mod = p_api->compiler->get_module();

                    auto main_function = mod->getFunction(_SNOWBALL_FUNCTION_ENTRY);

                    if (main_function) {
                        main_function->deleteBody();
                    } else {
                        llvm::FunctionType* function_type = llvm::FunctionType::get(builder->getInt32Ty(), {});
                        main_function = (llvm::Function*)mod->getOrInsertFunction(_SNOWBALL_FUNCTION_ENTRY, function_type).getCallee();
                    }

                    llvm::BasicBlock *body = llvm::BasicBlock::Create(builder->getContext(), "body", main_function);
                    builder->SetInsertPoint(body);

                    auto puts = get_puts(mod, builder);

                    if (tests.size() == 0) {
                        builder->CreateCall(puts, { builder->CreateGlobalStringPtr(Logger::format("\n%swarning%s: no unit tests found!", BYEL, RESET), ".test::message::ERNOTESTS") });
                        builder->CreateRet(builder->getInt32(1));
                    } else {
                        builder->CreateCall(puts, { builder->CreateGlobalStringPtr(Logger::format("\nrunning %s%i%s %s:", BCYN, tests.size(), RESET, tests.size() == 1 ? "test" : "tests"), ".test::message") });

                        auto core_test = mod->getFunction(__SNOWBALL_CORE_TEST_START());
                        auto call = builder->CreateCall(core_test);

                        builder->CreateRet(call);
                    }
                }
            };
    };
}

#undef __SNOWBALL_CORE_TEST_START
#endif // __SNOWBALL_ATTRIBUTES_TESTS_H_
