//
// Created by 刘典 on 2021/9/12.
//

#ifndef NODEDRIVING_INVOCABLE_HPP
#define NODEDRIVING_INVOCABLE_HPP
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <iostream>

class Port {
public:
    enum Direction {In, Out};
private:
    std::string _type;
    std::string _name;
    Direction _direction;
public:

    const std::string &getType() const {
        return _type;
    }

    void setType(const std::string &type) {
        _type = type;
    }

    const std::string &getName() const {
        return _name;
    }

    void setName(const std::string &name) {
        _name = name;
    }

    Direction getDirection() const {
        return _direction;
    }

    void setDirection(Direction direction) {
        _direction = direction;
    }
};

class Param {
private:
    std::string _type, _name, _value;
public:
    const std::string &getType() const {
        return _type;
    }

    void setType(const std::string &type) {
        _type = type;
        if(_type == "_Bool")
            _type = "bool";
    }

    const std::string &getName() const {
        return _name;
    }

    void setName(const std::string &name) {
        _name = name;
    }

    const std::string getValue() const {
        if(_value.empty()) {
            if(isInteger())
                return "0";
            else if(isFloat())
                return "0.0";
        }
        return _value;
    }

    void setValue(const std::string &value) {
        _value = value;
    }

    bool isInteger() const {
        return _type == "int" || _type == "bool";
    }

    bool isFloat() const {
        return _type == "float" || _type == "double";
    }

    bool isString() const {
        return  _type == "std::string";
    }

    const std::string getLiteral() const {
        if(isInteger()) {
            if(_type=="bool") {
                if(getValue()=="0")
                    return "false";
                else
                    return "true";
            }
            return _value.empty() ? "0" : _value;
        }else if(isFloat()) {
            return _value.empty() ? "0.0" : _value;
        } else if(isString()) {
            return "\"" + _value + "\"";
        } else {
            std::cerr << "warning: param type: " + _type + "not support";
            return "\"" + _value + "\"";
        }
    }
};

class Invocable {
public:
    enum Type {Function, Class};
private:
    Type _type;
    std::string _name;
    std::string _header_file;
    std::vector<Port> _portList;
    std::vector<Param> _paramList;
public:
    Type getType() const {
        return _type;
    }

    void setType(Type type) {
        _type = type;
    }

    const std::string &getName() const {
        return _name;
    }

    void setName(const std::string &name) {
        _name = name;
    }

    const std::string &getHeaderFile() const {
        return _header_file;
    }

    void setHeaderFile(const std::string &headerFile) {
        _header_file = headerFile;
    }

    const std::vector<Port> &getPortList() const {
        return _portList;
    }

    void setPortList(const std::vector<Port> &portList) {
        _portList = portList;
    }

    const std::vector<Param> & getParamList() const {
        return _paramList;
    }

    void setParamList(const std::vector<Param> & paramList) {
        _paramList = paramList;
    }
    bool hasParam(const std::string & name) {
        return std::find_if(_paramList.begin(), _paramList.end(), [&name](const Param & p){return p.getName() == name;}) != _paramList.end();
    }
    void setParamValue(const std::string & name, const std::string & value) {
        auto iter = std::find_if(_paramList.begin(), _paramList.end(), [&name](const Param & p){return p.getName() == name;});
        if(iter==_paramList.end())
            throw std::logic_error("param name '" + name + "' not exists");
        iter->setValue(value);
    }



    bool operator<(const Invocable &rhs) const {
        return _name < rhs._name;
    }
    unsigned int getNumOutput() const {
        return std::count_if(_portList.begin(), _portList.end(), [](const Port & p){return p.getDirection() == Port::Out;});
    }
    unsigned int getNumInput() const {
        return std::count_if(_portList.begin(), _portList.end(), [](const Port & p){return p.getDirection() == Port::In;});

    }
    const Port getInputPort(unsigned int i) const {
        int j = 0;
        for(const auto & p:_portList) {
            if(p.getDirection() == Port::In ) {
                if(j==i) return p;
                else j++;
            }
        }
        throw std::out_of_range("input port index out of range");

    }
    const Port & getOutputPort(unsigned int i) const {
        int j = 0;
        for(const auto & p:_portList) {
            if(p.getDirection() == Port::Out ) {
                if(j==i) return p;
                else j++;
            }

        }
        std::cout << "here" << std::endl;
        throw std::out_of_range("output port index out of range");

    }

};
#endif //NODEDRIVING_INVOCABLE_HPP
