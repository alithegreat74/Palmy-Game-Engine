#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec2 aTextureCoordinates;
layout (location = 2) in vec4 aColor;

out vec2 TextureCoordinates;
out vec4 Color;

uniform mat4 uCameraMatrix;
void main()
{
	TextureCoordinates = aTextureCoordinates;
	Color = aColor;
	gl_Position = uCameraMatrix * aPos;
}