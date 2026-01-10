#include <bullet/btBulletDynamicsCommon.h>
#include <t3d/t3dmath.h>
#include "../actors/models/complex.hpp"

namespace bodyForce {

    inline void applyForce(ComplexBody* body) { //, T3DVec3 direction, float amount) {

        btVector3 relativeForce = btVector3(0.0,20,0);
        // btMatrix3x3& boxRot = body->rigidBody->getWorldTransform().getBasis();
        // btVector3 correctedForce = boxRot * relativeForce;
        btTransform boxTrans;
        body->rigidBody->getMotionState()->getWorldTransform(boxTrans);
        btVector3 correctedForce = (boxTrans * relativeForce) - boxTrans.getOrigin();
        body->rigidBody->applyCentralForce(correctedForce);




        //body->rigidBody->applyForce(btVector3(direction.x, direction.y, direction.z), btVector3(amount, amount, amount));
    }

}
