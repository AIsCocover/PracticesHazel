#include "Application.h"
#include <iostream>

namespace Hazel {

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		//while (true);
		printf("PRESS ENTER TO EXIT PROGRAM...");
		while (getchar() != '\n');
	}

}
