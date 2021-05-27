/*
 * File:   TempCalc
 * Author: MBender
 *
 * This routine controls and calculates the air temperature in the
 * container 
 * 
 * Routine      When Called     Purpose
 * -------      -----------     ------------------------------------
 * AN0_Init     Startup         Initialize the A/D Converter
 * AN0_ISR      A/D IRS         Capture A/D Result and tell Main
 * CaptureTemp  Sample Timer    Start A/D conversion of thermistor
 * ComputeTemp  Main            Calculate the temperature
 */
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "Master.h"

// Thermistor Constants
#define rPrime      0.01763227  
#define ThermBeta   3950.0
#define R1Therm     4700

// Floating Point Decomposition
float gfVtherm;     // Voltage at thermistor
float gfRtherm;     // Thermistor resistance value
float gfRRatio;     // Rtherm / rPrime
float gfLnRRatio;   // ln(gfRRatio)

void AN0_Init()
{
    ADCON0  = 0x01;     // Channel 0, A/D Enabled, Idle
    ADCON2  = 0xA8;     // Tad = Fosc/2.  Tacq = 12 Tad
    PIR1bits.ADIF = 0;  // Clear any pending interrupts
    PIE1bits.ADIE = 1;  // Enable Interrupts
}

void AN0_ISR()
{
    giTempCapture = (uint8_t) (ADRESH << 8);
    giTempCapture += ADRESL;
    PIR1bits.ADIF = 0;          // Clear Interrupt Flag
    gb_TempCaptured = true;     // Tell Main we got it.
}

void CaptureTemp()
{
    //  Start Thermistor A/D Conversion.
    //  A/D Done Interrupt will trigger ComputeTemp routine
    gb_TempCaptured = false;    // Just in case
    ADCON0bits.GO = 1;
}

void ComputeTemp()
{    
    gfVtherm = (Vcc * giTempCapture)/1023;
    gfRtherm = gfVtherm * R1Therm / (Vcc - gfVtherm);
    gfRRatio = gfRtherm / rPrime;
    gfLnRRatio = log(gfRRatio);
    gfAirTempC = ThermBeta / gfLnRRatio - gc_AbsZero;
    giAirTempC = (int) round(gfAirTempC);
    giAirTempF = (int) round((gfAirTempC * 9 / 5) + 32);
    Nop();                    // For break point
}