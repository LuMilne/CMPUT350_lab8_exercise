#ifndef BASIC_TRANSFORM_H
#define BASIC_TRANSFORM_H

#include <cassert>

#include "vector_util.h"
#include <SFML/System/Vector2.hpp>

struct BasicTransform {
    // compose(f, g) is equivalent to first applying g, then applying f.
    static BasicTransform compose(const BasicTransform& f, const BasicTransform& g) {
        return BasicTransform(
            f.scale*g.scale,
            f.translation * g.scale + g.translation
        );
    };
    /*
        point p = (3,4)
        BasicTransform f = scale:(1,2), translation:(-4,0)
        BasicTransform g = scale:(-1,-1), translation:(6,6)
        q = f.applyPoint(p) ( q = (3*1-4,4*2) = (-1,8) )
        r = g.applyPoint(q) ( r = (-1*-1+6,8*-1+6) = (7,-2) )
        h.applyPoint(3,4) == (7,-2)
            r.x = (3*1-4)*-1+6
                = 3*-1+4+6
            h.scale = q.scale*r.scale
            h.translation = q.translation*r.scale + r.translation
    */

    static BasicTransform inverse(const BasicTransform& f) {
        return BasicTransform(
            {1/f.scale.x, 1/f.scale.y},
            {-f.translation.x/f.scale.x, -f.translation.y/f.scale.y}
        );
    };
    /* 
        f(x) = sx + t
            x' = sx + t
            x = (x' - t) / s
            x = (1/s)x' - t/s
    */

    constexpr BasicTransform(const sf::Vector2f& scale = {1.f, 1.f},
                             const sf::Vector2f& translation = {0.f, 0.f})
        : scale{scale}, translation{translation} {}

    constexpr sf::Vector2f applyPoint(const sf::Vector2f& p) const {
        // first scale, then translate -- if you do the reverse, the translation gets messed up.
        return {p.x * scale.x + translation.x, p.y * scale.y + translation.y};
    }

    constexpr sf::Vector2f applyVector(const sf::Vector2f& p) const {
        // vectors are not translated by transformations
        return {p.x * scale.x, p.y * scale.y};
    }

    constexpr bool operator==(const BasicTransform& other) const {
        return scale == other.scale && translation == other.translation;
    }

    sf::Vector2f scale;
    sf::Vector2f translation;
};

#endif