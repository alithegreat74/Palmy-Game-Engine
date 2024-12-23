#pragma once
#include "../Event/Event.h"

namespace Palmy {
	class Layer {
	public:
		Layer(const std::string& layerName = "New Layer");
		virtual ~Layer() {

		}

		virtual void OnAttach(){}
		virtual void OnUpdate(){}
		virtual void OnEvent(Event& event){}

	protected:
		std::string m_LayerName;
	};

	
}