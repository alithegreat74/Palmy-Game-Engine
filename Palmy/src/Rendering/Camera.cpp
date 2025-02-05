#include "pch.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Palmy
{
	Camera::Camera(glm::vec3 front, glm::vec3 position)
		:m_Front(front), m_Position(position),m_Projection(glm::mat4(1.0f)),m_View(glm::mat4(1.0))
	{
		m_View = glm::lookAt(m_Position, m_Position + m_Front, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	glm::mat4 Camera::GetCameraMatrix() const
	{
		return m_Projection * m_View;
	}
	OrthoGraphicCamera::OrthoGraphicCamera(glm::vec3 front, glm::vec3 position, float left, float right, float top, float bottom, float zNear, float zFar)
		:Camera(front,position)
	{
		m_Projection = glm::ortho(left, right, bottom, top, zNear, zFar);
	}
	PerspectiveCamera::PerspectiveCamera(glm::vec3 front, glm::vec3 position, float fov, float aspectRatio, float zNear, float zFar)
		:Camera(front,position)
	{
		m_Projection = glm::perspective(fov, aspectRatio, zNear, zFar);
	}
}