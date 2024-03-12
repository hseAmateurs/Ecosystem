//
// Created by Shon on 03.03.2024.
//

#include "animations.h"

namespace texture {
    float offsetPathogen(float angle, AnimationParameters *parameters) {
        return
                (
                        powf(sinf((angle + parameters->delta) * parameters->wavePeriod * 2), 10)
                        +
                        powf(sinf((angle + parameters->delta) * parameters->wavePeriod * 3), 2)
                )
                *
                parameters->currentPulsationAspect;
    }

    void pulsationPathogen(AnimationParameters *parameters) {
        parameters->currentPulsationAspect =
                parameters->pulsationWaveHeight
                +
                (
                        powf(sinf(parameters->delta * parameters->pulsationSpeed * 3), 2)
                        +
                        powf(sinf(parameters->delta * parameters->pulsationSpeed * 2), 2)
                )
                *
                parameters->pulsationSpan;
    }


    AnimationParameters pathogen{
            offsetPathogen,
            pulsationPathogen,
            4,
            1.16f,
            2.f,
            0.07f,
            0.1f,

            // look at dying or birthing constructor in cellTexture.h
            1,
            1.18f,
            1,
    };
}
