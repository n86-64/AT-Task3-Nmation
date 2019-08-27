// File - FileReaderBinary.h
// Description - A Binary file reader, used for all binary objects (Shaders etc.)

#pragma once

#include <string>
#include <fstream>

class FileReaderBinary {
public:
	FileReaderBinary() {};
	FileReaderBinary(std::string fileName);
	~FileReaderBinary();

	void setFileName(std::string fileName);
	bool openFile();

	char*  getFileData();
	size_t getFileSize();

private:
	std::string filename;

	char* file = nullptr;
	size_t size = 0;
};