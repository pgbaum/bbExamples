# Information from
#
# AM335x ARM CortexTM-A8 Microprocessors
# (MPUs) Technical Reference Manual
# http://www.ti.com/lit/ds/symlink/am3358.pdf
# 7.4.5 ELM Registers
#
# SitaraTM AM335x ARM CortexTM-A8 Microprocessors (MPUs)
# http://www.ti.com/lit/ug/spruh73j/spruh73j.pdf
# Table 2-7. Ball Characteristics (ZCE and ZCZ Packages)
# 
# BeagleBone Black System Reference Manual
# https://github.com/CircuitCo/BeagleBone-Black/blob/master/BBB_SRM.pdf
# Table 12: Expansion Header P8 Pinout
# Table 13: Expansion Header P9 Pinout

# address, MODE0, MODE7, Header Pin
mux = [
   ( 0x800, "conf_gpmc_ad0", "gpio1_0", "P8.25" ),
   ( 0x804, "conf_gpmc_ad1", "gpio1_1", "P8.24" ),
   ( 0x808, "conf_gpmc_ad2", "gpio1_2", "P8.5" ),
   ( 0x80C, "conf_gpmc_ad3", "gpio1_3", "P8.6" ),
   ( 0x810, "conf_gpmc_ad4", "gpio1_4", "P8.23" ),
   ( 0x814, "conf_gpmc_ad5", "gpio1_5", "P8.22" ),
   ( 0x818, "conf_gpmc_ad6", "gpio1_6", "P8.3" ),
   ( 0x81C, "conf_gpmc_ad7", "gpio1_7", "P8.4" ),
   ( 0x820, "conf_gpmc_ad8", "gpio0_22", "P8.19" ),
   ( 0x824, "conf_gpmc_ad9", "gpio0_23", "P8.13" ),
   ( 0x828, "conf_gpmc_ad10", "gpio0_26", "P8.14" ),
   ( 0x82C, "conf_gpmc_ad11", "gpio0_27", "P8.17" ),
   ( 0x830, "conf_gpmc_ad12", "gpio1_12", "P8.12" ),
   ( 0x834, "conf_gpmc_ad13", "gpio1_13", "P8.11" ),
   ( 0x838, "conf_gpmc_ad14", "gpio1_14", "P8.16" ),
   ( 0x83C, "conf_gpmc_ad15", "gpio1_15", "P8.15" ),
   ( 0x840, "conf_gpmc_a0", "gpio1_16", "P9.15" ),
   ( 0x844, "conf_gpmc_a1", "gpio1_17", "P9.23" ),
   ( 0x848, "conf_gpmc_a2", "gpio1_18", "P9.14" ),
   ( 0x84C, "conf_gpmc_a3", "gpio1_19", "P9.16" ),
   ( 0x850, "conf_gpmc_a4", "gpio1_20", "" ),
   ( 0x854, "conf_gpmc_a5", "gpio1_21", "" ),
   ( 0x858, "conf_gpmc_a6", "gpio1_22", "" ),
   ( 0x85C, "conf_gpmc_a7", "gpio1_23", "" ),
   ( 0x860, "conf_gpmc_a8", "gpio1_24", "" ),
   ( 0x864, "conf_gpmc_a9", "gpio1_25", "" ),
   ( 0x868, "conf_gpmc_a10", "gpio1_26", "" ),
   ( 0x86C, "conf_gpmc_a11", "gpio1_27", "" ),
   ( 0x870, "conf_gpmc_wait0", "gpio0_30", "P9.11" ),
   ( 0x874, "conf_gpmc_wpn", "gpio0_31", "P9.13" ),
   ( 0x878, "conf_gpmc_ben1", "gpio1_28", "P9.12" ),
   ( 0x87C, "conf_gpmc_csn0", "gpio1_29", "P8.26" ),
   ( 0x880, "conf_gpmc_csn1", "gpio1_30", "P8.21" ),
   ( 0x884, "conf_gpmc_csn2", "gpio1_31", "P8.20" ),
   ( 0x888, "conf_gpmc_csn3", "gpio2_0", "" ),
   ( 0x88C, "conf_gpmc_clk", "gpio2_1", "P8.18" ),
   ( 0x890, "conf_gpmc_advn_ale", "gpio2_2", "P8.7" ),
   ( 0x894, "conf_gpmc_oen_ren", "gpio2_3", "P8.8" ),
   ( 0x898, "conf_gpmc_wen", "gpio2_4", "P8.10" ),
   ( 0x89C, "conf_gpmc_ben0_cle", "gpio2_5", "P8.9" ),
   ( 0x8A0, "conf_lcd_data0", "gpio2_6", "P8.45" ),
   ( 0x8A4, "conf_lcd_data1", "gpio2_7", "P8.46" ),
   ( 0x8A8, "conf_lcd_data2", "gpio2_8", "P8.43" ),
   ( 0x8AC, "conf_lcd_data3", "gpio2_9", "P8.44" ),
   ( 0x8B0, "conf_lcd_data4", "gpio2_10", "P8.41" ),
   ( 0x8B4, "conf_lcd_data5", "gpio2_11", "P8.42" ),
   ( 0x8B8, "conf_lcd_data6", "gpio2_12", "P8.39" ),
   ( 0x8BC, "conf_lcd_data7", "gpio2_13", "P8.40" ),
   ( 0x8C0, "conf_lcd_data8", "gpio2_14", "P8.37" ),
   ( 0x8C4, "conf_lcd_data9", "gpio2_15", "P8.38" ),
   ( 0x8C8, "conf_lcd_data10", "gpio2_16", "P8.36" ),
   ( 0x8CC, "conf_lcd_data11", "gpio2_17", "P8.34" ),
   ( 0x8D0, "conf_lcd_data12", "gpio0_8", "P8.35" ),
   ( 0x8D4, "conf_lcd_data13", "gpio0_9", "P8.33" ),
   ( 0x8D8, "conf_lcd_data14", "gpio0_10", "P8.31" ),
   ( 0x8DC, "conf_lcd_data15", "gpio0_11", "P8.32" ),
   ( 0x8E0, "conf_lcd_vsync", "gpio2_22", "P8.27" ),
   ( 0x8E4, "conf_lcd_hsync", "gpio2_23", "P8.29" ),
   ( 0x8E8, "conf_lcd_pclk", "gpio2_24", "P8.28" ),
   ( 0x8EC, "conf_lcd_ac_bias_en", "gpio2_25", "P8.30" ),
   ( 0x8F0, "conf_mmc0_dat3", "gpio2_26", "" ),
   ( 0x8F4, "conf_mmc0_dat2", "gpio2_27", "" ),
   ( 0x8F8, "conf_mmc0_dat1", "gpio2_28", "" ),
   ( 0x8FC, "conf_mmc0_dat0", "gpio2_29", "" ),
   ( 0x900, "conf_mmc0_clk", "gpio2_30", "" ),
   ( 0x904, "conf_mmc0_cmd", "gpio2_32", "" ),
   ( 0x908, "conf_mii1_col", "gpio3_0", "" ),
   ( 0x90C, "conf_mii1_crs", "gpio3_1", "" ),
   ( 0x910, "conf_mii1_rx_er", "gpio3_2", "" ),
   ( 0x914, "conf_mii1_tx_en", "gpio3_3", "" ),
   ( 0x918, "conf_mii1_rx_dv", "gpio3_4", "" ),
   ( 0x91C, "conf_mii1_txd3", "gpio0_16", "" ),
   ( 0x920, "conf_mii1_txd2", "gpio0_17", "" ),
   ( 0x924, "conf_mii1_txd1", "gpio0_21", "" ),
   ( 0x928, "conf_mii1_txd0", "gpio0_28", "" ),
   ( 0x92C, "conf_mii1_tx_clk", "gpio3_9", "" ),
   ( 0x930, "conf_mii1_rx_clk", "gpio3_10", "" ),
   ( 0x934, "conf_mii1_rxd3", "gpio2_18", "" ),
   ( 0x938, "conf_mii1_rxd2", "gpio2_19", "" ),
   ( 0x93C, "conf_mii1_rxd1", "gpio2_20", "" ),
   ( 0x940, "conf_mii1_rxd0", "gpio2_21", "" ),
   ( 0x944, "conf_rmii1_ref_clk", "gpio0_29", "" ),
   ( 0x948, "conf_mdio", "gpio0_0", "" ),
   ( 0x94C, "conf_mdc", "gpio0_1", "" ),
   ( 0x950, "conf_spi0_sclk", "gpio0_2", "P9.22" ),
   ( 0x954, "conf_spi0_d0", "gpio0_3", "P9.21" ),
   ( 0x958, "conf_spi0_d1", "gpio0_4", "P9.18" ),
   ( 0x95C, "conf_spi0_cs0", "gpio0_5", "P9.17" ),
   ( 0x960, "conf_spi0_cs1", "gpio0_6", "" ),
   ( 0x964, "conf_ecap0_in_pwm0_out", "gpio0_7", "" ),
   ( 0x968, "conf_uart0_ctsn", "gpio1_8", "" ),
   ( 0x96C, "conf_uart0_rtsn", "gpio1_9", "" ),
   ( 0x970, "conf_uart0_rxd", "gpio1_10", "" ),
   ( 0x974, "conf_uart0_txd", "gpio1_11", "" ),
   ( 0x978, "conf_uart1_ctsn", "gpio0_12", "P9.20" ),
   ( 0x97C, "conf_uart1_rtsn", "gpio0_13", "P9.19" ),
   ( 0x980, "conf_uart1_rxd", "gpio0_14", "P9.26" ),
   ( 0x984, "conf_uart1_txd", "gpio0_15", "P9.24" ),
   ( 0x988, "conf_i2c0_sda", "gpio3_5", "" ),
   ( 0x98C, "conf_i2c0_scl", "gpio3_6", "" ),
   ( 0x990, "conf_mcasp0_aclkx", "gpio3_14", "P9.31" ),
   ( 0x994, "conf_mcasp0_fsx", "gpio3_15", "P9.29" ),
   ( 0x998, "conf_mcasp0_axr0", "gpio3_16", "P9.30" ),
   ( 0x99C, "conf_mcasp0_ahclkr", "gpio3_17", "P9.28" ),
   ( 0x9A0, "conf_mcasp0_aclkr", "gpio3_18", "" ),
   ( 0x9A4, "conf_mcasp0_fsr", "gpio3_19", "P9.27" ),
   ( 0x9A8, "conf_mcasp0_axr1", "gpio3_20", "" ),
   ( 0x9AC, "conf_mcasp0_ahclkx", "gpio3_21", "P9.25" ),
   ( 0x9B0, "conf_xdma_event_intr0", "gpio0_19", "" ),
   ( 0x9B4, "conf_xdma_event_intr1", "gpio0_20", "" ),
   ( 0x9B8, "conf_warmrstn", "", "" ),
   ( 0x9C0, "conf_nnmi", "", "" ),
   ( 0x9D0, "conf_tms", "", "" ),
   ( 0x9D4, "conf_tdi", "", "" ),
   ( 0x9D8, "conf_tdo", "", "" ),
   ( 0x9DC, "conf_tck", "", "" ),
   ( 0x9E0, "conf_trstn", "", "" ),
   ( 0x9E4, "conf_emu0", "gpio3_7", "" ),
   ( 0x9E8, "conf_emu1", "gpio3_8", "" ),
   ( 0x9F8, "conf_rtc_pwronrstn", "", "" ),
   ( 0x9FC, "conf_pmic_power_en", "", "" ),
   ( 0xA00, "conf_ext_wakeup", "", "" ),
   ( 0xA04, "conf_rtc_kaldo_enn", "", "" ),
   ( 0xA1C, "conf_usb0_drvvbus", "gpio0_18", "" ),
   ( 0xA34, "conf_usb1_drvvbus", "gpio3_13", "" ),
   ( 0xE00, "cqdetect_status", "", "" ),
   ( 0xE04, "ddr_io_ctrl", "", "" ),
   ( 0xE0C, "vtp_ctrl", "", "" ),
   ( 0xE14, "vref_ctrl", "", "" ),
   ( 0xF90, "tpcc_evt_mux_0_3", "", "" ),
   ( 0xF94, "tpcc_evt_mux_4_7", "", "" ),
   ( 0xF98, "tpcc_evt_mux_8_11", "", "" ),
   ( 0xF9C, "tpcc_evt_mux_12_15", "", "" ),
   ( 0xFA0, "tpcc_evt_mux_16_19", "", "" ),
   ( 0xFA4, "tpcc_evt_mux_20_23", "", "" ),
   ( 0xFA8, "tpcc_evt_mux_24_27", "", "" ),
   ( 0xFAC, "tpcc_evt_mux_28_31", "", "" ),
   ( 0xFB0, "tpcc_evt_mux_32_35", "", "" ),
   ( 0xFB4, "tpcc_evt_mux_36_39", "", "" ),
   ( 0xFB8, "tpcc_evt_mux_40_43", "", "" ),
   ( 0xFBC, "tpcc_evt_mux_44_47", "", "" ),
   ( 0xFC0, "tpcc_evt_mux_48_51", "", "" ),
   ( 0xFC4, "tpcc_evt_mux_52_55", "", "" ),
   ( 0xFC8, "tpcc_evt_mux_56_59", "", "" ),
   ( 0xFCC, "tpcc_evt_mux_60_63", "", "" ),
   ( 0xFD0, "timer_evt_capt", "", "" ),
   ( 0xFD4, "ecap_evt_capt", "", "" ),
   ( 0xFD8, "adc_evt_capt", "", "" ),
   ( 0x1000, "reset_iso", "", "" ),
   ( 0x1318, "dpll_pwr_sw_ctrl", "", "" ),
   ( 0x131C, "ddr_cke_ctrl", "", "" ),
   ( 0x1320, "sma2", "", "" ),
   ( 0x1324, "m3_txev_eoi", "", "" ),
   ( 0x1328, "ipc_msg_reg0", "", "" ),
   ( 0x132C, "ipc_msg_reg1", "", "" ),
   ( 0x1330, "ipc_msg_reg2", "", "" ),
   ( 0x1334, "ipc_msg_reg3", "", "" ),
   ( 0x1338, "ipc_msg_reg4", "", "" ),
   ( 0x133C, "ipc_msg_reg5", "", "" ),
   ( 0x1340, "ipc_msg_reg6", "", "" ),
   ( 0x1344, "ipc_msg_reg7", "", "" ),
   ( 0x1404, "ddr_cmd0_ioctrl", "", "" ),
   ( 0x1408, "ddr_cmd1_ioctrl", "", "" ),
   ( 0x140C, "ddr_cmd2_ioctrl", "", "" ),
   ( 0x1440, "ddr_data0_ioctrl", "", "" ),
   ( 0x1144, "ddr_data1_ioctrl", "", "" )
]

import sys

def findByAddress( addr ):
   for el in mux:
      if el[0] == addr:
         return el
   return None

def showByHeaderPin( muxList ):
   # print sorted by header pin
   onlyHeader = [t for t in muxList if len( t[3] )]
   for el in sorted( onlyHeader,
         key = lambda t: int( t[3][1] ) * 100 + int( t[3][3:] ) ):
      print "{:5} {:s}".format( el[3], el[2] )

def findGPIO( up ):
   if up:
      end = '37'
   else:
      end = '27'

   gpios = []
   for line in open( "/sys/kernel/debug/pinctrl/44e10800.pinmux/pins" ):
      ll =  line.strip().split( " " )
      if len( ll ) == 5:
         mode = ll[3]
         if mode.endswith( end ):
            addr = int( ll[2][5:-3], 16 )
            gpios.append( findByAddress( addr ) )

   if len( gpios ) > 0:
      showByHeaderPin( gpios )

if len( sys.argv ) == 2:
   if sys.argv[1] == "findUpGPIO":
      findGPIO( True )
   elif sys.argv[1] == "findDownGPIO":
      findGPIO( False )
   else:
      showByHeaderPin( mux )

else:
   showByHeaderPin( mux )
