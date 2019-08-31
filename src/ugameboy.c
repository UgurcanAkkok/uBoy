#include "ugameboy.h"

int main(int argc, char* argv[]){
    if (argc < 2) usage();
    /* TODO
     * parse_arg(argv);
     *
     * Parses args and defines the vars accordingly
     * which effectively does smthn like
     * int arg_h = 1; // Index of h
     * char * arg_h_parameter = argv[arg_h + 1];
     *
     */

    char * romname;
    
    int argc_;
    int i;
    char *argv_;
    char argv0s;
    char * argv0l;
    char * arg_p;
    for (argc_ = 1, i = 0; argc_< argc \
            && argv[argc_][i++] == '-'; argc_++){

        argv_ = argv[argc_];
        if (argv_[i] != '-') {
            /* Short option */
            argv0s = argv_[i];
            if (argv_[++i]){
                arg_p = &argv_[i];
            }
            else {
                arg_p = argv[++argc_];
            }

            switch (argv0s){
                case 'h':
                    usage();
                    break;
                case 'l':
                    printf("Log lvl is %s\n", arg_p);
                    set_log_lvl(atoi(arg_p));
                    break;
            }
        }
        else {
            /* Long option */
            argv0l = &argv_[2];
        }
    }

    romname = argv[argc - 1];
    log_init();

    load_rom(romname);
#if HEXDUMP
    disassemble("rom.hexdump");
#else
    cpu_main();
#endif

    log_close();


}
