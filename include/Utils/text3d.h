/*******************************************************************************
* CGoGN: Combinatorial and Geometric modeling with Generic N-dimensional Maps  *
* version 0.1                                                                  *
* Copyright (C) 2009, IGG Team, LSIIT, University of Strasbourg                *
*                                                                              *
* This library is free software; you can redistribute it and/or modify it      *
* under the terms of the GNU Lesser General Public License as published by the *
* Free Software Foundation; either version 2.1 of the License, or (at your     *
* option) any later version.                                                   *
*                                                                              *
* This library is distributed in the hope that it will be useful, but WITHOUT  *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or        *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License  *
* for more details.                                                            *
*                                                                              *
* You should have received a copy of the GNU Lesser General Public License     *
* along with this library; if not, write to the Free Software Foundation,      *
* Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.           *
*                                                                              *
* Web site: https://iggservis.u-strasbg.fr/CGoGN/                              *
* Contact information: cgogn@unistra.fr                                        *
*                                                                              *
*******************************************************************************/

#ifndef __TEXT_3D__
#define __TEXT_3D__

#include "Utils/GLSLShader.h"
#include "Geometry/vector_gen.h"
#include <IL/ilu.h>
#include <IL/ilut.h>

namespace CGoGN
{
namespace Utils
{

class Strings3D
{
protected:
    static const unsigned int WIDTHFONT = 32;

    static const unsigned int REALWIDTHFONT = 18;

    static const unsigned int WIDTHTEXTURE = 512;

    static const unsigned int HEIGHTTEXTURE = 256;

    static const unsigned int CHARSPERLINE = WIDTHTEXTURE/WIDTHFONT;

    static const unsigned int CHARSPERCOL = HEIGHTTEXTURE/WIDTHFONT;

    ILuint m_imgName;

	std::vector<std::string> m_strings;

	unsigned int m_nbChars;

    std::vector< std::pair<unsigned int, unsigned int> > m_strpos;

    std::vector< Geom::Vec3f > m_strTranslate;

    /**
     * VBO (4f: x,y,u,v)
     */
    GLuint m_vbo1;

    unsigned int sendOneStringToVBO(const std::string& str, float **buffer);


    GLuint m_idTexture;

    GLuint m_uniform_texture;

    GLuint m_uniform_scale;

    GLuint m_uniform_position;

    GLuint m_uniform_color;

    Utils::GLSLShader m_shader;


public:
	Strings3D();

	~Strings3D();

	/**
	 * initialization step
	 * OpenGL context must be opened
	 * @param scale factor for font rendering
	 */
	void init(float scale=1.0f);

	/**
	 * add astring
	 * @param string to add to pool of string
	 * @return the id of string for rendering
	 */
	unsigned int addString(const std::string& str);

	/**
	 * add astring with its position
	 * @param string to add to pool of string
	 * @param pos the position of text
	 * @return the id of string (future use:updating data)
	 */
	unsigned int addString(const std::string& str, const Geom::Vec3f& pos);

	/**
	 * once all string are stored, we must send it to the gracphic card
	 */
	void sendToVBO();

	/**
	 * draw on string
	 * @param idSt the id of string
	 * @param pos the position of text
	 */
	void draw(unsigned int idSt, const Geom::Vec3f& pos);

	/**
	* Draw all text stored with their position
	* @param color the color of text
	*/
	void drawAll(const Geom::Vec3f& color);

	/**
	* call once before several draw(id,pos)
	* @param color the color of text
	*/
	void predraw(const Geom::Vec3f& color);

	/**
	* call once after several draw(id,pos)
	*/
	void postdraw();

	/**
	 * set the scale for font rendering
	 * @param scale
	 */
	void setScale(float scale);

};
}
}
#endif