#include "utils.h"

void usage(){
    printf("usage is : \t%s ROM\n", __FILE__);
    die("Usage is printed");
}

void die(char * errmsg){
    printf("%s\n", errmsg);
    exit(1);
}

void log_init(){
#if LOG
    logF = fopen(LOG_FILE_NAME, "w");

#endif
}

void set_log_lvl(int n){
    LOG_LVL = n;
}

void log_value(DEBUG_LVL lvl, char * logfstr, int val){
#if LOG
    char logstr[LOG_MAX_LENGTH];
    sprintf(logstr, logfstr, val);
    log_write(lvl, logstr);
#endif
}
void log_write(enum DEBUG_LVL lvl, char * logstr){
#if LOG
    if (lvl < LOG_LVL) {
        return;
    }

    switch(lvl){
        case MSG:
            fprintf(logF, "MSG: ");
            break;
        case WARN:
            fprintf(logF, "WARN: ");
            break;
        case CRITIC:
            fprintf(logF, "CRITIC: ");
            break;
        case ERR:
            fprintf(logF, "ERR: ");
            break;
    }
    time_t t = time(NULL);
    struct tm now = *localtime(&t);
    fprintf(logF, "%.2d:%.2d:%.2d %d.%d\t",now.tm_hour, now.tm_min,
            now.tm_sec, now.tm_mday, now.tm_mon + 1);
    fprintf(logF, "%s\n", logstr);
    return;
#endif
}

void log_close(){
#if LOG
    fclose(logF);
#endif
}

void disassemble(char * outname){
    FILE * out = fopen(outname, "w");
    int i;
    uint8_t byte;
    unsigned short j;

    for (i = 0; i < 0x8000;){
        fprintf(out, "%.8X :\t", i);
        for(j = 0; j < 16; j++){
            byte = read_mem((uint16_t) i++);
            fprintf(out, "%.2x ", byte);
        }
        fprintf(out, "\n");
    }
    fclose(out);

}
