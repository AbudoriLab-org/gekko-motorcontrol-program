/*
 * 使い方はこちら
 * https://qiita.com/bleach31/items/256229d006e0b3134341
 */
#include "driver/pcnt.h"

void qei_setup_x4(pcnt_unit_t pcnt_unit, int gpioA, int gpioB)
{
  pcnt_config_t pcnt_confA;
  pcnt_config_t pcnt_confB;

  pcnt_confA.unit = pcnt_unit;
  pcnt_confA.channel = PCNT_CHANNEL_0;
  pcnt_confA.pulse_gpio_num = gpioA;
  pcnt_confA.ctrl_gpio_num = gpioB;
  pcnt_confA.pos_mode = PCNT_COUNT_INC;
  pcnt_confA.neg_mode = PCNT_COUNT_DEC;
  pcnt_confA.lctrl_mode = PCNT_MODE_REVERSE;
  pcnt_confA.hctrl_mode = PCNT_MODE_KEEP;
  pcnt_confA.counter_h_lim = 32767;
  pcnt_confA.counter_l_lim = -32768;

  pcnt_confB.unit = pcnt_unit;
  pcnt_confB.channel = PCNT_CHANNEL_1;
  pcnt_confB.pulse_gpio_num = gpioB;
  pcnt_confB.ctrl_gpio_num = gpioA;
  pcnt_confB.pos_mode = PCNT_COUNT_INC;
  pcnt_confB.neg_mode = PCNT_COUNT_DEC;
  //ここが逆になる
  pcnt_confB.lctrl_mode = PCNT_MODE_KEEP;
  pcnt_confB.hctrl_mode = PCNT_MODE_REVERSE;
  pcnt_confB.counter_h_lim = 32767;
  pcnt_confB.counter_l_lim = -32768;

  /* Initialize PCNT unit */
  pcnt_unit_config(&pcnt_confA);
  pcnt_unit_config(&pcnt_confB);

  pcnt_counter_pause(pcnt_unit);
  pcnt_counter_clear(pcnt_unit);
  pcnt_counter_resume(pcnt_unit);
}

void qei_setup_x1(pcnt_unit_t pcnt_unit, int gpioA, int gpioB)
{
  pcnt_config_t pcnt_confA;

  pcnt_confA.unit = pcnt_unit;
  pcnt_confA.channel = PCNT_CHANNEL_0;
  pcnt_confA.pulse_gpio_num = gpioA;
  pcnt_confA.ctrl_gpio_num = gpioB;
  pcnt_confA.pos_mode = PCNT_COUNT_INC;      //立ち上がりのみカウント
  pcnt_confA.neg_mode = PCNT_COUNT_DIS;      //立ち下がりはカウントしない
  pcnt_confA.lctrl_mode = PCNT_MODE_REVERSE; //立ち上がり時にB相がHighなら逆転
  pcnt_confA.hctrl_mode = PCNT_MODE_KEEP;
  pcnt_confA.counter_h_lim = 32767;//max 32767;
  pcnt_confA.counter_l_lim = -32767;//min -32768;

  /* Initialize PCNT unit */
  pcnt_unit_config(&pcnt_confA);

  //割り込み設定
  //pcnt_event_enable(pcnt_unit, PCNT_EVT_ZERO);
  //pcnt_event_enable(pcnt_unit, PCNT_EVT_H_LIM);
  //pcnt_event_enable(pcnt_unit, PCNT_EVT_L_LIM);

  pcnt_counter_pause(pcnt_unit);
  pcnt_counter_clear(pcnt_unit);
  pcnt_counter_resume(pcnt_unit);
}
