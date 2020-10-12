#pragma once

#include <imgui.h>

namespace Fractal
{
	class ImGuiLayer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnUpdate();
		void OnEvent(Event& event);

	private:
		inline void DefineApplicationUI();
		inline void Init();
		inline void Shutdown();
	};
}