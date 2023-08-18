
#include "SnowballIREmitter.h"
#include "../../ir/module/Module.h"
#include "../../ir/module/MainModule.h"
#include "../../ir/values/all.h"

namespace snowball {
namespace codegen {

SnowballIREmitter::SnowballIREmitter(std::shared_ptr<ir::Module> p_module) 
    : module(p_module) { }

void SnowballIREmitter::codegen(std::string p_output) {
    
    auto mainModule = utils::dyn_cast<ir::MainModule>(module);
    assert(mainModule);

    for (auto m : mainModule->getModules()) visit(m);
    visit(mainModule);

    // write content to file
    std::ofstream file(p_output);
    file << output.str();
    file.close();
}

void SnowballIREmitter::addContent(std::string str) {
    output << str;
}

void SnowballIREmitter::visit(std::shared_ptr<ir::Module> m) {
    addContent("module " + m->getName() + " {\n");
    for (auto v : m->getVariables()) {
        addContent("  var " + v->getIdentifier() + " : " + v->getType()->getPrettyName());
        if (v->getValue()) {
            addContent(" = ");
            v->getValue()->visit(this);
        } 
        addContent(";\n");
    }
    for (auto f : m->getFunctions()) {
        if (f->isExternal(f->getMangle())) addContent("  extern ");
        else addContent("  ");
        addContent("fn " + f->getNiceName() + "(");
        for (auto p : f->getArgs()) {
            p.second->visit(this);
            if (p != f->getArgs().back()) addContent(", ");
        }
        addContent(") : " + f->getRetTy()->getPrettyName());
        if (f->isExternal(f->getMangle())) addContent(";\n");
        else if (f->hasAttribute(Attributes::LLVM_FUNC)) {
            addContent(" [LLVM] {\n");
            addContent("    " + f->getLLVMBody() + "\n");
            addContent("  }\n");
        } else if (!f->isDeclaration()) {
            addContent(" ");
            f->getBody()->visit(this);
            addContent("\n\n");
        }
    }
    addContent("}\n");
}

void SnowballIREmitter::visit(ir::Variable* v) {
    addContent(v->getIdentifier());
}

void SnowballIREmitter::visit(ir::Func* f) {
    addContent(f->getNiceName());
}

void SnowballIREmitter::visit(ir::Block* b) {
    addContent("{\n");
    for (auto s : b->getBlock()) {
        addContent("    ");
        s->visit(this);
        addContent("\n");
    }
    addContent("  }");
}

void SnowballIREmitter::visit(ir::Return* r) {
    addContent("return ");
    if (r->getExpr())
        r->getExpr()->visit(this);
}

void SnowballIREmitter::visit(ir::Call* c) {
    c->getCallee()->visit(this);
    addContent("(");
    for (auto a : c->getArguments()) {
        a->visit(this);
        if (a != c->getArguments().back()) addContent(", ");
    }
    addContent(")");
}

void SnowballIREmitter::visit(ir::Conditional* c) {
    addContent("if (");
    c->getCondition()->visit(this);
    addContent(") ");
    c->getBlock()->visit(this);
    if (c->getElse()) {
        addContent(" else ");
        c->getElse()->visit(this);
    }
}

void SnowballIREmitter::visit(ir::WhileLoop* w) {
    addContent("while (");
    w->getCondition()->visit(this);
    addContent(") ");
    w->getBlock()->visit(this);
}

void SnowballIREmitter::visit(ir::Cast* c) {
    addContent("cast<");
    addContent(c->getCastType()->getPrettyName());
    addContent(">(");
    c->getExpr()->visit(this);
    addContent(")");
}

void SnowballIREmitter::visit(ir::TryCatch* tc) {
    addContent("try ");
    tc->getBlock()->visit(this);
    for (auto i = 0; i < tc->getCatchBlocks().size(); i++) {
        addContent(" catch (");
        tc->getCatchVars()[i]->visit(this);
        addContent(": ");
        addContent(tc->getCatchVars()[i]->getType()->getPrettyName());
        addContent(") ");
        tc->getCatchBlocks()[i]->visit(this);
    }
}

void SnowballIREmitter::visit(ir::Throw* t) {
    addContent("throw ");
    t->getExpr()->visit(this);
}

void SnowballIREmitter::visit(ir::VariableDeclaration* vd) {
    addContent("(" + vd->getIdentifier());
    if (vd->getValue()) {
        addContent(" = ");
        vd->getValue()->visit(this);
    } 
    addContent(")");
}

void SnowballIREmitter::visit(ir::IndexExtract* ie) {
    addContent("(");
    ie->getValue()->visit(this);
    addContent(")");
    addContent(" get element at ");
    addContent(std::to_string(ie->getIndex()));
    addContent(" (field: " + ie->getField()->name + ")");
}

void SnowballIREmitter::visit(ir::ValueExtract* ve) {
    addContent("load ");
    ve->getValue()->visit(this);
}

void SnowballIREmitter::visit(ir::Argument* a) {
    addContent(a->getName());
    addContent(": ");
    addContent(a->getType()->getPrettyName());
}

void SnowballIREmitter::visit(ir::NumberValue* nv) {
    addContent(std::to_string(nv->getConstantValue()));
}

void SnowballIREmitter::visit(ir::BooleanValue* bv) {
    addContent(bv->getConstantValue() ? "true" : "false");
}

void SnowballIREmitter::visit(ir::StringValue* sv) {
    addContent("\"" + sv->getConstantValue() + "\"");
}

void SnowballIREmitter::visit(ir::FloatValue* fv) {
    addContent(std::to_string(fv->getConstantValue()));
}

void SnowballIREmitter::visit(ir::CharValue* cv) {
    addContent("\'" + std::to_string(cv->getConstantValue()) + "\'");
}

void SnowballIREmitter::visit(ir::ReferenceTo* rt) {
    addContent("&(");
    rt->getValue()->visit(this);
    addContent(")");
}

void SnowballIREmitter::visit(ir::DereferenceTo* d) {
    addContent("*(");
    d->getValue()->visit(this);
    addContent(")");
}

}
}
