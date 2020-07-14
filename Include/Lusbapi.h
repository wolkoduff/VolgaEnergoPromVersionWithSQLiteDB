#ifndef __LusbapiH__
#define __LusbapiH__

	// --------------------------------------------------------------------------
	// ---------------------------- COMMON PART ---------------------------------
	// --------------------------------------------------------------------------
	#include <windows.h>
	#include "LusbapiTypes.h"

	// ������ ����������
	#define 	VERSION_MAJOR_LUSBAPI 			(0x3)		// ������ ���� �����
	#define 	VERSION_MINOR_LUSBAPI 			(0x4)		// ������ ���� �����
	#define 	CURRENT_VERSION_LUSBAPI			((VERSION_MAJOR_LUSBAPI << 0x10) | VERSION_MINOR_LUSBAPI)

	#define InitLDevice(Slot) OpenLDevice(Slot)

	// ��������������� �������
	extern "C" DWORD WINAPI GetDllVersion(void);
	extern "C" LPVOID WINAPI CreateLInstance(PCHAR const DeviceName);

	// ��������� ������� �������� ������ ������ �� ���� USB
	enum { USB11_LUSBAPI, USB20_LUSBAPI, INVALID_USB_SPEED_LUSBAPI };
	// ������ ���������� �����-���� ����������� ������
	enum { NO_MODULE_MODIFICATION_LUSBAPI = -1 };
	// ����������� ��������� ���-�� ������������ ����������� ������
	const WORD MAX_VIRTUAL_SLOTS_QUANTITY_LUSBAPI = 127;


	// ==========================================================================
	// *************************** L-Card USB BASE ******************************
	// ==========================================================================
	struct ILUSBBASE
	{
		// ������� ������ ���������� ��� ������ � USB ������������
		virtual BOOL WINAPI OpenLDevice(WORD VirtualSlot) = 0;
		virtual BOOL WINAPI CloseLDevice(void) = 0;
		virtual BOOL WINAPI ReleaseLInstance(void) = 0;
		// ��������� ����������� ���������� USB
		virtual HANDLE WINAPI GetModuleHandle(void) = 0;
		// ��������� �������� ������������� ������
		virtual BOOL WINAPI GetModuleName(PCHAR const ModuleName) = 0;
		// ��������� ������� �������� ������ ���� USB
		virtual BOOL WINAPI GetUsbSpeed(BYTE * const UsbSpeed) = 0;
		// ���������� ������� ������� ������������������ ������
		virtual BOOL WINAPI LowPowerMode(BOOL LowPowerFlag) = 0;
		// ������� ������ ������ � ��������� �������
		virtual BOOL WINAPI GetLastErrorInfo(LAST_ERROR_INFO_LUSBAPI * const LastErrorInfo) = 0;
	};




	// ==========================================================================
	// *************************** ������ E14-140 *******************************
	// ==========================================================================
	// ��������� ������� ���������� �������� ���������� ������ E14-140
	enum {	ADC_INPUT_RANGE_10000mV_E140, ADC_INPUT_RANGE_2500mV_E140, ADC_INPUT_RANGE_625mV_E140, ADC_INPUT_RANGE_156mV_E140, INVALID_ADC_INPUT_RANGE_E140 };
	// ��������� ������� ��������� �������� ��������� ��� ���
	enum {	INT_ADC_CLOCK_E140, EXT_ADC_CLOCK_E140, INVALID_ADC_CLOCK_E140 };
	// ��������� ������� ���������� ����������� �������� ��������� ���
	// �� ����� SYN �������� ��������� ������� (������ ��� ����������
	// ��������� �������� ��������� ���)
	enum {	ADC_CLOCK_TRANS_DISABLED_E140, ADC_CLOCK_TRANS_ENABLED_E140, INVALID_ADC_CLOCK_TRANS_E140 };
	// ��������� ���� ������������� ������ E14-140
	enum { 	NO_SYNC_E140, TTL_START_SYNC_E140, TTL_KADR_SYNC_E140, ANALOG_SYNC_E140, INVALID_SYNC_E140 };
	// ��������� ����� ������� ���������� ���
	enum {	DAC_INACCESSIBLED_E140, DAC_ACCESSIBLED_E140, INVALID_DAC_OPTION_E140 };
	// ��������� ������� ������� ������ E14-140
	enum {	REVISION_A_E140, REVISION_B_E140, INVALID_REVISION_E140 };
	// ��������� ������� ������������� ��������� ������ ��� � ���
	enum {	DIS_ADC_DAC_SYNC_E140, ENA_ADC_DAC_SYNC_E140, INVALID_ADC_DAC_SYNC_E140 };
	// ��������� ������� ������� ��������� ���������� ���
	enum {	NORMAL_DAC_ON_STOP_E140, ZERO_DAC_ON_STOP_E140, INVALID_DAC_ON_STOP_E140 };

	// ��������� ��� ������ � �������
	enum 	{
				MAX_CONTROL_TABLE_LENGTH_E140 = 128,
				ADC_INPUT_RANGES_QUANTITY_E140 = INVALID_ADC_INPUT_RANGE_E140,
				ADC_CALIBR_COEFS_QUANTITY_E140 = ADC_INPUT_RANGES_QUANTITY_E140,
				DAC_CHANNELS_QUANTITY_E140 = 0x2, DAC_CALIBR_COEFS_QUANTITY_E140 = DAC_CHANNELS_QUANTITY_E140,
				TTL_LINES_QUANTITY_E140 = 0x10,	  		// ���-�� �������� �����
				USER_FLASH_SIZE_E140 = 0x200,   			// ������ ������� ����������������� ���� � ������
				REVISIONS_QUANTITY_E140 = INVALID_REVISION_E140,		// ���-�� ������� (�����������) ������
			};
	// ��������� �������� ���������� ��� � �
	const double ADC_INPUT_RANGES_E140[ADC_INPUT_RANGES_QUANTITY_E140] =
	{
		10.0, 10.0/4.0, 10.0/16.0, 10.0/64.0
	};
	// ��������� ��������� ���������� ��� � �
	const double DAC_OUTPUT_RANGE_E140 = 5.0;
	// ��������� ������� ������
	const BYTE REVISIONS_E140[REVISIONS_QUANTITY_E140] = { 'A', 'B' };

	#pragma pack(1)
	// ��������� � ����������� �� ������ E14-140
	struct MODULE_DESCRIPTION_E140
	{
		MODULE_INFO_LUSBAPI     Module;		// ����� ���������� � ������
		INTERFACE_INFO_LUSBAPI  Interface;	// ���������� �� ������������ ����������
		MCU_INFO_LUSBAPI<VERSION_INFO_LUSBAPI>		Mcu;	// ���������� � ����������������
		ADC_INFO_LUSBAPI        Adc;			// ���������� � ���
		DAC_INFO_LUSBAPI        Dac;			// ���������� � ���
		DIGITAL_IO_INFO_LUSBAPI DigitalIo;	// ���������� � �������� �����-������
	};
	// ��������� ����������������� ���� ������ E14-140
	struct USER_FLASH_E140
	{
		BYTE Buffer[USER_FLASH_SIZE_E140];
	};
	// ���������, �������� ����� ������ ��� ��� ������ E14-140
	struct ADC_PARS_E140
	{
		WORD ClkSource;							// �������� �������� ��������� ��� ������� ���
		WORD EnableClkOutput;					// ���������� ���������� �������� ��������� ������� ���
		WORD InputMode;							// ����� ����� ����� � ���
		WORD SynchroAdType;						// ��� ���������� �������������
		WORD SynchroAdMode; 						// ����� ���������� ������������
		WORD SynchroAdChannel;  				// ����� ��� ��� ���������� �������������
		SHORT SynchroAdPorog; 					// ����� ������������ ��� ��� ���������� �������������
		WORD ChannelsQuantity;					// ����� �������� �������
		WORD ControlTable[128];					// ����������� ������� � ��������� ��������
		double AdcRate;							// ������� ������ ��� � ���
		double InterKadrDelay;					// ����������� �������� � ��
		double KadrRate;							// ������� ����� � ���
	};
	// ���������, �������� ����� ��������� ������ ��� ��� ������ E14-140
	struct DAC_PARS_E140
	{
		BYTE SyncWithADC;							// 0 = ������� ���� ���; !0 = ���������������� � ������ ���
		BYTE SetZeroOnStop;						// !0 = ��� ��������� ���������� ������ ���������� �� ������ ��� 0 �
		double DacRate;							// ������� ������ ��� � ���
	};
	#pragma pack()

	//-----------------------------------------------------------------------------
	// ��������� ��� ������ E14-140
	//-----------------------------------------------------------------------------
	struct ILE140 : public ILUSBBASE
	{
		// ������� ��� ������ � ���
		virtual BOOL WINAPI GET_ADC_PARS(ADC_PARS_E140 * const AdcPars) = 0;
		virtual BOOL WINAPI SET_ADC_PARS(ADC_PARS_E140 * const AdcPars) = 0;
		virtual BOOL WINAPI START_ADC(void) = 0;
		virtual BOOL WINAPI STOP_ADC(void) = 0;
		virtual BOOL WINAPI ADC_KADR(SHORT * const Data) = 0;
		virtual BOOL WINAPI ADC_SAMPLE(SHORT * const AdcData, WORD AdcChannel) = 0;
		virtual BOOL WINAPI ReadData(IO_REQUEST_LUSBAPI * const ReadRequest) = 0;

		// ������� ��� ������ � ���
		virtual BOOL WINAPI GET_DAC_PARS(DAC_PARS_E140 * const DacPars) = 0;
		virtual BOOL WINAPI SET_DAC_PARS(DAC_PARS_E140 * const DacPars) = 0;
		virtual BOOL WINAPI START_DAC(void) = 0;
		virtual BOOL WINAPI STOP_DAC(void) = 0;
		virtual BOOL WINAPI WriteData(IO_REQUEST_LUSBAPI * const WriteRequest) = 0;
		virtual BOOL WINAPI DAC_SAMPLE(SHORT * const DacData, WORD DacChannel) = 0;
		virtual BOOL WINAPI DAC_SAMPLES(SHORT * const DacData1, SHORT * const DacData2) = 0;

		// ������� ��� ������ � ��� �������
		virtual BOOL WINAPI ENABLE_TTL_OUT(BOOL EnableTtlOut) = 0;
		virtual BOOL WINAPI TTL_IN(WORD * const TtlIn) = 0;
		virtual BOOL WINAPI TTL_OUT(WORD TtlOut) = 0;

		// ������� ��� ������ � ���������������� ����������� ����
		virtual BOOL WINAPI ENABLE_FLASH_WRITE(BOOL IsUserFlashWriteEnabled) = 0;
		virtual BOOL WINAPI READ_FLASH_ARRAY(USER_FLASH_E140 * const UserFlash) = 0;
		virtual BOOL WINAPI WRITE_FLASH_ARRAY(USER_FLASH_E140 * const UserFlash) = 0;

		// ������� ��� ������ �� ��������� ����������� ����
		virtual BOOL WINAPI GET_MODULE_DESCRIPTION(MODULE_DESCRIPTION_E140 * const ModuleDescription) = 0;
		virtual BOOL WINAPI SAVE_MODULE_DESCRIPTION(MODULE_DESCRIPTION_E140 * const ModuleDescription) = 0;

		// ������� ��� ������� ������ � ����������������
		virtual BOOL WINAPI GetArray(BYTE * const Buffer, WORD Size, WORD Address) = 0;
		virtual BOOL WINAPI PutArray(BYTE * const Buffer, WORD Size, WORD Address) = 0;
	};





	// ==========================================================================
	// *************************** ������ E-154 *******************************
	// ==========================================================================
	// ��������� ������� ���������� �������� ���������� ������ E-154
	enum {	ADC_INPUT_RANGE_5000mV_E154, ADC_INPUT_RANGE_1600mV_E154, ADC_INPUT_RANGE_500mV_E154, ADC_INPUT_RANGE_160mV_E154, INVALID_ADC_INPUT_RANGE_E154 };
	// ��������� ������� ��������� �������� ��������� ��� ���, ��������� ��� ������������� � E14-140
	enum {	INT_ADC_CLOCK_E154, EXT_ADC_CLOCK_E154, INVALID_ADC_CLOCK_E154 };
	// ��������� ������� ���������� ����������� �������� ��������� ���
	// �� ����� SYN �������� ��������� ������� (������ ��� ����������
	// ��������� �������� ��������� ���),   ��������� ��� ������������� � E14-140
	enum {	ADC_CLOCK_TRANS_DISABLED_E154, ADC_CLOCK_TRANS_ENABLED_E154, INVALID_ADC_CLOCK_TRANS_E154 };
	// ��������� ���� ������������� ������ E-154
	enum { 	NO_SYNC_E154, TTL_START_SYNC_E154, TTL_KADR_SYNC_E154, ANALOG_SYNC_E154, INVALID_SYNC_E154 };
	// ��������� ����� ������� ���������� ���
	enum {	DAC_INACCESSIBLED_E154, DAC_ACCESSIBLED_E154, INVALID_DAC_OPTION_E154 };
	// ��������� ������� ������� ������ E-154
	enum {	REVISION_A_E154, INVALID_REVISION_E154 };

	// ��������� ��� ������ � �������
	enum 	{
				MAX_CONTROL_TABLE_LENGTH_E154 = 16,
				ADC_INPUT_RANGES_QUANTITY_E154 = INVALID_ADC_INPUT_RANGE_E154,
				ADC_CALIBR_COEFS_QUANTITY_E154 = ADC_INPUT_RANGES_QUANTITY_E154,
				DAC_CHANNELS_QUANTITY_E154 = 0x1, DAC_CALIBR_COEFS_QUANTITY_E154 = DAC_CHANNELS_QUANTITY_E154,
				TTL_LINES_QUANTITY_E154 = 0x08,	  		// ���-�� �������� �����
				USER_FLASH_SIZE_E154 = 0x80,   			// ������ ������� ����������������� ���� � ������
				REVISIONS_QUANTITY_E154 = INVALID_REVISION_E154,		// ���-�� ������� (�����������) ������
			};
	// ��������� �������� ���������� ��� � �
	const double ADC_INPUT_RANGES_E154[ADC_INPUT_RANGES_QUANTITY_E154] =
	{
		5.0, 1.6, 0.5, 0.16
	};
	// ��������� ��������� ���������� ��� � �
	const double DAC_OUTPUT_RANGE_E154 = 5.0;
	// ��������� ������� ������
	const BYTE REVISIONS_E154[REVISIONS_QUANTITY_E154] = { 'A' };

	#pragma pack(1)
	// ��������� � ����������� �� ������ E-154
	struct MODULE_DESCRIPTION_E154
	{
		MODULE_INFO_LUSBAPI     Module;		// ����� ���������� � ������
		INTERFACE_INFO_LUSBAPI  Interface;	// ���������� �� ������������ ����������
		MCU_INFO_LUSBAPI<VERSION_INFO_LUSBAPI>		Mcu;	// ���������� � ����������������
		ADC_INFO_LUSBAPI        Adc;			// ���������� � ���
		DAC_INFO_LUSBAPI        Dac;			// ���������� � ���
		DIGITAL_IO_INFO_LUSBAPI DigitalIo;	// ���������� � �������� �����-������
	};
	// ���������, �������� ����� ������ ��� ��� ������ E14-154
	struct ADC_PARS_E154
	{
		WORD ClkSource;							// �������� �������� ��������� ��� ������� ���
		WORD EnableClkOutput;					// ���������� ���������� �������� ��������� ������� ���
		WORD InputMode;							// ����� ����� ����� � ���
		WORD SynchroAdType;						// ��� ���������� �������������
		WORD SynchroAdMode; 						// ����� ���������� ������������
		WORD SynchroAdChannel;  				// ����� ��� ��� ���������� �������������
		SHORT SynchroAdPorog; 					// ����� ������������ ��� ��� ���������� �������������
		WORD ChannelsQuantity;					// ����� �������� �������
		WORD ControlTable[16];					// ����������� ������� � ��������� ��������
		double AdcRate;	  			  			// ������� ������ ��� � ���
		double InterKadrDelay;		  			// ����������� �������� � ��
		double KadrRate;							// ������� ����� � ���
	};

	#pragma pack()

	//-----------------------------------------------------------------------------
	// ��������� ��� ������ E14-154
	//-----------------------------------------------------------------------------
	struct ILE154 : public ILUSBBASE
	{
		// ������� ��� ������ � ���
		virtual BOOL WINAPI GET_ADC_PARS(ADC_PARS_E154 * const AdcPars) = 0;
		virtual BOOL WINAPI SET_ADC_PARS(ADC_PARS_E154 * const AdcPars) = 0;
		virtual BOOL WINAPI START_ADC(void) = 0;
		virtual BOOL WINAPI STOP_ADC(void) = 0;
		virtual BOOL WINAPI ADC_KADR(SHORT * const Data) = 0;
		virtual BOOL WINAPI ADC_SAMPLE(SHORT * const AdcData, WORD AdcChannel) = 0;
		virtual BOOL WINAPI ReadData(IO_REQUEST_LUSBAPI * const ReadRequest) = 0;
		virtual BOOL WINAPI ProcessArray(SHORT *src, double *dest, DWORD size, BOOL calibr, BOOL volt) = 0;
		virtual BOOL WINAPI ProcessOnePoint(SHORT src, double *dest, DWORD channel, BOOL calibr, BOOL volt) = 0;
		virtual BOOL WINAPI FIFO_STATUS(DWORD *FifoOverflowFlag, double *FifoMaxPercentLoad, DWORD *FifoSize, DWORD *MaxFifoBytesUsed) = 0;

		// ������� ��� ������ � ���
		virtual BOOL WINAPI DAC_SAMPLE(SHORT * const DacData, WORD DacChannel) = 0;
		virtual BOOL WINAPI DAC_SAMPLE_VOLT(double  const DacData, BOOL calibr) = 0;

		// ������� ��� ������ � ��� �������
		virtual BOOL WINAPI ENABLE_TTL_OUT(BOOL EnableTtlOut) = 0;
		virtual BOOL WINAPI TTL_IN(WORD * const TtlIn) = 0;
		virtual BOOL WINAPI TTL_OUT(WORD TtlOut) = 0;

		// ������� ��� ������ � ���������������� ����������� ����
		virtual BOOL WINAPI ENABLE_FLASH_WRITE(BOOL IsUserFlashWriteEnabled) = 0;
		virtual BOOL WINAPI READ_FLASH_ARRAY(BYTE * const UserFlash) = 0;
		virtual BOOL WINAPI WRITE_FLASH_ARRAY(BYTE * const UserFlash) = 0;

		// ������� ��� ������ �� ��������� ����������� ����
		virtual BOOL WINAPI GET_MODULE_DESCRIPTION(MODULE_DESCRIPTION_E154 * const ModuleDescription) = 0;
		virtual BOOL WINAPI SAVE_MODULE_DESCRIPTION(MODULE_DESCRIPTION_E154 * const ModuleDescription) = 0;

		// ������� ��� ������� ������ � ����������������
		virtual BOOL WINAPI GetArray(BYTE * const Buffer, WORD Size, WORD Address) = 0;
		virtual BOOL WINAPI PutArray(BYTE * const Buffer, WORD Size, WORD Address) = 0;
	};




	// ==========================================================================
	// *************************** ������ E14-440 *******************************
	// ==========================================================================
	// ��������� ��������� ������ ������ E14-440
	enum {	INIT_E440, RESET_E440, INVALID_RESET_TYPE_E440 };
	// ��������� ������� ��������� �������� ��������� ��� ���
	enum	{	INT_ADC_CLOCK_E440, INT_ADC_CLOCK_WITH_TRANS_E440, EXT_ADC_CLOCK_E440, INVALID_ADC_CLOCK_E440 };
	// ��������� ������� ���������� �������� ���������� ������ E14-440
	enum {	ADC_INPUT_RANGE_10000mV_E440, ADC_INPUT_RANGE_2500mV_E440, ADC_INPUT_RANGE_625mV_E440, ADC_INPUT_RANGE_156mV_E440, INVALID_ADC_INPUT_RANGE_E440 };
	// ��������� ���� ������������� ������ E14-440
	enum {	NO_SYNC_E440, TTL_START_SYNC_E440, TTL_KADR_SYNC_E440, ANALOG_SYNC_E440, INVALID_SYNC_E440 };
	// ��������� ����� ������� ���������� ���
	enum {	DAC_INACCESSIBLED_E440, DAC_ACCESSIBLED_E440, INVALID_DAC_OPTION_E440 };
	// ��������� ���� DSP (������ ������ ADSP-2185)
	enum {	ADSP2184_E440, ADSP2185_E440, ADSP2186_E440, INVALID_DSP_TYPE_E440 };
	// ��������� �������� ������� ������ (������ ������ 24000 ���)
	enum {	F14745_E440, F16667_E440, F20000_E440, F24000_E440, INVALID_QUARTZ_FREQ_E440 };
	// ��������� ������� ������� ������ E14-440
	enum	{	REVISION_A_E440, REVISION_B_E440, REVISION_C_E440, REVISION_D_E440, REVISION_E_E440, REVISION_F_E440, INVALID_REVISION_E440 };

	// ��������� ��� ������ � �������
	enum 	{
				MAX_CONTROL_TABLE_LENGTH_E440 = 128,
				ADC_INPUT_RANGES_QUANTITY_E440 = INVALID_ADC_INPUT_RANGE_E440,
				ADC_CALIBR_COEFS_QUANTITY_E440 = ADC_INPUT_RANGES_QUANTITY_E440,
				MAX_ADC_FIFO_SIZE_E440 = 0x3000,			// 12288
				DAC_CHANNELS_QUANTITY_E440 = 0x2, DAC_CALIBR_COEFS_QUANTITY_E440 = DAC_CHANNELS_QUANTITY_E440,
				MAX_DAC_FIFO_SIZE_E440 = 0x0FC0,			// 4032
				TTL_LINES_QUANTITY_E440 = 0x10, 			// ���-�� �������� �����
				REVISIONS_QUANTITY_E440 = INVALID_REVISION_E440,		// ���-�� ������� (�����������) ������
			};
	// ��������� �������� ���������� ��� � �
	const double ADC_INPUT_RANGES_E440[ADC_INPUT_RANGES_QUANTITY_E440] =
	{
		10.0, 10.0/4.0, 10.0/16.0, 10.0/64.0
	};
	// ��������� ��������� ���������� ��� � �
	const double DAC_OUTPUT_RANGE_E440 = 5.0;
	// ��������� ������� ������
	const BYTE REVISIONS_E440[REVISIONS_QUANTITY_E440] = { 'A', 'B', 'C', 'D', 'E', 'F' };

	#pragma pack(1)
	// ��������� � ����������� �� ������ E14-440
	struct MODULE_DESCRIPTION_E440
	{
		MODULE_INFO_LUSBAPI     Module;		// ����� ���������� � ������
		INTERFACE_INFO_LUSBAPI  Interface;	// ���������� �� ������������ ����������
		MCU_INFO_LUSBAPI<VERSION_INFO_LUSBAPI>		Mcu;	// ���������� � ����������������
		DSP_INFO_LUSBAPI        Dsp;			// ���������� � DSP
		ADC_INFO_LUSBAPI        Adc;			// ���������� � ���
		DAC_INFO_LUSBAPI        Dac;			// ���������� � ���
		DIGITAL_IO_INFO_LUSBAPI DigitalIo;	// ���������� � �������� �����-������
	};
	// ���������, �������� ����� ������ ��� ��� ������ E-440
	struct ADC_PARS_E440
	{
		BOOL IsAdcEnabled;		 			// ������ ������ ��� (������ ��� ������)
		BOOL IsCorrectionEnabled;			// ���������� ����������� �������������� ������ �� ������ �������� DSP
		WORD AdcClockSource;					// �������� �������� ��������� ������� ���: ���������� ��� �������
		WORD InputMode;						// ����� ����� ����� � ���
		WORD SynchroAdType;					// ��� ���������� �������������
		WORD SynchroAdMode; 					// ����� ���������� ������������
		WORD SynchroAdChannel;  			// ����� ��� ��� ���������� �������������
		SHORT SynchroAdPorog; 				// ����� ������������ ��� ��� ���������� �������������
		WORD ChannelsQuantity;				// ����� �������� �������
		WORD ControlTable[MAX_CONTROL_TABLE_LENGTH_E440];		// ����������� ������� � ��������� ��������
		double AdcRate;	  			  		// ������� ������ ��� � ���
		double InterKadrDelay;		  		// ����������� �������� � ��
		double KadrRate;					// ������� ����� � ���
		WORD AdcFifoBaseAddress;			// ������� ����� FIFO ������ ���
		WORD AdcFifoLength;					// ����� FIFO ������ ���
		double AdcOffsetCoefs[ADC_CALIBR_COEFS_QUANTITY_E440];	// ��������	���: 4���������
		double AdcScaleCoefs[ADC_CALIBR_COEFS_QUANTITY_E440];		// ������� ���	: 4���������
	};

	// ���������, �������� ����� ������ ��� ��� ������ E-440
	struct DAC_PARS_E440
	{
		BOOL DacEnabled;						// ����������/���������� ������ ���
		double DacRate;	  			  		// ������� ������ ��� � ���
		WORD DacFifoBaseAddress;			// ������� ����� FIFO ������ ���
		WORD DacFifoLength;					// ����� FIFO ������ ���
	};
	#pragma pack()

	// ����� ������ �������� ����� ������ � ������ �������� �������� DSP
	const WORD DataBaseAddress_E440 = 0x30;
	// ���������� �������� LBIOS ��� ������ E14-440 (������������ � ������ �������� DSP)
	#define 	  	L_PROGRAM_BASE_ADDRESS_E440				(DataBaseAddress_E440 + 0x0)
	#define 	  	L_READY_E440 									(DataBaseAddress_E440 + 0x1)
	#define	  	L_TMODE1_E440 									(DataBaseAddress_E440 + 0x2)
	#define	  	L_TMODE2_E440 									(DataBaseAddress_E440 + 0x3)
	#define	  	L_TEST_LOAD_E440	 							(DataBaseAddress_E440 + 0x4)
	#define	  	L_COMMAND_E440	 			      			(DataBaseAddress_E440 + 0x5)

	#define		L_DAC_SCLK_DIV_E440							(DataBaseAddress_E440 + 0x7)
	#define		L_DAC_RATE_E440								(DataBaseAddress_E440 + 0x8)
	#define	  	L_ADC_RATE_E440  			      			(DataBaseAddress_E440 + 0x9)
	#define		L_ADC_ENABLED_E440	 						(DataBaseAddress_E440 + 0xA)
	#define		L_ADC_FIFO_BASE_ADDRESS_E440				(DataBaseAddress_E440 + 0xB)
	#define		L_CUR_ADC_FIFO_LENGTH_E440					(DataBaseAddress_E440 + 0xC)
	#define		L_ADC_FIFO_LENGTH_E440						(DataBaseAddress_E440 + 0xE)
	#define		L_CORRECTION_ENABLED_E440					(DataBaseAddress_E440 + 0xF)
	#define		L_LBIOS_VERSION_E440							(DataBaseAddress_E440 + 0x10)
	#define		L_ADC_SAMPLE_E440								(DataBaseAddress_E440 + 0x11)
	#define		L_ADC_CHANNEL_E440	 						(DataBaseAddress_E440 + 0x12)
	#define		L_INPUT_MODE_E440								(DataBaseAddress_E440 + 0x13)
	#define		L_SYNCHRO_AD_CHANNEL_E440					(DataBaseAddress_E440 + 0x16)
	#define		L_SYNCHRO_AD_POROG_E440						(DataBaseAddress_E440 + 0x17)
	#define		L_SYNCHRO_AD_MODE_E440 						(DataBaseAddress_E440 + 0x18)
	#define		L_SYNCHRO_AD_TYPE_E440 						(DataBaseAddress_E440 + 0x19)

	#define		L_CONTROL_TABLE_LENGHT_E440				(DataBaseAddress_E440 + 0x1B)
	#define		L_FIRST_SAMPLE_DELAY_E440					(DataBaseAddress_E440 + 0x1C)
	#define		L_INTER_KADR_DELAY_E440						(DataBaseAddress_E440 + 0x1D)

	#define		L_DAC_SAMPLE_E440								(DataBaseAddress_E440 + 0x20)
	#define		L_DAC_ENABLED_E440					 		(DataBaseAddress_E440 + 0x21)
	#define		L_DAC_FIFO_BASE_ADDRESS_E440				(DataBaseAddress_E440 + 0x22)
	#define		L_CUR_DAC_FIFO_LENGTH_E440					(DataBaseAddress_E440 + 0x24)
	#define		L_DAC_FIFO_LENGTH_E440						(DataBaseAddress_E440 + 0x25)

	#define		L_FLASH_ENABLED_E440 						(DataBaseAddress_E440 + 0x26)
	#define		L_FLASH_ADDRESS_E440 						(DataBaseAddress_E440 + 0x27)
	#define		L_FLASH_DATA_E440 							(DataBaseAddress_E440 + 0x28)

	#define		L_ENABLE_TTL_OUT_E440						(DataBaseAddress_E440 + 0x29)
	#define		L_TTL_OUT_E440									(DataBaseAddress_E440 + 0x2A)
	#define		L_TTL_IN_E440									(DataBaseAddress_E440 + 0x2B)

	#define		L_ADC_CLOCK_SOURCE_E440						(DataBaseAddress_E440 + 0x2F)

	#define		L_SCALE_E440									(DataBaseAddress_E440 + 0x30)
	#define		L_ZERO_E440										(DataBaseAddress_E440 + 0x34)

	#define		L_CONTROL_TABLE_E440							(0x80)

	#define		L_DSP_INFO_STUCTURE_E440					(0x200)

	//-----------------------------------------------------------------------------
	// ��������� ������ E14-440
	//-----------------------------------------------------------------------------
	struct ILE440 : public ILUSBBASE
	{
		// ������� ������ � DSP
		virtual BOOL WINAPI RESET_MODULE(BYTE ResetFlag = INIT_E440) = 0;
		virtual BOOL WINAPI LOAD_MODULE(PCHAR const FileName = NULL) = 0;
		virtual BOOL WINAPI TEST_MODULE(void) = 0;
		virtual BOOL WINAPI SEND_COMMAND(WORD Command) = 0;

		// ������� ��� ������ � ���
		virtual BOOL WINAPI GET_ADC_PARS(ADC_PARS_E440 * const AdcPars) = 0;
		virtual BOOL WINAPI SET_ADC_PARS(ADC_PARS_E440 * const AdcPars) = 0;
		virtual BOOL WINAPI START_ADC(void) = 0;
		virtual BOOL WINAPI STOP_ADC(void) = 0;
		virtual BOOL WINAPI ADC_KADR(SHORT * const Data) = 0;
		virtual BOOL WINAPI ADC_SAMPLE(SHORT * const AdcData, WORD AdcChannel) = 0;
		virtual BOOL WINAPI ReadData(IO_REQUEST_LUSBAPI * const ReadRequest) = 0;

		// ������� ��� ������ � ���
		virtual BOOL WINAPI GET_DAC_PARS(DAC_PARS_E440 * const DacPars) = 0;
		virtual BOOL WINAPI SET_DAC_PARS(DAC_PARS_E440 * const DacPars) = 0;
		virtual BOOL WINAPI START_DAC(void) = 0;
		virtual BOOL WINAPI STOP_DAC(void) = 0;
		virtual BOOL WINAPI WriteData(IO_REQUEST_LUSBAPI * const WriteRequest) = 0;
		virtual BOOL WINAPI DAC_SAMPLE(SHORT * const DacData, WORD DacChannel) = 0;

		// ������� ��� ������ � ��������� �������
		virtual BOOL WINAPI ENABLE_TTL_OUT(BOOL EnableTtlOut) = 0;
		virtual BOOL WINAPI TTL_IN(WORD * const TtlIn) = 0;
		virtual BOOL WINAPI TTL_OUT(WORD TtlOut) = 0;

		// ������� ��� ������ ���������������� ���� ������
		virtual BOOL WINAPI ENABLE_FLASH_WRITE(BOOL EnableFlashWrite) = 0;
		virtual BOOL WINAPI READ_FLASH_WORD(WORD FlashAddress, SHORT * const FlashWord) = 0;
		virtual BOOL WINAPI WRITE_FLASH_WORD(WORD FlashAddress, SHORT FlashWord) = 0;

		// ������� ��� ������ �� ��������� ����������� �� ����
		virtual BOOL WINAPI GET_MODULE_DESCRIPTION(MODULE_DESCRIPTION_E440 * const ModuleDescription) = 0;
		virtual BOOL WINAPI SAVE_MODULE_DESCRIPTION(MODULE_DESCRIPTION_E440 * const ModuleDescription) = 0;

		// ������� ��� ������ � ������� DSP
		virtual BOOL WINAPI PUT_LBIOS_WORD(WORD Address, SHORT Data) = 0;
		virtual BOOL WINAPI GET_LBIOS_WORD(WORD Address, SHORT * const Data) = 0;
		virtual BOOL WINAPI PUT_DM_WORD(WORD Address, SHORT Data) = 0;
		virtual BOOL WINAPI GET_DM_WORD(WORD Address, SHORT * const Data) = 0;
		virtual BOOL WINAPI PUT_PM_WORD(WORD Address, long Data) = 0;
		virtual BOOL WINAPI GET_PM_WORD(WORD Address, long * const Data) = 0;
		virtual BOOL WINAPI PUT_DM_ARRAY(WORD BaseAddress, WORD NPoints, SHORT * const Data) = 0;
		virtual BOOL WINAPI GET_DM_ARRAY(WORD BaseAddress, WORD NPoints, SHORT * const Data) = 0;
		virtual BOOL WINAPI PUT_PM_ARRAY(WORD BaseAddress, WORD NPoints, long * const Data) = 0;
		virtual BOOL WINAPI GET_PM_ARRAY(WORD BaseAddress, WORD NPoints, long * const Data) = 0;

		// ������� ��� ������ � ����������� ���� ������
		virtual BOOL WINAPI ERASE_BOOT_FLASH(void) = 0;
		virtual BOOL WINAPI PUT_ARRAY_BOOT_FLASH(DWORD BaseAddress, DWORD NBytes, BYTE *Data) = 0;
		virtual BOOL WINAPI GET_ARRAY_BOOT_FLASH(DWORD BaseAddress, DWORD NBytes, BYTE *Data) = 0;
	};




	// ==========================================================================
	// *************************** ������ E20-10 ********************************
	// ==========================================================================
	// ��������� ������� ��������� ������� ������ ����� ������
	enum {
				INT_ADC_START_E2010, INT_ADC_START_WITH_TRANS_E2010,
				EXT_ADC_START_ON_RISING_EDGE_E2010, EXT_ADC_START_ON_FALLING_EDGE_E2010,
//				EXT_ADC_START_ON_HIGH_LEVEL_E2010, EXT_ADC_START_ON_LOW_LEVEL_E2010,		// ��� Rev.B � ���� (���� ���)
				INVALID_ADC_START_E2010
			};
	// ��������� ������� ��������� �������� ��������� ��� ������� ���
	enum {	INT_ADC_CLOCK_E2010, INT_ADC_CLOCK_WITH_TRANS_E2010, EXT_ADC_CLOCK_ON_RISING_EDGE_E2010, EXT_ADC_CLOCK_ON_FALLING_EDGE_E2010, INVALID_ADC_CLOCK_E2010 };
	// ��������� ���� ���������� ������������� ����� ������ (��� Rev.B � ����)
	enum {
				NO_ANALOG_SYNCHRO_E2010,			// ���������� ���������� �������������
				ANALOG_SYNCHRO_ON_RISING_CROSSING_E2010, ANALOG_SYNCHRO_ON_FALLING_CROSSING_E2010,	// ���������� ������������� �� ��������
				ANALOG_SYNCHRO_ON_HIGH_LEVEL_E2010, ANALOG_SYNCHRO_ON_LOW_LEVEL_E2010,		// ���������� ������������� �� ������
				INVALID_ANALOG_SYNCHRO_E2010
			};
	// ��������� ������� ���������� �������� ���������� ������ E20-10
	enum {	ADC_INPUT_RANGE_3000mV_E2010, ADC_INPUT_RANGE_1000mV_E2010, ADC_INPUT_RANGE_300mV_E2010, INVALID_ADC_INPUT_RANGE_E2010 };
	// ��������� ���� ����������� �������� ������ ������ E20-10
	enum {	ADC_INPUT_ZERO_E2010, ADC_INPUT_SIGNAL_E2010, INVALID_ADC_INPUT_E2010 };
	// ��������� ������� ��� ���������� ������� ����� �������� ������ E20-10 (��� Rev.B � ����)
	enum {	INPUT_CURRENT_OFF_E2010, INPUT_CURRENT_ON_E2010, INVALID_INPUT_CURRENT_E2010 };
	// ��������� ������ �������� ����� ���������� ������� ������� ��� ����� ������ (������ ��� Rev.A)
	enum {	CLIPPING_OVERLOAD_E2010, MARKER_OVERLOAD_E2010, INVALID_OVERLOAD_E2010 };
	// ��������� ������ ����� ������ ��� ���������� ����� ������ � ���
	enum {
				// ������� ���� BufferOverrun ��������� DATA_STATE_E2010
				BUFFER_OVERRUN_E2010 = 0x0,		// ������������ ����������� ������ ������
				// ������� ���� ChannelsOverFlow ��������� DATA_STATE_E2010 (��� Rev.B � ����)
				OVERFLOW_OF_CHANNEL_1_E2010 = 0x0, OVERFLOW_OF_CHANNEL_2_E2010,	// ���� ��������� ��������� ������������ ��������� ����� ���������������� ������
				OVERFLOW_OF_CHANNEL_3_E2010, OVERFLOW_OF_CHANNEL_4_E2010,			// �� ����� ���������� ������ ������� ����� ������ ReadData()
				OVERFLOW_E2010 = 0x7					// ��� ����������� �������� ����� ������������ ��������� ����� ������ �� �� ����� ����� ������ �� ������� START_ADC() �� STOP_ADC()
			};
	// ��������� ����� ������� ���������� ��� ��� ������ E20-10
	enum {	DAC_INACCESSIBLED_E2010, DAC_ACCESSIBLED_E2010, INVALID_DAC_OPTION_E2010 };
	// ��������� ������� ������� ������ E20-10
	enum {	REVISION_A_E2010, REVISION_B_E2010, INVALID_REVISION_E2010 };
	// ��������� ������� ����������� ������ E20-10
	enum {	BASE_MODIFICATION_E2010, 			// ������ ������� ������ 1.25 ���
				F5_MODIFICATION_E2010, 				// ������ ������� ������ 5.00 ���
				INVALID_MODIFICATION_E2010 };

	// ��������� ������� ��������� ��� ������� �������� ������� ������ ������ E20-10
	enum { NO_TEST_MODE_E2010, TEST_MODE_1_E2010 };

	// ��������� ��� ������ � �������
	enum 	{
				ADC_CHANNELS_QUANTITY_E2010 = 0x4, MAX_CONTROL_TABLE_LENGTH_E2010 = 256,
				ADC_INPUT_RANGES_QUANTITY_E2010 = INVALID_ADC_INPUT_RANGE_E2010,
				ADC_INPUT_TYPES_QUANTITY_E2010 = INVALID_ADC_INPUT_E2010,
				ADC_CALIBR_COEFS_QUANTITY_E2010 = ADC_CHANNELS_QUANTITY_E2010 * ADC_INPUT_RANGES_QUANTITY_E2010,
				DAC_CHANNELS_QUANTITY_E2010 = 0x2, DAC_CALIBR_COEFS_QUANTITY_E2010 = DAC_CHANNELS_QUANTITY_E2010,
				TTL_LINES_QUANTITY_E2010 = 0x10,		// ���-�� ������� � �������� �������� �����
				USER_FLASH_SIZE_E2010 = 0x200,  		// ������ ������� ����������������� ���� � ������
				REVISIONS_QUANTITY_E2010 = INVALID_REVISION_E2010,				// ���-�� ������� ������
				MODIFICATIONS_QUANTITY_E2010 = INVALID_MODIFICATION_E2010,	// ���-�� ��������� ���������� (�����������) ������
				ADC_PLUS_OVERLOAD_MARKER_E2010 = 0x5FFF,	// ������� '����' ���������� ������� � ��� (������ ��� Rev.A)
				ADC_MINUS_OVERLOAD_MARKER_E2010 = 0xA000	// ������� '�����' ���������� ������� � ��� (������ ��� Rev.A)
			};

	// ��������� �������� ���������� ��� � �
	const double ADC_INPUT_RANGES_E2010[ADC_INPUT_RANGES_QUANTITY_E2010] =
	{
		3.0, 1.0, 0.3
	};
	// �������� ��������� ���������� ��� � �
	const double DAC_OUTPUT_RANGE_E2010 = 5.0;
	// ��������� ������� ������
	const BYTE REVISIONS_E2010[REVISIONS_QUANTITY_E2010] = { 'A', 'B' };
	// ��������� ���������� ������
	const char * const MODIFICATIONS_E2010[MODIFICATIONS_QUANTITY_E2010] = { "BASE", "F5" };

	#pragma pack(1)
	// ��������� � ����� ����������� �� ������ E20-10
	struct MODULE_DESCRIPTION_E2010
	{
		MODULE_INFO_LUSBAPI     Module;		// ����� ���������� � ������
		INTERFACE_INFO_LUSBAPI  Interface;	// ���������� �� ����������
		MCU_INFO_LUSBAPI<MCU_VERSION_INFO_LUSBAPI>	Mcu;	// ���������� � ����������������
		PLD_INFO_LUSBAPI        Pld;			// ���������� � ����
		ADC_INFO_LUSBAPI        Adc;			// ���������� � ���
		DAC_INFO_LUSBAPI        Dac;			// ���������� � ���
		DIGITAL_IO_INFO_LUSBAPI DigitalIo;	// ���������� � �������� �����-������
	};
	// ��������� ����������������� ����
	struct USER_FLASH_E2010
	{
		BYTE Buffer[USER_FLASH_SIZE_E2010];
	};
	// ��������� � ����������� ������������� ����� ������ � ���
	struct SYNCHRO_PARS_E2010
	{
		WORD	StartSource;				  	// ��� � �������� ������� ������ ����� ������ � ��� (���������� ��� ������� � �.�.)
		DWORD StartDelay; 					// �������� ������ ����� ������ � ������ �������� c ��� (��� Rev.B � ����)
		WORD	SynhroSource;					// �������� �������� ��������� ������� ��� (���������� ��� ������� � �.�.)
		DWORD StopAfterNKadrs;				// ������� ����� ������ ����� ����������� ����� ���-�� ��������� ������ �������� ��� (��� Rev.B � ����)
		WORD	SynchroAdMode;   				// ����� ���������� ������������: ������� ��� ������� (��� Rev.B � ����)
		WORD	SynchroAdChannel;				// ���������� ����� ��� ��� ���������� ������������� (��� Rev.B � ����)
		SHORT SynchroAdPorog;  				// ����� ������������ ��� ���������� ������������� (��� Rev.B � ����)
		BYTE	IsBlockDataMarkerEnabled;	// ������������ ������ ����� ������ (������, ��������, ��� ���������� ������������� ����� �� ������) (��� Rev.B � ����)
	};
	// ��������� � ����������� ������ ���
	struct ADC_PARS_E2010
	{
		BOOL IsAdcCorrectionEnabled;		// ���������� ����������� �������������� �������������� ���������� ������ �� ������ ������ (��� Rev.B � ����)
		WORD OverloadMode;					// ����� �������� ����� ���������� ������� ������� ������ (������ ��� Rev.A)
		WORD InputCurrentControl;			// ���������� ������� ����� �������� (��� Rev.B � ����)
		SYNCHRO_PARS_E2010 SynchroPars;	// ��������� ������������� ����� ������ � ���
		WORD ChannelsQuantity;				// ���-�� �������� ������� (������ ����� ��������)
		WORD ControlTable[MAX_CONTROL_TABLE_LENGTH_E2010];	// ����������� ������� � ��������� ����������� ��������
		WORD InputRange[ADC_CHANNELS_QUANTITY_E2010]; 	// ������� ���������� �������� ���������� ���������� �������: 3.0�, 1.0� ��� 0.3�
		WORD InputSwitch[ADC_CHANNELS_QUANTITY_E2010];	// ������� ���� ����������� ���������� �������: ����� ��� ������
		double AdcRate;						// ������� ������ ��� � ���
		double InterKadrDelay;				// ����������� �������� � ��
		double KadrRate;						// ������� ����� � ���
		double AdcOffsetCoefs[ADC_INPUT_RANGES_QUANTITY_E2010][ADC_CHANNELS_QUANTITY_E2010];	// ������ ������������� ��� ������������� �������� �������� ���: (3 ���������)*(4 ������) (��� Rev.B � ����)
		double AdcScaleCoefs[ADC_INPUT_RANGES_QUANTITY_E2010][ADC_CHANNELS_QUANTITY_E2010];		// ������ ������������� ��� ������������� �������� �������� ���: (3 ���������)*(4 ������) (��� Rev.B � ����)
	};
	// ��������� � ����������� � ������� ��������� �������� ����� ������
	struct DATA_STATE_E2010
	{
		BYTE ChannelsOverFlow;			// ������� �������� ���������� ������� ���������� ������� (��� Rev.B � ����)
		BYTE BufferOverrun;				// ������� �������� ������������ ����������� ������ ������
		DWORD CurBufferFilling;			// ������������� ����������� ������ ������ Rev.B � ����, � ��������
		DWORD MaxOfBufferFilling;		// �� ����� ����� ������������ ������������� ����������� ������ ������ Rev.B � ����, � ��������
		DWORD BufferSize;					// ������ ����������� ������ ������ Rev.B � ����, � ��������
		double CurBufferFillingPercent;		// ������� ������� ���������� ����������� ������ ������ Rev.B � ����, � %
		double MaxOfBufferFillingPercent;	// �� ����� ����� ������������ ������� ���������� ����������� ������ ������ Rev.B � ����, � %
	};
	#pragma pack()

	//-----------------------------------------------------------------------------
	// ��������� ������ E20-10
	//-----------------------------------------------------------------------------
	struct ILE2010 : public ILUSBBASE
	{
		// �������� ���� ������
		virtual BOOL WINAPI LOAD_MODULE(PCHAR const FileName = NULL) = 0;
		virtual BOOL WINAPI TEST_MODULE(WORD TestModeMask = 0x0) = 0;

		// ������ � ���
		virtual BOOL WINAPI GET_ADC_PARS(ADC_PARS_E2010 * const AdcPars) = 0;
		virtual BOOL WINAPI SET_ADC_PARS(ADC_PARS_E2010 * const AdcPars) = 0;
		virtual BOOL WINAPI START_ADC(void) = 0;
		virtual BOOL WINAPI STOP_ADC(void) = 0;
		virtual BOOL WINAPI GET_DATA_STATE(DATA_STATE_E2010 * const DataState) = 0;
		virtual BOOL WINAPI ReadData(IO_REQUEST_LUSBAPI * const ReadRequest) = 0;

		// ����������� ���������� ������ � ���
		virtual BOOL WINAPI DAC_SAMPLE(SHORT * const DacData, WORD DacChannel) = 0;

		// ������ � ��������� �������
		virtual BOOL WINAPI ENABLE_TTL_OUT(BOOL EnableTtlOut) = 0;
		virtual BOOL WINAPI TTL_IN (WORD * const TtlIn) = 0;
		virtual BOOL WINAPI TTL_OUT(WORD TtlOut) = 0;

		// ������� ��� ������ � ���������������� ����������� ����
		virtual BOOL WINAPI ENABLE_FLASH_WRITE(BOOL IsUserFlashWriteEnabled) = 0;
		virtual BOOL WINAPI READ_FLASH_ARRAY(USER_FLASH_E2010 * const UserFlash) = 0;
		virtual BOOL WINAPI WRITE_FLASH_ARRAY(USER_FLASH_E2010 * const UserFlash) = 0;

		// ���������� � ������
		virtual BOOL WINAPI GET_MODULE_DESCRIPTION(MODULE_DESCRIPTION_E2010 * const ModuleDescription) = 0;
		virtual BOOL WINAPI SAVE_MODULE_DESCRIPTION(MODULE_DESCRIPTION_E2010 * const ModuleDescription) = 0;
	};





	// ==========================================================================
	// **************************** ������ E-310 ********************************
	// ==========================================================================

	// -============= ��������� ==============-
	// ���� ������������ ���������������� �� ������� ��� ����������
	enum CYCLIC_AUTO_SCAN_TYPES_E310
	{
		NO_CYCLIC_AUTOSCAN_E310,
		CYCLIC_PILA_AUTO_SCAN_E310, CYCLIC_TRIANGLE_AUTO_SCAN_E310,
		INVALID_CYCLIC_AUTOSCAN_TYPE_E310
	};
	// ���� ���������� ������� ����������
	enum INCREMENT_INTERVAL_TYPES_E310
	{
		WAVEFORM_CYCLE_INCREMENT_INTERVAL_E310,
		CLOCK_PERIOD_INCREMENT_INTERVAL_E310,
		INVALID_INCREMENT_INTERVAL_TYPE_E310
	};
	// ��������� ������� ���������� ���������� ������� ����������
	enum INCREMENT_INTERVAL_MULTIPLIERS_INDEXES_E310
	{
		INCREMENT_INTERVAL_MULTIPLIERS_001_E310,
		INCREMENT_INTERVAL_MULTIPLIERS_005_E310,
		INCREMENT_INTERVAL_MULTIPLIERS_100_E310,
		INCREMENT_INTERVAL_MULTIPLIERS_500_E310,
		INVALID_INCREMENT_INTERVAL_MULTIPLIER_E310
	};
	// ��������� ������� ��������� ����������� ��������� ��� ����������
	enum MASTER_CLOCK_SOURCES_E310
	{
		INTERNAL_MASTER_CLOCK_E310, EXTERNAL_MASTER_CLOCK_E310, INVALID_MASTER_CLOCK_SOURCE_E310
	};
	// ��������� ���� ������������� ������� ����������
	enum INCREMENT_TYPES_E310
	{
		AUTO_INCREMENT_E310, CTRL_LINE_INCREMENT_E310, INVALID_INCREMENT_TYPE_E310
	};
	// ��������� ���� ����� CTRL
	enum CTRL_LINE_TYPES_E310
	{
		INTERNAL_CTRL_LINE_E310, EXTERNAL_CTRL_LINE_E310, INVALID_CTRL_LINE_TYPE_E310
	};
	// ��������� ���� ����� INTERRUPT
	enum INTERRUPT_LINE_TYPES_E310
	{
		INTERNAL_INTERRUPT_LINE_E310, EXTERNAL_INTERRUPT_LINE_E310, INVALID_INTERRUPT_LINE_TYPE_E310
	};
	// ��������� ���� ������������ ��������� ������������� �� ����� "SYNCOUT"
	enum SYNCOUT_TYPES_E310
	{
		SYNCOUT_ON_EACH_INCREMENT_E310, SYNCOUT_AT_END_OF_SCAN_E310, INVALID_SYNCOUT_TYPES_E310
	};
	// ��������� ���� ���������� �������� ��������
	enum ANALOG_OUTPUT_TYPES_E310
	{
		TRIANGULAR_ANALOG_OUTPUT_E310, SINUSOIDAL_ANALOG_OUTPUT_E310, INVALID_ANALOG_OUTPUT_TYPE_E310
	};
	// ��������� ������� �������� ��������� ������ ����������
	enum ANALOG_OUTPUT_GAINS_INDEXES_E310
	{
		ANALOG_OUTPUT_GAIN_PLUS_10_DB_E310, ANALOG_OUTPUT_GAIN_PLUS_06_DB_E310,
		ANALOG_OUTPUT_GAIN_PLUS_04_DB_E310, ANALOG_OUTPUT_GAIN_PLUS_03_DB_E310,
		ANALOG_OUTPUT_GAIN_00_DB_E310,
		ANALOG_OUTPUT_GAIN_MINUS_02_DB_E310, ANALOG_OUTPUT_GAIN_MINUS_03_DB_E310,
		ANALOG_OUTPUT_GAIN_MINUS_06_DB_E310, ANALOG_OUTPUT_GAIN_MINUS_09_DB_E310,
		ANALOG_OUTPUT_GAIN_MINUS_12_DB_E310, ANALOG_OUTPUT_GAIN_MINUS_14_DB_E310,
		ANALOG_OUTPUT_GAIN_MINUS_18_DB_E310, ANALOG_OUTPUT_GAIN_MINUS_21_DB_E310,
		ANALOG_OUTPUT_GAIN_MINUS_24_DB_E310,
		INVALID_ANALOG_OUTPUT_GAINS_INDEX_E310,
		ANALOG_OUTPUT_GAINS_QUANTITY_E310 = INVALID_ANALOG_OUTPUT_GAINS_INDEX_E310
	};
	// ��������� ������� �������� �� ������ 10 ��
	enum OUTPUT_10_OHM_OFFSET_SOURCES_E310
	{
		INTERNAL_OUTPUT_10_OHM_OFFSET_E310,
		EXTERNAL_OUTPUT_10_OHM_OFFSET_E310,
		INVALID_OUTPUT_10_OHM_OFFSET_SOURCE_E310
	};
	// -======================================-

	// -============= ���������� FM ==============-
	// ��������� ������� �������� �������� ������� FM
	enum FM_MODES_E310
	{
		PERIOD_MODE_FM_E310, GATE_MODE_FM_E310, CAPTURE_MODE_FM_E310, INVALID_FM_MODE_E310
	};
	// ��������� ������� �������� �������� ������� ���������� ������� FM
	enum INPUT_DIVIDER_FM_E310
	{
		INPUT_DIVIDER_8_FM_E310, INPUT_DIVIDER_1_FM_E310, INVALID_INPUT_DIVIDER_FM_E310
	};
	// ��������� ������� �������� ������� ������� FM
	enum BASE_CLOCK_DIV_INDEXES_FM_E310
	{
		BASE_CLOCK_DIV_01_INDEX_FM_E310, BASE_CLOCK_DIV_02_INDEX_FM_E310,
		BASE_CLOCK_DIV_04_INDEX_FM_E310, BASE_CLOCK_DIV_08_INDEX_FM_E310,
		BASE_CLOCK_DIV_16_INDEX_FM_E310, BASE_CLOCK_DIV_32_INDEX_FM_E310,
		BASE_CLOCK_DIV_64_INDEX_FM_E310,
		INVALID_BASE_CLOCK_DIV_INDEX_FM_E310
	};
	// -==========================================-

	// -============= � � � ==============-
	// ��������� ��������� ������� ���
	enum ADC_START_SOURCES_E310
	{
		INTERNAL_ADC_START_E310, EXTERNAL_ADC_START_E310, INVALID_ADC_START_SOURCES_E310
	};
	// ��������� ������ ��� ��� ������� ����� ������� ���
	enum ADC_CHANNEL_BIT_NUMBERS_E310
	{
		ADC_CHANNEL_1_E310, ADC_CHANNEL_2_E310, ADC_CHANNEL_3_E310, ADC_CHANNEL_4_E310, 
		INVALID_ADC_CHANNEL_BIT_NUMBER_E310,
		ADC_CHANNEL_QUANTITY_E310 = INVALID_ADC_CHANNEL_BIT_NUMBER_E310
	};
	// -==================================-

	// ������ ������� ����������������� ���� � ������
	enum {	USER_FLASH_SIZE_E310 = 0x200 };
	// ��������� ������� ������� ������ E-310
	enum {	REVISION_A_E310, /*REVISION_B_E310,*/ INVALID_REVISION_E310, REVISIONS_QUANTITY_E310 = INVALID_REVISION_E310, };

	// ��������� ������� ������
	const BYTE REVISIONS_E310[REVISIONS_QUANTITY_E310] = { 'A'/*, 'B'*/ };

	#pragma pack(1)
	// ��������� � ����� ����������� �� ������ E-310
	struct MODULE_DESCRIPTION_E310
	{
		MODULE_INFO_LUSBAPI		Module;		// ����� ���������� � ������
		INTERFACE_INFO_LUSBAPI	Interface;	// ���������� �� ����������
		MCU_INFO_LUSBAPI<MCU_VERSION_INFO_LUSBAPI>	Mcu;	// ���������� � ����������������
		ADC_INFO_LUSBAPI			Adc;			// ���������� � ���
		DAC_INFO_LUSBAPI        Dac;			// ���������� � ���
		DIGITAL_IO_INFO_LUSBAPI DigitalIo;	// ���������� � �������� �����-������
	};

	// ��������� ����������������� ����
	struct USER_FLASH_E310
	{
		BYTE Buffer[USER_FLASH_SIZE_E310];
	};

	// ��������� � ����������� ���������� ����������
	struct INCREMENT_INTRERVAL_PARS_E310
	{
		BYTE	 BaseIntervalType;		// [in-out]	��� �������� ��������� ����������, ������� ����� ���� ������: ������� MCLK ��� ������� ��������� �������
		BYTE	 MultiplierIndex;			// [in-out]	������ ���������� ��� �������� ��������� ���������� (��� INCREMENT_INTERVAL_MULTIPLIERS_INDEXES_E310)
		double MultiplierValue;			// [out]		�������� ���������� ��� �������� ��������� ����������: 1, 5, 100 ��� 500
		WORD	 BaseIntervalsNumber;	// [in-out]	���-�� ������� ���������� � ��������� ����������
		double Duration; 					// [out] 	����� ������������ ���������� � �� (������ ��� ��������� ���������� �� MCLK, ����� 0
	};

	// ��������� � ����������� ���������� ������� ����������
	struct ANALOG_OUTPUTS_PARS_E310
	{
		BYTE	 SignalType;				// [in-out]	��� ����������� ������� �� ������� 10 � 50 ��: �������������� ��� �����������
		BYTE	 GainIndex;					// [in-out]	������ �������� ��������� ������ ���������� (��� ANALOG_OUTPUT_GAINS_INDEXES_E310)
		double GaindB;						// [out]		�������� ��������� ������ ���������� � ��
		double Output10OhmInV;			// [out]		��������� ������� �� ������ 10 �� � �
		double Output10OhmIndB;			// [out]		��������� ������� �� ������ 10 �� � ��
		double Output10OhmOffset;		// [in-out]	�������� ����������� �������� �� ������ 10 �� � �
		BYTE	 Output10OhmOffsetSource;//[in-out]	��� �������� �� ������ 10 ��: ���������� ��� �������
		double Output50OhmInV;			// [out]		��������� ������� �� ������ 50 �� � �
		double Output50OhmIndB;			// [out]		��������� ������� �� ������ 50 �� � ��
	};

	// ��������� � ����������� ������ ����������
	struct GENERATOR_PARS_E310
	{
		BOOL	 GeneratorEna;				// [in]		������� ��������� ������ ����������
		double StartFrequency;			// [in-out]	��������� ������� � ���
		double FinalFrequency;			// [out]		�������� ������� � ���
		double FrequencyIncrements;	// [in-out]	������� ���������� � ���
		WORD	 NumberOfIncrements;		// [in-out]	���-�� ���������� ������� ������������
		INCREMENT_INTRERVAL_PARS_E310 IncrementIntervalPars;	// [in-out] ��������� ���������� ����������
		double MasterClock;				// [in-out]	������� ������������ ������� ���������� � ���
		BYTE	 MasterClockSource;		// [in-out]	�������� ������������ ������� ����������: ���������� ��� �������
		BYTE	 CyclicAutoScanType;		// [in-out]	��� ������������ ���������������� ��������� �������: ��� ������������ ������������, '����' ��� '�����������'
		BYTE	 IncrementType;			// [in-out]	��� ������������� ������� ����������: ���������� (��������������) ��� � ������� ����������� ����� "CTRL"
		BYTE	 CtrlLineType;				// [in-out]	��� ����� "CTRL" ��� (���������� �������������� �������)/������ ����������: ���������� (�� MCU) ��� �������
		BYTE	 InterrupLineType;		// [in-out]	��� ����� "INTERRUPT" ��� �������� ������ ����������: ���������� (�� MCU) ��� �������
		BOOL	 SquareWaveOutputEna;	// [in-out]	���������� ������� ���������� �� �������� ������ "������"
		BOOL	 SynchroOutEna;			// [in-out]	���������� ������������� ���������� �� �������� ����� "SYNCOUT"
		BYTE	 SynchroOutType;			// [in-out]	��� ������������ ������������� ����������: ��� ������ ���������� ������� ��� ������ �� ��������� ������������
		ANALOG_OUTPUTS_PARS_E310 AnalogOutputsPars;	//	[in-out] ��������� ������ ���������� �������
	};

	// ��������� � ����������� ������ ���������� ������� (FM)
	struct FM_PARS_E310
	{
		BOOL	 FmEna;					   // [out]		������� ��������� ������ ���������� �������
		BYTE	 Mode;						// [in-out]	����� ������ ���������� �������
		BYTE	 InputDivider;				// [in-out]	���������� ������� ������� ��������� 1/8 (��� INPUT_DIVIDER_FM_E310)
		BYTE	 BaseClockRateDivIndex;	// [in-out]	������ �������� ������� �������� ������� (��� BASE_CLOCK_DIV_INDEXES_FM_E310)
		DWORD  ClockRate;					// [out]		������� �������� ������� �������� FM � ��
		DWORD  BaseClockRate;			// [const]	������� �������� ������� �������� FM 25 000 000 ��
		double Offset;						// [in-out]	�������� ������ ���������� ������� � �
	};

	// ��������� � ����������� � ������� ����������� �������
	struct FM_SAMPLE_E310
	{
		BOOL	 IsActual;					// [out]	������� ���������������� �����e���� ������
		double Frequency;					// [out]	������� ����������� ������� � ���
		double Period;						// [out]	������ ����������� ������� � ��
		double DutyCycle;					// [out]	���������� ����������� ������� � ��
	};

	// ��������� ��� ������ � ���
	struct ADC_PARS_E310
	{
		BYTE	 AdcStartSource;	  		// [in-out]	�������� ������� ������� ���: ���������� ��� �������
		BYTE	 ChannelsMask;				// [in-out]	������� ����� �������� ������� (������� 4 ����)
		double InputRange;				// [out]		������� �������� ��� � �
	};

	// ��������� � ��������� ���
	struct ADC_DATA_E310
	{
		SHORT 	DataInCode[ADC_CHANNEL_QUANTITY_E310];		// [out] ������ ������ � ��� � �����
		double	DataInV[ADC_CHANNEL_QUANTITY_E310];			// [out] ������ ������ � ��� � �
	};
	#pragma pack()

	//-----------------------------------------------------------------------------
	// ��������� ������ E-310
	//-----------------------------------------------------------------------------
	struct ILE310 : public ILUSBBASE
	{
		// ---------------- ������� ��� ������ � ����������� ----------------------------
		// ������� ������ ���������� ������ ����������
		virtual BOOL WINAPI GET_GENERATOR_PARS(GENERATOR_PARS_E310 * const GenPars) = 0;
		// ������� ��������� g��������� ������ ����������
		virtual BOOL WINAPI SET_GENERATOR_PARS(GENERATOR_PARS_E310 * const GenPars) = 0;
		// ����� ������ ����������
		virtual BOOL WINAPI START_GENERATOR(void) = 0;
		// ������� ������ ����������
		virtual BOOL WINAPI STOP_GENERATOR(void) = 0;

		// ---------- ������� ��� ������ � ������������� (FM) -------------------
		// ��������� ������� ���������� ������ ������������ (FM)
		virtual BOOL WINAPI GET_FM_PARS(FM_PARS_E310 * const FmPars) = 0;
		// ��������� ��������� ���������� ������ ������������ (FM)
		virtual BOOL WINAPI SET_FM_PARS(FM_PARS_E310 * const FmPars) = 0;
		// ����� ������ ������������ (FM)
		virtual BOOL WINAPI START_FM(void) = 0;
		// ������� ������ ������������ (FM)
		virtual BOOL WINAPI STOP_FM(void) = 0;
		// ���������� ������� ��������� �������
		virtual BOOL WINAPI FM_SAMPLE(FM_SAMPLE_E310 * const FmSample) = 0;

		// ------------------ ������� ��� ������ ��� ---------------------------
		// ��������� ������� ���������� ������ ���
		virtual BOOL WINAPI GET_ADC_PARS(ADC_PARS_E310 * const AdcPars) = 0;
		// ��������� ��������� ���������� ������ ���
		virtual BOOL WINAPI SET_ADC_PARS(ADC_PARS_E310 * const AdcPars) = 0;
		// ���������� ������� �������� � ���
		virtual BOOL WINAPI GET_ADC_DATA(ADC_DATA_E310 * const AdcData) = 0;

		// ---------- ������� ��� ������ � ��������� ������� -------------------
		// ���������������� �������� �����: ���� ��� �����
		virtual BOOL WINAPI CONFIG_TTL_LINES(WORD Pattern, BOOL AddTtlLinesEna = FALSE) = 0;
		// ������ ��������� �������� ������� �����
		virtual BOOL WINAPI TTL_IN (WORD * const TtlIn) = 0;
		// ��������� ��������� �������� �������� �����
		virtual BOOL WINAPI TTL_OUT(WORD * const TtlOut) = 0;

		// ------- ������� ��� ������ � ���������������� ����������� ����  -------
		// ����������/���������� ������ ������ � ���������������� ������� ����
		virtual BOOL WINAPI ENABLE_FLASH_WRITE(BOOL IsUserFlashWriteEnabled) = 0;
		// ������� ���������������� ������� ����
		virtual BOOL WINAPI READ_FLASH_ARRAY(USER_FLASH_E310 * const UserFlash) = 0;
		// ������ ���������������� ������� ����
		virtual BOOL WINAPI WRITE_FLASH_ARRAY(USER_FLASH_E310 * const UserFlash) = 0;

		// ------- ������� ��� ������ �� ��������� ����������� �� ���� -----------
		// ������� ��������� ���������� � ������ �� ����
		virtual BOOL WINAPI GET_MODULE_DESCRIPTION(MODULE_DESCRIPTION_E310 * const md) = 0;
		// ������� ��������� ���������� � ������ � ����
		virtual BOOL WINAPI SAVE_MODULE_DESCRIPTION(MODULE_DESCRIPTION_E310 * const md) = 0;
	};

#endif
