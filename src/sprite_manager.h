#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "sprite.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <filesystem>
#include <stdexcept>

using SpriteID = size_t;

class SpriteManager {
public:
    sf::Texture& registerTexture(const std::string& filepath) {
        // Validate filetype
        if( !filepath.ends_with(".png") && !filepath.ends_with(".jpg") ) {
            throw std::invalid_argument("Invalid file format in file path");
        }
        std::filesystem::path path = filepath;
        // If path exists and is new, assign
        if ( std::filesystem::exists(path) && !texStore.contains(path) ) {
            sf::Texture tex(path);
            auto [it, flag] = texStore.insert_or_assign(path, tex);
            return it->second;
        }
    }

    template <typename... Args> SpriteID createSprite(Args&&... args) {
        Sprite sprite(args...);
        spriteStore.insert_or_assign(++storeSize, sprite);
        return storeSize;
    }

    Sprite& getSprite(SpriteID id) {
        if( spriteStore.contains(id) ) {
            return spriteStore.find(id)->second;
        }
    }

private:
    std::unordered_map<std::filesystem::path, sf::Texture> texStore;
    std::unordered_map<SpriteID, Sprite> spriteStore;
    SpriteID storeSize = 0;
};

#endif  // SPRITE_MANAGER_H
