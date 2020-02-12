#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	std::cout << "Welcome to Hazel Engine !!!" << std::endl;
	
	Hazel::Log::Init();
	HZ_TRACE("Initialized Log!");
	int a = 5;
	HZ_INFO("Hello! Var={0}", a);
	HZ_CRIITICAL("Critical!!!");

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif // HZ_PLATFORM_WINDOWS
