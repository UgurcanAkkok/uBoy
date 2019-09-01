/*
 *  uGameBoy, a gameboy emulator.
 *  Copyright (C) 2019  Uğurcan Akkök

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.

 *  to contact about this program, mail akkokugurcan@gmail.com
 */
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

    bool hexdump = 0;
    char * dump_fname;

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
                case 'x':
                    hexdump = 1;
                    if (arg_p)
                        dump_fname = arg_p;
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

    if (hexdump) disassemble(dump_fname);
    else cpu_main();

    log_close();


}
