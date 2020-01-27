#include <main.h>
#include <lcd.c>
#define LCD_ENABLE_PIN  PIN_D0                                    ////
#define LCD_RS_PIN      PIN_D1                                    ////
#define LCD_RW_PIN      PIN_D2                                    ////
#define LCD_DATA4       PIN_D4                                   ////
#define LCD_DATA5       PIN_D5                                   ////
#define LCD_DATA6       PIN_D6                                    ////
#define LCD_DATA7       PIN_D7
#define echo            PIN_C3//birinci mesafe sensörü
#define trig            PIN_C2//birinci mesafe sensörü
#define echo_1          PIN_C1//ikinci mesafe sensörü
#define trig_1          PIN_C0//ikinci mesafe sensörü
#define echo_2          PIN_C4//üçüncü mesafe sensörü
#define trig_2          PIN_C5//üçüncü mesafe sensörü

unsigned long int c,d,e;//16 bit timer tutucularý
float a,b,f;//float mesafe deðerleri

float mesafe_sag[10];
float mesafe_sol[10];
float mesafe_arka[10];
float sag_toplam=0;
float sol_toplam=0;
float arka_toplam=0;
float sag_ortalama=0;
float sol_ortalama=0;
float arka_ortalama=0;

void sag_sensor(){

       setup_timer_1 ( T1_DISABLED );
       setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);
       for(int i=0;i<10;i++){
       
       
      output_high(trig_1); //Trigger ucu aktif
      delay_us(15);        //15us bekleme
      output_low(trig_1);  //Trigger ucu pasif
      //Sensör okumaya hazýr
      while(!(input(echo_1))) //Echo ucu 1 olana kadar hiçbir iþlem yapma
      {
      }
      set_timer1(0);          //Echo ucu 1 olduðu zaman timer1'i sýfýrla
      
      while((input(echo_1)))  //Echo ucu 0 olana kadar hiçbir iþlem yapma
      {
      }
      d=get_timer1();         //Echo ucu 0 olduðunda timer1 deðerini c deðiþkenine at (bizim süre deðiþkenimiz)
      b=d*0.0037;                 //Mesafeyi cm olarak ölçmek için süre deðiþkenini 58'e bölüyorum
      mesafe_sag[i]=b;
      //lcd_gotoxy(1,1);
      ///printf(lcd_putc"Sag: %0.2f ",b);
   }
   sag_toplam=(mesafe_sag[0]+mesafe_sag[1]+mesafe_sag[2]+mesafe_sag[3]+mesafe_sag[4]+mesafe_sag[5]+mesafe_sag[6]+mesafe_sag[7]+mesafe_sag[8]+mesafe_sag[9]);
   sag_ortalama=(sag_toplam/10);
   lcd_gotoxy(1,2); 
   printf(lcd_putc"Sg:%0.1f ",sag_ortalama);
}


void sol_sensor(){
       setup_timer_1 ( T1_DISABLED );
       setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);
       for(int j=0;j<10;j++){
       
      output_high(trig); //Trigger ucu aktif
      delay_us(15);        //15us bekleme
      output_low(trig);  //Trigger ucu pasif
      //Sensör okumaya hazýr
      while(!(input(echo))) //Echo ucu 1 olana kadar hiçbir iþlem yapma
      {
      }
      set_timer1(0);          //Echo ucu 1 olduðu zaman timer1'i sýfýrla
      
      while((input(echo)))  //Echo ucu 0 olana kadar hiçbir iþlem yapma
      {
      }
      c=get_timer1();         //Echo ucu 0 olduðunda timer1 deðerini c deðiþkenine at (bizim süre deðiþkenimiz)
      a=(c*0.0037); 
       mesafe_sol[j]=a;//Mesafeyi cm olarak ölçmek için süre deðiþkenini 58'e bölüyorum
     // lcd_gotoxy(1,2); 
      //printf(lcd_putc"Sol: %0.2f ",a);    
      
     
     

       }
      sol_toplam=(mesafe_sol[0]+mesafe_sol[1]+mesafe_sol[2]+mesafe_sol[3]+mesafe_sol[4]+mesafe_sol[5]+mesafe_sol[6]+mesafe_sol[7]+mesafe_sol[8]+mesafe_sol[9]);
      sol_ortalama=(sol_toplam/10);
      lcd_gotoxy(10,2);
      printf(lcd_putc"Sl:%0.1f",sol_ortalama);
}



void arka_sensor(){
       setup_timer_1 ( T1_DISABLED );
       setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);
       for(int k=0;k<10;k++){
       
      output_high(trig_2); //Trigger ucu aktif
      delay_us(15);        //15us bekleme
      output_low(trig_2);  //Trigger ucu pasif
      //Sensör okumaya hazýr
      while(!(input(echo_2))) //Echo ucu 1 olana kadar hiçbir iþlem yapma
      {
      }
      set_timer1(0);          //Echo ucu 1 olduðu zaman timer1'i sýfýrla
      
      while((input(echo_2)))  //Echo ucu 0 olana kadar hiçbir iþlem yapma
      {
      }
      e=get_timer1();         //Echo ucu 0 olduðunda timer1 deðerini c deðiþkenine at (bizim süre deðiþkenimiz)
      f=e*0.0037; 
       mesafe_arka[k]=f;//Mesafeyi cm olarak ölçmek için süre deðiþkenini 58'e bölüyorum
     // lcd_gotoxy(1,2); 
      //printf(lcd_putc"Sol: %0.2f ",a);    

       }
      arka_toplam=(mesafe_arka[0]+mesafe_arka[1]+mesafe_arka[2]+mesafe_arka[3]+mesafe_arka[4]+mesafe_arka[5]+mesafe_arka[6]+mesafe_arka[7]+mesafe_arka[8]+mesafe_arka[9]);
       arka_ortalama=( arka_toplam/10);
      lcd_gotoxy(1,1);
      printf(lcd_putc"*****G:%0.1f*****", arka_ortalama);
}


void main()
{
  a=0;
  c=0;
  b=0;
  d=0;
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);    //Timer1 ayarlarý yapýlýyor dahili clock kaynaðý ve bölme oraný 1
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
  
    lcd_init();
   
    lcd_putc("\f  PARS TECH");
    delay_ms(500);
    lcd_putc("\f");

      
   while(TRUE)
   {
   
   sag_sensor();
   delay_ms(500);
   sol_sensor();
   delay_ms(500);
   arka_sensor();
   delay_ms(500);
     
       
   }

}
