extern void LINUZSYS();
extern void FORRGPBSC();
extern void COURRMOV();
// extern void SCRNPAINT(comst char *format, ...)
extern void EXECUTECOMMAND();
// extern void SHLLHANDL();
extern void HYDRMEM();
extern void IDTLOAD();
extern void initmouse();
// extern void SYSPE();

void GLDMAIN() {
IDTLOAD();
    LINUZSYS();
        HYDRMEM();
            initmouse();
          COURRMOV();
            FORRGPBSC();
                // EXECUTECOMMAND();
                    // SYSPE();
                        // SHLLHANDL();
                            // KBCOMST1

}