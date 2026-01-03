#pragma once
#include <bullet/btBulletDynamicsCommon.h>

class Physics {
    public:
        Physics() {
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

    private:
        btCollisionConfiguration *collisionConfiguration;
        btDispatcher *dispatcher;
        btBroadphaseInterface *broadphase;
        btConstraintSolver *solver;
        btDynamicsWorld *dynamicsWorld;
        btRigidBody *groundPlaneBody;
};
