#include <Breach/BreachSL.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

static int WINDOW_WIDTH = 640;
static int WINDOW_HEIGHT = 480;

enum WindowMode {FULLSCREEN, BORDERLESS, WINDOWED};

char TITLE[] = "Breach engine";

static unsigned int CompileShader(unsigned int type, const std::string& source){
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE){
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		
		std::cout<<"Failed to compile "<<(type == GL_VERTEX_SHADER ? "vertex" : "fragment")<<" shader"<<std::endl;
		std::cout<<message<<std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
	glViewport(0,0,width,height);
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
}

int main(){
	GLFWwindow *window;

	WindowMode wMode = WINDOWED;
	
	if(!glfwInit()){
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	if(!monitor){
		std::cout<<"Failed to find primary monitor"<<std::endl;
		return -1;
	}

	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
 
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	if(wMode == FULLSCREEN){
		window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE, monitor, NULL);
	}
	else if(wMode == BORDERLESS){
		window = glfwCreateWindow(mode->width, mode->height, TITLE, monitor, NULL);
	}
	else if(wMode == WINDOWED){
		glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
		window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE, NULL, NULL);
	}

	if(!window){
		std::cout<<"Failed to initialize GLFW"<<std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	//load GLAD
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout<<"Failed to initialize GLAD"<<std::endl;
		return 0;
	}

	glViewport(0,0,WINDOW_WIDTH, WINDOW_HEIGHT);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	std::cout<<glGetString(GL_VERSION)<<std::endl;

	float positions[6] = {
		-0.5f, -0.5f,
		0.0f, 0.5f,
		0.5f, -0.5f
	};

	//vertex array data(VAO)
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//vertex buffer data(VBO)
	//create and bind buffer
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

	glBindVertexArray(0);

	Bshader bshader = BSL::ParseShader("./shader.bsh");


	unsigned int shader = CreateShader(bshader.vertex, bshader.fragment);
	glUseProgram(shader);

	while(!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
