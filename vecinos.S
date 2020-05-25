#define O_GP 20
#define O_FP 16
#define SS 40
#define O_A0 (SS)
#define O_A1 (O_A0 + 4)
#define O_A2 (O_A1 + 4)
#define O_A3 (O_A2 + 4)
#define O_A4 (O_A3 + 4)

.text
.align 2

.globl vecinos
.ent vecinos

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

    /* t0 = cant_vecinos */
    addiu t0,zero,0

    /* ----Vecino a la derecha---- */

    /* t1 = vecino_der_x = x + 1 */
    lw t1, O_A1(fp)
    addiu t1,t1,1

    /* v0 = N (temporalmente) */
    lw v0, O_A4(fp)
    sltu v0,t1,v0
    bnez v0,der
    nop
    /* si no se cumple la condicion, vecino_der_x = 0 */
    addiu t1,zero,0

der:
    /* v0 = N */
    lw v0, O_A4(fp)
    /* v0 = N * vecino_der_x */
    mul v0,t1,v0

    /* v1 = y */
    lw v1,O_A2(fp)
    /* v0 = vecino_der_x * N + y */
    addu v0,v0,v1
    /* v1 = adress array */
    lw v1,O_A0(fp)
    /* v0 = posicion array vecino */
    addu v0,v0,v1
    /* v1 = a[x][y] */
    lbu v1,0(v0)
    /* v0 = 1 */
    li v0,1
    bne v0,v1,siguiente
    nop
    /* cant_vecinos ++ */
    addiu t0,t0,1

siguiente:
    /* ----Vecino a la izquierda---- */

    /* t3 = vecino_izq_x = x - 1 */
    lw t3, O_A1(fp)
    //addiu t3,t3,-1

    /* v0 = N (temporalmente) */
    lw v0, O_A4(fp)
    bnez t3,izq
    nop
    /* si no se cumple la condicion, vecino_izq_x = N - 1 */
    addiu t3,v0,zero

izq:
    addiu t3,t3,-1
    /* v0 = N * vecino_izq_x */
    mul v0,t3,v0

    /* v1 = y */
    lw v1,O_A2(fp)
    /* v0 = vecino_izq_x * N + y */
    addu v0,v0,v1
    /* v1 = adress array */
    lw v1,O_A0(fp)
    /* v0 = posicion array vecino */
    addu v0,v0,v1
    /* v1 = a[x][y] */
    lbu v1,0(v0)
    /* v0 = 1 */
    li v0,1
    bne v0,v1,siguiente2
    nop
    /* cant_vecinos ++ */
    addiu t0,t0,1

siguiente2:
















    /* Restauro gp y fp */
    lw fp, O_FP(sp)
    lw gp, O_GP(sp)
    addiu sp, sp, SS

    jr ra

.end vecinos   