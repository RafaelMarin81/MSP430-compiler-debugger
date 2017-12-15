/* Map MCU preprocessor definitions to chip-specific include files.
 *
 * This file is automatically generated from TI-provided data.  Each device
 * is mapped to a genericized name by ignoring differences in memory type,
 * end-equipment optimization, and some other variances.  Preprocessor
 * directives are generated to include the appropriate header for each
 * device.  Generic names, such as msp430x1611, are recognized only if
 * they are sufficient to uniquely identify a device.  When this is not
 * the case, a comment indicates why a generic is excluded: normally
 * because devices have different peripherals or memory maps.
 */
#ifndef __msp430_h_
#define __msp430_h_

/** Date upstream material received from TI */
#define __MSP430MCU_UPSTREAM__ 20130311
/** Date of msp430mcu package release */
#define __MSP430MCU__ 20130321

/** Bit-markers for type of CPU present.
 * Check against __MSP430_CPU__ preprocessor symbol. */
#define MSP430_CPU_MSP430 0x0000
#define MSP430_CPU_MSP430X 0x0002
#define MSP430_CPU_MSP430XV2 0x0003

/** Bit-markers for type of hardware multiplier present.
 * Check against __MSP430_MPY__ (undefined if no hardware multiplier). */
#define MSP430_MPY_NONE 0x0000
#define MSP430_MPY_TYPE_16 0x0010
#define MSP430_MPY_TYPE_32 0x0020
#define MSP430_MPY_TYPE_ANY 0x0030
#define MSP430_MPY_HAS_SE 0x0001
#define MSP430_MPY_HAS_DW 0x0002
#define MSP430_MPY_16 MSP430_MPY_TYPE_16
#define MSP430_MPY_16SE (MSP430_MPY_16 | MSP430_MPY_HAS_SE)
#define MSP430_MPY_32 (MSP430_MPY_TYPE_16 | MSP430_MPY_TYPE_32 | MSP430_MPY_HAS_SE)
#define MSP430_MPY_32DW (MSP430_MPY_32 | MSP430_MPY_HAS_DW)

/** Bit-markers indicating CPUX target flags that are enabled.  Values
 * must be disjoint from msp430_cpu_e.  Check against __MSP430X__
 * (undefined on non-CPUX microcontroller).  */
#define MSP430_CPUX_TARGET_SR20 0x0100
#define MSP430_CPUX_TARGET_A20 0x0200
#define MSP430_CPUX_TARGET_C20 0x0400
#define MSP430_CPUX_TARGET_D20 0x0800

/** Bit-markers indicating the selected memory model.  Values must be
 * disjoint from msp430_cpu_e and msp430_cpux_target_e.  Though these
 * are recorded in __MSP430X__, use the MSP430_CPUX_TARGET_foo flags
 * for behavioral control. */
#define MSP430_MEMORY_MODEL_NONE 0x000000
#define MSP430_MEMORY_MODEL_SMALL 0x000010
#define MSP430_MEMORY_MODEL_MEDIUM 0x000020
#define MSP430_MEMORY_MODEL_LARGE 0x000030
#define MSP430_MEMORY_MODEL_HUGE 0x000040
#define MSP430_MEMORY_MODEL_MASK 0x000070

#if defined(__CC430F5123__)
#include <cc430f5123.h>   /* Genericizable */
#elif defined(__CC430F5125__)
#include <cc430f5125.h>   /* Genericizable */
#elif defined(__CC430F5133__)
#include <cc430f5133.h>   /* Genericizable */
#elif defined(__CC430F5135__)
#include <cc430f5135.h>   /* Genericizable */
#elif defined(__CC430F5137__)
#include <cc430f5137.h>   /* Genericizable */
#elif defined(__CC430F5143__)
#include <cc430f5143.h>   /* Genericizable */
#elif defined(__CC430F5145__)
#include <cc430f5145.h>   /* Genericizable */
#elif defined(__CC430F5147__)
#include <cc430f5147.h>   /* Genericizable */
#elif defined(__CC430F6125__)
#include <cc430f6125.h>   /* Genericizable */
#elif defined(__CC430F6126__)
#include <cc430f6126.h>   /* Genericizable */
#elif defined(__CC430F6127__)
#include <cc430f6127.h>   /* Genericizable */
#elif defined(__CC430F6135__)
#include <cc430f6135.h>   /* Genericizable */
#elif defined(__CC430F6137__)
#include <cc430f6137.h>   /* Genericizable */
#elif defined(__CC430F6143__)
#include <cc430f6143.h>   /* Genericizable */
#elif defined(__CC430F6145__)
#include <cc430f6145.h>   /* Genericizable */
#elif defined(__CC430F6147__)
#include <cc430f6147.h>   /* Genericizable */
#elif defined(__MSP430C091__)
#include <msp430c091.h>   /* Genericizable */
#elif defined(__MSP430L092__)
#include <msp430l092.h>   /* Device mismatch msp430_092 */
#elif defined(__MSP430C092__)
#include <msp430c092.h>   /* Device mismatch msp430_092 */
#elif defined(__MSP430F110__)
#include <msp430f110.h>   /* Genericizable */
#elif defined(__MSP430F1101__)
#include <msp430f1101.h>   /* Multi-device msp430_1101 */
#elif defined(__MSP430F1101A__)
#include <msp430f1101a.h>   /* Multi-device msp430_1101 */
#elif defined(__MSP430C111__)
#include <msp430c111.h>   /* Genericizable */
#elif defined(__MSP430F1111__)
#include <msp430f1111.h>   /* Device mismatch msp430_1111 */
#elif defined(__MSP430F1111A__)
#include <msp430f1111a.h>   /* Device mismatch msp430_1111 */
#elif defined(__MSP430C1111__)
#include <msp430c1111.h>   /* Device mismatch msp430_1111 */
#elif defined(__MSP430E112__)
#include <msp430e112.h>   /* Device mismatch msp430_112 */
#elif defined(__MSP430F112__)
#include <msp430f112.h>   /* Device mismatch msp430_112 */
#elif defined(__MSP430P112__)
#include <msp430p112.h>   /* Device mismatch msp430_112 */
#elif defined(__MSP430C112__)
#include <msp430c112.h>   /* Device mismatch msp430_112 */
#elif defined(__MSP430F1121__)
#include <msp430f1121.h>   /* Device mismatch msp430_1121 */
#elif defined(__MSP430F1121A__)
#include <msp430f1121a.h>   /* Device mismatch msp430_1121 */
#elif defined(__MSP430C1121__)
#include <msp430c1121.h>   /* Device mismatch msp430_1121 */
#elif defined(__MSP430F1122__)
#include <msp430f1122.h>   /* Genericizable */
#elif defined(__MSP430F1132__)
#include <msp430f1132.h>   /* Genericizable */
#elif defined(__MSP430F122__)
#include <msp430f122.h>   /* Genericizable */
#elif defined(__MSP430F1222__)
#include <msp430f1222.h>   /* Genericizable */
#elif defined(__MSP430F123__)
#include <msp430f123.h>   /* Genericizable */
#elif defined(__MSP430F1232__)
#include <msp430f1232.h>   /* Genericizable */
#elif defined(__MSP430F133__)
#include <msp430f133.h>   /* Genericizable */
#elif defined(__MSP430C1331__)
#include <msp430c1331.h>   /* Genericizable */
#elif defined(__MSP430F135__)
#include <msp430f135.h>   /* Genericizable */
#elif defined(__MSP430C1351__)
#include <msp430c1351.h>   /* Genericizable */
#elif defined(__MSP430F147__)
#include <msp430f147.h>   /* Genericizable */
#elif defined(__MSP430F1471__)
#include <msp430f1471.h>   /* Genericizable */
#elif defined(__MSP430F148__)
#include <msp430f148.h>   /* Genericizable */
#elif defined(__MSP430F1481__)
#include <msp430f1481.h>   /* Genericizable */
#elif defined(__MSP430F149__)
#include <msp430f149.h>   /* Genericizable */
#elif defined(__MSP430F1491__)
#include <msp430f1491.h>   /* Genericizable */
#elif defined(__MSP430F155__)
#include <msp430f155.h>   /* Genericizable */
#elif defined(__MSP430F156__)
#include <msp430f156.h>   /* Genericizable */
#elif defined(__MSP430F157__)
#include <msp430f157.h>   /* Genericizable */
#elif defined(__MSP430F1610__)
#include <msp430f1610.h>   /* Genericizable */
#elif defined(__MSP430F1611__)
#include <msp430f1611.h>   /* Genericizable */
#elif defined(__MSP430F1612__)
#include <msp430f1612.h>   /* Genericizable */
#elif defined(__MSP430F167__)
#include <msp430f167.h>   /* Genericizable */
#elif defined(__MSP430F168__)
#include <msp430f168.h>   /* Genericizable */
#elif defined(__MSP430F169__)
#include <msp430f169.h>   /* Genericizable */
#elif defined(__MSP430G2001__)
#include <msp430g2001.h>   /* Device mismatch msp430_2001 */
#elif defined(__MSP430F2001__)
#include <msp430f2001.h>   /* Device mismatch msp430_2001 */
#elif defined(__MSP430F2002__)
#include <msp430f2002.h>   /* Genericizable */
#elif defined(__MSP430F2003__)
#include <msp430f2003.h>   /* Genericizable */
#elif defined(__MSP430F2011__)
#include <msp430f2011.h>   /* Genericizable */
#elif defined(__MSP430F2012__)
#include <msp430f2012.h>   /* Genericizable */
#elif defined(__MSP430F2013__)
#include <msp430f2013.h>   /* Genericizable */
#elif defined(__MSP430G2101__)
#include <msp430g2101.h>   /* Header mismatch msp430_2101 */
#elif defined(__MSP430F2101__)
#include <msp430f2101.h>   /* Header mismatch msp430_2101 */
#elif defined(__MSP430G2102__)
#include <msp430g2102.h>   /* Genericizable */
#elif defined(__MSP430G2111__)
#include <msp430g2111.h>   /* Device mismatch msp430_2111 */
#elif defined(__MSP430F2111__)
#include <msp430f2111.h>   /* Device mismatch msp430_2111 */
#elif defined(__MSP430F2112__)
#include <msp430f2112.h>   /* Device mismatch msp430_2112 */
#elif defined(__MSP430G2112__)
#include <msp430g2112.h>   /* Device mismatch msp430_2112 */
#elif defined(__MSP430G2113__)
#include <msp430g2113.h>   /* Genericizable */
#elif defined(__MSP430F2121__)
#include <msp430f2121.h>   /* Device mismatch msp430_2121 */
#elif defined(__MSP430G2121__)
#include <msp430g2121.h>   /* Device mismatch msp430_2121 */
#elif defined(__MSP430F2122__)
#include <msp430f2122.h>   /* Genericizable */
#elif defined(__MSP430F2131__)
#include <msp430f2131.h>   /* Device mismatch msp430_2131 */
#elif defined(__MSP430G2131__)
#include <msp430g2131.h>   /* Device mismatch msp430_2131 */
#elif defined(__MSP430F2132__)
#include <msp430f2132.h>   /* Device mismatch msp430_2132 */
#elif defined(__MSP430G2132__)
#include <msp430g2132.h>   /* Device mismatch msp430_2132 */
#elif defined(__MSP430G2152__)
#include <msp430g2152.h>   /* Genericizable */
#elif defined(__MSP430G2153__)
#include <msp430g2153.h>   /* Genericizable */
#elif defined(__MSP430G2201__)
#include <msp430g2201.h>   /* Genericizable */
#elif defined(__MSP430G2202__)
#include <msp430g2202.h>   /* Genericizable */
#elif defined(__MSP430G2203__)
#include <msp430g2203.h>   /* Genericizable */
#elif defined(__MSP430AFE221__)
#include <msp430afe221.h>   /* Genericizable */
#elif defined(__MSP430G2210__)
#include <msp430g2210.h>   /* Genericizable */
#elif defined(__MSP430G2211__)
#include <msp430g2211.h>   /* Genericizable */
#elif defined(__MSP430G2212__)
#include <msp430g2212.h>   /* Genericizable */
#elif defined(__MSP430G2213__)
#include <msp430g2213.h>   /* Genericizable */
#elif defined(__MSP430AFE222__)
#include <msp430afe222.h>   /* Genericizable */
#elif defined(__MSP430G2221__)
#include <msp430g2221.h>   /* Genericizable */
#elif defined(__MSP430AFE223__)
#include <msp430afe223.h>   /* Genericizable */
#elif defined(__MSP430G2230__)
#include <msp430g2230.h>   /* Genericizable */
#elif defined(__MSP430G2231__)
#include <msp430g2231.h>   /* Genericizable */
#elif defined(__MSP430G2232__)
#include <msp430g2232.h>   /* Device mismatch msp430_2232 */
#elif defined(__MSP430F2232__)
#include <msp430f2232.h>   /* Device mismatch msp430_2232 */
#elif defined(__MSP430G2233__)
#include <msp430g2233.h>   /* Genericizable */
#elif defined(__MSP430F2234__)
#include <msp430f2234.h>   /* Genericizable */
#elif defined(__MSP430G2252__)
#include <msp430g2252.h>   /* Device mismatch msp430_2252 */
#elif defined(__MSP430F2252__)
#include <msp430f2252.h>   /* Device mismatch msp430_2252 */
#elif defined(__MSP430G2253__)
#include <msp430g2253.h>   /* Genericizable */
#elif defined(__MSP430F2254__)
#include <msp430f2254.h>   /* Genericizable */
#elif defined(__MSP430F2272__)
#include <msp430f2272.h>   /* Genericizable */
#elif defined(__MSP430F2274__)
#include <msp430f2274.h>   /* Genericizable */
#elif defined(__MSP430G2302__)
#include <msp430g2302.h>   /* Genericizable */
#elif defined(__MSP430G2303__)
#include <msp430g2303.h>   /* Genericizable */
#elif defined(__MSP430AFE231__)
#include <msp430afe231.h>   /* Genericizable */
#elif defined(__MSP430G2312__)
#include <msp430g2312.h>   /* Genericizable */
#elif defined(__MSP430G2313__)
#include <msp430g2313.h>   /* Genericizable */
#elif defined(__MSP430AFE232__)
#include <msp430afe232.h>   /* Genericizable */
#elif defined(__MSP430AFE233__)
#include <msp430afe233.h>   /* Device mismatch msp430_233 */
#elif defined(__MSP430F233__)
#include <msp430f233.h>   /* Device mismatch msp430_233 */
#elif defined(__MSP430F2330__)
#include <msp430f2330.h>   /* Genericizable */
#elif defined(__MSP430G2332__)
#include <msp430g2332.h>   /* Genericizable */
#elif defined(__MSP430G2333__)
#include <msp430g2333.h>   /* Genericizable */
#elif defined(__MSP430F235__)
#include <msp430f235.h>   /* Genericizable */
#elif defined(__MSP430F2350__)
#include <msp430f2350.h>   /* Genericizable */
#elif defined(__MSP430G2352__)
#include <msp430g2352.h>   /* Genericizable */
#elif defined(__MSP430G2353__)
#include <msp430g2353.h>   /* Genericizable */
#elif defined(__MSP430F2370__)
#include <msp430f2370.h>   /* Genericizable */
#elif defined(__MSP430G2402__)
#include <msp430g2402.h>   /* Genericizable */
#elif defined(__MSP430G2403__)
#include <msp430g2403.h>   /* Genericizable */
#elif defined(__MSP430F2410__)
#include <msp430f2410.h>   /* Genericizable */
#elif defined(__MSP430G2412__)
#include <msp430g2412.h>   /* Genericizable */
#elif defined(__MSP430G2413__)
#include <msp430g2413.h>   /* Genericizable */
#elif defined(__MSP430F2416__)
#include <msp430f2416.h>   /* Genericizable */
#elif defined(__MSP430F2417__)
#include <msp430f2417.h>   /* Genericizable */
#elif defined(__MSP430F2418__)
#include <msp430f2418.h>   /* Genericizable */
#elif defined(__MSP430F2419__)
#include <msp430f2419.h>   /* Genericizable */
#elif defined(__MSP430G2432__)
#include <msp430g2432.h>   /* Genericizable */
#elif defined(__MSP430G2433__)
#include <msp430g2433.h>   /* Genericizable */
#elif defined(__MSP430G2444__)
#include <msp430g2444.h>   /* Genericizable */
#elif defined(__MSP430G2452__)
#include <msp430g2452.h>   /* Genericizable */
#elif defined(__MSP430G2453__)
#include <msp430g2453.h>   /* Genericizable */
#elif defined(__MSP430F247__)
#include <msp430f247.h>   /* Genericizable */
#elif defined(__MSP430F2471__)
#include <msp430f2471.h>   /* Genericizable */
#elif defined(__MSP430F248__)
#include <msp430f248.h>   /* Genericizable */
#elif defined(__MSP430F2481__)
#include <msp430f2481.h>   /* Genericizable */
#elif defined(__MSP430F249__)
#include <msp430f249.h>   /* Genericizable */
#elif defined(__MSP430F2491__)
#include <msp430f2491.h>   /* Genericizable */
#elif defined(__MSP430AFE251__)
#include <msp430afe251.h>   /* Genericizable */
#elif defined(__MSP430G2513__)
#include <msp430g2513.h>   /* Genericizable */
#elif defined(__MSP430AFE252__)
#include <msp430afe252.h>   /* Genericizable */
#elif defined(__MSP430AFE253__)
#include <msp430afe253.h>   /* Genericizable */
#elif defined(__MSP430G2533__)
#include <msp430g2533.h>   /* Genericizable */
#elif defined(__MSP430G2544__)
#include <msp430g2544.h>   /* Genericizable */
#elif defined(__MSP430G2553__)
#include <msp430g2553.h>   /* Header mismatch msp430_2553 */
#elif defined(__MSP430TCH5E__)
#include <msp430tch5e.h>   /* Header mismatch msp430_2553 */
#elif defined(__MSP430F2616__)
#include <msp430f2616.h>   /* Genericizable */
#elif defined(__MSP430F2617__)
#include <msp430f2617.h>   /* Genericizable */
#elif defined(__MSP430F2618__)
#include <msp430f2618.h>   /* Genericizable */
#elif defined(__MSP430F2619__)
#include <msp430f2619.h>   /* Genericizable */
#elif defined(__MSP430G2744__)
#include <msp430g2744.h>   /* Genericizable */
#elif defined(__MSP430G2755__)
#include <msp430g2755.h>   /* Genericizable */
#elif defined(__MSP430G2855__)
#include <msp430g2855.h>   /* Genericizable */
#elif defined(__MSP430G2955__)
#include <msp430g2955.h>   /* Genericizable */
#elif defined(__MSP430C311S__)
#include <msp430c311s.h>   /* Genericizable */
#elif defined(__MSP430C312__)
#include <msp430c312.h>   /* Genericizable */
#elif defined(__MSP430C313__)
#include <msp430c313.h>   /* Multi-device msp430_313 */
#elif defined(__MSP430P313__)
#include <msp430p313.h>   /* Multi-device msp430_313 */
#elif defined(__MSP430E313__)
#include <msp430e313.h>   /* Multi-device msp430_313 */
#elif defined(__MSP430C314__)
#include <msp430c314.h>   /* Genericizable */
#elif defined(__MSP430P315S__)
#include <msp430p315s.h>   /* Multi-device msp430_315 */
#elif defined(__MSP430E315__)
#include <msp430e315.h>   /* Multi-device msp430_315 */
#elif defined(__MSP430P315__)
#include <msp430p315.h>   /* Multi-device msp430_315 */
#elif defined(__MSP430C315__)
#include <msp430c315.h>   /* Multi-device msp430_315 */
#elif defined(__MSP430C323__)
#include <msp430c323.h>   /* Genericizable */
#elif defined(__MSP430P325__)
#include <msp430p325.h>   /* Multi-device msp430_325 */
#elif defined(__MSP430E325__)
#include <msp430e325.h>   /* Multi-device msp430_325 */
#elif defined(__MSP430C325__)
#include <msp430c325.h>   /* Multi-device msp430_325 */
#elif defined(__MSP430C336__)
#include <msp430c336.h>   /* Genericizable */
#elif defined(__MSP430P337__)
#include <msp430p337.h>   /* Multi-device msp430_337 */
#elif defined(__MSP430C337__)
#include <msp430c337.h>   /* Multi-device msp430_337 */
#elif defined(__MSP430E337__)
#include <msp430e337.h>   /* Multi-device msp430_337 */
#elif defined(__MSP430F412__)
#include <msp430f412.h>   /* Device mismatch msp430_412 */
#elif defined(__MSP430C412__)
#include <msp430c412.h>   /* Device mismatch msp430_412 */
#elif defined(__MSP430F413__)
#include <msp430f413.h>   /* Device mismatch msp430_413 */
#elif defined(__MSP430C413__)
#include <msp430c413.h>   /* Device mismatch msp430_413 */
#elif defined(__MSP430F4132__)
#include <msp430f4132.h>   /* Genericizable */
#elif defined(__MSP430F415__)
#include <msp430f415.h>   /* Genericizable */
#elif defined(__MSP430F4152__)
#include <msp430f4152.h>   /* Genericizable */
#elif defined(__MSP430F417__)
#include <msp430f417.h>   /* Genericizable */
#elif defined(__MSP430F423__)
#include <msp430f423.h>   /* Device mismatch msp430_423 */
#elif defined(__MSP430FE423__)
#include <msp430fe423.h>   /* Device mismatch msp430_423 */
#elif defined(__MSP430FW423__)
#include <msp430fw423.h>   /* Device mismatch msp430_423 */
#elif defined(__MSP430F423A__)
#include <msp430f423a.h>   /* Device mismatch msp430_423 */
#elif defined(__MSP430FE423A__)
#include <msp430fe423a.h>   /* Device mismatch msp430_423 */
#elif defined(__MSP430FE4232__)
#include <msp430fe4232.h>   /* Genericizable */
#elif defined(__MSP430FE4242__)
#include <msp430fe4242.h>   /* Genericizable */
#elif defined(__MSP430FE425__)
#include <msp430fe425.h>   /* Device mismatch msp430_425 */
#elif defined(__MSP430FE425A__)
#include <msp430fe425a.h>   /* Device mismatch msp430_425 */
#elif defined(__MSP430FW425__)
#include <msp430fw425.h>   /* Device mismatch msp430_425 */
#elif defined(__MSP430F425A__)
#include <msp430f425a.h>   /* Device mismatch msp430_425 */
#elif defined(__MSP430F425__)
#include <msp430f425.h>   /* Device mismatch msp430_425 */
#elif defined(__MSP430FG4250__)
#include <msp430fg4250.h>   /* Header mismatch msp430_4250 */
#elif defined(__MSP430F4250__)
#include <msp430f4250.h>   /* Header mismatch msp430_4250 */
#elif defined(__MSP430FE4252__)
#include <msp430fe4252.h>   /* Genericizable */
#elif defined(__MSP430FG4260__)
#include <msp430fg4260.h>   /* Header mismatch msp430_4260 */
#elif defined(__MSP430F4260__)
#include <msp430f4260.h>   /* Header mismatch msp430_4260 */
#elif defined(__MSP430F427A__)
#include <msp430f427a.h>   /* Device mismatch msp430_427 */
#elif defined(__MSP430FE427__)
#include <msp430fe427.h>   /* Device mismatch msp430_427 */
#elif defined(__MSP430F427__)
#include <msp430f427.h>   /* Device mismatch msp430_427 */
#elif defined(__MSP430FW427__)
#include <msp430fw427.h>   /* Device mismatch msp430_427 */
#elif defined(__MSP430FE427A__)
#include <msp430fe427a.h>   /* Device mismatch msp430_427 */
#elif defined(__MSP430F4270__)
#include <msp430f4270.h>   /* Header mismatch msp430_4270 */
#elif defined(__MSP430FG4270__)
#include <msp430fg4270.h>   /* Header mismatch msp430_4270 */
#elif defined(__MSP430FE4272__)
#include <msp430fe4272.h>   /* Genericizable */
#elif defined(__MSP430FW428__)
#include <msp430fw428.h>   /* Genericizable */
#elif defined(__MSP430FW429__)
#include <msp430fw429.h>   /* Genericizable */
#elif defined(__MSP430F435__)
#include <msp430f435.h>   /* Genericizable */
#elif defined(__MSP430F4351__)
#include <msp430f4351.h>   /* Genericizable */
#elif defined(__MSP430F436__)
#include <msp430f436.h>   /* Genericizable */
#elif defined(__MSP430F4361__)
#include <msp430f4361.h>   /* Genericizable */
#elif defined(__MSP430FG437__)
#include <msp430fg437.h>   /* Header mismatch msp430_437 */
#elif defined(__MSP430F437__)
#include <msp430f437.h>   /* Header mismatch msp430_437 */
#elif defined(__MSP430F4371__)
#include <msp430f4371.h>   /* Genericizable */
#elif defined(__MSP430F438__)
#include <msp430f438.h>   /* Header mismatch msp430_438 */
#elif defined(__MSP430FG438__)
#include <msp430fg438.h>   /* Header mismatch msp430_438 */
#elif defined(__MSP430F439__)
#include <msp430f439.h>   /* Header mismatch msp430_439 */
#elif defined(__MSP430FG439__)
#include <msp430fg439.h>   /* Header mismatch msp430_439 */
#elif defined(__MSP430F447__)
#include <msp430f447.h>   /* Genericizable */
#elif defined(__MSP430F448__)
#include <msp430f448.h>   /* Genericizable */
#elif defined(__MSP430F4481__)
#include <msp430f4481.h>   /* Genericizable */
#elif defined(__MSP430F449__)
#include <msp430f449.h>   /* Genericizable */
#elif defined(__MSP430F4491__)
#include <msp430f4491.h>   /* Genericizable */
#elif defined(__MSP430CG4616__)
#include <msp430cg4616.h>   /* Header mismatch msp430_4616 */
#elif defined(__MSP430F4616__)
#include <msp430f4616.h>   /* Header mismatch msp430_4616 */
#elif defined(__MSP430FG4616__)
#include <msp430fg4616.h>   /* Header mismatch msp430_4616 */
#elif defined(__MSP430F46161__)
#include <msp430f46161.h>   /* Genericizable */
#elif defined(__MSP430F4617__)
#include <msp430f4617.h>   /* Header mismatch msp430_4617 */
#elif defined(__MSP430CG4617__)
#include <msp430cg4617.h>   /* Header mismatch msp430_4617 */
#elif defined(__MSP430FG4617__)
#include <msp430fg4617.h>   /* Header mismatch msp430_4617 */
#elif defined(__MSP430F46171__)
#include <msp430f46171.h>   /* Genericizable */
#elif defined(__MSP430FG4618__)
#include <msp430fg4618.h>   /* Header mismatch msp430_4618 */
#elif defined(__MSP430CG4618__)
#include <msp430cg4618.h>   /* Header mismatch msp430_4618 */
#elif defined(__MSP430F4618__)
#include <msp430f4618.h>   /* Header mismatch msp430_4618 */
#elif defined(__MSP430F46181__)
#include <msp430f46181.h>   /* Genericizable */
#elif defined(__MSP430FG4619__)
#include <msp430fg4619.h>   /* Header mismatch msp430_4619 */
#elif defined(__MSP430F4619__)
#include <msp430f4619.h>   /* Header mismatch msp430_4619 */
#elif defined(__MSP430CG4619__)
#include <msp430cg4619.h>   /* Header mismatch msp430_4619 */
#elif defined(__MSP430F46191__)
#include <msp430f46191.h>   /* Genericizable */
#elif defined(__MSP430F47126__)
#include <msp430f47126.h>   /* Genericizable */
#elif defined(__MSP430F47127__)
#include <msp430f47127.h>   /* Genericizable */
#elif defined(__MSP430F47163__)
#include <msp430f47163.h>   /* Genericizable */
#elif defined(__MSP430F47166__)
#include <msp430f47166.h>   /* Genericizable */
#elif defined(__MSP430F47167__)
#include <msp430f47167.h>   /* Genericizable */
#elif defined(__MSP430F47173__)
#include <msp430f47173.h>   /* Genericizable */
#elif defined(__MSP430F47176__)
#include <msp430f47176.h>   /* Genericizable */
#elif defined(__MSP430F47177__)
#include <msp430f47177.h>   /* Genericizable */
#elif defined(__MSP430F47183__)
#include <msp430f47183.h>   /* Genericizable */
#elif defined(__MSP430F47186__)
#include <msp430f47186.h>   /* Genericizable */
#elif defined(__MSP430F47187__)
#include <msp430f47187.h>   /* Genericizable */
#elif defined(__MSP430F47193__)
#include <msp430f47193.h>   /* Genericizable */
#elif defined(__MSP430F47196__)
#include <msp430f47196.h>   /* Genericizable */
#elif defined(__MSP430F47197__)
#include <msp430f47197.h>   /* Genericizable */
#elif defined(__MSP430FG477__)
#include <msp430fg477.h>   /* Header mismatch msp430_477 */
#elif defined(__MSP430F477__)
#include <msp430f477.h>   /* Header mismatch msp430_477 */
#elif defined(__MSP430F478__)
#include <msp430f478.h>   /* Header mismatch msp430_478 */
#elif defined(__MSP430FG478__)
#include <msp430fg478.h>   /* Header mismatch msp430_478 */
#elif defined(__MSP430F4783__)
#include <msp430f4783.h>   /* Genericizable */
#elif defined(__MSP430F4784__)
#include <msp430f4784.h>   /* Genericizable */
#elif defined(__MSP430F479__)
#include <msp430f479.h>   /* Header mismatch msp430_479 */
#elif defined(__MSP430FG479__)
#include <msp430fg479.h>   /* Header mismatch msp430_479 */
#elif defined(__MSP430F4793__)
#include <msp430f4793.h>   /* Genericizable */
#elif defined(__MSP430F4794__)
#include <msp430f4794.h>   /* Genericizable */
#elif defined(__MSP430F5131__)
#include <msp430f5131.h>   /* Genericizable */
#elif defined(__MSP430F5132__)
#include <msp430f5132.h>   /* Genericizable */
#elif defined(__MSP430F5151__)
#include <msp430f5151.h>   /* Genericizable */
#elif defined(__MSP430F5152__)
#include <msp430f5152.h>   /* Genericizable */
#elif defined(__MSP430F5171__)
#include <msp430f5171.h>   /* Genericizable */
#elif defined(__MSP430F5172__)
#include <msp430f5172.h>   /* Genericizable */
#elif defined(__MSP430BT5190__)
#include <msp430bt5190.h>   /* Genericizable */
#elif defined(__MSP430F5212__)
#include <msp430f5212.h>   /* Genericizable */
#elif defined(__MSP430F5213__)
#include <msp430f5213.h>   /* Genericizable */
#elif defined(__MSP430F5214__)
#include <msp430f5214.h>   /* Genericizable */
#elif defined(__MSP430F5217__)
#include <msp430f5217.h>   /* Genericizable */
#elif defined(__MSP430F5218__)
#include <msp430f5218.h>   /* Genericizable */
#elif defined(__MSP430F5219__)
#include <msp430f5219.h>   /* Genericizable */
#elif defined(__MSP430F5222__)
#include <msp430f5222.h>   /* Genericizable */
#elif defined(__MSP430F5223__)
#include <msp430f5223.h>   /* Genericizable */
#elif defined(__MSP430F5224__)
#include <msp430f5224.h>   /* Genericizable */
#elif defined(__MSP430F5227__)
#include <msp430f5227.h>   /* Genericizable */
#elif defined(__MSP430F5228__)
#include <msp430f5228.h>   /* Genericizable */
#elif defined(__MSP430F5229__)
#include <msp430f5229.h>   /* Genericizable */
#elif defined(__MSP430F5304__)
#include <msp430f5304.h>   /* Genericizable */
#elif defined(__MSP430F5308__)
#include <msp430f5308.h>   /* Genericizable */
#elif defined(__MSP430F5309__)
#include <msp430f5309.h>   /* Genericizable */
#elif defined(__MSP430F5310__)
#include <msp430f5310.h>   /* Genericizable */
#elif defined(__MSP430F5324__)
#include <msp430f5324.h>   /* Genericizable */
#elif defined(__MSP430F5325__)
#include <msp430f5325.h>   /* Genericizable */
#elif defined(__MSP430F5326__)
#include <msp430f5326.h>   /* Genericizable */
#elif defined(__MSP430F5327__)
#include <msp430f5327.h>   /* Genericizable */
#elif defined(__MSP430F5328__)
#include <msp430f5328.h>   /* Genericizable */
#elif defined(__MSP430F5329__)
#include <msp430f5329.h>   /* Genericizable */
#elif defined(__MSP430F5333__)
#include <msp430f5333.h>   /* Genericizable */
#elif defined(__MSP430F5335__)
#include <msp430f5335.h>   /* Genericizable */
#elif defined(__MSP430F5336__)
#include <msp430f5336.h>   /* Genericizable */
#elif defined(__MSP430F5338__)
#include <msp430f5338.h>   /* Genericizable */
#elif defined(__MSP430F5340__)
#include <msp430f5340.h>   /* Genericizable */
#elif defined(__MSP430F5341__)
#include <msp430f5341.h>   /* Genericizable */
#elif defined(__MSP430F5342__)
#include <msp430f5342.h>   /* Genericizable */
#elif defined(__MSP430F5358__)
#include <msp430f5358.h>   /* Genericizable */
#elif defined(__MSP430F5359__)
#include <msp430f5359.h>   /* Genericizable */
#elif defined(__MSP430F5418A__)
#include <msp430f5418a.h>   /* Device mismatch msp430_5418 */
#elif defined(__MSP430F5418__)
#include <msp430f5418.h>   /* Device mismatch msp430_5418 */
#elif defined(__MSP430F5419A__)
#include <msp430f5419a.h>   /* Device mismatch msp430_5419 */
#elif defined(__MSP430F5419__)
#include <msp430f5419.h>   /* Device mismatch msp430_5419 */
#elif defined(__MSP430F5435__)
#include <msp430f5435.h>   /* Device mismatch msp430_5435 */
#elif defined(__MSP430F5435A__)
#include <msp430f5435a.h>   /* Device mismatch msp430_5435 */
#elif defined(__MSP430F5436__)
#include <msp430f5436.h>   /* Device mismatch msp430_5436 */
#elif defined(__MSP430F5436A__)
#include <msp430f5436a.h>   /* Device mismatch msp430_5436 */
#elif defined(__MSP430F5437__)
#include <msp430f5437.h>   /* Device mismatch msp430_5437 */
#elif defined(__MSP430F5437A__)
#include <msp430f5437a.h>   /* Device mismatch msp430_5437 */
#elif defined(__MSP430F5438A__)
#include <msp430f5438a.h>   /* Device mismatch msp430_5438 */
#elif defined(__MSP430SL5438A__)
#include <msp430sl5438a.h>   /* Device mismatch msp430_5438 */
#elif defined(__MSP430F5438__)
#include <msp430f5438.h>   /* Device mismatch msp430_5438 */
#elif defined(__MSP430F5500__)
#include <msp430f5500.h>   /* Genericizable */
#elif defined(__MSP430F5501__)
#include <msp430f5501.h>   /* Genericizable */
#elif defined(__MSP430F5502__)
#include <msp430f5502.h>   /* Genericizable */
#elif defined(__MSP430F5503__)
#include <msp430f5503.h>   /* Genericizable */
#elif defined(__MSP430F5504__)
#include <msp430f5504.h>   /* Genericizable */
#elif defined(__MSP430F5505__)
#include <msp430f5505.h>   /* Genericizable */
#elif defined(__MSP430F5506__)
#include <msp430f5506.h>   /* Genericizable */
#elif defined(__MSP430F5507__)
#include <msp430f5507.h>   /* Genericizable */
#elif defined(__MSP430F5508__)
#include <msp430f5508.h>   /* Genericizable */
#elif defined(__MSP430F5509__)
#include <msp430f5509.h>   /* Genericizable */
#elif defined(__MSP430F5510__)
#include <msp430f5510.h>   /* Genericizable */
#elif defined(__MSP430F5513__)
#include <msp430f5513.h>   /* Genericizable */
#elif defined(__MSP430F5514__)
#include <msp430f5514.h>   /* Genericizable */
#elif defined(__MSP430F5515__)
#include <msp430f5515.h>   /* Genericizable */
#elif defined(__MSP430F5517__)
#include <msp430f5517.h>   /* Genericizable */
#elif defined(__MSP430F5519__)
#include <msp430f5519.h>   /* Genericizable */
#elif defined(__MSP430F5521__)
#include <msp430f5521.h>   /* Genericizable */
#elif defined(__MSP430F5522__)
#include <msp430f5522.h>   /* Genericizable */
#elif defined(__MSP430F5524__)
#include <msp430f5524.h>   /* Genericizable */
#elif defined(__MSP430F5525__)
#include <msp430f5525.h>   /* Genericizable */
#elif defined(__MSP430F5526__)
#include <msp430f5526.h>   /* Genericizable */
#elif defined(__MSP430F5527__)
#include <msp430f5527.h>   /* Genericizable */
#elif defined(__MSP430F5528__)
#include <msp430f5528.h>   /* Genericizable */
#elif defined(__MSP430F5529__)
#include <msp430f5529.h>   /* Genericizable */
#elif defined(__MSP430F5630__)
#include <msp430f5630.h>   /* Genericizable */
#elif defined(__MSP430F5631__)
#include <msp430f5631.h>   /* Genericizable */
#elif defined(__MSP430F5632__)
#include <msp430f5632.h>   /* Genericizable */
#elif defined(__MSP430F5633__)
#include <msp430f5633.h>   /* Genericizable */
#elif defined(__MSP430F5634__)
#include <msp430f5634.h>   /* Genericizable */
#elif defined(__MSP430F5635__)
#include <msp430f5635.h>   /* Genericizable */
#elif defined(__MSP430F5636__)
#include <msp430f5636.h>   /* Genericizable */
#elif defined(__MSP430F5637__)
#include <msp430f5637.h>   /* Genericizable */
#elif defined(__MSP430F5638__)
#include <msp430f5638.h>   /* Genericizable */
#elif defined(__MSP430F5658__)
#include <msp430f5658.h>   /* Genericizable */
#elif defined(__MSP430F5659__)
#include <msp430f5659.h>   /* Genericizable */
#elif defined(__MSP430FR5720__)
#include <msp430fr5720.h>   /* Genericizable */
#elif defined(__MSP430FR5721__)
#include <msp430fr5721.h>   /* Genericizable */
#elif defined(__MSP430FR5722__)
#include <msp430fr5722.h>   /* Genericizable */
#elif defined(__MSP430FR5723__)
#include <msp430fr5723.h>   /* Genericizable */
#elif defined(__MSP430FR5724__)
#include <msp430fr5724.h>   /* Genericizable */
#elif defined(__MSP430FR5725__)
#include <msp430fr5725.h>   /* Genericizable */
#elif defined(__MSP430FR5726__)
#include <msp430fr5726.h>   /* Genericizable */
#elif defined(__MSP430FR5727__)
#include <msp430fr5727.h>   /* Genericizable */
#elif defined(__MSP430FR5728__)
#include <msp430fr5728.h>   /* Genericizable */
#elif defined(__MSP430FR5729__)
#include <msp430fr5729.h>   /* Genericizable */
#elif defined(__MSP430FR5730__)
#include <msp430fr5730.h>   /* Genericizable */
#elif defined(__MSP430FR5731__)
#include <msp430fr5731.h>   /* Genericizable */
#elif defined(__MSP430FR5732__)
#include <msp430fr5732.h>   /* Genericizable */
#elif defined(__MSP430FR5733__)
#include <msp430fr5733.h>   /* Genericizable */
#elif defined(__MSP430FR5734__)
#include <msp430fr5734.h>   /* Genericizable */
#elif defined(__MSP430FR5735__)
#include <msp430fr5735.h>   /* Genericizable */
#elif defined(__MSP430FR5736__)
#include <msp430fr5736.h>   /* Genericizable */
#elif defined(__MSP430FR5737__)
#include <msp430fr5737.h>   /* Genericizable */
#elif defined(__MSP430FR5738__)
#include <msp430fr5738.h>   /* Genericizable */
#elif defined(__MSP430FR5739__)
#include <msp430fr5739.h>   /* Genericizable */
#elif defined(__MSP430FR5949__)
#include <msp430fr5949.h>   /* Genericizable */
#elif defined(__MSP430FR5969__)
#include <msp430fr5969.h>   /* Genericizable */
#elif defined(__MSP430F6433__)
#include <msp430f6433.h>   /* Genericizable */
#elif defined(__MSP430F6435__)
#include <msp430f6435.h>   /* Genericizable */
#elif defined(__MSP430F6436__)
#include <msp430f6436.h>   /* Genericizable */
#elif defined(__MSP430F6438__)
#include <msp430f6438.h>   /* Genericizable */
#elif defined(__MSP430F6458__)
#include <msp430f6458.h>   /* Genericizable */
#elif defined(__MSP430F6459__)
#include <msp430f6459.h>   /* Genericizable */
#elif defined(__MSP430F6630__)
#include <msp430f6630.h>   /* Genericizable */
#elif defined(__MSP430F6631__)
#include <msp430f6631.h>   /* Genericizable */
#elif defined(__MSP430F6632__)
#include <msp430f6632.h>   /* Genericizable */
#elif defined(__MSP430F6633__)
#include <msp430f6633.h>   /* Genericizable */
#elif defined(__MSP430F6634__)
#include <msp430f6634.h>   /* Genericizable */
#elif defined(__MSP430F6635__)
#include <msp430f6635.h>   /* Genericizable */
#elif defined(__MSP430F6636__)
#include <msp430f6636.h>   /* Genericizable */
#elif defined(__MSP430F6637__)
#include <msp430f6637.h>   /* Genericizable */
#elif defined(__MSP430F6638__)
#include <msp430f6638.h>   /* Genericizable */
#elif defined(__MSP430F6658__)
#include <msp430f6658.h>   /* Genericizable */
#elif defined(__MSP430F6659__)
#include <msp430f6659.h>   /* Genericizable */
#elif defined(__MSP430F6720__)
#include <msp430f6720.h>   /* Genericizable */
#elif defined(__MSP430F6721__)
#include <msp430f6721.h>   /* Genericizable */
#elif defined(__MSP430F6723__)
#include <msp430f6723.h>   /* Genericizable */
#elif defined(__MSP430F6724__)
#include <msp430f6724.h>   /* Genericizable */
#elif defined(__MSP430F6725__)
#include <msp430f6725.h>   /* Genericizable */
#elif defined(__MSP430F6726__)
#include <msp430f6726.h>   /* Genericizable */
#elif defined(__MSP430F6730__)
#include <msp430f6730.h>   /* Genericizable */
#elif defined(__MSP430F6731__)
#include <msp430f6731.h>   /* Genericizable */
#elif defined(__MSP430F6733__)
#include <msp430f6733.h>   /* Genericizable */
#elif defined(__MSP430F6734__)
#include <msp430f6734.h>   /* Genericizable */
#elif defined(__MSP430F6735__)
#include <msp430f6735.h>   /* Genericizable */
#elif defined(__MSP430F6736__)
#include <msp430f6736.h>   /* Genericizable */
#elif defined(__MSP430F6745__)
#include <msp430f6745.h>   /* Genericizable */
#elif defined(__MSP430F67451__)
#include <msp430f67451.h>   /* Genericizable */
#elif defined(__MSP430F6746__)
#include <msp430f6746.h>   /* Genericizable */
#elif defined(__MSP430F67461__)
#include <msp430f67461.h>   /* Genericizable */
#elif defined(__MSP430F6747__)
#include <msp430f6747.h>   /* Genericizable */
#elif defined(__MSP430F67471__)
#include <msp430f67471.h>   /* Genericizable */
#elif defined(__MSP430F6748__)
#include <msp430f6748.h>   /* Genericizable */
#elif defined(__MSP430F67481__)
#include <msp430f67481.h>   /* Genericizable */
#elif defined(__MSP430F6749__)
#include <msp430f6749.h>   /* Genericizable */
#elif defined(__MSP430F67491__)
#include <msp430f67491.h>   /* Genericizable */
#elif defined(__MSP430F6765__)
#include <msp430f6765.h>   /* Genericizable */
#elif defined(__MSP430F67651__)
#include <msp430f67651.h>   /* Genericizable */
#elif defined(__MSP430F6766__)
#include <msp430f6766.h>   /* Genericizable */
#elif defined(__MSP430F67661__)
#include <msp430f67661.h>   /* Genericizable */
#elif defined(__MSP430F6767__)
#include <msp430f6767.h>   /* Genericizable */
#elif defined(__MSP430F67671__)
#include <msp430f67671.h>   /* Genericizable */
#elif defined(__MSP430F6768__)
#include <msp430f6768.h>   /* Genericizable */
#elif defined(__MSP430F67681__)
#include <msp430f67681.h>   /* Genericizable */
#elif defined(__MSP430F6769__)
#include <msp430f6769.h>   /* Genericizable */
#elif defined(__MSP430F67691__)
#include <msp430f67691.h>   /* Genericizable */
#elif defined(__MSP430F6775__)
#include <msp430f6775.h>   /* Genericizable */
#elif defined(__MSP430F67751__)
#include <msp430f67751.h>   /* Genericizable */
#elif defined(__MSP430F6776__)
#include <msp430f6776.h>   /* Genericizable */
#elif defined(__MSP430F67761__)
#include <msp430f67761.h>   /* Genericizable */
#elif defined(__MSP430F6777__)
#include <msp430f6777.h>   /* Genericizable */
#elif defined(__MSP430F67771__)
#include <msp430f67771.h>   /* Genericizable */
#elif defined(__MSP430F6778__)
#include <msp430f6778.h>   /* Genericizable */
#elif defined(__MSP430F67781__)
#include <msp430f67781.h>   /* Genericizable */
#elif defined(__MSP430F6779__)
#include <msp430f6779.h>   /* Genericizable */
#elif defined(__MSP430F67791__)
#include <msp430f67791.h>   /* Genericizable */

#elif defined(__MSP430XGENERIC__)
#include <msp430xgeneric.h>
#elif defined(__MSP430GENERIC__)
#include <msp430generic.h>
#else
#warning Unable to identify and include MCU header, use -mmcu=MCU
#endif

#endif /* __msp430_h_ */
