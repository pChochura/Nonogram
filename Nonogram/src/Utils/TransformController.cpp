#include "TransformController.h"

void TransformController::setPos(Vector pos) { 
    this->pos = pos;
}

void TransformController::setScale(Vector scale) { 
    this->scale = scale; 
}

void TransformController::translateTo(Vector offset) {
    this->pos = offset;
}

void TransformController::translateBy(Vector offset) {
    this->pos += offset;
}

void TransformController::scaleTo(Vector scale, Vector origin = { 0, 0 }) {
    Vector scaleDiff = this->scale - scale;
    Vector temp = scaleDiff * origin;
    this->pos -= temp;

    this->scale = scale;
}

void TransformController::scaleBy(Vector scale, Vector origin = { 0, 0 }) {
    Vector temp = scale * origin;
    this->pos -= temp;

    this->scale += scale;
}