#include "FileReaderBinary.h"

FileReaderBinary::FileReaderBinary(std::string fileName)
	:filename(fileName)
{
}

FileReaderBinary::~FileReaderBinary()
{
	if (file) 
	{
		delete[] file;
		file = nullptr;
	}
}

void FileReaderBinary::setFileName(std::string fileName)
{
	filename = fileName;
}

bool FileReaderBinary::openFile()
{
	std::fstream  fileHandle = std::fstream(filename, std::ios::in | std::ios::binary);

	if (!fileHandle.fail()) 
	{
		// get the file size
		fileHandle.seekg(0, fileHandle.end);
		size = fileHandle.tellg();

		fileHandle.seekg(0, fileHandle.beg);

		if (file) 
		{
			delete[] file;
			file = nullptr;
		}

		file = new char[size];
		fileHandle.read(file, size); // Read the data into the buffer

		return true;
	}
	else
	{
		return false;
	}

}

char* FileReaderBinary::getFileData()
{
	return file;
}

size_t FileReaderBinary::getFileSize()
{
	return size;
}
