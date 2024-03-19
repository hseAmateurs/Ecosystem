//
// Created by Shon on 03.03.2024.
//

#include "animations.h"

namespace texture {
    float offsetNeutro(float angle, AnimationParameters *parameters) {
        return
                sinf((angle + parameters->delta) * parameters->wavePeriod)
                *
                parameters->currentPulsationAspect;
    }

    void pulsationNeutro(AnimationParameters *parameters) {
        parameters->currentPulsationAspect =
                parameters->pulsationWaveHeight
                +
                (
                        powf(sinf(parameters->delta * parameters->pulsationSpeed), 2)
                        +
                        powf(sinf(parameters->delta * parameters->pulsationSpeed * 4), 4)
                )
                *
                parameters->pulsationSpan;
    }


    AnimationParameters neutrophil{
            offsetNeutro,
            pulsationNeutro,
            13,
            0.46f,
            2.5f,
            0.04f,
            0.1f,

            // look at dying or birthing constructor in cellTexture.h
            4,
            0.885f,
            0.08f,
            5.f,
            4.f,
    };
}
