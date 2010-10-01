///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-27
// Updated : 2010-09-27
// Licence : This source is under MIT License
// File    : gli/gtx/gl_texture_2d.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_GTX_GL_TEXTURE_2D_INCLUDED
#define GLI_GTX_GL_TEXTURE_2D_INCLUDED

#include "../gli.hpp"

#ifndef GL_VERSION_1_1
#error "ERROR: OpenGL must be included before GLI_GTX_gl_texture2d"
#endif//GL_VERSION_1_1

namespace gli{
namespace gtx{
namespace gl_texture_2d
{
	GLuint createTexture2D(std::string const & Filename);
}//namespace gl_texture_2d
}//namespace gtx
}//namespace gli

namespace gli{using namespace gtx::gl_texture_2d;}

#include "gl_texture_2d.inl"

#endif//GLI_GTX_GL_TEXTURE_2D_INCLUDED