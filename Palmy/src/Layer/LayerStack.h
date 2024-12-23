#pragma once
#include <vector>
#include "Layer.h"
#include <memory>
namespace Palmy {
	class LayerStack {
	public:
		LayerStack():
			m_Layers(0){}

		void AttachLayer(std::shared_ptr<Layer> layer);
		inline std::vector<std::shared_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
		inline std::vector<std::shared_ptr<Layer>>::iterator end() { return m_Layers.end(); }
		inline std::vector<std::shared_ptr<Layer>>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		inline std::vector<std::shared_ptr<Layer>>::reverse_iterator rend() { return m_Layers.rend(); }

	private:
		std::vector<std::shared_ptr<Layer>> m_Layers;
	};
}