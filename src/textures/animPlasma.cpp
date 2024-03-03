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
                        powf(sinf(parameters->delta * parameters->pulsationSpeed), 2)
                        +
                        powf(sinf(parameters->delta * parameters->pulsationSpeed * 4), 4)
                )
                *
                parameters->pulsationSpan;
    }


    AnimationParameters plasmaCell{
            offsetPlasma,
            pulsationPlasma,
            13,
            0.008f,
            3.5f,
            0.04f,
            0.1f,
    };
}