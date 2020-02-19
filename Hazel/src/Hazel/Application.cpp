#include "hzpch.h"
#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"

#include <glad/glad.h>

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
			
			for (Layer* layer : m_LayerStack)	// ����Ⱦ��ǰ��layer������Ⱦ�����layer������Ⱦ��layer�Ḳ������Ⱦ��layer��
			{
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		// ���m_Window�Ļص����յ���WindowCloseEvent�������OnWindowClose������(������¼��ַ���EventDispatcher���кܴ���Ż��ռ�)
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClose));

		HZ_CORE_TRACE("{0}", e.ToString());

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)	// �Ӻ���ǰִ�лص�������ִ�������Ļ��layer�Ļص���
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}
}
