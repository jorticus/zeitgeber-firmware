#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Zeitgeber.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Zeitgeber.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/applications/main/appmain.o ${OBJECTDIR}/api/graphics/font.o ${OBJECTDIR}/api/graphics/gfx.o ${OBJECTDIR}/api/bluetooth.o ${OBJECTDIR}/api/oled.o ${OBJECTDIR}/api/power_monitor.o ${OBJECTDIR}/api/sensors.o ${OBJECTDIR}/api/usb.o ${OBJECTDIR}/api/app.o ${OBJECTDIR}/api/clock.o ${OBJECTDIR}/api/compass.o ${OBJECTDIR}/core/scheduler.o ${OBJECTDIR}/core/cpu.o ${OBJECTDIR}/core/systick.o ${OBJECTDIR}/core/traps.o ${OBJECTDIR}/core/os.o ${OBJECTDIR}/drivers/HMC5883.o ${OBJECTDIR}/drivers/MMA7455.o ${OBJECTDIR}/drivers/ssd1351.o ${OBJECTDIR}/peripherals/gpio.o ${OBJECTDIR}/peripherals/adc.o ${OBJECTDIR}/peripherals/pwm.o ${OBJECTDIR}/peripherals/rtc.o ${OBJECTDIR}/peripherals/ssd1351p.o ${OBJECTDIR}/peripherals/i2c.o ${OBJECTDIR}/peripherals/spi.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/applications/main/appmain.o.d ${OBJECTDIR}/api/graphics/font.o.d ${OBJECTDIR}/api/graphics/gfx.o.d ${OBJECTDIR}/api/bluetooth.o.d ${OBJECTDIR}/api/oled.o.d ${OBJECTDIR}/api/power_monitor.o.d ${OBJECTDIR}/api/sensors.o.d ${OBJECTDIR}/api/usb.o.d ${OBJECTDIR}/api/app.o.d ${OBJECTDIR}/api/clock.o.d ${OBJECTDIR}/api/compass.o.d ${OBJECTDIR}/core/scheduler.o.d ${OBJECTDIR}/core/cpu.o.d ${OBJECTDIR}/core/systick.o.d ${OBJECTDIR}/core/traps.o.d ${OBJECTDIR}/core/os.o.d ${OBJECTDIR}/drivers/HMC5883.o.d ${OBJECTDIR}/drivers/MMA7455.o.d ${OBJECTDIR}/drivers/ssd1351.o.d ${OBJECTDIR}/peripherals/gpio.o.d ${OBJECTDIR}/peripherals/adc.o.d ${OBJECTDIR}/peripherals/pwm.o.d ${OBJECTDIR}/peripherals/rtc.o.d ${OBJECTDIR}/peripherals/ssd1351p.o.d ${OBJECTDIR}/peripherals/i2c.o.d ${OBJECTDIR}/peripherals/spi.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/applications/main/appmain.o ${OBJECTDIR}/api/graphics/font.o ${OBJECTDIR}/api/graphics/gfx.o ${OBJECTDIR}/api/bluetooth.o ${OBJECTDIR}/api/oled.o ${OBJECTDIR}/api/power_monitor.o ${OBJECTDIR}/api/sensors.o ${OBJECTDIR}/api/usb.o ${OBJECTDIR}/api/app.o ${OBJECTDIR}/api/clock.o ${OBJECTDIR}/api/compass.o ${OBJECTDIR}/core/scheduler.o ${OBJECTDIR}/core/cpu.o ${OBJECTDIR}/core/systick.o ${OBJECTDIR}/core/traps.o ${OBJECTDIR}/core/os.o ${OBJECTDIR}/drivers/HMC5883.o ${OBJECTDIR}/drivers/MMA7455.o ${OBJECTDIR}/drivers/ssd1351.o ${OBJECTDIR}/peripherals/gpio.o ${OBJECTDIR}/peripherals/adc.o ${OBJECTDIR}/peripherals/pwm.o ${OBJECTDIR}/peripherals/rtc.o ${OBJECTDIR}/peripherals/ssd1351p.o ${OBJECTDIR}/peripherals/i2c.o ${OBJECTDIR}/peripherals/spi.o ${OBJECTDIR}/main.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Zeitgeber.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ256DA206
MP_LINKER_FILE_OPTION=,--script="app_hid_boot_p24FJ256DA206.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/applications/main/appmain.o: applications/main/appmain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/applications/main 
	@${RM} ${OBJECTDIR}/applications/main/appmain.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  applications/main/appmain.c  -o ${OBJECTDIR}/applications/main/appmain.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/applications/main/appmain.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/applications/main/appmain.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/graphics/font.o: api/graphics/font.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api/graphics 
	@${RM} ${OBJECTDIR}/api/graphics/font.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/graphics/font.c  -o ${OBJECTDIR}/api/graphics/font.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/graphics/font.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/graphics/font.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/graphics/gfx.o: api/graphics/gfx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api/graphics 
	@${RM} ${OBJECTDIR}/api/graphics/gfx.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/graphics/gfx.c  -o ${OBJECTDIR}/api/graphics/gfx.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/graphics/gfx.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/graphics/gfx.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/bluetooth.o: api/bluetooth.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api 
	@${RM} ${OBJECTDIR}/api/bluetooth.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/bluetooth.c  -o ${OBJECTDIR}/api/bluetooth.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/bluetooth.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/bluetooth.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/oled.o: api/oled.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api 
	@${RM} ${OBJECTDIR}/api/oled.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/oled.c  -o ${OBJECTDIR}/api/oled.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/oled.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/oled.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/power_monitor.o: api/power_monitor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api 
	@${RM} ${OBJECTDIR}/api/power_monitor.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/power_monitor.c  -o ${OBJECTDIR}/api/power_monitor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/power_monitor.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/power_monitor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/sensors.o: api/sensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api 
	@${RM} ${OBJECTDIR}/api/sensors.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/sensors.c  -o ${OBJECTDIR}/api/sensors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/sensors.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/sensors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/usb.o: api/usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api 
	@${RM} ${OBJECTDIR}/api/usb.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/usb.c  -o ${OBJECTDIR}/api/usb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/usb.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/usb.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/app.o: api/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api 
	@${RM} ${OBJECTDIR}/api/app.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/app.c  -o ${OBJECTDIR}/api/app.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/app.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/app.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/clock.o: api/clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api 
	@${RM} ${OBJECTDIR}/api/clock.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/clock.c  -o ${OBJECTDIR}/api/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/clock.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/clock.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/compass.o: api/compass.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api 
	@${RM} ${OBJECTDIR}/api/compass.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/compass.c  -o ${OBJECTDIR}/api/compass.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/compass.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/compass.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/core/scheduler.o: core/scheduler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/core 
	@${RM} ${OBJECTDIR}/core/scheduler.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  core/scheduler.c  -o ${OBJECTDIR}/core/scheduler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/core/scheduler.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/core/scheduler.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/core/cpu.o: core/cpu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/core 
	@${RM} ${OBJECTDIR}/core/cpu.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  core/cpu.c  -o ${OBJECTDIR}/core/cpu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/core/cpu.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/core/cpu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/core/systick.o: core/systick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/core 
	@${RM} ${OBJECTDIR}/core/systick.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  core/systick.c  -o ${OBJECTDIR}/core/systick.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/core/systick.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/core/systick.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/core/traps.o: core/traps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/core 
	@${RM} ${OBJECTDIR}/core/traps.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  core/traps.c  -o ${OBJECTDIR}/core/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/core/traps.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/core/traps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/core/os.o: core/os.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/core 
	@${RM} ${OBJECTDIR}/core/os.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  core/os.c  -o ${OBJECTDIR}/core/os.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/core/os.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/core/os.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/drivers/HMC5883.o: drivers/HMC5883.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/drivers 
	@${RM} ${OBJECTDIR}/drivers/HMC5883.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drivers/HMC5883.c  -o ${OBJECTDIR}/drivers/HMC5883.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/drivers/HMC5883.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/drivers/HMC5883.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/drivers/MMA7455.o: drivers/MMA7455.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/drivers 
	@${RM} ${OBJECTDIR}/drivers/MMA7455.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drivers/MMA7455.c  -o ${OBJECTDIR}/drivers/MMA7455.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/drivers/MMA7455.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/drivers/MMA7455.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/drivers/ssd1351.o: drivers/ssd1351.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/drivers 
	@${RM} ${OBJECTDIR}/drivers/ssd1351.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drivers/ssd1351.c  -o ${OBJECTDIR}/drivers/ssd1351.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/drivers/ssd1351.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/drivers/ssd1351.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/peripherals/gpio.o: peripherals/gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/peripherals 
	@${RM} ${OBJECTDIR}/peripherals/gpio.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  peripherals/gpio.c  -o ${OBJECTDIR}/peripherals/gpio.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/peripherals/gpio.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/peripherals/gpio.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/peripherals/adc.o: peripherals/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/peripherals 
	@${RM} ${OBJECTDIR}/peripherals/adc.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  peripherals/adc.c  -o ${OBJECTDIR}/peripherals/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/peripherals/adc.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/peripherals/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/peripherals/pwm.o: peripherals/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/peripherals 
	@${RM} ${OBJECTDIR}/peripherals/pwm.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  peripherals/pwm.c  -o ${OBJECTDIR}/peripherals/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/peripherals/pwm.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/peripherals/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/peripherals/rtc.o: peripherals/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/peripherals 
	@${RM} ${OBJECTDIR}/peripherals/rtc.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  peripherals/rtc.c  -o ${OBJECTDIR}/peripherals/rtc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/peripherals/rtc.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/peripherals/rtc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/peripherals/ssd1351p.o: peripherals/ssd1351p.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/peripherals 
	@${RM} ${OBJECTDIR}/peripherals/ssd1351p.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  peripherals/ssd1351p.c  -o ${OBJECTDIR}/peripherals/ssd1351p.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/peripherals/ssd1351p.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/peripherals/ssd1351p.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/peripherals/i2c.o: peripherals/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/peripherals 
	@${RM} ${OBJECTDIR}/peripherals/i2c.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  peripherals/i2c.c  -o ${OBJECTDIR}/peripherals/i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/peripherals/i2c.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/peripherals/i2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/peripherals/spi.o: peripherals/spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/peripherals 
	@${RM} ${OBJECTDIR}/peripherals/spi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  peripherals/spi.c  -o ${OBJECTDIR}/peripherals/spi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/peripherals/spi.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/peripherals/spi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/applications/main/appmain.o: applications/main/appmain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/applications/main 
	@${RM} ${OBJECTDIR}/applications/main/appmain.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  applications/main/appmain.c  -o ${OBJECTDIR}/applications/main/appmain.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/applications/main/appmain.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/applications/main/appmain.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/graphics/font.o: api/graphics/font.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api/graphics 
	@${RM} ${OBJECTDIR}/api/graphics/font.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/graphics/font.c  -o ${OBJECTDIR}/api/graphics/font.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/graphics/font.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/graphics/font.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/graphics/gfx.o: api/graphics/gfx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api/graphics 
	@${RM} ${OBJECTDIR}/api/graphics/gfx.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/graphics/gfx.c  -o ${OBJECTDIR}/api/graphics/gfx.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/graphics/gfx.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/graphics/gfx.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/bluetooth.o: api/bluetooth.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api 
	@${RM} ${OBJECTDIR}/api/bluetooth.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/bluetooth.c  -o ${OBJECTDIR}/api/bluetooth.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/bluetooth.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/bluetooth.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/oled.o: api/oled.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api 
	@${RM} ${OBJECTDIR}/api/oled.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/oled.c  -o ${OBJECTDIR}/api/oled.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/oled.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/oled.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/power_monitor.o: api/power_monitor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api 
	@${RM} ${OBJECTDIR}/api/power_monitor.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/power_monitor.c  -o ${OBJECTDIR}/api/power_monitor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/power_monitor.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/power_monitor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/sensors.o: api/sensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api 
	@${RM} ${OBJECTDIR}/api/sensors.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/sensors.c  -o ${OBJECTDIR}/api/sensors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/sensors.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/sensors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/usb.o: api/usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api 
	@${RM} ${OBJECTDIR}/api/usb.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/usb.c  -o ${OBJECTDIR}/api/usb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/usb.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/usb.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/app.o: api/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api 
	@${RM} ${OBJECTDIR}/api/app.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/app.c  -o ${OBJECTDIR}/api/app.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/app.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/app.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/clock.o: api/clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api 
	@${RM} ${OBJECTDIR}/api/clock.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/clock.c  -o ${OBJECTDIR}/api/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/clock.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/clock.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/api/compass.o: api/compass.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/api 
	@${RM} ${OBJECTDIR}/api/compass.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  api/compass.c  -o ${OBJECTDIR}/api/compass.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/api/compass.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/api/compass.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/core/scheduler.o: core/scheduler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/core 
	@${RM} ${OBJECTDIR}/core/scheduler.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  core/scheduler.c  -o ${OBJECTDIR}/core/scheduler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/core/scheduler.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/core/scheduler.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/core/cpu.o: core/cpu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/core 
	@${RM} ${OBJECTDIR}/core/cpu.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  core/cpu.c  -o ${OBJECTDIR}/core/cpu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/core/cpu.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/core/cpu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/core/systick.o: core/systick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/core 
	@${RM} ${OBJECTDIR}/core/systick.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  core/systick.c  -o ${OBJECTDIR}/core/systick.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/core/systick.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/core/systick.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/core/traps.o: core/traps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/core 
	@${RM} ${OBJECTDIR}/core/traps.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  core/traps.c  -o ${OBJECTDIR}/core/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/core/traps.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/core/traps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/core/os.o: core/os.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/core 
	@${RM} ${OBJECTDIR}/core/os.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  core/os.c  -o ${OBJECTDIR}/core/os.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/core/os.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/core/os.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/drivers/HMC5883.o: drivers/HMC5883.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/drivers 
	@${RM} ${OBJECTDIR}/drivers/HMC5883.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drivers/HMC5883.c  -o ${OBJECTDIR}/drivers/HMC5883.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/drivers/HMC5883.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/drivers/HMC5883.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/drivers/MMA7455.o: drivers/MMA7455.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/drivers 
	@${RM} ${OBJECTDIR}/drivers/MMA7455.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drivers/MMA7455.c  -o ${OBJECTDIR}/drivers/MMA7455.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/drivers/MMA7455.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/drivers/MMA7455.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/drivers/ssd1351.o: drivers/ssd1351.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/drivers 
	@${RM} ${OBJECTDIR}/drivers/ssd1351.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drivers/ssd1351.c  -o ${OBJECTDIR}/drivers/ssd1351.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/drivers/ssd1351.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/drivers/ssd1351.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/peripherals/gpio.o: peripherals/gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/peripherals 
	@${RM} ${OBJECTDIR}/peripherals/gpio.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  peripherals/gpio.c  -o ${OBJECTDIR}/peripherals/gpio.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/peripherals/gpio.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/peripherals/gpio.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/peripherals/adc.o: peripherals/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/peripherals 
	@${RM} ${OBJECTDIR}/peripherals/adc.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  peripherals/adc.c  -o ${OBJECTDIR}/peripherals/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/peripherals/adc.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/peripherals/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/peripherals/pwm.o: peripherals/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/peripherals 
	@${RM} ${OBJECTDIR}/peripherals/pwm.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  peripherals/pwm.c  -o ${OBJECTDIR}/peripherals/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/peripherals/pwm.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/peripherals/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/peripherals/rtc.o: peripherals/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/peripherals 
	@${RM} ${OBJECTDIR}/peripherals/rtc.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  peripherals/rtc.c  -o ${OBJECTDIR}/peripherals/rtc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/peripherals/rtc.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/peripherals/rtc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/peripherals/ssd1351p.o: peripherals/ssd1351p.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/peripherals 
	@${RM} ${OBJECTDIR}/peripherals/ssd1351p.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  peripherals/ssd1351p.c  -o ${OBJECTDIR}/peripherals/ssd1351p.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/peripherals/ssd1351p.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/peripherals/ssd1351p.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/peripherals/i2c.o: peripherals/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/peripherals 
	@${RM} ${OBJECTDIR}/peripherals/i2c.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  peripherals/i2c.c  -o ${OBJECTDIR}/peripherals/i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/peripherals/i2c.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/peripherals/i2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/peripherals/spi.o: peripherals/spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/peripherals 
	@${RM} ${OBJECTDIR}/peripherals/spi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  peripherals/spi.c  -o ${OBJECTDIR}/peripherals/spi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/peripherals/spi.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/peripherals/spi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -menable-large-arrays -O0 -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Zeitgeber.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    app_hid_boot_p24FJ256DA206.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Zeitgeber.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -Wl,--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PICKIT2=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Zeitgeber.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   app_hid_boot_p24FJ256DA206.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Zeitgeber.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Zeitgeber.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
