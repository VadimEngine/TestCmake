#include <gtest/gtest.h>
#include "Camera.h"

/**
 * @brief Test that camera is initalized correctly
 */
TEST(CameraTest, Initialization) {
    Camera theCamera;
    glm::vec3 cameraPosition = theCamera.getPosition();
    EXPECT_TRUE(cameraPosition.x == 0);
    EXPECT_TRUE(cameraPosition.y == 0);
    EXPECT_TRUE(cameraPosition.z == 0);
}