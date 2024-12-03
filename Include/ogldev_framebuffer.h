/*
        Copyright 2023 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <GL/glew.h>

#include "ogldev_save_viewport.h"

class Framebuffer {

public:
    Framebuffer();

    ~Framebuffer();

    void Init(int Width, int Height);

    void BindForWriting();

    void UnbindWriting();

    void BindForReading(GLenum TextureUnit);

    void BindDepthForReading(GLenum TextureUnit);

    GLuint GetTexture() const { return m_textureBuffer; }

    GLuint GetDepthTexture() const { return m_depthBuffer; }

private:
    int m_width = 0;
    int m_height = 0;
    GLuint m_fbo = -1;
    GLuint m_textureBuffer = -1;
    GLuint m_depthBuffer = -1;
    SaveViewport m_saveViewport;
};
