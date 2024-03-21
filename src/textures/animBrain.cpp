//
// Created by Shon on 21.03.2024
//

#include "animations.h"

namespace texture {
    float offsetBrain(float angle, AnimationParameters *parameters) {
        return
                sinf((angle + parameters->delta) * parameters->wavePeriod)
                *
                parameters->currentPulsationAspect;
    }

    void pulsationBrain(AnimationParameters *parameters) {
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


    AnimationParameters brain{
            offsetBrain,
            pulsationBrain,
            7,
            0.116f,
            4.f,
            0.01f,
            0.01f,

            // look at dying or birthing constructor in cellTexture.h
            5,
            0.885f,
            0.08f,
            5.f,
            4.f,
    };
}
