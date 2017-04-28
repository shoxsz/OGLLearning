#include "dds_loader.hpp"

#include <string>
#include <algorithm>
#include <iostream>

#include <utils\binary_reader.hpp>

#define DDS_MAGIC "DDS"

//  DDS_header.dwFlags
#define DDSD_CAPS                   0x00000001 
#define DDSD_HEIGHT                 0x00000002 
#define DDSD_WIDTH                  0x00000004 
#define DDSD_PITCH                  0x00000008 
#define DDSD_PIXELFORMAT            0x00001000 
#define DDSD_MIPMAPCOUNT            0x00020000 
#define DDSD_LINEARSIZE             0x00080000 
#define DDSD_DEPTH                  0x00800000 

//  DDS_header.sPixelFormat.dwFlags
#define DDPF_ALPHAPIXELS            0x00000001 
#define DDPF_FOURCC                 0x00000004 
#define DDPF_INDEXED                0x00000020 
#define DDPF_RGB                    0x00000040 

//  DDS_header.sCaps.dwCaps1
#define DDSCAPS_COMPLEX             0x00000008 
#define DDSCAPS_TEXTURE             0x00001000 
#define DDSCAPS_MIPMAP              0x00400000 

//  DDS_header.sCaps.dwCaps2
#define DDSCAPS2_CUBEMAP            0x00000200 
#define DDSCAPS2_CUBEMAP_POSITIVEX  0x00000400 
#define DDSCAPS2_CUBEMAP_NEGATIVEX  0x00000800 
#define DDSCAPS2_CUBEMAP_POSITIVEY  0x00001000 
#define DDSCAPS2_CUBEMAP_NEGATIVEY  0x00002000 
#define DDSCAPS2_CUBEMAP_POSITIVEZ  0x00004000 
#define DDSCAPS2_CUBEMAP_NEGATIVEZ  0x00008000 
#define DDSCAPS2_VOLUME             0x00200000 

#define D3DFMT_DXT1     '1TXD'    //  DXT1 compression texture format 
#define D3DFMT_DXT2     '2TXD'    //  DXT2 compression texture format 
#define D3DFMT_DXT3     '3TXD'    //  DXT3 compression texture format 
#define D3DFMT_DXT4     '4TXD'    //  DXT4 compression texture format 
#define D3DFMT_DXT5     '5TXD'    //  DXT5 compression texture format 

#define PF_IS_DXT1(pf) \
  ((pf.dwFlags & DDPF_FOURCC) && \
   (pf.dwFourCC == D3DFMT_DXT1))

#define PF_IS_DXT3(pf) \
  ((pf.dwFlags & DDPF_FOURCC) && \
   (pf.dwFourCC == D3DFMT_DXT3))

#define PF_IS_DXT5(pf) \
  ((pf.dwFlags & DDPF_FOURCC) && \
   (pf.dwFourCC == D3DFMT_DXT5))

#define PF_IS_BGRA8(pf) \
  ((pf.dwFlags & DDPF_RGB) && \
   (pf.dwFlags & DDPF_ALPHAPIXELS) && \
   (pf.dwRGBBitCount == 32) && \
   (pf.dwRBitMask == 0xff0000) && \
   (pf.dwGBitMask == 0xff00) && \
   (pf.dwBBitMask == 0xff) && \
   (pf.dwAlphaBitMask == 0xff000000U))

#define PF_IS_BGR8(pf) \
  ((pf.dwFlags & DDPF_ALPHAPIXELS) && \
  !(pf.dwFlags & DDPF_ALPHAPIXELS) && \
   (pf.dwRGBBitCount == 24) && \
   (pf.dwRBitMask == 0xff0000) && \
   (pf.dwGBitMask == 0xff00) && \
   (pf.dwBBitMask == 0xff))

#define PF_IS_BGR5A1(pf) \
  ((pf.dwFlags & DDPF_RGB) && \
   (pf.dwFlags & DDPF_ALPHAPIXELS) && \
   (pf.dwRGBBitCount == 16) && \
   (pf.dwRBitMask == 0x00007c00) && \
   (pf.dwGBitMask == 0x000003e0) && \
   (pf.dwBBitMask == 0x0000001f) && \
   (pf.dwAlphaBitMask == 0x00008000))

#define PF_IS_BGR565(pf) \
  ((pf.dwFlags & DDPF_RGB) && \
  !(pf.dwFlags & DDPF_ALPHAPIXELS) && \
   (pf.dwRGBBitCount == 16) && \
   (pf.dwRBitMask == 0x0000f800) && \
   (pf.dwGBitMask == 0x000007e0) && \
   (pf.dwBBitMask == 0x0000001f))

#define PF_IS_INDEX8(pf) \
  ((pf.dwFlags & DDPF_INDEXED) && \
   (pf.dwRGBBitCount == 8))


union DDS_header {
	struct {
		unsigned int    dwMagic;
		unsigned int    dwSize;
		unsigned int    dwFlags;
		unsigned int    dwHeight;
		unsigned int    dwWidth;
		unsigned int    dwPitchOrLinearSize;
		unsigned int    dwDepth;
		unsigned int    dwMipMapCount;
		unsigned int    dwReserved1[11];

		//  DDPIXELFORMAT
		struct {
			unsigned int    dwSize;
			unsigned int    dwFlags;
			unsigned int    dwFourCC;
			unsigned int    dwRGBBitCount;
			unsigned int    dwRBitMask;
			unsigned int    dwGBitMask;
			unsigned int    dwBBitMask;
			unsigned int    dwAlphaBitMask;
		}               sPixelFormat;

		//  DDCAPS2
		struct {
			unsigned int    dwCaps1;
			unsigned int    dwCaps2;
			unsigned int    dwDDSX;
			unsigned int    dwReserved;
		}               sCaps;
		unsigned int    dwReserved2;
	};
	char data[128];
};


struct DdsLoadInfo {
	bool compressed;
	bool swap;
	bool palette;
	unsigned int divSize;
	unsigned int blockBytes;
	GLenum internalFormat;
	GLenum externalFormat;
	GLenum type;
};

DdsLoadInfo loadInfoDXT1 = {
	true, false, false, 4, 8, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
};
DdsLoadInfo loadInfoDXT3 = {
	true, false, false, 4, 16, GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
};
DdsLoadInfo loadInfoDXT5 = {
	true, false, false, 4, 16, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
};
DdsLoadInfo loadInfoBGRA8 = {
	false, false, false, 1, 4, GL_RGBA8, GL_BGRA, GL_UNSIGNED_BYTE
};
DdsLoadInfo loadInfoBGR8 = {
	false, false, false, 1, 3, GL_RGB8, GL_BGR, GL_UNSIGNED_BYTE
};
DdsLoadInfo loadInfoBGR5A1 = {
	false, true, false, 1, 2, GL_RGB5_A1, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV
};
DdsLoadInfo loadInfoBGR565 = {
	false, true, false, 1, 2, GL_RGB5, GL_RGB, GL_UNSIGNED_SHORT_5_6_5
};
DdsLoadInfo loadInfoIndex8 = {
	false, false, true, 1, 1, GL_RGB8, GL_BGRA, GL_UNSIGNED_BYTE
};


void assert(bool expression, const std::string& description = "Failed to load file!") {
	if (expression == false) {
		throw std::runtime_error(description);
	}
}

Texture2DPtr DDSLoader::load(const std::string& file){
	DDS_header hdr;
	size_t s = 0;
	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int mipMapCount = 0;
	std::string magic;
	bool hasMipmaps = false;

	Texture2DPtr texture(new Texture2D());

	std::ifstream istream(file);
	assert(istream.is_open(), "Failed to open file: " + file);
	
	BinaryReader reader(istream);

	reader.read(&hdr, sizeof(hdr));

	magic.resize(3);
	magic[0] = ((char*)&hdr.dwMagic)[0];
	magic[1] = ((char*)&hdr.dwMagic)[1];
	magic[2] = ((char*)&hdr.dwMagic)[2];

	assert(magic == DDS_MAGIC);
	assert(hdr.dwSize == 124);
	assert(hdr.dwFlags & DDSD_PIXELFORMAT);
	assert(hdr.dwFlags & DDSD_CAPS);

	unsigned int xSize = hdr.dwWidth;
	unsigned int ySize = hdr.dwHeight;
	assert(!(xSize & (xSize - 1)));
	assert(!(ySize & (ySize - 1)));

	DdsLoadInfo * li;

	if (PF_IS_DXT1(hdr.sPixelFormat)) {
		li = &loadInfoDXT1;
	}
	else if (PF_IS_DXT3(hdr.sPixelFormat)) {
		li = &loadInfoDXT3;
	}
	else if (PF_IS_DXT5(hdr.sPixelFormat)) {
		li = &loadInfoDXT5;
	}
	else if (PF_IS_BGRA8(hdr.sPixelFormat)) {
		li = &loadInfoBGRA8;
	}
	else if (PF_IS_BGR8(hdr.sPixelFormat)) {
		li = &loadInfoBGR8;
	}
	else if (PF_IS_BGR5A1(hdr.sPixelFormat)) {
		li = &loadInfoBGR5A1;
	}
	else if (PF_IS_BGR565(hdr.sPixelFormat)) {
		li = &loadInfoBGR565;
	}
	else if (PF_IS_INDEX8(hdr.sPixelFormat)) {
		li = &loadInfoIndex8;
	}
	else {
		throw std::runtime_error("Undefined pixel format!");
	}

	x = xSize;
	y = ySize;
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);
	mipMapCount = (hdr.dwFlags & DDSD_MIPMAPCOUNT) ? hdr.dwMipMapCount : 1;
	if (mipMapCount > 1) {
		hasMipmaps = true;
	}
	if (li->compressed) {
		size_t size = std::max(li->divSize, x) / li->divSize * std::max(li->divSize, y) / li->divSize * li->blockBytes;
		assert(size == hdr.dwPitchOrLinearSize);
		assert(hdr.dwFlags & DDSD_LINEARSIZE);
		unsigned char* data = new unsigned char[size];
		
		li->internalFormat;
		for (unsigned int ix = 0; ix < mipMapCount; ++ix) {
			reader.read(data, size);
			texture->updatePixelsCompressed(data, Size(x, y), size, (CompressedFormat)li->internalFormat, ix);
			x = (x + 1) >> 1;
			y = (y + 1) >> 1;
			size = std::max(li->divSize, x) / li->divSize * std::max(li->divSize, y) / li->divSize * li->blockBytes;
		}
		delete data;
	}
	/*else if (li->palette) {
		//  currently, we unpack palette into BGRA
		//  I'm not sure we always get pitch...
		assert(hdr.dwFlags & DDSD_PITCH);
		assert(hdr.sPixelFormat.dwRGBBitCount == 8);
		size_t size = hdr.dwPitchOrLinearSize * ySize;
		//  And I'm even less sure we don't get padding on the smaller MIP levels...
		assert(size == x * y * li->blockBytes);
		format = li->externalFormat;
		cFormat = li->internalFormat;
		unsigned char * data = (unsigned char *)malloc(size);
		unsigned int palette[256];
		unsigned int * unpacked = (unsigned int *)malloc(size * sizeof(unsigned int));
		fread(palette, 4, 256, f);
		for (unsigned int ix = 0; ix < mipMapCount; ++ix) {
			fread(data, 1, size, f);
			for (unsigned int zz = 0; zz < size; ++zz) {
				unpacked[zz] = palette[data[zz]];
			}
			glPixelStorei(GL_UNPACK_ROW_LENGTH, y);
			glTexImage2D(GL_TEXTURE_2D, ix, li->internalFormat, x, y, 0, li->externalFormat, li->type, unpacked);
			gl->updateError();
			x = (x + 1) >> 1;
			y = (y + 1) >> 1;
			size = x * y * li->blockBytes;
		}
		free(data);
		free(unpacked);
	}
	else {
		if (li->swap) {
			glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_TRUE);
		}
		size = x * y * li->blockBytes;
		format = li->externalFormat;
		cFormat = li->internalFormat;
		unsigned char * data = (unsigned char *)malloc(size);
		//fixme: how are MIP maps stored for 24-bit if pitch != ySize*3 ?
		for (unsigned int ix = 0; ix < mipMapCount; ++ix) {
			fread(data, 1, size, f);
			glPixelStorei(GL_UNPACK_ROW_LENGTH, y);
			glTexImage2D(GL_TEXTURE_2D, ix, li->internalFormat, x, y, 0, li->externalFormat, li->type, data);
			gl->updateError();
			x = (x + 1) >> 1;
			y = (y + 1) >> 1;
			size = x * y * li->blockBytes;
		}
		free(data);
		glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
		gl->updateError();
	}*/
	texture->mipmapsRange(0, mipMapCount - 1);

	return texture;
}