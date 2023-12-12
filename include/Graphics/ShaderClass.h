#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader {
private:
	void compileErrors(unsigned int shader, const char* type);
public :
	GLuint ID;
	/// <summary>
	/// throws an error if file not found
	/// </summary>
	/// <param name="vertexFile">.vert</param>
	/// <param name="fragmentFile">.frag</param>
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate()const;
	void Delete() const;
};


#endif