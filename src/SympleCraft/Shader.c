#include "SympleCraft/Shader.h"

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <gl/glew.h>

Shader CreateShader(const char* vertFile, const char* fragFile)
{
	char* vertexSource;
	char* fragmentSource;

	{
		FILE* fs;
		errno_t err = fopen_s(&fs, vertFile, "rb");
		if (!err && fs)
		{
			fseek(fs, 0, SEEK_END);
			long size = ftell(fs);
			rewind(fs);

			vertexSource = malloc(size + 1);

			fread_s(vertexSource, size, 1, size, fs);
			fclose(fs);
			vertexSource[size] = 0;
		}
		else
		{
			char errMsg[64];
			if (!strerror_s(errMsg, sizeof(errMsg), err))
				fprintf(stderr, "[!]: Error reading Vertex File '%s': %s", vertFile, errMsg);
			return -1;
		}
	}

	{
		FILE* fs;
		errno_t err = fopen_s(&fs, fragFile, "rb");
		if (!err && fs)
		{
			fseek(fs, 0, SEEK_END);
			long size = ftell(fs);
			rewind(fs);

			fragmentSource = malloc(size + 1);

			fread_s(fragmentSource, size, 1, size, fs);
			fclose(fs);
			fragmentSource[size] = 0;
		}
		else
		{
			char errMsg[64];
			if (!strerror_s(errMsg, sizeof(errMsg), err))
				fprintf(stderr, "[!]: Error reading Fragment File '%s': %s", fragFile, errMsg);
			return -1;
		}
	}

	GLuint shader = glCreateProgram();
	{
		GLuint vert, frag;
		vert = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vert, 1, &vertexSource, NULL);
		glCompileShader(vert);
		{
			GLint status;
			glGetShaderiv(vert, GL_COMPILE_STATUS, &status);
			if (!status)
			{
				GLsizei length;
				glGetShaderiv(vert, GL_INFO_LOG_LENGTH, &length);

				GLchar* msg = malloc(length);
				glGetShaderInfoLog(vert, length, &length, msg);
				glDeleteShader(vert);

				fprintf(stderr, "[!]: Failed to compile Vertex Shader: %s\n", msg);
				free(msg);
			}
		}

		frag = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(frag, 1, &fragmentSource, NULL);
		glCompileShader(frag);
		{
			GLint status;
			glGetShaderiv(frag, GL_COMPILE_STATUS, &status);
			if (!status)
			{
				GLsizei length;
				glGetShaderiv(frag, GL_INFO_LOG_LENGTH, &length);

				GLchar* msg = malloc(length);
				glGetShaderInfoLog(frag, length, &length, msg);
				glDeleteShader(frag);

				fprintf(stderr, "[!]: Failed to compile Fragment Shader: %s\n", msg);
				free(msg);
			}
		}

		glAttachShader(shader, vert);
		glAttachShader(shader, frag);

		glLinkProgram(shader);
		glValidateProgram(shader);

		glDeleteShader(vert);
		glDeleteShader(frag);

		free(vertexSource);
		free(fragmentSource);
	}
}

void BindShader(Shader shader)
{
	glUseProgram(shader);
}

void DeleteShader(Shader shader)
{
	glDeleteProgram(shader);
}

int GetUniformLocation(Shader shader, const char* name)
{
	return glGetUniformLocation(shader, name);
}

void SetShaderUniformi(Shader shader, const char* name, int value)
{
	glUniform1i(GetUniformLocation(shader, name), value);
}
void SetShaderUniformf(Shader shader, const char* name, float value)
{
	glUniform1f(GetUniformLocation(shader, name), value);
}
void SetShaderUniformVec(Shader shader, const char* name, Vector vector)
{
	glUniform4f(GetUniformLocation(shader, name), vector->x, vector->y, vector->z, vector->w);
}
void SetShaderUniformMat(Shader shader, const char* name, Matrix matrix)
{
	glUniformMatrix4fv(GetUniformLocation(shader, name), 16, GL_TRUE, matrix);
}