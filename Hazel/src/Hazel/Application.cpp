#include "hzpch.h"
#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"

#include <GLFW/glfw3.h>

/*
	std::bind可以把可调用对象保存起来，在需要时再调用。
	对于普通函数，第一个参数为可调用对象，第二个参数为调用该对象时传入的参数列表。参数列表可以用占位符std::placeholders::_n表示。
		std::placeholders::_1表示使用入参的第一个参数，_2表示使用入参的第二个参数...以此类推。因此可以通过调换_1和_2的位置来控制入参传入的顺序。
	对于类成员函数，第二个参数需要传入类对象本身，然后第三个参数才是参数列表。
*/
#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hazel {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		// 如果m_Window的回调接收到了WindowCloseEvent，则调用OnWindowClose函数。(这里的事件分发器EventDispatcher还有很大的优化空间)
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClose));

		HZ_CORE_TRACE("{0}", e.ToString());
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
