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

class Param {
public:
    enum Direction {In, Out};
    enum Passing {Value, Pointer, Ref};
private:
    std::string _type;
    std::string _name;
    Direction _direction;
    Passing _passing;
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

    Passing getPassing() const {
        return _passing;
    }

    void setPassing(Passing passing) {
        _passing = passing;
    }
};

class Returning {
public:
    enum Passing {Value, Pointer, Ref};
private:
    std::string _type;
    Passing _passing;
public:
    const std::string &getType() const {
        return _type;
    }

    void setType(const std::string &type) {
        _type = type;
    }

    Passing getPassing() const {
        return _passing;
    }

    void setPassing(Passing passing) {
        _passing = passing;
    }

    bool isVoid() const {
        return _type == "void";
    }

};

class Invocable {
public:
    enum Type {Function, Class};
private:
    Type _type;
    std::string _name;
    std::string _header_file;
    std::vector<Param> _paramList;
    Returning _returning;
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

    const std::vector<Param> &getParamList() const {
        return _paramList;
    }

    void setParamList(const std::vector<Param> &paramList) {
        _paramList = paramList;
    }

    const Returning &getReturning() const {
        return _returning;
    }

    void setReturning(const Returning &returning) {
        _returning = returning;
    }

    bool operator<(const Invocable &rhs) const {
        return _name < rhs._name;
    }
    unsigned int getNumOutput() const {
        return std::count_if(_paramList.begin(), _paramList.end(), [](const Param & p){return p.getDirection()==Param::Out;});
    }
    unsigned int getNumInput() const {
        return std::count_if(_paramList.begin(), _paramList.end(), [](const Param & p){return p.getDirection()==Param::In;});

    }
    const Param & getInputParam(unsigned int i) const {
        int j = 0;
        for(const auto & p:_paramList) {
            if(p.getDirection()==Param::In ) {
                if(j==i) return p;
                else j++;
            }
        }
        throw std::out_of_range("input param index out of range");

    }
    const Param & getOutputParam(unsigned int i) const {
        int j = 0;
        for(const auto & p:_paramList) {
            if(p.getDirection()==Param::Out ) {
                if(j==i) return p;
                else j++;
            }

        }
        std::cout << "here" << std::endl;
        throw std::out_of_range("output param index out of range");

    }

};
#endif //NODEDRIVING_INVOCABLE_HPP
