//
// Created by Shon on 03.03.2024.
//

#include "animations.h"

namespace texture {

    float offsetBody(float angle, AnimationParameters *parameters) {
        return
                sinf((angle + parameters->delta) * parameters->wavePeriod)
                *
                parameters->currentPulsationAspect;
    }

    void pulsationBody(AnimationParameters *parameters) {
        parameters->currentPulsationAspect =
                parameters->pulsationWaveHeight
                +
                (
                        powf(sinf(parameters->delta * parameters->pulsationSpeed * 2), 1)
                        +
                        powf(sinf(parameters->delta * parameters->pulsationSpeed * 3), 4)
                )
                *
                parameters->pulsationSpan;
    }


    AnimationParameters bodyCell{
            offsetBody,
            pulsationBody,
            10,
            0.006f,
            4.f,
            0.03f,
            0.06f,

            // look at dying or birthing constructor in cellTexture.h
            1,
            0.02f,
    };
}
