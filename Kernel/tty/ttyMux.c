#include "../VideoDriver/driver.h"
#include "vterm.h"
#include "tty.h"
#include "../include/lib.h"

#define KERNEL_LOG_VT 7

static vterm_t vt[8];
static int active_vt_id = 0;
static int is_tty_initialized = 0;

static void flip_tty();

void init_tty()
{
  int i = 0;
  char vt_msg[] = "tty0\n";

  //Quantity of ttys = 8
  for(; i<8; i++) {
      vt[i] = new_vterm();
      if(i==KERNEL_LOG_VT) {
        write_vterm(vt[i], "::::: kernel log :::::\n", 23);
      } else {
        vt_msg[3] = '0' + i + 1;
        write_vterm(vt[i], vt_msg, 5);
      }
  }
  active_vt_id = 0;
  is_tty_initialized=1;
}

void write_tty(const char * buff, size_t count)
{
  if(!is_tty_initialized)
    return;
  write_vterm(vt[get_vt_thread(current_thread())], buff, count);
  if(get_vt_thread(current_thread()) == active_vt_id)
    flip_tty(); //solo se hace si la terminal activa es la del proceso que hizo el write
}


void read_tty(char * buff, size_t count)
{
  if(!is_tty_initialized)
    return;
  read_vterm(vt[get_vt_thread(current_thread())], buff, count);
}

void flip_tty()
{
  if(!is_tty_initialized)
    return;
  cpytext_vterm(vt[active_vt_id], (void(*)(char, uint8_t, uint8_t, uint8_t))videoPutChar);
}

void set_fg_tty(int vterm_id, tid_t tid)
{
    set_fg_vterm(vt[vterm_id], tid);
}

void keyPressed_tty(keycode_t key) //esto se hace en la terminal activa
{
  if(!is_tty_initialized)
    return;
  if(key.action == KBD_ACTION_PRESSED) {
    switch (key.code) {
      case 0x01:  active_vt_id = 0; flip_tty(); return;
      case 0x02:  active_vt_id = 1; flip_tty(); return;
      case 0x03:  active_vt_id = 2; flip_tty(); return;
      case 0x04:  active_vt_id = 3; flip_tty(); return;
      case 0x05:  active_vt_id = 4; flip_tty(); return;
      case 0x06:  active_vt_id = 5; flip_tty(); return;
      case 0x07:  active_vt_id = 6; flip_tty(); return;
      case 0x08:  active_vt_id = 7; flip_tty(); return;
    }
  }
  keyPressed_vterm(vt[active_vt_id], key);
  flip_tty();
}
extern void halt_cpu();
void switch_to_kernel_log_tty()
{
  k_log("Exception!\n");
  active_vt_id = 7; flip_tty();
  while(1) { halt_cpu(); }
}

void k_log_putchar(void * p, char c)
{
  if(!is_tty_initialized)
    return;
  write_vterm(vt[KERNEL_LOG_VT], &c, 1);
  if(active_vt_id == KERNEL_LOG_VT)
  flip_tty(); //solo se hace si la terminal del kernel esta activa
}
