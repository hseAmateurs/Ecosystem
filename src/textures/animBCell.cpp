//
// Created by Shon on 03.03.2024.
//

#include "animations.h"

namespace texture {
    float offsetBCell(float angle, AnimationParameters *parameters) {
        return
                sinf((angle + parameters->delta) * parameters->wavePeriod)
                *
                parameters->currentPulsationAspect;
    }

    void pulsationBCell(AnimationParameters *parameters) {
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


    AnimationParameters bCell{
            offsetBCell,
            pulsationBCell,
            13,
            0.008f,
            3.5f,
            0.04f,
            0.1f,
    };
}
