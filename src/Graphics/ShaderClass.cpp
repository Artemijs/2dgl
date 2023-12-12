#include "Graphics/ShaderClass.h"

std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return (contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragFile) {
	std::string vertCode = get_file_contents(vertexFile);
	std::string fragCode = get_file_contents(fragFile);

	const char* vertSrc = vertCode.c_str();
	const char* fragSrc = fragCode.c_str();

	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertSrc, NULL);
	glCompileShader(vertShader);
	compileErrors(vertShader, "VERTEX");

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragSrc, NULL);
	glCompileShader(fragShader);
	compileErrors(fragShader, "FRAGMENT");

	ID = glCreateProgram();;
	glAttachShader(ID, vertShader);
	glAttachShader(ID, fragShader);
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

}
void Shader::Activate() const {
	glUseProgram(ID);
}

void Shader::Delete() const {
	glDeleteProgram(ID);
}
void Shader::compileErrors(unsigned int shader, const char* type) {
	GLint hasComppiled;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasComppiled);
		if (hasComppiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n"<<std::endl;	
			std::cout << infoLog << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasComppiled);
		if (hasComppiled == GL_FALSE) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
			std::cout << infoLog << std::endl;
		}
	}
	
}