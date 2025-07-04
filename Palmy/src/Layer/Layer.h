#pragma once
#include "../Event/Event.h"
#include "../Rendering/Renderer2D.h"
namespace Palmy {
	class Layer {
	public:
		Layer(const std::string& layerName = "New Layer");
		virtual ~Layer() {

		}
		virtual void OnAttach(std::shared_ptr<Renderer2D> renderer)
		{
			m_Renderer = renderer;
		}
		virtual void OnUpdate(){}
		virtual void OnEvent(Event& event){}

	protected:
		std::shared_ptr<Renderer2D> m_Renderer;
		std::string m_LayerName;
	};

	
}