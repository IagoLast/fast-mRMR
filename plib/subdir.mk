################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../plib/Histogram.cpp \
../plib/JointProb.cpp \
../plib/MutualInfo.cpp \
../plib/ProbTable.cpp \
../plib/RawData.cpp 

OBJS += \
./plib/Histogram.o \
./plib/JointProb.o \
./plib/MutualInfo.o \
./plib/ProbTable.o \
./plib/RawData.o 

CPP_DEPS += \
./plib/Histogram.d \
./plib/JointProb.d \
./plib/MutualInfo.d \
./plib/ProbTable.d \
./plib/RawData.d 


# Each subdirectory must supply rules for building sources it contributes
plib/%.o: ../plib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


