#pragma once
#include <memory>
#include <string>
#include <vector>
#include <map>

class IntType;
class StringType;
class ArrayIntType;
class ArrayStringType;
class BoolType;
class ObjectType;

class IVisitor
{
public:
    virtual void visit(const IntType* element)          = 0;
    virtual void visit(const StringType* element)       = 0;
    virtual void visit(const ArrayIntType* element)     = 0;
    virtual void visit(const ArrayStringType* element)  = 0;
    virtual void visit(const BoolType* element)         = 0;
    virtual void visit(const ObjectType* element)       = 0;
};

class IDataType
{
public:
    virtual void accept(IVisitor* visitor) const        = 0;
};

class IntType : public IDataType
{
public:
    using value_type        = int32_t;
    using reference         = int32_t&;
    using const_reference   = const int32_t&;

private:
    value_type m_data;
public:
    IntType() : m_data(value_type()) { }
    IntType(const_reference value) : m_data(value) { }

    void accept(IVisitor* visitor) const override;

    reference get_value() { return m_data; }
    const_reference get_value() const { return m_data; }

    void set_value(value_type value) { m_data = value; }
};

class StringType : public IDataType
{
public:
    using value_type        = std::string;
    using reference         = std::string&;
    using const_reference   = const std::string&;

private:
    value_type m_data;
public:
    StringType() : m_data(value_type()) { }
    StringType(const_reference value) : m_data(value) { }

    void accept(IVisitor* visitor) const override;

    reference get_value() { return m_data; }
    const_reference get_value() const { return m_data; }

    void set_value(value_type value) { m_data = value; }
};

class ArrayIntType : public IDataType
{
public:
    using value_type        = std::vector<int32_t>;
    using reference         = std::vector<int32_t>&;
    using const_reference   = const std::vector<int32_t>&;

private:
    value_type m_data;
public:
    ArrayIntType() : m_data(value_type()) { }
    ArrayIntType(const_reference value) : m_data(value) { }

    void accept(IVisitor* visitor) const override;

    reference get_value() { return m_data; }
    const_reference get_value() const { return m_data; }

    void set_value(value_type value) { m_data = value; }
};

class ArrayStringType : public IDataType
{
public:
    using value_type        = std::vector<std::string>;
    using reference         = std::vector<std::string>&;
    using const_reference   = const std::vector<std::string>&;

private:
    value_type m_data;
public:
    ArrayStringType() : m_data(value_type()) { }
    ArrayStringType(const_reference value) : m_data(value) { }

    void accept(IVisitor* visitor) const override;

    reference get_value() { return m_data; }
    const_reference get_value() const { return m_data; }

    void set_value(value_type value) { m_data = value; }
};

class BoolType : public IDataType
{
public:
    using value_type        = bool;
    using reference         = bool&;
    using const_reference   = const bool&;

private:
    value_type m_data;
public:
    BoolType() : m_data(value_type()) { }
    BoolType(const_reference value) : m_data(value) { }

    void accept(IVisitor* visitor) const override;

    reference get_value() { return m_data; }
    const_reference get_value() const { return m_data; }

    void set_value(value_type value) { m_data = value; }
};

class ObjectType : public IDataType
{
public:
    using data_pointer = std::shared_ptr<IDataType>;

    using value_type        = std::map<std::string, data_pointer>;
    using reference         = std::map<std::string, data_pointer>&;
    using const_reference   = const std::map<std::string, data_pointer>&;

private:
    value_type m_data;
public:
    ObjectType() : m_data(value_type()) { }
    ObjectType(const_reference value) : m_data(value) { }

    void accept(IVisitor* visitor) const override;

    reference get_value() { return m_data; }
    const_reference get_value() const { return m_data; }

    void set_value(value_type value) { m_data = value; }
};

template <class T>
class GetValue : public IVisitor
{
    using value_type = T;
    using reference = T&;
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
        if constexpr (std::is_same<value_type, IntType::value_type>::value)
        {
            result = element->get_value();
        }
    }

    void visit(const StringType* element) override
    {
        if constexpr (std::is_same<value_type, StringType::value_type>::value)
        {
            result = element->get_value();
        }
    }

    void visit(const ArrayIntType* element) override
    {
        if constexpr (std::is_same<value_type, ArrayIntType::value_type>::value)
        {
            result = element->get_value();
        }
    }

    void visit(const ArrayStringType* element) override
    {
        if constexpr (std::is_same<value_type, ArrayStringType::value_type>::value)
        {
            result = element->get_value();
        }
    }

    void visit(const BoolType* element) override
    {
        if constexpr (std::is_same<value_type, BoolType::value_type>::value)
        {
            result = element->get_value();
        }
    }

    void visit(const ObjectType* element) override
    {
        if constexpr (std::is_same<value_type, ObjectType::value_type>::value)
        {
            result = element->get_value();
        }
    }
};
