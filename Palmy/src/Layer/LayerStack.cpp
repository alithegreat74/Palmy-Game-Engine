#include "LayerStack.h"

namespace Palmy {

	void LayerStack::AttachLayer(std::shared_ptr<Layer> layer)
	{
		m_Layers.push_back(layer);
	}

}