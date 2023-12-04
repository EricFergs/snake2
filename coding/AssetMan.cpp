#include "AssetMan.hpp"
#include <stdexcept>

namespace Engine {

    AssetMan::AssetMan() {}

    AssetMan::~AssetMan() {}

    void AssetMan::AddTexture(int id, const std::string& filePath, bool wantRepeated)
    {
        auto texture = std::make_unique<sf::Texture>();

        if (texture->loadFromFile(filePath))
        {
            texture->setRepeated(wantRepeated);
            m_textures[id] = std::move(texture);
        }
        else
        {
            //std::cout << "Testing" << endl;
        }
    }

    void AssetMan::AddFont(int id, const std::string& filePath)
    {
        auto font = std::make_unique<sf::Font>();

        if (font->loadFromFile(filePath))
        {
            m_fonts[id] = std::move(font);
        }
        else
        {
            //std::cout << "Testing2" << endl;
        }
    }

    const sf::Texture& AssetMan::GetTexture(int id) const
    {
        auto it = m_textures.find(id);
        if (it != m_textures.end())
        {
            return *(it->second.get());
        }
        else
        {
            throw std::out_of_range("Texture with ID not found");
        }
    }

    const sf::Font& AssetMan::GetFont(int id) const
    {
        auto it = m_fonts.find(id);
        if (it != m_fonts.end())
        {
            return *(it->second.get());
        }
        else
        {
            throw std::out_of_range("Font with ID not found");
        }
    }

}
