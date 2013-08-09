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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1847356646/usb_device.o ${OBJECTDIR}/_ext/1933592704/usb_function_hid.o ${OBJECTDIR}/main.o ${OBJECTDIR}/usb_descriptors.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1847356646/usb_device.o.d ${OBJECTDIR}/_ext/1933592704/usb_function_hid.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/usb_descriptors.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1847356646/usb_device.o ${OBJECTDIR}/_ext/1933592704/usb_function_hid.o ${OBJECTDIR}/main.o ${OBJECTDIR}/usb_descriptors.o


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ256DA206
MP_LINKER_FILE_OPTION=,--script=p24FJ256DA206.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1847356646/usb_device.o: C:/Microchip/Microchip/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1847356646 
	@${RM} ${OBJECTDIR}/_ext/1847356646/usb_device.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  C:/Microchip/Microchip/USB/usb_device.c  -o ${OBJECTDIR}/_ext/1847356646/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1847356646/usb_device.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -O0 -I"C:/Microchip/Microchip" -I"C:/Microchip/Microchip/Include" -I"C:/Microchip/Microchip/Include/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1847356646/usb_device.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1933592704/usb_function_hid.o: C:/Microchip/Microchip/USB/HID\ Device\ Driver/usb_function_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1933592704 
	@${RM} ${OBJECTDIR}/_ext/1933592704/usb_function_hid.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "C:/Microchip/Microchip/USB/HID Device Driver/usb_function_hid.c"  -o ${OBJECTDIR}/_ext/1933592704/usb_function_hid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1933592704/usb_function_hid.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -O0 -I"C:/Microchip/Microchip" -I"C:/Microchip/Microchip/Include" -I"C:/Microchip/Microchip/Include/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1933592704/usb_function_hid.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -O0 -I"C:/Microchip/Microchip" -I"C:/Microchip/Microchip/Include" -I"C:/Microchip/Microchip/Include/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/usb_descriptors.o: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_descriptors.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  usb_descriptors.c  -o ${OBJECTDIR}/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_descriptors.o.d"        -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -O0 -I"C:/Microchip/Microchip" -I"C:/Microchip/Microchip/Include" -I"C:/Microchip/Microchip/Include/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/usb_descriptors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1847356646/usb_device.o: C:/Microchip/Microchip/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1847356646 
	@${RM} ${OBJECTDIR}/_ext/1847356646/usb_device.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  C:/Microchip/Microchip/USB/usb_device.c  -o ${OBJECTDIR}/_ext/1847356646/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1847356646/usb_device.o.d"        -g -omf=elf -O0 -I"C:/Microchip/Microchip" -I"C:/Microchip/Microchip/Include" -I"C:/Microchip/Microchip/Include/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1847356646/usb_device.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1933592704/usb_function_hid.o: C:/Microchip/Microchip/USB/HID\ Device\ Driver/usb_function_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1933592704 
	@${RM} ${OBJECTDIR}/_ext/1933592704/usb_function_hid.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "C:/Microchip/Microchip/USB/HID Device Driver/usb_function_hid.c"  -o ${OBJECTDIR}/_ext/1933592704/usb_function_hid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1933592704/usb_function_hid.o.d"        -g -omf=elf -O0 -I"C:/Microchip/Microchip" -I"C:/Microchip/Microchip/Include" -I"C:/Microchip/Microchip/Include/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1933592704/usb_function_hid.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -O0 -I"C:/Microchip/Microchip" -I"C:/Microchip/Microchip/Include" -I"C:/Microchip/Microchip/Include/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/usb_descriptors.o: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_descriptors.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  usb_descriptors.c  -o ${OBJECTDIR}/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_descriptors.o.d"        -g -omf=elf -O0 -I"C:/Microchip/Microchip" -I"C:/Microchip/Microchip/Include" -I"C:/Microchip/Microchip/Include/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/usb_descriptors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
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
dist/${CND_CONF}/${IMAGE_TYPE}/Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -Wl,--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PICKIT2=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Bootloader.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Bootloader.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf 
	
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
