#include <iostream>

#include "core/assets.h"
#include "core/field.h"
#include "core/windowRender.h"
#include "core/temperature.h"
#include "core/controller.h"

int main() {
    setbuf(stdout, nullptr);
    srand(time(nullptr));

    Assets::instance().loadFont("../resources/font/couriercyrps_bold.ttf");
    Assets::instance().loadConfig("../config.csv");

    Field field;
    field.init();

    Temperature temperature(&field);

    WindowRender windowRender(&field, &temperature);

    Controller controller(&windowRender, &temperature);
    controller.run();

    return 0;
}
