/*******************************************************************************
* File Name: P2_5.h
* Version 2.30
*
* Description:
*  This header file contains definitions associated with the Shift Register
*  component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


#if !defined(CY_SHIFTREG_P2_5_H)
#define CY_SHIFTREG_P2_5_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component ShiftReg_v2_30 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define P2_5_FIFO_SIZE          (4u)
#define P2_5_USE_INPUT_FIFO     (0u)
#define P2_5_USE_OUTPUT_FIFO    (0u)
#define P2_5_SR_SIZE            (16u)


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;

    uint16 saveSrA0Reg;
    uint16 saveSrA1Reg;

    #if(CY_UDB_V0)
        uint16 saveSrIntMask;
    #endif /* (CY_UDB_V0) */

} P2_5_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  P2_5_Start(void)                              ;
void  P2_5_Stop(void)                               ;
void  P2_5_Init(void)                               ;
void  P2_5_Enable(void)                             ;
void  P2_5_RestoreConfig(void)                      ;
void  P2_5_SaveConfig(void)                         ;
void  P2_5_Sleep(void)                              ;
void  P2_5_Wakeup(void)                             ;
void  P2_5_EnableInt(void)                          ;
void  P2_5_DisableInt(void)                         ;
void  P2_5_SetIntMode(uint8 interruptSource)        ;
uint8 P2_5_GetIntStatus(void)                       ;
void  P2_5_WriteRegValue(uint16 shiftData) \
                                                                ;
uint16 P2_5_ReadRegValue(void) ;
uint8    P2_5_GetFIFOStatus(uint8 fifoId)           ;

#if(0u != P2_5_USE_INPUT_FIFO)
    cystatus P2_5_WriteData(uint16 shiftData) \
                                                                ;
#endif /* (0u != P2_5_USE_INPUT_FIFO) */

#if(0u != P2_5_USE_OUTPUT_FIFO)
    uint16 P2_5_ReadData(void) ;
#endif /* (0u != P2_5_USE_OUTPUT_FIFO) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 P2_5_initVar;


/***************************************
*           API Constants
***************************************/

#define P2_5_LOAD                   (0x01u)
#define P2_5_STORE                  (0x02u)
#define P2_5_RESET                  (0x04u)

#define P2_5_IN_FIFO                (0x01u)
#define P2_5_OUT_FIFO               (0x02u)

#define P2_5_RET_FIFO_FULL          (0x00u)

/* This define is obsolete */
#define P2_5_RET_FIFO_NOT_EMPTY     (0x01u)

#define P2_5_RET_FIFO_PARTIAL       (0x01u)
#define P2_5_RET_FIFO_EMPTY         (0x02u)
#define P2_5_RET_FIFO_NOT_DEFINED   (0xFEu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define P2_5__LEFT 0
#define P2_5__RIGHT 1



/***************************************
*    Initial Parameter Constants
***************************************/

#define P2_5_SR_MASK    (0xFFFFu) /* Unsigned is added to parameter */
#define P2_5_INT_SRC    (1u)
#define P2_5_DIRECTION  (1u)


/***************************************
*             Registers
***************************************/

/* Control register */
#define P2_5_SR_CONTROL_REG (* (reg8 *) \
                                           P2_5_bSR_SyncCtl_CtrlReg__CONTROL_REG)
#define P2_5_SR_CONTROL_PTR (  (reg8 *) \
                                           P2_5_bSR_SyncCtl_CtrlReg__CONTROL_REG)

/* Status register */
#define P2_5_SR_STATUS_REG      (* (reg8 *) P2_5_bSR_StsReg__STATUS_REG)
#define P2_5_SR_STATUS_PTR      (  (reg8 *) P2_5_bSR_StsReg__STATUS_REG)

/* Interrupt status register */
#define P2_5_SR_STATUS_MASK_REG (* (reg8 *) P2_5_bSR_StsReg__MASK_REG)
#define P2_5_SR_STATUS_MASK_PTR (  (reg8 *) P2_5_bSR_StsReg__MASK_REG)

/* Aux control register */
#define P2_5_SR_AUX_CONTROL_REG (* (reg8 *) P2_5_bSR_StsReg__STATUS_AUX_CTL_REG)
#define P2_5_SR_AUX_CONTROL_PTR (  (reg8 *) P2_5_bSR_StsReg__STATUS_AUX_CTL_REG)

/* A1 register: only used to implement capture function */
#define P2_5_SHIFT_REG_CAPTURE_PTR    ( (reg8 *) \
                                        P2_5_bSR_sC16_BShiftRegDp_u0__A1_REG )

#if(CY_PSOC3 || CY_PSOC5)
    #define P2_5_IN_FIFO_VAL_LSB_PTR        ( (reg16 *) \
                                        P2_5_bSR_sC16_BShiftRegDp_u0__F0_REG )

    #define P2_5_SHIFT_REG_LSB_PTR          ( (reg16 *) \
                                        P2_5_bSR_sC16_BShiftRegDp_u0__A0_REG )

    #define P2_5_SHIFT_REG_VALUE_LSB_PTR    ( (reg16 *) \
                                        P2_5_bSR_sC16_BShiftRegDp_u0__A1_REG )

    #define P2_5_OUT_FIFO_VAL_LSB_PTR       ( (reg16 *) \
                                        P2_5_bSR_sC16_BShiftRegDp_u0__F1_REG )

#else
    #if(P2_5_SR_SIZE <= 8u) /* 8bit - ShiftReg */
        #define P2_5_IN_FIFO_VAL_LSB_PTR        ( (reg8 *) \
                                        P2_5_bSR_sC16_BShiftRegDp_u0__F0_REG )

        #define P2_5_SHIFT_REG_LSB_PTR          ( (reg8 *) \
                                        P2_5_bSR_sC16_BShiftRegDp_u0__A0_REG )

        #define P2_5_SHIFT_REG_VALUE_LSB_PTR    ( (reg8 *) \
                                        P2_5_bSR_sC16_BShiftRegDp_u0__A1_REG )

        #define P2_5_OUT_FIFO_VAL_LSB_PTR       ( (reg8 *) \
                                        P2_5_bSR_sC16_BShiftRegDp_u0__F1_REG )

    #elif(P2_5_SR_SIZE <= 16u) /* 16bit - ShiftReg */
        #define P2_5_IN_FIFO_VAL_LSB_PTR        ( (reg16 *) \
                                  P2_5_bSR_sC16_BShiftRegDp_u0__16BIT_F0_REG )

        #define P2_5_SHIFT_REG_LSB_PTR          ( (reg16 *) \
                                  P2_5_bSR_sC16_BShiftRegDp_u0__16BIT_A0_REG )

        #define P2_5_SHIFT_REG_VALUE_LSB_PTR    ( (reg16 *) \
                                  P2_5_bSR_sC16_BShiftRegDp_u0__16BIT_A1_REG )

        #define P2_5_OUT_FIFO_VAL_LSB_PTR       ( (reg16 *) \
                                  P2_5_bSR_sC16_BShiftRegDp_u0__16BIT_F1_REG )


    #elif(P2_5_SR_SIZE <= 24u) /* 24bit - ShiftReg */
        #define P2_5_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                        P2_5_bSR_sC16_BShiftRegDp_u0__F0_REG )

        #define P2_5_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                        P2_5_bSR_sC16_BShiftRegDp_u0__A0_REG )

        #define P2_5_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                        P2_5_bSR_sC16_BShiftRegDp_u0__A1_REG )

        #define P2_5_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                        P2_5_bSR_sC16_BShiftRegDp_u0__F1_REG )

    #else /* 32bit - ShiftReg */
        #define P2_5_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                  P2_5_bSR_sC16_BShiftRegDp_u0__32BIT_F0_REG )

        #define P2_5_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                  P2_5_bSR_sC16_BShiftRegDp_u0__32BIT_A0_REG )

        #define P2_5_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                  P2_5_bSR_sC16_BShiftRegDp_u0__32BIT_A1_REG )

        #define P2_5_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                  P2_5_bSR_sC16_BShiftRegDp_u0__32BIT_F1_REG )

    #endif  /* (P2_5_SR_SIZE <= 8u) */
#endif      /* (CY_PSOC3 || CY_PSOC5) */


/***************************************
*       Register Constants
***************************************/

#define P2_5_INTERRUPTS_ENABLE      (0x10u)
#define P2_5_LOAD_INT_EN            (0x01u)
#define P2_5_STORE_INT_EN           (0x02u)
#define P2_5_RESET_INT_EN           (0x04u)
#define P2_5_CLK_EN                 (0x01u)

#define P2_5_RESET_INT_EN_MASK      (0xFBu)
#define P2_5_LOAD_INT_EN_MASK       (0xFEu)
#define P2_5_STORE_INT_EN_MASK      (0xFDu)
#define P2_5_INTS_EN_MASK           (0x07u)

#define P2_5_OUT_FIFO_CLR_BIT       (0x02u)

#if(0u != P2_5_USE_INPUT_FIFO)

    #define P2_5_IN_FIFO_MASK       (0x18u)

    #define P2_5_IN_FIFO_FULL       (0x00u)
    #define P2_5_IN_FIFO_EMPTY      (0x01u)
    #define P2_5_IN_FIFO_PARTIAL    (0x02u)
    
    /* This define is obsolete */
    #define P2_5_IN_FIFO_NOT_EMPTY  (0x02u)
    
#endif /* (0u != P2_5_USE_INPUT_FIFO) */

#define P2_5_OUT_FIFO_MASK          (0x60u)

#define P2_5_OUT_FIFO_EMPTY         (0x00u)
#define P2_5_OUT_FIFO_FULL          (0x01u)
#define P2_5_OUT_FIFO_PARTIAL       (0x02u)

/* This define is obsolete */
#define P2_5_OUT_FIFO_NOT_EMPTY     (0x02u)

#define P2_5_IN_FIFO_SHIFT_MASK     (0x03u)
#define P2_5_OUT_FIFO_SHIFT_MASK    (0x05u)

#define P2_5_DISABLED               (0u)
#define P2_5_DEFAULT_A0             (0u)
#define P2_5_DEFAULT_A1             (0u)


/***************************************
*       Macros
***************************************/

#define P2_5_IS_ENABLED         (0u != (P2_5_SR_CONTROL & P2_5_CLK_EN))

#define P2_5_GET_OUT_FIFO_STS   ((P2_5_SR_STATUS & P2_5_OUT_FIFO_MASK) >> \
                                              P2_5_OUT_FIFO_SHIFT_MASK)

#define P2_5_GET_IN_FIFO_STS    ((P2_5_SR_STATUS & P2_5_IN_FIFO_MASK)  >> \
                                              P2_5_IN_FIFO_SHIFT_MASK)


/***************************************
*       Obsolete
***************************************/

/* Following code are OBSOLETE and must not be used 
 * starting from ShiftReg 2.20 
 */

#define P2_5_SR_CONTROL     (P2_5_SR_CONTROL_REG)
#define P2_5_SR_STATUS      (P2_5_SR_STATUS_REG)
#define P2_5_SR_STATUS_MASK (P2_5_SR_STATUS_MASK_REG)
#define P2_5_SR_AUX_CONTROL (P2_5_SR_AUX_CONTROL_REG)

#define P2_5_IN_FIFO_SHFT_MASK  (P2_5_IN_FIFO_SHIFT_MASK)
#define P2_5_OUT_FIFO_SHFT_MASK (P2_5_OUT_FIFO_SHFIT_MASK)

#define P2_5_RET_FIFO_BAD_PARAM (0xFFu)

#endif /* (CY_SHIFTREG_P2_5_H) */


/* [] END OF FILE */
