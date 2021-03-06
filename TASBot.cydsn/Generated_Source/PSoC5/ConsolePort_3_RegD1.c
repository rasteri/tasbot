/*******************************************************************************
* File Name: ConsolePort_3_RegD1.c
* Version 2.30
*
* Description:
*  This file provides the API source code for the Shift Register component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "ConsolePort_3_RegD1.h"

uint8 ConsolePort_3_RegD1_initVar = 0u;


/*******************************************************************************
* Function Name: ConsolePort_3_RegD1_Start
********************************************************************************
*
* Summary:
*  Starts the Shift Register.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ConsolePort_3_RegD1_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ConsolePort_3_RegD1_Start(void) 
{
    if(0u == ConsolePort_3_RegD1_initVar)
    {
        ConsolePort_3_RegD1_Init();
        ConsolePort_3_RegD1_initVar = 1u; /* Component initialized */
    }

    ConsolePort_3_RegD1_Enable();
}


/*******************************************************************************
* Function Name: ConsolePort_3_RegD1_Enable
********************************************************************************
*
* Summary:
*  Enables the Shift Register.
*
* Parameters:
*  void.
*
* Return:
*  void.
*
*******************************************************************************/
void ConsolePort_3_RegD1_Enable(void) 
{
    /* Changing address in Datapath Control Store
       from NOP to component state machine commands space */
    ConsolePort_3_RegD1_SR_CONTROL |= ConsolePort_3_RegD1_CLK_EN;

    ConsolePort_3_RegD1_EnableInt();
}


/*******************************************************************************
* Function Name: ConsolePort_3_RegD1_Init
********************************************************************************
*
* Summary:
*  Initializes Tx and/or Rx interrupt sources with initial values.
*
* Parameters:
*  void.
*
* Return:
*  void.
*
*******************************************************************************/
void ConsolePort_3_RegD1_Init(void) 
{
    ConsolePort_3_RegD1_SetIntMode(ConsolePort_3_RegD1_INT_SRC);
}


/*******************************************************************************
* Function Name: ConsolePort_3_RegD1_Stop
********************************************************************************
*
* Summary:
*  Disables the Shift Register
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ConsolePort_3_RegD1_Stop(void) 
{
    /*changing Datapath Control Store address to NOP space*/
    ConsolePort_3_RegD1_SR_CONTROL &= ((uint8) ~ConsolePort_3_RegD1_CLK_EN);
    ConsolePort_3_RegD1_DisableInt();
}


/*******************************************************************************
* Function Name: ConsolePort_3_RegD1_EnableInt
********************************************************************************
*
* Summary:
*  Enables the Shift Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ConsolePort_3_RegD1_EnableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    ConsolePort_3_RegD1_SR_AUX_CONTROL |= ConsolePort_3_RegD1_INTERRUPTS_ENABLE;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: ConsolePort_3_RegD1_DisableInt
********************************************************************************
*
* Summary:
*  Disables the Shift Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ConsolePort_3_RegD1_DisableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    ConsolePort_3_RegD1_SR_AUX_CONTROL &= ((uint8) ~ConsolePort_3_RegD1_INTERRUPTS_ENABLE);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: ConsolePort_3_RegD1_GetFIFOStatus
********************************************************************************
*
* Summary:
*  Returns current status of input or output FIFO.
*
* Parameters:
*  fifoId.
*
* Return:
*  FIFO status.
*
*******************************************************************************/
uint8 ConsolePort_3_RegD1_GetFIFOStatus(uint8 fifoId) 
{
    uint8 result;

    result = ConsolePort_3_RegD1_RET_FIFO_NOT_DEFINED;

    #if(0u != ConsolePort_3_RegD1_USE_INPUT_FIFO)
        if(ConsolePort_3_RegD1_IN_FIFO == fifoId)
        {
            switch(ConsolePort_3_RegD1_GET_IN_FIFO_STS)
            {
                case ConsolePort_3_RegD1_IN_FIFO_FULL :
                    result = ConsolePort_3_RegD1_RET_FIFO_FULL;
                    break;

                case ConsolePort_3_RegD1_IN_FIFO_EMPTY :
                    result = ConsolePort_3_RegD1_RET_FIFO_EMPTY;
                    break;

                case ConsolePort_3_RegD1_IN_FIFO_PARTIAL:
                    result = ConsolePort_3_RegD1_RET_FIFO_PARTIAL;
                    break;
                    
                default:
                    /* Initial result value, while 
                       IN_FIFO_EMPTY case is false 
                     */
                    result = ConsolePort_3_RegD1_RET_FIFO_EMPTY;
                    break;
            }   
        }
    #endif /* (0u != ConsolePort_3_RegD1_USE_INPUT_FIFO) */

    if(ConsolePort_3_RegD1_OUT_FIFO == fifoId)
    {
        switch(ConsolePort_3_RegD1_GET_OUT_FIFO_STS)
        {
            case ConsolePort_3_RegD1_OUT_FIFO_FULL :
                result = ConsolePort_3_RegD1_RET_FIFO_FULL;
                break;

            case ConsolePort_3_RegD1_OUT_FIFO_EMPTY :
                result = ConsolePort_3_RegD1_RET_FIFO_EMPTY;
                break;

            case ConsolePort_3_RegD1_OUT_FIFO_PARTIAL :
                result = ConsolePort_3_RegD1_RET_FIFO_PARTIAL;
                break;

            default:
                /* Initial result value, while 
                   OUT_FIFO_FULL case is false 
                 */
                result = ConsolePort_3_RegD1_RET_FIFO_FULL;
                break;
        }
    }

    return(result);
}


/*******************************************************************************
* Function Name: ConsolePort_3_RegD1_SetIntMode
********************************************************************************
*
* Summary:
*  Sets the Interrupt Source for the Shift Register interrupt. Multiple
*  sources may be ORed together
*
* Parameters:
*  interruptSource: Byte containing the constant for the selected interrupt
*  source/s.
*
* Return:
*  None.
*
*******************************************************************************/
void ConsolePort_3_RegD1_SetIntMode(uint8 interruptSource) 
{
    ConsolePort_3_RegD1_SR_STATUS_MASK &= ((uint8) ~ConsolePort_3_RegD1_INTS_EN_MASK);          /* Clear existing int */
    ConsolePort_3_RegD1_SR_STATUS_MASK |= (interruptSource & ConsolePort_3_RegD1_INTS_EN_MASK); /* Set int */
}


/*******************************************************************************
* Function Name: ConsolePort_3_RegD1_GetIntStatus
********************************************************************************
*
* Summary:
*  Gets the Shift Register Interrupt status.
*
* Parameters:
*  None.
*
* Return:
*  Byte containing the constant for the selected interrupt source/s.
*
*******************************************************************************/
uint8 ConsolePort_3_RegD1_GetIntStatus(void) 
{
    return(ConsolePort_3_RegD1_SR_STATUS & ConsolePort_3_RegD1_INTS_EN_MASK);
}


/*******************************************************************************
* Function Name: ConsolePort_3_RegD1_WriteRegValue
********************************************************************************
*
* Summary:
*  Send state directly to shift register
*
* Parameters:
*  shiftData: containing shift register state.
*
* Return:
*  None.
*
*******************************************************************************/
void ConsolePort_3_RegD1_WriteRegValue(uint16 shiftData)
                                                                     
{
    CY_SET_REG16(ConsolePort_3_RegD1_SHIFT_REG_LSB_PTR, shiftData);
}


#if(0u != ConsolePort_3_RegD1_USE_INPUT_FIFO)
    /*******************************************************************************
    * Function Name: ConsolePort_3_RegD1_WriteData
    ********************************************************************************
    *
    * Summary:
    *  Send state to FIFO for later transfer to shift register based on the Load
    *  input
    *
    * Parameters:
    *  shiftData: containing shift register state.
    *
    * Return:
    *  Indicates: successful execution of function
    *  when FIFO is empty; and error when FIFO is full.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    cystatus ConsolePort_3_RegD1_WriteData(uint16 shiftData)
                                                                         
    {
        cystatus result;

        result = CYRET_INVALID_STATE;

        /* Writes data into the input FIFO if it is not FULL */
        if(ConsolePort_3_RegD1_RET_FIFO_FULL != (ConsolePort_3_RegD1_GetFIFOStatus(ConsolePort_3_RegD1_IN_FIFO)))
        {
            CY_SET_REG16(ConsolePort_3_RegD1_IN_FIFO_VAL_LSB_PTR, shiftData);
            result = CYRET_SUCCESS;
        }

        return(result);
    }
#endif /* (0u != ConsolePort_3_RegD1_USE_INPUT_FIFO) */


#if(0u != ConsolePort_3_RegD1_USE_OUTPUT_FIFO)
    /*******************************************************************************
    * Function Name: ConsolePort_3_RegD1_ReadData
    ********************************************************************************
    *
    * Summary:
    *  Returns state in FIFO due to Store input.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Shift Register state
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 ConsolePort_3_RegD1_ReadData(void) 
    {
        return(CY_GET_REG16(ConsolePort_3_RegD1_OUT_FIFO_VAL_LSB_PTR));
    }
#endif /* (0u != ConsolePort_3_RegD1_USE_OUTPUT_FIFO) */


/*******************************************************************************
* Function Name: ConsolePort_3_RegD1_ReadRegValue
********************************************************************************
*
* Summary:
*  Directly returns current state in shift register, not data in FIFO due
*  to Store input.
*
* Parameters:
*  None.
*
* Return:
*  Shift Register state. Clears output FIFO.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint16 ConsolePort_3_RegD1_ReadRegValue(void) 
{
    uint16 result;

    /* Clear FIFO before software capture */
    while(ConsolePort_3_RegD1_RET_FIFO_EMPTY != ConsolePort_3_RegD1_GetFIFOStatus(ConsolePort_3_RegD1_OUT_FIFO))
    {
        (void) CY_GET_REG16(ConsolePort_3_RegD1_OUT_FIFO_VAL_LSB_PTR);
    }

    /* Read of 8 bits from A1 causes capture to output FIFO */
    (void) CY_GET_REG8(ConsolePort_3_RegD1_SHIFT_REG_CAPTURE_PTR);

    /* Read output FIFO */
    result  = CY_GET_REG16(ConsolePort_3_RegD1_OUT_FIFO_VAL_LSB_PTR);
    
    #if(0u != (ConsolePort_3_RegD1_SR_SIZE % 8u))
        result &= ((uint16) ConsolePort_3_RegD1_SR_MASK);
    #endif /* (0u != (ConsolePort_3_RegD1_SR_SIZE % 8u)) */
    
    return(result);
}


/* [] END OF FILE */
