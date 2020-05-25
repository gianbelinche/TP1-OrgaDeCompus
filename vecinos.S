#define O_GP 20
#define O_FP 16
#define SS 40
#define O_A0 (SS)
#define O_A1 (O_A0 + 4)
#define O_A2 (O_A1 + 4)
#define O_A3 (O_A2 + 4)

.text
.align 2

.globl vecinos
.ent strlcpy

vecinos:
    /* Actualizo sp */
    subu sp,sp,SS

    /* Guardo valores de gp y fp */
    sw gp, O_GP(sp)
    sw fp, O_FP(SP)
    move fp, sp

    /* Guardo parametros a0 -- a3 */
    sw   a0, O_A0(fp)
    sw   a1, O_A1(fp)
    sw   a2, O_A2(fp)
    sw   a3, O_A3(fp)

    /* Logica de la funcion */













    /* Restauro gp y fp */
    lw fp, O_FP(sp)
    lw gp, O_GP(sp)
    addiu sp, sp, SS

    jr ra

.end strlcpy    