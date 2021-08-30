#pragma once
#include "DataType.h"

class Factory
{
public:
	template <class _Ty>
	std::shared_ptr<IDataType> get_instance(_Ty);
};


template<>
inline std::shared_ptr<IDataType> Factory::get_instance<int32_t>(int32_t value)
{
	return std::make_shared<IntType>(value);
}

template<>
inline std::shared_ptr<IDataType> Factory::get_instance<std::string>(std::string value)
{
	return std::make_shared<StringType>(value);
}

template<>
inline std::shared_ptr<IDataType> Factory::get_instance<std::vector<int32_t>>(std::vector<int32_t> value)
{
	return std::make_shared<ArrayIntType>(value);
}

template<>
inline std::shared_ptr<IDataType> Factory::get_instance<std::vector<std::string>>(std::vector<std::string> value)
{
	return std::make_shared<ArrayStringType>(value);
}

template<>
inline std::shared_ptr<IDataType> Factory::get_instance<bool>(bool  value)
{
	return std::make_shared<BoolType>(value);
}

template<class _Ty>
inline std::shared_ptr<IDataType> Factory::get_instance(_Ty)
{
	return nullptr;
}
