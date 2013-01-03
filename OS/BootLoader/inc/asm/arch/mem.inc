;
; (C) Copyright 2006
; Texas Instruments, <www.ti.com>
; Richard Woodruff <r-woodruff2@ti.com>
;
; See file CREDITS for list of people who contributed to this
; project.
;
; This program is free software; you can redistribute it and/or
; modify it under the terms of the GNU General Public License as
; published by the Free Software Foundation; either version 2 of
; the License, or (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program; if not, write to the Free Software
; Foundation, Inc., 59 Temple Place, Suite 330, Boston,
; MA 02111-1307 USA
;

SDRC_CS0_OSET    EQU	0x0
SDRC_CS1_OSET    EQU	0x30  ; mirror CS1 regs appear offset 0x30 from CS0 

; set the 343x-SDRC incoming address convention 
    IF	:DEF:SDRC_B_R_C
B_ALL	EQU	(0 << 6)	; bank-row-column 
    ELIF :DEF:SDRC_B1_R_B0_C
B_ALL	EQU	(1 << 6)	; bank1-row-bank0-column 
    ELIF :DEF:SDRC_R_B_C
B_ALL	EQU	(2 << 6)	; row-bank-column 
    ENDIF

; Future memory combinations based on past 
SDP_SDRC_MDCFG_MONO_DDR    EQU	0x0
SDP_COMBO_MDCFG_0_DDR      EQU	0x0
SDP_SDRC_MDCFG_0_SDR       EQU	0x0

; Slower full frequency range default timings for x32 operation
SDP_SDRC_SHARING	EQU     0x00000100
SDP_SDRC_MR_0_SDR	EQU	0x00000031

    IF	:DEF:CONFIG_3430ZEBU
SDP_SDRC_MDCFG_0_DDR		EQU	(0x02582019:OR:B_ALL) ; Infin ddr module 
    ELSE
SDP_SDRC_MDCFG_0_DDR		EQU	(0x02584019:OR:B_ALL)
SDP_SDRC_MDCFG_0_DDR_MICRON_XM	EQU	(0x03588019:OR:B_ALL)
SDP_SDRC_MDCFG_0_DDR_NUMONYX_XM	EQU	(0x04590019:OR:B_ALL)
SDP_SDRC_MDCFG_0_DDR_HYNIX	EQU	(0x03588019:OR:B_ALL)
    ENDIF

; Numonyx devices 
MK65KX001AM_SDRC_MCDCFG		EQU	(0x02584019:OR:B_ALL)
MK65KX002AM_SDRC_MCDCFG		EQU	(0x03588019:OR:B_ALL)

SDP_SDRC_MR_0_DDR		EQU	0x00000032

; Diabling power down mode using CKE pin 
SDP_SDRC_POWER_POP		EQU	0x00000081

; optimized timings good for current shipping parts 
SDP_3430_SDRC_RFR_CTRL_100MHz   EQU	0x0002da01
SDP_3430_SDRC_RFR_CTRL_133MHz   EQU	0x0003de01 ; 7.8us/7.5ns - 50=0x3de 
SDP_3430_SDRC_RFR_CTRL_165MHz   EQU	0x0004e201 ; 7.8us/6ns - 50=0x4e2 
SDP_3430_SDRC_RFR_CTRL_200MHz   EQU	0x0005e601 ; 7.8us/5ns - 50=0x5e6 

DLL_OFFSET              EQU	0
DLL_WRITEDDRCLKX2DIS    EQU	1
DLL_ENADLL              EQU	1
DLL_LOCKDLL             EQU	0
DLL_DLLPHASE_72         EQU	0
DLL_DLLPHASE_90         EQU	1

; rkw - need to find of 90/72 degree recommendation for speed like before.
SDP_SDRC_DLLAB_CTRL	EQU	((DLL_ENADLL << 3) :OR: (DLL_LOCKDLL << 2) :OR: (DLL_DLLPHASE_90 << 1))

; Infineon part of 3430SDP (133MHz optimized) ~ 7.5ns
;	TDAL = Twr/Tck + Trp/tck = 15/7.5 + 22.5/7.5 = 2 + 3 = 5
;	TDPL = 15/7.5	= 2
;	TRRD = 15/2.5	= 2
;	TRCD = 22.5/7.5	= 3
;	TRP = 22.5/7.5	= 3
;	TRAS = 45/7.5	= 6
;	TRC = 65/7.5	= 8.6->9
;	TRFC = 75/7.5	= 10
;   ACTIMB
;	TCKE = 2
;	XSR = 120/7.5 = 16
 
INFINEON_TDAL_133	EQU	5
INFINEON_TDPL_133	EQU	2
INFINEON_TRRD_133   	EQU	2
INFINEON_TRCD_133       EQU     3
INFINEON_TRP_133        EQU     3
INFINEON_TRAS_133       EQU     6
INFINEON_TRC_133        EQU     9
INFINEON_TRFC_133      	EQU     10
INFINEON_V_ACTIMA_133 	EQU	((INFINEON_TRFC_133 << 27) :OR: (INFINEON_TRC_133 << 22) :OR: (INFINEON_TRAS_133 << 18) :OR:(INFINEON_TRP_133 << 15) :OR: (INFINEON_TRCD_133 << 12) :OR:(INFINEON_TRRD_133 << 9) :OR:(INFINEON_TDPL_133 << 6) :OR: (INFINEON_TDAL_133))

INFINEON_TWTR_133       EQU     1
INFINEON_TCKE_133       EQU     2
INFINEON_TXP_133        EQU     2
INFINEON_XSR_133       	EQU     16
INFINEON_V_ACTIMB_133 	EQU	((INFINEON_TCKE_133 << 12) :OR: (INFINEON_XSR_133 << 0)) :OR: (INFINEON_TXP_133 << 8) :OR: (INFINEON_TWTR_133 << 16)

INFINEON_V_ACTIMA_100	EQU	INFINEON_V_ACTIMA_133
INFINEON_V_ACTIMB_100 	EQU	INFINEON_V_ACTIMB_133


; Infineon part of 3430SDP (165MHz optimized) 6.06ns
;    ACTIMA
; 	TDAL = Twr/Tck + Trp/tck = 15/6 + 18/6 = 2.5 + 3 = 5.5 -> 6
; 	TDPL (Twr) = 15/6	= 2.5 -> 3
; 	TRRD = 12/6	= 2
; 	TRCD = 18/6	= 3
; 	TRP = 18/6	= 3
; 	TRAS = 42/6	= 7
; 	TRC = 60/6	= 10
; 	TRFC = 72/6	= 12
;    ACTIMB
; 	TCKE = 2
; 	XSR = 120/6 = 20
 
INFINEON_TDAL_165   	EQU	6
INFINEON_TDPL_165   	EQU	3
INFINEON_TRRD_165   	EQU	2
INFINEON_TRCD_165   	EQU	3
INFINEON_TRP_165    	EQU	3
INFINEON_TRAS_165   	EQU	7
INFINEON_TRC_165   	EQU	10
INFINEON_TRFC_165  	EQU	12
INFINEON_V_ACTIMA_165 	EQU	((INFINEON_TRFC_165 << 27) :OR: (INFINEON_TRC_165 << 22) :OR: (INFINEON_TRAS_165 << 18) :OR: (INFINEON_TRP_165 << 15) :OR: (INFINEON_TRCD_165 << 12) :OR:(INFINEON_TRRD_165 << 9) :OR: (INFINEON_TDPL_165 << 6) :OR: (INFINEON_TDAL_165))

INFINEON_TWTR_165   	EQU	1
INFINEON_TCKE_165   	EQU	2
INFINEON_TXP_165    	EQU	2
INFINEON_XSR_165    	EQU	20
INFINEON_V_ACTIMB_165 	EQU	((INFINEON_TCKE_165 << 12) :OR: (INFINEON_XSR_165 << 0)) :OR: (INFINEON_TXP_165 << 8) :OR: (INFINEON_TWTR_165 << 16)

; Micron part of 3430 EVM (133MHz optimized) ~ 7.5ns
;	TDAL = Twr/Tck + Trp/tck = 15/7.5 + 22.5/7.5 = 2 + 3 = 5
;	TDPL =  15/7.5   = 2
;	TRRD =  15/7.5   = 2
;	TRCD =  22.5/7.5 = 3
;	TRP  =  22.5/7.5 = 3
;	TRAS =  45/7.5   = 6
;	TRC  =  75/7.5   = 10
;	TRFC =  125/7.5  = 16.6->17
;   ACTIMB
;	TWTR =  1
;	TCKE =  1
;	TXSR =  138/7.5  = 18.3->19
;	TXP  =  25/7.5   = 3.3->4
 
MICRON_TDAL_133   	EQU	5
MICRON_TDPL_133   	EQU	2
MICRON_TRRD_133   	EQU	2
MICRON_TRCD_133         EQU     3
MICRON_TRP_133          EQU     3
MICRON_TRAS_133         EQU     6
MICRON_TRC_133          EQU     10
MICRON_TRFC_133         EQU     17
MICRON_V_ACTIMA_133 	EQU	((MICRON_TRFC_133 << 27) :OR: (MICRON_TRC_133 << 22) :OR: (MICRON_TRAS_133 << 18) :OR:(MICRON_TRP_133 << 15) :OR: (MICRON_TRCD_133 << 12) :OR:(MICRON_TRRD_133 << 9) :OR:(MICRON_TDPL_133 << 6) :OR: (MICRON_TDAL_133))

MICRON_TWTR_133         EQU     1
MICRON_TCKE_133         EQU     1
MICRON_TXSR_133         EQU     19
MICRON_TXP_133          EQU     4
MICRON_V_ACTIMB_133 	EQU	((MICRON_TWTR_133 << 16) :OR: (MICRON_TCKE_133 << 12) :OR: (MICRON_TXP_133 << 8) :OR: (MICRON_TXSR_133 << 0))

MICRON_V_ACTIMA_100 	EQU	MICRON_V_ACTIMA_133
MICRON_V_ACTIMB_100 	EQU	MICRON_V_ACTIMB_133

; Micron part of 3430 EVM (165MHz optimized) 6.06ns
;   ACTIMA
;	TDAL = Twr/Tck + Trp/tck = 15/6 + 18 /6 = 2.5 + 3 = 5.5 -> 6
;	TDPL (Twr) = 15/6	= 2.5 -> 3
;	TRRD = 12/6	= 2
;	TRCD = 18/6 = 3
;	TRP = 18/6	= 3
;	TRAS = 42/6	= 7
;	TRC = 60/6	= 10
;	TRFC = 125/6	= 21
;   ACTIMB
;	TWTR =  1
;	TCKE =  1
;	TXSR =  138/6  = 23
;	TXP  =  25/6   = 4.1 ~5
 
MICRON_TDAL_165   	EQU	6
MICRON_TDPL_165         EQU     3
MICRON_TRRD_165         EQU     2
MICRON_TRCD_165         EQU     3
MICRON_TRP_165          EQU     3
MICRON_TRAS_165         EQU     7
MICRON_TRC_165         	EQU     10
MICRON_TRFC_165        	EQU     21
MICRON_V_ACTIMA_165 	EQU	((MICRON_TRFC_165 << 27) :OR: (MICRON_TRC_165 << 22) :OR: (MICRON_TRAS_165 << 18) :OR: (MICRON_TRP_165 << 15) :OR: (MICRON_TRCD_165 << 12) :OR:(MICRON_TRRD_165 << 9) :OR: (MICRON_TDPL_165 << 6) :OR: (MICRON_TDAL_165))

MICRON_TWTR_165   	EQU	1
MICRON_TCKE_165   	EQU	1
MICRON_TXP_165    	EQU	5
MICRON_XSR_165    	EQU	23
MICRON_V_ACTIMB_165 	EQU	((MICRON_TCKE_165 << 12) :OR: (MICRON_XSR_165 << 0)) :OR: (MICRON_TXP_165 << 8) :OR: (MICRON_TWTR_165 << 16)

; Micron part (200MHz optimized) 5 ns
  
MICRON_TDAL_200   	EQU	6
MICRON_TDPL_200   	EQU	3
MICRON_TRRD_200   	EQU	2
MICRON_TRCD_200         EQU     3
MICRON_TRP_200          EQU     3
MICRON_TRAS_200         EQU     8
MICRON_TRC_200         	EQU     11
MICRON_TRFC_200        	EQU     15
MICRON_V_ACTIMA_200 	EQU	((MICRON_TRFC_200 << 27) :OR: (MICRON_TRC_200 << 22) :OR: (MICRON_TRAS_200 << 18) :OR: (MICRON_TRP_200 << 15) :OR: (MICRON_TRCD_200 << 12) :OR:(MICRON_TRRD_200 << 9) :OR: (MICRON_TDPL_200 << 6) :OR: (MICRON_TDAL_200))

MICRON_TWTR_200         EQU     2
MICRON_TCKE_200         EQU     4
MICRON_TXP_200          EQU     2
MICRON_XSR_200         	EQU     23
MICRON_V_ACTIMB_200 	EQU	((MICRON_TCKE_200 << 12) :OR: (MICRON_XSR_200 << 0)) :OR: (MICRON_TXP_200 << 8) :OR: (MICRON_TWTR_200 << 16)

; NUMONYX part of IGEP0020 (165MHz optimized) 6.06ns
;   ACTIMA
;      TDAL = Twr/Tck + Trp/tck = 15/6 + 18/6 = 2.5 + 3 = 5.5 -> 6
;      TDPL (Twr) = 15/6 = 2.5 -> 3
;      TRRD = 12/6 = 2
;      TRCD = 22.5/6 = 3.75 -> 4
;      TRP  = 18/6 = 3
;      TRAS = 42/6 = 7
;      TRC  = 60/6 = 10
;      TRFC = 140/6 = 23.3 -> 24
;   ACTIMB
;	TWTR = 2
;	TCKE = 2
;	TXSR = 200/6 =  33.3 -> 34
;	TXP  = 1.0 + 1.1 = 2.1 -> 3 ¿?
 
NUMONYX_TDAL_165   	EQU	6
NUMONYX_TDPL_165   	EQU	3
NUMONYX_TRRD_165   	EQU	2
NUMONYX_TRCD_165        EQU     4
NUMONYX_TRP_165         EQU     3
NUMONYX_TRAS_165        EQU     7
NUMONYX_TRC_165        	EQU     10
NUMONYX_TRFC_165       	EQU     24
NUMONYX_V_ACTIMA_165 	EQU	((NUMONYX_TRFC_165 << 27) :OR: (NUMONYX_TRC_165 << 22) :OR: (NUMONYX_TRAS_165 << 18) :OR: (NUMONYX_TRP_165 << 15) :OR: (NUMONYX_TRCD_165 << 12) :OR:(NUMONYX_TRRD_165 << 9) :OR: (NUMONYX_TDPL_165 << 6) :OR: (NUMONYX_TDAL_165))

NUMONYX_TWTR_165        EQU     2
NUMONYX_TCKE_165        EQU     2
NUMONYX_TXP_165         EQU     3
NUMONYX_XSR_165         EQU     34
NUMONYX_V_ACTIMB_165 	EQU	((NUMONYX_TCKE_165 << 12) :OR: (NUMONYX_XSR_165 << 0)) :OR: (NUMONYX_TXP_165 << 8) :OR: (NUMONYX_TWTR_165 << 16)

;
; Hynix part of Overo (165MHz optimized) 6.06ns
;   ACTIMA
;     ACTIMA
;        TDAL = Twr/Tck + Trp/tck = 15/6 + 18/6 = 2.5 + 3 = 5.5 -> 6
;        TDPL (Twr) = 15/6       = 2.5 -> 3
;        TRRD = 12/6     = 2
;        TRCD = 18/6     = 3
;        TRP = 18/6      = 3
;        TRAS = 42/6     = 7
;        TRC = 60/6      = 10
;        TRFC = 97.5/6    = 17
;     ACTIMB
;        TWTR = 1
;        TCKE = 1
;        TXP = 1+1
;        XSR = 140/6 = 24
 
HYNIX_TDAL_165 		EQU	6
HYNIX_TDPL_165          EQU	3
HYNIX_TRRD_165          EQU     2
HYNIX_TRCD_165          EQU     3
HYNIX_TRP_165           EQU     3
HYNIX_TRAS_165          EQU     7
HYNIX_TRC_165    	EQU     10
HYNIX_TRFC_165         	EQU     21
HYNIX_V_ACTIMA_165 	EQU	((HYNIX_TRFC_165 << 27) :OR: (HYNIX_TRC_165 << 22) :OR: (HYNIX_TRAS_165 << 18) :OR: (HYNIX_TRP_165 << 15) :OR: (HYNIX_TRCD_165 << 12) :OR: (HYNIX_TRRD_165 << 9) :OR: (HYNIX_TDPL_165 << 6) :OR: (HYNIX_TDAL_165))

HYNIX_TWTR_165   	EQU	1
HYNIX_TCKE_165   	EQU	1
HYNIX_TXP_165    	EQU	2
HYNIX_XSR_165    	EQU	24
HYNIX_V_ACTIMB_165 	EQU	((HYNIX_TCKE_165 << 12) :OR: (HYNIX_XSR_165 << 0) :OR: (HYNIX_TXP_165 << 8) :OR: (HYNIX_TWTR_165 << 16))

; New and compatability speed defines 
    IF	:DEF:PRCM_CLK_CFG2_200MHZ || :DEF:PRCM_CONFIG_II || :DEF:PRCM_CONFIG_5B
L3_100MHZ	EQU	1	; Use with <= 100MHz SDRAM 
    ELIF :DEF:PRCM_CLK_CFG2_266MHZ || :DEF:PRCM_CONFIG_III || :DEF:PRCM_CONFIG_5A
L3_133MHZ	EQU	1	; Use with <= 133MHz SDRAM
    ELIF :DEF:PRCM_CLK_CFG2_332MHZ || :DEF:PRCM_CONFIG_I || :DEF:PRCM_CONFIG_2
L3_165MHZ	EQU	1	; Use with <= 165MHz SDRAM (L3=166 on 3430) 
    ENDIF

    IF :DEF:L3_100MHZ
MICRON_SDRC_ACTIM_CTRLA_0	EQU	MICRON_V_ACTIMA_100
MICRON_SDRC_ACTIM_CTRLB_0	EQU	MICRON_V_ACTIMB_100
    ELIF :DEF:L3_133MHZ
MICRON_SDRC_ACTIM_CTRLA_0     	EQU	MICRON_V_ACTIMA_133
MICRON_SDRC_ACTIM_CTRLB_0     	EQU	MICRON_V_ACTIMB_133
    ELIF :DEF:L3_165MHZ
MICRON_SDRC_ACTIM_CTRLA_0  	EQU	MICRON_V_ACTIMA_165
MICRON_SDRC_ACTIM_CTRLB_0     	EQU	MICRON_V_ACTIMB_165
NUMONYX_SDRC_ACTIM_CTRLA_0    	EQU	NUMONYX_V_ACTIMA_165
NUMONYX_SDRC_ACTIM_CTRLB_0    	EQU	NUMONYX_V_ACTIMB_165
    ENDIF

    IF :DEF:L3_100MHZ
INFINEON_SDRC_ACTIM_CTRLA_0  	EQU	INFINEON_V_ACTIMA_100
INFINEON_SDRC_ACTIM_CTRLB_0     EQU	INFINEON_V_ACTIMB_100
    ELIF :DEF:L3_133MHZ
INFINEON_SDRC_ACTIM_CTRLA_0    	EQU	INFINEON_V_ACTIMA_133
INFINEON_SDRC_ACTIM_CTRLB_0    	EQU	INFINEON_V_ACTIMB_133
    ELIF :DEF:L3_165MHZ
INFINEON_SDRC_ACTIM_CTRLA_0    	EQU	INFINEON_V_ACTIMA_165
INFINEON_SDRC_ACTIM_CTRLB_0    	EQU	INFINEON_V_ACTIMB_165
    ENDIF

    IF :DEF:L3_100MHZ
SDP_SDRC_RFR_CTRL          	EQU	SDP_3430_SDRC_RFR_CTRL_100MHz
    ELIF :DEF:L3_133MHZ
SDP_SDRC_RFR_CTRL          	EQU	SDP_3430_SDRC_RFR_CTRL_133MHz
    ELIF :DEF:L3_165MHZ
SDP_SDRC_RFR_CTRL          	EQU	SDP_3430_SDRC_RFR_CTRL_165MHz
    ENDIF

;
; GPMC settings -
; Definitions is as per the following format
;  <PART>_GPMC_CONFIG<x> <value>
; Where:
; PART is the part name e.g. STNOR - Intel Strata Flash
; x is GPMC config registers from 1 to 6 (there will be 6 macros)
; Value is corresponding value
;
; For every valid PRCM configuration there should be only one definition of
; the same. if values are independent of the board, this definition will be
; present in this file if values are dependent on the board, then this should
; go into corresponding mem-boardName.h file
;
; Currently valid part Names are (PART):
; STNOR - Intel Strata Flash
; SMNAND - Samsung NAND
; M_NAND - Micron Large page x16 NAND
; MPDB - H4 MPDB board
; SBNOR - Sibley NOR
; ONNAND - Samsung One NAND
;
; include/configs/file.h contains the defn - for all CS we are interested
; OMAP34XX_GPMC_CSx PART
; OMAP34XX_GPMC_CSx_SIZE Size
; OMAP34XX_GPMC_CSx_MAP Map
; Where:
; x - CS number
; PART - Part Name as defined above
; SIZE - how big is the mapping to be
;   GPMC_SIZE_128M - 0x8
;   GPMC_SIZE_64M  - 0xC
;   GPMC_SIZE_32M  - 0xE
;   GPMC_SIZE_16M  - 0xF
; MAP  - Map this CS to which address(GPMC address space)- Absolute address
;   >>24 before being used.
; 

GPMC_SIZE_128M	EQU	0x8
GPMC_SIZE_64M   EQU	0xC
GPMC_SIZE_32M   EQU	0xE
GPMC_SIZE_16M   EQU	0xF

    IF	:DEF:L3_100MHZ
SMNAND_GPMC_CONFIG1 	EQU	0x0
SMNAND_GPMC_CONFIG2 	EQU	0x00141400
SMNAND_GPMC_CONFIG3     EQU     0x00141400
SMNAND_GPMC_CONFIG4     EQU     0x0F010F01
SMNAND_GPMC_CONFIG5     EQU     0x010C1414
SMNAND_GPMC_CONFIG6     EQU     0x00000A80

M_NAND_GPMC_CONFIG1     EQU     0x00001800
M_NAND_GPMC_CONFIG2     EQU     SMNAND_GPMC_CONFIG2
M_NAND_GPMC_CONFIG3     EQU     SMNAND_GPMC_CONFIG3
M_NAND_GPMC_CONFIG4     EQU     SMNAND_GPMC_CONFIG4
M_NAND_GPMC_CONFIG5     EQU     SMNAND_GPMC_CONFIG5
M_NAND_GPMC_CONFIG6     EQU     SMNAND_GPMC_CONFIG6
STNOR_GPMC_CONFIG1      EQU     0x3
STNOR_GPMC_CONFIG2      EQU     0x000f0f01
STNOR_GPMC_CONFIG3      EQU     0x00050502
STNOR_GPMC_CONFIG4      EQU     0x0C060C06
STNOR_GPMC_CONFIG5      EQU     0x01131F1F
STNOR_GPMC_CONFIG6      EQU     0x0  ; 0? 
MPDB_GPMC_CONFIG1       EQU     0x00011000
MPDB_GPMC_CONFIG2       EQU     0x001F1F00
MPDB_GPMC_CONFIG3       EQU     0x00080802
MPDB_GPMC_CONFIG4       EQU     0x1C091C09
MPDB_GPMC_CONFIG5       EQU     0x031A1F1F
MPDB_GPMC_CONFIG6       EQU     0x000003C2
    ENDIF

    IF	:DEF:L3_133MHZ
 SMNAND_GPMC_CONFIG1 0x00000800
 SMNAND_GPMC_CONFIG2 0x00141400
 SMNAND_GPMC_CONFIG3 0x00141400
 SMNAND_GPMC_CONFIG4 0x0F010F01
 SMNAND_GPMC_CONFIG5 0x010C1414
 SMNAND_GPMC_CONFIG6 0x00000A80
 SMNAND_GPMC_CONFIG7 0x00000C44

 M_NAND_GPMC_CONFIG1 0x00001800
 M_NAND_GPMC_CONFIG2 SMNAND_GPMC_CONFIG2
 M_NAND_GPMC_CONFIG3 SMNAND_GPMC_CONFIG3
 M_NAND_GPMC_CONFIG4 SMNAND_GPMC_CONFIG4
 M_NAND_GPMC_CONFIG5 SMNAND_GPMC_CONFIG5
 M_NAND_GPMC_CONFIG6 SMNAND_GPMC_CONFIG6
 M_NAND_GPMC_CONFIG7 SMNAND_GPMC_CONFIG7

 STNOR_GPMC_CONFIG1  0x1203
 STNOR_GPMC_CONFIG2  0x00151501
 STNOR_GPMC_CONFIG3  0x00060602
 STNOR_GPMC_CONFIG4  0x10081008
 STNOR_GPMC_CONFIG5  0x01131F1F
 STNOR_GPMC_CONFIG6  0x000004c4

 SIBNOR_GPMC_CONFIG1  0x1200
 SIBNOR_GPMC_CONFIG2  0x001f1f00
 SIBNOR_GPMC_CONFIG3  0x00080802
 SIBNOR_GPMC_CONFIG4  0x1C091C09
 SIBNOR_GPMC_CONFIG5  0x01131F1F
 SIBNOR_GPMC_CONFIG6  0x000003C2

 MPDB_GPMC_CONFIG1  0x00011000
 MPDB_GPMC_CONFIG2  0x001f1f01
 MPDB_GPMC_CONFIG3  0x00080803
 MPDB_GPMC_CONFIG4  0x1C091C09
 MPDB_GPMC_CONFIG5  0x041f1F1F
 MPDB_GPMC_CONFIG6  0x000004C4

 P2_GPMC_CONFIG1  0x0
 P2_GPMC_CONFIG2  0x0
 P2_GPMC_CONFIG3  0x0
 P2_GPMC_CONFIG4  0x0
 P2_GPMC_CONFIG5  0x0
 P2_GPMC_CONFIG6  0x0

ONENAND_GPMC_CONFIG1 0x00001200
ONENAND_GPMC_CONFIG2 0x000c0c01
ONENAND_GPMC_CONFIG3 0x00030301
ONENAND_GPMC_CONFIG4 0x0c040c04
ONENAND_GPMC_CONFIG5 0x010C1010
ONENAND_GPMC_CONFIG6 0x00000000
    ENDIF	; L3_133MHZ

    IF	:DEF:L3_165MHZ
SMNAND_GPMC_CONFIG1 	EQU	0x00000800
SMNAND_GPMC_CONFIG2 	EQU	0x00141400
SMNAND_GPMC_CONFIG3 	EQU	0x00141400
SMNAND_GPMC_CONFIG4     EQU     0x0F010F01
SMNAND_GPMC_CONFIG5     EQU     0x010C1414
SMNAND_GPMC_CONFIG6     EQU     0x1F0F0A80
SMNAND_GPMC_CONFIG7     EQU     0x00000C44

M_NAND_GPMC_CONFIG1     EQU     0x00001800
M_NAND_GPMC_CONFIG2     EQU     SMNAND_GPMC_CONFIG2
M_NAND_GPMC_CONFIG3     EQU     SMNAND_GPMC_CONFIG3
M_NAND_GPMC_CONFIG4     EQU     SMNAND_GPMC_CONFIG4
M_NAND_GPMC_CONFIG5     EQU     SMNAND_GPMC_CONFIG5
M_NAND_GPMC_CONFIG6     EQU     SMNAND_GPMC_CONFIG6
M_NAND_GPMC_CONFIG7     EQU     SMNAND_GPMC_CONFIG7

STNOR_GPMC_CONFIG1      EQU     0x3
STNOR_GPMC_CONFIG2      EQU     0x00151501
STNOR_GPMC_CONFIG3      EQU     0x00060602
STNOR_GPMC_CONFIG4      EQU     0x11091109
STNOR_GPMC_CONFIG5      EQU     0x01141F1F
STNOR_GPMC_CONFIG6      EQU     0x000004c4

SIBNOR_GPMC_CONFIG1     EQU     0x1200
SIBNOR_GPMC_CONFIG2     EQU     0x001f1f00
SIBNOR_GPMC_CONFIG3     EQU     0x00080802
SIBNOR_GPMC_CONFIG4     EQU     0x1C091C09
SIBNOR_GPMC_CONFIG5     EQU     0x01131F1F
SIBNOR_GPMC_CONFIG6     EQU	0x1F0F03C2

SDPV2_MPDB_GPMC_CONFIG1    EQU  0x00611200
SDPV2_MPDB_GPMC_CONFIG2    EQU  0x001F1F01
SDPV2_MPDB_GPMC_CONFIG3    EQU  0x00080803
SDPV2_MPDB_GPMC_CONFIG4    EQU  0x1D091D09
SDPV2_MPDB_GPMC_CONFIG5    EQU  0x041D1F1F
SDPV2_MPDB_GPMC_CONFIG6    EQU	0x1D0904C4

MPDB_GPMC_CONFIG1  	EQU	0x00011000
MPDB_GPMC_CONFIG2  	EQU	0x001f1f01
MPDB_GPMC_CONFIG3	EQU	0x00080803
MPDB_GPMC_CONFIG4  	EQU	0x1c0b1c0a
MPDB_GPMC_CONFIG5  	EQU	0x041f1F1F
MPDB_GPMC_CONFIG6  	EQU	0x1F0F04C4

P2_GPMC_CONFIG1	EQU	0x0
P2_GPMC_CONFIG2	EQU	0x0
P2_GPMC_CONFIG3 EQU	0x0
P2_GPMC_CONFIG4 EQU	0x0
P2_GPMC_CONFIG5 EQU	0x0
P2_GPMC_CONFIG6 EQU	0x0

ONENAND_GPMC_CONFIG1	EQU	0x00001200
ONENAND_GPMC_CONFIG2    EQU     0x000F0F01
ONENAND_GPMC_CONFIG3    EQU     0x00030301
ONENAND_GPMC_CONFIG4    EQU     0x0F040F04
ONENAND_GPMC_CONFIG5    EQU     0x010F1010
ONENAND_GPMC_CONFIG6    EQU  	0x1F060000

    ENDIF

; max number of GPMC Chip Selects 
GPMC_MAX_CS	EQU	8

; max number of GPMC regs 
GPMC_MAX_REG   	EQU	7

PISMO1_NOR  	EQU	1
PISMO1_NAND     EQU	2
PISMO2_CS0  	EQU	3
PISMO2_CS1  	EQU	4
PISMO1_ONENAND  EQU	5
POP_ONENAND	EQU	5
DBG_MPDB       	EQU	6
PISMO2_NAND_CS0 EQU	7
PISMO2_NAND_CS1 EQU	8

; make it readable for the gpmc_init 
PISMO1_NOR_BASE		EQU	FLASH_BASE
PISMO1_NAND_BASE	EQU	NAND_BASE
;PISMO2_CS0_BASE		EQU	PISMO2_MAP1
PISMO1_ONEN_BASE	EQU	ONENAND_MAP
POP_ONEN_BASE  		EQU 	ONENAND_MAP
DBG_MPDB_BASE 		EQU  	DEBUG_BASE

    END