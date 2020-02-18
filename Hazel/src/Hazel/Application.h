#pragma once

#include "Core.h"
#include "Window.h"
#include "Hazel/Events/ApplicationEvent.h"

namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
	};

	// To be defined in actual application class
	Application* CreateApplication();

}

