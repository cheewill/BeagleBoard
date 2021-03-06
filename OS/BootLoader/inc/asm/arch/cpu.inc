;
; (C) Copyright 2006
; Texas Instruments, <www.ti.com>
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

; GPMC Mapping
FLASH_BASE		EQU     0x10000000  ; NOR flash (aligned to 256 Meg) 
FLASH_BASE_SDPV1	EQU     0x04000000  ; NOR flash (aligned to 64 Meg) 
FLASH_BASE_SDPV2	EQU     0x10000000  ; NOR flash (aligned to 256 Meg) 
DEBUG_BASE		EQU     0x08000000  ; debug board 
NAND_BASE		EQU     0x30000000  ; NAND addr (actual size small port)
PISMO2_BASE		EQU     0x18000000  ; PISMO2 CS1/2 
ONENAND_MAP		EQU     0x20000000  ; OneNand addr (actual size small port 

    INCLUDE	omap3430.inc

; Register offsets of common modules
; Control
CONTROL_STATUS	EQU	(OMAP34XX_CTRL_BASE + 0x2F0)
OMAP34XX_MCR	EQU	(OMAP34XX_CTRL_BASE + 0x8C)

CONTROL_SCALABLE_OMAP_STATUS	EQU	(OMAP34XX_CTRL_BASE + 0x44C)
CONTROL_SCALABLE_OMAP_OCP	EQU	(OMAP34XX_CTRL_BASE + 0x534)


; Tap Information 
TAP_IDCODE_REG		EQU	(OMAP34XX_TAP_BASE+0x204)
PRODUCTION_ID		EQU	(OMAP34XX_TAP_BASE+0x208)

; device type
DEVICE_MASK		EQU     (BIT8:OR:BIT9:OR:BIT10)
TST_DEVICE		EQU     0x0
EMU_DEVICE		EQU     0x1
HS_DEVICE		EQU     0x2
GP_DEVICE		EQU     0x3

; We are not concerned with BIT5 as it only determines
; the prirotiy between memory or perpheral booting 

SYSBOOT_MASK		EQU     (BIT0:OR:BIT1:OR:BIT2:OR:BIT3:OR:BIT4)

; GPMC CS3/cs4/cs6 not avaliable
GPMC_BASE		EQU     (OMAP34XX_GPMC_BASE)
GPMC_SYSCONFIG		EQU     (OMAP34XX_GPMC_BASE+0x10)
GPMC_IRQSTATUS		EQU     (OMAP34XX_GPMC_BASE+0x18)
GPMC_IRQENABLE		EQU     (OMAP34XX_GPMC_BASE+0x1C)
GPMC_TIMEOUT_CONTROL	EQU     (OMAP34XX_GPMC_BASE+0x40)
GPMC_CONFIG		EQU     (OMAP34XX_GPMC_BASE+0x50)
GPMC_STATUS		EQU     (OMAP34XX_GPMC_BASE+0x54)

GPMC_CONFIG_CS0		EQU     (OMAP34XX_GPMC_BASE+0x60)
GPMC_CONFIG_WIDTH	EQU     (0x30)

GPMC_CONFIG1		EQU     (0x00)
GPMC_CONFIG2		EQU     (0x04)
GPMC_CONFIG3		EQU     (0x08)
GPMC_CONFIG4		EQU     (0x0C)
GPMC_CONFIG5		EQU     (0x10)
GPMC_CONFIG6		EQU     (0x14)
GPMC_CONFIG7		EQU     (0x18)
GPMC_NAND_CMD		EQU     (0x1C)
GPMC_NAND_ADR		EQU     (0x20)
GPMC_NAND_DAT		EQU     (0x24)

GPMC_ECC_CONFIG		EQU     (0x1F4)
GPMC_ECC_CONTROL	EQU     (0x1F8)
GPMC_ECC_SIZE_CONFIG	EQU     (0x1FC)
GPMC_ECC1_RESULT	EQU     (0x200)
GPMC_ECC2_RESULT	EQU     (0x204)
GPMC_ECC3_RESULT	EQU     (0x208)
GPMC_ECC4_RESULT	EQU     (0x20C)
GPMC_ECC5_RESULT	EQU     (0x210)
GPMC_ECC6_RESULT	EQU     (0x214)
GPMC_ECC7_RESULT	EQU     (0x218)
GPMC_ECC8_RESULT	EQU     (0x21C)
GPMC_ECC9_RESULT	EQU     (0x220)

; SMS 
SMS_SYSCONFIG		EQU     (OMAP34XX_SMS_BASE+0x10)
SMS_RG_ATT0		EQU     (OMAP34XX_SMS_BASE+0x48)
SMS_CLASS_ARB0		EQU     (OMAP34XX_SMS_BASE+0xD0)
BURSTCOMPLETE_GROUP7	EQU     BIT31

; SDRC 
SDRC_SYSCONFIG		EQU     (OMAP34XX_SDRC_BASE+0x10)
SDRC_STATUS		EQU     (OMAP34XX_SDRC_BASE+0x14)
SDRC_CS_CFG		EQU     (OMAP34XX_SDRC_BASE+0x40)
SDRC_SHARING		EQU     (OMAP34XX_SDRC_BASE+0x44)
SDRC_DLLA_CTRL		EQU     (OMAP34XX_SDRC_BASE+0x60)
SDRC_DLLA_STATUS	EQU     (OMAP34XX_SDRC_BASE+0x64)
SDRC_DLLB_CTRL		EQU     (OMAP34XX_SDRC_BASE+0x68)
SDRC_DLLB_STATUS	EQU     (OMAP34XX_SDRC_BASE+0x6C)
DLLPHASE		EQU     BIT1
LOADDLL			EQU     BIT2
DLL_DELAY_MASK		EQU     0xFF00
DLL_NO_FILTER_MASK	EQU     (BIT8|BIT9)

SDRC_POWER		EQU     (OMAP34XX_SDRC_BASE+0x70)
WAKEUPPROC		EQU     BIT26

SDRC_MCFG_0		EQU     (OMAP34XX_SDRC_BASE+0x80)
SDRC_MCFG_1		EQU     (OMAP34XX_SDRC_BASE+0xB0)
SDRC_MR_0		EQU     (OMAP34XX_SDRC_BASE+0x84)
SDRC_MR_1		EQU     (OMAP34XX_SDRC_BASE+0xB4)
SDRC_ACTIM_CTRLA_0	EQU     (OMAP34XX_SDRC_BASE+0x9C)
SDRC_ACTIM_CTRLB_0	EQU     (OMAP34XX_SDRC_BASE+0xA0)
SDRC_ACTIM_CTRLA_1	EQU     (OMAP34XX_SDRC_BASE+0xC4)
SDRC_ACTIM_CTRLB_1	EQU     (OMAP34XX_SDRC_BASE+0xC8)
SDRC_RFR_CTRL_0		EQU     (OMAP34XX_SDRC_BASE+0xA4)
SDRC_RFR_CTRL_1		EQU     (OMAP34XX_SDRC_BASE+0xD4)
SDRC_MANUAL_0		EQU     (OMAP34XX_SDRC_BASE+0xA8)
SDRC_MANUAL_1		EQU     (OMAP34XX_SDRC_BASE+0xD8)
OMAP34XX_SDRC_CS0	EQU     0x80000000
OMAP34XX_SDRC_CS1	EQU     0xA0000000
CMD_NOP			EQU     0x0
CMD_PRECHARGE		EQU     0x1
CMD_AUTOREFRESH		EQU     0x2
CMD_ENTR_PWRDOWN	EQU     0x3
CMD_EXIT_PWRDOWN	EQU     0x4
CMD_ENTR_SRFRSH		EQU     0x5
CMD_CKE_HIGH		EQU     0x6
CMD_CKE_LOW		EQU     0x7
SOFTRESET		EQU     BIT1
SMART_IDLE		EQU     (0x2 << 3)
REF_ON_IDLE		EQU     (0x1 << 6)

; timer regs offsets (32 bit regs) 
TIDR			EQU     0x0      ; r 
TIOCP_CFG		EQU     0x10     ; rw 
TISTAT			EQU     0x14     ; r 
TISR			EQU     0x18     ; rw 
TIER			EQU     0x1C     ; rw 
TWER			EQU     0x20     ; rw 
TCLR			EQU     0x24     ; rw 
TCRR			EQU     0x28     ; rw 
TLDR			EQU     0x2C     ; rw 
TTGR			EQU     0x30     ; rw 
TWPS			EQU     0x34     ; r 
TMAR			EQU     0x38     ; rw 
TCAR1			EQU     0x3c     ; r 
TSICR			EQU     0x40     ; rw 
TCAR2			EQU     0x44     ; r 
GPT_EN			EQU     ((0<<2):OR:BIT1:OR:BIT0) ; enable sys_clk NO-prescale /1 

; Watchdog 
WWPS			EQU     0x34     ; r 
WSPR			EQU     0x48     ; rw 
WD_UNLOCK1		EQU     0xAAAA
WD_UNLOCK2		EQU     0x5555

; PRCM 
CM_FCLKEN_IVA2      	EQU     0x48004000
CM_CLKEN_PLL_IVA2   	EQU     0x48004004
CM_IDLEST_PLL_IVA2  	EQU     0x48004024
CM_CLKSEL1_PLL_IVA2     EQU     0x48004040
CM_CLKSEL2_PLL_IVA2     EQU     0x48004044
CM_CLKEN_PLL_MPU        EQU     0x48004904
CM_IDLEST_PLL_MPU       EQU     0x48004924
CM_CLKSEL1_PLL_MPU      EQU     0x48004940
CM_CLKSEL2_PLL_MPU      EQU     0x48004944
CM_FCLKEN1_CORE         EQU     0x48004a00
CM_ICLKEN1_CORE         EQU     0x48004a10
CM_ICLKEN2_CORE         EQU     0x48004a14
CM_CLKSEL_CORE          EQU     0x48004a40
CM_FCLKEN_GFX           EQU     0x48004b00
CM_ICLKEN_GFX           EQU     0x48004b10
CM_CLKSEL_GFX           EQU     0x48004b40
CM_FCLKEN_WKUP          EQU     0x48004c00
CM_ICLKEN_WKUP          EQU     0x48004c10
CM_CLKSEL_WKUP          EQU     0x48004c40
CM_IDLEST_WKUP          EQU     0x48004c20
CM_CLKEN_PLL            EQU     0x48004d00
CM_IDLEST_CKGEN         EQU     0x48004d20
CM_CLKSEL1_PLL          EQU     0x48004d40
CM_CLKSEL2_PLL          EQU     0x48004d44
CM_CLKSEL3_PLL          EQU     0x48004d48
CM_FCLKEN_DSS           EQU     0x48004e00
CM_ICLKEN_DSS           EQU     0x48004e10
CM_CLKSEL_DSS           EQU     0x48004e40
CM_FCLKEN_CAM           EQU     0x48004f00
CM_ICLKEN_CAM           EQU     0x48004f10
CM_CLKSEL_CAM           EQU     0x48004F40
CM_FCLKEN_PER           EQU     0x48005000
CM_ICLKEN_PER           EQU     0x48005010
CM_CLKSEL_PER           EQU     0x48005040
CM_CLKSEL1_EMU          EQU     0x48005140

PRM_CLKSEL              EQU      0x48306d40
PRM_RSTCTRL             EQU      0x48307250
PRM_CLKSRC_CTRL         EQU      0x48307270

SYSCLKDIV_2	        EQU         (0x1 << 7)

; SMX-APE 
PM_RT_APE_BASE_ADDR_ARM		EQU	(SMX_APE_BASE + 0x10000)
PM_GPMC_BASE_ADDR_ARM		EQU	(SMX_APE_BASE + 0x12400)
PM_OCM_RAM_BASE_ADDR_ARM	EQU	(SMX_APE_BASE + 0x12800)
PM_OCM_ROM_BASE_ADDR_ARM	EQU	(SMX_APE_BASE + 0x12C00)
PM_IVA2_BASE_ADDR_ARM		EQU	(SMX_APE_BASE + 0x14000)

RT_REQ_INFO_PERMISSION_1	EQU	(PM_RT_APE_BASE_ADDR_ARM + 0x68)
RT_READ_PERMISSION_0		EQU	(PM_RT_APE_BASE_ADDR_ARM + 0x50)
RT_WRITE_PERMISSION_0		EQU	(PM_RT_APE_BASE_ADDR_ARM + 0x58)
RT_ADDR_MATCH_1			EQU	(PM_RT_APE_BASE_ADDR_ARM + 0x60)

GPMC_REQ_INFO_PERMISSION_0	EQU	(PM_GPMC_BASE_ADDR_ARM + 0x48)
GPMC_READ_PERMISSION_0		EQU	(PM_GPMC_BASE_ADDR_ARM + 0x50)
GPMC_WRITE_PERMISSION_0		EQU	(PM_GPMC_BASE_ADDR_ARM + 0x58)

OCM_REQ_INFO_PERMISSION_0	EQU	(PM_OCM_RAM_BASE_ADDR_ARM + 0x48)
OCM_READ_PERMISSION_0		EQU	(PM_OCM_RAM_BASE_ADDR_ARM + 0x50)
OCM_WRITE_PERMISSION_0		EQU	(PM_OCM_RAM_BASE_ADDR_ARM + 0x58)
OCM_ADDR_MATCH_2		EQU	(PM_OCM_RAM_BASE_ADDR_ARM + 0x80)

IVA2_REQ_INFO_PERMISSION_0	EQU	(PM_IVA2_BASE_ADDR_ARM + 0x48)
IVA2_READ_PERMISSION_0		EQU	(PM_IVA2_BASE_ADDR_ARM + 0x50)
IVA2_WRITE_PERMISSION_0		EQU	(PM_IVA2_BASE_ADDR_ARM + 0x58)

IVA2_REQ_INFO_PERMISSION_1	EQU	(PM_IVA2_BASE_ADDR_ARM + 0x68)
IVA2_READ_PERMISSION_1		EQU	(PM_IVA2_BASE_ADDR_ARM + 0x70)
IVA2_WRITE_PERMISSION_1		EQU	(PM_IVA2_BASE_ADDR_ARM + 0x78)

IVA2_REQ_INFO_PERMISSION_2	EQU	(PM_IVA2_BASE_ADDR_ARM + 0x88)
IVA2_READ_PERMISSION_2		EQU	(PM_IVA2_BASE_ADDR_ARM + 0x90)
IVA2_WRITE_PERMISSION_2		EQU	(PM_IVA2_BASE_ADDR_ARM + 0x98)

IVA2_REQ_INFO_PERMISSION_3	EQU	(PM_IVA2_BASE_ADDR_ARM + 0xA8)
IVA2_READ_PERMISSION_3		EQU	(PM_IVA2_BASE_ADDR_ARM + 0xB0)
IVA2_WRITE_PERMISSION_3		EQU	(PM_IVA2_BASE_ADDR_ARM + 0xB8)

; I2C base 
I2C_BASE1		EQU	(OMAP34XX_CORE_L4_IO_BASE + 0x70000)
I2C_BASE2		EQU	(OMAP34XX_CORE_L4_IO_BASE + 0x72000)
I2C_BASE3		EQU	(OMAP34XX_CORE_L4_IO_BASE + 0x60000)

    END
