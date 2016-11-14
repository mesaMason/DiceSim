#include "WeightedDie.h"

#include "btBulletDynamicsCommon.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btAlignedObjectArray.h"
#include "../../../bullet3-2.85.1/examples/CommonInterfaces/CommonRigidBodyBase.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define BOOT_Z_DEPTH 5
#define PLANE_X_WIDTH 2

struct WeightedDie : public CommonRigidBodyBase {
    WeightedDie(struct GUIHelperInterface* helper):CommonRigidBodyBase(helper) {}
    virtual ~WeightedDie(){}
    virtual void initPhysics();
    virtual void renderScene();
    void resetCamera() {
        float dist = 41;
        float pitch = 0;
        float yaw = 0;
        float targetPos[3]={0, 30, 0};
        m_guiHelper->resetCamera(dist, pitch, yaw, targetPos[0], targetPos[1], targetPos[2]);
    }
};

void WeightedDie::initPhysics() {
    // set Y axis as up and use CommonRigiBodyBase's create world
    m_guiHelper->setUpAxis(1);
    createEmptyDynamicsWorld();

    // define physics debug drawer
    m_guiHelper->createPhysicsDebugDrawer(m_dynamicsWorld);
    if (m_dynamicsWorld->getDebugDrawer()) {
        m_dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe+btIDebugDraw::DBG_DrawContactPoints);
    }

    // define ground shape to act as floor
    btBoxShape* groundShape = createBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
    m_collisionShapes.push_back(groundShape);

    // provide default orientation and position of ground
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(btScalar(0), btScalar(-50), btScalar(0)));

    // create the ground
    {
        btScalar mass(0.);
        createRigidBody(mass, groundTransform, groundShape, btVector4(btScalar(0), btScalar(0), btScalar(1), btScalar(1)));
    }
    
    // create a box shape (the die)
    {
        btBoxShape* colShape = createBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5)));
        m_collisionShapes.push_back(colShape);
        btTransform startTransform;
        btScalar mass(1.f);
        btQuaternion startQuaternion(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0)), btScalar(2));
        startTransform.setRotation(startQuaternion);
        startTransform.setOrigin(btVector3(btScalar(0), btScalar(50), btScalar(0)));
        createRigidBody(mass, startTransform, colShape);
    }

    // create the first plane (really thin box) for box to bounce off of
    btBoxShape* obstacleBox1 = createBoxShape(btVector3(btScalar(PLANE_X_WIDTH), btScalar(0.01), btScalar(BOOT_Z_DEPTH)));
    m_collisionShapes.push_back(obstacleBox1);
    btTransform obstacleBoxTransform;
    btQuaternion obstacleBoxQuaternion(btVector3(btScalar(0), btScalar(0), btScalar(1)), btScalar(M_PI/4));
    obstacleBoxTransform.setRotation(obstacleBoxQuaternion);
    obstacleBoxTransform.setOrigin(btVector3(btScalar(PLANE_X_WIDTH/2), btScalar(30), btScalar(0)));
    {
        btScalar mass(0.);
        createRigidBody(mass, obstacleBoxTransform, obstacleBox1);
    }

    // 2nd plane
    btBoxShape* obstacleBox2 = createBoxShape(btVector3(btScalar(PLANE_X_WIDTH), btScalar(0.01), btScalar(BOOT_Z_DEPTH)));
    m_collisionShapes.push_back(obstacleBox2);
    btQuaternion obstacleBox2Quaternion(btVector3(btScalar(0), btScalar(0), btScalar(1)), btScalar(-M_PI/4));
    obstacleBoxTransform.setRotation(obstacleBox2Quaternion);
    obstacleBoxTransform.setOrigin(btVector3(btScalar(-PLANE_X_WIDTH/2), btScalar(25), btScalar(0)));
    {
        btScalar mass(0.);
        createRigidBody(mass, obstacleBoxTransform, obstacleBox2);
    }

    // 3rd plane
    btBoxShape* obstacleBox3 = createBoxShape(btVector3(btScalar(PLANE_X_WIDTH), btScalar(0.01), btScalar(BOOT_Z_DEPTH)));
    m_collisionShapes.push_back(obstacleBox3);
    obstacleBoxTransform.setRotation(obstacleBoxQuaternion);
    obstacleBoxTransform.setOrigin(btVector3(btScalar(PLANE_X_WIDTH/2), btScalar(20), btScalar(0)));
    {
        btScalar mass(0.);
        createRigidBody(mass, obstacleBoxTransform, obstacleBox3);
    }

    // 4th plane
    btBoxShape* obstacleBox4 = createBoxShape(btVector3(btScalar(PLANE_X_WIDTH), btScalar(0.01), btScalar(BOOT_Z_DEPTH)));
    m_collisionShapes.push_back(obstacleBox4);
    obstacleBoxTransform.setRotation(obstacleBox2Quaternion);
    obstacleBoxTransform.setOrigin(btVector3(btScalar(-PLANE_X_WIDTH/2), btScalar(15), btScalar(0)));
    {
        btScalar mass(0.);
        createRigidBody(mass, obstacleBoxTransform, obstacleBox4);
    }

    // 5th plane
    btBoxShape* obstacleBox5 = createBoxShape(btVector3(btScalar(PLANE_X_WIDTH), btScalar(0.01), btScalar(BOOT_Z_DEPTH)));
    m_collisionShapes.push_back(obstacleBox5);
    obstacleBoxTransform.setRotation(obstacleBoxQuaternion);
    obstacleBoxTransform.setOrigin(btVector3(btScalar(PLANE_X_WIDTH/2), btScalar(10), btScalar(0)));
    {
        btScalar mass(0.);
        createRigidBody(mass, obstacleBoxTransform, obstacleBox5);
    }

    // 6th plane
    btBoxShape* obstacleBox6 = createBoxShape(btVector3(btScalar(PLANE_X_WIDTH), btScalar(0.01), btScalar(BOOT_Z_DEPTH)));
    m_collisionShapes.push_back(obstacleBox6);
    obstacleBoxTransform.setRotation(obstacleBox2Quaternion);
    obstacleBoxTransform.setOrigin(btVector3(btScalar(-PLANE_X_WIDTH/2), btScalar(5), btScalar(0)));
    {
        btScalar mass(0.);
        createRigidBody(mass, obstacleBoxTransform, obstacleBox6);
    }
    
    // wall of the "boot"
    btBoxShape* wall1 = createBoxShape(btVector3(btScalar(0.01), btScalar(40), btScalar(BOOT_Z_DEPTH)));
    btTransform wallTransform;
    wallTransform.setIdentity();
    wallTransform.setOrigin(btVector3(btScalar(-2.5), btScalar(40), btScalar(0)));
    {
        btScalar mass(0.);
        createRigidBody(mass, wallTransform, wall1);
        m_collisionShapes.push_back(wall1);
    }

    // 2nd wall of the "boot" - the front one that is open at the bottom
    btBoxShape* wall2 = createBoxShape(btVector3(btScalar(0.01), btScalar(40), btScalar(BOOT_Z_DEPTH)));
    wallTransform.setOrigin(btVector3(btScalar(2.5), btScalar(45), btScalar(0)));
    {
        btScalar mass(0.);
        createRigidBody(mass, wallTransform, wall2);
        m_collisionShapes.push_back(wall2);
    }
        
    // generate objects in GUI
    m_guiHelper->autogenerateGraphicsObjects(m_dynamicsWorld);
}

void WeightedDie::renderScene() {
    CommonRigidBodyBase::renderScene();
}

CommonExampleInterface* WeightedDieCreateFunc(CommonExampleOptions& options) {
    return new WeightedDie(options.m_guiHelper);
}

