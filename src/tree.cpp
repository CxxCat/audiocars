#include "tree.h"

#include <string>

#include "ofMain.h"

Tree::Tree(const ofVec3f& center, int side, const ofImage& image)
    : position(center)
    , image(image) {
    float rnd = ofRandomf();
    position.x = (kOffset + rnd * kRange) * side;
    width += rnd;
}

float Tree::order() {
    return position.z;
}

void Tree::draw(const Camera& camera) {
    ofVec2f scrSize = camera.scaleByWidth(position, width, image);

    auto scrPosition = camera.worldToScreen(position);
    ofSetColor(ofColor(255, 255, 255, 255 * camera.alpha(order())));
    image.draw(
        scrPosition.x - scrSize.x / 2,
        scrPosition.y - scrSize.y,
        scrSize.x,
        scrSize.y
    );
}
