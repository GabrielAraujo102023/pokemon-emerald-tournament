/* mGBA 0.10.3 core API prototype. No battle logic lives on the host.
 * Line protocol operates only on GBA RAM; EOF ends the one-instance process.
 */
#include <mgba/core/core.h>
#include <mgba/core/serialize.h>
#include <mgba/core/version.h>
#include <mgba/core/log.h>
#include <mgba-util/vfs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h>
static int ram(uint32_t a, uint32_t n) {
    uint64_t end=(uint64_t)a+n;
    return n && ((a>=0x02000000u && end<=0x02040000u) || (a>=0x03000000u && end<=0x03008000u));
}
static void log_stderr(struct mLogger *logger, int category, enum mLogLevel level, const char *format, va_list args) {
    (void)logger; (void)category; (void)level;
    vfprintf(stderr,format,args); fputc('\n',stderr);
}
int main(int argc, char **argv) {
    struct mLogger logger={.log=log_stderr,.filter=NULL};
    mLogSetDefaultLogger(&logger);
    if(argc==2 && !strcmp(argv[1],"--version")) { printf("emerald-mgba-bridge ABI 1; mGBA %s (%s)\n",projectVersion,gitCommit); return 0; }
    int ready = argc==6 && !strcmp(argv[1],"--capture-ready");
    int boot = ready || (argc==6 && !strcmp(argv[1],"--boot-probe"));
    if(!boot && argc!=3) { fprintf(stderr,"usage: emerald-mgba-bridge ROM CHECKPOINT\n"); return 2; }
    struct mCore *core=mCoreFind(argv[boot?2:1]);
    if(!core || !core->init(core)) return 3;
    mCoreInitConfig(core,"emerald-tournament");
    if(!mCoreLoadFile(core,argv[boot?2:1])) return 4;
    unsigned width=0, height=0;
    core->desiredVideoDimensions(core,&width,&height);
    if(!width || !height || width>1024 || height>1024) return 6;
    color_t *pixels=calloc((size_t)width*height,sizeof(color_t));
    if(!pixels) return 7;
    core->setVideoBuffer(core,pixels,width);
    if(boot) { core->rtc.override=RTC_FIXED; core->rtc.value=0; } /* Boot probe policy: Unix epoch, not host wall clock. */
    core->reset(core);
    if(boot) {
        char *end; unsigned long frames=strtoul(argv[3],&end,0);
        if(*end || !frames || frames>36000) return 8;
        unsigned long address=strtoul(argv[4],&end,0);
        if(*end || address>UINT32_MAX || !ram((uint32_t)address,4)) return 9;
        core->setKeys(core,0);
        for(unsigned long frame=0;frame<frames;frame++) {
            core->runFrame(core);
            printf("%lu %u\n",frame+1,core->busRead32(core,(uint32_t)address));
            if(ready && core->busRead32(core,(uint32_t)address+8)==2) break;
        }
        if(ready && core->busRead32(core,(uint32_t)address+8)!=2) return 11;
        struct VFile *saved=VFileOpen(argv[5],O_RDWR|O_CREAT|O_TRUNC);
        if(!saved || !mCoreSaveStateNamed(core,saved,SAVESTATE_SAVEDATA|SAVESTATE_RTC)) return 10;
        saved->close(saved);
        core->deinit(core); free(pixels); return 0;
    }
    struct VFile *state=VFileOpen(argv[2],O_RDONLY);
    if(!state || !mCoreLoadStateNamed(core,state,SAVESTATE_SAVEDATA|SAVESTATE_RTC)) return 5;
    state->close(state);
    core->setKeys(core,0);
    puts("READY 1"); fflush(stdout);
    char line[256], command;
    uint32_t a,n;
    while(fgets(line,sizeof(line),stdin)) {
        if(sscanf(line," %c %u %u",&command,&a,&n)==3 && command=='R' && n<=65536 && ram(a,n)) {
            for(uint32_t i=0;i<n;i++) printf("%02x",core->busRead8(core,a+i));
            puts("");
        } else if(sscanf(line," %c %u %u",&command,&a,&n)==3 && command=='W' && ram(a,4) && !(a&3)) {
            core->busWrite32(core,a,n); puts("OK");
        } else if(sscanf(line," %c %u",&command,&n)==2 && command=='F' && n>0 && n<=60) {
            for(uint32_t i=0;i<n;i++) core->runFrame(core);
            puts("OK");
        } else { puts("ERROR invalid command"); }
        fflush(stdout);
    }
    core->deinit(core);
    free(pixels);
    return 0;
}
