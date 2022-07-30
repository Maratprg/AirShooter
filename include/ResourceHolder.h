#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstring>
#include <string>
#include <map>

#include <vector>
#include <algorithm>

// RAII texture namespaces with their enums
namespace specific_Texture
{
    enum ID_air
    {
       Cloud,
       Eagle,
       Raptor,
       Combat,
       Defeater,
       NRD,
       ComRap,
       ComRapDeaf,
       SRD,
       NRDC,
       Boss,
       IslandTopF,
       Enum_Count
    };

    enum ID_scene
    {
       Start,
       Stage_1,
       Stage_2,
       Stage_3,
       Stop,
       TEST,
       Enum_Coun
    };
}


// RAII sound buffer namespace with their enum
namespace specific_Soundbuff
{
    enum ID
    {
       bossBorn,
       bossBurn,
       bossDamage,
       bossShoot,
       enemyDamage,
       enemyKill,
       enemyShoot,
       playerDamage,
       playerGass,
       playerRotate,
       playerShadow,
       playerShoot,
       redifine,
       start,
       Enum_Count
    };
}

// RAII sound buffer namespaces with their enum
namespace specific_Music
{
    enum ID
    {
        Game_On,
        Stage_One,
        Stage_Two,
        Stage_Three,
        Game_Off,
        Enum_Count
    };
}

class ResourceHolder
{
    public:
        ResourceHolder();
        virtual ~ResourceHolder();

        sf::Texture& getTextureAir(specific_Texture::ID_air id);
        void addTextureAir(specific_Texture::ID_air id, std::string file_Path);

        sf::Texture& getTextureScene(specific_Texture::ID_scene id);
        void addTextureScene(specific_Texture::ID_scene id, std::string file_Path);

        sf::SoundBuffer& getSndBuff(specific_Soundbuff::ID id);
        void addSndBuff(specific_Soundbuff::ID id, std::string file_Path);

        sf::Music& getMusic() {return music;};
        void setMusic(std::string file_Path) {  music.openFromFile(file_Path);  };

        sf::Vector2f& getEnemySize(specific_Texture::ID_air id);

    public:
        void loadTexturesAir();
        void loadEnemySizesMAP();
        void loadTexturesScene();
        void loadSBuff();
        void loadMusic();

    private:
        sf::Texture textureAir[specific_Texture::ID_air::Enum_Count];
        sf::Texture textureScene[specific_Texture::ID_scene::Enum_Coun];
        std::map <specific_Soundbuff::ID, sf::SoundBuffer> bMap;
        sf::Music music;

        //for size of enemy
        std::map <specific_Texture::ID_air, sf::Vector2f> bSize;
};

#endif // RESOURCEHOLDER_H
