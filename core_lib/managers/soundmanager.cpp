#include "soundmanager.h"


#include "object.h"
#include "layersound.h"
#include "soundclip.h"
#include "soundplayer.h"

SoundManager::SoundManager( QObject* parnet ) : BaseManager( parnet )
{
}

SoundManager::~SoundManager()
{
}

bool SoundManager::init()
{
    return true;
}

Status SoundManager::onObjectLoaded( Object* )
{
    return Status::OK;
}

Status SoundManager::loadSound( Layer* soundLayer, int frameNumber, QString strSoundFile )
{
    Q_ASSERT( soundLayer );
    if ( soundLayer->type() != Layer::SOUND )
    {
        return Status::ERROR_INVALID_LAYER_TYPE;
    }

    if ( frameNumber < 0 )
    {
        return Status::ERROR_INVALID_FRAME_NUMBER;
    }

    if ( !QFile::exists( strSoundFile ) )
    {
        return Status::FILE_NOT_FOUND;
    }
    
    KeyFrame* key = soundLayer->getKeyFrameAt( frameNumber );
    if ( key == nullptr )
    {
        key = new SoundClip;
        soundLayer->addKeyFrame( frameNumber, key );
    }
    
    if ( !key->fileName().isEmpty() )
    {
        return Status::FAIL;
    }

    QString strCopyFile = soundLayer->object()->copyFileToDataFolder( strSoundFile );
    Q_ASSERT( !strCopyFile.isEmpty() );

    SoundClip* soundClip = dynamic_cast< SoundClip* >( key );
    soundClip->init( strCopyFile );

    Status st = createMeidaPlayer( soundClip );
    if ( !st.ok() )
    {
        delete soundClip;
        return st;
    }

    return Status::OK;
}

Status SoundManager::createMeidaPlayer( SoundClip* clip )
{
    SoundPlayer* newPlayer = new SoundPlayer();
    newPlayer->init( clip );

    return Status::OK;
}
