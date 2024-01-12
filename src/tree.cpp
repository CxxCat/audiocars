#include "tree.h"

#include <string>

Tree::Tree(const ofVec3f position, const ofImage& image)
    : position(position)
    , image(image) {
}

float Tree::order() {
    return position.z;
}

void Tree::draw(const Camera& camera) {
    ofVec2f scrSize = camera.scaleByWidth(position, kWidth, image);

    auto scrPosition = camera.worldToScreen(position);
    ofSetColor(ofColor::white);
    image.draw(
        scrPosition.x - scrSize.x / 2,
        scrPosition.y - scrSize.y,
        scrSize.x,
        scrSize.y
    );
}
