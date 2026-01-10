#pragma once
#include <bullet/btBulletDynamicsCommon.h>
#include "drawer.hpp"

#define USE_PHYSICS_DEBUG_DRAW 1

class Physics {
    public:
        Physics(DebugDrawer& drawer): _drawer(drawer) {
            setupPhysics();
        }
        ~Physics();
        void setupPhysics();
        void setGravity(btVector3 gravity);
        btRigidBody* createCubeRigidBody(float startingPosition[3], float size[3], float mass);
        void stepSimulation(float deltaTime = 30.0f);
        btVector3 getRigidBodyPosition(btRigidBody *rigidBody);
        btQuaternion getRigidBodyRotation(btRigidBody *rigidBody);
        void setRigidBodyRotation(btRigidBody *rigidBody, float rotation[3]);
        void createGroundRigidBody();
        void applyForce(btRigidBody *rigidBody);

    private:
        btCollisionConfiguration *collisionConfiguration;
        btDispatcher *dispatcher;
        btBroadphaseInterface *broadphase;
        btConstraintSolver *solver;
        btDynamicsWorld *dynamicsWorld;
        btRigidBody *groundPlaneBody;

        DebugDrawer& _drawer;
};
