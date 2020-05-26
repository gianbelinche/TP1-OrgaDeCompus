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

    /* v0 = N */
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
    /* v1 = a[vecino_der_x][y] */
    lbu v1,0(v0)
    /* v0 = 1 */
    li v0,1
    bne v0,v1,siguiente
    nop
    /* cant_vecinos ++ */
    addiu t0,t0,1

siguiente:
    /* ----Vecino a la izquierda---- */

    /* t2 = vecino_izq_x = x - 1 */
    lw t2, O_A1(fp)

    /* v0 = N */
    lw v0, O_A4(fp)
    bnez t2,izq
    nop
    /* si no se cumple la condicion, vecino_izq_x = N - 1 */
    addiu t2,v0,0

izq:
    addiu t2,t2,-1
    /* v0 = N * vecino_izq_x */
    mul v0,t2,v0

    /* v1 = y */
    lw v1,O_A2(fp)
    /* v0 = vecino_izq_x * N + y */
    addu v0,v0,v1
    /* v1 = adress array */
    lw v1,O_A0(fp)
    /* v0 = posicion array vecino */
    addu v0,v0,v1
    /* v1 = a[vecino_izq_x][y] */
    lbu v1,0(v0)
    /* v0 = 1 */
    li v0,1
    bne v0,v1,siguiente2
    nop
    /* cant_vecinos ++ */
    addiu t0,t0,1

siguiente2:
    /* ----Vecino abajo---- */

    /* t3 = vecino_abajo_y = y + 1 */
    lw t3, O_A2(fp)
    addiu t3,t3,1

    /* v0 = M */
    lw v0, O_A3(fp)
    sltu v0,t3,v0
    bnez v0,abajo
    nop
    /* si no se cumple la condicion, vecino_abajo_y = 0 */
    addiu t3,zero,0

abajo:
    /* v0 = N * x */
    lw v0, O_A4(fp)
    lw v1, O_A1(fp)
    mul v0,v1,v0

    /* v0 = x * N + vecino_abajo_y */
    addu v0,v0,t3
    /* v1 = adress array */
    lw v1,O_A0(fp)
    /* v0 = posicion array vecino */
    addu v0,v0,v1
    /* v1 = a[x][vecino_abajo_y] */
    lbu v1,0(v0)
    /* v0 = 1 */
    li v0,1
    bne v0,v1,siguiente3
    nop
    /* cant_vecinos ++ */
    addiu t0,t0,1

siguiente3:
    /* ----Vecino arriba---- */

    /* t4 = vecino_arriba_y = y - 1 */
    lw t4, O_A2(fp)

    /* v0 = M */
    lw v0, O_A3(fp)

    bnez t4,arriba
    nop
    /* si no se cumple la condicion, vecino_arriba_y = M - 1 */
    addiu t4,v0,0

arriba:
    addiu t4,t4,-1
    /* v0 = N * x */
    lw v0, O_A4(fp)
    lw v1, O_A1(fp)
    mul v0,v1,v0

    /* v0 = x * N + vecino_arriba_y */
    addu v0,v0,t4
    /* v1 = adress array */
    lw v1,O_A0(fp)
    /* v0 = posicion array vecino */
    addu v0,v0,v1
    /* v1 = a[x][vecino_arriba_y] */
    lbu v1,0(v0)
    /* v0 = 1 */
    li v0,1
    bne v0,v1,siguiente4
    nop
    /* cant_vecinos ++ */
    addiu t0,t0,1

siguiente4:
    /* ----Vecino abajo der---- */

    /* v0 = N * vecino_der_x + vecino_abajo_y */
    lw v0, O_A4(fp)
    mul v0,v0,t1
    addu v0,v0,t3

    /* v1 = adress array */
    lw v1,O_A0(fp)
    /* v0 = posicion array vecino */
    addu v0,v0,v1
    /* v1 = a[x_vecino_der][vecino_abajo_y] */
    lbu v1,0(v0)
    /* v0 = 1 */
    li v0,1
    bne v0,v1,siguiente5
    nop
    /* cant_vecinos ++ */
    addiu t0,t0,1

siguiente5:
        





















    /* Restauro gp y fp */
    lw fp, O_FP(sp)
    lw gp, O_GP(sp)
    addiu sp, sp, SS

    jr ra

.end vecinos   