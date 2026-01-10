#include <libdragon.h>
#include <GL/gl.h>
#include "drawer.hpp"

void DebugDrawer::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color) {
    glColor3f(color[0], color[1], color[2]);
    glVertex3f(from[0], from[1], from[2]);

    glColor3f(color[0], color[1], color[2]);
    glVertex3f(to[0], to[1], to[2]);
}

void DebugDrawer::drawContactPoint(const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color) {
    float length = distance * 100.0f;

    glColor3f(color[0], color[1], color[2]);
    glVertex3f(PointOnB[0], PointOnB[1], PointOnB[2]);

    glColor3f(color[0], color[1], color[2]);
    glVertex3f(PointOnB[0] + normalOnB[0] * length, PointOnB[1] + normalOnB[1]* length, PointOnB[2] + normalOnB[2]* length);
}

void DebugDrawer::reportErrorWarning(const char *warningString) {
}

void DebugDrawer::draw3dText(const btVector3 &location, const char *textString) {
}

void DebugDrawer::setDebugMode(int debugMode) {
    mDebugMode = debugMode;
}

int DebugDrawer::getDebugMode() const {
    return mDebugMode;
}




