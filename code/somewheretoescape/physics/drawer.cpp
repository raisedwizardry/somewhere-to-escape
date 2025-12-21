#include <rdpq_mode.h>
#include <rdpq_tri.h>
#include <bullet/btBulletDynamicsCommon.h>
#include "drawer.hpp"

void DebugDrawer::drawContactPoint(const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance,
    int lifeTime, const btVector3 &color) {
}

void DebugDrawer::reportErrorWarning(const char *warningString) {
}

void DebugDrawer::draw3dText(const btVector3 &location, const char *textString) {
}

void DebugDrawer::setDebugMode(int debugMode) {
}

int DebugDrawer::getDebugMode() const {
    return 0;
}

void DebugDrawer::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color) {

    // Reset to standard rendering mode.
    rdpq_set_mode_standard();

    // Configure the combiner for flat-color rendering
    rdpq_mode_combiner(RDPQ_COMBINER_FLAT);
    rdpq_mode_zbuf(true, true);
    // Configure the flat color
    rdpq_set_prim_color(RGBA32(0, 255, 0, 255));

    // Draw the triangle
    float v1[] = { from.getX(), from.getY(), from.getZ() };
    float v2[] = { from.getX(), from.getY(), from.getZ() };
    float v3[] = { to.getX(), to.getY(), to.getZ() };
    rdpq_triangle(&TRIFMT_ZBUF, v1, v2, v3);
}


