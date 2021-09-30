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
        const clang::CXXMethodDecl *operatorCall = findOperatorCallDecl(decl);
        if (!operatorCall)
            return true;
        if(parseParamsAndReturn(operatorCall, invocable)) {
            _findContext.getResult().push_back(invocable);
        }

        return true;
    }

    bool VisitFunctionDecl(clang::FunctionDecl *decl) {
        if (decl->isCXXClassMember() || decl->isCXXInstanceMember())
            return true;
        if (!inFile(decl))
            return true;
        Invocable invocable;
        invocable.setType(Invocable::Function);
        invocable.setName(decl->getQualifiedNameAsString());
        invocable.setHeaderFile(_findContext.getHeaderFile().string());
        if(parseParamsAndReturn(decl, invocable)) {
            _findContext.getResult().push_back(invocable);
        }
        return true;

    }

private:
    static const clang::CXXMethodDecl *findOperatorCallDecl(clang::CXXRecordDecl *decl) {
        for (const auto *method: decl->methods()) {
            if (method->getNameAsString() == "operator()" && method->getAccess() == clang::AS_public)
                return method;

        }
        return nullptr;
    }

    static bool parseParam(const clang::ParmVarDecl *decl, Param &param) {
        param.setName(decl->getNameAsString());
        clang::QualType type = decl->getType();
        if (type->isBuiltinType() || type->isRecordType()) {
            param.setPassing(Param::Value);
            param.setDirection(Param::In);
            param.setType(type.getUnqualifiedType().getAsString());
            return true;
        }
        if (type->isPointerType() || type->isLValueReferenceType()) {
            if (type->isPointerType())
                param.setPassing(Param::Pointer);
            else
                param.setPassing(Param::Ref);
            clang::QualType ee = type->getPointeeType();
            if (!ee->isBuiltinType() && !ee->isRecordType())
                return false;
            if (ee.isConstQualified())
                param.setDirection(Param::In);
            else
                param.setDirection(Param::Out);
            param.setType(ee.getUnqualifiedType().getAsString());
            return true;
        }
        return false;
    }

    static bool parseReturning(const clang::QualType &returnType, Returning & returning) {
        if (returnType->isBuiltinType() || returnType->isRecordType()) {
            returning.setType(returnType.getUnqualifiedType().getAsString());
            returning.setPassing(Returning::Value);
            return true;
        }

        if (returnType->isPointerType() || returnType->isLValueReferenceType()) {
            if (returnType->isPointerType())
                returning.setPassing(Returning::Pointer);
            else
                returning.setPassing(Returning::Ref);
            clang::QualType ee = returnType->getPointeeType();
            if (!ee->isBuiltinType() && !ee->isRecordType())
                return false;
            returning.setType(ee.getUnqualifiedType().getAsString());
            return true;
        }
        return false;
    }

    static bool parseParamsAndReturn(const clang::FunctionDecl *decl, Invocable &invocable) {
        std::vector<Param> params(decl->getNumParams());
        for (int i = 0; i < decl->getNumParams(); ++i) {
            const clang::ParmVarDecl *parmVarDecl = decl->getParamDecl(i);
            if(!parseParam(parmVarDecl, params[i]))
                return false;
        }
        invocable.setParamList(params);
        Returning returning;
        if(!parseReturning(decl->getReturnType(), returning))
            return false;
        invocable.setReturning(returning);
        return true;
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
                getInsertArgumentAdjuster({"-I", "/home/fc/clang+llvm-12.0.0-x86_64-linux-gnu-ubuntu-20.04/lib/clang/12.0.0/include"},
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
