//
// Created by 刘典 on 2021/10/21.
//

#ifndef NODEDRIVING_SOURCE_GENERATOR_HPP
#define NODEDRIVING_SOURCE_GENERATOR_HPP

#include <nodes/FlowScene>
#include <nodes/Node>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include "models.hpp"
#include <iostream>
#include <sstream>

class SourceGenerator {
private:
    static void extractIncludes(const QtNodes::FlowScene &scene, std::set<std::string> &includes) {
        for (const auto *node: scene.allNodes()) {
            const auto *model = static_cast<InvocableDataModel *>(node->nodeDataModel());
            includes.insert(model->invocable().getHeaderFile());
        }
    }

    static void
    makeNodeVarNames(const QtNodes::FlowScene &scene, std::map<const InvocableDataModel *, std::string> &nodeVarNames) {
        int i = 0;
        for (const auto *node: scene.allNodes()) {
            const auto *model = static_cast<InvocableDataModel *>(node->nodeDataModel());
            nodeVarNames.insert({model, "_node" + std::to_string(i++)});
        }
    }

    static void makeConnections(const QtNodes::FlowScene &scene,
                                const std::map<const InvocableDataModel *, std::string> &nodeVarNames,
                                std::map<std::string, std::vector<std::string>> &connections) {
        for(const auto & p: scene.connections()) {
            const auto & c = *p.second;
            const QtNodes::Node * out_node = c.getNode(QtNodes::PortType::Out);
            const auto *out_model = static_cast<InvocableDataModel *>(out_node->nodeDataModel());
            const QtNodes::Node * in_node = c.getNode(QtNodes::PortType::In);
            const auto *in_model = static_cast<InvocableDataModel *>(in_node->nodeDataModel());
            const auto & out_port = c.dataType(QtNodes::PortType::Out);
            const auto & in_port = c.dataType(QtNodes::PortType::In);
            std::string out = nodeVarNames.find(out_model)->second + "." + out_port.name.toStdString();
            std::string in = nodeVarNames.find(in_model)->second + "." + in_port.name.toStdString();
            if(connections.find(out) == connections.end())
                connections.insert({out, {}});
            connections.find(out)->second.push_back(in);


        }

    }

    static std::string indent(int n) {
        return std::string(4 * n, ' ');
    }

    static void generateIncludes(const std::set<std::string> &includes, std::ofstream &file) {
        file << "#include <adas/runtime.hpp>" << std::endl;
        file << "#include <unistd.h>" << std::endl;
        for (const auto &inc: includes)
            file << "#include <" << inc << ">" << std::endl;
    }
    static std::string nodeParamValueList(const std::vector<Param> & params) {
        if(params.empty())
            return "";
        std::stringstream ss;
        ss << "{";
        bool first = true;
        for(const Param & p: params) {
            if(!first)
                ss << ", ";
            ss << p.getLiteral();
            first = false;
        }
        ss << "}";
        return ss.str();

    }
    static void generateTask(const std::map<const InvocableDataModel *, std::string> &varNames,
                             const std::map<std::string, std::vector<std::string>> &connections, std::ofstream &file) {
        file << "class task0 {" << std::endl;
        file << "private:" << std::endl;
        for(const auto & p: varNames) {
            const std::string & type = p.first->invocable().getName();
            const std::string & name = p.second;
            file << indent(1) << type << " " << name << nodeParamValueList(p.first->invocable().getParamList()) << ";" << std::endl;
        }
        file << "public:" << std::endl;
        file << indent(1) << "task0() {" << std::endl;
        for(const auto & p: connections) {
            file << indent(2) << p.first << ".handler([this](auto value) {" << std::endl;
            for(const auto & in: p.second) {
                file << indent(3) << in << ".set(value);" << std::endl;
            }
            file << indent(2) <<"});" << std::endl;

        }
        file << indent(1) << "}" << std::endl;
        file << "};" << std::endl;

    }
    static void generateMain(std::ofstream & file) {
        file << "int main(int argc, char **argv) {" << std::endl;
        file << indent(1) << "adas::runtime::task<task0> _task0;" << std::endl;
        file << indent(1) << "pause();" << std::endl;
        file << "}" << std::endl;

    }

public:
    static void generate(const QtNodes::FlowScene &scene, std::ofstream &file) {
        std::set<std::string> includes;
        std::map<const InvocableDataModel *, std::string> varNames;
        std::map<std::string, std::vector<std::string>> connections;
        extractIncludes(scene, includes);
        makeNodeVarNames(scene, varNames);
        makeConnections(scene, varNames, connections);
        generateIncludes(includes, file);
        generateTask(varNames, connections, file);
        generateMain(file);

    }

};

#endif //NODEDRIVING_SOURCE_GENERATOR_HPP
