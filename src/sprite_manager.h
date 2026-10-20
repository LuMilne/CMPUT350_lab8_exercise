#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "sprite.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <filesystem>

using SpriteID = size_t;

class SpriteManager {
public:
    sf::Texture& registerTexture(const std::string& filepath) {
        // Validate filetype
        if( !filepath.ends_with(".png") || !filepath.ends_with(".jpg") ) return;
        std::filesystem::path path = filepath;
        // If path exists and is new, assign
        if ( std::filesystem::exists(path) && !texStore.contains(path) ) {
            sf::Texture tex(path);
            texStore.insert_or_assign(path, tex);
        }
    }

private:
    std::unordered_map<std::filesystem::path, sf::Texture*> texStore;
};

#endif  // SPRITE_MANAGER_H
