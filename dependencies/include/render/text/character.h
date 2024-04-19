#ifndef CE_CHARACTER_H
#define CE_CHARACTER_H

#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>

struct Character {
    static std::map<wchar_t, Character> characters;
    
    unsigned int textureID;  // ID handle of the glyph texture
    glm::ivec2 size;         // Size of glyph
    glm::ivec2 bearing;      // Offset from baseline to left/top of glyph
    unsigned int advance;    // Offset to advance to next glyph
};

#endif /* character_h */
