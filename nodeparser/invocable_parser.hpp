//
// Created by 刘典 on 2021/9/12.
//

#ifndef NODEDRIVING_INVOCABLE_PARSER_HPP
#define NODEDRIVING_INVOCABLE_PARSER_HPP

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CompilationDatabase.h>
#include "invocable.hpp"
#include <filesystem>
#include <list>
#include <optional>

class FindInvocableContext {
private:
    std::list<Invocable> &_result;
    const std::filesystem::path &_includePaths, &_file;
public:
    FindInvocableContext(std::list<Invocable> &result, const std::filesystem::path &includePaths,
                         const std::filesystem::path &file) : _result(result), _includePaths(includePaths),
                                                              _file(file) {}

    FindInvocableContext(const FindInvocableContext &other) = delete;

    FindInvocableContext &operator=(const FindInvocableContext &other) = delete;


    std::list<Invocable> &getResult() const {
        return _result;
    }

    const std::filesystem::path &getIncludePaths() const {
        return _includePaths;
    }

    const std::filesystem::path &getFile() const {
        return _file;
    }

    std::filesystem::path getHeaderFile() const {
        return std::filesystem::relative(_file, _includePaths);
    };

};

class FindInvocableVisitor
        : public clang::RecursiveASTVisitor<FindInvocableVisitor> {
public:
    explicit FindInvocableVisitor(clang::ASTContext *context, FindInvocableContext &findInvocableContext)
            : _context(context), _findContext(findInvocableContext) {}



    bool VisitCXXRecordDecl(clang::CXXRecordDecl *decl) {
        if (!inFile(decl))
            return true;
        Invocable invocable;
        invocable.setType(Invocable::Class);
        invocable.setName(decl->getQualifiedNameAsString());
        invocable.setHeaderFile(_findContext.getHeaderFile().string());
        for(const auto *method: decl->methods()) {
            const auto *ctor = clang::dyn_cast<clang::CXXConstructorDecl>(method);
            if(!ctor)
                continue;
            if(ctor->getAccess()!=clang::AS_public)
                continue;
            if(ctor->isDefaultConstructor() || ctor->isCopyOrMoveConstructor())
                continue;
            llvm::outs() << "constructor: " << ctor->getNameAsString() << " params: " << ctor->getNumParams() << "\n";
            parseConstructorParams(ctor, invocable);

        }
        if(parseFields(decl, invocable)) {
            _findContext.getResult().push_back(invocable);
        }

        return true;
    }


private:
    std::optional<Port> parsePort(const clang::FieldDecl *field) {
        if(field->getAccess() != clang::AS_public)
            return {};
        Port ret;
        ret.setName(field->getNameAsString());
        clang::QualType type = field->getType();
        const auto *tst = type->getAs<clang::TemplateSpecializationType>();
        if(!tst)
            return {};
        if(!tst->isRecordType())
            return {};
        std::string temp_name =  tst->getAs<clang::RecordType>()->getDecl()->getQualifiedNameAsString();
        if(temp_name == "adas::node::out")
            ret.setDirection(Port::Out);
        else if(temp_name == "adas::node::in")
            ret.setDirection(Port::In);
        else
            return {};
        if(tst->getNumArgs() != 1)
            return {};
        if (tst->getArg(0).getKind() != clang::TemplateArgument::Type)
            return {};
        ret.setType(tst->getArg(0).getAsType().getAsString());
        return ret;
    }
    bool parseFields(const clang::CXXRecordDecl *decl, Invocable &invocable) {
        std::vector<Port> ports;
        for (const auto *field: decl->fields()) {
            auto port_opt = parsePort(field);
            if(!port_opt)
                continue;
            ports.push_back(*port_opt);
        }
        if(ports.empty())
            return false;
        invocable.setPortList(ports);
        return true;
    }

    void parseConstructorParams(const clang::CXXConstructorDecl *decl, Invocable & invocable) {
        std::vector<Param> params(decl->getNumParams());
        for (int i = 0; i < decl->getNumParams(); ++i) {
            auto & p = params[i];
            const clang::ParmVarDecl *parmVarDecl = decl->getParamDecl(i);
            p.setType(parmVarDecl->getType().getAsString());
            p.setName(parmVarDecl->getNameAsString());
            llvm::outs() << "type: " << p.getType() << " name: " << p.getName() << "\n";
        }
        invocable.setParamList(params);

    }

    bool inFile(clang::Decl *decl) {
        clang::FullSourceLoc fullSourceLoc = _context->getFullLoc(decl->getBeginLoc());
        if (!fullSourceLoc.isValid())
            return false;
        auto file_entry = fullSourceLoc.getFileEntry();
        if (!file_entry || !file_entry->isValid())
            return false;
        std::filesystem::path file = file_entry->getName().str();
        return std::filesystem::equivalent(file, _findContext.getFile());
    }

private:
    clang::ASTContext *_context;
    FindInvocableContext &_findContext;
};

class FindInvocableConsumer : public clang::ASTConsumer {
public:
    explicit FindInvocableConsumer(clang::ASTContext *context, FindInvocableContext &findInvocableContext)
            : _visitor(context, findInvocableContext) {}

    void HandleTranslationUnit(clang::ASTContext &context) override {
        _visitor.TraverseDecl(context.getTranslationUnitDecl());
    }

private:
    FindInvocableVisitor _visitor;
};

class FindInvocableAction : public clang::ASTFrontendAction {
public:
    explicit FindInvocableAction(FindInvocableContext &findInvocableContext) : _findContext(findInvocableContext) {}

    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
            clang::CompilerInstance &compiler, llvm::StringRef inFile) override {
        return std::make_unique<FindInvocableConsumer>(&compiler.getASTContext(), _findContext);
    }

private:
    FindInvocableContext &_findContext;
};

class FindInvocableActionFactory : public clang::tooling::FrontendActionFactory {
public:
    explicit FindInvocableActionFactory(FindInvocableContext &findContext) : _findContext(findContext) {}

    std::unique_ptr<clang::FrontendAction> create() override {
        return std::make_unique<FindInvocableAction>(_findContext);
    }

private:
    FindInvocableContext &_findContext;
};

class InvocableParser {
private:
    std::filesystem::path _includePaths;
public:
    void setIncludePaths(const std::filesystem::path &includePaths) {
        _includePaths = includePaths;
    }

    bool parse(const std::filesystem::path &file, std::list<Invocable> &result, std::string &error_message) {
        FindInvocableContext findInvocableContext(result, _includePaths, file);
        clang::tooling::FixedCompilationDatabase compilation(".", {});
        clang::tooling::ClangTool tool(compilation, {file.string()});
        tool.appendArgumentsAdjuster(
                getInsertArgumentAdjuster("-std=c++17",
                                          clang::tooling::ArgumentInsertPosition::END));
        tool.appendArgumentsAdjuster(
                getInsertArgumentAdjuster({"-I", "/home/fc/clang+llvm-12.0.0-x86_64-linux-gnu-ubuntu-20.04/lib/clang/12.0.0/include"},
                                          clang::tooling::ArgumentInsertPosition::END));
        tool.appendArgumentsAdjuster(
                getInsertArgumentAdjuster({"-I", "/home/fc/works/CLionProjects/runtime/include"},
                                          clang::tooling::ArgumentInsertPosition::END));
        tool.appendArgumentsAdjuster(
                getInsertArgumentAdjuster({"-I", "/usr/local/boost_1_76_0/include"},
                                          clang::tooling::ArgumentInsertPosition::END));
        tool.appendArgumentsAdjuster(
                getInsertArgumentAdjuster({"-I", _includePaths.string()},
                                          clang::tooling::ArgumentInsertPosition::END));
        //        tool.appendArgumentsAdjuster(getInsertArgumentAdjuster("-v", // Verbose
        //                                                               clang::tooling::ArgumentInsertPosition::END));
        //        tool.appendArgumentsAdjuster(getInsertArgumentAdjuster("--language=c++", // C++
        //                                                               clang::tooling::ArgumentInsertPosition::END));
        FindInvocableActionFactory factory(findInvocableContext);
        //tool.setDiagnosticConsumer(nullptr);
        int ret = tool.run(&factory);
        if (ret != 0) {
            error_message = "编译错误，请查看编译日志";
            return false;
        }
        return true;
    }

};


#endif //NODEDRIVING_INVOCABLE_PARSER_HPP
