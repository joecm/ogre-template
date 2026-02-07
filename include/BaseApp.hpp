#include <Ogre.h>
#include <Bites/OgreApplicationContext.h>
#include <Bites/OgreInput.h> 

class BaseApp : public OgreBites::ApplicationContext, public OgreBites::InputListener {
    public:
        //Standard constructor
        BaseApp() : OgreBites::ApplicationContext("BaseApp") {
            mScnMgr=nullptr;
            mCam=nullptr;
            mNodeCam=nullptr;
        }
        void setup() override
        {
            //1) Do not forget to call the base first
            OgreBites::ApplicationContext::setup();
            
            // 2) Register for input events
            addInputListener(this);
                        
            //3) Create the SceneManager, in this case a generic one
            mScnMgr= getRoot()->createSceneManager(Ogre::ST_GENERIC, "BaseAppSMInstance");

            // 4) Sistema de shaders RTShaderSystem: necesario para muchos materiales en OGRE 1.12
            if (!Ogre::RTShader::ShaderGenerator::getSingletonPtr()) {
                Ogre::RTShader::ShaderGenerator::initialize();
            }
            Ogre::RTShader::ShaderGenerator::getSingleton().addSceneManager(mScnMgr);

            // 5) Carga de recursos
            Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("General");

            // 6) Create the camera and set its position
            mCam = mScnMgr->createCamera("myCam");
            mNodeCam = mScnMgr->getRootSceneNode()->createChildSceneNode("CameraNode");
            mNodeCam->setPosition(0.0F, 0.0F, 500.0F);
            mNodeCam->attachObject(mCam);
            mCam->lookAt(Ogre::Vector3(0.0F, 0.0F, -300.0F));
            mCam->setNearClipDistance(5.0F);
            getRenderWindow()->addViewport(mCam);
            // 7) Create your scene here :)
            createScene();
        }

    protected:
        virtual void createScene() = 0;
        
        bool keyPressed(const OgreBites::KeyboardEvent& evt) override
        {
            if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
            {
                getRoot()->queueEndRendering();
                return true;
            }
            
            Ogre::SceneNode* nodeSinbad = mScnMgr->getSceneNode("SinbadNode");
            if (nodeSinbad) {
                const Ogre::Radian step = Ogre::Degree(5.0F);
                if(evt.keysym.sym == 'w') nodeSinbad->pitch(step);
                if(evt.keysym.sym == 's') nodeSinbad->pitch(-step);
                if(evt.keysym.sym == 'a') nodeSinbad->yaw(step);
                if(evt.keysym.sym == 'd') nodeSinbad->yaw(-step);
            }

            // Modo Render (R)
            if (mNodeCam && evt.keysym.sym == 'r') {
                Ogre::PolygonMode pm = mCam->getPolygonMode();
                if (pm == Ogre::PM_SOLID) pm = Ogre::PM_WIREFRAME;
                else if (pm == Ogre::PM_WIREFRAME) pm=Ogre::PM_POINTS;
                else pm = Ogre::PM_SOLID;
                mCam->setPolygonMode(pm);
            }
            
            if (mNodeCam) {
                const Ogre::Real movestep = 10.0F;
                if(evt.keysym.sym == OgreBites::SDLK_UP) mNodeCam->translate(0.0F, 0.0F, -movestep, Ogre::Node::TS_LOCAL);
                if(evt.keysym.sym == OgreBites::SDLK_DOWN) mNodeCam->translate(0.0F, 0.0F, movestep, Ogre::Node::TS_LOCAL);
                if(evt.keysym.sym == OgreBites::SDLK_LEFT) mNodeCam->translate(-movestep, 0.0F, 0.0F, Ogre::Node::TS_LOCAL);
                if(evt.keysym.sym == OgreBites::SDLK_RIGHT) mNodeCam->translate(movestep, 0.0F, 0.0F, Ogre::Node::TS_LOCAL);
            }
            return true;
        }
        Ogre::SceneManager* mScnMgr;
        Ogre::SceneNode* mNodeCam;
        Ogre::Camera* mCam;
};