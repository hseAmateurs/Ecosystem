//
// Created by Shon on 03.03.2024.
//

#include "animations.h"

namespace texture {
    float offsetMacro(float angle, AnimationParameters *parameters) {
        return
                (
                        powf(sinf((angle + parameters->delta) * parameters->wavePeriod * 3), 1)
                        +
                        powf(sinf((angle + parameters->delta) * parameters->wavePeriod * 1), 2)
                )
                *
                parameters->currentPulsationAspect;
    }

    void pulsationMacro(AnimationParameters *parameters) {
        parameters->currentPulsationAspect =
                parameters->pulsationWaveHeight
                +
                (
                        powf(sinf(parameters->delta * parameters->pulsationSpeed * 2), 1)
                        +
                        powf(sinf(parameters->delta * parameters->pulsationSpeed * 3), 2)
                )
                *
                parameters->pulsationSpan;
    }

    AnimationParameters macrophage{
            offsetMacro,
            pulsationMacro,
            3,
            0.2f,
            3.4f,
            0.1f,
            0.2f,

            // look at dying or birthing constructor in cellTexture.h
            10,
            0.59f,
            1,
    };

}

