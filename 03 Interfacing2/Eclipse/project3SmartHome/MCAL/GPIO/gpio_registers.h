/******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio_registers.h
 *
 * Description: 
 *
 * Created on: Sep 28, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef MCAL_GPIO_GPIO_REGISTERS_H_
#define MCAL_GPIO_GPIO_REGISTERS_H_

#include "../../std_types.h"

// Auto-generated register typedefs and defines

typedef union
{
  struct
  {
    uint8 c :1;
    uint8 z :1;
    uint8 n :1;
    uint8 v :1;
    uint8 s :1;
    uint8 h :1;
    uint8 t :1;
    uint8 i :1;
  };
} SREGbits_t;
#define SREGbits (*((volatile SREGbits_t*)(0x5F)))

typedef union
{
  struct
  {
    uint8 sp8 :1;
    uint8 sp9 :1;
    uint8 sp10 :1;
    uint8 sp11 :1;
    uint8 :1;
    uint8 :1;
    uint8 :1;
    uint8 :1;
  };
} SPHbits_t;
#define SPHbits (*((volatile SPHbits_t*)(0x5E)))

typedef union
{
  struct
  {
    uint8 sp0 :1;
    uint8 sp1 :1;
    uint8 sp2 :1;
    uint8 sp3 :1;
    uint8 sp4 :1;
    uint8 sp5 :1;
    uint8 sp6 :1;
    uint8 sp7 :1;
  };
} SPLbits_t;
#define SPLbits (*((volatile SPLbits_t*)(0x5D)))

typedef union
{
  struct
  {
    uint8 ivce :1;
    uint8 ivsel :1;
    uint8 :1;
    uint8 :1;
    uint8 :1;
    uint8 int2 :1;
    uint8 int0 :1;
    uint8 int1 :1;
  };
} GICRbits_t;
#define GICRbits (*((volatile GICRbits_t*)(0x5B)))

typedef union
{
  struct
  {
    uint8 :1;
    uint8 :1;
    uint8 :1;
    uint8 :1;
    uint8 :1;
    uint8 intf2 :1;
    uint8 intf0 :1;
    uint8 intf1 :1;
  };
} GIFRbits_t;
#define GIFRbits (*((volatile GIFRbits_t*)(0x5A)))

typedef union
{
  struct
  {
    uint8 toie0 :1;
    uint8 ocie0 :1;
    uint8 toie1 :1;
    uint8 ocie1b :1;
    uint8 ocie1a :1;
    uint8 ticie1 :1;
    uint8 toie2 :1;
    uint8 ocie2 :1;
  };
} TIMSKbits_t;
#define TIMSKbits (*((volatile TIMSKbits_t*)(0x59)))

typedef union
{
  struct
  {
    uint8 tov0 :1;
    uint8 ocf0 :1;
    uint8 tov1 :1;
    uint8 ocf1b :1;
    uint8 ocf1a :1;
    uint8 icf1 :1;
    uint8 tov2 :1;
    uint8 ocf2 :1;
  };
} TIFRbits_t;
#define TIFRbits (*((volatile TIFRbits_t*)(0x58)))

typedef union
{
  struct
  {
    uint8 spmen :1;
    uint8 pgers :1;
    uint8 pgwrt :1;
    uint8 blbset :1;
    uint8 rwwsre :1;
    uint8 :1;
    uint8 rwwsb :1;
    uint8 spmie :1;
  };
} SPMCRbits_t;
#define SPMCRbits (*((volatile SPMCRbits_t*)(0x57)))

typedef union
{
  struct
  {
    uint8 twie :1;
    uint8 :1;
    uint8 twen :1;
    uint8 twwc :1;
    uint8 twsto :1;
    uint8 twsta :1;
    uint8 twea :1;
    uint8 twint :1;
  };
} TWCRbits_t;
#define TWCRbits (*((volatile TWCRbits_t*)(0x56)))

typedef union
{
  struct
  {
    uint8 isc00 :1;
    uint8 isc01 :1;
    uint8 isc10 :1;
    uint8 isc11 :1;
    uint8 sm0 :1;
    uint8 sm1 :1;
    uint8 sm2 :1;
    uint8 se :1;
  };
} MCUCRbits_t;
#define MCUCRbits (*((volatile MCUCRbits_t*)(0x55)))

typedef union
{
  struct
  {
    uint8 porf :1;
    uint8 extrf :1;
    uint8 borf :1;
    uint8 wdrf :1;
    uint8 jtrf :1;
    uint8 :1;
    uint8 isc2 :1;
    uint8 jtd :1;
  };
} MCUCSRbits_t;
#define MCUCSRbits (*((volatile MCUCSRbits_t*)(0x54)))

typedef union
{
  struct
  {
    uint8 cs00 :1;
    uint8 cs01 :1;
    uint8 cs02 :1;
    uint8 wgm01 :1;
    uint8 com00 :1;
    uint8 com01 :1;
    uint8 wgm00 :1;
    uint8 foc0 :1;
  };
  struct
  {
    uint8 cs0 :3;
    uint8 :1;
    uint8 com0 :2;

  };
} TCCR0bits_t;
#define TCCR0bits (*((volatile TCCR0bits_t*)(0x53)))

typedef union
{
  struct
  {
    uint8 psr10 :1;
    uint8 psr2 :1;
    uint8 pud :1;
    uint8 acme :1;
    uint8 :1;
    uint8 adts0 :1;
    uint8 adts1 :1;
    uint8 adts2 :1;
  };
} SFIORbits_t;
#define SFIORbits (*((volatile SFIORbits_t*)(0x50)))

typedef union
{
  struct
  {
    uint8 wgm10 :1;
    uint8 wgm11 :1;
    uint8 foc1b :1;
    uint8 foc1a :1;
    uint8 com1b0 :1;
    uint8 com1b1 :1;
    uint8 com1a0 :1;
    uint8 com1a1 :1;
  };
} TCCR1Abits_t;
#define TCCR1Abits (*((volatile TCCR1Abits_t*)(0x4F)))

typedef union
{
  struct
  {
    uint8 cs10 :1;
    uint8 cs11 :1;
    uint8 cs12 :1;
    uint8 wgm12 :1;
    uint8 wgm13 :1;
    uint8 :1;
    uint8 ices1 :1;
    uint8 icnc1 :1;
  };
} TCCR1Bbits_t;
#define TCCR1Bbits (*((volatile TCCR1Bbits_t*)(0x4E)))

typedef union
{
  struct
  {
    uint8 cs20 :1;
    uint8 cs21 :1;
    uint8 cs22 :1;
    uint8 wgm21 :1;
    uint8 com20 :1;
    uint8 com21 :1;
    uint8 wgm20 :1;
    uint8 foc2 :1;
  };
} TCCR2bits_t;
#define TCCR2bits (*((volatile TCCR2bits_t*)(0x45)))

typedef union
{
  struct
  {
    uint8 tcr2ub :1;
    uint8 ocr2ub :1;
    uint8 tcn2ub :1;
    uint8 as2 :1;
    uint8 :1;
    uint8 :1;
    uint8 :1;
    uint8 :1;
  };
} ASSRbits_t;
#define ASSRbits (*((volatile ASSRbits_t*)(0x42)))

typedef union
{
  struct
  {
    uint8 wdp0 :1;
    uint8 wdp1 :1;
    uint8 wdp2 :1;
    uint8 wde :1;
    uint8 wdtoe :1;
    uint8 :1;
    uint8 :1;
    uint8 :1;
  };
} WDTCRbits_t;
#define WDTCRbits (*((volatile WDTCRbits_t*)(0x41)))

typedef union
{
  struct
  {
    uint8 ucpol :1;
    uint8 ucsz0 :1;
    uint8 ucsz1 :1;
    uint8 usbs :1;
    uint8 upm0 :1;
    uint8 upm1 :1;
    uint8 umsel :1;
    uint8 ursel :1;
  };
} UCSRCbits_t;
#define UCSRCbits (*((volatile UCSRCbits_t*)(0x40)))

typedef union
{
  struct
  {
    uint8 eear8 :1;
    uint8 eear9 :1;
    uint8 :1;
    uint8 :1;
    uint8 :1;
    uint8 :1;
    uint8 :1;
    uint8 :1;
  };
} EEARHbits_t;
#define EEARHbits (*((volatile EEARHbits_t*)(0x3F)))

typedef union
{
  struct
  {
    uint8 eere :1;
    uint8 eewe :1;
    uint8 eemwe :1;
    uint8 eerie :1;
    uint8 :1;
    uint8 :1;
    uint8 :1;
    uint8 :1;
  };
} EECRbits_t;
#define EECRbits (*((volatile EECRbits_t*)(0x3C)))

typedef union
{
  struct
  {
    uint8 porta0 :1;
    uint8 porta1 :1;
    uint8 porta2 :1;
    uint8 porta3 :1;
    uint8 porta4 :1;
    uint8 porta5 :1;
    uint8 porta6 :1;
    uint8 porta7 :1;
  };
} PORTAbits_t;
#define PORTAbits (*((volatile PORTAbits_t*)(0x3B)))

typedef union
{
  struct
  {
    uint8 dda0 :1;
    uint8 dda1 :1;
    uint8 dda2 :1;
    uint8 dda3 :1;
    uint8 dda4 :1;
    uint8 dda5 :1;
    uint8 dda6 :1;
    uint8 dda7 :1;
  };
} DDRAbits_t;
#define DDRAbits (*((volatile DDRAbits_t*)(0x3A)))

typedef union
{
  struct
  {
    uint8 pina0 :1;
    uint8 pina1 :1;
    uint8 pina2 :1;
    uint8 pina3 :1;
    uint8 pina4 :1;
    uint8 pina5 :1;
    uint8 pina6 :1;
    uint8 pina7 :1;
  };
} PINAbits_t;
#define PINAbits (*((volatile PINAbits_t*)(0x39)))

typedef union
{
  struct
  {
    uint8 portb0 :1;
    uint8 portb1 :1;
    uint8 portb2 :1;
    uint8 portb3 :1;
    uint8 portb4 :1;
    uint8 portb5 :1;
    uint8 portb6 :1;
    uint8 portb7 :1;
  };
} PORTBbits_t;
#define PORTBbits (*((volatile PORTBbits_t*)(0x38)))

typedef union
{
  struct
  {
    uint8 ddb0 :1;
    uint8 ddb1 :1;
    uint8 ddb2 :1;
    uint8 ddb3 :1;
    uint8 ddb4 :1;
    uint8 ddb5 :1;
    uint8 ddb6 :1;
    uint8 ddb7 :1;
  };
} DDRBbits_t;
#define DDRBbits (*((volatile DDRBbits_t*)(0x37)))

typedef union
{
  struct
  {
    uint8 pinb0 :1;
    uint8 pinb1 :1;
    uint8 pinb2 :1;
    uint8 pinb3 :1;
    uint8 pinb4 :1;
    uint8 pinb5 :1;
    uint8 pinb6 :1;
    uint8 pinb7 :1;
  };
} PINBbits_t;
#define PINBbits (*((volatile PINBbits_t*)(0x36)))

typedef union
{
  struct
  {
    uint8 portc0 :1;
    uint8 portc1 :1;
    uint8 portc2 :1;
    uint8 portc3 :1;
    uint8 portc4 :1;
    uint8 portc5 :1;
    uint8 portc6 :1;
    uint8 portc7 :1;
  };
} PORTCbits_t;
#define PORTCbits (*((volatile PORTCbits_t*)(0x35)))

typedef union
{
  struct
  {
    uint8 ddc0 :1;
    uint8 ddc1 :1;
    uint8 ddc2 :1;
    uint8 ddc3 :1;
    uint8 ddc4 :1;
    uint8 ddc5 :1;
    uint8 ddc6 :1;
    uint8 ddc7 :1;
  };
} DDRCbits_t;
#define DDRCbits (*((volatile DDRCbits_t*)(0x34)))

typedef union
{
  struct
  {
    uint8 pinc0 :1;
    uint8 pinc1 :1;
    uint8 pinc2 :1;
    uint8 pinc3 :1;
    uint8 pinc4 :1;
    uint8 pinc5 :1;
    uint8 pinc6 :1;
    uint8 pinc7 :1;
  };
} PINCbits_t;
#define PINCbits (*((volatile PINCbits_t*)(0x33)))

typedef union
{
  struct
  {
    uint8 portd0 :1;
    uint8 portd1 :1;
    uint8 portd2 :1;
    uint8 portd3 :1;
    uint8 portd4 :1;
    uint8 portd5 :1;
    uint8 portd6 :1;
    uint8 portd7 :1;
  };
} PORTDbits_t;
#define PORTDbits (*((volatile PORTDbits_t*)(0x32)))

typedef union
{
  struct
  {
    uint8 ddd0 :1;
    uint8 ddd1 :1;
    uint8 ddd2 :1;
    uint8 ddd3 :1;
    uint8 ddd4 :1;
    uint8 ddd5 :1;
    uint8 ddd6 :1;
    uint8 ddd7 :1;
  };
} DDRDbits_t;
#define DDRDbits (*((volatile DDRDbits_t*)(0x31)))

typedef union
{
  struct
  {
    uint8 pind0 :1;
    uint8 pind1 :1;
    uint8 pind2 :1;
    uint8 pind3 :1;
    uint8 pind4 :1;
    uint8 pind5 :1;
    uint8 pind6 :1;
    uint8 pind7 :1;
  };
} PINDbits_t;
#define PINDbits (*((volatile PINDbits_t*)(0x30)))

typedef union
{
  struct
  {
    uint8 spi2x :1;
    uint8 :1;
    uint8 :1;
    uint8 :1;
    uint8 :1;
    uint8 :1;
    uint8 wcol :1;
    uint8 spif :1;
  };
} SPSRbits_t;
#define SPSRbits (*((volatile SPSRbits_t*)(0x2E)))

typedef union
{
  struct
  {
    uint8 spr0 :1;
    uint8 spr1 :1;
    uint8 cpha :1;
    uint8 cpol :1;
    uint8 mstr :1;
    uint8 dord :1;
    uint8 spe :1;
    uint8 spie :1;
  };
} SPCRbits_t;
#define SPCRbits (*((volatile SPCRbits_t*)(0x2D)))

typedef union
{
  struct
  {
    uint8 mpcm :1;
    uint8 u2x :1;
    uint8 pe :1;
    uint8 dor :1;
    uint8 fe :1;
    uint8 udre :1;
    uint8 txc :1;
    uint8 rxc :1;
  };
} UCSRAbits_t;
#define UCSRAbits (*((volatile UCSRAbits_t*)(0x2B)))

typedef union
{
  struct
  {
    uint8 txb8 :1;
    uint8 rxb8 :1;
    uint8 ucsz2 :1;
    uint8 txen :1;
    uint8 rxen :1;
    uint8 udrie :1;
    uint8 txcie :1;
    uint8 rxcie :1;
  };
} UCSRBbits_t;
#define UCSRBbits (*((volatile UCSRBbits_t*)(0x2A)))

typedef union
{
  struct
  {
    uint8 acis0 :1;
    uint8 acis1 :1;
    uint8 acic :1;
    uint8 acie :1;
    uint8 aci :1;
    uint8 aco :1;
    uint8 acbg :1;
    uint8 acd :1;
  };
} ACSRbits_t;
#define ACSRbits (*((volatile ACSRbits_t*)(0x28)))

typedef union
{
  struct
  {
    uint8 mux0 :1;
    uint8 mux1 :1;
    uint8 mux2 :1;
    uint8 mux3 :1;
    uint8 mux4 :1;
    uint8 adlar :1;
    uint8 refs0 :1;
    uint8 refs1 :1;
  };
  struct
  {
    uint8 mux :5;
    uint8 :1;
    uint8 refs :2;
  };
} ADMUXbits_t;
#define ADMUXbits (*((volatile ADMUXbits_t*)(0x27)))

typedef union
{
  struct
  {
    uint8 adps0 :1;
    uint8 adps1 :1;
    uint8 adps2 :1;
    uint8 adie :1;
    uint8 adif :1;
    uint8 adate :1;
    uint8 adsc :1;
    uint8 aden :1;
  };
  struct
  {
    uint8 adps :3;
    uint8 :5;
  };
} ADCSRAbits_t;
#define ADCSRAbits (*((volatile ADCSRAbits_t*)(0x26)))

typedef union
{
  struct
  {
    uint8 twgce :1;
    uint8 twa0 :1;
    uint8 twa1 :1;
    uint8 twa2 :1;
    uint8 twa3 :1;
    uint8 twa4 :1;
    uint8 twa5 :1;
    uint8 twa6 :1;
  };
} TWARbits_t;
#define TWARbits (*((volatile TWARbits_t*)(0x22)))

typedef union
{
  struct
  {
    uint8 twps0 :1;
    uint8 twps1 :1;
    uint8 :1;
    uint8 tws3 :1;
    uint8 tws4 :1;
    uint8 tws5 :1;
    uint8 tws6 :1;
    uint8 tws7 :1;
  };
} TWSRbits_t;
#define TWSRbits (*((volatile TWSRbits_t*)(0x21)))

#endif /* MCAL_GPIO_GPIO_REGISTERS_H_ */
