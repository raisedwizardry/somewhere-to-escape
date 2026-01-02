#include <math.h>
#include <algorithm>
#include <bullet/btBulletDynamicsCommon.h>
#include "physics.hpp"

#include "drawer.hpp"

Physics::~Physics() {
    delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
}

void Physics::setupPhysics() {
    btDefaultCollisionConstructionInfo constructionInfo;
    constructionInfo.m_defaultMaxCollisionAlgorithmPoolSize = 512;
    constructionInfo.m_defaultMaxPersistentManifoldPoolSize = 512;

    collisionConfiguration = new btDefaultCollisionConfiguration(constructionInfo);
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    broadphase = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	setGravity(btVector3(0.0f, -9.8f, 0.0f));
}

void Physics::stepSimulation(float deltaTime) {
    dynamicsWorld->stepSimulation(1.f / deltaTime, 10);
}

void Physics::setGravity(btVector3 gravity) {
    dynamicsWorld->setGravity(gravity);
}

void Physics::createGroundRigidBody() {
    btCollisionShape *groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);

    btDefaultMotionState *groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

    btScalar mass = 0;
    btVector3 groundInertia(0, 0, 0);
    groundShape->calculateLocalInertia(mass, groundInertia);

    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(mass, groundMotionState, groundShape, groundInertia);
    groundPlaneBody = new btRigidBody(groundRigidBodyCI);
    groundPlaneBody->setRestitution(1.0f);
    groundPlaneBody->setCollisionFlags(groundPlaneBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    groundPlaneBody->setActivationState(DISABLE_DEACTIVATION);

    dynamicsWorld->addRigidBody(groundPlaneBody);
}

btRigidBody* Physics::createCubeRigidBody(float startingPosition[3], float size[3], float mass) {
    btBoxShape *boxShape = new btBoxShape(btVector3(size[0], size[1], size[2]));

    btDefaultMotionState *cubeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(startingPosition[0], startingPosition[1], startingPosition[2])));

    btScalar massToUse(mass);
    btVector3 cubeInertia(0, 0, 0);
    boxShape->calculateLocalInertia(massToUse, cubeInertia);
    btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI(mass, cubeMotionState, boxShape, cubeInertia);

    btRigidBody *body = new btRigidBody(cubeRigidBodyCI);
    dynamicsWorld->addRigidBody(body);
    body->setRestitution(0.3f);
    body->setFriction(0.5f);
    body->applyTorque(btVector3(0, 0, 0));

    body->setAngularVelocity(btVector3(0, 0, 0));
    return body;
}

btVector3 Physics::getRigidBodyPosition(btRigidBody *rigidBody) {
    btTransform trans;
    rigidBody->getMotionState()->getWorldTransform(trans);

    btVector3 pos = trans.getOrigin();

    return pos;
}

btQuaternion Physics::getRigidBodyRotation(btRigidBody *rigidBody) {
    btTransform trans;

    rigidBody->getMotionState()->getWorldTransform(trans);

    btQuaternion rot = trans.getRotation();

    return rot;
}

void Physics::setRigidBodyRotation(btRigidBody *rigidBody, float rotation[3]) {
    btTransform trans;
    btQuaternion deltaLocalRotation(rotation[0], rotation[1], rotation[2]);
    btQuaternion oldBodyRotation = rigidBody->getWorldTransform().getRotation();
    btQuaternion newBodyRotation = oldBodyRotation * deltaLocalRotation;
    trans.setRotation(newBodyRotation);

    rigidBody->getMotionState()->setWorldTransform(trans);
}
