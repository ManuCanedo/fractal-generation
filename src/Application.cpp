#include "Application.h"
#include "Log.h"
#include "Bitmap.h"

namespace Fractal
{
	Application::Application() {}
	Application::~Application() {}

	void Application::Run()
	{
		std::string name{ "blackImage.bmp" };

		LOG_TRACE("Application running");
		Fractal::Bitmap image(800, 600);
		LOG_WARN("Bitmap created");
		image.Write(name);
		LOG_INFO("Image generation successful");
		LOG_TRACE("Image saved as {0}", name);
	}

	Application* Application::CreateApplication()
	{
		return new Application;
	}
}