#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include "irrlicht.h"
#include <QObject>
#include <QWidget>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class ParticleManager{
    public:
        ParticleManager(IrrlichtDevice* device);
        ~ParticleManager();

        //common settings
        stringw imagepath;
        QString type;
        f32 minStartSize;
        f32 maxStartSize;
        f32 duration;
        vector3df direction;
        vector3df scale;
        u32 minRate;
        u32 maxRate;
        f32 minTime;
        f32 maxTime;
        SColor minColor;
        SColor maxColor;

        //sphere settings
        u32 sphereRadius;
        //box settings
        aabbox3d<f32> boxSize;

        //functions
        void setColorBright(QColor& color);
        void setColorDark(QColor& color);
        void setDirection(float x, float y, float z);
        void createParticle();
        void createEmitter();

    private:        
        //vars
        IParticleSystemSceneNode* particleNode;
        IParticleEmitter* particleEmitter;
        IParticleAffector* particleAffector;
        IrrlichtDevice* device;
        ISceneManager* manager;


        //functions
        void init();

};

#endif // PARTICLEMANAGER
