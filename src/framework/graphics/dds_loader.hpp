#ifndef _DDS_LOADER_HPP_
#define _DDS_LOADER_HPP_

#include <graphics\texture.hpp>

#include <memory>
#include <vector>
#include <fstream>

/*o código em "dds_loader.cpp" foi adaptado de: 
	http://www.mindcontrol.org/~hplus/graphics/dds-info/MyDDS.cpp
	e
	http://www.mindcontrol.org/~hplus/graphics/dds-info/MyDDS.h

	mais fontes: 
	https://msdn.microsoft.com/pt-br/library/windows/desktop/bb943991(v=vs.85).aspx
*/

class DDSLoader {
public:
	Texture2DPtr load(const std::string& file);
};

#endif