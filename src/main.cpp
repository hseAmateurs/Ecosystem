#include <iostream>

#include "core/assets.h"
#include "core/field.h"
#include "core/windowRender.h"

int main() {
    setbuf(stdout, nullptr);
    srand(time(nullptr));

    Assets::instance().loadFont("../resources/font/couriercyrps_bold.ttf");
    Assets::instance().loadConfig("../config.csv");

    Field field;
    field.init();

    WindowRender windowRender(field);
    windowRender.start();

    return 0;
}
