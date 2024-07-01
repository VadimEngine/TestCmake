#include "Utils.h"

namespace utils {
    size_t Vec2Hash::operator()(const glm::ivec2& v) const {
        return std::hash<int>()(v.x) ^ std::hash<int>()(v.y);
    }
} // namespace utils
