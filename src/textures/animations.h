//
// Created by Shon on 03.03.2024.
//

#ifndef ECOSYSTEM_ANIMATIONS_H
#define ECOSYSTEM_ANIMATIONS_H

#include "cellTexture.h"
#include <cmath>

namespace texture {

    float offsetBody(float angle, AnimationParameters *parameters);

    void pulsationBody(AnimationParameters *parameters);

    float offsetMacro(float angle, AnimationParameters *parameters);

    void pulsationMacro(AnimationParameters *parameters);

    float offsetPathogen(float angle, AnimationParameters *parameters);

    void pulsationPathogen(AnimationParameters *parameters);

    float offsetAntibody(float angle, AnimationParameters *parameters);

    void pulsationAntibody(AnimationParameters *parameters);

    float offsetNeutro(float angle, AnimationParameters *parameters);

    void pulsationNeutro(AnimationParameters *parameters);

    float offsetBCell(float angle, AnimationParameters *parameters);

    void pulsationBCell(AnimationParameters *parameters);

    float offsetPlasma(float angle, AnimationParameters *parameters);

    void pulsationPlasma(AnimationParameters *parameters);




    extern AnimationParameters bodyCell;

    extern AnimationParameters macrophage;

    extern AnimationParameters pathogen;

    extern AnimationParameters antibody;

    extern AnimationParameters neutrophil;

    extern AnimationParameters bCell;

    extern AnimationParameters plasmaCell;
}
#endif //ECOSYSTEM_ANIMATIONS_H
