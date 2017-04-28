#ifndef _BINARY_READER_HPP_
#define _BINARY_READER_HPP_

#include <fstream>
#include <vector>

class BinaryReader {
public:
	BinaryReader(std::ifstream& io) :io(io) {}

	std::string getString(size_t size)
	{
		std::vector<char> buf(size);
		io.read(&buf[0], size);
		return std::string(buf.begin(), buf.end());
	}

	void read(void *p, size_t size)
	{
		io.read((char*)p, size);
	}

	template<typename T>
	T get()
	{
		T buf;
		io.read((char*)&buf, sizeof(T));
		return buf;
	}
private:
	std::ifstream& io;
};

#endif