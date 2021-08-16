#pragma once
#include <iostream>
#include <string>
#include <vector>

class IntType;
class StringType;
class ArrayIntType;


class IVisitor
{
public:
    virtual void visit(const IntType* element)      = 0;
    virtual void visit(const StringType* element)   = 0;
    virtual void visit(const ArrayIntType* element) = 0;
};

class IDataType
{
public:
    virtual void accept(IVisitor* visitor) const    = 0;
};

class IntType : public IDataType
{
    using value_type      = int32_t;
    using reference       = int32_t&;
    using const_reference = const int32_t&;

private:
    value_type m_data;
public:
    IntType() : m_data(value_type()) { }
    IntType(const_reference value) : m_data(value) { }

    void accept(IVisitor* visitor) const override;

    reference get_value() { return m_data; }
    const_reference get_value() const { return m_data; }
};

class StringType : public IDataType
{
    using value_type      = std::string;
    using reference       = std::string&;
    using const_reference = const std::string&;

private:
    value_type m_data;
public:
    StringType() : m_data(value_type()) { }
    StringType(const_reference value) : m_data(value) { }

    void accept(IVisitor* visitor) const override;

    reference get_value() { return m_data; }
    const_reference get_value() const { return m_data; }
};

class ArrayIntType : public IDataType
{
    using value_type = std::vector<IntType>;
    using reference = std::vector<IntType>&;
    using const_reference = const std::vector<IntType>&;

private:
    value_type m_data;
public:
    ArrayIntType() : m_data(value_type()) { }
    ArrayIntType(const_reference value) : m_data(value) { }

    void accept(IVisitor* visitor) const override;

    reference get_value() { return m_data; }
    const_reference get_value() const { return m_data; }
};

template <class T>
class GetValue : public IVisitor
{
    using value_type      = T;
    using reference       = T&;
    using const_reference = const T&;

private:
    value_type result;
    void set_value(value_type value) { result = value; }

public:
    GetValue() : result(value_type()) { }
    
    value_type get_value() { return result; }
    const value_type get_value() const { return result; }

    void visit(const IntType* element) override
    {
        if constexpr (std::is_same_v<value_type, int>)
        {
            // std::cout << "This shit int" << element->get_value();
            result = element->get_value();
        }
    }

    void visit(const StringType* element) override
    {
        // std::cout << "This shit string" << element->get_value();
        if constexpr (std::is_same_v<value_type, std::string>)
        {
            result = element->get_value();
        }
    }

    void visit(const ArrayIntType* element) override
    {
        std::cout << "This shit";
    }


};
