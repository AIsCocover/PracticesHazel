#pragma once

#include "Hazel/Core.h"
#include "Hazel/Window.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/LayerStack.h"

namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);

		LayerStack m_LayerStack;
	};

	// To be defined in actual application class
	Application* CreateApplication();

}

