#include "../src/s4c.h"

int main(void) {
    printf("Using s4c-animate v%s\n", string_s4c_version());
#ifdef S4C_GUI_H_
    printf("Using s4c-gui v%s\n", string_s4c_gui_version());
#endif // S4C_GUI_H_
    return 0;
}
