#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTextureCoordinates;

out vec2 TextureCoordinates;

uniform mat4 uCameraMatrix;

void main()
{
	TextureCoordinates = aTextureCoordinates;
	gl_Position = uCameraMatrix * vec4(aPos,0.0, 1.0);
}