#pragma once
#include <glm.hpp>
namespace Palmy
{
	class Camera {
	public:
		Camera(glm::vec3 front, glm::vec3 position);
		virtual ~Camera(){}
		glm::mat4 GetCameraMatrix()const;
	protected:
		glm::mat4 m_Projection;
		glm::mat4 m_View;
		glm::vec3 m_Front;
		glm::vec3 m_Position;
	};
	class OrthoGraphicCamera :public Camera {
	public:
		OrthoGraphicCamera(glm::vec3 front, glm::vec3 position, float left, float right, float top, float bottom, float zNear, float zFar);
	};
	class PerspectiveCamera :public Camera {
	public:
		PerspectiveCamera(glm::vec3 front, glm::vec3 position,float fov, float aspectRatio, float zNear,float zFar);
	};
}