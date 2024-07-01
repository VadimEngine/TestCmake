#pragma once
#include <glm/vec2.hpp>

namespace utils {
    /** Hash for glm::ivec2 */
    struct Vec2Hash {
        size_t operator()(const glm::ivec2& v) const;
    };
} // namespace utils
