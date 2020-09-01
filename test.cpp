#include "stdafx.h"
#include "math.h"
#define SITENUM   4


CBIT128 cbit;

FPVI10 fpvi0_VCC(0);
FPVI10 fpvi1_VOUT(1);
FOVI fovi2(2);
FOVI FOVI8(8);
FOVI FOVI9(9);
FOVI FOVI10(10);
FOVI FOVI12(12);
FOVI FOVI13(13);
QVM qvm0(0);
QVM qvm1(1);
QTMU_PLUS qtmu0(0);
QTMU_PLUS qtmu1(1);
HVI1K hvi1k0(0);	

DIO dio(0);
DWORD pattern=0;

double adresult[4] = { 0 };
int i = 0;
int BitsperPin;
int FailLines;
int dout=0;

#define K1 1,4
#define K2 2,5
#define K3 3,6

//multisite settings should be included here
DUT_API void HardWareCfg()
{
	StsSetModuleToSite(MD_FPVI10, SITE_1, 0, 1, -1);//set channels 0-1 to SITE1
	StsSetModuleToSite(MD_FPVI10, SITE_2, 2, 3, -1);//set channels 2-3 to SITE2

	StsSetModuleToSite(MD_FOVI, SITE_1, 0, 1, 2, 3, 4, 5, 6, 7, -1);
	StsSetModuleToSite(MD_FOVI, SITE_2, 8, 9, 10, 11, 12, 13, 14, 15, -1);

	StsSetModuleToSite(MD_QVM, SITE_1, 0, 1, 2, 3, -1);

	StsSetModuleToSite(MD_QTMUPLUS, SITE_1, 0, 1, 2, 3, -1);

	StsSetModuleToSite(MD_HVI1K, SITE_1, 0, -1);//set channel 0 to SITE1


}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//initialize function will be called before all the test functions.
DUT_API void InitBeforeTestFlow()
{
	fpvi0_VCC.Set(FV,0,FPVI10_5V,FPVI10_100MA,RELAY_ON);
	fpvi1_VOUT.Set(FV,0,FPVI10_5V,FPVI10_100MA,RELAY_ON);
	fovi2.Set(FV,0,FOVI_5V,FOVI_100MA,RELAY_ON);
	delay_ms(1);

	qvm0.Init();

	qtmu0.Init();
	dio.Init();

    dio.SetClockFreq(500e+3);//500Khz rate

    dio.SetDelay(0, 75e-9, 375e-9, 250e-9);//set channel 0 delay
	dio.SetDelay(1, 10e-9, 375e-9, 250-9);//set channel 1 delay
	dio.SetDelay(2, 10e-9, 375e-9, 250e-9);//set channel 2 delay
	dio.SetDelay(3, 10e-9, 375e-9, 250e-9);//set channel 3 delay
	dio.SetDelay(4, 125e-9, 375e-9, 250e-9);//set channel 4 delay
	dio.SetDelay(5, 125e-9, 375e-9, 250e-9);//set channel 5 delay
	dio.SetDelay(6, 125e-9, 375e-9, 250e-9);//set channel 6 delay
	dio.SetDelay(7, 125e-9, 375e-9, 250e-9);//set channel 7 delay

	dio.SetDelayWithLabel(DIO::OnTheFly1, 0, 10e-9f, 0.9e-3f, 0.5e-3f);
    dio.SetDelayWithLabel(DIO::OnTheFly1, 1, 10e-9f, 0.9e-3f, 0.5e-3f);
	
	dio.SetWaveFormat(0, "NRZ");//set channel 0 format
	dio.SetWaveFormat(1, "NRZ");//set channel 1 format
	dio.SetWaveFormat(2, "NRZ");//set channel 2 format
	dio.SetWaveFormat(3, "NRZ");//set channel 3 format
	dio.SetWaveFormat(4, "NRZ");//set channel 4 format
	dio.SetWaveFormat(5, "NRZ");//set channel 5 format
	dio.SetWaveFormat(6, "NRZ");//set channel 6 format
	dio.SetWaveFormat(7, "NRZ");//set channel 7 format
    
    dio.SetVIH(5.0); //set driver high voltage
    dio.SetVIL(0.0);//set driver low voltage
    dio.SetVOH(2.4); //set compare high voltage
    dio.SetVOL(0.4);//set compare low voltage
	
	
	//  LAB_O ENB_O CLK_O D_O LAB_I ENB_I CLK_I D_I
	//    7     6     5    4    3     2     1    0
    
    dio.LoadPattern(0,"XXXXXXX0");
	dio.LoadPattern(1,"XXXXXXX1");
	dio.LoadPattern(2,"XXXXXXX0");
	dio.LoadPattern(3,"XXXXXXX1");

	dio.LoadPattern(4,"XXXXXXX1");
	dio.LoadPattern(5,"XXXXXXX0");
	dio.LoadPattern(6,"XXXXXXX0");
	dio.LoadPattern(7,"XXXXXXX0");

	dio.LoadPatternWithLabel("XXXXL010", "lable_1");
    dio.LoadPatternWithLabel("XXXXL001");
    dio.LoadPatternWithLabel("XXXXH100");
    dio.LoadPatternWithLabel("XXXXL001");
    dio.LoadPatternWithLabel("XXXXL000");
    dio.LoadPatternWithLabel("XXXXH101");
    dio.LoadPatternWithLabel("XXXXH100");
    dio.LoadPatternWithLabel("XXXXH101");
    dio.LoadPatternWithLabel("XXXXL000");
    dio.LoadPatternWithLabel("XXXXL001");
    dio.LoadPatternWithLabel("XXXXH100");
    dio.LoadPatternWithLabel("XXXXL001");
    dio.LoadPatternWithLabel("XXXXH110");
    dio.LoadPatternWithLabel("XXXXL011");
    dio.LoadPatternWithLabel("XXXXH110");
    dio.LoadPatternWithLabel("XXXXL011");
    dio.LoadPatternWithLabel("XXXXL000");
    dio.LoadPatternWithLabel("XXXXH101");
    dio.LoadPatternWithLabel("XXXXL000");
    dio.LoadPatternWithLabel("XXXXL001");
    dio.LoadPatternWithLabel("XXXXL000");
    dio.LoadPatternWithLabel("XXXXH101");
    dio.LoadPatternWithLabel("XXXXH100");
    dio.LoadPatternWithLabel("XXXXL001");
    dio.LoadPatternWithLabel("XXXXH100");
    dio.LoadPatternWithLabel("XXXXL011");
    dio.LoadPatternWithLabel("XXXXH110");
    dio.LoadPatternWithLabel("XXXXL011");
    dio.LoadPatternWithLabel("XXXXL010", "lable_2");

	dio.LoadPatternWithLabel("XXXXXXX0", "a1");
    dio.LoadPatternWithLabel("XXXXXXX1");
	dio.LoadPatternWithLabel("XXXXXXX0", "a2");
  
    
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//initializefunction will be called after all the test functions.
DUT_API void InitAfterTestFlow()
{		
	fpvi0_VCC.Set(FV,0,FPVI10_5V,FPVI10_100MA,RELAY_ON);
	fpvi1_VOUT.Set(FV,0,FPVI10_5V,FPVI10_100MA,RELAY_ON);
	fovi2.Set(FV,0,FOVI_5V,FOVI_100MA,RELAY_ON);
	delay_ms(1);

	fpvi0_VCC.Set(FV,0,FPVI10_5V,FPVI10_100MA,RELAY_OFF);
	fpvi1_VOUT.Set(FV,0,FPVI10_5V,FPVI10_100MA,RELAY_OFF);
	fovi2.Set(FV,0,FOVI_5V,FOVI_100MA,RELAY_OFF);
	cbit.SetOn(-1);
	delay_ms(1);

	FOVI8.Set(FV, 0, FOVI_20V, FOVI_1A, RELAY_ON);
	FOVI9.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_ms(2);
	FOVI8.Set(FV, 0, FOVI_20V, FOVI_1A, RELAY_OFF);
	FOVI9.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_OFF);
	delay_ms(2);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//Fail site hardware set function will be called after failed params, it can be called for serveral times. 
DUT_API void SetupFailSite(const unsigned char*byFailSite)
{			
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

DUT_API int test_Example(short funcindex, LPCTSTR funclabel)
{
    //{{AFX_STS_PARAM_PROTOTYPES
    CParam *Vin_GND = StsGetParam(funcindex,"Vin_GND");
    CParam *Vout_GND = StsGetParam(funcindex,"Vout_GND");
    //}}AFX_STS_PARAM_PROTOTYPES

	double adresult[4]={0};
	int i=0;
	
	fpvi0_VCC.Set(FI, -100e-6, FPVI10_5V, FPVI10_1MA, RELAY_ON);
	delay_ms(1);
	fpvi0_VCC.MeasureVI(20, 20);

	for(i=0; i<SITENUM; i++)
	{
		Vin_GND->SetTestResult(i, 0, fpvi0_VCC.GetMeasResult(i, MVRET));
		
	}
	
	fpvi0_VCC.Set(FV, 0, FPVI10_5V, FPVI10_1MA, RELAY_ON);
	delay_ms(1);

	fpvi1_VOUT.Set(FI, -1e-3, FPVI10_5V, FPVI10_10MA, RELAY_ON);
	delay_ms(1);
	fpvi1_VOUT.MeasureVI(20, 20);
	for(i=0; i<SITENUM; i++)
	{
		Vout_GND->SetTestResult(i, 0, fpvi1_VOUT.GetMeasResult(i, MVRET));
		
	}
	
	fpvi1_VOUT.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
	delay_ms(1);
	
    // TODO: Add your function code here
    return 0;
}





DUT_API int VOUT(short funcindex, LPCTSTR funclabel)
{
    //{{AFX_STS_PARAM_PROTOTYPES
    CParam *Vout1 = StsGetParam(funcindex,"Vout1");
    CParam *Vout2 = StsGetParam(funcindex,"Vout2");
    CParam *Vout3 = StsGetParam(funcindex,"Vout3");
    //}}AFX_STS_PARAM_PROTOTYPES

	double adresult[4]={0};
	int i=0;

	cbit.SetOn(K1,-1);
	delay_ms(3);
//Vout2
	fpvi0_VCC.Set(FV, 8, FPVI10_10V, FPVI10_1A, RELAY_ON);
	delay_ms(2);
	fpvi1_VOUT.Set(FI, -10e-3, FPVI10_5V, FPVI10_1A, RELAY_ON);
	delay_ms(2);
	fpvi1_VOUT.MeasureVI(20, 20);
	for(i=0; i<SITENUM; i++)
	{
		adresult[i]=fpvi1_VOUT.GetMeasResult(i, MVRET);
		Vout2->SetTestResult(i, 0, adresult[i]);
		
	}

//Vout1
	fpvi1_VOUT.Set(FI, -0.8, FPVI10_5V, FPVI10_1A, RELAY_ON);
	delay_ms(2);
	fpvi1_VOUT.MeasureVI(20, 20);
	for(i=0; i<SITENUM; i++)
	{
		adresult[i]=fpvi1_VOUT.GetMeasResult(i, MVRET);
		Vout1->SetTestResult(i, 0, adresult[i]);
		
	}

//Vout3
	fpvi0_VCC.Set(FV, 6, FPVI10_10V, FPVI10_1A, RELAY_ON);
	delay_ms(2);
	fpvi1_VOUT.MeasureVI(20, 20);
	for(i=0; i<SITENUM; i++)
	{
		adresult[i]=fpvi1_VOUT.GetMeasResult(i, MVRET);
		Vout3->SetTestResult(i, 0, adresult[i]);
		
	}

	fpvi1_VOUT.Set(FI, -0, FPVI10_5V, FPVI10_1A, RELAY_ON);
	delay_ms(2);

    fpvi0_VCC.Set(FV, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);
	delay_ms(2);

	fpvi1_VOUT.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
	delay_ms(2);

	cbit.SetOn(-1);
	delay_ms(3);

	
    // TODO: Add your function code here
    return 0;
}



DUT_API int IQ(short funcindex, LPCTSTR funclabel)
{
    //{{AFX_STS_PARAM_PROTOTYPES
    CParam *Iq = StsGetParam(funcindex,"Iq");
    //}}AFX_STS_PARAM_PROTOTYPES

	cbit.SetOn(K1, -1);
	delay_ms(3);

	
	fpvi0_VCC.Set(FV, 8, FPVI10_10V, FPVI10_10MA, RELAY_ON);
	delay_ms(1);
	fpvi1_VOUT.Set(FI,0,FPVI10_5V,FPVI10_1MA,RELAY_ON);
	delay_ms(1);
	fpvi0_VCC.MeasureVI(100,20);

	for(i=0; i<SITENUM; i++)
	{
		adresult[i]=fpvi0_VCC.GetMeasResult(i, MIRET);
		Iq->SetTestResult(i, 0, adresult[i]*1000);
		
	}
	
	fpvi0_VCC.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_ON);
	delay_ms(1);
	fpvi1_VOUT.Set(FV,0,FPVI10_5V,FPVI10_1MA, RELAY_ON);
	delay_ms(1);
	cbit.SetOn(-1);
	delay_ms(3);
	
    // TODO: Add your function code here
    return 0;
}


DUT_API int Iadj(short funcindex, LPCTSTR funclabel)
{
    //{{AFX_STS_PARAM_PROTOTYPES
    CParam *Iadj = StsGetParam(funcindex,"Iadj");
    //}}AFX_STS_PARAM_PROTOTYPES

	double adresult[4]={0};
	int i=0;
	
	fpvi0_VCC.Set(FV, 8, FPVI10_10V, FPVI10_100MA, RELAY_ON);
	delay_ms(1);
	fpvi1_VOUT.Set(FI,-10e-3,FPVI10_5V,FPVI10_10MA,RELAY_ON);
	delay_ms(1);
	fpvi0_VCC.MeasureVI(200, 10);

	for(i=0; i<SITENUM; i++)
	{
		adresult[i]=fpvi0_VCC.GetMeasResult(i, MIRET);
		Iadj->SetTestResult(i, 0, adresult[i]);
		
	}
	
	fpvi0_VCC.Set(FV, 0, FPVI10_10V, FPVI10_1A, RELAY_OFF);
	delay_ms(1);
	fpvi1_VOUT.Set(FV,0,FPVI10_5V,FPVI10_1MA,RELAY_OFF);
	delay_ms(1);
	delay_ms(3);
	
    // TODO: Add your function code here
    return 0;
}



DUT_API int Vdrop(short funcindex, LPCTSTR funclabel)
{
    //{{AFX_STS_PARAM_PROTOTYPES
    CParam *Vin = StsGetParam(funcindex,"Vin");
    CParam *Vout = StsGetParam(funcindex,"Vout");
    CParam *Vdrop = StsGetParam(funcindex,"Vdrop");
    //}}AFX_STS_PARAM_PROTOTYPES

	double adresult1[4]={0};
	double adresult2[4]={0};
	int i=0;

	double Trig = 3.234;
	double Trig_Point[4]={0};
	double awg_pattern[1000]={0.0};
	int sam = 1000;//5V->4V step =0.0001V sam = stepNum
	int interval = 100;//每步时间（us）



	cbit.SetOn(K1,-1);
	delay_ms(3);
	//fpvi1_VOUT.Set(FI,-10e-3,FPVI10_5V,FPVI10_10MA,RELAY_ON);
	fpvi1_VOUT.Set(FI,0,FPVI10_5V,FPVI10_10MA,RELAY_ON);
	delay_ms(1);
	fpvi0_VCC.Set(FV, 5, FPVI10_10V, FPVI10_10MA, RELAY_ON);
	delay_ms(1);

	STSAWGCreateRampData(&awg_pattern[0],sam,1,5,4);
	//设置一个斜波数据组首地址从0开始，数据长度sam，周期1，起始值5V，结束值4V。
	fpvi0_VCC.AwgLoader("VCC_Awg",FV,FPVI10_5V,FPVI10_10MA,awg_pattern,sam);
    fpvi0_VCC.Set(FV, 5, FPVI10_5V, FPVI10_10MA, RELAY_ON);
	fpvi0_VCC.AwgSelect("VCC_Awg",0,sam-1,sam-1,interval);
	fpvi1_VOUT.SetMeasVTrig(Trig,TRIG_FALLING);

	fpvi0_VCC.MeasureVI(sam,interval,MEAS_AWG);
	fpvi1_VOUT.MeasureVI(sam,interval,MEAS_AWG);
	STSEnableAWG(&fpvi0_VCC); // fovi0 使能同步 AWG
    STSEnableMeas(&fpvi0_VCC, &fpvi1_VOUT); // fovi0 和 fovi1 使能同步测量
    STSAWGRun();//AWG 同步启动


	for(i=0; i<SITENUM; i++)
	{
		Trig_Point[i]=fpvi1_VOUT.GetMeasResult(i, MVRET,TRIG_RESULT);
		adresult1[i]=fpvi0_VCC.GetMeasResult(i, MVRET);
		adresult2[i]=fpvi1_VOUT.GetMeasResult(i, MVRET);
		Vin->SetTestResult(i, 0, adresult1[i]);
		Vout->SetTestResult(i, 0, adresult2[i]);
		Vdrop->SetTestResult(i, 0, adresult1[i]-adresult2[i]);
		
	}
	
	fpvi0_VCC.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_ON);
	delay_ms(1);
	fpvi1_VOUT.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
	delay_ms(1);

	fpvi0_VCC.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_OFF);
	fpvi1_VOUT.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_OFF);

	cbit.SetOn(-1);
	delay_ms(3);
	
    // TODO: Add your function code here
    return 0;
}



DUT_API int Rdson(short funcindex, LPCTSTR funclabel)
{
    //{{AFX_STS_PARAM_PROTOTYPES
    CParam *Rdson = StsGetParam(funcindex,"Rdson");
    //}}AFX_STS_PARAM_PROTOTYPES

    // TODO: Add your function code here

	double avg_result[100] = {0.0};


	FOVI8.Set(FV, 0, FOVI_20V, FOVI_1A, RELAY_ON);
	FOVI9.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	
	FOVI8.Set(FV, 10, FOVI_20V, FOVI_1A, RELAY_ON);
	delay_ms(1);
	FOVI9.Set(FI, -100e-3, FOVI_20V, FOVI_1A, RELAY_ON);
	delay_ms(1);
	FOVI8.MeasureVI(10, 10);
	for(i=0; i<SITENUM; i++)
	{
		adresult[i] = FOVI8.GetMeasResult(i, MIRET);
	//	Iin->SetTestResult(i, 0,adresult[i]);
	}

 	qvm0.Connect();
 	delay_ms(2);

	qvm0.MeasureLADC(200,5,QVM_LADC_5V,QVM_LADC_40KHz,MEAS_NORMAL);//sample is 200;interval time is 5us 
	for(i=0; i<SITENUM; i++)
	{
		avg_result[i] = qvm0.GetMeasResult(i, AVERAGE_RESULT);
		//Vin->SetTestResult(i, 0,avg_result[i]);
        Rdson->SetTestResult(i, 0,(avg_result[i]/adresult[i])*1e3);
	}


	FOVI9.Set(FI, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	FOVI8.Set(FV, 0, FOVI_20V, FOVI_1A, RELAY_ON);
	FOVI9.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	qvm0.Disconnect();
	delay_ms(1);
	FOVI8.Set(FV, 0, FOVI_20V, FOVI_1A, RELAY_OFF);
	FOVI9.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_OFF);

    return 0;
}


DUT_API int test_THD(short funcindex, LPCTSTR funclabel)
{
    //{{AFX_STS_PARAM_PROTOTYPES
    CParam *THD = StsGetParam(funcindex,"THD");
    //}}AFX_STS_PARAM_PROTOTYPES

    // TODO: Add your function code here

	int sam = 100; //awgSize
	int interval = 10; //awgInterval，unit=us
	double awg_pattern[1000]={0.0};
	double THD_result[SITENUM] = {0.0};
	double data_result[4096]={0.0};

	STSAWGCreateSineData(&awg_pattern[0],sam,1,4,2,0);
	FOVI10.AwgLoader("Sin_Awg",FV,FOVI_5V,FOVI_100MA,awg_pattern,sam);
    FOVI10.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);
	FOVI10.AwgRun("Sin_Awg", 0, (sam-1), 0, interval,AWG_LOOP);
	delay_ms(2);

	qvm1.Init();
	qvm1.Connect();
	delay_ms(2);
	qvm1.MeasureLADC(4096,5,QVM_LADC_5V,QVM_LADC_40KHz,MEAS_NORMAL);
    
	for(i=0; i<SITENUM; i++)
    {
		qvm0.BlockRead(i, 0, 4096, data_result, SAMPLE_DATA);
		//直接获取数据，数据存在数组data_result中
	}

	FILE *fp;
    fp=fopen("acout_4096.csv","wb");
    for(int j=0;j<4096;j++)
    fprintf(fp,"%3.6f\n", data_result[j]);
    fclose(fp);
	
	qvm1.StartFFT(DIRECT_FFT);
	for(i=0; i<SITENUM; i++)
	{
		THD_result[i] = qvm1.GetFFTResult(i,THD_RESULT,TOTAL_HARM,20);
		THD->SetTestResult(i, 0, THD_result[i]);//dB
	}

	FOVI10.AwgStop();
	FOVI10.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_OFF);

    return 0;
}


DUT_API int FOSE(short funcindex, LPCTSTR funclabel)
{
    //{{AFX_STS_PARAM_PROTOTYPES
    CParam *fose = StsGetParam(funcindex,"fose");
    CParam *Duty = StsGetParam(funcindex,"Duty");
    CParam *Tr = StsGetParam(funcindex,"Tr");
    CParam *TPLH = StsGetParam(funcindex,"TPLH");
    CParam *Freq_Squ = StsGetParam(funcindex,"Freq_Squ");
    CParam *Tevent0 = StsGetParam(funcindex,"Tevent0");
    CParam *Tevent1 = StsGetParam(funcindex,"Tevent1");
    CParam *Tevent2 = StsGetParam(funcindex,"Tevent2");
    //}}AFX_STS_PARAM_PROTOTYPES

    // TODO: Add your function code here

	//------------ fose -------------

	cbit.SetOn(31,63,-1);
	delay_ms(3);
	double val[SITENUM] = {0.0};

	dio.Connect();
	delay_ms(3);
	dio.LoopSet(4,7,-1);//4-7，无限循环
	dio.RunPattern(4,7);
	delay_ms(1);
	qtmu0.Init();
	qtmu0.SetStartInput(QTMU_PLUS_IMPEDANCE_1M,QTMU_PLUS_VRNG_5V,QTMU_PLUS_FILTER_PASS);
	qtmu0.SetStartTrigger(2, QTMU_PLUS_POS_SLOPE);//trigger=2V, Rising edge
	qtmu0.SetInSource(QTMU_PLUS_SINGLE_SOURCE); //SINGLE_SOURCE
	qtmu0.Connect(); 
	delay_ms(1);
	qtmu0.MeasFreq(QTMU_PLUS_COARSE,QTMU_PLUS_TRNG_US,10,10); //cycle number=10，timeout=10ms
	for(i=0; i<SITENUM; i++ )
	{
		val[i] = qtmu0.GetMeasureResult(i);
		fose->SetTestResult(i, 0, val[i]);
	}

	dio.StopPattern();
	dio.RunPattern(4,5);
	delay_ms(1);


	//------------ duty -------------

	dio.LoopSet(4,7,-1);//4-7，无限循环
	dio.RunPattern(4,7);
	
	qtmu0.SetStartInput(QTMU_PLUS_IMPEDANCE_1M,QTMU_PLUS_VRNG_5V,QTMU_PLUS_FILTER_PASS);
	qtmu0.SetStartTrigger(2, QTMU_PLUS_POS_SLOPE);
	qtmu0.SetInSource(QTMU_PLUS_SINGLE_SOURCE); //SINGLE_SOURCE
	qtmu0.Connect();
	delay_ms(1);
	qtmu0.MeasDC(2, QTMU_PLUS_HIGH_DUTY,10);//trigger=2V, timeout=10ms, read Dutycycle
	for(i=0; i<SITENUM; i++ )
	{
		val[i] = qtmu0.GetMeasureResult(i);
		Duty->SetTestResult(i, 0, val[i]);
	}
	dio.StopPattern();
	dio.RunPattern(4,5);
	delay_ms(1);
	qtmu0.Disconnect(); 
	dio.Disconnect();
	delay_ms(1); 
	

	//------------ tr -------------
    
	cbit.SetOn(63,-1);
    delay_ms(3);
	FOVI12.Set(FV,0,FOVI_10V,FOVI_10MA,RELAY_ON);
	delay_ms(1);
	qtmu1.SetStartInput(QTMU_PLUS_IMPEDANCE_1M,QTMU_PLUS_VRNG_25V,QTMU_PLUS_FILTER_PASS);
	qtmu1.SetStopInput(QTMU_PLUS_IMPEDANCE_1M,QTMU_PLUS_VRNG_25V,QTMU_PLUS_FILTER_PASS);
	qtmu1.SetStartTrigger(0.5,QTMU_PLUS_POS_SLOPE);//trigger=2.1V, Rising edge
	qtmu1.SetStopTrigger(4.5,QTMU_PLUS_POS_SLOPE);//trigger=13.3V, Rising edge
	qtmu1.SetInSource(QTMU_PLUS_SINGLE_SOURCE);//SINGLE_SOURCE
	qtmu1.Connect(); 
	delay_ms(1);
	qtmu1.SetSinglePulseMeas(QTMU_PLUS_COARSE,QTMU_PLUS_TIME_US,0);
	qtmu1.SetTimeOut(10);//timeout=10ms

	//set the trigger signal here
    FOVI12.Set(FV,5,FOVI_10V,FOVI_10MA,RELAY_ON,0.5);
	delay_ms(1);

	
	qtmu1.SinglePlsMeas(0); 
	for(i=0; i<SITENUM; i++ )
	{
		val[i] = qtmu0.GetMeasureResult(i);
		Tr->SetTestResult(i, 0, val[i]);
	}

    qtmu1.Disconnect(); 
    delay_ms(1);
	FOVI12.Set(FV,0,FOVI_10V,FOVI_10MA,RELAY_ON);
	delay_ms(1);
	FOVI12.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);



	//------------ TPHL -------------

	FOVI12.Set(FV,0,FOVI_10V,FOVI_10MA,RELAY_ON);
	FOVI13.Set(FV,0,FOVI_10V,FOVI_10MA,RELAY_ON);
	delay_ms(1);
	qtmu1.Init();
	qtmu1.SetStartInput(QTMU_PLUS_IMPEDANCE_1M,QTMU_PLUS_VRNG_25V,QTMU_PLUS_FILTER_PASS);
    qtmu1.SetStopInput(QTMU_PLUS_IMPEDANCE_1M,QTMU_PLUS_VRNG_25V,QTMU_PLUS_FILTER_PASS);
    qtmu1.SetStartTrigger(2.5,QTMU_PLUS_NEG_SLOPE);//trigger=2.5V, falling edge
    qtmu1.SetStopTrigger(7.7,QTMU_PLUS_POS_SLOPE);//trigger=7.7V, rising edge
    qtmu1.SetInSource(QTMU_PLUS_DUAL_SOURCE);
    qtmu1.Connect();
    delay_ms(1);
    qtmu1.SetSinglePulseMeas(QTMU_PLUS_COARSE,QTMU_PLUS_TIME_US,0);
    qtmu1.SetTimeOut(10); //timeout=10ms

    //set the trigger signal here
	FOVI12.Set(FV,5,FOVI_10V,FOVI_10MA,RELAY_ON);
	delay_ms(1);
	FOVI13.Set(FV,5,FOVI_10V,FOVI_10MA,RELAY_ON);
	delay_ms(1);

    qtmu1.SinglePlsMeas(0);
    for(i=0; i<SITENUM; i++ )
    {
        val[i] = qtmu0.GetMeasureResult(i);
        TPLH ->SetTestResult(i, 0, val[i]);
    }
    qtmu0.Disconnect();
	delay_ms(1);
	FOVI12.Set(FV,0,FOVI_5V,FOVI_100MA,RELAY_ON);
	FOVI13.Set(FV,0,FOVI_5V,FOVI_100MA,RELAY_ON);
	delay_ms(1);
	FOVI12.Set(FV,0,FOVI_5V,FOVI_100MA,RELAY_OFF);
	FOVI13.Set(FV,0,FOVI_5V,FOVI_100MA,RELAY_OFF);
	delay_ms(1);

	//------------ Freq_Squ -------------

	//------------ Tevent -------------


	double awg_pattern[1000] = {0.0};
	int sam = 100;
	int interval = 100;
	int j = 0;
	double Tevent[SITENUM][10]= {0.0};
	double adresult[SITENUM]={0.0};

	FOVI12.Set(FV, 0, FOVI_5V, FOVI_1A, RELAY_ON);//the V_range(FOVI_5V) and I_range(FOVI_1A) should be the same with AwgLoader

	STSAWGCreateSquareData(&awg_pattern[0], sam, 2, 5, 2.5, 50); //squarewave, awgData=0, awgSize=100, wavecycle=1, Vpp=5V, DCoffset=0V, dutycycle=0
	FOVI12.AwgLoader("Squ_AWG", FV, FOVI_5V, FOVI_1A, awg_pattern, sam);//load the data of "awg_pattern"(sam=100), named "Squ_AWG"
	FOVI12.Set(FV, 0, FOVI_5V, FOVI_1A, RELAY_ON);//the V_range(FOVI_5V) and I_range(FOVI_1A) should be the same with AwgLoader
	FOVI12.AwgSelect("Squ_AWG", 0, sam-1, 0, interval);
	STSEnableAWG(&FOVI12);
	FOVI12.AwgRun("Squ_AWG ", 0, (sam-1), 0, interval, AWG_LOOP);//select AWGpattern of "Squ_AWG" for LOOP, startAddr=0, stopAddr=sam-1, loopBackAddr=0, awgInterval=10us
	STSAWGRun();
	delay_ms(1);

	qtmu1.Init();
	qtmu1.SetStartInput(QTMU_PLUS_IMPEDANCE_1M,QTMU_PLUS_VRNG_5V,QTMU_PLUS_FILTER_PASS); 
	qtmu1.SetStopInput(QTMU_PLUS_IMPEDANCE_1M,QTMU_PLUS_VRNG_5V,QTMU_PLUS_FILTER_PASS); 

	qtmu1.SetStartTrigger(2, QTMU_PLUS_POS_SLOPE); //trigger=2V, captured the first event for rising edge 
	qtmu1.SetInSource(QTMU_PLUS_SINGLE_SOURCE); //SINGLE_SOURCE 
	qtmu1.Connect();
	delay_ms(1);

	//qtmu1.MeasFreq(QTMU_PLUS_COARSE,QTMU_PLUS_TRNG_US,10,10); //cycle number=10，timeout=10ms
	qtmu1.EventCounter(3,20);//choose 5 event to capture //set the trigger signal here 

	for (int i = 0; i < SITENUM; i++)
	{
		for(j=0;j<3;j++) 
		{ 
			Tevent[i][j]= qtmu1.GetEventCounterMeasureResult(i,j); 
		} 
		
		Tevent0->SetTestResult(i,0,Tevent[i][0]*1e-3);
		Tevent1->SetTestResult(i,0,Tevent[i][1]*1e-3);
		Tevent2->SetTestResult(i,0,Tevent[i][2]*1e-3);

		val[i] = qtmu1.GetMeasureResult(i);
		Freq_Squ->SetTestResult(i, 0, val[i]);
	}
	FOVI12.AwgStop();
	FOVI12.Set(FV, 0, FOVI_5V, FOVI_1A, RELAY_ON);
	qtmu1.Disconnect();
    return 0;
}


DUT_API int DIO(short funcindex, LPCTSTR funclabel)
{
    //{{AFX_STS_PARAM_PROTOTYPES
    CParam *C_data = StsGetParam(funcindex,"C_data");
    CParam *I2C_data = StsGetParam(funcindex,"I2C_data");
    //}}AFX_STS_PARAM_PROTOTYPES

    // TODO: Add your function code here
	dio.Connect();
	delay_ms(1);

    dio.RunPatternWithLabel("lable_1", "lable_2"); 
    delay_us(500);
    
	for(i=0; i<SITENUM; i++)
	{
		pattern = dio.GetSerialPatternResultWithLabel(3, "lable_1", "lable_2", MSB);
        C_data->SetTestResult(i, 0, pattern);
	}
    
    
	

	dio.SetOnTheFlyWithLabel(DIO::OnTheFly1,"a1","a2");
	dio.SetOnTheFlyWithLabel(DIO::OnTheFly2,"a1","a2");
	dio.RunPatternWithLabel("a1", "a2"); 
	delay_ms(30);

	



	double Period = 10e3;
	dio.I2CSet(0,1,2,3,-1,-1,-1,-1);//site1 , sda0,clk0
	dio.I2CSetClockFreq(Period);
	dio.I2CWriteData(0X30,0XA0,0X7C,DIO::I2CByte1);
	dio.I2CReadData(0X30,0XA0, 1);// Read 1 byte data from device address 0X30 and register address 0XA0

	for(i=0; i<SITENUM; i++)
	{
		
        adresult[i] = dio.I2CGetReadData(i, 1);
		I2C_data->SetTestResult(i, 0, adresult[i]);
	}
    
	



    return 0;
}


DUT_API int HVI1K(short funcindex, LPCTSTR funclabel)
{
    //{{AFX_STS_PARAM_PROTOTYPES
    CParam *IDSS = StsGetParam(funcindex,"IDSS");
    CParam *BVDSS = StsGetParam(funcindex,"BVDSS");
    //}}AFX_STS_PARAM_PROTOTYPES

    // TODO: Add your function code here

	hvi1k0.Set(FI, 0, HVI1K_1000V, HVI1K_1MA, RELAY_ON);//set 1MA range to give 250uA
	delay_ms(1);

	hvi1k0.SetRiseTime(HVI1K_FAST);//set risetime to FAST
	hvi1k0.Set(FI, -250e-6, HVI1K_1000V, HVI1K_1MA, RELAY_ON);//set 1MA range to give 250uA
	delay_ms(30);
	hvi1k0.MeasureVI(MV, 100, 20);//set mode to MV, sample number is 100, interval time is 20us
	for(i=0; i<SITENUM; i++)
	{
		adresult[i] = hvi1k0.GetMeasResult(i);//return the average value to adresult	
		BVDSS->SetTestResult(i, 0, adresult[i]);//V
	}
	hvi1k0.Set(FV, 0, HVI1K_1000V, HVI1K_1MA, RELAY_ON); //set current to 0
	delay_ms(5); //delay sevral ms to wait voltage reduce to 0

	hvi1k0.SetRiseTime(HVI1K_FAST);//set risetime to FAST
	hvi1k0.Set(FV, 500, HVI1K_1000V, HVI1K_1MA, RELAY_ON);//Advise using the 1MA range to set the 500V to save setting time.
	delay_ms(10);//delay for 10ms to ensure 500V is seted
	hvi1k0.Set(FV, 500, HVI1K_1000V, HVI1K_1UA, RELAY_ON);//change 1MA range to 1UA, in order to measure small current.
	delay_ms(30);//Advise to set delay time between 10ms-50ms
	hvi1k0.MeasureVI(MI, 100, 20);//set mode to MI, sample number is 100, interval time is 20us
	for(i=0; i<SITENUM; i++)
	{
		adresult[i] = hvi1k0.GetMeasResult(i);//return the average value to adresult
		IDSS->SetTestResult(i, 0, adresult[i]*1e-6);//convert unit A to uA
	}

	hvi1k0.Set(FV, 0, HVI1K_1000V, HVI1K_1MA, RELAY_ON);//set voltage to 0
	delay_ms(5); //delay sevral ms to wait voltage reduce to 0
	hvi1k0.Set(FV, 0, HVI1K_1000V, HVI1K_1MA, RELAY_OFF);//set output relay to RELAY_OFF in the end
	delay_ms(1);


    return 0;
}
