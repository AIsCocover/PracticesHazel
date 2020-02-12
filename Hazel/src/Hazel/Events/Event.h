#pragma once

#include "Hazel/Core.h"

namespace Hazel {
	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

/*
	#：构串操作符 
		构串操作符#只能修饰带参数的宏的形参，它将实参的字符序列（而不是实参代表的值）转换成字符串常量。
		例：
			#define TEST1(x) #x#x#x
			#define TEST2(x) "class"#x"Info"

			int abc = 100;
			TEST1(abc);			-->	abcabcabc
			TEST2(abc);			--> classabcInfo

	##：合并操作符
		合并操作符##将出现在其左右的字符序列合并成一个新的标识符。

		注意：
		使用合并操作符##时，自身的标识符必须预先有定义，否则编译器会报“标识符未定义”的编译错误。
		字符序列合并成新的标识符不是字符串。

		例：
			#define CLASS_NAME(name) class##name
			#define MERGE(x,y) x##y##x

			CLASS_NAME(Timer);			--> classTimer
			MERGE(me,To);					-->	meTome
*/
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
														   virtual EventType GetEventType() const override { return GetStaticType(); }\
														   virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

/*
	1. 成员函数前加const表示函数返回值为const，不可修改；
		成员函数后加const(只有类的非静态成员函数后才可以加const)表示该函数中，本类的this指针为const类型，不能在该函数中改变类的成员变量的值，即成员变量为read only(只读)。
	2. 虚函数初始化为0表示这是一个纯虚函数，需要在派生类中实现才可被调用。
*/
	class Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;			// &运算。若flag跟category相同，则返回值跟flag一致。
		}
	protected:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();		// require #include <string>
	}
}