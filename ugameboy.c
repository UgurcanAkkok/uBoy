#include "ugameboy.h"

int main(int argc, char* argv[]){
    if (argc < 2) usage(argv);
    /* TODO
     * Parses args and defines the vars accordingly
     * which effectively does smthn like
     * int arg_h = 1; // Index of h
     * char * arg_h_parameter = argv[arg_h + 1];
     *
     * parse_arg(argv);
     */

    log_init();

    load_rom(argv[1]);
#if HEXDUMP
    disassemble("rom.x");
#else
    cpu_main();
#endif

    log_close();


}
