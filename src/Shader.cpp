#include "GameEngine/Shader.h"

static string parseShader(string fileName) {
	ifstream file(fileName.c_str());
	string shaderStr = "";
	string line = "";

	if (file.is_open()) {
		while (getline(file, line)) {
			shaderStr += line;
			shaderStr += '\n';
			//cout << line << '\n';
		}
		file.close();
	} else {
		cout << "unable to open file " << fileName << endl;
	}

	return shaderStr;
}

Shader::Shader(string vertexFile, string fragmentFile) {

	string vs = parseShader(vertexFile);
	string fs = parseShader(fragmentFile);

	const GLchar* vertexShaderSource = vs.c_str();
	const GLchar* fragmentShaderSource = fs.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog
				<< std::endl;
	}

	
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog
				<< std::endl;
	}
	
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog
				<< std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

Shader::~Shader() {
	glDeleteProgram(program);
}

