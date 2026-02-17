#include "BaseApp.hpp"
#include <iostream>

class Example : public BaseApp {
    public:
        Example(Ogre::String name="OgreBook_Example") : BaseApp(name) {}
    protected:
        void createScene() override
        {
            mScnMgr->setAmbientLight(Ogre::ColourValue(1.0F, 1.0F, 1.0F));
            // see Readme.txt
        }
};

int main(int argc, char** argv)
{
    try {
        Example app ("Nombre del ejemplo");
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    } catch (const std::exception& e) {
        std::cerr << "Error occurred during execution: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}