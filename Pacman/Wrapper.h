#pragma once
#include <memory>
#include <functional>

template<typename T>
class Wrapper
{
	std::unique_ptr<T, std::function<void(T*)>>_innerObject;
	
public:
	Wrapper() = default;

	Wrapper(std::function<void(T*)>func,T *object=nullptr):_innerObject(object,func) {  }

	T& Get()const;

	void Set(T *t);
};

template <typename T>
T& Wrapper<T>::Get() const
{
	return *_innerObject;
}

template <typename T>
void Wrapper<T>::Set(T *t)
{
	_innerObject.reset(t);
}


