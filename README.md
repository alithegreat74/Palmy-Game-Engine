
# Palmy
Palmy is a 2D game engine currently implemented with OpenGl


## How to build the project

This project is configured in cmake so try to build with your cmake GUI or run

NOTE: This project was tested and built with windows, so I can't garantee a smooth operation on other operating systems
```bash
  mkdir build
  cd build
  cmake ..
```

Alternatively you can run the batch files in the scripts folder for windows

### For Visual studio
```bash
    Scripts/Generate_MSVC_Release.bat
```
### For make files
```bash
    Scripts/Generate_Makefile_Release.bat
```
Both of these files are release builds so for debug builds you have to run your own commands


## Implemented Features

- Window Creation
- Quad Rendering
- Camera Controlling
- Resource managing
- Hot reloading
- Batch Rendering
- Texture atlas support
## How to use
You need another project that includes and links the Engine project located in the Palmy directory. As an example I created a sandbox project that creates a flappy bird game which could act as a good reference.


### How to create a new application
In your project you have to include the EntryPoint.h file from the engine project in your main project file.
here is what a normal main file project looks like

```
class ExampleLayer :public Palmy::Layer {}
class SandboxApp :public Palmy::Application {
public:
	SandboxApp() :
		Palmy::Application("Sandbox")
	{
		AttachLayer(std::make_shared<ExampleLayer>("Example Layer"));
	}
};
Palmy::Application* Palmy::Create() {

	return new Sandbox::SandboxApp();
}
```
you need to do three things create a class that inherits from the Palmy::Application and another class that inherits from Palmy::Layer and attach that layer class in your application class' constructor. and also define the Palmy::Create function in your code and make it return a heap allocated instance of your application class.

### How to use the resource manager
The resource manager class creates a .meta file for each file and folder in the assets folder which allocate a unique id to all of them. you can get each file from the resource manger by putting the id as a parameter like this:
```
std::shared_ptr<Palmy::Texture2D> backgroundTexture = Palmy::ResourceManager::GetTexture2D(1589568186);
```

### Enable or disable the hot reload feature
Allthough the hot reload feature is really cool it takes a lot of cpu so if you're just making a game with this engine, disable it because you're not editing anything. This feature is made for when we have an editor.

to enable this feature just go to AssetMetaGenerator.cpp file and it the start of the file add
```
#define ENGINE_MODE
```
It is obvious that to disable this feature just remove this line
## Thirdparty Libraries

 - GLFW (Context Creation)
 - GLAD (OpenGL functions)
 - ImGUI (Currently it's used for debugging)
 - stb_image (for Texture Loading)
 - GLM (Linear algebra library)
 - spdlog (Logging library)
 - yaml-cpp (writing yaml files)


## Where is this project headed
The next big thing we're gonna do is create an editor for the project. Then after that I'm gonna create as many games as I can, so I understand what this engine needs. This project will probably stay a 2D engine, and I currently have no plans of creating a 3D engine. So that's why we're gonna stick with opengl, and not have any other graphics api