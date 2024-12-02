#ifndef INOCENT_H
#define INOCENT_H

#include "personaje.h"

class Inocent : public Personaje {
public:
    Inocent(float x, float y, const sf::Texture& texture);
    void update() override;
};

#endif