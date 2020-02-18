#include "hzpch.h"
#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"

#include <GLFW/glfw3.h>

/*
	std::bind���԰ѿɵ��ö��󱣴�����������Ҫʱ�ٵ��á�
	������ͨ��������һ������Ϊ�ɵ��ö��󣬵ڶ�������Ϊ���øö���ʱ����Ĳ����б������б������ռλ��std::placeholders::_n��ʾ��
		std::placeholders::_1��ʾʹ����εĵ�һ��������_2��ʾʹ����εĵڶ�������...�Դ����ơ���˿���ͨ������_1��_2��λ����������δ����˳��
	�������Ա�������ڶ���������Ҫ�����������Ȼ��������������ǲ����б�
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
		// ���m_Window�Ļص����յ���WindowCloseEvent�������OnWindowClose������(������¼��ַ���EventDispatcher���кܴ���Ż��ռ�)
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
