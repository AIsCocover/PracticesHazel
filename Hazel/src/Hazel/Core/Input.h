#pragma once

#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/MouseCodes.h"

/*
	default和delete关键字
		在C++11中，可以在想要“禁止使用”的特殊成员函数声明后加"= delete;"，而需要保留的加"= default;"或者不采取操作。
		特殊成员函数指的是C++98编译器会隐式产生的四个函数：缺省构造函数、析构函数、拷贝构造函数、拷贝赋值算子，以及C++11中的移动构造函数以及移动赋值算子。
*/
namespace Hazel {
	class Input
	{
	protected:
		Input() = default;
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

	protected:

	private:
		
	};
}