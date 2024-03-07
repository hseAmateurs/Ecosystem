//
// Created by Shon on 03->03->2024->
//

#include "animations.h"

namespace texture {
    float offsetPlasma(float angle, AnimationParameters *parameters) {
        return
                sinf((angle + parameters->delta) * parameters->wavePeriod)
                *
                parameters->currentPulsationAspect;
    }

    void pulsationPlasma(AnimationParameters *parameters) {
        parameters->currentPulsationAspect =
                parameters->pulsationWaveHeight
                +
                (
                        powf(sinf(parameters->delta * parameters->pulsationSpeed), 10)
                        +
                        powf(sinf(parameters->delta * parameters->pulsationSpeed * 4), 4)
                )
                *
                parameters->pulsationSpan;
    }


    AnimationParameters plasmaCell{
            offsetPlasma,
            pulsationPlasma,
            7,
            0.116f,
            4.f,
            0.04f,
            0.03f,

            // look at dying or birthing constructor in cellTexture.h
            5,
            0.885f,
    };
}
