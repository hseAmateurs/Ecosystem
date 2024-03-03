//
// Created by Shon on 03->03->2024->
//

#include "animations.h"
#include <cmath>

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

    AnimationParameters bodyCell{
            offsetBody,
            pulsationBody,
            10,
            0.006f,
            4.f,
            0.03f,
            0.06f,
    };

    AnimationParameters macrophage{
            offsetMacro,
            pulsationMacro,
            3,
            0.005f,
            3.4f,
            0.1f,
            0.2f,
    };

    AnimationParameters pathogen{
            offsetPathogen,
            pulsationPathogen,
            4,
            0.02f,
            2.f,
            0.07f,
            0.1f,
    };


    AnimationParameters antibody{
            offsetAntibody,
            pulsationAntibody,
            3,
            0.015f,
            2.f,
            0.1f,
            0.5f,
    };


    AnimationParameters neutrophil{
            offsetNeutro,
            pulsationNeutro,
            13,
            0.008f,
            3.5f,
            0.04f,
            0.1f,
    };


    AnimationParameters bCell{
            offsetBCell,
            pulsationBCell,
            13,
            0.008f,
            3.5f,
            0.04f,
            0.1f,
    };


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
