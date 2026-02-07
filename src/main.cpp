#include "BaseApp.hpp"
#include <iostream>

class Example : public BaseApp {
    protected:
        void createScene() override
        {
            mScnMgr->setAmbientLight(Ogre::ColourValue(1.0F, 1.0F, 1.0F));
            Ogre::Entity* ent = mScnMgr->createEntity("Sinbad", "Sinbad.mesh");
            Ogre::SceneNode* node = mScnMgr->getRootSceneNode()->createChildSceneNode("SinbadNode");
            node->attachObject(ent);
        }
};

int main(int argc, char** argv)
{
    try {
        Example app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    } catch (const std::exception& e) {
        std::cerr << "Error occurred during execution: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}