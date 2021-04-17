Load Protocol (ISO15693)

SR  0F 98 //Configure T0
          //���ö�ʱ��0�Ŀ��ƼĴ���
          //��ʱ���ڴ������ʱ�Զ���ʼ 
          //������ֵ�ﵽ��ʱ����ʱ����T0ReloadValue��Ԥ��ֵ������ʱ 
          //��ʱ��0����ʱ������Ϊ13.56 MHz

SR  14 92 //Configure T1 and cascade it with T0
          //���ö�ʱ��1�Ŀ��ƼĴ���
          //��ʱ���ڴ������ʱ�Զ���ʼ 
          //��ʱ��1����ʱ��Ϊ��ʱ��0������

SR  19 20 //Configure T2 for LFO AutoTrimm 
          //���ö�ʱ��2�Ŀ��ƼĴ���
          //��ʱ������������ʱ��LFO΢����PosEdgeʱ����/ֹͣ��
          //��ʱ���ݼ���0��ֹͣ������ʱ������ʱ�� Timer2Irqλ������Ϊ1�� 
          //��ʱ��2����ʱ����13.56 MHz  

SR  1A 03 //T2 reload value for LFO AutoTrimm
          //���ö�ʱ��2Ԥ��ֵ�ĸ��ֽ�
          //��ʱ���������¼����ؼĴ���T2ReloadValHi�ͼĴ���T2ReloadValLoֵ��
          //�ı�˼Ĵ����������´������¼�Ӱ�춨ʱ����
            
SR  1B FF //���ö�ʱ��2Ԥ��ֵ�ĵ��ֽ�

SR  1E 00 //Configure T3 (for LPCD/ AutoTrimm) 
          //��ʱ��3�Ŀ��ƼĴ���
          //��ʱ��3�����Զ���ʼ
          //��ʱ��3����ʱ����13.56 MHz
  
SR  02 90 //Set FiFo-Size and Waterlevel
          //����FIFO���ƼĴ���
          //FIFO��СΪ255�ֽ�
          //����Ϊ�����FIFO������
          
SR  03 FE 

SR  0C 80 // Init. RxBitCtrl register
          //���ý��������ƼĴ���
          //���������ڽ��շ�����ײλ�ú��ÿ��λ����0ȡ��
          //�˹�������ISO/IEC 14443����ײ 
          //�������ڽ��յ��ĵ�һ����Чλ��λ�á�
          //�������յ���λ����ݵ�һλ��λ�õ���
          //0x80���ý���λ��LSB�洢�ڵ�0λ���ڶ������յ�λ�洢�ڵ�1λλ�� 
          //ע�⣺���RxAlign(bit6-bit4)=0�����ݽ������ֽ�Ϊ������λ��������λΪ������λ��
          //��������λΪ������λͨ���н��յ�����������ֽڵ���Чλ�������Ϊ�㣬�����ֽڶ�Ϊ��Ч��

SR  28 80 //���ý��������ƼĴ���
          //��TX2���ŷ�ת�����2���ź�
          //����TX1 �� TX2 ���迹ģʽ
          
SR  29 00 // Init. TxAmp register 
          //����TxAmp�Ĵ�����TX1�ĵ�ѹ�������������ܵ����
          //����������������ٹ̶�ֵ��
          //����4����TVDD�۳�����Ԥ��ֵ��TVDD-100 mV    
          //�趨ʣ���ز��ٷֱ�
          //����ʣ���ز��͵���ָ��
          //ʣ���ز�:99%������ָ����0.5% 

SR  2A 01 // Init. DrvCon register
          //����TxEnvelopeΪ����Դ
          
SR  2B 05 // Init. TxI register
          //���ù���΢��ֵ������Ԥ��Tx �ĸ��ص���
          //�������Ԥ�ڸ��ص����������ý��Ż��ķ�ʽ���Ƶ���ָ����
          //��ʱ����Ϊ0x05
              
SR  34 00 // Init RxSOFD register 
          //��Ҫ�����ü�⵽SOF���ᷢ��RxSOFIrq�ȵȣ���ء�
          //0x00���ǲ�������Щ 

SR  38 12 // Init. RCV register
          //����Ϊȫ���RXP��������ģʽ
          //ADC����������ģʽ
          //����Ϊ��������1/4���ź�ǿ�ȣ�������Ϊ��ײ

SR  00 00 // Cancel any command execution.Flush Fifo, Clear IRQ1, IRQ2
          //ֹͣ�κ���� 
					
SR  02 B0 //FIFO��СΪ255�ֽ�
          //������Ϊ�����FIFO������
           
SR  06 7F //��λ6��λ0д��1ʱ���һЩ�ж�����
          //����HiAlertIrq��LoQlertIrq��IdleIrq��TxIrq��RxIrq��ErrIrq��RxSOFIrq

SR  07 7F //��λ5��λ0д��1ʱ�����λ���ж�����
          //bit6   GlobalIrq   ����Ч��Irq ����ʱ����
          //bit5   LPCD_Irq    �ڵ͹��Ŀ�������У�LPCD���м�⵽��ʱ����  
          //bit4   Timer4Irq   ����Ϊ�߼�1������ʱ��4�������硣
          //bit3   Timer3Irq   ����Ϊ�߼�1������ʱ��3�������硣
          //bit2   Timer2Irq   ����Ϊ�߼�1������ʱ��2�������硣
          //bit1   Timer1Irq   ����Ϊ�߼�1������ʱ��1�������硣
          //bit0   Timer0Irq   ����Ϊ�߼�1������ʱ��0�������硣
// Write in FIFO "Load protocol" params(TxProtocol=Iso15693(0a), RxProtocol=Iso15693(0a),
SR  05 0A 
SR  05 0A 
SR  08 10 // Enable IRQ0, IRQ1 interrupt sources
          //ʹ��IRQ0��IRQ1�ж�Դ
          //����Ϊ��������ж�����IdleIrqEn=1��
 
SR  09 40 //����Ϊ����ȫ���ж�����
          
SR  00 0D // Execute Rc663 command: "Load protocol"
          //ִ��Rc663���������Э�顱

SLP 100

SR  08 00 //IRQ0���ж�����ʹ�ܼĴ����������ж�ȫ����ʹ��
SR  09 00 //IRQ1���ж�����ʹ�ܼĴ����������ж�ȫ����ʹ��

SR  02 B0 // Flush FIFO
          //����Ϊ�����FIFO������

//> Apply RegisterSet
SR  2C 7B //����TxCrcPreset�Ĵ���������CRCԤ�ã�
          //����ΪCRC16
          //CRC�Ĵ���Ԥ��ֵΪcrc16->FFFFH
 
SR  2D 7B //����RxCrcPreset�Ĵ���������CRCԤ�ã�
          //����ΪCRC16
          //CRC�Ĵ���Ԥ��ֵΪcrc16->FFFFH

/////////////����Ϊ���������üĴ���/////////////////           
SR  2E 08 //TxDataNum�Ĵ���  
          //����bit3=1�����ݽ��ᱻ����
        
SR  2F 00 //��������ݵ��ƿ���Ĵ�����
          //�������������ʱ�������ݵ����峤�ȡ��������ز�ʱ����+1��������
             
SR  30 00 //TxSym10BurstLen�Ĵ���
          //���Э����Ҫһ��ͻ���źţ�δ���Ƶĸ��ز���
          //�䳤�ȿ���TxSymBurstLen�����壬ֵ�ĸߵͿ���TxSym10BurstCtrl���塣
          //�˴�0x00����ͻ������1����λ��Ϊ8λ

SR  31 00 //TxWaitCtrl�Ĵ���
          //����ֹͣλ�ͷ��͵�EGT����ֹͣλ+���Ᵽ��ʱ��EGT��
          //0x00������Ϊ��ֹͣλ����EGT
          //ע�⣺��ʹ����ISO/IEC 14443 Type B

SR  33 0F //����Symbol3��Ϊֹͣ���ŷ���
          //����Symbol3��Ϊ��ʼ���ŷ���  

SR  35 02 //����Ϊ���յ���RxEOFSymbolReg�ж���Ľ�������
          //�����źŵĴ����ٶ�Ϊ 26kbd

SR  37 4E //���ý��յ�MinLevel����ע�⣺MinLevelӦ����ϵͳ������ƽ��
          //�������Ƽ������Ԫ��MinLevel

SR  39 04 //����Ĵ����������棨rcv_gain���͸�ͨת��Ƶ�ʣ�rcv_hpcf��
          //���ý����ͼ1

SR  36 8C // Set the RxWait register 
          //����RxWait��ʱ��Ϊ RxWait x��0.5/DBFreq��
          //��ʱRxWait=0x0C

SR  31 C0 //����TxWait��ʱ�������ݽ��ս���ʱ��ʼ
          //����TxWait��ʱ��ΪTxWait x 16/13.56 MHz

SR  32 00 //���ý��պͷ���֮���2������������֮������ʱ��

// Write Timer-0, Timer-1 reload values(high,low)
//д��ʱ��0����ʱ��1��װֵ
SR  10 18 //���ö�ʱ��0Ԥ��ֵ�ĸ��ֽ�Ϊ0x18
SR  11 86 //���ö�ʱ��0Ԥ��ֵ�ĵ��ֽ�Ϊ0x86
SR  15 00 //���ö�ʱ��1Ԥ��ֵ�ĸ��ֽ�Ϊ0x00
SR  16 00 //���ö�ʱ��1Ԥ��ֵ�ĵ��ֽ�Ϊ0x00
SR  29 0A //TxAmp�Ĵ���������Ŵ�
          //����TxAmp�Ĵ�����TX1�ĵ�ѹ�������������ܵ����
          //����������������ٹ̶�ֵ��
          //����4����TVDD�۳�����Ԥ��ֵ��TVDD-100 mV    
          //�趨ʣ���ز��ٷֱ�
          //����ʣ���ز��͵���ָ��
          //ʣ���ز�:83%������ָ����9.3% 

SR  28 81 //����TX2���ŷ�ת�����2���ź�
          //�κ�����£����������0��������ģʽ 

SR  0B 00 // Disable MIFARE Crypto1
          //�ر�MIFARE���� 

//> =============================================
//> FieldOn
//> =============================================
SR  28 89 //����TX2���ŷ�ת�����2���ź�
          //����TX1��TX2���Ŷ�ʹ��
          //�κ�����£����������0��������ģʽ 
//> =============================================
//> ActivateCard  ���
//> =============================================

// Set short timeout. Timer-0,Timer-1 reload values(hi,lo) 
//д��ʱ��0����ʱ��1��װֵ
SR  10 24 //���ö�ʱ��0Ԥ��ֵ�ĸ��ֽ�Ϊ0x24
SR  11 EB //���ö�ʱ��0Ԥ��ֵ�ĵ��ֽ�Ϊ0xEB
SR  15 00 //���ö�ʱ��1Ԥ��ֵ�ĸ��ֽ�Ϊ0x00
SR  16 00 //���ö�ʱ��1Ԥ��ֵ�ĵ��ֽ�Ϊ0x00

// Cancel any command execution.Flush FIFO. Clear IRQ0,IRQ1
SR  00 00 //ֹͣ�κ�����

SR  02 B0 //FIFO��СΪ255�ֽ�
          //������Ϊ�����FIFO������
SR  06 7F //��λ6��λ0д��1ʱ���һЩ�ж�����
          //����HiAlertIrq��LoQlertIrq��IdleIrq��TxIrq��RxIrq��ErrIrq��RxSOFIrq

SR  07 7F //��λ5��λ0д��1ʱ�����λ���ж�����

// Write: "Flags" and "Inventory" cmd in FIFO 
//�����ڲ�FIFO������������������
//��663�����ֲ�7.5�½�-Buffer��
SR  05 36 
SR  05 01 
SR  05 00 
SR  05 00 

SR  00 07 // Execute RC663 "Transceive" command.
          //ִ��RC663���շ������

// Wait until the command is finished
//�ȴ��������
// Enable IRQ0,IRQ1 interrupt sources
// ʹ��IRQ0��IRQ1�ж�Դ
GR  08    
SR  08 18 //IRQ0���ж�����ʹ�ܼĴ�������������ж��������������ж�����
GR  09  
SR  09 42 //IRQ1���ж�����ʹ�ܼĴ���������ȫ���ж���������ʱ��1�ж�����

   ::: L_WaitTransceiveFinished
   GR  07    // Response:  60
   JNM IOR 40 40 L_WaitTransceiveFinished

// Disable IRQ0,IRQ1 interrupt sources 
// ʹ��IRQ0��IRQ1�ж�Դ
GR  08  
SR  08 00 //IRQ0���ж�����ʹ�ܼĴ����������ж�����ȫ��������
GR  09  
SR  09 00 //IRQ1���ж�����ʹ�ܼĴ����������ж�����ȫ��������

// Get IRQ0 status
//��ȡIRQ0 ״̬
GR  06   
GR  07   

//> Read FIFO, UID
//��ȡ FIFO, UID
GR  04   
GR  05   
GR  05  
GR  05   
GR  05   
GR  05   
GR  05   
GR  05   
GR  05  
GR  05    
GR  05    
GR  06    
GR  07    
GR  04    

// Read Error status register
//��ȡ����״̬�Ĵ���
GR  0A    // Response:  00

GR  2E    // Response:  08
SR  2E 08 
GR  0C    // Response:  80
GR  2E    // Response:  08
SR  2E 08 


//> =============================================
//> Apply Waiting time 
//> =============================================

SR  10 20 //���ö�ʱ��0Ԥ��ֵ�ĸ��ֽ�Ϊ0x20
SR  11 FF //���ö�ʱ��0Ԥ��ֵ�ĵ��ֽ�Ϊ0xFF
SR  15 00 //���ö�ʱ��1Ԥ��ֵ�ĸ��ֽ�Ϊ0x00
SR  16 00 //���ö�ʱ��1Ԥ��ֵ�ĵ��ֽ�Ϊ0x00

GR  0E    // Response:  00

// Clear all IRQ1 flags
//��������жϱ�־
SR  07 7F 



//> End of the script
//> .............................................

          
