//
// Created by Shon on 03.03.2024.
//

#include "animations.h"

namespace texture {
    float offsetAntibody(float angle, AnimationParameters *parameters) {
        return
                (
                        powf(sinf((angle + parameters->delta) * parameters->wavePeriod), 1)
                        //+
                        //(float)pow(sin( (angle+parameters->delta) * parameters->wavePeriod * 1),2)
                )
                *
                parameters->currentPulsationAspect;
    }

    void pulsationAntibody(AnimationParameters *parameters) {
        parameters->currentPulsationAspect =
                parameters->pulsationWaveHeight
                +
                (
                        powf(sinf(parameters->delta * parameters->pulsationSpeed * 1), 2)
                        //+
                        //pow(sin( parameters->delta * parameters->pulsationSpeed * 2), 2)
                )
                *
                parameters->pulsationSpan;
    }

    AnimationParameters antibody{
            offsetAntibody,
            pulsationAntibody,
            3,
            0.87f,
            2.f,
            0.1f,
            0.5f,

            // look at dying or birthing constructor in cellTexture.h
            1,
            0.885f,
    };
}
