#include "ResourceHolder.h"

ResourceHolder::ResourceHolder()
    {
        // constructor initialization of loading everything
        this->loadTexturesAir();
        this->loadEnemySizesMAP();
        this->loadTexturesScene();
        this->loadSBuff();
        this->loadMusic();

    }

ResourceHolder::~ResourceHolder() {}

// implementation of resource loading in the form of a function
void ResourceHolder::loadTexturesAir()
    {
      try
        {
          this->addTextureAir(specific_Texture::ID_air::Boss, "Media/Boss.png");
          this->addTextureAir(specific_Texture::ID_air::Cloud, "Media/Cloud.png");
          this->addTextureAir(specific_Texture::ID_air::Combat, "Media/Combat.png");
          this->addTextureAir(specific_Texture::ID_air::ComRap, "Media/ComRap.png");
          this->addTextureAir(specific_Texture::ID_air::ComRapDeaf, "Media/ComRapDeaf.png");
          this->addTextureAir(specific_Texture::ID_air::Defeater, "Media/Defeater.png");
          this->addTextureAir(specific_Texture::ID_air::Eagle, "Media/Eagle.png");
          this->addTextureAir(specific_Texture::ID_air::IslandTopF, "Media/IslandTopF.png");
          this->addTextureAir(specific_Texture::ID_air::NRD, "Media/NRD.png");
          this->addTextureAir(specific_Texture::ID_air::NRDC, "Media/NRDC.png");
          this->addTextureAir(specific_Texture::ID_air::Raptor, "Media/Raptor.png");
          this->addTextureAir(specific_Texture::ID_air::SRD, "Media/SRD.png");
        }
      catch (std::runtime_error& e)
        {
         std::cout << "Resource eror is ::: " << e.what() << std::endl;
        }

    }

// loading sizes of sprites
void ResourceHolder::loadEnemySizesMAP()
    {
      using namespace std;
      bSize.insert(make_pair(specific_Texture::ID_air::Cloud, sf::Vector2f(189.f, 131.f)));
      bSize.insert(make_pair(specific_Texture::ID_air::Eagle, sf::Vector2f(189.f, 189.f)));
      bSize.insert(make_pair(specific_Texture::ID_air::Raptor, sf::Vector2f(189.f, 156.f)));
      bSize.insert(make_pair(specific_Texture::ID_air::Combat, sf::Vector2f(189.f, 169.f)));
      bSize.insert(make_pair(specific_Texture::ID_air::Defeater, sf::Vector2f(189.f, 210.f)));
      bSize.insert(make_pair(specific_Texture::ID_air::NRD, sf::Vector2f(230.f, 189.f)));
      bSize.insert(make_pair(specific_Texture::ID_air::ComRap, sf::Vector2f(222.f, 189.f)));
      bSize.insert(make_pair(specific_Texture::ID_air::ComRapDeaf, sf::Vector2f(434.f, 484.f)));
      bSize.insert(make_pair(specific_Texture::ID_air::SRD, sf::Vector2f(189.f, 210.f)));
      bSize.insert(make_pair(specific_Texture::ID_air::NRDC, sf::Vector2f(220.f, 189.f)));
      bSize.insert(make_pair(specific_Texture::ID_air::Boss, sf::Vector2f(387.f, 340.f)));
      bSize.insert(make_pair(specific_Texture::ID_air::IslandTopF, sf::Vector2f(353.f, 353.f)));

    }

// loading scene textures
void ResourceHolder::loadTexturesScene()
    {
        try
        {
          this->addTextureScene(specific_Texture::ID_scene::Start, "Media/landscape/Start.png");
          this->addTextureScene(specific_Texture::ID_scene::Stop, "Media/landscape/Stop.png");
          this->addTextureScene(specific_Texture::ID_scene::Stage_1, "Media/landscape/Stage_1.png");
          this->addTextureScene(specific_Texture::ID_scene::Stage_2, "Media/landscape/Stage_2.png");
          this->addTextureScene(specific_Texture::ID_scene::Stage_3, "Media/landscape/Stage_3.png");
          this->addTextureScene(specific_Texture::ID_scene::TEST, "Media/landscape/TEST.png");
        }
        catch(std::runtime_error& e)
        {
            std::cout << "Resource eror is ::: " << e.what() << std::endl;
        }
    }

// load game sounds buffer
void ResourceHolder::loadSBuff()
{
    try
    {
      this->addSndBuff(specific_Soundbuff::ID::bossBorn, "Media/sound/bossBorn.ogg" );
      this->addSndBuff(specific_Soundbuff::ID::bossBurn, "Media/sound/bossBurn.ogg" );
      this->addSndBuff(specific_Soundbuff::ID::bossDamage, "Media/sound/bossDamage.ogg" );
      this->addSndBuff(specific_Soundbuff::ID::bossShoot, "Media/sound/bossShoot.ogg" );
      this->addSndBuff(specific_Soundbuff::ID::enemyDamage, "Media/sound/enemyDamage.ogg" );
      this->addSndBuff(specific_Soundbuff::ID::enemyKill, "Media/sound/enemyKill.ogg" );
      this->addSndBuff(specific_Soundbuff::ID::enemyShoot, "Media/sound/enemyShoot.ogg" );
      this->addSndBuff(specific_Soundbuff::ID::playerDamage, "Media/sound/playerDamage.ogg" );
      this->addSndBuff(specific_Soundbuff::ID::playerGass, "Media/sound/playerGass.ogg" );
      this->addSndBuff(specific_Soundbuff::ID::playerRotate, "Media/sound/playerRotate.ogg" );
      this->addSndBuff(specific_Soundbuff::ID::playerShadow, "Media/sound/playerShadow.ogg" );
      this->addSndBuff(specific_Soundbuff::ID::playerShoot, "Media/sound/playerShoot.ogg" );
      this->addSndBuff(specific_Soundbuff::ID::redifine, "Media/sound/redifine.ogg" );
      this->addSndBuff(specific_Soundbuff::ID::start, "Media/sound/start.ogg" );

    }
    catch (std::runtime_error& e)
    {
       std::cout << "Buffer Sound Error: " << e.what() << std::endl;
    }
}
// try to load music in game
void ResourceHolder::loadMusic()
{
    try
    {
        this->setMusic("Media/sound/loadinger.ogg");
    }
    catch(std::runtime_error& e)
    {
       std::cout << "Load Mmusic Fail!: " << e.what() << std::endl;
    }

}

// return texture link by the specific id
sf::Texture& ResourceHolder::getTextureAir(specific_Texture::ID_air id)
    {
        return textureAir[id];
    }
// add a new texture by specific id
void ResourceHolder::addTextureAir(specific_Texture::ID_air id, std::string file_Path)
    {
        textureAir[id].loadFromFile(file_Path);
    }

sf::Texture& ResourceHolder::getTextureScene(specific_Texture::ID_scene id)
    {
        return textureScene[id];
    }

void ResourceHolder::addTextureScene(specific_Texture::ID_scene id, std::string file_Path)
    {
        textureScene[id].loadFromFile(file_Path);
    }

// return link of short sound buffer container by cpesific id
sf::SoundBuffer& ResourceHolder::getSndBuff(specific_Soundbuff::ID id)
    {
        std::map <specific_Soundbuff::ID, sf::SoundBuffer> :: iterator it;
        it = bMap.find(id);
        return it->second;
    }
// add a new sound buffer by specific id
void ResourceHolder::addSndBuff(specific_Soundbuff::ID id, std::string file_Path)
    {
        sf::SoundBuffer b;
        b.loadFromFile(file_Path);
        bMap[id] = b;
    }

//return sizes of textures adding in holder
sf::Vector2f& ResourceHolder::getEnemySize(specific_Texture::ID_air id)
    {
        std::map <specific_Texture::ID_air, sf::Vector2f> :: iterator it;
        it = bSize.find(id);
        return it->second;
    }
