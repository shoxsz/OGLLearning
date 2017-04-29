#ifndef _SKN_LOADER_HPP_
#define _SKN_LOADER_HPP_

#include "3d_model.hpp"

/*implementar um leitor de arquivos .skn usados para em league of legends
	referências: https://github.com/lispascal/lolblender/wiki/File-Formats
*/

class SKNLoader {
public:
	void load(const std::string& file, std::vector<ModelPtr>& models);
private:
};

#endif